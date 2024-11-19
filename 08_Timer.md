# Časovač

Časovač, anglicky Timer je v mikroprocesorové technice důležitá periferie. Použijeme ho například při generování přesného časového signálu, PWM, měření času, ale i počítání vnějších událostí (např. počtu impulzů z nějakého čidla). Je integrován uvnitř pouzdra mikroprocesoru, ale funguje samostatně, to znamená že po prvotním nastavení počítá sám, i když jádro procesoru dělá něco jiného. Tím pádem je časování přesné a navíc jádro procesoru může dělat něco jiného, nemusí být "zabržděno" v čekacích smyčkách (např. funkce _delay_ms()) .

## Princip časovače, důležité registry

Základní jednotkou časovače je čítací registr, který zvýší svou hodnotu o 1 při každé nástupné hraně hodinového signálu. Pokud dosáhne maximální hodnoty (255 pro 8bitový čítač a 65535 pro 16bitový) při další hraně hodin "přeteče" ->nastaví se opět do 0 a nastaví příznakový bit do 1.

![image](https://github.com/user-attachments/assets/c4c13016-1b2d-40f1-81c7-ca5e91862b35)

## Nastavení časovače

V našem přípravku je zdrojem hodinového signálu krystal s frekvencí 16 MHz, tedy jeden "tick" trvá 1/f = 1/16*10^6 = 62,5ns . Timer1 je 16bitový, tedy maximální hodnota je 65535. Takže k přetečení čítače by došlo za 65536 *  62,5ns = 4,096ms. Pokud chceme aby perioda časovače byla delší (např. chceme blikat s LEDkou jednou za 500ms) můžeme hodinový signál z krystalu vydělit předděličkou (prescaler). Prescaler můžeme změnit zápisem do bitů CSnx v registru TCCR1B viz tabulka.

![image](https://github.com/user-attachments/assets/1aa90833-aa8f-49f3-bf8b-b20401c2be39)

V registru TCCR1B najdeme můžeme nastavit režim časovače (v této lekci budeme používat Normal mode a CTC mode) a nastavení prescaleru (předděličky hodinového signálu) .

![image](https://github.com/user-attachments/assets/03858294-1551-4f8e-a3e9-1179efdfa39f)

Podle toho, jaký chceme použít režim (mode) časovače, nastavíme jednotlivé bity WGMxx. Pozn. bity  WGM11 a WGM10 v tomto cvičení nastavovat nepotřebujeme, stačí nám je nechat v defaultní hodnotě, což je 0. Pokud bychom chtěli ale zvolit další režimy, najdeme je v registru TCCR1A. 

![image](https://github.com/user-attachments/assets/1686f100-b836-415c-a0d4-cf21dd0fff0c)



## Příznakové bity
Hodnota čítače se zvyšuje s každou hranou hodinového signálu. Když dojde až do maxima, při dalším hraně hodin přeteče (overflow) a nastaví se opět do nuly. Při přetečení se nastaví příznakový bit TOV v registru TIFR1. Registr TIFR1 obsahuje i další příznaky, např v tomto cvičení použijeme ještě příznak OCF1A, který se používá v CTC režimu a nastaví se, když se hodnota čítače rovná hodnotě v compare registru OCR1A. 

![image](https://github.com/user-attachments/assets/7e6b6389-acac-4013-b738-894638c304be)



## Časovač Timer1 v režimu Normal

Zkusme využít časovač pro blikání LEDkami. Použijeme Timer1 v režimu Normal. Čítač spustíme a budeme čekat, až dojde k přetečení (budeme dokola číst bit TOV1). Až dojde k přetečení, musíme příznakový bit ručně vymazat (zapsáním 1). Pak znegujeme stav LEDek na portu F a opět budeme čekat na další přetečení.

```C
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

>### 1. Úkol
>Nastavte jiné hodnoty prescaleru a sledujte jak se změní rychlost blikání LEDek, spočítejte frekvenci blikání (ověříme měřením logickým analyzerem).

## Časovač Timer1 v režimu CTC
Nastavením prescaleru můžeme získat pouze několik málo frekvencí přetečení časovače. Pro jemnější nastavení můžeme použít režim CTC (Clear timer on Compare Match). Funguje tak, že nenecháme časovač počítat od nuly do maxima, ale do registru OCR1A nastavíme novou maximální hodnotu časovače. Když časovač "dopočítá" do této hodnoty (hodnota čítacího registru TCNT1 se bude rovnat hodnotě v compare registru OCR1A) dojde k přetečení čítače, nastaví se příznak přetečení OCF1A a čítač se nastaví opět do nuly. VIz obrázek níže.

![image](https://github.com/user-attachments/assets/8d2910e8-3add-4462-b892-426b771df6f6)

Hodnotu pro nastavení registru OCR1 spočítáme podle vzorce:

![image](https://github.com/user-attachments/assets/fa05b1f2-aba1-4796-b380-07afbf4027fd)

Kde:

f<sub>clk</sub>  - frekvence hodin mikrokontroléru (v našem přípravku 16MHz)

Prescaler - zvolená hodnota předděličky (/64, /1024 atd) 

𝑓<sub>target</sub> - žádaná frekvence přetečení čítače


>### 2. Úkol 
>Nastav časovač pomocí CTC režimu, aby došlo k přetečení každých 500ms


## Změna frekvence časovače pomocí přednastavení časovače (preload)

Pokud z nějakého důvodu nechceme nebo nemůžeme použít CTC režim (např. používáme procesor, jehož čítač CTC režium neumí), můžeme změnit frekvenci časovače tím, že nebude začínat od nuly, ale od vyšší hodnoty.

![image](https://github.com/user-attachments/assets/065ff747-06ff-49ed-b3b2-4533922b9b37)

Hodnotu pro přednsastavení registru TCNT spočítáme podle vzorce:

![image](https://github.com/user-attachments/assets/bdaa10f3-8dca-4608-b075-b84bdd6b398c)

Kde:

f<sub>clk</sub>  - frekvence hodin mikrokontroléru (v našem přípravku 16MHz)

Prescaler - zvolená hodnota předděličky (/64, /1024 atd) 

𝑓<sub>target</sub> - žádaná frekvence přetečení čítače

Bits - počet bitů čítače (8 pro Timer0 a 16 pro Timer1)

Narozdíl od CTC režimu, zde musíme do registru TCNT pokaždé, když timer přeteče, nastavit opět ručně vypočítanou hodnotu.

>### 3. Úkol
>Nastavte časovač do Normal režimu s přednastavením do TCNT aby došlo k přetečení každé 2s.


### [Zpět na obsah](README.md)
