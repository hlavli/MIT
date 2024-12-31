<script type="text/javascript" id="MathJax-script" async src="https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-svg.js"> </script>

# AD převodník

Mikroprocesor jako digitální součástka dokáže pracovat pouze s digitálním signálem. Stav svých pinů čte pouze jako logickou jedničku nebo logickou nulu. Co když ale chceme měřit analogové hodnoty? Například  výstupní napětí z teplotního čidla, nebo napětí baterie, abychom zjistili stav jejícho nabití? K tomu slouží Analogově digtitální převodník - ADC. 

Většina mikrokontrolerů, včetně toho v našem přípravku má jeden nebo více ADC integrovaný ve svém pouzdře. AD převodník nám převede analogové napětí na vstupním pinu na digitální hodnotu, se kterou pak procesor může dále pracovat.

## Referenční napětí
AD převodník funguje poměrově (ratiometric) to znamená že hodnota jeho výstupu udává poměr měřeného napětí  a referenčního napětí. 

$$
\Large Digitální_hodnota = Rozlišení_ADC \times \frac{Vin}{Vref}
$$

Napříkald u 10bitového ADC, kde Vref je 5V a měřené napětí je 2,5V:

$$
\Large 1023 \times \frac{2,5}{5} = 512
$$

Zdroj referenčního napětí si můžeme zvolit. Může jim být napájecí napětí mikrokontroleru, vnitřní zdroj referenčního napětí či externě připojený zdroj ref. napětí (např. speciální obvody, jako je LM4040 nebo LM336).

## Prescaler hodinového signálu
Podobně jako u časovače, musíme nastavit, s jakou frekvencí hodinového signálu bude AD převodník pracovat. Do jisté míry platí, že čím bude převod rychlejší, tím méně bude přesný a naopak. AD převodník použitý v ATmega 2560 vyžaduje prekvenci mezi 50kHz a 200kHz.

## Mutliplexer
Protože AD převodník je v čipu mikrokontroleru jen jeden, ale je užitečné mít možnost měřit analogové napětí na více pinech, lze pomocí multiplexeru připojit AD převodník k různým pinům. Výběr pinu musíme samozřejmě provést dřív, než spustíme měření.


## Důležité registry

![image](https://github.com/user-attachments/assets/7ca78391-e95f-47b8-a29e-5abd5dee4b28)

![image](https://github.com/user-attachments/assets/5d9e78f5-7b8a-40ef-9b43-b4790e6940f7)

![image](https://github.com/user-attachments/assets/3110e411-45c2-4292-869f-4fe0f37e1bc9)

![image](https://github.com/user-attachments/assets/048354c4-1092-4b57-9370-897b7a885049)

![image](https://github.com/user-attachments/assets/ee141afe-1064-4e5a-af2a-17c9bf33633f)


## Spuštění konverze
Jak spustit, počkat na výsledek, zmínit přerušení

![image](https://github.com/user-attachments/assets/e095c283-b1fd-48c5-9536-54699dae509f)



## Úkoly
1. Měřte pomocí ADC hodnotu napětí na potenciometru a zobrazujte ji na LCD displeji.
2. Rozvěcejte LEDky podle polohy potenciometru (0V - nesvítí žádná LED, 5V - svítí všechny, 2.5V - svítí 4 LEDky atd).
3. Nastavujte potenciometrem rychlost blikání LEDek (1Hz - 50Hz). Frekvenci zobrazujte na LCD displeji.
