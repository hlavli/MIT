# Datová komunikace
Pokud potřebujeme, aby si mikroprocesor vyměňoval data s jinými součástkami nebo mikroprocesory, existuje mnoho typů komunikace, které můžeme použít. Liší se rychlostí, počtem použitých vodičů, odolností proti rušením atd. Často používanými komunikačními sběrnicemi jsou [UART, SPI a I2C](https://www.hibit.dev/posts/102/communication-protocols-uart-i2c-and-spi). My se v dnešním cvičení budeme věnovat UARTu, ale předtím si ukážeme základní typy dělení komunikačních sběrnic a protokolů.

## Komunikace sériová vs paralelní
<img src="https://github.com/user-attachments/assets/b722c856-ee3a-4386-9277-d220b1fbb68c" width="700"/>

## Komunikace synchronní vs asynchronní
<img src="https://github.com/user-attachments/assets/f093542f-f7f0-45c8-bd6f-ed4ccfbbfce0" width="700"/>

*Zdroj obrázku: https://docs.madmachine.io/learn/advanced/uart*

## Komunikace podle směru přenosu dat
![image](https://github.com/user-attachments/assets/7a229ec2-9fcf-4323-990d-89079ab7ef44)

*Zdroj obrázku: http://www.lboptic.com/index.php?m=content&c=index&a=show&catid=20&id=10*


## UART 
-Rx, Tx, baudrate, startbit, stopbit, parita

![image](https://github.com/user-attachments/assets/c544e539-6958-4283-9fec-905060d4e42c)

*Zdroj obrázku: https://docs.madmachine.io/learn/advanced/uart*


## Registry
1. UDR: USART Data Register
It has basically two registers, one is Tx. Byte and the other is Rx Byte. Both share the same UDR register. Do remember that, when we write to the UDR reg. Tx buffer will get written and when we read from this register, Rx Buffer will get read. Buffer uses the FIFO shift register to transmit the data.

2. UCSRA: USART Control and Status Register A. As the name suggests, is used for control and status flags. In a similar fashion, there are two more USART control and status registers, namely UCSRB and UCSRC.

3. UBRR: USART Baud Rate Register, this is a 16-bit register used for the setting baud rate.


## Úkoly
1. Nakonfigurujte na mikrokontroleru UART pro rychlost 9600. Připojte přípravek k počítači přes **USB port, který je na přípravku napravo**. Posílejte každou sekundu zprávu do počítače. V počítači můžete pro komunikaci použít např. serial monitor v Arduino IDE.
2. Napište program, který přijme 1 bajt na UARTu a zapíše ho na PORT F. Na portu F máme připojeny LEDky, takže ho nadstavte jako výstupní,a ť vidíme přijatý bajt na LEDkách.
3. Propojte dva přípravky přes UART. Při stisku klávesy na jednom přípravku se rozsvítí LEDky na druhém přípravku. 


## Další užitečné zdroje informací:
[UART Tutorial](https://www.electronicwings.com/avr-atmega/atmega1632-usart)

[Video UART a digitální komunikace](https://www.youtube.com/watch?feature=shared&v=Af6wO4QX28E)

[Další UART Tutorial](https://learn.sparkfun.com/tutorials/serial-communication)


### [Zpět na obsah](README.md)
