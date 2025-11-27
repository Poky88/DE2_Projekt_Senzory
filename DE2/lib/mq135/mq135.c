/**
 * @file
 * @brief Implementace ovladače senzoru MQ-135.
 * @ingroup mq135
 *
 * Modul využívá knihovnu @ref adc pro čtení analogové hodnoty z
 * příslušného ADC kanálu. Naměřená hodnota je dále zpracována do
 * jednoduchého odhadu koncentrace CO2 v ppm.
 */

#include <avr/io.h>
#include <util/delay.h>
#include "adc.h"
#include "mq135.h"

/**
 * @brief Číslo ADC kanálu, na který je připojen výstup senzoru MQ-135.
 *
 * Při změně zapojení (jiný analogový vstup) je nutné upravit tuto konstantu.
 */
#define MQ135_ADC_CHANNEL 1 // A1

void MQ135_init(void)
{
    /* Zatím nic, ale místo pro případnou kalibraci nebo warm-up delay. */
}

uint16_t MQ135_read_raw(void)
{
    uint32_t sum = 0;

    /* Provedeme několik měření a vrátíme jejich průměr. */
    for (uint8_t i = 0; i < 10; i++)
    {
        sum += ADC_read(MQ135_ADC_CHANNEL);
        _delay_ms(10);
    }

    return (uint16_t)(sum / 10);
}

float MQ135_raw_to_co2(uint16_t raw)
{
    /* Ochrana proti příliš nízkým hodnotám (šum, nestabilita senzoru). */
    if (raw < 200)
        raw = 200;

    /* Jednoduchý lineární model, pouze orientační převod na ppm. */
    return (raw - 200) * 2.0f;
}

float MQ135_read_co2(void)
{
    uint16_t raw = MQ135_read_raw();
    return MQ135_raw_to_co2(raw);
}
