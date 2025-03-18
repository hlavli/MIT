# Maticový displej

![image](https://github.com/user-attachments/assets/28cc79c2-ec6c-4f9e-b6d0-0fe4740bd020)

## Princip funkce

Jedním portem nastavíme data na řádku, druhým portem vybereme řádek.

![image](https://github.com/user-attachments/assets/5215499b-795d-44b5-a037-b70ced5ad1eb)

*Zdroj obrázku: https://randomnerdtutorials.com/guide-for-8x8-dot-matrix-max7219-with-arduino-pong-game/*



## Zapojení v přípravku
Když se podíváme na maticový displej ve schématu naší výukové desky, vypdá to takto:

Piny **R0** až **R7** znamenají **R**ow 0-7 

Piny **AR0** až **AR7** znamenají **A**node **R**ed 0-7

Piny **AG0** až **AG7** znamenají **A**node **G**reen 0-7

Vidíme, že každý bod displeje je tvořen dvěma LEDkami - červenou a zelenou. Můžeme tedy rozsvítit jednu z nich, žádnou nebo obě.

![image](https://github.com/user-attachments/assets/d012b838-8fce-415b-8ce0-09f92d8b69c3)




## Úkoly:
1. Vymyslete si vlastní obrázek 8x8 pixelů (smajlík, srdce, kočka,...) a sestavte si pole s hodnotami pro každý řádek displeje.
2. Zobrazte obrázek na displeji bez použití časovače, pouze s  použitím cyklu for a funkce _delay_ms().
3. Zobrazte obrázek pomocí přerušení časovače - vykreslení se bude vykonávat v obsluze přerušení, hlavní smyčka programu zůstane volná.
4. Nadefinujte si druhý obrázek a v hlavní smyčce provádějte změnu obrázků. Samotné zobrazování ponechte v rutině přerušení časovače.
5. Vytvořte program, který zobrazuje text, písmeno po písmenu. Hodnoty k vykreslení jednotlivých písmen můžete použít ze souboru Font_8x8.h.
6. Napište program tak, aby po stisku klávesy změňil barvu obrázku na displeji z červené na zelenou.
