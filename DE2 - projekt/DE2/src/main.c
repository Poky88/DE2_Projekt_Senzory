/*
 * Read values from DHT11, MQ-9, and GP2Y1010AU0F sensors
 * and display them on OLED (I2C).
 *
 * Developed in PlatformIO without Arduino framework.
 * (c) 2024, MIT license
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "timer.h"
#include "twi.h"
#include "oled.h"

#define DHT_ADR       0x5C
#define DHT_HUM_MEM   0
#define DHT_TEMP_MEM  2

#define DUST_LED_PIN  PB4     // D4 - řídí LED v senzoru prachu
#define DUST_ADC_PIN  0       // A0
#define MQ9_ADC_PIN   1       // A1

volatile uint8_t flag_update = 0;
volatile uint8_t dht_values[5];

// --- Inicializace OLED displeje --------------------------------
void oled_setup(void)
{
    oled_init(OLED_DISP_ON);
    oled_clrscr();
    oled_charMode(DOUBLESIZE);
    oled_puts("Air Monitor");
    oled_charMode(NORMALSIZE);
    oled_gotoxy(0, 2);
    oled_puts("T[°C]:");
    oled_gotoxy(0, 3);
    oled_puts("H[%]:");
    oled_gotoxy(0, 4);
    oled_puts("Prach[ug/m3]:");
    oled_gotoxy(0, 5);
    oled_puts("CO2[ppm]:");
    oled_display();
}

// --- Timer1 nastavení (1s overflow) -----------------------------
void timer1_init(void)
{
    tim1_ovf_1sec();
    tim1_ovf_enable();
}

// --- ADC inicializace ------------------------------------------
void adc_init(void)
{
    ADMUX = (1 << REFS0);                    // referenční napětí AVcc
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1); // prescaler 64
}

// --- ADC čtení z kanálu ----------------------------------------
uint16_t adc_read(uint8_t channel)
{
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
    return ADC;
}

// --- Čtení senzoru prachu --------------------------------------
uint16_t dust_read(void)
{
    PORTB |= (1 << DUST_LED_PIN);     // zapni IR LED
    _delay_us(280);
    uint16_t val = adc_read(DUST_ADC_PIN);
    _delay_us(40);
    PORTB &= ~(1 << DUST_LED_PIN);    // vypni IR LED
    return val;
}

// --- Hlavní funkce ---------------------------------------------
int main(void)
{
    char text[16];
    uint16_t dust_raw, co2_raw;

    DDRB |= (1 << DUST_LED_PIN); // výstup pro řízení LED senzoru prachu

    adc_init();
    twi_init();
    oled_setup();
    timer1_init();
    sei();

    while (1)
    {
        if (flag_update)
        {
            // --- DHT11 (teplota, vlhkost) ---
            twi_readfrom_mem_into(DHT_ADR, DHT_HUM_MEM, dht_values, 5);
            uint8_t hum_int = dht_values[0];
            uint8_t temp_int = dht_values[2];

            // --- Prach (GP2Y1010AU0F) ---
            dust_raw = dust_read();
            float dust_conc = dust_raw * 0.17;   // přibližný přepočet na µg/m³

            // --- CO2 (MQ9) ---
            co2_raw = adc_read(MQ9_ADC_PIN);
            float co2_ppm = (float)co2_raw * 1.5; // přibližný přepočet na ppm

            // --- Výpis na OLED ---
            oled_gotoxy(8, 2);
            sprintf(text, "%3u", temp_int);
            oled_puts(text);

            oled_gotoxy(8, 3);
            sprintf(text, "%3u", hum_int);
            oled_puts(text);

            oled_gotoxy(13, 4);
            sprintf(text, "%4u", (uint16_t)dust_conc);
            oled_puts(text);

            oled_gotoxy(10, 5);
            sprintf(text, "%4u", (uint16_t)co2_ppm);
            oled_puts(text);

            oled_display();
            flag_update = 0;
        }
    }
    return 0;
}

// --- Přerušení Timer1 ------------------------------------------
ISR(TIMER1_OVF_vect)
{
    static uint8_t n_ovfs = 0;
    n_ovfs++;
    if (n_ovfs >= 1)   // každých 5 sekund
    {
        n_ovfs = 0;
        flag_update = 1;
    }
}
