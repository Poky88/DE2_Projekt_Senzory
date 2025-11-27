#ifndef MQ135_H
#define MQ135_H

#include <stdint.h>

/**
 * @file
 * @defgroup mq135 MQ-135 Gas Sensor Library 
 * @code
 * #include "mq135.h"
 * @endcode
 *
 * @brief Jednoduchý ovladač senzoru MQ-135 pro měření kvality vzduchu.
 *
 * Knihovna poskytuje funkce pro čtení surové hodnoty z ADC a velmi
 * orientační přepočet na „ekvivalent“ koncentrace CO2 v ppm. Převod
 * není metrologicky kalibrován a slouží pouze pro demonstrační účely.
 *
 * @{
 */

/**
 * @brief Inicializace senzoru MQ135.
 *
 * V aktuální implementaci neprovádí žádnou konfiguraci. Funkce je
 * připravena pro případné doplnění kalibrace, warm-up delay apod.
 */
void MQ135_init(void);

/**
 * @brief Přečte surovou hodnotu z ADC a vrátí průměr z několika měření.
 *
 * Funkce provede několik vzorkování na příslušném ADC kanálu, mezi
 * vzorky vkládá krátké zpoždění a vrátí celočíselný aritmetický průměr.
 *
 * @return Průměrná hodnota z ADC (0–1023).
 */
uint16_t MQ135_read_raw(void);

/**
 * @brief Přepočet surové ADC hodnoty na orientační koncentraci CO2.
 *
 * Funkce použije jednoduchý lineární model pro odhad koncentrace CO2
 * v ppm. Při velmi nízkých hodnotách je vstupní parametr oříznut na 200,
 * aby se omezil vliv šumu a nestability senzoru v nízkém rozsahu.
 *
 * @param raw Surová hodnota z ADC (0–1023).
 * @return Odhadovaná koncentrace CO2 v ppm (orientačně).
 */
float MQ135_raw_to_co2(uint16_t raw);

/**
 * @brief Přečte senzor a rovnou vrátí odhad koncentrace CO2.
 *
 * Funkce interně zavolá MQ135_read_raw() a výsledek následně předá
 * funkci MQ135_raw_to_co2().
 *
 * @return Odhadovaná koncentrace CO2 v ppm (orientačně).
 */
float MQ135_read_co2(void);

/** @} */

#endif
