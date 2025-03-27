# Samostatná úloha - Dálkové ovládání LED světla pomocí UARTu

Naprogramujte dva mikrokontroléry ATmega2560, které budou komunikovat přes UART. Jeden bude sloužit jako ovládací jednotka s klávesnicí, druhý bude přijímat příkazy a podle nich nastavovat LEDky.

![image](https://github.com/user-attachments/assets/e95ffe7d-c199-461f-86b0-b83ea28b15b6)

## Požadavky na funkci systému

### Ovládací jednotka

- Čeká na vstup z klávesnice.
- Po stisku klávesy pošle odpovídající příkaz (1 bajt) přes UART
- Příkazy:
    - 'A' – zapnout všechny LED
    - 'B' – zapnout jen liché LED
    - 'C' – vypnout všechny LED


### Jednotka pro ovládání LED
- Přijímá příkazy přes UART
- Podle přijatého znaku nastavuje LEDky
- Pokud přijde neplatný znak, ignoruje ho

### Bonusové úkoly
- Přidejte možnost zapínat a vypínat LEDky po jedné - klávesa * přidá jednu LEDku, klávesa # zhasne jednu LEDku
- Pokud přijde neplatný znak, přijímající jednotka spustí krátký tón bzučáku
- Přidejte možnost LEDky nastavovat otáčením potenciometru 

### [Zpět na obsah](README.md)
