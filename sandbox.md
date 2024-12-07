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

Tomuto přístupu, kdy hlavní program pořád dokola kontroluje, zda se nastavil nějaký bit se říká *polling*. Nevýhoda je, že procesor tráví svůj čas jen kontrolou bitu a nemůže dělat nic jiného. Aby 

## Přerušení
Přerušení je mechanismus mikroprocesoru, který mu umožňuje okamžitě reagovat na nějakou událost. Například na stisk tlačítka, přijetí dat na sériovém portu, přetečení časovače a mnohá další.

Například pokud chceme 

![image](https://github.com/user-attachments/assets/bba2d83e-c752-4c72-a31f-fc065e720727)







![image](https://github.com/user-attachments/assets/d318174c-cbe7-4fe9-9a21-7af3dff00903)


```C
#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned char cislice[]={0xc0,0xf9,0xA4,0xb0,0x99,0x92,0x82,0xd8,0x80,0x90,0x88,0x83,0xc6,0xA1,0x86,0x8e};

unsigned char pozice[3] = {0b11011111,0b11101111,0b11110111}; //Pole s hodnotami pro port D, které zapnou anodu dané pozice
unsigned char zobraz[3] = {1,5,8}; // Pole s čísly, která chceme zobrazovat

volatile int aktual_poz = 0; // Proměnná s číslem aktuálně zobrazované pozice. Protože do ní zapisujeme během přerušení, musíme použít typ *volatile*

ISR(TIMER1_COMPA_vect) // Rutina pro obsluhu přerušení - speciální funkce, která se vykoná při přerušení
{
	PORTD = pozice[aktual_poz]; // Zápisem do portu D aktivujeme aktuální pozici displeje
	PORTB = cislice[zobraz[aktual_poz]];	// Zapíšeme na displej aktuální prvek z pole
	aktual_poz++;	// Zvýšíme aktuální pozici. Pokud je vyšší než 2, nastavíme ji do nuly
	if (aktual_poz>2){
		aktual_poz = 0;
	}	
}

int main(void)
{
	// Nastavení vstupů/výstupů
	DDRB = 0xff; // Nastavíme port B, jako výstup (je připojen k segmentům displeje)
	DDRD = 0xff; // Nastavíme port D, jako výstup (je připojen k anodám, řídí, která číslice je aktivní)

	TCCR1B = 0b0001010; //Zvolíme CTC režim a požadovanou předděličku
	OCR1A=2500;	// Zápisem do komaračního registru určíme frekvenci přetečení ćítače
	TIMSK1=0x02; // Povolíme přerušení od časovače 1
	sei(); // Povolíme přerušení

	// Nekonečná smyčka
	while(1)
	{
	}

}
```








<script type="text/javascript" id="MathJax-script" async
  src="https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-svg.js">https://github.com/TomasChovanec/MIT/blob/main/sandbox.md
</script>

$$ \Large Ftimer = CPU Frequency / Prescalar $$

$$\Large Ftimer = 16MHz/1024 = 15.625KHz $$

$$ \Large Ttick = 1/ 15.625K = 64 \mu seconds$$

$$Ttotal = 64\mu s X 255 = 16ms$$


$$Ftimer = CPU Frequency/Prescalar $$ $$Ftimer = 16MHz/1024 = 15.625KHz $$

$$Ttick = 1/ 15.625K = 64 \mu seconds$$ $$Ttotal = 64\mu s X 65536 = 4 seconds$$

So that is 4 secs! We just need 100 msec so, $$100ms/64\mu s = 1562 = 0x061A$$

$$ \Large Ftimer = CPU Frequency / Prescalar $$

$$
\Large t_{\text{tick}} = \frac{Frequency}{Prescaler} = \frac{16e6}{64} \, \mu\text{s}
$$

$$
\Large t_{\text{tick}} = \frac{64}{16 \times 10^6} = 4 \, \mu\text{s}
$$

$$
\Large t_{\text{tick}} = \frac{N_{\text{prescaler}}}{f_{\text{clk}}}
$$
