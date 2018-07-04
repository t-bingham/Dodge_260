/** @file   ledmat.c
    @author M. P. Hayes, UCECE (Modified by: T. Mann (tma123) & T. Bingham (tbi18))
    @date   23 August 2010 (Modification date: 15 Oct 2017)
    @brief  Functions used to help draw on the Ledmat using the PIO functions.
*/

#include "system.h"
#include "pacer.h"
#include "pio.h"

uint8_t state;
uint8_t ticker = 1;

/* Initialises all LEDs and turns them off. */
void ledmat_init(void) 
{
    pio_config_set (LEDMAT_ROW1_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_ROW2_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_ROW3_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_ROW4_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_ROW5_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_ROW6_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_ROW7_PIO, PIO_OUTPUT_HIGH);
    
    pio_config_set (LEDMAT_COL1_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_COL2_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_COL3_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_COL4_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_COL5_PIO, PIO_OUTPUT_HIGH);
    
    state = 0;
}

/* Turns off all the LEDs. */
void ledmat_high_all(void)
{
    /* Rows */
    pio_output_high(LEDMAT_ROW1_PIO);
    pio_output_high(LEDMAT_ROW2_PIO);
    pio_output_high(LEDMAT_ROW3_PIO);
    pio_output_high(LEDMAT_ROW4_PIO);
    pio_output_high(LEDMAT_ROW5_PIO);
    pio_output_high(LEDMAT_ROW6_PIO);
    pio_output_high(LEDMAT_ROW7_PIO);
 
    /* Columns */
    pio_output_high(LEDMAT_COL1_PIO);
    pio_output_high(LEDMAT_COL2_PIO);
    pio_output_high(LEDMAT_COL3_PIO);
    pio_output_high(LEDMAT_COL4_PIO);
    pio_output_high(LEDMAT_COL5_PIO);
}

/* Turns on all the LEDs. */
void ledmat_low_all(void)
{
    /* Rows */
    pio_output_low(LEDMAT_ROW1_PIO);
    pio_output_low(LEDMAT_ROW2_PIO);
    pio_output_low(LEDMAT_ROW3_PIO);
    pio_output_low(LEDMAT_ROW4_PIO);
    pio_output_low(LEDMAT_ROW5_PIO);
    pio_output_low(LEDMAT_ROW6_PIO);
    pio_output_low(LEDMAT_ROW7_PIO);
 
    /* Columns */
    pio_output_low(LEDMAT_COL1_PIO);
    pio_output_low(LEDMAT_COL2_PIO);
    pio_output_low(LEDMAT_COL3_PIO);
    pio_output_low(LEDMAT_COL4_PIO);
    pio_output_low(LEDMAT_COL5_PIO);
}

/* Turns a single cell on. */
void ledmat_low_cell(uint8_t row, uint8_t column)
{
    switch (row) {
    case 1: 
        pio_output_low(LEDMAT_ROW1_PIO); break;
    case 2: 
        pio_output_low(LEDMAT_ROW2_PIO); break;
    case 3: 
        pio_output_low(LEDMAT_ROW3_PIO); break;
    case 4: 
        pio_output_low(LEDMAT_ROW4_PIO); break;
    case 5: 
        pio_output_low(LEDMAT_ROW5_PIO); break;
    case 6: 
        pio_output_low(LEDMAT_ROW6_PIO); break;
    case 7: 
        pio_output_low(LEDMAT_ROW7_PIO); break;
    }
    
    switch (column) {
    case 1: 
        pio_output_low(LEDMAT_COL1_PIO); break;
    case 2: 
        pio_output_low(LEDMAT_COL2_PIO); break;
    case 3: 
        pio_output_low(LEDMAT_COL3_PIO); break;
    case 4: 
        pio_output_low(LEDMAT_COL4_PIO); break;
    case 5: 
        pio_output_low(LEDMAT_COL5_PIO); break;
    }
    
}

/* Displays an x. */
void ledmat_loser(void) 
{
    uint64_t i = 0;    
    
    while (i < 10000) {
        if (state) {    
            ledmat_high_all();
                        
            ledmat_low_cell(2,2);
            ledmat_low_cell(2,4);
            ledmat_low_cell(3,2);
            ledmat_low_cell(3,4);

            ledmat_low_cell(5,2);
            ledmat_low_cell(5,4);
            ledmat_low_cell(6,2);
            ledmat_low_cell(6,4);
            
        } else {
            ledmat_high_all();
            
            ledmat_low_cell(3,3);     
            ledmat_low_cell(4,3);     
            ledmat_low_cell(5,3);        
        }
        
        state = !state;
        i++;
    }
    
    ledmat_high_all();
}

/* Displays a crown. */
void ledmat_winner(void) 
{
    uint64_t i = 0;    
    
    while (i < 10000) {
        if (state) {    
            ledmat_high_all();
            
            ledmat_low_cell(2,2);
            ledmat_low_cell(4,2);
            ledmat_low_cell(6,2);
        } else {
            ledmat_high_all();
            
            ledmat_low_cell(2,3);        
            ledmat_low_cell(3,3);
            ledmat_low_cell(4,3);
            ledmat_low_cell(5,3);
            ledmat_low_cell(6,3);
            
            ledmat_low_cell(2,4);
            ledmat_low_cell(3,4);
            ledmat_low_cell(4,4);
            ledmat_low_cell(5,4);
            ledmat_low_cell(6,4);
        }
        
        state = !state;
        i++;
    }
    
    ledmat_high_all();
}

/* Displays an arrow pointing to the navswitch. */
void ledmat_arrow(void) 
{
    uint8_t i = 0;
    
    while (i < 2) {
        if (state) {
            ledmat_high_all();
            
            ledmat_low_cell(5,1);        
            ledmat_low_cell(5,2);
            ledmat_low_cell(5,3);
            ledmat_low_cell(5,4);
            ledmat_low_cell(5,5);
        } else {
            ledmat_high_all();
            
            ledmat_low_cell(6,4);
            ledmat_low_cell(4,4);
        }
        
        state = !state;
        i++;
    }
}

/* Displays an ellipsis. */
void ledmat_ready(void) 
{
    ledmat_high_all();
                
    ledmat_low_cell(6,4);
    ledmat_low_cell(4,4);
    ledmat_low_cell(2,4);
}

/* Displays a Y and an N. */
void ledmat_again(void) 
{
    uint64_t i = 0;    
    
    while (i < 100) {
        if (ticker == 1) {    
            ledmat_high_all();
                                    
            ledmat_low_cell(3,2);
            ledmat_low_cell(3,3);
            ledmat_low_cell(3,4);
            
            ledmat_low_cell(1,2);
            ledmat_low_cell(1,3);
            ledmat_low_cell(1,4);
            
            ticker = 2;
            
        } else if (ticker == 2) {
            ledmat_high_all();
       
            ledmat_low_cell(2,3);
            ledmat_low_cell(6,3);
        
            ticker = 3;
            
        } else if (ticker == 3) {
            ledmat_high_all();
            
            ledmat_low_cell(7,2);
            ledmat_low_cell(5,2);
            
            
            ticker = 4;
            
        } else if (ticker == 4) {
            ledmat_high_all();
            
            ledmat_low_cell(6,4);
            
            ticker = 1;
        }
        
        i++;
    }
    
    ledmat_high_all();
}

