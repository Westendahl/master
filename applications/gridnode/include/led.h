#ifndef __GRIDNODE_LED__H__
#define __GRIDNODE_LED__H__

// For LED
#include <device.h>
#include <gpio.h>

// Assume same controller for all
#define LED_PORT LED0_GPIO_CONTROLLER
#define LED0 LED0_GPIO_PIN
#define LED1 LED1_GPIO_PIN
#define LED2 LED2_GPIO_PIN
#define LED3 LED3_GPIO_PIN

void leds_init();
void leds_write(uint8_t mask, uint8_t value);

#endif /* __GRIDNODE_LED__H__ */