/*
 * seos.c
 *
 *  Created on: Jul 8, 2013
 *      Author: Administrator
 */

#include <derivative.h>
#include "main.h"
#include "seos.h"
#include "port.h"

#include "led.h"

void interrupt INTERRUPT_TPM2OVF seos_isr()
{
    TPM2SC_TOF = 0b0; // ACK timer overflow interrupt, reading flag, then write a zero to the bit.
    led_change_state();
}

void seos_tpm_init(void)
{
    // use bus rate clock(8MHz), prescale factor selction is 128, then 1s = 8MHz/128 = 62500.
    TPM2MOD = 0xF424;
    // TPM2SC = 0b0100 1111
    // TOIE = 1 ; time overflow interrupt enable
    // CLKSB:CLKSA = 01; bus rate clock
    // PS2:PS1:PS0 = 111; clock source divided-by 128
    TPM2SC = 0x4F;
}
void seos_goto_sleep(void)
{
    __asm WAIT;
}
