/**
 * 74HC4094 driver
 *
 * (c) 2013 Matthias Hannig
 */

#include "hc4094.h"
#include <avr/io.h>
#include <util/delay.h>

/**
 * Initialize HC4094 driver.
 */
void hc4094_init()
{
  // Set data direction
  HC4094_DDR |= HC4094_CLK|HC4094_STR|HC4094_OE|HC4094_DATA;
}


/** 
 * Set output enabled
 */
void hc4094_output( char enabled ) 
{
  if( enabled ) {
    HC4094_PORT |= HC4094_OE;
  }
  else {
    HC4094_PORT &= ~HC4094_OE;
  }
}


/**
 * Write byte 
 */ 
void hc4094_write( char byte ) 
{
  int i, bit;
 
  // toggle bits
  for( i = 0; i < 8; i++ ) {
    bit = (byte >> i)&1;
    
    // pull down clock
    HC4094_PORT &= ~HC4094_CLK;
    
    if( bit ) {
      HC4094_PORT |= HC4094_DATA; 
    }
    else {
      HC4094_PORT &= ~HC4094_DATA; 
    }

    // raise clock
    HC4094_PORT |= HC4094_CLK;

    _delay_us(1);
  }

  // pull down clock
  HC4094_PORT &= ~HC4094_CLK;
}


/**
 * Execute strobe pulse
 */
void hc4094_strobe()
{
  HC4094_PORT |= HC4094_STR;
  _delay_us(1);
  HC4094_PORT &= ~HC4094_STR;
  _delay_us(1);
}

