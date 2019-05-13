#include "walltime.h"

static struct sntp_ctx ctx;
static struct sockaddr_in ntp_addr;

int walltime_init(){
    u64_t epoch_time;
    int rv;

    /* ipv4 ntp*/
    memset(&ntp_addr, 0, sizeof(ntp_addr));

    ntp_addr.sin_family = AF_INET;
    ntp_addr.sin_port = htons(123);
    /* inet_pton(AF_INET, "129.240.2.6", // ntp.uio.no
            &ntp_addr.sin_addr); */ // Why not work?
    ntp_addr.sin_addr.s_addr = (u32_t) 0x0602f081; // "129.240.2.6" // ntp.uio.no

    rv = sntp_init(&ctx, (struct sockaddr *) &ntp_addr,
                sizeof(struct sockaddr_in));
    if (rv < 0) {
        printk("Failed to init sntp ctx: %d", rv);
        return -1;
    }

    rv = sntp_request(&ctx, K_FOREVER, &epoch_time);
    if (rv < 0) {
        printk("Failed to send sntp request: %d", rv);
        return -1;
    }
    printk("SNTP time: %llx\n", epoch_time);
    printk("status: %d\n", rv);

    sntp_close(&ctx);
    
    return 0;
}