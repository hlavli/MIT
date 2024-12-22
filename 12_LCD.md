# LCD displej

V této lekci si ukážeme, jak zobrazovat data na LCD displeji, který máme na výukovém přípravku. Abychom si práci s ním zjednodušili, využijeme hotovou knihovnu, pro práci s displjeme, kterou do našeho projektu vložíme.

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

*Project -> Properties -> Toolchain -> Libraries * a zde přidat ```libprintf_flt.a```

![image](https://github.com/user-attachments/assets/c45b611f-f7ac-4bb2-8f03-4c535b61194f)

*Project -> Properties -> Toolchain -> AVR/GNU Linker -> General* a zaškrtnout *Use vprintf library(WI,-u,vprintf)*

![image](https://github.com/user-attachments/assets/055a77a5-5b6e-4db0-a893-6c867007efb9)






## Funkce knihovny lcd.c

lcd_home();

sprintf(lcd_buffer,"Uin=%5.3f V",uvstupni);

lcd_gotoxy(0,1);

lcd_puts(lcd_buffer);

lcd_puts(„Posunute“);

lcd_clrscr();

## ASCII kód
Na displeji se data zobrazují pomocí ASCII kódů.

![image](https://github.com/user-attachments/assets/ebd7fdb8-ab3d-473b-8a44-4fda306c2422)

*Zdroj obrázku: https://www.sciencebuddies.org/cdn/references/ascii-table.png*
