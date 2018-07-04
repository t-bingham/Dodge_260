/** @file   game.c
    @author T. Mann (tma123) & T. Bingham (tbi18)
    @date   15 Oct 2017
    @brief  Game module.
    @note   Contains paced loops, handles IR Communication.
*/

#include "system.h"
#include "pio.h"
#include "pacer.h"
#include "player.h"
#include "wall.h"
#include "ledmat.h"
#include "navswitch.h"
#include "ir_uart.h"

#define PACER_RATE 250
#define MESSAGE_RATE 250

int main (void)
{
    system_init();
    ledmat_init();
    navswitch_init();
    ir_uart_init();
    led_init();
    led_on(); 
    pacer_init(PACER_RATE);
    
    /* Initialising variables. */
    uint8_t state = 0;
    uint8_t wall_return = 0;
    uint8_t player_ready = 0;
    uint8_t enemy_ready = 0;
    uint8_t player_again = 0;
    uint8_t enemy_again = 0;
    char ready_response = 'N';
    play_again:
    
    
    /* Waits until both players are ready. 
     * Each loop if an IR Input has been received it is stored until it can be checked. 
     */
    while (!player_ready || !enemy_ready) 
    {
        if (!player_ready) {
            ledmat_arrow();
        }
        
        if (ir_uart_read_ready_p()) {
            ready_response = ir_uart_getc ();
        }
        
        navswitch_update();     
        
        /* When an "R" character is recieved, the enemy's ready state is set to 1. */
        if (ready_response == 'R' && !enemy_ready) {
            enemy_ready = 1;
        }
        
        /* Send "R" character to enemy when ready.
         * Generate seed from the clock value when the player readies up. 	     
         */
        if (navswitch_push_event_p (NAVSWITCH_PUSH) && !player_ready) {
            player_ready = 1;
            ir_uart_putc('R');
            srand(TCNT1);
            ledmat_ready();
            continue;
        }
    }
    
    
    wall_init();
    player_init();
    
    while (1)
    {
        pacer_wait();
        navswitch_update();
     
        
        /* Multiplexing between displaying the player and the wall using state. */
        if (state) {
            ledmat_high_all();
            player_update();
            
        } else {
            ledmat_high_all();
            
            /* If the player loses tell the enemy by sending an "X" character.
             * Then display the losing ledmat pattern. 
             */
            wall_return = wall_update();
            if (wall_return == 1) {
                ir_uart_putc('X');
                ledmat_loser();
                break;
            } 
        }
        
        state = !state;
        
        
        /* Adjusting player location. */
        if (navswitch_push_event_p (NAVSWITCH_EAST))
            move_player(MOVE_UP);
            
        if (navswitch_push_event_p (NAVSWITCH_WEST))
            move_player(MOVE_DOWN);
            
            

        /* Check to see if the other player has lost, 
         * they will have sent an "X" character via IR. 
         * If so, display winning ledmat. 
         */
         if (ir_uart_read_ready_p() && ir_uart_getc () == 'X') {
            ledmat_winner();
            break;
        }
        
    }
    
    char enemy_response;
    
    /* Checking to see if both players want to play again.
     * Each loop if an IR Input is received it is stored until it can be checked.
     */
    while (1) {
        
        if (ir_uart_read_ready_p()) {
            enemy_response = ir_uart_getc ();
        }
        
        /* When player hasn't selected anything yet. */
        if (!player_again) {
            ledmat_again();
            
            /* Player selects yes. 
             * Send the enemy a "Y" to signal that the player wishes to play again. 
             */
            if(navswitch_push_event_p (NAVSWITCH_SOUTH)) {
                ledmat_ready();
                player_again = 1;
                ir_uart_putc('Y');
            }
                    
            /* Player selects no. 
             * Sends a "N" to signal no.
             */    
            if(navswitch_push_event_p (NAVSWITCH_NORTH)) {
                ir_uart_putc('N');
                break;
            }
            
            /* Enemy selects yes. 
             * Occurs when the received IR Transmission is a "Y".
             */
            if (enemy_response == 'Y') {
                enemy_again = 1;
            }
                        
            /* Enemy selects no.  
             * Occurs when the received IR Transmission is a "N".
             * This forces player to quit too.
             */
	        if (enemy_response == 'N') {
                player_again = 0;
                break;
            }
                
        } else {
        
            /* Enemy selects yes. */
            if (enemy_response == 'Y') {
                enemy_again = 1;
                break;
            }
                            
            /* Enemy selects no. 	     
             * Forces player to quit too.
             */
            if (enemy_response == 'N') {
                player_again = 0;
                break;
            }
        }
        
        navswitch_update();
        
    }

    ledmat_high_all();
    
    /* Checks to see if both players want to play again.
     * If yes, resets initialisation. 
     * Then goes back to the start, to allow both players to ready up again.
     */
    if (player_again && enemy_again) {
        player_ready = 0;
        enemy_ready = 0;
        
        player_again = 0;
        enemy_again = 0;
        
        state = 0;
        wall_return = 0;
        
        ready_response = 'N';
        enemy_response = 'A';
        
        goto play_again;
    }
    
    
    led_off();
    
    return 0;
}
