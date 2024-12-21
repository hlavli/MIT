# Multiplex sedmisegmentového displeje s využitím přerušení

Zkusíme si opět multiplex sedmisegmentového displeje, ale tentokrát k tomu využijeme přerušení. Níže je rozpracovaný (zatím nefunkční) kód pro zobrazování trojciferného čísla na 7segmentovém displeji.

1. Doplňte kód, aby s periodou 1ms zobrazoval postupně tři číslice z pole *zobraz* na třech pozicích 7seg displeje
   - nastavte mód a předděličku časovače
   - spočítejte si hodnotu pro komparační registr, aby se přerušení vyvolalo jednou za milisekundu
   - povolte přerušení od časovače a povolte globální přerušení
   - nadefinujte funkci pro obsluhu přerušení, ve které budete řídit displej (viz cvičení s multiplexováním displeje)
2. Doplňte kód, aby se **nejnižší číslice** zobrazovaného čísla každých 100ms zvýšila o jedničku (158 -> 159 -> 150 ->151 -> ...)
3. Doplňte kód, aby se zobrazované trojciferné číslo každých 100ms zvětšilo o jedničku (tedy displej bude zobrazovat čísla 150 -> 151 ->...-> 159 -> 160 -> 161 -> ...)

```C
#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned char cislice[]={0xc0, 0xf9, 0xA4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x90, 0x88, 0x83, 0xc6, 0xA1, 0x86, 0x8e};
unsigned char pozice[3] = { 0b11110111,0b11101111, 0b11011111}; //Pole s hodnotami pro port D, které zapnou anodu dané pozice
unsigned char zobraz[3] = {1, 5, 0}; // Pole s čísly, která chceme zobrazovat

??? //definujeme funkci pro obsluhu přerušení

int main(void)
{
	// Nastavení vstupů/výstupů
	DDRB = 0xff; // Nastavíme port B, jako výstup (je připojen k segmentům displeje)
	DDRD = 0xff; // Nastavíme port D, jako výstup (je připojen k anodám, řídí, která číslice je aktivní)

	TCCR1B = ???; //Zvolíme CTC režim a požadovanou předděličku
	OCR1A = ???;	// Zápisem do komparačního registru určíme frekvenci přetečení čítače

	???? // Povolíme přerušení od časovače 1
	???? // Povolíme přerušení
	
	// Nekonečná smyčka
	while(1)
	{
	}
}
