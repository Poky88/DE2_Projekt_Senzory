/**
 * @file
 * @brief Implementace ovladače senzoru DHT12.
 * @ingroup dht12
 *
 * Modul využívá I2C/TWI knihovnu (@ref twi) pro komunikaci se senzorem
 * DHT12 na pevně dané adrese. Jsou zpřístupněny funkce pro čtení teploty
 * a relativní vlhkosti v základní přesnosti.
 */

#include <stdint.h>
#include "twi.h"
#include "dht12.h"

/**
 * @brief I2C adresa senzoru DHT12.
 */
#define DHT12_ADDR 0x5C

void DHT12_init(void)
{
    /* V současné verzi není nutná žádná speciální inicializace. */
}

float DHT12_getHumidity(void)
{
    uint8_t buf[2];

    /* Registry 0x00 a 0x01: integer a desetinná část vlhkosti. */
    twi_readfrom_mem_into(DHT12_ADDR, 0x00, buf, 2);

    uint8_t hum_int = buf[0];
    uint8_t hum_dec = buf[1];

    return hum_int + hum_dec / 10.0f;
}

float DHT12_getTemperature(void)
{
    uint8_t buf[2];

    /* Registry 0x02 a 0x03: integer a desetinná část teploty. */
    twi_readfrom_mem_into(DHT12_ADDR, 0x02, buf, 2);

    uint8_t t_int = buf[0];
    uint8_t t_dec = buf[1];

    /* Poznámka: sign bit (záporné teploty) zde není zpracován,
     pro běžné pokojové teploty to není problém. */
    return t_int + t_dec / 10.0f;
}
