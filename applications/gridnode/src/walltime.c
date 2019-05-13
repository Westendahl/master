#include "walltime.h"
#include "estimator.h"

static struct sntp_ctx ctx;
static struct sockaddr_in ntp_addr;

static tinysync_est_state_t state;
static tinysync_est_ret_t last_result;

// Gets a tiny-sync datapoint by requesting time over SNTP
int get_datapoint(tinysync_datapoint_t * datapoint){
    int rv;

    /* ipv4 ntp*/
    memset(&ntp_addr, 0, sizeof(ntp_addr));

    ntp_addr.sin_family = AF_INET;
    ntp_addr.sin_port = htons(123);
    /* inet_pton(AF_INET, "129.240.2.6", // ntp.uio.no
            &ntp_addr.sin_addr); */ // Bug: inet_pton does not seem to work
    ntp_addr.sin_addr.s_addr = (u32_t) 0x0602f081; // "129.240.2.6" // ntp.uio.no

    rv = sntp_init(&ctx, (struct sockaddr *) &ntp_addr,
                sizeof(struct sockaddr_in));
    if (rv < 0) {
        printk("Failed to init sntp ctx: %d", rv);
        return -1;
    }

    datapoint->t_o = k_uptime_get();
    rv = sntp_request(&ctx, K_FOREVER, &(datapoint->t_b) );
    if (rv < 0) {
        printk("Failed to send sntp request: %d", rv);
        return -1;
    }
    datapoint->t_r = k_uptime_get();


    printk("SNTP time: %llx\n", datapoint->t_b);
    printk("status: %d\n", rv);

    sntp_close(&ctx);
    
    return 0;
}

int walltime_calibrate(){
    tinysync_datapoint_t datapoint;
    int err = get_datapoint(&datapoint);
    if (err < 0) return -1;
    last_result = tinysync_est_etimate(&state, &datapoint);
    while(last_result != TINYSYNC_EST_OK){
        k_sleep(K_MSEC(1000));
        int err = get_datapoint(&datapoint);
        if (err < 0) return -1;
        last_result = tinysync_est_etimate(&state, &datapoint);
        //uint64_t now = k_uptime_get();
        //uint64_t max_t_2 = (uint64_t)((((double)now) - state.lineset.ba.b) / state.lineset.ba.a);
        //uint64_t min_t_2 = (uint64_t)((((double)now) - state.lineset.ab.b) / state.lineset.ab.a);

        //printk("T2EXP:%llx\n", (max_t_2/2) + (min_t_2/2) );
        //printk("ACC (1024ths)(1sec):%lld\n", ((max_t_2/2) - (min_t_2/2)) >> 22 );
        //printk("RESLT:%d\n",result);
    }
    return 0;
}

int walltime_get(uint64_t * t_expected, uint64_t * accuracy){
    if (last_result != TINYSYNC_EST_OK) {
        return -1;
    }
    uint64_t now = k_uptime_get();
    uint64_t max_t_2 = (uint64_t)((((double)now) - state.lineset.ba.b) / state.lineset.ba.a);
    uint64_t min_t_2 = (uint64_t)((((double)now) - state.lineset.ab.b) / state.lineset.ab.a);
    *t_expected = (max_t_2/2) + (min_t_2/2);
    *accuracy = (max_t_2/2) - (min_t_2/2);
    return 0;
}

int walltime_init(){
    tinysync_est_state_t_initialize(&state);
    last_result = TINYSYNC_EST_INVALID;
    int err = walltime_calibrate();
    if (err < 0) return -1;
    return 0;
}