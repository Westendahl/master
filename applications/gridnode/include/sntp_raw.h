/*
 * Copyright (c) 2017 Linaro Limited
 * Copyright (c) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __GRIDNODE_SNTP__H__
#define __GRIDNODE_SNTP__H__

#include <net/socket.h>

/**
 * @brief Simple Network Time Protocol API
 * @defgroup sntp SNTP
 * @ingroup networking
 * @{
 */

/** SNTP context */
struct sntp_ctx {
	struct {
		struct pollfd fds[1];
		int nfds;
		int fd;
	} sock;

	/** Timestamp when the request was sent from client to server.
	 *  This is used to check if the originated timestamp in the server
	 *  reply matches the one in client request.
	 */
	u32_t expected_orig_ts;
};

/**
 * @brief Initialize SNTP context
 *
 * @param ctx Address of sntp context.
 * @param addr IP address of NTP/SNTP server.
 * @param addr_len IP address length of NTP/SNTP server.
 *
 * @return 0 if ok, <0 if error.
 */
int sntp_init(struct sntp_ctx *ctx, struct sockaddr *addr,
	      socklen_t addr_len);

/**
 * @brief Send SNTP request
 *
 * @param ctx Address of sntp context.
 * @param timeout Timeout of waiting for sntp response (in milliseconds).
 * @param sntp_time 64-bit NTP Tx timestamp from server.
 *
 * @return 0 if ok, <0 if error.
 */
int sntp_request(struct sntp_ctx *ctx, u32_t timeout, u64_t *sntp_time);

/**
 * @brief Release SNTP context
 *
 * @param ctx Address of sntp context.
 */
void sntp_close(struct sntp_ctx *ctx);

/**
 * @}
 */

#endif /* __GRIDNODE_SNTP__H__ */
