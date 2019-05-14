#include "sensor.h"
#include "walltime.h"

int sensor_build_payload(u8_t * payload_buf){
    uint64_t timestamp = 0;
    uint64_t accuracy = 0;
    int err;

    // Get wall-time stamp
    err = walltime_get(&timestamp, &accuracy);
    if (err < 0) return -1;

    printk("accuracy(1024ths):%llu\n",accuracy>>22);

    // Recalibrate if inaccurate (>=0.5s)
    if (accuracy>>31 > 0){
        printk("TOO INACCURATE\n");
        err = walltime_calibrate();
        if (err < 0) return -1;
    }

    // Build payload string
    sprintf(payload_buf, "%x %x", (u32_t)(timestamp>>32), (u32_t)(timestamp));

    return 0;
}