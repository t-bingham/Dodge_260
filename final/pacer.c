/** @file   pacer.c
    @author M. P. Hayes, UCECE (Modified by: T. Mann & T. Bingham)
    @date   23 August 2010 (Modification date: 15 Oct 2017)
    @brief  Modified pacer module.
    @note   Initialised with a user set frequency (Hz) to pace loops.
*/

#include <avr/io.h>
#include "pacer.h"
#include <math.h>

static uint16_t pacer_period;

/* Initialise the pacer module. */
void pacer_init (uint16_t pacer_frequency)
{
    /* Initialise timer/counter peripheral. 
     * Also calculate the timer/counter value from the pacer frequency. 
     */
    TCCR1A = 0x00;
    TCCR1B = 0x05;
    TCCR1C = 0x00;
    
    pacer_period = 1000 / pacer_frequency;
}


/* Pace while loop.  */
void pacer_wait (void)
{
    /* Convert the pacer period to the clock units. */
    float clockValue;
    clockValue = ((float) pacer_period / 1000) / 0.000128;
       
    
    /* Wait for the timer/couter to reach the clock value. */
    while (TCNT1 < clockValue) {
        continue;
    }
             
    TCNT1 = 0;
}
