# Monitorování kvality ovzduší
Tento kompaktní systém postavený na platformě Arduino umožňuje sledovat klíčové parametry kvality ovzduší. Arduino zajišťuje rychlé a spolehlivé zpracování dat ze senzorů a jejich okamžité zobrazení na displeji. Díky tomu máte všechny podstatné informace o stavu vzduchu neustále přehledně k dispozici.

<div align="center">
<img width="400" height="1024" alt="image" src="https://github.com/user-attachments/assets/d136b4e3-11a7-4141-b94c-7681a828e50b" />
</div>

# Členové týmu

- Tomáš Pokorný
- Tomáš Rosa
- Dominik Uherka
- Daniel Valčík

# Návrh a popis projektu
V tomto projektu se věnujeme návrhem a realizací měření různých veličin souvisejících s kvalitou ovzduší. Cílem projektu je pomocí senzorů přijímat data, které jsou zpracovány a zobrazovány na displeji. Díky tomu může uživatel získat základní parametry okolního ovzduší. Data získáváme pomocí čtyř senzorů, které monitorují teplotu a relativní vlhkost, koncentraci plynů a množství prachových částic. Následně mikrokontrolér ATmega328, který slouží jako centrální jednotka zajišťující komunikaci se senzory data zpracová a zobrazuje na OLED displeji.


<div align="center">
<img width="400" height="523" alt="image" src="https://github.com/user-attachments/assets/ab5eba99-46fc-4661-87fd-8c39425a7338" />
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

DHT12 umožňuje měřit:
- **teplotu** v rozsahu **–20 až +60 °C** s typickou přesností **±0,5 °C**,  
- **relativní vlhkost** v rozsahu **20 až 95 %** s přesností **±3 až ±5 %**.

<div align="center">
<img width="400" height="1080" alt="image" src="https://github.com/user-attachments/assets/0179e0f3-a192-49c1-9566-df1eb6b1592a" />
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
<img width="400" height="535" alt="image" src="https://github.com/user-attachments/assets/754fa839-44c8-4cb4-887a-250628d83489" />
</div>

<div align="center">
<img width="400" height="515" alt="image" src="https://github.com/user-attachments/assets/60b26543-a79d-4fed-ac7f-87b488875818" />
</div>

<div align="center">
<img width="400" height="874" alt="image" src="https://github.com/user-attachments/assets/563b94ab-5330-43ff-936d-617a24f2f7e0" />
</div>



# Popis programu


# Demontrační video


# Demonstrační poster
