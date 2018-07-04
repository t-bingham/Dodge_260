/** @file   wall.c
    @author T. Mann (tma123) & T. Bingham (tbi18)
    @date   15 Oct 2017
    @brief  Wall module, also handles collisions.
    @note   Contains all functions needed to generate and move the wall.
*/

#include "system.h"
#include "player.h"
#include "pio.h"
#include "ledmat.h"
#include <stdlib.h>

static uint8_t wall[6];
static uint8_t wall_position;
static uint8_t wall_speed;
static uint8_t wall_counter; // Used to determine the number of loops before changing position.
static uint8_t score_counter;
static uint8_t level;

static int8_t wall_direction;

/* Initialises the wall. */
void wall_init(void)
{
    wall_generate();
    wall_position = 7; //Always comes from position 7 first round.
    level = 0;
    score_counter = 0;
    wall_speed = 0;
    wall_direction = -1;

}

/* Updates the wall's position.
 * Generates a new wall when the previous one has reached the player.
 */
uint8_t wall_update(void)
{
    /* Updates wall position. */

    uint8_t loops = 70 - wall_speed;
    uint8_t i = 1;
    uint8_t exitflag = 0;

    /* Loops so wall isn't updated every clock tick. */
    if (wall_counter == loops) {
        wall_position += wall_direction;
        wall_counter = 0;
    } else {
        wall_counter++;
    }

    ledmat_high_all();

    /* Checks if the player made it through the gap in the wall. */
    if (wall_position == 4 && collision()) {
        return !exitflag;
    }

    if (wall_position == (4 + wall_direction)) {
        score_counter++;

        /* Speeds up the wall by increasing the level every 5 successes. */
        if ((score_counter % 5 == 0) && (wall_speed < 30)) {
            level += 1;
            wall_speed = 10 * level;
        }

        /* Generates a new wall.
         * Resets the counter variable.
         */
        wall_counter = 0;
        wall_generate();

        /* Determines the wall starting position based on wall direction. */
        if (wall_direction == -1) {
            wall_position = 7;
        } else {
            wall_position = 1;
        }
    }

    /* Displaying wall. */
    while (i < 6) {
        if (wall[i] == 1)
            ledmat_low_cell(wall_position, i);

        i++;
    }


    return exitflag;
}

/* Generates a new wall.
 * Includes generating the gap position, filling in the wall array,
 * and choosing which direction the wall will come from.
 */
void wall_generate(void)
{
    uint8_t i = 1;

    /* Randomising wall gap. */
    uint8_t gap_position = rand() % 5 + 1;

    /* Randomising wall direction. */
    wall_direction = rand() % 2;

    if (wall_direction == 0)
        wall_direction = -1;

    /* Filling in wall array. */
    while (i < 6) {
        if (i != gap_position) {
            wall[i] = 1;
        } else {
            wall[i] = 0;
        }
        i++;
    }

}

/* Checks for player collision. */
int collision(void)
{
    uint8_t player_height = player_get_height();

    /* Compares player location with wall array. */
    if (wall[player_height])
        return 1;

    return 0;

}
