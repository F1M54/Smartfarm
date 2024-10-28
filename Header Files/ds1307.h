/*
 * ds1307.h
 *
 *  Created on:
 *      Author:
 */

#ifndef INC_DS1307_H_
#define INC_DS1307_H_
#include "main.h"
#include "stdbool.h"


// DS1307 I2C adresi ve register tanımları
#define RTC_I2C 	0x68<<1  // I2C address
#define RTC_SECOND 	0x00
#define RTC_MINUTE 	0x01
#define RTC_HOUR  	0x02
#define RTC_DATE   		0x04
#define RTC_MONTH  		0x05
#define RTC_YEAR   		0x06
#define RTC_UTC_HOUR	0x08
#define RTC_CENTURY 	0x10
#define RTC_TIMEOUT		1000

// Zaman ve tarih yapısı (struct)
typedef struct {
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day;
    uint8_t month;
    uint16_t year;
} RTC_TimeDate;

// Fonksiyon prototipleri
void initDS1307(I2C_HandleTypeDef *hi2c);
void startDS1307(bool start);
uint8_t stateDS1307(void);

// Modüler zaman ve tarih okuma/yazma fonksiyonları
void setTimeValue(uint8_t registerAddr, uint8_t value);
uint8_t getTimeValue(uint8_t registerAddr);

// BCD ve ondalık dönüştürme fonksiyonları
uint16_t convertDEC(uint16_t binaryNum);
uint16_t convertBCD(uint16_t decimalNum);

// Struct kullanarak zaman ve tarih okuma/ayarlama fonksiyonları
void getRTC(RTC_TimeDate *timeDate);
void setRTC(RTC_TimeDate *timeDate);

/*
uint8_t dayDS1307(uint8_t *day);
uint8_t monthDS1307(uint8_t *month);
uint16_t yearDS1307(uint16_t *year);
uint8_t hourDS1307(uint8_t *hour);
uint8_t minDS1307(uint8_t *minute);
uint8_t secDS1307(uint8_t *second);
uint8_t timezoneDS1307(uint8_t *timezone);
*/

// Tekil zaman/tarih ayarlama fonksiyonları
void setDAY(uint8_t date);
void setMONTH(uint8_t month);
void setYEAR(uint16_t year);

void setHOUR(uint8_t hour);
void setMINUTE(uint8_t minute);
void setSECONDS(uint8_t second);
void setTIMEZONE(int8_t hour);

#endif /* INC_DS1307_H_ */
