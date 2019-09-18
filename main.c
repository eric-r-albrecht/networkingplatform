#include <msp430.h>
#include "gpio.h"

/**
 * main.c
 */

extern const gpio DEMO_LED_1_6_IO;
extern const gpio DEMO_LED_1_0_IO;
extern const gpio DEMO_LED_BANK_IO;
extern const gpio DEMO_BUTTON_IO;

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	DEMO_LED_BANK_IO.io_map->config(DEMO_LED_BANK_IO.io_cfg);
	DEMO_BUTTON_IO.io_map->config(DEMO_BUTTON_IO.io_cfg);


	DEMO_LED_1_6_IO.io_map->set(DEMO_LED_1_6_IO.io_cfg);
	DEMO_LED_1_6_IO.io_map->clear(DEMO_LED_1_6_IO.io_cfg);
	DEMO_LED_1_6_IO.io_map->set(DEMO_LED_1_6_IO.io_cfg);

	DEMO_LED_1_0_IO.io_map->set(DEMO_LED_1_0_IO.io_cfg);
	DEMO_LED_1_0_IO.io_map->clear(DEMO_LED_1_0_IO.io_cfg);
	DEMO_LED_1_0_IO.io_map->set(DEMO_LED_1_0_IO.io_cfg);

	DEMO_LED_BANK_IO.io_map->set(DEMO_LED_BANK_IO.io_cfg);
	DEMO_LED_BANK_IO.io_map->clear(DEMO_LED_BANK_IO.io_cfg);
	DEMO_LED_BANK_IO.io_map->set(DEMO_LED_BANK_IO.io_cfg);
	DEMO_LED_BANK_IO.io_map->clear(DEMO_LED_BANK_IO.io_cfg);

	while(1){
	    if(DEMO_BUTTON_IO.io_map->read(DEMO_BUTTON_IO.io_cfg) == ePin_ON){
	        DEMO_LED_BANK_IO.io_map->set(DEMO_LED_BANK_IO.io_cfg);
	    } else {
	        DEMO_LED_BANK_IO.io_map->clear(DEMO_LED_BANK_IO.io_cfg);
	    }
	}
}
