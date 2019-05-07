#ifndef __GRIDNODE_CONTROLLER__H__
#define __GRIDNODE_CONTROLLER__H__

#include <zephyr.h>
#include <stdio.h>
#include <uart.h>
#include <string.h>

void handle_message (u8_t * buf, size_t length);

#endif /* __GRIDNODE_CONTROLLER__H__ */