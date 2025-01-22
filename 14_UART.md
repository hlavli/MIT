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
-Rx, Tx, baudrate, startbit, stopbit, parita

![image](https://github.com/user-attachments/assets/df3e67e7-d689-404f-a48b-13965745c909)

![image](https://github.com/user-attachments/assets/c544e539-6958-4283-9fec-905060d4e42c)

*Zdroj obrázku: https://docs.madmachine.io/learn/advanced/uart*


## Důležité registry
1. **UDR**: USART Data Register
It has basically two registers, one is Tx. Byte and the other is Rx Byte. Both share the same UDR register. Do remember that, when we write to the UDR reg. Tx buffer will get written and when we read from this register, Rx Buffer will get read. Buffer uses the FIFO shift register to transmit the data.

3. **UBRR**: USART Baud Rate Register, this is a 16-bit register used for the setting baud rate.


![image](https://github.com/user-attachments/assets/9cbfa471-2743-433b-ae33-8aa2f83c389f)

**UDREn**: USART Data Register Empty
The UDREn Flag indicates if the transmit buffer (UDRn) is ready to receive new data. If UDREn is one, the buffer is
empty, and therefore ready to be written. The UDREn Flag can generate a Data Register Empty interrupt (see
description of the UDRIEn bit).
UDREn is set after a reset to indicate that the Transmitter is ready.

**RXCn**: USART Receive Complete
This flag bit is set when there are unread data in the receive buffer and cleared when the receive buffer is empty
(that is, does not contain any unread data). If the Receiver is disabled, the receive buffer will be flushed and consequently the RXCn bit will become zero. The RXCn Flag can be used to generate a Receive Complete interrupt (see
description of the RXCIEn bit).

![image](https://github.com/user-attachments/assets/866889a6-f2ca-461c-ab52-81cf4cb518bb)

**RXENn**: Receiver Enable n
Writing this bit to one enables the USART Receiver. The Receiver will override normal port operation for the RxDn
pin when enabled. Disabling the Receiver will flush the receive buffer invalidating the FEn, DORn, and UPEn
Flags.

**TXENn**: Transmitter Enable n
Writing this bit to one enables the USART Transmitter. The Transmitter will override normal port operation for the
TxDn pin when enabled. The disabling of the Transmitter (writing TXENn to zero) will not become effective until
ongoing and pending transmissions are completed, that is, when the Transmit Shift Register and Transmit Buffer
Register do not contain data to be transmitted. When disabled, the Transmitter will no longer override the TxDn
port.

![image](https://github.com/user-attachments/assets/945f0ace-4812-4466-b15f-0ce4130af783)
**UCSZn1:0**: Character Size
The UCSZn1:0 bits combined with the UCSZn2 bit in UCSRnB sets the number of data bits (Character SiZe) in a
frame the Receiver and Transmitter use.

![image](https://github.com/user-attachments/assets/bced14bb-1a4e-4121-ba5c-1f0983a2f354)


## Použití UARTu

```c
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <stdio.h>

#define BAUDRATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUDRATE * 16UL))) - 1)

//Funkce pro odeslání jednoho znaku
void USART_send( unsigned char data)
{
	//čekáme, dokud se nedokončí předchozí vysílání
	while(!(UCSR1A & (1<<UDRE1)));
	
	//zapíšeme bajt, který chceme odeslat
	UDR1 = data;
}

//Funkce pro odeslání textového řetězce
void USART_putstring(char* StringPtr)
{
// posílá znaky řetězce jeden po druhém, dokud nenarazí na konec řetězce (null)
	while(*StringPtr != 0x00)
	{
		USART_send(*StringPtr);
		StringPtr++;
	}
}

// Funkce pro příjem jednoho znaku
unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while (!(UCSR1A & (1<<RXC1)));
	/* Get and return received data from buffer */
	return UDR1;
}

// Hlavní program
int main(void)
{
	UBRR1 = BAUD_PRESCALER;// Set the baud rate prescale rate register
	UCSR1C = ((1 << UCSZ11)|(1<<UCSZ10));   // Set frame format: 8data, 1 stop bit
	UCSR1B = ((1<<RXEN1)|(1<<TXEN1));       // Enable receiver and transmitter

	while (1) 
	{
	}
}
```


## Úkoly
1. Posílejte pomocí funkce USART_send() střídavě jednou za sekundu znaky 'a' a 'b'. Data přijímejte v Microchip studiu v Terminal window.
2. Použijte funkci USART_putstring() k odeslání textového řetězce. Opět posílejte jednou z asekundu a zobrazujte v Terminal window.
3. Posílejte na UART zprávu "Counter: 0" kde číslo ve zprávě se bude pokaždíé o 1 zvyšovat. Kromě funkce USART_putstring() použijte i funkci sprinf() kterou jsme používali v [lekci s LCD displejem](https://tomaschovanec.github.io/MIT/12_LCD.html#ascii-k%C3%B3d-funkce-sprintf)
4. Pomocí funkce USART_Receive() přijímejte jeden bajt z počítače. Pokaždé když procesor přijme bajt, zapíše jeho hodnotu na PORT F a tím ho zobrazí na LEDkách. Nezapomeňte nastavit PORTF jako výstup. 
5. Propojte dva přípravky přes UART. Při stisku klávesy na jednom přípravku se rozsvítí LEDky na druhém přípravku. 


## Další užitečné zdroje informací:
[UART Tutorial](https://www.electronicwings.com/avr-atmega/atmega1632-usart)

[Video UART a digitální komunikace](https://www.youtube.com/watch?feature=shared&v=Af6wO4QX28E)

[Další UART Tutorial](https://learn.sparkfun.com/tutorials/serial-communication)


### [Zpět na obsah](README.md)
