/** @file   player.h
    @author T. Mann & T. Bingham
    @date   15 Oct 2017
    @brief  Player module.
    @note   Contains all functions needed to update and move the player.
*/

#ifndef PLAYER_H
#define PLAYER_H

#include "system.h"
#include "ledmat.h"

/* Directions enumerated for readability. */
enum direction {MOVE_UP, MOVE_DOWN};

/* Initialising player. */
void player_init(void);

/* Updates player position. */
void update_player(void);

/* Updates player height each loop. */
void move_player(uint8_t move);

/* Returns the player's current height. */
uint8_t player_get_height(void);

#endif //PLAYER_H
