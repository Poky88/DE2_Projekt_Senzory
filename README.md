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
V tomto projektu se věnujeme návrhem a realizací měření různých veličin souvisejících s kvalitou ovzduší. Cílem projektu je pomocí senzorů přijímat data, které jsou zpracovány a zobrazovány na displeji. Díky tomu může uživatel získat základní parametry okolního ovzduší. Data získáváme pomocí čtyř senzorů, které monitorují teplotu a relativní vlhkost, koncentraci CO₂ a množství prachových částic. Následně mikrokontrolér ATmega328, který slouží jako centrální jednotka zajišťující komunikaci se senzory data zpracová a zobrazuje na OLED displeji.


<div align="center">
<img width="400" height="523" alt="image" src="https://github.com/user-attachments/assets/ab5eba99-46fc-4661-87fd-8c39425a7338" />
</div>

# Popis komponent

### Senzor MQ-135
Senzor MQ-135 je určen pro monitorování kvality ovzduší a pracuje na principu změny elektrického odporu v závislosti na přítomnosti různých plynů. Aktivní vrstvu senzoru tvoří oxid cíničitý (SnO₂), jehož vodivost se mění podle koncentrace amoniaku, oxidů dusíku, kouřových složek a zejména oxidu uhličitého. V projektu slouží MQ-135 pro měření koncentrace CO₂. Jeho výstup je analogový, a proto jej mikrokontrolér zpracovává pomocí analogově-digitálního převodníku.

<div align="center">
<img width="400" height="510" alt="Senzor MQ-135" src="https://github.com/user-attachments/assets/5b4b8167-b24f-428c-abb8-88ab65c619fb" />
</div>

### Senzor DHT 11
Senzor DHT11 je digitální snímač teploty a vlhkosti, který obsahuje rezistivní polymerový senzor pro měření vlhkosti a teplotní čidlo typu NTC. Komunikuje s mikrokontrolérem pomocí jednoduchého jednovodičového protokolu, při němž po inicializačním signálu ze strany mikrokontroléru odešle digitální informaci o teplotě a relativní vlhkosti. Umožňuje měřit teploty v rozsahu od 0 do 50 °C s přesností ±1 °C a relativní vlhkost od 20 do 90 % s odchylkou přibližně ±4 %. Senzor je vhodný pro aplikace s pomaleji se měnícími hodnotami prostředí.

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
<img width="400" height="3024" alt="image" src="https://github.com/user-attachments/assets/10b6f3ab-a80f-452a-b0c5-c10a4fce9fb1" />
</div>



# Popis programu


# Demontrační video


# Demonstrační poster
