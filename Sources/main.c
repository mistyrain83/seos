#include <hidef.h> /* for EnableInterrupts macro */
#include <derivative.h> /* include peripheral declarations */
#include "main.h"
#include "board.h"

#include "port.h"
#include "seos.h"

#include "led.h"
#include "relay.h"


void main(void)
{
    /* include your code here */
    // Disable COP
    SOPT1_COPT = 0b00;
    board_init();       // initialise multi-purpose clock generator
    led_init(); // initialise led pin settings
    //relay_init();
    //sci_init();
    seos_tpm_init();
    //relay_on();
    EnableInterrupts;
    
    for (;;)
    {
        __RESET_WATCHDOG(); // feeds the dog
        seos_goto_sleep();
    } /* loop forever */
    
    /* please make sure that you never leave main */
}

