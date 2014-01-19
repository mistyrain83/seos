/*
 * board.c
 *
 *  Created on: Jul 8, 2013
 *      Author: Qi Xiangbing
 */
#include <derivative.h>
#include "main.h"
#include "port.h"
#include "board.h"

/* Moving from FEI to PEE mode. 
 * External Crystal = 16MHz
 * Bus Frequency = 8MHz
*/
void board_init(void)
{
	 // 1. First, FEI must transition to FBE mode:
	 // a) MCGC2 = 0x36
	
//	MCGC2_BDIV = 0b00;	// divides selected clock by 2
//	// high frequency range selected for the external oscillator of 1MHz to 16MHz (1MHz to 40MHz for external clock source),
//	 // because the frequency of 16MHz is within the high frequency range
//	MCGC2_RANGE = 0b1;
//	MCGC2_HGO = 0b1;	// configure external oscillator for high gain operation
//	MCGC2_LP = 0b0;		// FLL (or PLL) is not disabled in bypass modes
//	MCGC2_EREFS = 0b1;	// oscillator requested, because a crystal is being used
//	MCGC2_ERCLKEN = 0b1;	// MCGERCLK active, ensure the external reference clock is active
//	MCGC2_EREFSTEN = 0b0;	// external reference clock is disabled in stop
	
	MCGC2 = 0x36;
	
	// b) Loop until OSCINT (indicating the crystal selected by EREFS bit) has been initialised.
	while(MCGSC_OSCINIT != 1)
	{
		;	// noop
	}
	
	// c) Block interrupts (if applicable by setting the interrupt bit in the CCR)
	
	// d) MCGC1 = 0xB8
	
//	MCGC1_CLKS = 0b10;	// external reference clock is selected, select external reference clock as system clock
//	 // 16MHz/128 = 125KHz, which is greater than the 31.25KHz to 39.0625KHz range which required by the FLL. Therefore
//	 // after the transition to FBE is complete, software must progress through to BLPE mode immediately by setting the 
//	 // LP bit in MCGC2.
//	MCGC1_RDIV = 0b111;	// divides reference clock by 128
//	MCGC1_IREFS = 0x0;	// external reference clock selected, setting the external reference clock
//	MCGC1_IRCLKEN = 0x0;	// MCGIRECLK inactive
//	MCGC1_IREFSTEN = 0x0;	// internal reference clock is disabled in stop
//	
	MCGC1 = 0xB8;
	
	// e) Loop until IREFST is 0, indicating the external reference is the current source for the reference clock
	while(MCGSC_IREFST != 0)
	{
		;	// noop
	}
	
	// f) Loop until CLKST in MCGSC are 10, indicating that the external reference clock is selected to feed MCGOUT
	while(MCGSC_CLKST != 0b10)
	{
		;	// noop
	}
	
	// 2. Then, FBE mode transitions into BLPE mode:
	// a) MCGC2 = 0x3E
	MCGC2_LP = 0b1; // FLL (or PLL) is disabled in bypass modes (lower power)
	
	// b) Enable interrupts (if applicable by clearing the interrupt bit in the CCR)
	// There must be no extra steps (including interrupt between steps 1d and 2a)
	
	// c) MCGC1 = 0xA0
	
//	MCGC1_CLKS = 0b10;	// external reference clock is selected
//	MCGC1_RDIV = 0b100;	// divides reference clock by 16, because 16MHz/16 = 1MHz which is in the 1MHz to 2MHz range required by the PLL
//	MCGC1_IREFS = 0x0;	// external reference clock selected, setting the external reference clock
//	MCGC1_IRCLKEN = 0x0;	// MCGIRECLK inactive
//	MCGC1_IREFSTEN = 0x0;	// internal reference clock is disabled in stop
	
	MCGC1 = 0xA0;
	
	// d) MCGC3 = 0x44
	
//	MCGC3_LOLIE = 0b0;	// no request on loss of lock
//	MCGC3_PLLS = 0b1;	// PLL is selected, in BLPE mode, changing this bit only prepares the MCG for PLL usage in PBE mode
//	MCGC3_CME = 0b0;	// clock monitor is disabled
//	// In BLPE mode, the configuration of the VDIV bits does not matter because the PLL is disabled. 
//	// Changing them only sets up the multiply value for PLL usage in PBE mode 
//	MCGC3_VDIV = 0b0100;	// multiply by 16, because 1MHz*16 is 16MHz
//	
	MCGC3 = 0x44;
	
	// e) Loop until PLLST is set, indicating that the current source for the PLLS clock is the PLL
	while(MCGSC_PLLST != 1)
	{
		;	// noop
	}
	
	// 3. Then, BLPE mode transitions into PBE mode
	// a) Clear LP to 0 here to switch to PBE mode
	MCGC2_LP = 0b0;	// FLL (or PLL) is not disabled in bypass modes
	
	// b) Loop until LOCK is set, indicating that the PLL has required lock
	while(MCGSC_LOCK !=1 )
	{
		;	// noop
	}
	
	// 4. Last, PBE mode transitions into PEE mode
	// a) MCGC1 = 0x20
	
//	MCGC1_CLKS = 0b00;	// output of FLL or PLL is selected
//	MCGC1_RDIV = 0b100;	// divides reference clock by 16
//	MCGC1_IREFS = 0b0;	// external reference clock selected
//	MCGC1_IRCLKEN = 0b0;	// MCGIRECLK inactive
//	MCGC1_IREFSTEN = 0b0;	// internal reference clock is disabled in stop
	
	MCGC1 = 0x20;
	
	// b) Loop until CLKST are 11, indicating that the PLL output is selected to feed MCGOUT in the current clock mode
	while(MCGSC_CLKST != 0b11)
	{
		;	// noop
	}
	
	// Now, Fext = 16MHz; R(RDIV) = 16; M(VDIV) = 16; B(BDIV) = 1. Then, MCGOUT = [(Fext/R)*M]/B = 16MHz, 
	// and the bus frequency is MCGOUT/2 = 8MHz.
}
