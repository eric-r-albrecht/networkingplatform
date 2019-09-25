/*
 * timer.h
 *
 *  Created on: Sep 22, 2019
 *      Author: albrechter
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

/**----------------------------------------------------------------------**/

/** Control Register Modes **/

typedef enum{
    CTL_reg = 0x0U,
    CCR0_CTL_reg = 0x2U,
    CCR1_CTL_reg = 0x4U,
    CCR2_CTL_reg = 0x6U,
    COUNTER_reg = 0x10U,
    CCR0_reg = 0x12U,
    CCR1_reg = 0x14U,
    CCR2_reg = 0x16U
}eTimer_Register;

typedef enum{
    eTimer_CLK=8U,
    eTimer_ID=6U,
    eTimer_MC=4U,
    eTimer_CLR=2U,
    eTimer_IE=1U,
    eTimer_IFG=0U,
    eTimer_No_Mask=0U
}eTimer_Control;

#define TIMER_MC_MASK 3U
#define TIMER_ID_MASK 3U
#define TIMER_CLK_MASK 3U
#define TIMER_IE_MASK 1U
#define TIMER_IFG_MASK 1U

typedef enum{
    eTimer_MC_STOP,
    eTimer_MC_UP,
    eTimer_MC_CONT,
    eTimer_MC_UP_DOWN
}eTimer_MC_options;

typedef enum{
    eTimer_ID_1,
    eTimer_ID_2,
    eTimer_ID_4,
    eTimer_ID_8
}eTimer_ID_options;

typedef enum{
    eTimer_CLK_TACLK,
    eTimer_CLK_ACLK,
    eTimer_CLK_SMCLK,
    eTimer_CLK_INCLK
}eTimer_CLK_options;

typedef enum{
    eTimer_IE_Disable,
    eTimer_IE_Enable
}eTimer_IE_options;

typedef enum{
    eTimer_IFG_No_Interrupt,
    eTimer_IFG_Interrupt_Pending
}eTimer_IFG_options;

/** End Control Register Modes **/

/**---------------------------------------------------------------**/

/** Start CCR Register Modes **/

typedef enum{
    eTimer_CCR_CM=14U,
    eTimer_CCR_CCIS=12U,
    eTimer_CCR_CAP=8U,
    eTimer_CCR_OUTMOD=5U,
    eTimer_CCR_IE=4U,
    eTimer_CCR_CCI=3U,
    eTimer_CCR_OUT=2U,
    eTimer_CCR_OVERFLOW=1U,
    eTimer_CCR_IFG=0U
}eTimer_CCR_Offset;

#define TIMER_CCR_CM_MASK 3U
#define TIMER_CCR_CCIS_MASK 3U
#define TIMER_CCR_CAP_MASK 1U
#define TIMER_CCR_OUTMOD_MASK 7U
#define TIMER_CCR_IE_MASK 1U
#define TIMER_CCR_IFG_MASK 1U
#define TIMER_CCR_OVERFLOW_MASK 1U
#define TIMER_CCR_OUT_MASK 1U

typedef enum{
    eTimer_CCR_CM__NO_CAPTURE,
    eTimer_CCR_CM__RISING_EDGE,
    eTimer_CCR_CM__FALLING_EDGE,
    eTimer_CCR_CM__BOTH_EDGES
}eTimer_CCR_CM_options;

typedef enum{
    eTimer_CCR_CCIS__CCIxA,
    eTimer_CCR_CCIS__CCIxB,
    eTimer_CCR_CCIS__GND,
    eTimer_CCR_CCIS__VCC
}eTimer_CCR_CCIS_options;

typedef enum{
    eTimer_CCR_CAP__COMPARE,
    eTimer_CCR_CAP__CAPTURE
}eTimer_CCR_CAP_options;

typedef enum{
    eTimer_CCR_OUTMOD__OUT_BIT,
    eTimer_CCR_OUTMOD__SET,
    eTimer_CCR_OUTMOD__TOGGLE_RESET,
    eTimer_CCR_OUTMOD__SET_RESET,
    eTimer_CCR_OUTMOD__TOGGLE,
    eTimer_CCR_OUTMOD__RESET,
    eTimer_CCR_OUTMOD__TOGGLE_SET,
    eTimer_CCR_OUTMOD__RESET_SET
}eTimer_CCR_OUTMOD_options;

typedef enum{
    eTimer_CCR_IE__DISABLE,
    eTimer_CCR_IE__ENABLE
}eTimer_CCR_IE_options;

typedef enum{
    eTimer_CCR_OUT__LOW,
    eTimer_CCR_OUT__HIGH
}eTimer_CCR_OUT_options;

typedef enum{
    eTimer_CCR_OVERFLOW__NO_OVERFLOW,
    eTimer_CCR_OVERFLOW__OVERFLOW_OCCURRED
}eTimer_CCR_OVERFLOW_options;

typedef enum{
    eTimer_CCR_IFG__NO_INTERRUPT,
    eTimer_CCR_IFG__INTERRUPT_PENDING
}eTimer_CCR_IFG_options;

/** End CCR Register Modes **/

/**------------------------------------------------------------------------**/

/** General timer variables **/

#define NO_MASK 0U
#define TIMER_FULL_MASK 0xFFFFU

/** End General Timer Variables **/

/**---------------------------------------------------------------------------**/

void set_timer_access(uint16_t timer_config, eTimer_Register register_offset, eTimer_Control mask, uint16_t option_mask, uint16_t value);
uint16_t read_timer_access(uint16_t timer_config, eTimer_Register register_offset);
void configure_timer(uint16_t timer_config);
void start_timer(uint16_t timer_config);
void stop_timer(uint16_t timer_config);
void enable_timer_interrupt(uint16_t timer_config);
void set_timer_period(uint16_t timer_config, uint16_t compare);

#endif /* TIMER_H_ */
