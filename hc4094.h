#ifndef HC4094_H
#define HC4094_H

/**
 * 74HCT4094 driver 
 * 
 * (c) 2013 Matthias Hannig 
 *
 */

#include "config.h"

// Config

#ifndef HC4094_PORT
 #error "74HC4095 PORT is not defined"
#endif

#ifndef HC4094_DDR
 #error "74HC4095 DDR is not defined"
#endif

#ifndef HC4094_CLK
  #error "74HC4095 CLK PIN not defined"
#endif

#ifndef HC4094_STR
  #error "74HC4095 STROBE PIN not defined"
#endif

#ifndef HC4094_OE
  #error "74HC4095 OUTPUT ENABLE PIN not defined"
#endif

#ifndef HC4094_DATA
  #error "74HC4095 DATA PIN not defined"
#endif

// Prototypes

void hc4094_init();
void hc4094_write( char byte );
void hc4094_output( char enabled );
void hc4094_strobe();


#endif


