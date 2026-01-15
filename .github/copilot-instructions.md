# Copilot Instructions - ATmega Embedded Systems Project

## Project Overview
This is a modular embedded systems framework for AVR ATmega microcontrollers (ATmega128A, ATmega16, ATmega8). The codebase follows a standardized API pattern with a task scheduler for cooperative multitasking.

## Architecture Overview

### Module Structure Pattern
Each hardware module follows this directory structure:
```
src/mega/{module_name}/
├── inc/
│   ├── {module}_api.h      # Public API interface
│   └── {module}_types.h    # Type definitions & enums
└── src/
    └── {module}.c          # Implementation
```

**Key modules**: `gpio`, `system`, `usart`, `twi`, `lcd`, `adc`, `keypad`, `button`, `eeprom`, `ds1307`, `tone`, `fifo`, etc.

### Critical Architecture Patterns

1. **Standardized API Design** ([../inc/mega.h](../inc/mega.h))
   - All modules expose three-layer pattern: `*_api.h` (public interface) → `*_types.h` (data definitions) → implementation
   - Example: `gpioSetMode()`, `gpioWrite()`, `gpioRead()` in [../src/mega/gpio/inc/gpio_api.h](../src/mega/gpio/inc/gpio_api.h)

2. **Task Scheduler** ([../src/mega/system/inc/scheduler_api.h](../src/mega/system/inc/scheduler_api.h))
   - Cooperative multitasking system with time-based task dispatch
   - Tasks registered with period in milliseconds via `schedulerAddTask(task_func, arg, period_ms)`
   - Main loop: `while(1) { schedulerDispatch(); appMain(); }`
   - Max 16 concurrent tasks (configurable via `MAX_TASKS` macro)

3. **Initialization Sequence** ([../src/mega.c](../src/mega.c))
   - Boot phase: `appBoot()` → `systemInit()`
   - Module init phase: Individual module initializers called sequentially
   - Task registration: Tasks added to scheduler with appropriate periods
   - Runtime: `systemStart()` launches interrupts, main loop dispatches tasks

4. **Hardware Abstraction Layer**
   - GPIO uses `gpio_t` type (uint8_t) for pin numbers, enums for modes/states
   - System provides timers: `systemMillis()`, `systemMicros()`, `systemSetTimerMs()`
   - All modules accept optional config structs in init functions (e.g., `usart_init(NULL)`)

## Build System

### Configuration-Specific Builds
- **MPLAB X IDE project** with three configurations: `Atmega128A`, `ATmega16`, `ATmega8`
- Build outputs: `build/{MCU}/production/` for firmware, `debug/` for debugging artifacts
- Makefile structure: `Makefile` → `nbproject/Makefile-{MCU}.mk` → `nbproject/Makefile-impl.mk`

### Build Commands
```bash
make all              # Build all configurations
make CONF=Atmega128A  # Build specific MCU
make clean            # Clean build artifacts
```

## Project-Specific Conventions

1. **Naming Patterns**
   - Driver functions: `{module}_driver()` (registered with scheduler)
   - API functions: `{module}{Action}()` (e.g., `gpioSetMode`, `lcdWrite`)
   - Types: `{module}_t` (e.g., `gpio_t`, `usart_config_t`)

2. **Resource Configuration**
   - [../inc/resource.h](../inc/resource.h) includes application-specific pin mappings and module configs
   - Per-application resource files can be included (commented examples reference nurse system apps)

3. **Scheduler Task Pattern**
   - Task function signature: `void task_name(void *arg)`
   - Typical periods: 1ms (signal generation, tone), 10ms (gpio, keypad, buttons), 20-100ms (IO modules)
   - Task registration happens after all module initialization but before `systemStart()`

## Working with Modules

### When Adding a New Module
1. Create `src/mega/{module_name}/{inc,src}` directories
2. Define types in `{module}_types.h` (enums, config structs)
3. Declare API functions in `{module}_api.h` (init, driver/task, control functions)
4. Implement in `src/{module}.c`
5. Add module initialization to `main()` in [../src/mega.c](../src/mega.c)
6. Register driver task with scheduler if periodic work needed
7. Include API header in [../inc/mega.h](../inc/mega.h)

### When Modifying Existing Modules
- Keep `_api.h` stable; changes must be backward compatible with [../src/mega.c](../src/mega.c)
- Driver function execution depends on scheduler period—adjust `period_ms` when changing timing
- Type changes in `_types.h` affect all dependent modules

## Integration Points & Dependencies

- **System clock**: Defined in clock configuration files, used by all timing modules
- **Interrupt handlers**: System module manages timer interrupts; other modules hook into ISRs
- **Task scheduling**: Central coordination point—all periodic work flows through scheduler
- **Hardware resources**: GPIO, USART, TWI shared across modules; manage conflicts in [../inc/resource.h](../inc/resource.h)

## Development Workflow Notes

- **Version tracking**: [../update versions.py](../update%20versions.py) auto-updates version info and Git metadata
- **Simulation**: VSM folder contains Proteus project files for hardware testing
- **Configuration macros**: Check [../inc/modules.h](../inc/modules.h) for module enable/disable flags
