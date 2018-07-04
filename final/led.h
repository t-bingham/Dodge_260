/** @file   led.h
    @author M. P. Hayes, UCECE (Modified by: T. Mann (tma123) & T. Bingham (tbi18))
    @date   15 Feb 2003 (Modification date: 15 Oct 2017)
    @brief  LED module.
    @note   Contains functions needed to use the Blue LED.
*/


#ifndef LED_H
#define LED_H

/* Turn LED1 on.  */
void led_on (void);


/* Turn LED1 off.  */
void led_off (void);


/* Initialise LED1.  */
void led_init (void);
#endif
