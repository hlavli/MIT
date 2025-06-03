# Stopky

Vytvořte na výukovém přípravku stopky. 

<img src="https://github.com/user-attachments/assets/fc7ba275-656b-448f-9df5-7d8b9a2ae141" width="400"/>

## Požadavky na funkci

- Čas se bude zobrazovat na LCD displeji ve formátu ```MM:SS:ss``` kde ```MM``` jsou minuty, ```SS``` sekundy a ```ss```setiny sekund.
- Tlačítko ```SW7``` bude mít funkci Start/Stop - jedno stisknutí stopky spustí, popř. zastaví, pokud už běží.
- Tlačítko ```SW6``` bude mít funkci Reset. Pokud jsou stopky zastaveny, vynuluje všechny číslice.


## Postup

**1.** Vytvořte nový projekt, přidejte do něj knihovnu pro [LCD displej](https://tomaschovanec.github.io/MIT/12_LCD.html), ověřte, že vám displej funguje

**2.** Vytvořte si proměnnou pro milisekundy. Jednou za 10ms tuto proměnnou zvyšte o 10 a její hodnotu vypište na displej. Pro odměření času použijte funkci ```_delay_ms(10);```.

**3.** Nyní si vytvořte proměnné pro sekundy a minuty. Pomocí podmínek naprogramujte, aby se správně navyšovaly (sekundy po 1000 ms a minuty po 60 s)

**4.** Celý čas zobrazujte na LCD displeji pomocí [funkce sprintf()](https://github.com/TomasChovanec/MIT/blob/main/12_LCD.md#ascii-k%C3%B3d-funkce-sprintf). Jako formátovací parametr ve funkci sprintf doporučuji použít ```%02d```.

**5.** Ověřte pomocí stopek na telefonu, zda je měření času přesné. Pokud ne, zkuste přijít na to, proč?

**6.** Abyste dosáhli přesného měření času, použijte časovač s přerušením.
    - Do funkce main přidejte nastavení časovače. Hodnotu registru OCR1A si spočítejte tak, aby se přerušení vyvolalo jednou za 10ms.

    ```c
    TIMSK1 = 0x02; // Povolení přerušení při shodě čítače s komparačním registrem OCR1A
    sei(); // Globální povolení přerušení
    TCCR1B = 0b0001100; // CTC režim, dělička 256 -> Ttick = 16us
    
    OCR1A = ???; // Dopočítejte počet ticků do přerušení 10ms (1 tick = 16us)
    ```
    
    - Nad funkcí ```main()``` nadefinujte funkci obsluhy přerušení časovače:
      
    ```c
    ISR(TIMER1_COMPA_vect)
    {
    // Zde přidejte zvyšování proměnných s milisekundami, sekundami a minutami
    }
    ```

**7.** Ověřte, že nyní stopky běží přesně

**8.** Přidejte funkcionalitu tlačítek Start/Stop a Reset



### Bonusový úkol
Použijte pro zobrazení sedmisegmentový displej.


## [Zpět na obsah](README.md)
