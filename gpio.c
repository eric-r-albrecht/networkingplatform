/*
 * gpio.c
 *
 *  Created on: Sep 15, 2019
 *      Author: albrechter
 */


#include "gpio.h"
#include <msp430.h>

/** Standard way to access gpio using pointer **/
void gpio_access(const gpio_cfg* io, uint8_t reg_offset, ePinState on_off){
    if(on_off == ePin_OFF) {
        *((uint8_t*) io->port_address+reg_offset) &= ~(io->mask);
    } else {
        *((uint8_t*) io->port_address+reg_offset) |= (io->mask);
    }
}

/** This is the standard config method for any io **/
void standard_config(const gpio_cfg* io){
    if(io->direction == eDir_IN){
        //*((uint8_t*) io->port_address+DIR) &= ~(io->mask);
        gpio_access(io, DIR, ePin_OFF);
    } else {
        //*( (uint8_t*)io->port_address+DIR) |= io->mask;
        gpio_access(io, DIR, ePin_ON);
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
        //*((uint8_t*)io->port_address+OUT_R) |= io->mask;
        gpio_access(io, OUT_R, ePin_ON);
    } else {
        //*((uint8_t*)io->port_address+OUT_R) &= ~(io->mask);
        gpio_access(io, OUT_R, ePin_OFF);
    }
}

/** This is the standard clear method for any io **/
void standard_clear(const gpio_cfg* io){
    if(io->active_config == eActive_HIGH) {
        //*((uint8_t*)io->port_address+OUT_R) &= ~(io->mask);
        gpio_access(io, OUT_R, ePin_OFF);
    } else {
        //*((uint8_t*)io->port_address+OUT_R) |= io->mask;
        gpio_access(io, OUT_R, ePin_ON);
    }
}

/** This is the standard toggle method for any io **/
void standard_toggle(const gpio_cfg* io){
    *((uint8_t*)io->port_address+OUT_R) ^= (io->mask);
}

/** Standard way to clear interrupt flags when runnign interrupts **/
void standard_toggle_interrupt_edge(const gpio_cfg* io){
    //*((uint8_t*)io->port_address+IFG) &= ~(io->mask);
    *((uint8_t*)io->port_address+IES) ^= (io->mask);
    gpio_access(io, IE, ePin_ON);
}

/** This is the standard set interrupt method for any io **/
void standard_set_interrupt(const gpio_cfg* io){
    if(io->interrupt_type == eInt_ON_TO_OFF){
        if(io->active_config == eActive_HIGH){
            //falling edge
            //*((uint8_t*)io->port_address+IES) &= ~(io->mask);
            gpio_access(io, IES, ePin_ON);
        } else {
            //rising edge
            //*((uint8_t*)io->port_address+IE) |= (io->mask);
            gpio_access(io, IES, ePin_OFF);
        }
        //*((uint8_t*)io->port_address+IFG) &= ~(io->mask);
        //*((uint8_t*)io->port_address+IE) |= (io->mask);
        gpio_access(io, IFG, ePin_OFF);
        gpio_access(io, IE, ePin_ON);
    } else if(io->interrupt_type == eInt_OFF_TO_ON){
        if(io->active_config == eActive_HIGH){
            //rising edge
            //*((uint8_t*)io->port_address+IE) |= (io->mask);
            gpio_access(io, IES, ePin_OFF);
        } else {
            //falling edge
            //*((uint8_t*)io->port_address+IE) &= ~(io->mask);
            gpio_access(io, IES, ePin_ON);
        }
        //*((uint8_t*)io->port_address+IFG) &= ~(io->mask);
        //*((uint8_t*)io->port_address+IE) |= (io->mask);
        gpio_access(io, IFG, ePin_OFF);
        gpio_access(io, IE, ePin_ON);
    } else {
        //ie off
        //*((uint8_t*)io->port_address+IFG) &= ~(io->mask);
        //*((uint8_t*)io->port_address+IE) &= ~(io->mask);
        gpio_access(io, IFG, ePin_OFF);
        gpio_access(io, IE, ePin_OFF);
    }
}

/** Does nothing...*/
void gpio_do_nothing(void){

}

/** Used to reset all interrupt flags **/
void reset_interrupt_flags(const gpio_cfg* io){
    *((uint8_t*) io->port_address+IFG) &= ~(0xFF);
}



const functions standard_map = {&standard_config, &standard_read, &standard_set, &standard_clear, &standard_toggle, &standard_set_interrupt, &standard_toggle_interrupt_edge};
