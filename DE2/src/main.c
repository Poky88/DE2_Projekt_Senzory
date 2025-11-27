#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "timer.h"
#include "twi.h"
#include "oled.h"
#include "adc.h"
#include "gp2y1010.h"
#include "mq135.h"
#include "dht12.h"

volatile uint8_t flag_update = 0;

/**
 * @file
 * @brief Hlavní aplikace pro měření kvality vnitřního prostředí.
 *
 * Program periodicky měří teplotu a vlhkost (DHT12), koncentraci
 * prachových částic (GP2Y1010AU0F) a odhad kvality vzduchu / CO2
 * (MQ-135). Naměřené hodnoty se zobrazují na OLED displeji.
 *
 * Aplikace využívá moduly: @ref dht12, @ref gp2y1010, @ref mq135,
 * @ref adc, @ref twi, @ref oled a @ref timer.
 *
 * Časovač TIMER1 generuje periodické přerušení, které nastavuje vlajku
 * @ref flag_update, podle které hlavní smyčka provádí aktualizaci.
 */


/**
 * @brief Inicializace a rozložení OLED displeje.
 *
 * Zapíše statické texty a připraví rozvržení obrazovky.
 */

// --- OLED inicializace --------------------------------------------------
void oled_setup(void)
{
    oled_init(OLED_DISP_ON);
    oled_clrscr();
    oled_charMode(DOUBLESIZE);
    oled_puts(" Monitor");
    oled_charMode(NORMALSIZE);
    oled_gotoxy(0, 2);
    oled_puts("Teplota[°C]:");
    oled_gotoxy(0, 3);
    oled_puts("Vlhkost[%]:");
    oled_gotoxy(0, 4);
    oled_puts("Prach[ug/m3]:");
    oled_gotoxy(0, 5);
    oled_puts("Plyny[ppm]:");
    oled_display();
}

/**
 * @brief Inicializuje časovač TIMER1 pro periodické přerušení.
 *
 * Každé přetečení nastaví vlajku @ref flag_update ve ISR.
 */

// --- Timer1 nastavení ----------------------------------------------------
void timer1_init(void)
{
    tim1_ovf_1sec();
    tim1_ovf_enable();
}

/**
 * @brief Vstupní bod programu.
 *
 * Provede inicializaci všech periferií (ADC, I2C, senzory, OLED, časovač)
 * a poté v nekonečné smyčce čeká na příznak aktualizace. Po jeho nastavení
 * provede měření senzorů a zobrazí výsledky na OLED displeji.
 */

// --- Hlavní funkce -------------------------------------------------------
int main(void)
{
    char text[16];

    // Inicializace periferií a senzorů
    ADC_init();        // ADC (pro MQ135, GP2Y1010)
    twi_init();        // I2C/TWI (pro DHT12, OLED)
    GP2Y_init();       // Prachový senzor
    MQ135_init();      // Plynový senzor
    DHT12_init();      // Teplota + vlhkost

    oled_setup();
    timer1_init();
    sei();


    while (1)
    {
        if (flag_update)
        {
            //------------------------------------------------------------------
            // DHT12 – teplota a vlhkost
            //------------------------------------------------------------------
            float temp = DHT12_getTemperature();
            float hum  = DHT12_getHumidity();

            // pro zobrazení na OLED stačí celé hodnoty
            uint8_t temp_int = (uint8_t)temp;
            uint8_t hum_int  = (uint8_t)hum;

            //------------------------------------------------------------------
            // Prach – GP2Y1010AU0F
            //------------------------------------------------------------------
            uint16_t dust_raw = 0;
            for (uint8_t i = 0; i < 10; i++)
            {
                dust_raw += GP2Y_read();
            }
            dust_raw /= 10;
            float dust_conc = dust_raw * 0.17f;   // převod na ug/m3 (orientační)

            //------------------------------------------------------------------
            // MQ135 – CO2 (orientačně)
            //------------------------------------------------------------------
            uint16_t mq_raw = MQ135_read_raw();
            float co2_ppm = MQ135_raw_to_co2(mq_raw);

            //------------------------------------------------------------------
            // Výpis na OLED
            //------------------------------------------------------------------

            // Teplota
            oled_gotoxy(13, 2);
            sprintf(text, "%4u", (uint16_t)temp_int);
            oled_puts(text);

            // Vlhkost
            oled_gotoxy(13, 3);
            sprintf(text, "%4u", (uint16_t)hum_int);
            oled_puts(text);

            // Prach
            oled_gotoxy(13, 4);
            sprintf(text, "%4u", (uint16_t)dust_conc);
            oled_puts(text);

            // Plyny
            oled_gotoxy(13, 5);
            sprintf(text, "%4u", (uint16_t)co2_ppm);
            oled_puts(text);


            oled_display();
            flag_update = 0;
        }
    }

    return 0;
}

/**
 * @brief Obsluha přerušení od TIMER1.
 *
 * Každé přetečení nastaví vlajku pro aktualizaci měření v hlavní smyčce.
 */

// --- Timer interrupt -----------------------------------------------------
ISR(TIMER1_OVF_vect)
{
    static uint8_t n_ovfs = 0;
    n_ovfs++;
    if (n_ovfs >= 1)
    {
        n_ovfs = 0;
        flag_update = 1;
    }
}
