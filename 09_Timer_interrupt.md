# Časovač s přerušením

V minulém cvičení jsme se naučili nastavit časovač v mikroprocesoru tak, aby přetekl například jednou za 100ms. Příznakový bit jsme v hlavním programu neustále sledovali. Když pak časovač přetekl a příznakový bit se nastavil do jedničky, náš program na to zareagoval, např. bliknul LEDkou.

```c
#include <avr/io.h>

int main(void)
{
	DDRF = 0xff; // PORTF nastavíme jako výstupní (LEDky)

	TCCR1B = 0b0000011; // Prescaler 64, Normal mode

	while(1)
	{
		while((TIFR1 & (1<<TOV1)) == 0); // Dokud není nastaven bit přetečení časovače, nedělej nic
		
		TIFR1 |= (1<<TOV1); // Vynulování příznakového bitu
		
		PORTF ^= 0xff; // Negace LEDek
	}
}
```

Tomuto přístupu, kdy hlavní program pořád dokola kontroluje, zda se nastavil nějaký bit se říká *polling*. Nevýhoda je, že procesor tráví svůj čas jen neustálým kontrolováním příznakového bitu a nedělá nic jiného. Lepší by bylo, kdyby procesor vykonával program a jen v okamžiku, kdy časovač přeteče by se automaticky zastavil, bliknul LEDkou a pak pokračoval v hlavním programu. Takováto funke v mikroprocesorech skutečně je a říkáme jí "přerušení".

## Přerušení
Přerušení (interrupt) je mechanismus mikroprocesoru, který mu umožňuje okamžitě reagovat na nějakou událost. Například na stisk tlačítka, přijetí dat na sériovém portu, přetečení časovače a mnohá další.

```C
ISR(TIMER1_COMPA_vect) // *ISR* znamená, že tato funkce je obsluha přerušení (interrupt routine). *TIMER1_COMPA_vect* znamená, že tato funkce se vykoná při přerušení od Timeru1 při detekci shody s komparačním registrem
{
// Zde bude kód, který se vykoná při přerušení
}
```

V tabulce níže je pro názornost několik vybraných zdrojů přerušení a názvy jejich vektorů. Seznam všech vektorů přerušení můžete najít v datasheetu mikroprocesoru.

Zde je několik příkladů zdrojů přerušení a jejich 
| Interrupt Definition                 | Vector Name          |
|:------------------------------------:|:--------------------:|
| External Interrupt Request 0         | INT0_vect            |
| Pin Change Interrupt Request 0       | PCINT0_vect          |
| Timer/Counter1 Capture Event         | TIMER1_CAPT_vect     |
| Timer/Counter1 Compare Match A       | TIMER1_COMPA_vect    |
| Timer/Counter1 Compare Match B       | TIMER1_COMPB_vect    |
| Timer/Counter1 Overflow              | TIMER1_OVF_vect      |
| SPI Serial Transfer Complete         | SPI_STC_vect         |
| USART Rx Complete                    | USART_RX_vect        |
| USART Data Register Empty            | USART_UDRE_vect      |
| USART Tx Complete                    | USART_TX_vect        |
| ADC Conversion Complete              | ADC_vect             |


|Pořadí bitu| 7    | 6    | 5    | 4    | 3    | 2    | 1    | 0    | 
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:| 
|**Název**|  **PORTF7** | **PORTF6** | **PORTF5** |  **PORTF4** | **PORTF3** | **PORTF2** | **PORTF1** | **PORTF0** | 
|**Hodnota**| **0**    | **0**    | **0**   | **1**   | **1**    | **1**   |  **0**   |  **1**   | 
|**LEDky**|🟡    | 🟡    | 🟡    | ⚪    | ⚪    | ⚪    | 🟡    | ⚪    | 

Například pokud chceme 

<img src="https://github.com/user-attachments/assets/143db4f3-b39f-427e-9634-3a00c36686ef" width="600"/>

![image](https://github.com/user-attachments/assets/d318174c-cbe7-4fe9-9a21-7af3dff00903)


```C
#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned char cislice[]={0xc0, 0xf9, 0xA4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x90, 0x88, 0x83, 0xc6, 0xA1, 0x86, 0x8e};

unsigned char pozice[3] = {0b11011111, 0b11101111, 0b11110111}; //Pole s hodnotami pro port D, které zapnou anodu dané pozice
unsigned char zobraz[3] = {1,5,0}; // Pole s čísly, která chceme zobrazovat

volatile int aktual_poz = 0; // Proměnná s číslem aktuálně zobrazované pozice. Protože do ní zapisujeme během přerušení, musíme použít typ *volatile*


ISR(TIMER1_COMPA_vect) // Rutina pro obsluhu přerušení - speciální funkce, která se vykoná při přerušení
{
// Zde doplňte kód, který při každém vyvolání přerušení zobrazí jednu číslici
}


int main(void)
{
	// Nastavení vstupů/výstupů
	DDRB = 0xff; // Nastavíme port B, jako výstup (je připojen k segmentům displeje)
	DDRD = 0xff; // Nastavíme port D, jako výstup (je připojen k anodám, řídí, která číslice je aktivní)

	TCCR1B = ???; //Zvolíme CTC režim a požadovanou předděličku
	OCR1A=???;	// Zápisem do komaračního registru určíme frekvenci přetečení ćítače
	TIMSK1=0x02; // Povolíme přerušení od časovače 1
	sei(); // Povolíme přerušení
	
	// Nekonečná smyčka
	while(1)
	{
	}

}
```

## Úkoly:
1. Doplňte kód výše tak, aby s periodou 1ms zobrazoval postupně tři číslice z pole *zobraz* na třech pozicích 7seg displeje
2. Doplňte kód tak, aby se **nejnižší číslice** zobrazovaného čísla každých 100ms zvýšila o jedničku (158 -> 159 -> 150 ->151 -> ...) 
3. Doplňte kód tak, aby se zobrazované trojciferné číslo každých 100ms zvětšilo o jedničku (tedy displej bude zobrazovat čísla 150 -> 151 ->...-> 159 -> 160, ...)

