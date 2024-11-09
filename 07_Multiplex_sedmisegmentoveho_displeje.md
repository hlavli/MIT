# Multiplex sedmisegmentového displeje
Na našem přípravku máme celkem 6 pozic sedmisegmentového displeje. Řídit jednu pozici displeje už umíme, nyní bychom chtěli pokročit a zobrazovat víceciferná čísla. Ze schématu ale víme, že sada vodičů pro řízení jednotlivých segmentů je jen jedna. Jak to tedy udělat, abychom mohli na různých pozicích zobrazovat různá čísla?

![image](https://github.com/user-attachments/assets/d7519c09-32a6-4c2c-b350-a08d664351e7)


## Multiplexování
Budeme muset použít techniku, které se říká multiplexování. Multiplexování je způsob, jak sdílet jeden komunikační kanál mezi více zdroji informací. V našem případě máme na přípravku 6 pozic sedmisegmentového displeje, ale pouze jednu sadu vodičů, které ovládají segmenty. Můžeme ale v čase postupně rozsvěcet a zhasínat jednotlivé pozice displeje. Pokud to budeme dělat dostatečně rychle, díky setrvačnosti lidského oka se nám bude zdát, že všechny pozice displeje svítí zároveň. 

![image](https://upload.wikimedia.org/wikipedia/commons/a/a4/7segment_multiplexing.gif)
*Zdroj obrázků: By Laserlicht, CC BY-SA 4.0, https://commons.wikimedia.org/w/index.php?curid=115556518* 

### [Zpět na obsah](README.md)
