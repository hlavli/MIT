# RTC - Real time clock

RTC modul (Real-Time Clock), je specializovaný integrovaný obvod, který uchovává přesný čas a datum i při výpadku napájení díky zabudované záložní baterii.
S mikroprocesorem komunikuje přes I2C sběrnici. Záložní baterie (malá knoflíková, v našem případě CR1225) zajišťuje chod i bez hlavního napájení. V našem přípravku máme osazen RTC modul DS1307 [(datasheet zde).](https://www.analog.com/media/en/technical-documentation/data-sheets/ds1307.pdf)

![image](https://github.com/user-attachments/assets/cce6d9e5-ccb2-46b5-b323-d633d9c3074b)

## I2C komunikace - základy, adresa, master/slave
I²C (Inter-Integrated Circuit) je sériová sběrnice pro komunikaci mezi mikrokontroléry a periferiemi. Používá dva signální vodiče:
SDA (Serial Data) – přenos dat
SCL (Serial Clock) – hodinový signál

Komunikace probíhá v režimu master-slave, kde master řídí přenos. Každé zařízení má unikátní adresu a lze připojit více zařízení na stejné dvě linky. Hezký článek o I2C komunikaci [zde](http://www.elektromys.eu/clanky/ele_i2c/clanek.html).

![image](https://github.com/user-attachments/assets/abc6c42b-abeb-4a6f-a850-ca47433e5dd9)
 
*Zdroj obrázku: https://www.hibit.dev/posts/102/communication-protocols-uart-i2c-and-spi*

![image](https://github.com/user-attachments/assets/8d93955c-0cee-41fa-94fe-6d2272da27a4)


## Registry DS1307
Pomocí I2C sběrnice můžeme vyčítat nebo zapisovat obsah registrů DS1307. V datasheetu najdeme rozložení jednotlivých časových údajů:

![image](https://github.com/user-attachments/assets/0fc05e64-ce7f-473a-a149-af28a7b3443b)


## RAM paměť v DS1307
RTC čip DS1307 obsahuje kromě obvodu reálného času i 56 bajtů RAM paměti. Ta je sice napěťově závislá (narozdíl od paměti EEPROM) a bez napájení se data ztratí, ale tím, že má modul vlastní baterii, data zůstanou zachována i když odpojíme napájecí adaptér přípravku. Paměť lze libovolně číst a zapisovat přes I²C sběrnici. Využít ji můžeme například k ukládání uživatelských dat a parametrů, které by měly zůstat zachovány i po vypnutí napájení. Adresa RAM v DS1307 začíná od 0x08 a končí na 0x3F.


## Knihovny pro I2C a DS1307
Pro usnadnění práce můžeme použít hotové knihovny pro I2C a  RTC obvod DS1307. Knihovny přidáte stejně jako knihovnu pro LCD. Projděte si zejména soubor [DS1307.h](files/DS1307.h) kde najdete deklarace funkcí, které knihovna obsahuje.

Stáhněte si následující soubory (přes pravé tlačítko a *Uložit odkaz jako*): [i2c.c](files/i2c.c),  [i2c.h](files/i2c.h), [DS1307.c](files/DS1307.c), [DS1307.h](files/DS1307.h).


## Úkoly
1. Zobrazte na LCD displeji čas a datum. Funkce pro získání času najdete v souboru [DS1307.h](files/DS1307.h) .
2. Pokud není na RTC přesný čas, nastavte jej funkcemi ```DS1307_set_xx()```.
3. Napište program, který čte z RTC jen sekundy. Změřte I2C komunikaci pomocí logického analyzeru (signál SDA je na pinu PD.0, SCL je na pinu PD.1). Zkuste v sw logického analyzeru nastavit dekódování I2C sběrnice a rozlišit v datech informaci o sekundách.
4. Na displeji zobrazujte počet stisknutí tlačítka. Po odpojení a opětovném připojení napájení by se tento počet neměl vynulovat, ale pokračovat od poslední zaznamenané hodnoty. Pro ukládání počtu stisků použijte RAM v modulu DS1307 a při startu programu hodnotu načtěte zpět.

### [Zpět na obsah](README.md)
