#ifndef GP2Y1010_H
#define GP2Y1010_H

#include <avr/io.h>
#include <util/delay.h>
#include "adc.h"

#define GP2Y_LED_PIN PD2
#define GP2Y_LED_DDR DDRD
#define GP2Y_LED_PORT PORTD

void GP2Y_init(void);
uint16_t GP2Y_read(void);

#endif
