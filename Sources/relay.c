/*
 * relay.c
 *
 *  Created on: Jun 8, 2013
 *      Author: Administrator
 */

#include <derivative.h>
#include "port.h"
#include "led.h"

void relay_init(void)
{
    RELAY1_dir = 0b1;
}

void relay_on(void)
{
    RELAY1_dat = 0b0;
}

void relay_off(void)
{
    RELAY1_dat = 0b1;
}
