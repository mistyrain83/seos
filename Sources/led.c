/*
 * ledflash.c
 *
 *  Created on: Jun 5, 2013
 *      Author: dell
 */

#include <derivative.h>
#include "port.h"
#include "led.h"

#define ON 0b0
#define OFF 0b1

#define redled LED1_dat
#define amberled LED2_dat
#define greenled LED4_dat

#define RED_DURATION 10
#define RED_AND_AMBER_DURATION 3
#define GREEN_DURATION 10
#define AMBER_DURATION 3

static eLED_STATE led_state;
static int time_in_state;

void led_init(void)
{
    led_state = RED;
    /* output driver enable */
    LED1_dir = 0b1;
    LED2_dir = 0b1;
    LED3_dir = 0b1;
    LED4_dir = 0b1;
    /* output data is 1*/
    LED1_dat = 0b1;
    LED2_dat = 0b1;
    LED3_dat = 0b1;
    LED4_dat = 0b1;
}

void led_change_state(void)
{
    switch (led_state)
    {
    case RED:
        redled = ON;
        amberled = OFF;
        greenled = OFF;
        
        if (++time_in_state >= RED_DURATION)
        {
            led_state = RED_AMBER;
            time_in_state = 0;
        }
        
        break;
        
    case RED_AMBER:
        redled = ON;
        amberled = ON;
        greenled = OFF;
        
        if (++time_in_state >= RED_AND_AMBER_DURATION)
        {
            led_state = GREEN;
            time_in_state = 0;
        }
        
        break;
        
    case GREEN:
        redled = OFF;
        amberled = OFF;
        greenled = ON;
        
        if (++time_in_state >= GREEN_DURATION)
        {
            led_state = AMBER;
            time_in_state = 0;
        }
        
        break;
        
    case AMBER:
        redled = OFF;
        amberled = ON;
        greenled = OFF;
        
        if (++time_in_state >= AMBER_DURATION)
        {
            led_state = RED;
            time_in_state = 0;
        }
        
        break;
        
    default:
        redled = ON;
        led_state = RED;
        time_in_state = 0;
        break;
    }
    
    /*
    if(led_state == 1)
    {
        led_state = 0;
        LED1_dat = 0;
    }
    else
    {
        led_state = 1;
        LED1_dat = 1;
    }
    */
}
