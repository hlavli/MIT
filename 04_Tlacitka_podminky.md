# Práce s tlačítky

V předchozích cvičeních jsme se naučili nastavit piny jako výstupní pomocí registrů DDRx a měnit jejich stav pomocí registrů PORTx. V této kapitole se naučíme nastavit piny jako vstupní a číst jejich stav. Použijeme k tomu tlačítka na našem přípravku.

## Jak funguje tlačítko, pull-up odpory
Ze schématu přípravku můžeme zjistit, že tlačítka jsou připojena na port K. Piny portu K jsou připojeny přes relativně velký odpor (4.7kΩ) k Vcc, tedy k +5V. Pokud tlačítko není stisknuto, "naměří" procesor na pinu 5V a vyhodnotí to jako logickou jedničku. 
Pokud ovšem tlačítko stiskneme, pin tím připojíme bez odporu přímo na zem. Procesor pak na pinu "naměří" 0V a vyhodnotí to jako logickou nulu. Těm 4.7kΩ rezistorům se říká pull-up odpory. Jsou důležité proto, aby i v případě, že tlačítko není stisknuto, byla na pinu jasně definovaná úroveň. Bez těchto odporů by v nestisknutém stavu pin nebyl k ničemu připojen a jeho stav by byl nedefinovaný (mohl by být snadno ovlivněn jakýmkoli náhodným blízkým elektrickým polem, rušením atd.)

![image](https://github.com/user-attachments/assets/6151bb0e-39b5-4151-88ce-77ba36529f5d)


## Čtení stavu pinu

Pro nastavení logické úrovně pinu procesoru jsme používali registr PORTx. Ovšem pozor, tento registr je pouze výstupní, tedy slouží k zápisu na pin, ale ne k jeho čtení! Ke čtení stavu pinu slouží jiný registr - PINx. V našem případě chceme číst stav tlačítek na portu K, tedy použijeme registr PINK. Jeho přečtením získáme stav všech pinů. Nás ale obvykle zajímá stav pinů jednotlivě, např. chceme zjistit, zda je stisknuto tlačítko úplně vlevo na přípravku (SW7).

Nastavíme všechny piny portu K jako vstupy

 ```c
DDRK = 0x00;
```

Abychom z celého registru PINK vybrali pouze stav jednoho tlačítka, můžeme použít známý výraz s logickým součinem a rotací:

 ```c
if((PINK & (1<<7))==0){ 
// udělej něco když je na PK7 log.0         
}  
```

nebo opačně:

 ```c
if(PINK & (1<<7) != 0){ 
// udělej něco když je na PK7 log.1 
}
```


Pokud chceme někde náš program zastavit a pokračovat až po stisku tlačítka, můžeme použít prázdný cyklu while:

 ```c
while(PINK & (1<<7) != 0){ 
// čekej, dokud je na PK7 log.1 tedy čekej, dokud tlačítko není stisknuto
//po stisku tlačítka tato smyčka končí a vykoná se program pod ní
}
```

Nebo naopak, můžeme něco dělat pouze po dobu, kdy je tlačítko stisknuto. Když tlačítko pustíme,cyklus skončí

 ```c
while(PINK & (1<<7) == 0){ 
// příkazy v cyklu se budou vykonávat dokud je pin 7 portu K v logické nule (tlačítko stisknuto) 
}
```

## Příklad s rozsvěcením LEDky

```c
#include <avr/io.h> // soubor definicemi adres registru, abychom mohli pouzivat symbolicke nazvy jako "PORTB" namisto ciselne adresy registru
#define F_CPU 16000000 // definice frekvence procesoru, v nasem pripade 16MHz aby spravne fungovala funkce delay
#include <util/delay.h> // pridani knihovny s funkci delay

int main()
{
	DDRK = 0b00000000; // vsechny piny portu K jako vstupy
	DDRF = 0b11111111; // vsechny piny portu F jako vystupy

	// nekonecna smycka
	while(1)
	{
		if((PINK & (1<<7)) == 0) // pokud je tlacitko SW7 stisknute
		{
			PORTF |= (1 << 7); // rozsvit LED7
		}
		else { // pokud tlacitko neni stisknuto
			PORTF &= ~(1 << 7); // zhasni LEDku
		}
	}
}

```

 
## Ošetření zákmitů - debouncing
Při stisku mechanických tlačíek zpravidla dochází k něžádoucímu jevu zákmitů, anglicky bouncing. To se projeví tak, že změna stavu nízké do vysoké úrovně neproběhne jednorázovým skokem, ale po krátkou dodu může úroveň "přeskakovat" tam a zpět. Je to způsobeno mechanickými vlastnostmi kontaktů tlačítka, má na to vliv např. síla a rychlost stisku. 

![image](https://www.nuvation.com/sites/default/files/blog/Switch%20Debouncing%20for%20Electronic%20Product%20Designs/Switch_Debouncing_Circuit_Waveform.jpg)

*Zdroj obrázku : https://www.nuvation.com/resources/article/switch-debouncing-electronic-product-designs*

Tento jev nám působí problémy, protože pokud například chceme programme detekovat stisk tlačítka, jako změnu z 1 do 0, pak kvůli zákmitům můžeme namísto jednoho stisku tlačítka detekovat falešně třebba deset stisků. Proto musíme tento jev ošetřit tak, aby nám nepůsobil problémy. To lze buď hardwarově, nejčastěji připojením kondenzátoru paralelně k tlačítku. Kondenzátor způsobí, že napětí na tlačítku se bude měnit pomaleji (zaoblí se hrana). Nebo lze zákmity odfiltrovat softwarově.

```c
void loop() {

  // Read the button value. We assume a pull-down resistor button configuration so
  // the button will be HIGH when pressed and LOW when not pressed
  int buttonVal = digitalRead(BUTTON_INPUT_PIN);

  // Wait to check the button state again
  delay(DEBOUNCE_WINDOW);

  // read the button value again
  int buttonVal2 = digitalRead(BUTTON_INPUT_PIN);

  // If buttonVal and buttonVal2 are the same, then we are in steady state
  // If this stead state value does not match our _lastButtonVal, then
  // a transition has occurred and we should save the new buttonVal
  // This works both for open-to-close transitions and close-to-open transitions
  if(buttonVal == buttonVal2 && _savedButtonVal != buttonVal){
    _savedButtonVal = buttonVal;
  }

  // Write out HIGH or LOW
  digitalWrite(LED_OUTPUT_PIN, _savedButtonVal);
}
```

