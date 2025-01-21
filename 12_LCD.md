# LCD displej

V této lekci si ukážeme, jak zobrazovat data na LCD displeji, který máme na výukovém přípravku. Konkrétně je to typ displeje HD44780. Abychom si práci s ním zjednodušili, využijeme hotovou knihovnu, kterou do našeho projektu vložíme.

1. Stáhněte si následující dva soubory:
[lcd.c](files/lcd.c) a [lcd.h](files/lcd.h)

2. Přidejte soubory do projektu
   
![image](https://github.com/user-attachments/assets/b5e0a928-6633-4ed3-82a1-6454d2d3117a)

3. Přidejte include knihovny lcd a knihovny stdio do main.c souboru
```c
#include "lcd.h"
#include <stdio.h>
```

## Přidání podpory desetinných čísel

Protože AVR mikrokontrolery mají relativně málo paměti a podpora desetinných čísel je relativně náročná, defaultně překladač do programu podporu desetinných čísel u funkce sprintf() nepřidává. Pokud však chcete desetinná čísla na displeji používat, lze ji povolit (za cenu zvětšení výsledného kódu a tím i zpomalení flashování).

*Project -> Properties -> Toolchain -> Libraries* a zde přidat ```libprintf_flt.a```

![image](https://github.com/user-attachments/assets/c45b611f-f7ac-4bb2-8f03-4c535b61194f)

*Project -> Properties -> Toolchain -> AVR/GNU Linker -> General* a zaškrtnout *Use vprintf library(WI,-u,vprintf)*

![image](https://github.com/user-attachments/assets/055a77a5-5b6e-4db0-a893-6c867007efb9)






## Příklady použití funkcí knihovny lcd.c

```lcd_init(LCD_DISP_ON);```  Inicializace displeje, zapne displej bez kurzoru. Jiné módy jsou např. LCD_DISP_OFF, LCD_DISP_ON_CURSOR, LCD_DISP_ON_CURSOR_BLINK.

```lcd_home();``` Přesune kursor displeje na začátek (první znak, první řádek)

```lcd_clrscr();``` Smaže celý displej a nastaví kurzor na (0, 0).

```lcd_gotoxy(0,1);``` Přesune kursor displeje na danou pozici (x- znak, y- řádek)

```lcd_puts(„Mam rad MIT!“);``` Zobrazí na displeji řetězec znaků

```lcd_command(LCD_SHIFT_LEFT);``` Posune text doleva


## ASCII kód, zobrazení hodnoty proměnné

Už umíme pomocí fuknce *lcd_puts* zobrazit konstantní textový řetězec. Ale co když chceme zobrazit např. hodnotu číselné proměnné?

Na displeji se data zobrazují pomocí ASCII kódů.

![image](https://github.com/user-attachments/assets/ebd7fdb8-ab3d-473b-8a44-4fda306c2422)

*Zdroj obrázku: https://www.sciencebuddies.org/cdn/references/ascii-table.png*

Například textový řetězec ```Ahoj 123``` převedeme do ASCII jako ```0x41 0x68 0x6F 0x6A 0x20 0x31 0x32 0x33```.

Pokud tedy chceme na displeji "vytisknout" hodnotu celočíselné proměnné, musíme každou její číslici převést na ASCII znak. S tím nám pomůže fuknce *sprintf*:

```c
char lcd_buffer[32];
int cislo = 156;
sprintf(lcd_buffer,"%d", cislo);
lcd_puts(lcd_buffer);
```

To ```%d```je tzv. formátovací parametr, který funkci říká, aby číslo "vytiskla" jako dekadické celé číslo. Další formátovací parametry mohou být třeba ```%X``` pro číslo zapsané v hexadecimální soustavě nebo ```%.2f``` pro desetinné číslo.


## Úkoly
1. Zobrazte na displeji na jednom řádku své jméno, na druhém příjmení
2. Zobrazte na displeji odpočet od 10 do 0 po 500ms.
3. Zobrazte na displeji číslo klávesy stisknuté na klávesnici.


### [Zpět na obsah](README.md)
