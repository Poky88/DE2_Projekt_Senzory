# Indoor air quality monitoring system
Measure temperature, humidity, CO2, and particulate matter (PM2.5/PM10) using sensors 
such as DHTx, MQx, SQP4x, SDS011, etc. Display data on a display or send it to a web dashboard.

# Členové týmu

- Tomáš Pokorný
- Tomáš Rosa
- Dominik Uherka
- Daniel Valčík

# Návrh a popis projektu
V tomto projektu se věnujeme návrhem a realizací měření různých veličin. Cílem projektu je pomocí senzorů přijímat data, které jsou zpracovány a zobrazovány na displeji. Díky tomu může uživatel získat informace o okolní teplotě a vlhkosti, množství oxidu uhelnatého, nebo množství prachových částic. 
ještě dopsat:
založený na mikrokontroléru ATmega328


# Popis komponent

### Senzor MQ-135

Senzor MQ-135 je detktor plynů, určený pro monitorování kvality ovzduší. Aktivním prvkem senzoru je tenká vrstva oxidu cíničitého (SnO2), jejíž elektrický odpor se mění v závislosti na přítomnosti a koncentraci určitých plynů. Tento mechanismus umožňuje senzoru reagovat zejména na amoniak (NH3), oxid dusíku (NOx), kouřové částice a především oxid uhličitý (CO2), který je v projektu využíván a zobrazován.

<div align="center">
<img width="400" height="510" alt="Senzor MQ-135" src="https://github.com/user-attachments/assets/5b4b8167-b24f-428c-abb8-88ab65c619fb" />
</div>

Senzor DHT 11

Senzor DHT11 je určený pro měření teploty a relativní vlhkosti vzduchu. Tento typ integruje teplotní čidlo a kapacitní senzor vlhkosti v jednom pouzdře.

Model DHT11 poskytuje teplotní rozsah od 0 do 50 °C s přesností ± 1 °C a relativní vlhkost mezi 20 až 90 % s odchylkou ±4 %.


Senzor DHT11 je digitální snímač teploty a vlhkosti. Senzor se skládá z rezistivních snímačů vlhkosti a teplotního měřicího zařízení NTC (Negative Temperature Coefficient). Komunikace mezi snímačem DHT11 a řídicím mikrokontrolérem probíhá pomocí zjednodušeného jednovodičového sériového protokolu.

<div align="center">
<img width="400" height="1080" alt="image" src="https://github.com/user-attachments/assets/0179e0f3-a192-49c1-9566-df1eb6b1592a" />
</div>

Optický senzor ovzduší GP2Y1010AU0F
- Senzor částic prachu a kouře



OLED displej
- IIC I2C OLED displej 1,3" - Bílý, 128 x 64

# Schéma zapojení

<div align="center">
<img width="400" height="535" alt="image" src="https://github.com/user-attachments/assets/754fa839-44c8-4cb4-887a-250628d83489" />
</div>

<div align="center">
<img width="400" height="622" alt="image" src="https://github.com/user-attachments/assets/97b443f3-bff2-46ef-b072-c82cc8e6e825" />
</div>

<div align="center">
<img width="400" height="598" alt="image" src="https://github.com/user-attachments/assets/0d18a866-019d-4f36-9a21-ac04f78ff7a2" />
</div>


# Popis programu


# Demontrační video


# Demonstrační poster
