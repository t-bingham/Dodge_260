/** @file   ledmat.h
    @author M. P. Hayes, UCECE (Modified by: T. Mann (tma123) & T. Bingham (tbi18))
    @date   23 August 2010 (Modification date: 15 Oct 2017)
    @brief  Functions used to help draw on the Ledmat using the PIO functions.
*/

#ifndef LEDMAT_H
#define LEDMAT_H

#include "system.h"
#include "pacer.h"
#include "pio.h"

/* Initialises all LEDs and turns them off. */
void ledmat_init (void);

/* Turns off all the LEDs. */
void ledmat_high_all(void);

/* Turns on all the LEDs. */
void ledmat_low_all(void);

/* Turns a single cell on. */
void ledmat_low_cell(uint8_t row, uint8_t column);

/* Displays an x. */
void ledmat_loser(void);

/* Displays a crown. */
void ledmat_winner(void);

/* Displays an ellipsis. */
void ledmat_waiting(void);

/* Displays a Y and an N. */
void ledmat_again(void);


#endif //LEDMAT_H
