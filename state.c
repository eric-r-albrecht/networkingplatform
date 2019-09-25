/*
 * state.c
 *
 *  Created on: Sep 23, 2019
 *      Author: albrechter
 */
#include "state.h"
#include "timer.h"
#include "timer_config.h"
#include "gpio.h"
#include "gpio_config.h"
extern eState current_state;
extern const gpio MANCHESTER_INPUT_IO;
extern const gpio DEMO_LED_RED_IO;
extern const gpio DEMO_LED_YELLOW_IO;
extern const gpio DEMO_LED_GREEN_IO;

inline void transition_idle(void){
    current_state = eState_IDLE;
    DEMO_LED_GREEN_IO.io_map->set(DEMO_LED_GREEN_IO.io_cfg);
   DEMO_LED_RED_IO.io_map->clear(DEMO_LED_RED_IO.io_cfg);
   DEMO_LED_YELLOW_IO.io_map->clear(DEMO_LED_YELLOW_IO.io_cfg);
}

inline void transition_busy(void){
    current_state = eState_BUSY;
    set_timer_period(TIMER_A_ADDRESS, FULL_PERIOD);
    DEMO_LED_GREEN_IO.io_map->clear(DEMO_LED_GREEN_IO.io_cfg);
   DEMO_LED_RED_IO.io_map->clear(DEMO_LED_RED_IO.io_cfg);
   DEMO_LED_YELLOW_IO.io_map->set(DEMO_LED_YELLOW_IO.io_cfg);
    start_timer(TIMER_A_ADDRESS);
}

inline void transition_collision(void){
    current_state = eState_COLLISION;
    DEMO_LED_GREEN_IO.io_map->clear(DEMO_LED_GREEN_IO.io_cfg);
   DEMO_LED_RED_IO.io_map->set(DEMO_LED_RED_IO.io_cfg);
   DEMO_LED_YELLOW_IO.io_map->clear(DEMO_LED_YELLOW_IO.io_cfg);
}
