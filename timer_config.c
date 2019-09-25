/*
 * timer_config.c
 *
 *  Created on: Sep 22, 2019
 *      Author: albrechter
 */
#include <msp430.h>
#include "gpio.h"
#include "timer.h"
#include "timer_config.h"
#include "state.h"

extern const gpio DEMO_LED_RED_IO;
extern const gpio DEMO_LED_GREEN_IO;
extern const gpio MANCHESTER_INPUT_IO;
extern eState current_state;
extern ePinState manchester_pin;

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    __disable_interrupt();
    gpio_access(MANCHESTER_INPUT_IO.io_cfg, IE, ePin_OFF);
    set_timer_access(TIMER_A_ADDRESS, CTL_reg, eTimer_IFG, TIMER_IFG_MASK, eTimer_IFG_No_Interrupt);
    set_timer_access(TIMER_A_ADDRESS, CCR0_CTL_reg, eTimer_CCR_IFG, TIMER_CCR_IFG_MASK,eTimer_CCR_IFG__NO_INTERRUPT);
    stop_timer(TIMER_A_ADDRESS);
    if(current_state == eState_BUSY) {
        if(MANCHESTER_INPUT_IO.io_map->read(MANCHESTER_INPUT_IO.io_cfg) == ePin_ON){
            transition_idle();
        } else {
            transition_collision();
        }
    }
    gpio_access(MANCHESTER_INPUT_IO.io_cfg, IE, ePin_ON);
    __enable_interrupt();
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A_1(void)
{
    set_timer_access(TIMER_A_ADDRESS, CTL_reg, eTimer_IFG, TIMER_IFG_MASK, eTimer_IFG_No_Interrupt);
    set_timer_access(TIMER_A_ADDRESS, CCR1_CTL_reg, eTimer_CCR_IE, TIMER_CCR_IE_MASK, eTimer_CCR_IE__DISABLE);
    //DEMO_LED_RED_IO.io_map->set(DEMO_LED_RED_IO.io_cfg);
}
