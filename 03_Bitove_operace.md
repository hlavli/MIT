# Převody číselných soustav, bitové operace
V mikroprocesorové technice potřebujeme často pracovat s čísly na úrovni bitů - když chceme přečíst stav jen jednoho tlačíka a ne všech osmi, když chceme zhasnout jen jednu LEDku a ostatní nechat svítit, atd. Proto je dobré ovládat základní převody mezi desítkovou (neboli decimální), šestnáctkovou (neboli hexadecimální) a dvojkovou (neboli binární). Složitější počty a převody je samozřejmě běžné dělat na kalkulačce, ale zíkladní operace budeme používat natoli k často, že se vyplatí je umět z hlavy.

Protože počítače používají binární soustavu, mohli bychom vše psát binárně. Ovšem u větších čísel je binární zápis dlouhý a nepřehledný. Proto se v praxi používá obvykle hexadecimální zápis, který lze do binárního snadno z hlavy převést.

## Převod z binární do hexadecimální soustavy

V hexadecimální soustavě může každá číslice nabývat hodnot od nuly do patnácti. Číslice 0-9 jsou stejné jako jsme zvyklí z desítkové soustavy, dále pak 10 píšeme jako A, 11 jako B, atd až 15 jako F.

![image](https://github.com/user-attachments/assets/07eff5d5-d405-4caa-a664-ae9a075abdff)



```
      8 4 2 1
bin:  0 0 0 1 = 1 
```

```
      8 4 2 1
bin:  0 1 0 1 = 4 + 1 = 5 
```

```
      8 4 2 1
bin:  1 1 1 1 = 8 + 4 + 2 + 1 = 15 = 0xF
```

```
      8 4 2 1  8 4 2 1
bin:  1 1 1 1  0 1 0 1 = 0xF5
```

```
      8 4 2 1  8 4 2 1
bin:  1 1 1 0  1 1 0 0 = 0x7C
```

## Převod z hexadecimální do binární soustavy

```
        8 4 2 1  8 4 2 1
0x52 =  0 1 0 1  0 0 1 0
```

```
        8 4 2 1  8 4 2 1
0xD7 =  1 1 0 1  0 1 1 1
```

## Bitová negace ~

```
0xD7 =  1101 0111

~0xD7 = 0010 1000 = 0x28 
```

## Bitová rotace << nebo >>

```
0x58      =  0101 1000
0xD7 << 1 =  1011 0000
```

```
0xD7      =  1101 0111
0xD7 << 2 =  0101 1100
```

![image](https://github.com/user-attachments/assets/59e0e6ec-3ca1-44f2-bdc5-428ca1057cc1)



## Logický součet OR |

| A   | B   | A \| B | 
|:---:|:---:|:------:| 
| 0   | 0   | 0      | 
| 0   | 1   | 1      | 
| 1   | 0   | 1      | 
| 1   | 1   | 1      | 

![image](https://github.com/user-attachments/assets/46fdfcb4-a01c-49ec-9f11-6813471c3cad)

```
  0x15   =>  0001 0101
| 0xF0   =>  0101 0000
------      ----------
  0x55   <=  0101 0101 
```

## Logický součin AND &

| A   | B   | A & B | 
|:---:|:---:|:-----:| 
| 0   | 0   | 0     | 
| 0   | 1   | 0     | 
| 1   | 0   | 0     | 
| 1   | 1   | 1     | 


![image](https://github.com/user-attachments/assets/78be4130-0ed2-4fa6-be46-073bf29692d8)


```
  0x15   =>  0001 0101
& 0xF0   =>  0101 0000
------      ----------
  0x10   <=  0001 0000 
```

## Práce s jednotlivými bity
V předchozí lekci, když jsme blikali LEDkami, jsme nastavovali všechny piny společně. V praxi ale většinou chceme ovládat jednotlivé piny každý zvlášť.
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


Chceme-li konkrétní **bit nastavit do jedničky** (např. pin 5 portu A):

``` PORTA |= 1<<5; ``` 

Chceme-li konkrétní **bit nastavit do nuly** (např. pin 5 portu A):

``` PORTA &= ~(1<<5); ```




## [Zpět na obsah](README.md)
