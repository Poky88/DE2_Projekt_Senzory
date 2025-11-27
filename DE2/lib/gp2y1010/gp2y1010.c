/**
 * @file
 * @brief Implementace ovladače senzoru GP2Y1010AU0F.
 * @ingroup gp2y1010
 *
 * Modul realizuje doporučené časování LED a měření analogového signálu
 * z prachového senzoru GP2Y1010AU0F. Konverzi na fyzikální jednotky
 * (µg/m³) je vhodné provádět v nadřazeném kódu, kde lze zohlednit
 * kalibraci konkrétního kusu senzoru.
 */

#include "gp2y1010.h"

void GP2Y_init(void)
{
    /* LED pin jako výstup, LED ve výchozím stavu vypnuta (HIGH). */
    GP2Y_LED_DDR  |= (1 << GP2Y_LED_PIN);
    GP2Y_LED_PORT |= (1 << GP2Y_LED_PIN);
}

uint16_t GP2Y_read(void)
{
    uint16_t val;

    /* Zapnout LED, vyčkat doporučený čas, změřit a zase vypnout. */
    GP2Y_LED_PORT &= ~(1 << GP2Y_LED_PIN);  // LED ON (LOW)
    _delay_us(280);
    val = ADC_read(GP2Y_ADC_CHANNEL);       // čtení z příslušného ADC kanálu
    _delay_us(40);
    GP2Y_LED_PORT |= (1 << GP2Y_LED_PIN);   // LED OFF (HIGH)
    _delay_us(9680);

    return val;
}
