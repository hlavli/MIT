# Datová komunikace, UART
Pokud potřebujeme, aby si mikroprocesor vyměňoval data s jinými součástkami nebo mikroprocesory, existuje mnoho typů komunikace, které můžeme použít. Liší se rychlostí, počtem použitých vodičů, odolností proti rušení atd. Často používanými komunikačními sběrnicemi jsou [UART, SPI a I2C](https://www.hibit.dev/posts/102/communication-protocols-uart-i2c-and-spi). My se v dnešním cvičení budeme věnovat UARTu, ale předtím si ukážeme základní typy dělení komunikačních sběrnic a protokolů.

## Komunikace sériová vs paralelní
<img src="https://github.com/user-attachments/assets/b722c856-ee3a-4386-9277-d220b1fbb68c" width="600"/>

## Komunikace synchronní vs asynchronní
<img src="https://github.com/user-attachments/assets/f093542f-f7f0-45c8-bd6f-ed4ccfbbfce0" width="600"/>

*Zdroj obrázku: https://docs.madmachine.io/learn/advanced/uart*

## Komunikace podle směru přenosu dat
![image](https://github.com/user-attachments/assets/7a229ec2-9fcf-4323-990d-89079ab7ef44)

*Zdroj obrázku: http://www.lboptic.com/index.php?m=content&c=index&a=show&catid=20&id=10*


## UART 
UART (Universal Asynchronous Receiver / Transmitter)  definuje protokol neboli sadu pravidel pro výměnu sériových dat mezi dvěma zařízeními. UART je velmi jednoduchý a používá pouze dva vodiče mezi vysílačem a přijímačem pro obousměrný přenos. Oba konce musí mít také společné uzemnění (GND).

![image](https://github.com/user-attachments/assets/df3e67e7-d689-404f-a48b-13965745c909)

![image](https://github.com/user-attachments/assets/c544e539-6958-4283-9fec-905060d4e42c)

*Zdroj obrázku: https://docs.madmachine.io/learn/advanced/uart*

## Zapojení v přípravku
Mikrokontroler ATmega 2560 má celkem 4 USART periferie. Dvě z nich jsou připojeny k převodníku na USB. Abychom nemuseli připojovat další kabel, budeme používat stejný USART jako pro programování. Podle schématu je to USART1, který je připojen k pinům D2 (RXD1) a D3 (TXD1). Proto i všechny registry, které budeme nastavovat, budou mít index 1 (UDR1, UCSR1A, atd.)

![image](https://github.com/user-attachments/assets/bb4b297b-66aa-44eb-9781-6a5e30dd114a)

## Důležité registry
![image](https://github.com/user-attachments/assets/9a27dede-da8f-4820-b290-bea24ab93c3e)

Datový registr, kam ukládáme bajt, který chceme odeslat, popřípadě z něj čteme přijatý bajt. Ve skutečnosti jsou to dva registry, jeden pro vysílání, druhý pro příjem, ale používají jedno označení.

![image](https://github.com/user-attachments/assets/687690ba-6405-40eb-96d5-a907f341005a)

USART Baud Rate Register, 16 bitový registr pro nastavení rychlosti přenosu (baudrate).

![image](https://github.com/user-attachments/assets/ec57c6d4-c3ef-4196-bfc7-477cc56750ea)

**UDREn**: USART Data Register Empty- Nastaví se automaticky do jedničky, když se předchozí bajt odeslal a můžeme tak do registru UDRn zapsat další bajt k odeslání

**RXCn**: USART Receive Complete - tento bit se automaticky nastaví do jedničky, když je přijat nový bajt

![image](https://github.com/user-attachments/assets/151d7de2-e425-4be7-b3c1-563f8e9fefe8)

**RXENn**: Receiver Enable - Zápisem jedničky se aktivuje příjem

**TXENn**: Transmitter Enable - Zápisem jedničky se aktivuje vysílání

![image](https://github.com/user-attachments/assets/d766fefa-4803-4fb0-9147-dc7e80c0d228)

**UCSZn1:0**: Kombinace bitů UCSZn1:0 a bitu UCSZn2 v registru UCSRnB nastavuje počet datových bitů (Character Size) v jednom datovém rámci

![image](https://github.com/user-attachments/assets/b5e166ab-999c-4a4f-9989-d929c988d689)


## Přidání pluginu Terminal do Microchip Studia
Abychom mohli data, která z procesoru odesíláme přes UART zobrazit v počítači, potřebujeme k tomu vhodný program. Mohli bychom použít Serial Monitor v Arduino IDE, ale lepší možnost je doinstalovat do Microchip Studia plugin Terminal. Pokud ho v Microchip Studiu ještě nemáte, postupujte podle návodu:

**1.** Stáhněte si plugin [Terminal for Atmel Studio](https://gallery.microchip.com/api/v2/package/EFC4C002-63A3-4BB9-981F-0C1ACAF81E03/2.8.4)

**2.** Otevřete instalační soubor pomocí programu Microsoft Visual Studio Version selector
    ![image](https://github.com/user-attachments/assets/918b44e8-5433-4370-9059-d90db87c569c)

**3.** Zavřete a znovu spusťte Microchip Studio

**4.** V menu View byste měli mít volbu Terminal

![image](https://github.com/user-attachments/assets/89325ab7-1b79-4545-8a7f-890498b3fdbd)



## Použití UARTu

```c
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <stdio.h>

#define BAUDRATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUDRATE * 16UL))) - 1)

// Funkce pro inicializaci UART perferie
void UART_init()
{
	UBRR1 = BAUD_PRESCALER; // Nastavit předděličku pro požadovaný baudrate
	UCSR1C = ((1 << UCSZ11)|(1<<UCSZ10));   // 8 datových bitů, žádná parita, 1 stop bit
	UCSR1B = ((1<<RXEN1)|(1<<TXEN1));       // Povolit příjem a vysílání
}

//Funkce pro odeslání jednoho znaku
void UART_send( unsigned char data)
{
// Doplňte kód
}

// Funkce pro příjem jednoho znaku
unsigned char UART_receive( void )
{
// Doplňte kód
}

// Funkce pro odeslání řetězce znaků
void UART_putstring(char* StringPtr)
{
    while(*StringPtr != 0x00)
    {
        UART_send(*StringPtr);
        StringPtr++;
    }
}


// Hlavní program
int main(void)
{
	UART_init();

	while (1) 
	{
	}
}
```


## Úkoly
**1.** Doplňte implementaci funkcí pro odeslání a příjem znaku

![image](https://github.com/user-attachments/assets/f671b965-2fd4-4154-a7ac-1089f3acd899)

**2.** Pomocí funkce UART_send() posílejte střídavě každou sekundu znaky 'a' a 'b'. Přijatá data zobrazte v okně Terminal v Microchip Studiu.

**3.** Pošlete pomocí funkce UART_putstring() textový řetězec. Data přijímejte v Microchip studiu v Terminal window.

**4.** Pomocí funkce UART_receive() přijímejte jeden bajt z počítače. Pokaždé když procesor přijme bajt, zapíše jeho hodnotu na PORT F a tím ho zobrazí na LEDkách. Nezapomeňte nastavit PORTF jako výstup. Přepněte si v okně Terminal posílání HEX namísto ASCII.

![image](https://github.com/user-attachments/assets/b0411a71-8153-41cd-92e5-8128129ca96f)


**5.** Propojte dva přípravky přes UART. Při stisku klávesy na jednom přípravku se rozsvítí LEDky na druhém přípravku. 


## Další užitečné zdroje informací
[UART Tutorial](https://www.electronicwings.com/avr-atmega/atmega1632-usart)

[Video UART a digitální komunikace](https://www.youtube.com/watch?feature=shared&v=Af6wO4QX28E)

[Další UART Tutorial](https://learn.sparkfun.com/tutorials/serial-communication)


### [Zpět na obsah](README.md)
