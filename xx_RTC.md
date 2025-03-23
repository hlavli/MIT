# RTC - real time clock

- co to je, jak funguje, baterie
- [Datasheet DS1307](https://www.analog.com/media/en/technical-documentation/data-sheets/ds1307.pdf), adresy jednotlivých číslic času, RAM

  ![image](https://github.com/user-attachments/assets/2f3c9eff-5ce0-4b2c-924a-f4c49438c906)
  
    ![image](https://github.com/user-attachments/assets/0fc05e64-ce7f-473a-a149-af28a7b3443b)

- I2C komunikace - základy, adresa, master/slave
  
    ![image](https://github.com/user-attachments/assets/abc6c42b-abeb-4a6f-a850-ca47433e5dd9)
  
  *Zdroj obrázku: https://www.hibit.dev/posts/102/communication-protocols-uart-i2c-and-spi*

- Přidání knihoven I2C, DS1307.  Stáhněte si následující soubory (přes pravé tlačítko a *Uložit odkaz jako*): [i2c.c](files/i2c.c),  [i2c.h](files/i2c.h), [DS1307.c](files/DS1307.c), [DS1307.h](files/DS1307.h).
- Zobrazit čas na LCD
- Zobrazit I2C čtení sekund na logickém analyzeru
