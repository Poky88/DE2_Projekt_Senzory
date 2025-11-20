/*
 * Read values from DHT11, MQ-135, and GP2Y1010AU0F sensors
 * and display them on OLED (I2C).
 *
 * PlatformIO project without Arduino framework.
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

#define DUST_LED_PIN  PB4
#define DUST_ADC_PIN  0       // A0
#define MQ135_ADC_PIN 1       // A1

volatile uint8_t flag_update = 0;
volatile uint8_t dht_values[5];

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
    oled_puts("CO2[ppm]:");
    oled_display();
}

// --- Timer1 nastavení ----------------------------------------------------
void timer1_init(void)
{
    tim1_ovf_1sec();
    tim1_ovf_enable();
}

// --- ADC inicializace ----------------------------------------------------
void adc_init(void)
{
    ADMUX = (1 << REFS0); 
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);
}

// --- ADC čtení kanálu ----------------------------------------------------
uint16_t adc_read(uint8_t channel)
{
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
    return ADC;
}

// --- Prachový senzor GP2Y1010AU0F ---------------------------------------
uint16_t dust_read(void)
{
    uint32_t sum = 0;
    for (uint8_t i = 0; i < 10; i++)
    {
        PORTB |= (1 << DUST_LED_PIN);
        _delay_us(280);
        sum += adc_read(DUST_ADC_PIN);
        _delay_us(40);
        PORTB &= ~(1 << DUST_LED_PIN);
        _delay_ms(10);
    }
    return (uint16_t)(sum / 10);
}

// --- MQ135 jednoduchý průměr ------------------------------------------------
uint16_t mq135_read(void)
{
    uint32_t sum = 0;
    for (uint8_t i = 0; i < 10; i++)
    {
        sum += adc_read(MQ135_ADC_PIN);
        _delay_ms(10);
    }
    return (uint16_t)(sum / 10);
}

// --- MQ135 přepočet ADC -> ppm (jednoduchý lineární model) -----------------
float mq135_co2(uint16_t raw)
{
    if (raw < 200) raw = 200;   // ochrana proti nízkým hodnotám
    return (raw - 200) * 2.0;   // orientační lineární přepočet
}

// --- Hlavní funkce -------------------------------------------------------
int main(void)
{
    char text[16];
    uint16_t dust_raw, mq_raw;

    DDRB |= (1 << DUST_LED_PIN);

    adc_init();
    twi_init();
    oled_setup();
    timer1_init();
    sei();

    while (1)
    {
        if (flag_update)
        {
            // --- DHT11 ---
            twi_readfrom_mem_into(DHT_ADR, DHT_HUM_MEM, dht_values, 5);
            uint8_t hum_int = dht_values[0];
            uint8_t temp_int = dht_values[2];

            // --- Prach ---
            dust_raw = dust_read();
            float dust_conc = dust_raw * 0.17;

            // --- MQ135 ---
            mq_raw = mq135_read();
            float co2_ppm = mq135_co2(mq_raw);

            // --- Výpis na OLED ---
            oled_gotoxy(13, 2);
            sprintf(text, "%3u", temp_int);
            oled_puts(text);

            oled_gotoxy(13, 3);
            sprintf(text, "%3u", hum_int);
            oled_puts(text);

            oled_gotoxy(13, 4);
            sprintf(text, "%4u", (uint16_t)dust_conc);
            oled_puts(text);

            oled_gotoxy(13, 5);
            sprintf(text, "%4u", (uint16_t)co2_ppm);
            oled_puts(text);

            oled_display();
            flag_update = 0;
        }
    }
    return 0;
}

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
