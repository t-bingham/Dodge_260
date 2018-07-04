/** @file   wall.h
    @author T. Mann & T. Bingham
    @date   15 Oct 2017
    @brief  Wall module, also handles collisions.
    @note   Contains all functions needed to generate and move the wall.
*/

#ifndef WALL_H
#define WALL_H

#include "system.h"
#include "player.h"
#include "pio.h"
#include "ledmat.h"
#include <stdlib.h>

/* Initialises the wall. */
void wall_init(void);

/* Updates the wall's position. 
 * Generates a new wall when the previous one has reached the player. 
 */
int wall_update(void);

/* Generates a new wall.
 * Includes generating the gap position, filling in the wall array,
 * and choosing which direction the wall will come from. 
 */
void wall_generate(void); 

/* Checks for player collision. */
int collision(void);

#endif //WALL_H
