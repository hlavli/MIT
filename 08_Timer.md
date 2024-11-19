# Timer

Timer, česky časovač je v mikroprocesorové technice důležitá periferie. Použijeme ho například při generování přesného časového signálu, PWM, měření času, ale i počítání vnějších událostí (např. počtu impulzů z nějakého čidla). Je integrován uvnitř pouzdra mikroprocesoru, ale funguje samostatně, to znamená že po prvotním nastavení počítá sám, i když jádro procesoru dělá něco jiného. Tím pádem je časování přesné a navíc jádro procesoru může dělat něco jiného, nemusí být "zabržděno" v čekacích smyčkách (např. funkce _delay_ms()) .

## Důležité registry

TODO přidat prescaler a hodiny
![image](https://github.com/user-attachments/assets/e0050a5c-eaf3-42a2-aa40-e599c1ef03e0)

TODO - control registr - nastavení prscaleru a módu (Normal/CTC)., Note.: je tu i druhý nastavovací registr, ten v této lekci neppotřebujem
![image](https://github.com/user-attachments/assets/f3b9f741-abce-4b6b-bf90-b0c40e429165)

TODO - různé možnosti prescaleru (bez něj je to 16MHz -> moc rychlé)

![image](https://github.com/user-attachments/assets/c8ab9daf-110e-46c4-9ba4-a1f7df43ef43)



TODO - flagy přetečení - když čítač dojde nakonec, nastaví se do 1
![image](https://github.com/user-attachments/assets/d9c9c9f0-933f-4f83-bc20-c1f9b1b2ffbf)


## Časovač Timer1 v režimu Normal

Timer1 je 16bitový, tzn max 0-65535

TODO zkusíme bliknout ledkou pokaždé, když čítač dojde do konce

```C
#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

int main(void)
{
    DDRF=0xFF;

	TCCR1A = 0x00; // Normal mode
	TCCR1B |= 0b00000101; // Prescaler /1024

	while(1)
	{
	while((TIFR1 & (1<<OCF1A)) == 0); // Dokud není nastaven bit přetečení časovače, nedělej nic
	
	TIFR1|=(1<<OCF1A); // Vynulování příznakového bitu
	
	PORTF ^= 0xff; // Negace LEDek
	}
}

```

## Změna frekvence časovače pomocí přednastavení časovače (preload)

TODO - pokud chceme změnit frekvenci časovače, můžeme ho zkrátit tím, že nebude začínat od nuly, ale od vyšší hodnoty

![image](https://github.com/user-attachments/assets/065ff747-06ff-49ed-b3b2-4533922b9b37)

Hodnotu pro přednsastavení registru TCNT1 spočítáme podle vzorce:
![image](https://github.com/user-attachments/assets/bdaa10f3-8dca-4608-b075-b84bdd6b398c)

TODO Pokaždé, když timer přeteče, nastavíme do něj opět vypočítanou hodnotu.

## Časovač Timer1 v režimu CTC
Režim CTC (Clear timer on Compare Match) nám umožní dosáhnout stejného efektu jako režim Normal s přednastavením. Ovšem 

![image](https://github.com/user-attachments/assets/8d2910e8-3add-4462-b892-426b771df6f6)

Hodnotu pro nastavení registru OCR1 spočítáme podle vzorce:
![image](https://github.com/user-attachments/assets/fa05b1f2-aba1-4796-b380-07afbf4027fd)


## Úkoly

1. Spočítej v Normal režimu co přednastavit do TCNT aby došlo k přetečení každou 1s
2. Spočítej v CTC režimu co přednastavit do TCNT aby došlo k přetečení každou 1s


### [Zpět na obsah](README.md)
