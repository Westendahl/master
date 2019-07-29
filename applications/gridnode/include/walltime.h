#ifndef __GRIDNODE_WALLTIME__H__
#define __GRIDNODE_WALLTIME__H__

#include <stdio.h>
#include "sntp_raw.h"

int walltime_calibrate();
int walltime_get(uint64_t * t_expected, uint64_t * accuracy);
int walltime_init();

#endif /* __GRIDNODE_WALLTIME__H__ */