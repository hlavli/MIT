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
