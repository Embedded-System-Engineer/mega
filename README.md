# ATmega Embedded Systems Framework

A modular embedded systems framework for AVR ATmega microcontrollers with standardized APIs, task scheduling, and hardware abstraction layers.

## 📋 Supported Microcontrollers

- **ATmega128A** - High-end 8-bit AVR with 128KB Flash
- **ATmega16** - Mid-range 8-bit AVR with 16KB Flash
- **ATmega8** - Entry-level 8-bit AVR with 8KB Flash

## 🏗️ Project Structure

```
mega/
├── inc/                          # Public headers
│   ├── mega.h                    # Main framework header
│   ├── modules.h                 # Module configuration flags
│   ├── resource.h                # Application-specific resource mapping
│   └── mega_optimized.h          # Performance optimizations
├── src/
│   ├── mega.c                    # Main entry point with initialization
│   └── mega/                     # Hardware modules
│       ├── gpio/                 # GPIO abstraction layer
│       ├── system/               # System clock & scheduler
│       ├── usart/                # Serial communication
│       ├── twi/                  # I2C/TWI interface
│       ├── lcd/                  # LCD display control
│       ├── keypad/               # Matrix keypad scanning
│       ├── button/               # Button input handling
│       ├── adc/                  # Analog-to-digital conversion
│       ├── eeprom/               # Internal EEPROM
│       ├── exeeprom/             # External EEPROM (via TWI)
│       ├── ds1307/               # Real-time clock
│       ├── Tone/                 # Tone/PWM generation
│       ├── SSD/                  # Seven-segment display
│       ├── _7seg/                # Alternative 7-segment driver
│       ├── csma/                 # CSMA communication protocol
│       ├── signalGenertor/       # Arbitrary signal generation
│       ├── lcdmnue/              # LCD menu system
│       ├── fifo/                 # FIFO buffer utility
│       ├── ZLP/                  # Zero-latency PWM
│       └── utility/              # Utility functions
├── build/                        # Build output directory
├── nbproject/                    # MPLAB X IDE project files
├── vsm/                          # Proteus simulation files
└── Makefile                      # Top-level build configuration
```

## 🎯 All Module Functions Reference

### GPIO (`src/mega/gpio/`)
**API Functions:**
```c
void gpioSetMode(gpio_t pin, gpio_mode_t mode);
void gpioWrite(gpio_t pin, gpio_state_t state);
gpio_state_t gpioRead(gpio_t pin);
```

### System & Scheduler (`src/mega/system/`)
**System Functions:**
```c
void systemInit(void);
void systemStart(void);
void systemStop(void);
millis_t systemMillis(void);
micros_t systemMicros(void);
time_t systemTime(void);
void systemSetTimerMs(system_timer_t *timer, millis_t period);
uint8_t systemIsTimeout(system_timer_t *timer);
```

**Scheduler Functions:**
```c
void schedulerInit(void);
int8_t schedulerAddTask(task_func_t func, void *arg, uint32_t period_ms);
void schedulerRun(void);
void schedulerDispatch(void);
```

### USART (`src/mega/usart/`)
```c
void usartInit(void);
void usartPutByte(usart_port_t port, uint8_t byte);
uint8_t usartGetByte(usart_port_t port);
uint8_t usartHasError(usart_port_t port);
```

### LCD (`src/mega/lcd/`)
```c
void lcdInit(void);
void lcdDriver(void);
void lcdClear(void);
void lcdSetCursor(uint8_t row, uint8_t col);
void lcdPrint(const char *str);
void lcdPrintAt(uint8_t row, uint8_t col, const char *str);
```

### Keypad (`src/mega/keypad/`)
```c
void keypadInit(void);
void keypadDriver(void);
void keypadRegisterCallback(uint8_t key_code, keypad_callback_t cb);
```

### Button (`src/mega/button/`)
```c
void buttonInit(void);
void buttonScan(void);
void buttonDriver(void);
void buttonRegisterEvent(button_callback_t cb, uint8_t index);
void buttonAssignConstantEvents(const button_code_t *events);
```

### ADC (`src/mega/ADC/`)
```c
void adcInit(const adc_config_t *config);
void adcStartConversion(adc_channel_t channel);
uint16_t adcGetValue(void);
uint16_t adcReadPolling(adc_channel_t channel);
```

### Tone/PWM (`src/mega/Tone/`)
```c
void toneInit(void);
void toneDriver(void);
void tonePlay(uint8_t channel, uint16_t period, uint8_t duration, uint16_t on_time);
void toneStop(uint8_t channel);
uint8_t toneIsPlaying(uint8_t channel);
```

### Seven-Segment Display (`src/mega/_7seg/`)
```c
void _7segInit(void);
void _7segScan(void);
_7seg_instance_t* _7segCreateDisplay(const uint8_t *digit_pins, uint8_t max_digit, uint8_t type);
void _7segRemoveDisplay(_7seg_instance_t *display);
void _7segWriteNumber(_7seg_instance_t *display, uint32_t value, uint8_t justify);
void _7segWriteString(_7seg_instance_t *display, const char *string, uint8_t justify);
void _7segWriteChar(_7seg_instance_t *display, uint8_t digit, char character);
void _7segClear(_7seg_instance_t *display);
```

### SSD Display (`src/mega/SSD/`)
```c
void ssdInit(void);
void ssdSync(void);
void ssdDriver(void);
void ssdPrint(const uint8_t *data, uint8_t start_idx, uint8_t start_digit, uint8_t length);
void ssdClearAll(void);
void ssdClearRange(uint8_t start_digit, uint8_t length, uint8_t default_char);
void ssdOpenTest(uint8_t start_digit, uint8_t end_digit, uint8_t type);
void ssdCloseTest(void);
```

### RTC DS1307 (`src/mega/ds1307/`)
```c
void ds1307Init(void);
void ds1307Driver(void);
void ds1307SetTime(const ds1307_time_t *time);
void ds1307GetTime(ds1307_time_t *time);
```

### Internal EEPROM (`src/mega/eeprom/`)
```c
void eepromInit(void);
void eepromDriver(void);
void eepromWrite(uint16_t addr, const uint8_t *data, uint8_t size);
uint8_t eepromRead(uint16_t addr, uint8_t *data, uint8_t size);
uint8_t eepromIsBusy(void);
```

### External EEPROM (`src/mega/exeeprom/`)
```c
void exepromInit(void);
void exepromDriver(void);
void exepromRead(uint16_t addr, uint8_t *buf, uint8_t len);
void exepromWrite(uint16_t addr, uint8_t *buf, uint8_t len);
uint8_t exepromIsReady(void);
```

### TWI/I2C (`src/mega/twi/`)
```c
void twiInit(uint32_t speed);
twi_status_t twiMasterTransfer(twi_package_t *pkg, uint8_t is_read);
twi_status_t twiGetStatus(void);
```

### Signal Generator (`src/mega/signalGenertor/`)
```c
void signalGenInit(void);
void signalGenDriver(void);
void signalGenStart(uint8_t channel, const signal_config_t *config);
void signalGenStop(uint8_t channel);
```

### LCD Menu (`src/mega/lcdmnue/`)
```c
void lcd_menu_init(void);
void lcd_menu_driver(void);
void lcd_menu_start(const menueItem_t *item);
uint8_t lcd_menu_is_open(void);
```

### FIFO Buffer (`src/mega/fifo/`)
```c
void fifoInit(fifo_t *fifo, uint8_t *buffer, uint16_t capacity);
fifo_status_t fifoWrite(fifo_t *fifo, const uint8_t *data, uint16_t size);
fifo_status_t fifoRead(fifo_t *fifo, uint8_t *data, uint16_t size);
fifo_status_t fifoPeek(fifo_t *fifo, uint8_t *data, uint16_t offset, uint16_t size);
uint16_t fifoGetFree(fifo_t *fifo);
uint16_t fifoGetUsed(fifo_t *fifo);
uint8_t fifoIsEmpty(fifo_t *fifo);
uint8_t fifoIsFull(fifo_t *fifo);
```

### Utility Functions (`src/mega/utility/`)
```c
uint8_t uXX_to_ascii(uint8_t *s, uint32_t x, uint8_t max);
uint8_t u32_to_ascii(uint8_t *s, uint32_t x);
uint8_t bcd_to_dec(uint8_t bcd);
uint8_t dec_to_bcd(uint8_t dec);
uint8_t map_value(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max);
uint8_t crc8_check(uint8_t *data, uint8_t len);
```

### CSMA Protocol (`src/mega/csma/`)
```c
void csmaInit(void);
void csmaDriver(void);
void csmaConfigureNode(uint8_t is_server, uint32_t activation_code);
void csmaSetOnHostRequest(csmaCallback_t cb);
void csmaSetOnClientResponse(csmaCallback_t cb);
void csmaRegisterSaveSerial(csmaSaveSerial_t cb);
uint8_t csmaPutData(uint8_t *buf, uint8_t len, uint8_t da, uint8_t type);
uint8_t csmaRequestRawFrame(uint8_t code, uint8_t *buffer, uint8_t da, uint8_t len, void (*state_cb)(uint8_t));
void csmaSetNodeIp(uint8_t ip);
void csmaSetNodeAddr(uint8_t addr);
uint8_t csmaGetNodeAddr(void);
uint8_t csmaGetMaxAddr(void);
uint8_t csmaSendFreeFrame(void);
```

### Zero-Latency PWM (`src/mega/ZLP/`)
```c
void zlpInit(void);
void zlpDriver(void);
void zlpSendData(const uint8_t *data, uint8_t len);
void zlpPrintLabel(uint8_t copies);
uint8_t zlpIsBusy(void);
```

## 🔧 Getting Started

### Build System

```bash
# Build all configurations
make all

# Build specific MCU
make CONF=Atmega128A
make CONF=ATmega16
make CONF=ATmega8

# Clean build artifacts
make clean
```

### Project Setup

1. Open in MPLAB X IDE: `File → Open Project → mega.X`
2. Select Configuration in project settings
3. Configure resources in `inc/resource.h` for pin mapping
4. Edit `inc/modules.h` to enable/disable modules

### Basic Application Template

```c
#include "mega.h"

void appBoot(void) {
    // Hardware initialization checks
}

void appInit(void) {
    // Initialize modules and register tasks
    lcdInit();
    keypadInit();
    schedulerAddTask(keypadDriver, NULL, 10);
}

void appMain(void) {
    // Non-blocking application logic
}

void appSync(void) {
    // Optional ISR context code
}
```

## 📝 Configuration

### Module Enable/Disable
Edit `inc/modules.h`:
```c
#define LCD_MODULE                (1)   // Enable
#define KEYPAD_MODULE             (1)   // Enable
#define USART_MODULE              (0)   // Disable
```

### Hardware Pin Mapping
Edit `inc/resource.h`:
```c
#define LCD_RS                    GPIO_A0
#define LCD_EN                    GPIO_A1
#define KEYPAD_C01_PIN           GPIO_B0
```

## 🏃 Initialization Sequence

1. `appBoot()` → Application boot checks
2. `systemInit()` → System clock & interrupts
3. Module inits → GPIO, USART, TWI, LCD, etc.
4. `appInit()` → Application initialization
5. Task registration → Add periodic tasks
6. `systemStart()` → Enable interrupts
7. Main loop → `schedulerDispatch()` + `appMain()`

## 📦 Typical Task Periods

- **1ms**: Signal generation, tone, PWM
- **10ms**: GPIO, keypad, buttons
- **20ms**: LCD multiplexing
- **50-100ms**: I/O, sensors, EEPROM
- **100-1000ms**: Communication, RTC sync

## 📊 Memory Usage

| Module | SRAM (Bytes) | Flash (Bytes) |
|--------|-------------|---------------|
| GPIO   | 0           | 150           |
| System | 14          | 694           |
| LCD    | 36          | 950           |
| Keypad | 50          | 764           |
| Tone   | Variable    | 400           |

## ⚙️ API Conventions

- **Init**: `{module}_init()`
- **Driver**: `{module}_driver()` (called from scheduler)
- **API**: `{module}{Action}()` (e.g., `gpioSetMode()`)
- **Types**: `{module}_t` (e.g., `gpio_t`)

## 🔗 Complete Integration Example

```c
void appInit(void) {
    lcdInit();
    keypadInit();
    adcInit(NULL);
    toneInit();
    
    schedulerAddTask(keypadDriver, NULL, 10);
    schedulerAddTask(lcdDriver, NULL, 20);
    schedulerAddTask(toneDriver, NULL, 1);
}

void appMain(void) {
    static uint32_t last_update = 0;
    uint32_t now = systemMillis();
    
    if (now - last_update >= 500) {
        uint16_t adc_val = adcReadPolling(0);
        lcdSetCursor(1, 0);
        lcdPrint("ADC: ");
        last_update = now;
    }
}
```

## 📚 Additional Resources

- **Build Output**: `build/{MCU}/production/`
- **Debug Info**: `debug/{MCU}/`
- **Version**: Run `update versions.py`
- **Simulation**: Proteus VSM projects in `vsm/`

## 📄 License

[Specify your license here]

## 👤 Author

Hassan Elsaied

---

**Framework Version**: Mega2v241022  
**Last Updated**: January 15, 2026  
**Status**: Production Ready
