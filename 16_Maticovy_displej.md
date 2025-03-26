# Maticový displej
Další z periferií, kterou se naučíme ovládat mikrokontrolerem je maticový displej 8x8. Je tvořen maticí LEDek a dokáže zobrazovat jak text, tak jednoduchou grafiku.

![image](https://github.com/user-attachments/assets/28cc79c2-ec6c-4f9e-b6d0-0fe4740bd020)

## Princip funkce

Maticový displej má 8x8 bodů. Pokud bychom chtěli každý bod řídit jedním pinem, potřebovali bychom jich 64, což je příliš mnoho, některé mikroprocesory ani tolik pinů nemají. Používá se tedy stejná technika, jakou jsme si už ukázali u sedmisegmentového displeje - **časový multiplex**.

Multiplexování u 8x8 maticového displeje funguje tak, že se v jeden okamžik rozsvítí **jen jeden řádek**. Řádky se postupně střídají rychlostí, kterou lidské oko nevnímá — například  **100Hz**.

Zapneme první řádek a rozsvítíme jen ty LEDky, které mají v daném řádku svítit. Pak přepneme na druhý řádek, a tak dál až k osmému.  Po zobrazení všech řádků se proces opakuje znovu a znovu. Čím rychleji cyklus běží, tím plynuleji obraz vypadá. Díky **setrvačnosti lidského oka** se to ale jeví jako by svítily všechny řádky zároveň.

![image](https://github.com/user-attachments/assets/5215499b-795d-44b5-a037-b70ced5ad1eb)

*Zdroj obrázku: https://randomnerdtutorials.com/guide-for-8x8-dot-matrix-max7219-with-arduino-pong-game/*


## Zapojení v přípravku
Když se podíváme na maticový displej ve schématu naší výukové desky, vypadá to takto:

Piny **R0** až **R7** znamenají **R**ow 0-7 

Piny **AR0** až **AR7** znamenají **A**node **R**ed 0-7

Piny **AG0** až **AG7** znamenají **A**node **G**reen 0-7

Vidíme, že každý bod displeje je tvořen dvěma LEDkami - červenou a zelenou. Můžeme tedy rozsvítit jednu z nich, žádnou nebo obě.

Piny R0-R7 pro výběr řádků jsou propojeny pomocí jumperů s portem PORTL. Piny AR0-AR7 popř. AG0-AG7 můžete pomocí plochých kabelů připojit k libovolným volným portům na přípravku (např. PORTA, PORTJ, PORTB,PORTD)

![image](https://github.com/user-attachments/assets/d012b838-8fce-415b-8ce0-09f92d8b69c3)


## Úkoly:
1. Napište program, který zobrazí na maticovém displeji svislou čáru odshora dolů.
2. Vymyslete si vlastní obrázek 8x8 pixelů (smajlík, srdce, kočka,...) a sestavte si pole s hodnotami pro každý řádek displeje.
3. Zobrazte obrázek na displeji bez použití časovače, pouze s  použitím cyklu for a funkce _delay_ms().
4. Zobrazte obrázek pomocí přerušení časovače - vykreslení se bude vykonávat v obsluze přerušení (funkce ```ISR(TIMER1_COMPA_vect){}```) hlavní smyčka programu zůstane volná. Časovač můžete nastavit například takto:
   ```c
   TIMSK1 = 0x02; // Povolení přerušení při shodě čítače s komparačním registrem OCR1A
   sei(); // Globální povolení přerušení
   TCCR1B = 0b0001100; // CTC režim, dělička 256 -> Ttick = 16us
   
   OCR1A = ???; // Dopočítejte počet ticků do přerušení 
   ```
5. Nadefinujte si druhý obrázek a v hlavní smyčce provádějte změnu obrázků. Samotné zobrazování ponechte v rutině přerušení časovače.
6. Vytvořte program, který zobrazuje text, písmeno po písmenu. Hodnoty k vykreslení jednotlivých písmen můžete použít ze souboru [Font_8x8.h](/files/Font_8x8.h).
7. Napište program tak, aby po stisku tlačítka změnil barvu obrázku na displeji z červené na zelenou.

### [Zpět na obsah](README.md)
