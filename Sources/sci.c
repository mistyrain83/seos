/*
 * sci.c
 *
 *  Created on: Jun 13, 2013
 *      Author: Administrator
 */

#include <derivative.h>
#include "port.h"

#include "sci.h"

void sci_init(void)
{
    // Bus Clock = 8MHz; baud rate = BUSCLK/(16*BR) = 9600, then BR = 53
    SCI1BDH = 0b00000000;
    SCI1BDL = 0b00110101;
    // 8-bits select; parity disable
    SCI1C1 = 0b00000000;
    SCI1C2 = 0b00001100;
}

void sci_send_byte(byte data)
{
    while (SCI1S1_TDRE == 0b0)
    {
        ;   // noop
    }
    
    SCI1D = data;
}
