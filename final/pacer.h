/** @file   pacer.h
    @author M. P. Hayes, UCECE (Modified by: T. Mann & T. Bingham)
    @date   23 August 2010 (Modification date: 15 Oct 2017)
    @brief  Modified pacer module.
    @note   Initialised with a user set frequency (Hz) to pace loops.
*/

#ifndef PACER_H
#define PACER_H

#include <avr/io.h>
#include "pacer.h"
#include <math.h>

/* Initialise the pacer module.  */
void pacer_init (uint16_t pacer_frequency);

/* Pace while loop.  */
void pacer_wait (void);

/* Makes the while loop wait for a longer period of time. */
void pacer_long_wait(void);

/* Makes the while loop wait for a very long period of time. */
void pacer_very_long_wait(void);

#endif //PACER_H
