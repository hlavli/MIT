/*
 * i2c.h
 *
 * Created: 17. 10. 2013 9:12:52
 * Author: Ondrej Tereò
 * Email: teren@eeas.cz
 * Company: Embedded Electronics & Solutions, s.r.o.
 */ 

#ifndef I2C_H_
#define I2C_H_

#include <util/delay.h>
#include <avr/io.h>

void i2c_ini();
void i2c_write_data(char data, char address, char chip_address);
char i2c_read_data(char address, char chip_address);


#endif /* I2C_H_ */