# Timer

Timer, česky časovač je v mikroprocesorové technice důležitá periferie. Použijeme ho například při generování přesného časového signálu, PWM, měření času, ale i počítání vnějších událostí (např. počtu impulzů z nějakého čidla). Je integrován uvnitř pouzdra mikroprocesoru, ale funguje samostatně, to znamená že neustále počítá, i když jádro procesoru dělá něco jiného. Tím pádem je časování přesné a navíc jádro procesoru může dělat něco jiného, nemusí být "zabržděno" v čekacích smyčkách (např. funkce _delay_ms()) .


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
Todo

<img src="https://github.com/user-attachments/assets/ca64838d-951c-4a38-af5d-1aede0d0d429" width="500"/>

## Časovač Timer1 v režimu CTC
Režim CTC (Clear timer on Compare Match) nám umožní dosáhnout stejného efektu jako režim Normal s přednastavením. Ovšem 

## Úkoly

1. 
2. 




### [Zpět na obsah](README.md)
