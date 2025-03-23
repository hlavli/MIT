# RTC - Real time clock

RTC modul (Real-Time Clock), je specializovaný integrovaný obvod, který uchovává přesný čas a datum i při výpadku napájení díky zabudované záložní baterii.
S mikroprocesorem komunikuje přes I2C sběrnici. Záložní baterie (malá knoflíková, v našem případě CR1225) zajišťuje chod i bez hlavního napájení. V našem přípravku máme osazen RTC modul DS1307 [(datasheet zde).](https://www.analog.com/media/en/technical-documentation/data-sheets/ds1307.pdf)

![image](https://github.com/user-attachments/assets/2f3c9eff-5ce0-4b2c-924a-f4c49438c906)

    ![image](https://github.com/user-attachments/assets/0fc05e64-ce7f-473a-a149-af28a7b3443b)

- I2C komunikace - základy, adresa, master/slave
  
    ![image](https://github.com/user-attachments/assets/abc6c42b-abeb-4a6f-a850-ca47433e5dd9)
 
  *Zdroj obrázku: https://www.hibit.dev/posts/102/communication-protocols-uart-i2c-and-spi*

  ![image](https://github.com/user-attachments/assets/8d93955c-0cee-41fa-94fe-6d2272da27a4)

- Přidání knihoven I2C, DS1307.  Stáhněte si následující soubory (přes pravé tlačítko a *Uložit odkaz jako*): [i2c.c](files/i2c.c),  [i2c.h](files/i2c.h), [DS1307.c](files/DS1307.c), [DS1307.h](files/DS1307.h).
- Zobrazit čas na LCD
- Zobrazit I2C čtení sekund na logickém analyzeru
