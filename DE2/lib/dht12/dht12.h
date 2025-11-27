#ifndef DHT12_H
#define DHT12_H

#include <stdint.h>

/**
 * @file
 * @defgroup dht12 DHT12 Temperature & Humidity Sensor Library 
 * @code
 * #include "dht12.h"
 * @endcode
 *
 * @brief Ovladač senzoru DHT12 (teplota a vlhkost, I2C).
 *
 * Knihovna poskytuje jednoduché funkce pro načtení teploty a relativní
 * vlhkosti z čidla DHT12 připojeného na I2C sběrnici. Přesnost a absolutní
 * kalibrace senzoru závisí na konkrétním kusu a nejsou v rámci této knihovny
 * dále korigovány.
 *
 * @{
 */

/**
 * @brief Inicializace senzoru DHT12.
 *
 * V aktuální implementaci neprovádí žádnou speciální inicializaci senzoru.
 * Funkce je připravena pro případné rozšíření (test přítomnosti na sběrnici,
 * ověření adresy apod.).
 */
void DHT12_init(void);

/**
 * @brief Vrátí teplotu v °C.
 *
 * Funkce načte dva bajty z odpovídajících registrů senzoru DHT12 a vrátí
 * teplotu se základní desetinnou přesností (rozsah zhruba -20 až +60 °C dle
 * datasheetu senzoru).
 *
 * @return Teplota v °C (float).
 */
float DHT12_getTemperature(void);

/**
 * @brief Vrátí relativní vlhkost v %.
 *
 * Funkce načte dva bajty z odpovídajících registrů senzoru DHT12 a vrátí
 * relativní vlhkost se základní desetinnou přesností (0–100 %).
 *
 * @return Relativní vlhkost v % (float).
 */
float DHT12_getHumidity(void);

/** @} */

#endif /* DHT12_H */
