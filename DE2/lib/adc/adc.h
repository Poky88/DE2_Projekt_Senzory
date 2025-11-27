#ifndef ADC_H
#define ADC_H

#include <avr/io.h>
#include <stdint.h>

/**
 * @file
 * @defgroup adc ADC Driver 
 * @brief Jednoduchý ovladač 10bit ADC převodníku mikrokontroléru AVR.
 *
 * Poskytuje funkce pro inicializaci převodníku a čtení hodnot z libovolného
 * analogového kanálu (A0–A7).
 *
 * @{
 */

/**
 * @brief Inicializuje ADC modul.
 *
 * Nastaví referenční napětí na AVcc (typicky 5 V), zapne ADC a nastaví
 * prescaler na 64.
 */
void ADC_init(void);

/**
 * @brief Provede čtení z daného ADC kanálu.
 *
 * @param channel Číslo analogového kanálu (0 = A0, 1 = A1, ...).
 * @return 10bit hodnota z ADC (0–1023).
 */
uint16_t ADC_read(uint8_t channel);

/** @} */

#endif
