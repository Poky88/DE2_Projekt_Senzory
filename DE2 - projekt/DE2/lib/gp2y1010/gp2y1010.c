#include "gp2y1010.h"

void GP2Y_init(void)
{
    GP2Y_LED_DDR |= (1 << GP2Y_LED_PIN);   // LED pin as output
    GP2Y_LED_PORT |= (1 << GP2Y_LED_PIN);  // LED OFF (HIGH)
}

uint16_t GP2Y_read(void)
{
    uint16_t val;

    GP2Y_LED_PORT &= ~(1 << GP2Y_LED_PIN); // LED ON
    _delay_us(280);
    val = ADC_read(1);                     // read from ADC1
    _delay_us(40);
    GP2Y_LED_PORT |= (1 << GP2Y_LED_PIN);  // LED OFF
    _delay_us(9680);

    return val;
}
