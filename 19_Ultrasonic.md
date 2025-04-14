# Ultrazvukový senzor vzdálenosti
S ultrazvukovým senzorem vzdálenosti HC-SR04 jsme už pracovali v rámci předmětu Praxe. Pro měření času, který potřebovala ultrazvuková vlna k cestě k překážce a zpět, jsme v Praxi používali funkci ```pulseIn()```. V předmětu MIT si ale ukazujeme práci s procesorem od základu, proto nepoužijeme hotovou funkci z knihovny, ale pro měření času použijeme čítač/časovač.

## Princip senzoru
Pro připomenutí - senzor funguje tak, že po aktivaci měření 10us pulzem na Trig pinu vyšle krátký ultrazvukový impulz a nastaví Echo pin do log. 1. Ve chvíli, kdy se k senzoru vrátí odražená vlna, nastaví Echo pin do log. 0. Proto pomocí délky pulzu na pinu Echo můžeme určit vzdálenost překážky.

![image](https://github.com/user-attachments/assets/b9491ccf-c2ee-4d43-abfb-c589ddbb5567)

*Zdroj obrázku: https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/*

![image](https://lastminuteengineers.com/wp-content/uploads/arduino/HC-SR04-Ultrasonic-Sensor-Working-Echo-reflected-from-Obstacle.gif)

*Zdroj obrázků: https://lastminuteengineers.com/arduino-sr04-ultrasonic-sensor-tutorial/*

### Zapojení
Kromě +5V napájení a GND musíme čidlo připojit ke dvěma libovolným pinům mikroprocesoru. **Pin Trig** slouží ke spuštění měření (vyslání ultrazvukového pulzu), musíme jej tedy v mikroprocesoru nastavit jako výstup. **Pin Echo** je výstup senzoru (tedy z pohledu mikroprocesoru vstup), na kterém senzor generuje puls, jehož délka odpovídá době od vyslání signálu do návratu odražené vlny.

![image](https://github.com/user-attachments/assets/97bf9bf2-9d66-4816-bda1-f13b5380f0e9)

5V pro napájení čidla najdete na přípravku například zde:

![image](https://github.com/user-attachments/assets/e5dff296-7023-495a-8e78-43398c8cf3c0)


### Úkoly

**1.** Připojte k výukovému přípravku ultrazvukový senzor. Zvolte si, kaz zapojíte Trig a Echo pin. Správně je nakonfigurujte jako vstup/výstup.
**2.** Napište program, který jednou za sekundu vygeneruje 10us pulz na pin Trig. Ověřte logickým analyzerem, jak vypadají průběhy na pinu Trig a pinu Echo
**3.** Dále potřebujeme měřit co nejpřesněji čas, po který je pin Echo v log1 (tedy čas od vyslání ultrazvukové vlny do návratu jejího odrazu. K tomu použijeme časovač v režimu Normal. Vyberte vhodnou hodnotu předděličky (spočítejte, nebo s logickým analyzerem změřte, jaký rozsah času budeme potřebovat).
**4.** Přidejte navíc LCD displej a zobrazujte na něm délku pulzu na Echo pinu.
**5.** Naměřenou hodnotu na displeji zobrazujte v centimetrech


## [Zpět na obsah](README.md)
