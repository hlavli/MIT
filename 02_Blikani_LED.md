# Blikání LEDkou, práce s registry
Začneme jednoduchým úkolem - chceme blikat LEDkami na výukové desce. Nejprve se podíváme do schématu desky, jak jsou LEDky připojeny k procesoru.

![image](https://github.com/user-attachments/assets/c65df3c2-af64-4412-8f52-a94575112aa8)

Ze schématu  vidíme, že LEDky jsou připojeny k portu F. Kladné elektrody jsou přes odpor připojené k Vcc (+5V), záporné elektrody jsou připojeny k pinům procesoru. Tedy když je na pinu procesoru logická 0, LEDKa svítí, pokud je na pinu logická 1, LEDka nesvítí. 

## Registry pro práci s porty mikrokontroleru
Funkce mikroprocesoru nastavujeme zápisem do příslušných registrů. V tuto chvíli nám pro ovládání LEDek postačí jen první dva registry.

### DDRx - Data direction register
Protože většina pinů procesoru lze použít jako vstup nebo jako výstup, musíme nejprve nastavit piny k LEDkám jako výstupní. K tomu slouží pro každý port registr **DDRx**, kde x je písmeno portu. V našem případě tedy **DDRF**. Každý bit v tomto registru ovládá jeden pin portu F. Pokud je bit 0, pin se používá jako vstupní, pokud je bit 1, pin je nastaven jako výstup.

### PORTx - Port data  register
To, zda je na pinu +5V (logická 1) nebo 0V (logická 0) lze nastavit pomocí registru **PORTx**, kde x je písmeno portu. V našem případě tedy **PORTF**

**Příklad stavu registru PORTF a stavu LEDek:**

|Pořadí bitu| 7    | 6    | 5    | 4    | 3    | 2    | 1    | 0    | 
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:| 
|**Název**|  **PORTF7** | **PORTF6** | **PORTF5** |  **PORTF4** | **PORTF3** | **PORTF2** | **PORTF1** | **PORTF0** | 
|**Hodnota**| **0**    | **0**    | **0**   | **1**   | **1**    | **1**   |  **0**   |  **1**   | 
|**LEDky**|🟡    | 🟡    | 🟡    | ⚪    | ⚪    | ⚪    | 🟡    | ⚪    | 

### PINx - Input pin  register
Slouží pro čtení stavu pinu, pokud je použit jako vstupní. Pro blikání LEDkami ho potřebovat nebudeme, ale využijeme ho hned až k LEDkám přidáme tlačítka.

## Blikání LEDkami
Začneme jednoduše a budeme blikat všemi LEDkami zároveň. Nastavíme všech 8 pinů portu F jako výstupní, tedy do každého bitu zapíšeme jedničku:

``` DDRF = 0b11111111; ```

Teď když jsou piny nastavené jako výstup, můžeme měnit jejich stav. K tomu slouží registr **PORTx**, v našem případě tedy **PORTF**.

Ze schématu víme, že LEDky rozsvítíme, pokud na všechny piny nastavíme logickou 0:

``` PORTF = 0b00000000; ```

A LEDKy zhasneme zápisem logické 1 na všechny piny:

``` PORTF = 0b11111111; ```

Program pro blikání všemi LEDKami najednou může tedy vypadat třeba takto:

```c
#include <avr/io.h> // soubor definicemi adres registru, abychom mohli pouzivat symbolicke nazvy jako "PORTB" namisto ciselne adresy registru
#define F_CPU 16000000 // definice frekvence procesoru, v nasem pripade 16MHz aby spravne fungovala funkce delay
#include <util/delay.h> // pridani knihovny s funkci delay

int main(void)
{
  DDRF = 0x11111111; //nastavi vsechny piny portu F jako vystupy
  
  while (1) //nekonecna smycka
  {
    PORTF = 0b00000000; // vsechny piny portu F nastavi jako 0 ->LEDky se rozsviti
    _delay_ms(500); // cekani 500ms

    PORTF = 0b11111111;; // vsechny piny portu F nastavi jako 1 ->LEDky zhasnou
    _delay_ms(500); // cekani 500ms
  }
}

```

## Práce s jednotlivými bity
Doteď jsme nastavovali všechny piny společně. V praxi ale většinou chceme ovládat jednotlivé piny každý zvlášť.
Dejme tomu, že chceme blikat pouze třetí LEDkou (LED2 připojená na PF.2, protože číslujeme od 0)

Mohli bychom to udělat takto

```c
DDRF = 0b00000100; //Pin 2 jako výstup, piny 1-7 jako vstup
PORTF = 0b00000000; // Pin 2 = 0 -> LED ON
PORTF = 0b00000100; // Pin 2 = 1 -> LED OFF
``` 

Nevýhoda ale je, že kromě pinu 0 ovlivňujeme i všechny ostatní piny. A pokud by například na pinu 5 byla jiná LEDka, kterou ovládat nechceme, musíme na to jít jinak.

### Nastavení jednotlivých bitů do 1 (set bit)

Pokud chceme nastavit bit 2 do jedničky, ale neovlivnit přitom ostatní bity registru, můžeme pro to použít logický součet. 

| A   | B   | A \| B | 
|:---:|:---:|:------:| 
| 0   | 0   | 0      | 
| 0   | 1   | 1      | 
| 1   | 0   | 1      | 
| 1   | 1   | 1      | 

K pozicím bitů. které nechceme změnit přičteme 0, k těm, které chceme nastavit do 1 přičteme jedničku.

Všechny tři zápisy níže jsou ekvivaletní, ale v praxi používáme ten poslední, protože je krátký a přehledný

``` PORTF = PORTF | 0b00000100; ``` Můžeme v jazyce C napsat kratší formou:

``` PORTF |= 0b00000100; ``` Abychom nemuseli odpočítávat nuly, můžeme použít operaci rotace:

``` PORTF |= 1<<2; ``` Tento zápis je v praxi nejčastější.


Číslu, které logický součtem přičítáme k hodnotě registru se říká maska. Masku můžeme vytvořit pomocí operátoru << tedy rotace doleva. 

V našem případě chceme nastavit bit 2, tedy vezmeme jedničku a posuneme ji dvakrát doleva:

``` 1<<2 = 0b00000100```

Když tuto hodnotu logicky přičteme k registru PORTF, všechny bity zůstanou nezměněny, pouze bit 2 se nastaví do 1.


### Nastavení jednotlivých bitů do 0 (clear bit)

Pokud chceme nastavit bit 2 do nuly, ale neovlivnit přitom ostatní bity registru, můžeme pro to použít logický součin. 

| A   | B   | A & B | 
|:---:|:---:|:-----:| 
| 0   | 0   | 0     | 
| 0   | 1   | 0     | 
| 1   | 0   | 0     | 
| 1   | 1   | 1     | 


Pozice bitů, které nechceme změnit vynásobíme jedničkou, pozice bitů, které chceme vynulovat vynásobíme nulou.

``` PORTF = PORTF & 0b11111011; ``` Můžeme v jazyce C napsat kratší formou:

``` PORTF &= 0b11111011; ``` Abychom nemuseli odpočítávat jedničky, můžeme použít operaci rotace:

``` PORTF &= ~(1<<2); ``` Tento zápis je v praxi nejčastější.

Kromě operace rotace, kterou jsme popsali výše zde přibyl operátor bitové negace ~. Ten změní každý bit na opačnou hodnotu. 

Nejprve pomocí rotace získáme hodnotu:

``` 1<<2 = 0b00000100``` 

Když tuto hodnotu bitově znegujeme, získáme masku, kterou potřebujeme.

``` ~(1<<2) = 0b11111011; ```

Když touto hodnotou logicky vynásobíme registr PORTF, všechny bity zůstanou nezměněny, pouze bit 2 se nastaví do 0.

# Shrnutí

Pro ovládání pinů procesoru AVR slouží tyto registry:

| Registr | Popis                                              | 
|:-------:| :------------------------------------------------ | 
| DDRx    | Nastaví piny daného portu jako vstup nebo výstup   | 
| PORTx   | Nastaví na pinech portu log 1 nebo 0 (+5V nebo 0V) | 
| PINx    | Přečte stav pinu (pokud ho používáme jako vstup)   | 


Chceme-li konkrétní **bit nastavit do jedničky** (např. pin 5 portu A) lze to přehledně zapsat pomocí funkce OR a bitové rotace:

``` PORTA |= 1<<5; ``` 

Chceme-li konkrétní **bit nastavit do nuly** (např. pin 5 portu A) lze to přehledně zapsat pomocí funkce AND, negace a bitové rotace:

``` PORTA &= ~(1<<5); ```

## [Zpět na obsah](README.md)

