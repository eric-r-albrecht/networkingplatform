/*
 * gpio.c
 *
 *  Created on: Sep 15, 2019
 *      Author: albrechter
 */


#include "gpio.h"

/** This is the standard config method for any io **/
void standard_config(const gpio_cfg* io){
    if(io->direction == eDir_IN){
        *((uint8_t*) io->port_address+DIR) &= ~(io->mask);
    } else {
        *( (uint8_t*)io->port_address+DIR) |= io->mask;
    }
}

/** This is the standard read method for any io **/
ePinState standard_read(const gpio_cfg* io){
    ePinState returnval = ePin_OFF;
    if((*((uint8_t*)io->port_address+IN_R) & io->mask) > EMPTY_GPIO) {
        if(io->active_config == eActive_HIGH) {
            returnval = ePin_ON;
        } else {
            returnval = ePin_OFF;
        }
    } else {
        if(io->active_config == eActive_HIGH){
            returnval = ePin_OFF;
        } else {
            returnval = ePin_ON;
        }
    }
    return returnval;
}

/** This is the standard set method for any io **/
void standard_set(const gpio_cfg* io){
    if(io->active_config == eActive_HIGH) {
        *((uint8_t*)io->port_address+OUT_R) |= io->mask;
    } else {
        *((uint8_t*)io->port_address+OUT_R) &= ~(io->mask);
    }
}

/** This is the standard clear method for any io **/
void standard_clear(const gpio_cfg* io){
    if(io->active_config == eActive_HIGH) {
        *((uint8_t*)io->port_address+OUT_R) &= ~(io->mask);
    } else {
        *((uint8_t*)io->port_address+OUT_R) |= io->mask;
    }
}

/** This is the standard set interrupt method for any io **/
void standard_set_interrupt(const gpio_cfg* io){

}

const functions standard_map = {&standard_config, &standard_read, &standard_set, &standard_clear, &standard_set_interrupt};
