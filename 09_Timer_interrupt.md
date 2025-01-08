# Časovač s přerušením

V minulém cvičení jsme se naučili nastavit časovač v mikroprocesoru tak, aby přetekl například jednou za 100ms. Příznakový bit jsme v hlavním programu neustále sledovali. Když pak časovač přetekl a příznakový bit se nastavil do jedničky, náš program na to zareagoval, např. bliknul LEDkou.  Tomuto přístupu, kdy hlavní program pořád dokola kontroluje, zda se nastavil nějaký bit se říká *polling*. Nevýhoda je, že procesor tráví svůj čas jen neustálým kontrolováním příznakového bitu a nedělá nic jiného. Lepší by bylo, kdyby procesor vykonával program a jen v okamžiku, kdy časovač přeteče by se automaticky zastavil, bliknul LEDkou a pak pokračoval v hlavním programu. Takováto funkce v mikroprocesorech skutečně je a říkáme jí "přerušení".

## Přerušení
Přerušení (interrupt) je mechanismus mikroprocesoru, který mu umožňuje okamžitě reagovat na nějakou událost. Například na stisk tlačítka, přijetí dat na sériovém portu, přetečení časovače a mnohá další. Pokud procesor detekuje přerušení (např. přetekl časovač) přeruší se aktuálně prováděný program a procesor přeskočí na funkci obsluhy přerušení. Poté, co tato funkce skončí opět procesor pokračuje tam kde přestal - vykonává dál instrukce hlavního programu.

<img src="https://github.com/user-attachments/assets/143db4f3-b39f-427e-9634-3a00c36686ef" width="600"/>

## Obsluha  přerušení
Kód, který se vykoná po detekci přerušení se nazývá obsluha přerušení (interrupt routine). Je to speciální funkce, kterou nazveme ISR (Interrupt Service Routine) a v závorce uvedeme vektor přerušení. Například, pokud budeme chtít pomocí časovače v CTC režimu blikat LEDkou, použijeme přerušení *Timer/Counter1 Compare Match A* a obslužnou funkci nadefinujeme takto:

```C
ISR(TIMER1_COMPA_vect)
{
PORTF ^= 0xff; // Negace LEDek
}
```

V tabulce níže je pro názornost několik vybraných zdrojů přerušení a názvy jejich vektorů. Seznam všech vektorů přerušení můžete najít v datasheetu mikroprocesoru.

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


## Povolení přerušení

Kromě definice obslužné funkce pro dané přerušení, musíme ještě povolit konkrétní přerušení (v našem případě přerušení od časovače najdeme v registru TIMSK1) a pak povolit globálně přerušení pomocí funkce sei().

![image](https://github.com/user-attachments/assets/d318174c-cbe7-4fe9-9a21-7af3dff00903)

Příklad kódu pro povolení přerušení OCIE1A.  Output Compare Interrupt Enable for Timer/Counter1, Channel A. Jedná se o přerušení, které je vyvoláno, když hodnota časovače/counteru 1 (Timer/Counter1) dosáhne hodnoty uložené v Output Compare Register A (OCR1A).

```C
TIMSK1 = 0x02; // Povolení přerušení při shodě čítače s komparačním registrem OCR1A
sei(); // Globální povolení přerušení
```

## Použití dalších časovačů

Doteď jsme používali jen časovač Timer1. Mikrokontroler ATmega 2560, který máme v přípravku, ale obsahuje časovačů mnohem více. Čtyři 16bitové: Timer1, Timer3, Timer4, Timer5 a pak ještě dva 8bitové Timer0 a Timer2. Osmibitové čítače se od šestnáctibitových liší nejen počtem bitů, ale mají i méně funkcí a jejich registry vypadají trochu jinak než u šestnáctibitových časovačů. 

Ovšem 16bitové časovače jsou navzájem totožné, liší se jen čísly ve jméně registru. Takže pokud si spočítáme a určíme například pro Timer1 hodnoty registrů TCCR1B a OCR1A, můžeme je úplně stejně použít pro Timer3, Timer4 nebo Timer5, pouze index ve jméně registur se změní. Tedy např pro Timer3 by to byly registry TCCR3B a OCR3A.


## Úkoly
1. Vytvořte program, který pomocí fuknce _delay_ms() bliká LED0 a LED1 s frekvencí 2Hz.
2. Rozšiřte progrma, aby blikal LED2 a LED3 s frekvencí 10Hz. Použijte k tomu časovač s přerušením.
3. Přidejte k zadání v bodu jedna ještě druhý 16bitový časovač, který bude LED6 a LED7 blikat s frekvencí 1Hz.
4. Při stisku tlačítka SW7 zvyšte frekvenci blikání LED6 a LED7 na 5Hz.

Pro usnadnění výpočtů hodnot pro časovače můžete použít tabulku s předpočítanými hodnotami:

![image](https://github.com/user-attachments/assets/d021eb3d-52b4-48d5-84a6-604a7a3b8ba0)

## Další užitečné zdroje informací

[Video k přerušením od časovače](https://www.youtube.com/watch?v=Uv9UeYUsA8A&ab_channel=Electronoobs)

[Přerušení obecně](https://www.renesas.com/en/support/engineer-school/mcu-05?srsltid=AfmBOoopor2K3EEakK9uVCQjMFgDe9IM-vR9Ue96SOFzn6UM89az0LUM)


## [Zpět na obsah](README.md)
