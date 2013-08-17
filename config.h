
#ifndef F_CPU
// #define F_CPU 16000000UL
#define F_CPU 8000000UL
#endif


/** 
 * Config
 */
#define HC4094_PORT PORTC
#define HC4094_DDR  DDRC

#define HC4094_CLK    (1<<PC0)
#define HC4094_DATA   (1<<PC1)
#define HC4094_STR    (1<<PC2)
#define HC4094_OE     (1<<PC3)


