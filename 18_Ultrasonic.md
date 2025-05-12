# Ultrazvukový senzor vzdálenosti
S ultrazvukovým senzorem vzdálenosti HC-SR04 jsme už pracovali v rámci předmětu Praxe. Pro měření času, který potřebovala ultrazvuková vlna k cestě k překážce a zpět, jsme v Praxi používali funkci ```pulseIn()```. V předmětu MIT si ale ukazujeme práci s procesorem od základu, proto nepoužijeme hotovou funkci z knihovny, ale pro měření času použijeme čítač/časovač.

## Princip senzoru
Senzor funguje tak, že po aktivaci měření 10us pulzem na Trig pinu vyšle krátký ultrazvukový impulz a nastaví Echo pin do log. 1. Ve chvíli, kdy se k senzoru vrátí odražená vlna, nastaví Echo pin do log. 0. Proto pomocí délky pulzu na pinu Echo můžeme určit vzdálenost překážky.

![image](https://github.com/user-attachments/assets/b9491ccf-c2ee-4d43-abfb-c589ddbb5567)

*Zdroj obrázku: https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/*

![image](https://github.com/user-attachments/assets/a929329a-320f-4a6d-aeca-b4092caa1869)

*Zdroj obrázků: https://medium.com/@robotamateur123/understanding-ultrasonic-sensor-e3791f883061*

### Zapojení
Kromě +5V napájení a GND musíme čidlo připojit ke dvěma libovolným pinům mikroprocesoru. **Pin Trig** slouží ke spuštění měření (vyslání ultrazvukového pulzu), musíme jej tedy v mikroprocesoru nastavit jako výstup. **Pin Echo** je výstup senzoru (tedy z pohledu mikroprocesoru vstup), na kterém senzor generuje puls, jehož délka odpovídá době od vyslání signálu do návratu odražené vlny.

![image](https://github.com/user-attachments/assets/97bf9bf2-9d66-4816-bda1-f13b5380f0e9)

5V pro napájení čidla najdete na přípravku například zde:

![image](https://github.com/user-attachments/assets/e5dff296-7023-495a-8e78-43398c8cf3c0)


### Úkoly

**1.** Připojte k výukovému přípravku ultrazvukový senzor. Zvolte si piny, kam zapojíte signály Trig a Echo. Správně je nakonfigurujte - Echo jako vstup, Trig jako výstup.

**2.** Napište program, který jednou za sekundu vygeneruje 10us pulz na pin Trig. Jak manipulovat s jednotlivými bity portu najdete [zde](https://tomaschovanec.github.io/MIT/03_Bitove_operace.html#negace-jednotliv%C3%BDch-bit%C5%AF-toggle-bit). Ověřte logickým analyzerem, jak vypadají průběhy na pinu Trig a pinu Echo. 

**3.** Dále potřebujeme měřit co nejpřesněji čas, po který je pin Echo v log. 1 (tedy čas od vyslání ultrazvukové vlny do návratu jejího odrazu. K tomu použijeme časovač v režimu Normal. Vyberte vhodnou hodnotu předděličky (spočítejte, nebo s logickým analyzerem změřte, jaký rozsah času budeme potřebovat). Hodnoty předděličky najdete [v lekci s časovačem](https://tomaschovanec.github.io/MIT/08_Timer.html#%C4%8Dasov%C3%A1n%C3%AD-pro-r%C5%AFzn%C3%A9-hodnoty-prescaleru).

Důležité registry pro časovač:

```c
TCNT1 = 0; // vynulování čítače (TCNT1 je čítací registr)
TCCR1A = 0; // normální režim
TCCR1B = ???; // nastavení předděličky a spuštění časovače
TCCR1B = 0;  // zastavení časovače
```
**4.** Přidejte navíc [LCD displej](https://tomaschovanec.github.io/MIT/12_LCD.html) a zobrazujte na něm délku pulzu na Echo pinu.

**5.** Naměřenou hodnotu na displeji zobrazujte v milimetrech. Pozor, pokud pro výpočet používáte desetinná čísla (např. násobíte 0.34) tak překladač automaticky číslo přetypuje na typ s desetinnou čárkou (float nebo double). Pokud chceme výsledek zobrazit na LCD displeji pomocí formátovacího znaku ```%d```, musíme číslo přetypovat na integer např: ```int vysledek = (int)(delka*0.34)```.

**6.**  Pomocí LED diod indikujte vzdálenost v krocích po 10 cm: 0–10 cm → 1 LED, 10–20 cm → 2 LED, …, 90 cm a více → 10 LED.

**7.** Pokud je vzdálenost nižší než 10cm, zapněte bzučák (na kterém pinu je zapojen najdete ve [schematu](files/Development_board_schematics.pdf), součástka s označením Bz1).

## [Zpět na obsah](README.md)
