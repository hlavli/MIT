/*
 * DS1307.h
 *
 * Created: 17. 10. 2013 9:49:33
 * Author: Ondrej Tereò
 * Email: teren@eeas.cz
 * Company: Embedded Electronics & Solutions, s.r.o.
 */ 


#ifndef DS1307_H_
#define DS1307_H_

#include "i2c.h"

#define DS1307_ADDRESS 0xD0

char DS1307_get_hours();
char DS1307_get_minutes();
char DS1307_get_seconds();
char DS1307_get_day();
char DS1307_get_date();
char DS1307_get_month();
char DS1307_get_year();

void DS1307_set_hours(char value);
void DS1307_set_minutes(char value);
void DS1307_set_seconds(char value);
void DS1307_set_day(char value);
void DS1307_set_date(char value);
void DS1307_set_month(char value);
void DS1307_set_year(char value);

char DS1307_time_conv2dec(char value);
char DS1307_time_conv2hex(char value);

#endif /* DS1307_H_ */