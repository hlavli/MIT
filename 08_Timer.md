# Timer

Timer, česky časovač je v mikroprocesorové technice důležitá periferie. Použijeme ho například při generování přesného časového signálu, PWM, měření času, ale i počítání vnějších událostí (např. počtu impulzů z nějakého čidla). Je integrován uvnitř pouzdra mikroprocesoru, ale funguje samostatně, to znamená že neustále počítá, i když jádro procesoru dělá něco jiného. Tím pádem je časování přesné a navíc jádro procesoru může dělat něco jiného, nemusí být "zabržděno" v čekacích smyčkách (např. funkce _delay_ms()) .

![image](https://github.com/user-attachments/assets/c8ab9daf-110e-46c4-9ba4-a1f7df43ef43)

![image](https://github.com/user-attachments/assets/5f4f9e58-a38f-4570-8df4-f526c06c624f)


## Časovač Timer1 v režimu Normal

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
	
	TIFR1|=(1<<OCF0A); // Vynulování příznakového bitu
	
	PORTF ^= 0xff; // Negace LEDek
	}
}

```

## Změna frekvence časovače pomocí přednastavení časovače (preload)

![image](https://github.com/user-attachments/assets/ece3c971-7831-4b28-8da7-70ffc9aad4ec)


## Časovač Timer1 v režimu CTC
Režim CTC (Clear timer on Compare Match) nám umožní dosáhnout stejného efektu jako režim Normal s přednastavením. Ovšem 

![image](https://github.com/user-attachments/assets/fa05b1f2-aba1-4796-b380-07afbf4027fd)

## Úkoly

1. 
2. 




### [Zpět na obsah](README.md)
