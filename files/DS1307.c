/*
 * DS1307.c
 *
 * Created: 17. 10. 2013 9:48:27
 * Author: Ondrej Tereò
 * Email: teren@eeas.cz
 * Company: Embedded Electronics & Solutions, s.r.o.
 */ 

#include "DS1307.h"

// funkcia pre vycitanie aktualnych hodin
char DS1307_get_hours()
{
	return DS1307_time_conv2dec(i2c_read_data(0x02, DS1307_ADDRESS));
}

// funkcia pre vycitanie aktualnych minut
char DS1307_get_minutes()
{
	return DS1307_time_conv2dec(i2c_read_data(0x01, DS1307_ADDRESS));
}

// funkcia pre vycitanie aktualnych sekund
char DS1307_get_seconds()
{
	return DS1307_time_conv2dec(i2c_read_data(0x00, DS1307_ADDRESS));
}

// funkcia pre vycitanie aktualneho dna v tyzdni
char DS1307_get_day()
{
	return DS1307_time_conv2dec(i2c_read_data(0x03, DS1307_ADDRESS));
}

// funkcia pre vycitanie aktualneho datumu (dna v mesiaci)
char DS1307_get_date()
{
	return DS1307_time_conv2dec(i2c_read_data(0x04, DS1307_ADDRESS));
}

// funkcia pre vycitanie aktualneho mesiaca
char DS1307_get_month()
{
	return DS1307_time_conv2dec(i2c_read_data(0x05, DS1307_ADDRESS));
}

// funkcia pre vycitanie aktualneho roku
char DS1307_get_year()
{
	return DS1307_time_conv2dec(i2c_read_data(0x06, DS1307_ADDRESS));
}

// funkcia pre nastavenie hodin
void DS1307_set_hours(char value)
{
	i2c_write_data(DS1307_time_conv2hex(value), 0x02, DS1307_ADDRESS);
}

// funkcia pre nastavenie minut
void DS1307_set_minutes(char value)
{
	i2c_write_data(DS1307_time_conv2hex(value), 0x01, DS1307_ADDRESS);
}

// funkcia pre nastavenie sekund
void DS1307_set_seconds(char value)
{
	i2c_write_data(DS1307_time_conv2hex(value), 0x00, DS1307_ADDRESS);
}

// funkcia pre nastavenie dna v tyzdni
void DS1307_set_day(char value)
{
	i2c_write_data(DS1307_time_conv2hex(value), 0x03, DS1307_ADDRESS);
}

// funkcia pre nastavenie datumu (dna v mesiaci)
void DS1307_set_date(char value)
{
	i2c_write_data(DS1307_time_conv2hex(value), 0x04, DS1307_ADDRESS);
}

// funkcia pre nastavenie mesiaca
void DS1307_set_month(char value)
{
	i2c_write_data(DS1307_time_conv2hex(value), 0x05, DS1307_ADDRESS);
}

// funkcia pre nastavenie roku
void DS1307_set_year(char value)
{
	i2c_write_data(DS1307_time_conv2hex(value), 0x06, DS1307_ADDRESS);
}

// funkcia vykonavajuca prevod cisla z tvaru 0x12 na 12 dekadickych
char DS1307_time_conv2dec(char value)
{
	char output;
	
	output = (value & 0x0F);
	output += ((value >> 4) & 0x0F) * 10;
	
	return output;
}

// funkcia vykonavajuca prevod cisla z tvaru 12 dekadickych na 0x12
char DS1307_time_conv2hex(char value)
{
	char output;
	
	output = (value / 10) << 4;
	output += value % 10;
	
	return output;
}