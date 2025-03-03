## Samostatná úloha - Vzdálené ovládání LED pomocí UART

Naprogramujte dva mikrokontroléry ATmega2560, které budou komunikovat přes UART. Jeden bude sloužit jako ovládací jednotka s klávesnicí, druhý bude přijímat příkazy a podle nich nastavovat LEDky.

### **Požadavky na funkci systému**

**Ovládací jednotka (Master)**
- Čeká na vstup z klávesnice.
- Po stisku určité klávesy pošle odpovídající příkaz přes UART
- Příkazy mohou být například:
'A' – zapne všechny LED
'B' – zapne polovinu LED
'C' – vypne všechny LED


**Jednotka pro ovládání LED (Slave)**
- Přijímá příkazy přes UART
- Podle přijatého znaku nastavuje LEDky
- Pokud přijde neplatný znak, ignoruje ho

**Bonusové úkoly**
- Umožněte nastavovat LEDky  od 0-10. Klávesa * přidá jednu LEDku, klávesa # zhasne jednu LEDku
- Pokud přijde neplatný znak ozve se tón bzučáku
- Bude možné LEDky nastavovat otáčením potenciometru 
