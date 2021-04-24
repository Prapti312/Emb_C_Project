#ifndef __AVR_ATmega328__
#define __AVR_ATmega328__
#endif
/**
 * @file project_main.c
 * @author Prapti Bhajiyawala (praptibhajiyawala312@gmail.com)
 * @brief Activity1 LED is ON only when Heater is ON and Occupancy of Person is Detected
 * @version 0.1
 * @date 2021-04-24
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "project_config.h"

#include "user_utils.h"
#include "activity.h"

/**
 * @brief Initialize all the Peripherals and pin configurations
 *
 */
void peripheral_init(void)
{
	DDRB|=(1<<LED_PIN);//SET PB0 AS OUTPUT PIN FOR LED
    DDRD&=~(1<<HEARTER_PIN);//PUSH BUTTON FOR PASENGER CHECK
    DDRD&=~(1<<OCCUPANCY_PIN);//PUSH BUTTON FOR HEATER CHECK

    HEATER_OCCUPANCY_PORT|=(1<<HEARTER_PIN);//SET 5 VOLT WHEN SWITCH IS OFF
    HEATER_OCCUPANCY_PORT|=(1<<OCCUPANCY_PIN);//SET 5 VOLT WHEN SWITCH IS OFF
}

void change_led_state(uint8_t state)
{
	LED_PORT = (state << LED_PIN);
}

int main(void)
{
	/* Initialize Peripherals */
	peripheral_init();

	for(;;)
	{
        if(!(HEATER_OCCUPANCY_PIN & (1<<HEARTER_PIN))  &&  !(HEATER_OCCUPANCY_PIN & (1<<OCCUPANCY_PIN)))
        {
            change_led_state(LED_ON);
		    delay_ms(LED_ON_TIME);
        }
        else
        {
            change_led_state(LED_OFF);
		    delay_ms(LED_OFF_TIME);
        }

	}
	return 0;
}