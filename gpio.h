/*
 * gpio.h
 *
 *  Created on: Sep 15, 2019
 *      Author: albrechter
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "stdint.h"

/** Direction of GPIO **/
typedef enum{
    eDir_IN,
    eDir_OUT
}eDirection;

/** Active Configuration **/
typedef enum{
    eActive_HIGH,
    eActive_LOW
}eActiveConfig;

/** Pin State **/
typedef enum{
    ePin_ON,
    ePin_OFF
}ePinState;

/** This is the mode for configuration **/
typedef enum{
    eMode_DIGITAL,
    eMode_ANALOG,
    eMode_ALT_FUNC
}eMode;

/** This is the interrupt status of the gpio **/
typedef enum{
    eInt_RISING_EDGE,
    eInt_FALLING_EDGE,
    eInt_NONE
}eInt;

/** This is the gpio registers to address**/
typedef enum{
    IN_R=0U,
    OUT_R,
    DIR,
    IFG,
    IES,
    IE,
    SEL,
    REN
} gpio_port_register;

typedef enum{
    PIN0=0b1,
    PIN1=0b10,
    PIN2=0b100,
    PIN3=0b1000,
    PIN4=0b10000,
    PIN5=0b100000,
    PIN6=0b1000000,
    PIN7=0b10000000
}ePin;

/** This is the entire GPIO configuration **/
typedef struct{
    uint8_t port_address;
    const eDirection direction;
    const eMode mode;
    const uint8_t mask;
    const eActiveConfig active_config;
    const eInt interrupt_type;
}gpio_cfg;

typedef struct{
    void (*config)(const gpio_cfg* io);
    ePinState (*read)(const gpio_cfg* io);
    void (*set)(const gpio_cfg* io);
    void (*clear)(const gpio_cfg* io);
    void (*set_interrupt)(const gpio_cfg* io);
}functions;

/** This is the assembly of the function with the config. **/
typedef struct{
    const gpio_cfg* io_cfg;
    const functions* io_map;
}gpio;

void standard_config(const gpio_cfg* io);
ePinState standard_read(const gpio_cfg* io);
void standard_set(const gpio_cfg* io);
void standard_clear(const gpio_cfg* io);
void standard_set_interrupt(const gpio_cfg* io);

#define EMPTY_GPIO 0U

#endif /* GPIO_H_ */
