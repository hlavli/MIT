# Stopky

Vytvořte na výukovém přípravku stopky. 

<img src="https://github.com/user-attachments/assets/fc7ba275-656b-448f-9df5-7d8b9a2ae141" width="600"/>

## Požadavky na funkci

- Čas se bude zobrazovat na LCD displeji ve formátu ```MM:SS:ss``` kde ```MM``` jsou minuty, ```SS``` sekundy a ```ss```setiny sekund.
- Tlačítko ```SW7``` bude mít funkci Start/Stop - jedno stisknutí stopky spustí, popř. zastaví, pokud už běží.
- Tlačítko ```SW6``` bude mít funkci Reset. Pokud jsou stopky zastaveny, vynuluje všechny číslice.


## Postup

1. Vytvořte nový projekt, přidejte do něj knihovnu pro [LCD displej](https://tomaschovanec.github.io/MIT/12_LCD.html), ověřte, že vám displej funguje
2. Vytvořte si proměnnou pro milisekundy. Jednou za 10ms tuto proměnnou zvyšte o 10 a její hodnotu vypište na displej. Pro odměření času použijte funkci ```_delay_ms(10);```.
3. Nyní si vytvořte proměnné pro sekundy a minuty. Pomocí podmínek naprogramujte, aby se správně navyšovaly (sekundy po 1000 ms a minuty po 60 s)
4. Ověřte pomocí stopek na telefonu, zda je měření času přesné. Pokud ne, zkuste přijít na to proč?



### Bonusový úkol
Použijte pro zobrazení sedmisegmentový displej.


## [Zpět na obsah](README.md)
