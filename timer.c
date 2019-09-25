/*
 * timer.c
 *
 *  Created on: Sep 22, 2019
 *      Author: albrechter
 */

#include <stdint.h>
#include "timer.h"
#include "timer_config.h"

void set_timer_access(uint16_t timer_config, eTimer_Register register_offset, eTimer_Control mask, uint16_t option_mask, uint16_t value){
    uint16_t* timer_pointer = (uint16_t*) (timer_config + register_offset);
    if(value > 0U){
        *(timer_pointer) |= (value << mask);
    } else {
        *(timer_pointer) &= ~(option_mask << mask);
    }
}

uint16_t read_timer_access(uint16_t timer_config, eTimer_Register register_offset){
    return *((uint16_t*)(timer_config + register_offset));
}

void stop_timer(uint16_t timer_config){
    set_timer_access(timer_config, CTL_reg, eTimer_MC, TIMER_MC_MASK, eTimer_MC_STOP);
}

void start_timer(uint16_t timer_config){
    //stop_timer(timer_config);
    set_timer_access(timer_config, COUNTER_reg, eTimer_No_Mask, TIMER_FULL_MASK, 0U);
    set_timer_access(timer_config, CTL_reg, eTimer_MC, TIMER_MC_MASK, eTimer_MC_UP);
}

void enable_timer_interrupt(uint16_t timer_config){
    //set_timer_access(timer_config, CTL_reg, eTimer_IE, TIMER_IE_MASK, eTimer_IE_Enable);
    set_timer_access(timer_config, CCR0_CTL_reg, eTimer_CCR_IE, TIMER_CCR_IE_MASK, eTimer_CCR_IE__ENABLE);
}

void set_timer_period(uint16_t timer_config, uint16_t compare){
    set_timer_access(timer_config, CCR0_reg, eTimer_No_Mask, TIMER_FULL_MASK, 0U);
    set_timer_access(timer_config, CCR0_reg, eTimer_No_Mask, TIMER_FULL_MASK, compare);
}

void configure_timer(uint16_t timer_config){
    /** Regular Timer config **/
    stop_timer(timer_config);
    set_timer_access(timer_config, CTL_reg, eTimer_ID, TIMER_ID_MASK, eTimer_ID_8);
    set_timer_access(timer_config, CTL_reg, eTimer_CLK, TIMER_CLK_MASK, eTimer_CLK_SMCLK);
    set_timer_access(timer_config, CTL_reg, eTimer_IFG, TIMER_IFG_MASK, eTimer_IFG_No_Interrupt);
    set_timer_access(timer_config, CCR0_CTL_reg, eTimer_CCR_IE, TIMER_CCR_IE_MASK, eTimer_CCR_IE__DISABLE);
    set_timer_access(timer_config, CCR1_CTL_reg, eTimer_CCR_IE, TIMER_CCR_IE_MASK, eTimer_CCR_IE__DISABLE);
    set_timer_access(timer_config, CCR2_CTL_reg, eTimer_CCR_IE, TIMER_CCR_IE_MASK, eTimer_CCR_IE__DISABLE);
    set_timer_access(timer_config, CCR0_CTL_reg, eTimer_CCR_IFG, TIMER_CCR_IFG_MASK, eTimer_CCR_IFG__NO_INTERRUPT);
    set_timer_access(timer_config, CCR1_CTL_reg, eTimer_CCR_IFG, TIMER_CCR_IFG_MASK, eTimer_CCR_IFG__NO_INTERRUPT);
    set_timer_access(timer_config, CCR2_CTL_reg, eTimer_CCR_IFG, TIMER_CCR_IFG_MASK, eTimer_CCR_IFG__NO_INTERRUPT);
}




