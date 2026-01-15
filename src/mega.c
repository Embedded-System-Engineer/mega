#include "../inc/mega.h"

int main(void) {
    // Hardware & System Initialization
    appBoot();
    system_init();
    
    // Module Initializations
    gpio_init(); // If needed
    usart_init(NULL); // Default config
    twi_init(NULL);
    eeprom_init();
    exepromInit();
    ds1307Init();
    keypad_init();
    button_init();
    signalGenInit();
    lcd_init();
    lcd_menu_init();
    csma_init();
    ssd_init();
    _7segInit();
    zlpInit();
    tone_init();
    adc_init(NULL);
    
    appInit();

    // Task Registration in Scheduler
    scheduler_add_task(csmaDriver, NULL, 10);
    scheduler_add_task(eepromDriver, NULL, 50);
    scheduler_add_task(exepromDriver, NULL, 20);
    scheduler_add_task(ds1307Driver, NULL, 100);
    scheduler_add_task(keypadDriver, NULL, 10);
    scheduler_add_task(buttonDriver, NULL, 10);
    scheduler_add_task(lcdDriver, NULL, 20);
    scheduler_add_task(lcdMenuDriver, NULL, 50);
    scheduler_add_task(signalGenDriver, NULL, 1);
    scheduler_add_task(toneDriver, NULL, 1);
    scheduler_add_task(zlpDriver, NULL, 50);

    system_start(); // Starts interrupts

    while (1) {
        scheduler_dispatch();
        appMain();
    }
    
    return 0;
}
