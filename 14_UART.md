# Datová komunikace, UART
Pokud potřebujeme, aby si mikroprocesor vyměňoval data s jinými součástkami nebo mikroprocesory, existuje mnoho typů komunikace, které můžeme použít. Liší se rychlostí, počtem použitých vodičů, odolností proti rušením atd. Často používanými komunikačními sběrnicemi jsou [UART, SPI a I2C](https://www.hibit.dev/posts/102/communication-protocols-uart-i2c-and-spi). My se v dnešním cvičení budeme věnovat UARTu, ale předtím si ukážeme základní typy dělení komunikačních sběrnic a protokolů.

## Komunikace sériová vs paralelní
<img src="https://github.com/user-attachments/assets/b722c856-ee3a-4386-9277-d220b1fbb68c" width="600"/>

## Komunikace synchronní vs asynchronní
<img src="https://github.com/user-attachments/assets/f093542f-f7f0-45c8-bd6f-ed4ccfbbfce0" width="600"/>

*Zdroj obrázku: https://docs.madmachine.io/learn/advanced/uart*

## Komunikace podle směru přenosu dat
![image](https://github.com/user-attachments/assets/7a229ec2-9fcf-4323-990d-89079ab7ef44)

*Zdroj obrázku: http://www.lboptic.com/index.php?m=content&c=index&a=show&catid=20&id=10*


## UART 
UART (universal asynchronous receiver / transmitter)  definuje protokol neboli sadu pravidel pro výměnu sériových dat mezi dvěma zařízeními. UART je velmi jednoduchý a používá pouze dva vodiče mezi vysílačem a přijímačem pro obousměrný přenos. Oba konce musí mít také společné uzemnění (GND).

![image](https://github.com/user-attachments/assets/df3e67e7-d689-404f-a48b-13965745c909)

![image](https://github.com/user-attachments/assets/c544e539-6958-4283-9fec-905060d4e42c)

*Zdroj obrázku: https://docs.madmachine.io/learn/advanced/uart*


## Důležité registry
1. **UDR**: USART Data Register - datový registr, kam ukládáme bajt, který chceme odeslat, popřípadě z něj čteme přijatý bajt. Ve skutečnosti jsou to dva registry, jeden pro vysílání, druhý pro příjem, ale používají jedno označení.

3. **UBRR**: USART Baud Rate Register, this is a 16-bit register used for the setting baud rate.


![image](https://github.com/user-attachments/assets/9cbfa471-2743-433b-ae33-8aa2f83c389f)

**UDREn**: USART Data Register Empty- Nastaví se automaticky do jedničky, když se předchozí bajt odeslal a můžeme tak do registru UDRn zapsat další bajt k odeslání

**RXCn**: USART Receive Complete - tento bit se automaticky nastaví do jedničky, když je přijat nový bajt

![image](https://github.com/user-attachments/assets/866889a6-f2ca-461c-ab52-81cf4cb518bb)

**RXENn**: Receiver Enable - Zápisem jedničky se aktivuje příjem

**TXENn**: Transmitter Enable - Zápisem jedničky se aktivuje vysílání

![image](https://github.com/user-attachments/assets/945f0ace-4812-4466-b15f-0ce4130af783)

**UCSZn1:0**: Kombinace bitů UCSZn1:0 a bitu UCSZn2 v registru UCSRnB nastavuje počet datových bitů (Character Size) v jednom datovém rámci

![image](https://github.com/user-attachments/assets/bced14bb-1a4e-4121-ba5c-1f0983a2f354)


## Přidání Terminal pluginu do Microchip Studia
Abychom mohli data, která z procesoru odesíláme přes UART zobrazit v počítači, potřebujeme k tomu vhodný program. Mohli bychom použít serial monitor v Arduino IDE, ale lepší možnost je doinstalovat do Microchip studia plugin Terminal. Pokud ho ještě v Microchip studiu nemáte, postupujte podle návodu:

1. Stáhněte si plugin [Terminal for Atmel Studio](https://gallery.microchip.com/api/v2/package/EFC4C002-63A3-4BB9-981F-0C1ACAF81E03/2.8.4)

2. Otevřete instalační soubor pomocí programu Microsoft Visual Studio Version selector
    ![image](https://github.com/user-attachments/assets/918b44e8-5433-4370-9059-d90db87c569c)

3. Zavřete a znovu spusťte Microchip Studio

4. V menu View byste měli mít volbu Terminal

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
void UART_init( unsigned char data)
{
	UBRR1 = BAUD_PRESCALER;// Set the baud rate prescale rate register
	UCSR1C = ((1 << UCSZ11)|(1<<UCSZ10));   // Set frame format: 8data, 1 stop bit
	UCSR1B = ((1<<RXEN1)|(1<<TXEN1));       // Enable receiver and transmitter
}

//Funkce pro odeslání jednoho znaku
void UART_send( unsigned char data)
{
// Doplňte kód
}

// Funkce pro příjem jednoho znaku
unsigned char UART_Receive( void )
{
// Doplňte kód
}

// Funkce pro odeslání rětězce znaků
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
	USART_init();

	while (1) 
	{
	}
}
```


## Úkoly
1. Doplňte implementaci funkcí pro odeslání a příjem znaku

![image](https://github.com/user-attachments/assets/fc405583-d257-412b-9bac-5fce2120cd08)

2. Posílejte pomocí funkce USART_send() střídavě jednou za sekundu znaky 'a' a 'b'. Data přijímejte v Microchip studiu v Terminal window.
3. Pošlete pomocí funkce USART_putstring() textový řetězec. Data přijímejte v Microchip studiu v Terminal window.
4. Pomocí funkce USART_Receive() přijímejte jeden bajt z počítače. Pokaždé když procesor přijme bajt, zapíše jeho hodnotu na PORT F a tím ho zobrazí na LEDkách. Nezapomeňte nastavit PORTF jako výstup. 
5. Propojte dva přípravky přes UART. Při stisku klávesy na jednom přípravku se rozsvítí LEDky na druhém přípravku. 


## Další užitečné zdroje informací
[UART Tutorial](https://www.electronicwings.com/avr-atmega/atmega1632-usart)

[Video UART a digitální komunikace](https://www.youtube.com/watch?feature=shared&v=Af6wO4QX28E)

[Další UART Tutorial](https://learn.sparkfun.com/tutorials/serial-communication)


### [Zpět na obsah](README.md)
