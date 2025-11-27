# Monitorování kvality ovzduší
Tento kompaktní systém postavený na platformě Arduino umožňuje sledovat klíčové parametry kvality ovzduší. Arduino zajišťuje rychlé a spolehlivé zpracování dat ze senzorů a jejich okamžité zobrazení na displeji. Díky tomu máte všechny podstatné informace o stavu vzduchu neustále přehledně k dispozici.

<div align="center">
<img width="400" height="622" alt="image" src="https://github.com/user-attachments/assets/3c4fc4d3-3641-472f-807d-b1a9bc6bc7e7" />
</div>

# Členové týmu

- Tomáš Pokorný: GitHub master
- Tomáš Rosa: programátor, GitHub
- Dominik Uherka: video maker, tvorba dokumentace
- Daniel Valčík: hlavní programátor

# Návrh a popis projektu
V tomto projektu se věnujeme návrhem a realizací měření různých veličin souvisejících s kvalitou ovzduší. Cílem projektu je pomocí senzorů přijímat data, které jsou zpracovány a zobrazovány na displeji. Díky tomu může uživatel získat základní parametry okolního ovzduší. Data získáváme pomocí čtyř senzorů, které monitorují teplotu a relativní vlhkost, koncentraci plynů a množství prachových částic. Následně mikrokontrolér ATmega328, který slouží jako centrální jednotka zajišťující komunikaci se senzory data zpracová a zobrazuje na OLED displeji.

<div align="center">
<img width="400" height="3024" alt="image" src="https://github.com/user-attachments/assets/f2a5c6f7-567f-46bb-8e47-0a5b9fbad628" />
</div>

# Popis komponent
### Senzor MQ-135
Senzor **MQ-135** slouží k orientačnímu měření kvality ovzduší. Jeho aktivní vrstvu tvoří **oxid cíničitý (SnO₂)**, jehož vodivost se mění v přítomnosti různých plynů a výparů.

Senzor **nereaguje na jeden konkrétní plyn**, ale na **celou směs látek**, zejména:
- amoniak (NH₃),
- oxidy dusíku,
- organické výpary (VOC),
- výpary z čisticích prostředků a parfémů,
- kouř,
- výfukové a domácí plyny,
- butan/propán (např. ze zapalovače).

V projektu slouží MQ-135 jako **indikátor znečištění vzduchu**, nikoliv jako přesný měřicí přístroj. Jeho výstup je analogový, proto jej mikrokontrolér zpracovává pomocí analogově-digitálního převodníku.

**Typické orientační hodnoty:**
- 0 → běžný „čistý“ vnitřní vzduch
- 200–300 → vaření, čističe, parfém, zhoršená kvalita vzduchu
- 500+ → silné výpary, kouř nebo přítomnost plynu

<div align="center">
<img width="400" height="510" alt="Senzor MQ-135" src="https://github.com/user-attachments/assets/5b4b8167-b24f-428c-abb8-88ab65c619fb" />
</div>

### Senzor DHT12
Senzor **DHT12** je digitální snímač teploty a vlhkosti, který komunikuje s mikrokontrolérem prostřednictvím sběrnice **I²C**.
Pro měření vlhkosti využívá senzor kapacitní polymerový prvek a pro měření teploty obsahuje integrované teplotní čidlo. Data o aktuální teplotě a vlhkosti jsou poskytována v digitální podobě bez potřeby dodatečné kalibrace.

**DHT12 umožňuje měřit:**
- **teplotu** v rozsahu **–20 až +60 °C** s typickou přesností **±0,5 °C**,  
- **relativní vlhkost** v rozsahu **20 až 95 %** s přesností **±3 až ±5 %**.

<div align="center">
<img width="400" height="352" alt="image" src="https://github.com/user-attachments/assets/9888b0fa-84c1-4e4d-9c67-af3ffe63f7aa" />
</div>

### Optický senzor ovzduší GP2Y1010AU0F
Optický senzor GP2Y1010AU0F je určený k detekci prachových částic ve vzduchu a pracuje na principu rozptylu světla. Uvnitř senzoru se nachází infračervená LED dioda, která vysílá světelný paprsek do měřicí komory. Pokud vzduchem prochází prachová částice, světlo se na ní rozptyluje a jeho část dopadá na fototranzistor. Ten následně generuje elektrický signál úměrný množství rozptýleného světla, přičemž tento signál je dále zesílen integrovaným zesilovačem. V zapojení se používá rezistor, který omezuje proud tekoucí LED diodou a zajišťuje stabilní intenzitu světelného pulzu. Kondenzátor v obvodu slouží k filtraci napájecího napětí, protože senzor je citlivý na šum a jakékoli kolísání napětí by mohlo způsobit nestabilitu nebo nepřesnost měření. Kondenzátor tedy snižuje rušení a přispívá k celkové stabilitě senzoru.


<div align="center">
<img width="400" height="510" alt="image" src="https://github.com/user-attachments/assets/4d161eb7-4fa0-4e3c-b817-3c8c11bbb309" />
</div>

### OLED displej
OLED displej o úhlopříčce 0,96 palce a rozlišení 128 × 64 pixelů představuje energeticky úsporné grafické zobrazovací zařízení vhodné pro tento projekt. Technologie OLED nabízí vysoký kontrast a dobrou čitelnost i při nízké spotřebě energie. Displej je řízen pomocí integrovaného řadiče, který zpracovává data a příkazy přicházející z mikrokontroléru. Komunikace probíhá přes sériové rozhraní I2C, což minimalizuje počet potřebných vodičů a zjednodušuje celkové zapojení. Na displeji se zobrazují všechny naměřené hodnoty jednotlivých senzorů, přičemž uživatel tak získává okamžitý přehled o aktuální kvalitě ovzduší.

<div align="center">
<img width="400" height="510" alt="image" src="https://github.com/user-attachments/assets/4a3a1e4a-426f-4813-9ed6-d736cfc0499c" />
</div>

# Schéma zapojení

<div align="center">
<img width="400" height="432" alt="image" src="https://github.com/user-attachments/assets/48621347-774c-4f7d-8f23-c30ff1c9e113" />
</div>

<div align="center">
<img width="400" height="645" alt="image" src="https://github.com/user-attachments/assets/07d37035-9cf0-41bf-9220-278c728942ec" />
</div>


# Popis programu
Program pravidelně měří teplotu, vlhkost, prašnost a koncentraci plynů pomocí senzorů DHT12, GP2Y1010 a MQ135. Po spuštění inicializuje všechny periférie, senzory, I2C komunikaci a OLED displej. Časovač TIMER1 vytváří přerušení, které nastavuje proměnnou flag_update, podle níž hlavní smyčka pozná, kdy má provést nové měření. Po každé aktualizaci program načte hodnoty senzorů, provede základní výpočty a převede je na použitelné jednotky. Následně výstupy zobrazí na OLED displeji v předem připraveném rozložení. Program tak cyklicky obnovuje data a poskytuje aktuální přehled o kvalitě okolního prostředí.

<div align="center">
<img width="420" height="747" alt="image" src="https://github.com/user-attachments/assets/8cfadb3d-341a-4a82-8841-df81a7a5a56c" />
</div>

# Demontrační video



https://github.com/user-attachments/assets/224a8f2f-f5b7-4f19-9710-5e3e66e5539a



# Demonstrační poster

# Zdroje
- GP2Y1010: https://dratek.cz/arduino-platforma/1126-opticky-senzor-kvality-ovzdusi-gp2y1010au0f.html?gad_source=1&gad_campaignid=17190055571&gbraid=0AAAAACVG_WdMdsI9GgEBoBiqihpy8xbHf&gclid=Cj0KCQiAiqDJBhCXARIsABk2kSmGebZPVCR5Vj_lhDj5BpFCFtRr2RC84YoECgKVjbpFDe2vHHXAIBkaAld2EALw_wcB
- MQ-135: https://dratek.cz/arduino-platforma/1298-senzor-plynu-mq135-mq-135-pro-arduino.html?gad_source=1&gad_campaignid=17190055571&gbraid=0AAAAACVG_WdMdsI9GgEBoBiqihpy8xbHf&gclid=Cj0KCQiAiqDJBhCXARIsABk2kSkOikeE0O3fDJ5GAutL6nGdgl48FiQheFX2JKIcwGJU9-1FHGK4amEaApDZEALw_wcB
- DHT-12: https://dratek.cz/ukonceno/1977-i2c-teplomer-a-vlhkomer-dht12-digitalni.html
- inspirováno kódem ze cvičení GITHUB: https://github.com/tomas-fryza/avr-labs
- Generování dokumentace Doxygen: https://www.doxygen.nl/
- simulační nástroj: https://wokwi.com/
- kreslení schémat: https://www.drawio.com/
- tvorba posteru: https://www.canva.com/cs_cz/
- V rámci práce byla využita asistence nástroje OpenAI
