#include <msp430.h>
#include "gpio.h"
#include "timer.h"
#include "timer_config.h"
#include "state.h"

/**
 * main.c
 */

extern const gpio DEMO_LED_RED_IO;
extern const gpio DEMO_LED_GREEN_IO;
extern const gpio DEMO_LED_YELLOW_IO;
extern const gpio DEMO_LED_BANK_IO;
extern const gpio DEMO_BUTTON_IO;
extern const gpio MANCHESTER_INPUT_IO;

volatile eState current_state;
volatile eInput_State manchester_state;

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	/* Configure the clock module - MCLK = 2MHz */
	DCOCTL = 0;
	BCSCTL1 = CALBC1_16MHZ;
	DCOCTL = CALDCO_16MHZ;

	__enable_interrupt();

	DEMO_LED_GREEN_IO.io_map->config(DEMO_LED_GREEN_IO.io_cfg);
	DEMO_LED_RED_IO.io_map->config(DEMO_LED_RED_IO.io_cfg);
	DEMO_LED_YELLOW_IO.io_map->config(DEMO_LED_YELLOW_IO.io_cfg);

	MANCHESTER_INPUT_IO.io_map->config(MANCHESTER_INPUT_IO.io_cfg);
	MANCHESTER_INPUT_IO.io_map->set_interrupt(MANCHESTER_INPUT_IO.io_cfg);

	DEMO_LED_GREEN_IO.io_map->set(DEMO_LED_GREEN_IO.io_cfg);
    DEMO_LED_RED_IO.io_map->clear(DEMO_LED_RED_IO.io_cfg);
    DEMO_LED_YELLOW_IO.io_map->set(DEMO_LED_YELLOW_IO.io_cfg);

	stop_timer(TIMER_A_ADDRESS);
	configure_timer(TIMER_A_ADDRESS);
	enable_timer_interrupt(TIMER_A_ADDRESS);
	transition_idle();
	stop_timer(TIMER_A_ADDRESS);


	while(1){};
}
