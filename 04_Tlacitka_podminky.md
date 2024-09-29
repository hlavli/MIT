### Práce s tlačítky

V předchozích cvičeních jsme se naučili nastavit piny jako výstupní pomocí registrů DDRx a měnit jejich stav pomocí registrů PORTx. V této kapitole se naučíme nastavit piny jako vstupní a číst jejich stav. Použijeme k tomu tlačítka na našem přípravku.

Ze schématu přípravku můžeme zjistit, že tlačítka jsou připojena na port K. Piny portu K jsou připojeny přes relativně velký odpor (4.7kΩ) k Vcc, tedy k +5V. Pokud tlačítko není stisknuto, "naměří" procesor na pinu 5V a vyhodnotí to jako logickou jedničku. 
Pokud ovšem tlačítko stiskneme, pin tím připojíme bez odporu přímo na zem. Procesor pak na pinu "naměří" 0V a vyhodnotí to jako logickou nulu. Těm 4.7kΩ rezistorům se říká pull-up odpory. Jsou důležité proto, aby i v případě, že tlačítko není stisknuto, byla na pinu jasně definovaná úroveň. 
Bez těchto odporů by v nestisknutém stavu pin nebyl k ničemu připojen a jeho stav by byl nedefinovaný (mohl by být snadno ovlivněn jakýmkoli náhodným blízkým elektrickým polem, rušením atd.)
![image](https://github.com/user-attachments/assets/6151bb0e-39b5-4151-88ce-77ba36529f5d)


 
 

	○ Podmínka if - else
	○ Cyklus while - čekání na stisk tlačítka

	○ Pin jako vstup, pullup/pulldown
	○ Čtení z registru PINx PORTx na pullup
		○ Vymaskovat do podmínky if ((PINK & (1<<7))==0)
Debouncing![image](https://github.com/user-attachments/assets/39e64e8a-0c5b-4b7a-acba-ad14a843e007)
