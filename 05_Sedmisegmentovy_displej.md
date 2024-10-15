# Sedmisegmentový displej


Sedmisegmentový displej je po LEDkách a tlačítkách další jednoduchá periferie na našem přípravku, se kterou se naučíme pracovat. Je to vcelku primitivní - sedmisegmentový displej není nic jiného, než LEDky ve tvaru podlouhlých segmentů, které jsou rozestaveny tak, aby se z nich dala skládat čísla.

## Princip funkce
Protože je pro každou číslici těchto LEDek osm (sedm segmentů plus desetinná tečka), můžeme je všechny připojit na jeden port mikroprocesoru a potom jedním zapsáním do registru portu, kde jsou LEDky připojeny nastavíme požadovoanou číslici.

![image](https://github.com/user-attachments/assets/4ca40da4-f47b-48d5-8bcc-c5c16d119e3e)


![image](https://github.com/user-attachments/assets/60f7e6fe-8fc7-4d36-a042-779cb9903295)

*Zdroj obrázků: https://www.electronics-tutorials.ws/blog/7-segment-display-tutorial.html* 

### Zobrazení čísla
Například pokud budeme mít displej připojen k portu B a budeme chtít zapsat nulu. Nula vypadá tak, že svítí všechny segmenty, kromě segmentu g a desetinné tečny (DP). Pokud máme displej se společnou anodou, kde plus je trvale připojeno a segment, který chceme rozsvítit, musíme "přizemnit". Tedy do segmentů které chceme rozsvítit zapíášeme nulu, do těch, které mají zůstat zhasnuté pak jedničku.

|Segment| DP    | g    | f    | e    | d    | c    | b    | a    | 
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:| 
|**Bit**|  **1**| **1**| **0**|  **0** | **0** | **0** | **0** | **0** | 

```C
PORTB = 0b11000000; // Zobrazíme na displeji nulu
```

### Zapojení displeje v našem  přípravku
Sedmisegmentové displeje mohou být buď se společnou katodou (všechny katody jsou spojeny a připojeny k zemi, anody jsou vyvedeny pro každý segment zvlášť) nebo naopak se společnou anodou. Pohledem do schématu našeho přípravku zjistíme, že ten náš je se společnou anodou.

![image](https://github.com/user-attachments/assets/d7519c09-32a6-4c2c-b350-a08d664351e7)

Na přípravku máme celkem šest sedmisegmentových číslic. Jak zobrazovat čísla na různých pozicích najednou, si ukážeme až v některém z dalších cvičení. Pro teĎ si vystačíme s jendou pozicí, například tou nejvíc vlevo. Ta je napájena anodou AN6. Pomocí Portu D k ní připojíme napětí, zatímco všechny ostatní necháme vypnuté - nulou otevřeme tranzistor, který jí napájí, jednočkou na všech ostatních pozicíh ostatní anody vypneme. Tranzistory na anodách jsou proto, že pokud by svítilo více segmentů zároveň, celkový proud by přesáhl maximální proud pinu procesoru a ten by se mohl zničit.

```C
PORTD = 0b11011111; // Otevřeme tranzistor, který připojí 5V na anodu AN6 (na přípravku nejvíc vlevo).
```

V našem přípravku není sedmisegmentový displej připojen k procesoru trvale, ale je vyveden na pinovou lištu. Pokud chceme displej používat, musíme ho připojit kablíky viz. obrázek níže.

![image](https://github.com/user-attachments/assets/1320cb6d-6883-4c99-9c53-15064df9df56)

## Příklad programu

```C
#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

unsigned char znaky[]={0x88, 0x83, 0xc6, 0xA1, 0x86, 0x8e}; // pole kombinací segmentů (a, b, c, d, e, f)

int main(void)
{	DDRB=0xff; // Nastaví port B, jako výstup (je připojen k segmentům)
	DDRD=0xff; // Nastaví port D, jako výstup (je připojen k anodám, řídí, která číslice je aktivní)
	PORTD=0xDF; // Otevře tranzistor, který napájí anodu číslice vlevo
	
	while (1)
	{
		for (int i=0;i<6;i++) //cyklus bude zvyšovat proměnnou "i" od 0 do 5
		{
			PORTB=znaky[i];	// Zapíše na displej i-tý prvek z pole
			_delay_ms(500); // Program se na 500ms zastaví, abychom stihli okem vnímat změnu
		}
	}
}
```
