#include "led.h"

void leds_init(){
	// Init LED1. Assume same device.
	struct device *dev;
	dev = device_get_binding(LED_PORT);
	gpio_pin_configure(dev, LED0, GPIO_DIR_OUT);
	gpio_pin_configure(dev, LED1, GPIO_DIR_OUT);
	gpio_pin_configure(dev, LED2, GPIO_DIR_OUT);
	gpio_pin_configure(dev, LED3, GPIO_DIR_OUT);
}

void leds_write(uint8_t mask, uint8_t value){
	struct device *dev;
	dev = device_get_binding(LED_PORT);
	if ((mask >> 0) & 1) gpio_pin_write(dev, LED0, (value >> 0) & 1);
	if ((mask >> 1) & 1) gpio_pin_write(dev, LED1, (value >> 1) & 1);
	if ((mask >> 2) & 1) gpio_pin_write(dev, LED2, (value >> 2) & 1);
	if ((mask >> 3) & 1) gpio_pin_write(dev, LED3, (value >> 3) & 1);
}