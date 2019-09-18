/*
 * gpio_config.c
 *
 *  Created on: Sep 15, 2019
 *      Author: albrechter
 */
#include "gpio.h"
#include "gpio_config.h"

extern const functions standard_map;

const gpio_cfg DEMO_LED_1_6_cfg = {PORT1, eDir_OUT, eMode_DIGITAL, PIN6, eActive_HIGH, eInt_NONE};
const gpio DEMO_LED_1_6_IO = {&DEMO_LED_1_6_cfg, &standard_map};

const gpio_cfg DEMO_LED_1_0_cfg = {PORT1, eDir_OUT, eMode_DIGITAL, PIN0, eActive_HIGH, eInt_NONE};
const gpio DEMO_LED_1_0_IO = {&DEMO_LED_1_0_cfg, &standard_map};

const gpio_cfg DEMO_LED_BANK_cfg = {PORT1, eDir_OUT, eMode_DIGITAL, PIN0 | PIN6, eActive_HIGH, eInt_NONE};
const gpio DEMO_LED_BANK_IO = {&DEMO_LED_BANK_cfg, &standard_map};

const gpio_cfg DEMO_BUTTON_cfg = {PORT1, eDir_IN, eMode_DIGITAL, PIN3, eActive_LOW, eInt_NONE};
const gpio DEMO_BUTTON_IO = {&DEMO_BUTTON_cfg, &standard_map};


