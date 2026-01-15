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

## � Module Usage Examples

### GPIO Example
```c
void appInit(void) {
    // Configure GPIO pins
    gpioSetMode(GPIO_A0, GPIO_MODE_OUTPUT);
    gpioSetMode(GPIO_A1, GPIO_MODE_INPUT_PULLUP);
}

void appMain(void) {
    // Write to output
    gpioWrite(GPIO_A0, GPIO_HIGH);
    
    // Read input
    gpio_state_t input = gpioRead(GPIO_A1);
    if (input == GPIO_HIGH) {
        gpioWrite(GPIO_A0, GPIO_LOW);
    }
}
```

### LCD Display Example
```c
void appInit(void) {
    lcdInit();
    schedulerAddTask(lcdDriver, NULL, 20);
}

void appMain(void) {
    lcdClear();
    lcdSetCursor(0, 0);
    lcdPrint("Temp: 25.5C");
    lcdSetCursor(1, 0);
    lcdPrint("Humidity: 60%");
}
```

### Keypad Input Example
```c
void keypadCallback(uint8_t key_code) {
    if (key_code == '1') {
        gpioWrite(GPIO_A0, GPIO_TGL);
    }
}

void appInit(void) {
    keypadInit();
    keypadRegisterCallback('1', keypadCallback);
    schedulerAddTask(keypadDriver, NULL, 10);
}
```

### Button Input Example
```c
void buttonPressCallback(button_event_t event) {
    switch (event) {
        case BUTTON_PRESSED:
            tonePlay(0, 1000, 1, 500);  // Play 1kHz for 500ms
            break;
        case BUTTON_RELEASED:
            toneStop(0);
            break;
        default:
            break;
    }
}

void appInit(void) {
    buttonInit();
    buttonRegisterEvent(buttonPressCallback, 0);
    schedulerAddTask(buttonDriver, NULL, 10);
}
```

### ADC Reading Example
```c
void appInit(void) {
    adc_config_t config = {0};
    config.prescaler = ADC_PRESCALER_128;
    config.ref_voltage = ADC_REF_AVCC;
    adcInit(&config);
}

void appMain(void) {
    static uint32_t last_read = 0;
    if (systemMillis() - last_read >= 100) {
        uint16_t analog = adcReadPolling(ADC_CH0);
        // Use analog value
        last_read = systemMillis();
    }
}
```

### Tone/PWM Generation Example
```c
void appInit(void) {
    toneInit();
    schedulerAddTask(toneDriver, NULL, 1);
}

void appMain(void) {
    // Play a melody
    static uint32_t last_play = 0;
    if (systemMillis() - last_play >= 1000) {
        tonePlay(0, 1000, 1, 500);  // Channel, period, duration, on_time
        last_play = systemMillis();
    }
}
```

### 7-Segment Display Example
```c
void appInit(void) {
    _7segInit();
    
    uint8_t digit_pins[] = {GPIO_D0, GPIO_D1, GPIO_D2, GPIO_D3};
    display = _7segCreateDisplay(digit_pins, 4, _7SEG_COMMON_CATHODE);
    
    schedulerAddTask(_7segScan, NULL, 1);
}

void appMain(void) {
    _7segWriteNumber(display, 1234, _7SEG_CENTER);
}
```

### DS1307 RTC Example
```c
void appInit(void) {
    ds1307Init();
    twi_init(NULL);
    schedulerAddTask(ds1307Driver, NULL, 100);
    
    // Set initial time
    ds1307_time_t init_time = {0, 30, 14, 15, 01, 2026};  // HH:MM:SS:Day:Month:Year
    ds1307SetTime(&init_time);
}

void appMain(void) {
    static uint32_t last_read = 0;
    if (systemMillis() - last_read >= 1000) {
        ds1307_time_t current_time;
        ds1307GetTime(&current_time);
        
        char time_str[9];
        sprintf(time_str, "%02d:%02d:%02d", current_time.hour, current_time.min, current_time.sec);
        lcdSetCursor(0, 0);
        lcdPrint(time_str);
        
        last_read = systemMillis();
    }
}
```

### Internal EEPROM Example
```c
void appInit(void) {
    eepromInit();
    schedulerAddTask(eepromDriver, NULL, 50);
}

void appMain(void) {
    // Write to EEPROM
    uint8_t data[] = {0x12, 0x34, 0x56};
    eepromWrite(0x00, data, 3);
    
    // Read from EEPROM
    uint8_t read_buf[3];
    if (eepromRead(0x00, read_buf, 3)) {
        // Data successfully read
    }
}
```

### External EEPROM Example
```c
void appInit(void) {
    twi_init(NULL);
    exepromInit();
    schedulerAddTask(exepromDriver, NULL, 20);
}

void appMain(void) {
    // Write data to external EEPROM at address 0x1000
    uint8_t write_data[] = {0xAA, 0xBB, 0xCC, 0xDD};
    exepromWrite(0x1000, write_data, 4);
    
    // Read data back
    uint8_t read_buf[4];
    exepromRead(0x1000, read_buf, 4);
    
    if (exepromIsReady()) {
        // Ready for next operation
    }
}
```

### USART Serial Communication Example
```c
void appInit(void) {
    usart_config_t config = {0};
    config.baudrate = BAUDRATE_9600;
    usartInit(&config);
}

void appMain(void) {
    // Transmit data
    const char *msg = "Hello UART\n";
    for (uint8_t i = 0; msg[i]; i++) {
        usartPutByte(USART_PORT_0, msg[i]);
    }
    
    // Receive data
    if (usartAvailable(USART_PORT_0)) {
        uint8_t byte = usartGetByte(USART_PORT_0);
        usartPutByte(USART_PORT_0, byte);  // Echo
    }
}
```

### Signal Generator Example
```c
void appInit(void) {
    signalGenInit();
    schedulerAddTask(signalGenDriver, NULL, 1);
}

void appMain(void) {
    signal_config_t config = {
        .period = 100,      // 100ms period
        .duty = 50,         // 50% duty cycle
        .toggle_count = 5,  // 5 toggles (2.5 cycles)
        .sleep_count = 2,   // Sleep for 2 periods between cycles
        .repeat = 3         // Repeat 3 times
    };
    
    signalGenStart(0, &config);
}
```

### CSMA Communication - Server Node Example
```c
// Server node for coordinating multiple client nodes
void csmaServerCallback(csma_event_t *event) {
    if (event->type == CSMA_CLIENT_REQUEST) {
        // Process client request
        uint8_t client_addr = event->src_addr;
        uint8_t *data = event->data;
        uint8_t len = event->length;
        
        // Send response
        uint8_t response[] = {0x01, 0x02, 0x03};
        csmaPutData(response, 3, client_addr, CSMA_TYPE_RESPONSE);
    }
}

void appInit(void) {
    csmaInit();
    csmaConfigureNode(1, 0x12345678);  // 1 = server, activation code
    csmaSetOnHostRequest(csmaServerCallback);
    schedulerAddTask(csmaDriver, NULL, 10);
}

void appMain(void) {
    // Server processing logic
    static uint32_t last_broadcast = 0;
    if (systemMillis() - last_broadcast >= 5000) {
        // Broadcast periodic status
        uint8_t status[] = {0xAA, 0xBB};
        csmaPutData(status, 2, CSMA_BROADCAST_ADDR, CSMA_TYPE_STATUS);
        last_broadcast = systemMillis();
    }
}
```

### CSMA Communication - Client Node Example
```c
// Client node for sending requests to server
void csmaClientCallback(csma_event_t *event) {
    if (event->type == CSMA_SERVER_RESPONSE) {
        // Process server response
        uint8_t *response_data = event->data;
        uint8_t response_len = event->length;
        
        // Handle response
        gpioWrite(GPIO_A0, GPIO_HIGH);
    }
}

void appInit(void) {
    csmaInit();
    csmaConfigureNode(0, 0x12345678);  // 0 = client, activation code
    csmaSetOnClientResponse(csmaClientCallback);
    csmaSetNodeAddr(0x02);  // Set node address as 0x02
    schedulerAddTask(csmaDriver, NULL, 10);
}

void appMain(void) {
    // Client sends periodic requests to server
    static uint32_t last_request = 0;
    if (systemMillis() - last_request >= 2000) {
        uint8_t request[] = {0x10, 0x20, 0x30};
        uint8_t server_addr = 0x01;  // Server address
        csmaPutData(request, 3, server_addr, CSMA_TYPE_REQUEST);
        
        last_request = systemMillis();
    }
}
```

### TWI/I2C Example
```c
void appInit(void) {
    twiInit(400000);  // 400kHz clock speed
}

void appMain(void) {
    // Read from I2C device (e.g., temperature sensor at 0x48)
    uint8_t addr_buf[1] = {0x00};  // Register address
    uint8_t data_buf[2];
    
    twi_package_t pkg = {
        .chip = 0x48,
        .addr = addr_buf,
        .addr_length = 1,
        .buffer = data_buf,
        .length = 2
    };
    
    if (twiMasterTransfer(&pkg, 1) == TWI_SUCCESS) {
        uint16_t temperature = (data_buf[0] << 8) | data_buf[1];
    }
}
```

### FIFO Buffer Example
```c
void appInit(void) {
    static uint8_t fifo_buffer[256];
    fifo_t rx_fifo;
    fifoInit(&rx_fifo, fifo_buffer, 256);
}

void usartRxISR(void) {
    uint8_t byte = usartGetByte(USART_PORT_0);
    fifoWrite(&rx_fifo, &byte, 1);
}

void appMain(void) {
    if (!fifoIsEmpty(&rx_fifo)) {
        uint8_t byte;
        if (fifoRead(&rx_fifo, &byte, 1) == FIFO_OK) {
            // Process received byte
            usartPutByte(USART_PORT_0, byte);  // Echo
        }
    }
}
```

### Multi-Module Integration Example
```c
void appInit(void) {
    // Initialize all modules
    lcdInit();
    keypadInit();
    adcInit(NULL);
    toneInit();
    ds1307Init();
    twi_init(NULL);
    
    // Register periodic tasks
    schedulerAddTask(lcdDriver, NULL, 20);
    schedulerAddTask(keypadDriver, NULL, 10);
    schedulerAddTask(toneDriver, NULL, 1);
    schedulerAddTask(ds1307Driver, NULL, 100);
}

void appMain(void) {
    static uint32_t display_timer = 0;
    
    if (systemMillis() - display_timer >= 500) {
        // Update LCD with sensor data
        uint16_t adc = adcReadPolling(0);
        
        lcdSetCursor(0, 0);
        lcdPrint("ADC:");
        
        char buf[10];
        sprintf(buf, "%04d", adc);
        lcdSetCursor(0, 5);
        lcdPrint(buf);
        
        // Get and display time
        ds1307_time_t time;
        ds1307GetTime(&time);
        
        lcdSetCursor(1, 0);
        sprintf(buf, "%02d:%02d:%02d", time.hour, time.min, time.sec);
        lcdPrint(buf);
        
        display_timer = systemMillis();
    }
}
```

## �🔧 Getting Started

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
