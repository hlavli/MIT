/*
 * i2c.c
 *
 * Created: 17. 10. 2013 9:11:37
 * Author: Ondrej Tereò
 * Email: teren@eeas.cz
 * Company: Embedded Electronics & Solutions, s.r.o.
 */ 

#include "i2c.h"

// funkcia pre inicializaciu I2C
void i2c_ini()
{
	// nastavenie komunikacnej rychlosti na 100 kHz
	TWBR = 0xC0;	
}

// funkcia pre zapis dat na I2C zbernicu na definovanu adresu pamati a chipu
void i2c_write_data(char data, char address, char chip_address)
{
	// vygenerovanie START Condition a cakanie na flag
	TWCR = 0xA4;	
	while ((TWCR & 0x80) == 0);
	
	// pripravenie adresy chipu do datoveho registra, vygenerovanie WRITE Condition a cakanie na flag
	TWDR = chip_address;
	TWCR = 0x84;
	while ((TWCR & 0x80) == 0);
	
	// pripravenie adresy pamate do datoveho registra, vygenerovanie WRITE Condition a cakanie na flag
	TWDR = address;
	TWCR = 0x84;
	while ((TWCR & 0x80) == 0);
	
	// pripravenie dat do datoveho registra, vygenerovanie WRITE Condition a cakanie na flag
	TWDR = data;
	TWCR = 0x84;
	while ((TWCR & 0x80) == 0);
	
	// vygenerovanie STOP Condition
	TWCR = 0x94;
}

// funkcia pre citanie dat z I2C zbernice z definovanej adresy cipu a pamate
char i2c_read_data(char address, char chip_address)
{
	// vygenerovanie START Condition a cakanie na flag
	TWCR = 0xA4;
	while ((TWCR & 0x80) == 0);
	
	// pripravenie adresy chipu do datoveho registra, vygenerovanie WRITE Condition a cakanie na flag
	TWDR = chip_address;
	TWCR = 0x84;
	while ((TWCR & 0x80) == 0);
	
	// pripravenie adresy pamate do datoveho registra, vygenerovanie WRITE Condition a cakanie na flag
	TWDR = address;
	TWCR = 0x84;
	while ((TWCR & 0x80) == 0);
	
	// vygenerovanie STOP Condition
	TWCR = 0x94;
	
	// vygenerovanie START Condition a cakanie na flag
	TWCR = 0xA4;
	while ((TWCR & 0x80) == 0);
	
	// pripravenie adresy chipu do datoveho registra pricitanej o 1 (READ mode), vygenerovanie WRITE Condition a cakanie na flag
	TWDR = chip_address + 1;
	TWCR = 0x84;
	while ((TWCR & 0x80) == 0);
	
	// vyposielanie nulovych dat za ucelom citania dat zo zbernice
	TWDR = 0x00;
	TWCR = 0x84;
	while ((TWCR & 0x80) == 0);
	
	// vygenerovanie STOP Condition
	TWCR = 0x94;
	
	// vratenie prijatych dat
	return TWDR;
}