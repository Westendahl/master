#
# Copyright (c) 2018 Nordic Semiconductor
#
# SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
#

cmake_minimum_required(VERSION 3.8.2)

include(../../cmake/boilerplate.cmake)
include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)

project(gridnode)

target_include_directories(app PRIVATE include)
target_sources(app PRIVATE src/main.c)
target_sources(app PRIVATE src/led.c)
target_sources(app PRIVATE src/controller.c)
target_sources(app PRIVATE src/walltime.c)
target_sources(app PRIVATE src/sntp_raw.c)
target_sources(app PRIVATE src/estimator.c)
