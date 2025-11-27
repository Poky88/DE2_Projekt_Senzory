/**
 * @file
 * @brief Implementace ovladače 10bit ADC převodníku AVR.
 * @ingroup adc
 */

#include "adc.h"

void ADC_init(void)
{
    // Reference voltage = AVcc, ADC enabled, prescaler = 64
    ADMUX = (1 << REFS0);
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);
}

uint16_t ADC_read(uint8_t channel)
{
    // zvolit kanál (spodní 4 bity ADMUX)
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);

    // spustit konverzi
    ADCSRA |= (1 << ADSC);

    // čekat na dokončení
    while (ADCSRA & (1 << ADSC))
        ;

    // vrátit výsledek (10bit)
    return ADC;
}
