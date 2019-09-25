/*
 * gpio_config.c
 *
 *  Created on: Sep 15, 2019
 *      Author: albrechter
 */
#include "gpio.h"
#include "gpio_config.h"
#include <msp430.h>
#include "timer.h"
#include "timer_config.h"
#include "state.h"

extern const functions standard_map;
extern volatile eState current_state;

const gpio_cfg DEMO_LED_1_6_cfg = {PORT1, eDir_OUT, eMode_DIGITAL, PIN6, eActive_HIGH, eInt_NONE};
const gpio DEMO_LED_RED_IO = {&DEMO_LED_1_6_cfg, &standard_map};

const gpio_cfg DEMO_LED_1_0_cfg = {PORT1, eDir_OUT, eMode_DIGITAL, PIN0, eActive_HIGH, eInt_NONE};
const gpio DEMO_LED_GREEN_IO = {&DEMO_LED_1_0_cfg, &standard_map};

const gpio_cfg DEMO_LED_BANK_cfg = {PORT1, eDir_OUT, eMode_DIGITAL, PIN0 | PIN6, eActive_HIGH, eInt_NONE};
const gpio DEMO_LED_BANK_IO = {&DEMO_LED_BANK_cfg, &standard_map};

const gpio_cfg DEMO_BUTTON_cfg = {PORT1, eDir_IN, eMode_DIGITAL, PIN3, eActive_LOW, eInt_OFF_TO_ON};
const gpio DEMO_BUTTON_IO = {&DEMO_BUTTON_cfg, &standard_map};

const gpio_cfg DEMO_LED_YELLOW_IO_cfg = {PORT1, eDir_OUT, eMode_DIGITAL, PIN4, eActive_LOW, eInt_NONE};
const gpio DEMO_LED_YELLOW_IO = {&DEMO_LED_YELLOW_IO_cfg, &standard_map};

const gpio_cfg MANCHESTER_INPUT_cfg = {PORT1, eDir_IN, eMode_DIGITAL, PIN1, eActive_HIGH, eInt_ON_TO_OFF};
const gpio MANCHESTER_INPUT_IO = {&MANCHESTER_INPUT_cfg, &standard_map};
volatile ePinState manchester_pin = ePin_ON;

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    stop_timer(TIMER_A_ADDRESS);
    switch(*((uint8_t*) PORT1+IFG) & ~(PIN4 | PIN6 | PIN0)){
    case PIN0:
        break;
    case PIN1:
        if(MANCHESTER_INPUT_IO.io_map->read(MANCHESTER_INPUT_IO.io_cfg) == ePin_ON){
            gpio_access(MANCHESTER_INPUT_IO.io_cfg, IES, ePin_ON);
            manchester_pin = ePin_ON;
        } else {
            gpio_access(MANCHESTER_INPUT_IO.io_cfg, IES, ePin_OFF);
            manchester_pin = ePin_OFF;
        }
        if(current_state == eState_IDLE || current_state == eState_COLLISION){
            transition_busy();
        } else if(current_state == eState_BUSY){
            set_timer_period(TIMER_A_ADDRESS, FULL_PERIOD);
            start_timer(TIMER_A_ADDRESS);
        }
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
    *((uint8_t*) PORT1 + IFG) &= ~(0xFF);
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
