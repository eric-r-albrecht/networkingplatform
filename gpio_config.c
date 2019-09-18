/*
 * gpio_config.c
 *
 *  Created on: Sep 15, 2019
 *      Author: albrechter
 */
#include "gpio.h"
#include "gpio_config.h"
#include <msp430.h>

extern const functions standard_map;

const gpio_cfg DEMO_LED_1_6_cfg = {PORT1, eDir_OUT, eMode_DIGITAL, PIN6, eActive_HIGH, eInt_NONE};
const gpio DEMO_LED_1_6_IO = {&DEMO_LED_1_6_cfg, &standard_map};

const gpio_cfg DEMO_LED_1_0_cfg = {PORT1, eDir_OUT, eMode_DIGITAL, PIN0, eActive_HIGH, eInt_NONE};
const gpio DEMO_LED_1_0_IO = {&DEMO_LED_1_0_cfg, &standard_map};

const gpio_cfg DEMO_LED_BANK_cfg = {PORT1, eDir_OUT, eMode_DIGITAL, PIN0 | PIN6, eActive_HIGH, eInt_NONE};
const gpio DEMO_LED_BANK_IO = {&DEMO_LED_BANK_cfg, &standard_map};

const gpio_cfg DEMO_BUTTON_cfg = {PORT1, eDir_IN, eMode_DIGITAL, PIN3, eActive_LOW, eInt_OFF_TO_ON};
const gpio DEMO_BUTTON_IO = {&DEMO_BUTTON_cfg, &standard_map};

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    __disable_interrupt();
    switch(*((uint8_t*) PORT1+IFG)){
    case PIN0:
        break;
    case PIN1:
        break;
    case PIN2:
        break;
    case PIN3:
        DEMO_LED_BANK_IO.io_map->toggle(DEMO_LED_BANK_IO.io_cfg);
        DEMO_BUTTON_IO.io_map->toggle_interrupt_edge(DEMO_BUTTON_IO.io_cfg);
        break;
    case PIN4:
        break;
    case PIN5:
        break;
    case PIN6:
        break;
    case PIN7:
        break;
    default:
        break;
    }
    *((uint8_t*) PORT1 + IFG) &= ~(0xFF);
    __enable_interrupt();
}

// Port 1 interrupt service routine
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    __disable_interrupt();
    switch(*((uint8_t*) PORT2+IFG)){
    case PIN0:
        break;
    case PIN1:
        break;
    case PIN2:
        break;
    case PIN3:
        break;
    case PIN4:
        break;
    case PIN5:
        break;
    case PIN6:
        break;
    case PIN7:
        break;
    default:
        break;
    }
    *((uint8_t*) PORT2 + IFG) &= ~(0xFF);
    __enable_interrupt();
}
