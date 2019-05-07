#include "controller.h"
#include "led.h"
void handle_message (u8_t * buf, size_t length){
    if (length < 2) return;
    switch (buf[0]) {
        case 'L':
            switch (buf[1]) {
                case '1': 
                    leds_write(0x8,0xF);
                    break;
                case '0': 
                    leds_write(0x8,0x0);
                    break;
                default: 
                    printk("Unknown char [1]: %c\n",buf[1]);
                    break;
            }
        break;
    default: 
    printk("Unknown char [0]: %c\n",buf[0]);
    break;
    }
};