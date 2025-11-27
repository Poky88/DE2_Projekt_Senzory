#ifndef GP2Y1010_H
#define GP2Y1010_H

#include <avr/io.h>
#include <util/delay.h>
#include "adc.h"

/**
 * @file
 * @defgroup gp2y1010 GP2Y1010 Dust Sensor Library 
 * @code
 * #include "gp2y1010.h"
 * @endcode
 *
 * @brief Jednoduchý ovladač optického prachového senzoru GP2Y1010AU0F.
 *
 * Knihovna implementuje základní časování LED a vzorkování analogového
 * výstupu senzoru v souladu s doporučením výrobce. Výstupem je surová
 * hodnota z ADC, kterou lze dále převádět na aproximovaný odhad
 * koncentrace prachových částic.
 *
 * @{
 */

/**
 * @brief Pin mikrokontroléru, který ovládá LED prachového senzoru.
 *
 * Symbolické definice vycházejí z portů mikrokontroléru.
 */
#define GP2Y_LED_PIN   PD3  // D3
#define GP2Y_LED_DDR   DDRD
#define GP2Y_LED_PORT  PORTD

/**
 * @brief ADC kanál, na který je připojen analogový výstup senzoru.
 *
 * Hodnota odpovídá číslu kanálu ADC (0 = A0, 1 = A1, ...). Při změně
 * zapojení senzoru na jiný analogový vstup upravte tuto konstantu.
 */
#define GP2Y_ADC_CHANNEL 0  // A0

/**
 * @brief Inicializace GPIO pinu pro ovládání LED senzoru.
 *
 * Nastaví pin LED jako výstup a LED uvede do výchozího stavu (typicky
 * vypnutá – logická 1, dle doporučení v datasheetu).
 */
void GP2Y_init(void);

/**
 * @brief Provede jedno měření prachového senzoru.
 *
 * Funkce provede krátký záblesk infra LED, v doporučeném čase odečte
 * analogový výstup z ADC a poté LED opět vypne. Vrací surovou hodnotu
 * z ADC (0–1023). Pro zmenšení šumu se obvykle používá průměr z více
 * těchto měření.
 *
 * @return Surová hodnota z ADC (0–1023).
 */
uint16_t GP2Y_read(void);

/** @} */

#endif /* GP2Y1010_H */
