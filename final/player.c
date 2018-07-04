/** @file   player.c
    @author T. Mann (tma123) & T. Bingham (tbi18)
    @date   15 Oct 2017
    @brief  Player module.
    @note   Contains all functions needed to update and move the player.
*/

#include "system.h"
#include "ledmat.h"
#include <avr/io.h>


static int8_t player_height;
static int8_t player_move;

enum {MOVE_UP, MOVE_DOWN};

/* Initialising player. */
void player_init(void) 
{
    player_height = 3;
    player_move = 1; // Makes player only able to move once per sucessive wall dodge.
    ledmat_high_all();
    ledmat_low_cell(3, player_height);
}

/* Updates player position. */
void player_update(void) 
{
    ledmat_high_all();
    ledmat_low_cell(4, player_height);
}

/* Updates player height each loop. */
void move_player(uint8_t move)
{
    
    /* Checks if button s3 is pushed if so, the player can hop two cells. */
    if ((PIND & (1<<7)) && (player_move == 1)) {
        
        player_move = 0;
        
        /* Player hops up. */
        if (move == MOVE_UP) {
            player_height += 2;
            if (player_height > 5) {
                player_height -= 5;
            }
        
        /* Player hops down. */    
        } else if (move == MOVE_DOWN) {
            player_height -= 2;
            if (player_height < 1) {
                player_height += 5;
            }
        }
        
    /* Otherwise, the player moves one cell. */     
    } else if (player_move == 1) {
        
        
        player_move = 0;
                
        /* Player moves up. */
        if (move == MOVE_UP) {
            player_height++;
            while (player_height > 5) {
                player_height -= 5;
            }
        
        /* Player moves down. */
        } else if (move == MOVE_DOWN) {
            player_height--;
            while (player_height < 1) {
                player_height += 5;
            }
        }
    }
}

/* Returns the player's current height. */
uint8_t player_get_height(void)
{
    player_move = 1;
    return player_height;
}
