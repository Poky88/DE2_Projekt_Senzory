#include "adc.h"

void ADC_init(void)
{
    // Reference voltage = AVcc, ADC enabled, prescaler = 64
    ADMUX = (1 << REFS0);
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);
}

uint16_t ADC_read(uint8_t channel)
{
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
    ADCSRA |= (1 << ADSC);              // start conversion
    while (ADCSRA & (1 << ADSC));       // wait for completion
    return ADC;
}
