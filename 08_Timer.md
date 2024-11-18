# Timer

Timer, česky časovač je v mikroprocesorové technice důležitá periferie. Použijeme ho například při generování přesného časového signálu, PWM, měření času, ale i počítání vnějších událostí (např. počtu impulzů z nějakého čidla). Je integrován uvnitř pouzdra mikroprocesoru, ale funguje samostatně, to znamená že neustále počítá, i když jádro procesoru dělá něco jiného. Tím pádem je časování přesné a navíc jádro procesoru může dělat něco jiného, nemusí být "zabržděno" v čekacích smyčkách (např. funkce _delay_ms()) .

## Preload
$$
\text{Reload Timer Value} = (2^{\text{Bits}} - 1) - \left( \frac{\text{Input Frequency}}{\text{Prescale} \times \text{Target Frequency}} \right)
$$


## Úkoly

1. 
2. 




### [Zpět na obsah](README.md)
