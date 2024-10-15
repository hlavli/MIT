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
PORTB = 0xC0; // Zobrazíme na displeji nulu
```

### Zapojení v přípravku
Sedmisegmentové displeje mohou být buď se společnou katodou (všechny katody jsou spojeny a připojeny k zemi, anody jsou vyvedeny pro každý segment zvlášť) nebo naopak se společnou anodou. Pohledem do schématu našeho přípravku zjistíme, že ten náš je se společnou anodou.

![image](https://github.com/user-attachments/assets/d7519c09-32a6-4c2c-b350-a08d664351e7)

V našem přípravku není sedmisegmentový displej připojen k procesoru trvale, ale je vyveden na pinovou lištu. Pokud chceme displej používat, musíme ho připojit kablíky viz. obrázek níže.

![image](https://github.com/user-attachments/assets/1320cb6d-6883-4c99-9c53-15064df9df56)


