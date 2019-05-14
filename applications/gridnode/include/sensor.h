#ifndef __GRIDNODE_SENSOR__H__
#define __GRIDNODE_SENSOR__H__

#include <zephyr.h>
#include <stdio.h>
#include <uart.h>
#include <string.h>

int sensor_build_payload(u8_t * payload_buf);

#endif /* __GRIDNODE_SENSOR__H__ */