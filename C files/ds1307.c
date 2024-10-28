/*
 * ds1307.c
 *
 *  Created on: 
 *      Author:
 */

#include "ds1307.h"
#include "main.h"
#include "stdbool.h"

I2C_HandleTypeDef *i2cDS1307;

/* Init the RTC DS1307 for starting the clock*/
void initDS1307(I2C_HandleTypeDef *hi2c) {
	rtc_hi2c  = hi2c;
	startDS1307(true);
}

/* Start to RTC DS1307 if start -> TRUE then start, if start -> FALSE,then stop*/
void startDS1307(bool start) {
    uint8_t controlReg = getTimeValue(RTC_SECOND);
    if (start) {
        controlReg &= ~(1 << 7); // CH (Clock Halt) bitini sıfırla
    } else {
        controlReg |= (1 << 7);  // CH bitini bir yap
    }
    setTimeValue(RTC_SECOND, controlReg);
}


/*
 * State of the RTC DS1307, it checks whether time starts or not start
 * 0x80 = 10000000, it is used for protecting the 7th bit, then zeros the other bits.
 * then it shifts 7 time to right, then the function returns 1 or 0.
 * it is used for flag.
 * */

uint8_t stateDS1307(void) {
    return (getDS1307(RTC_SECOND) & 0x80) ? 0 : 1;
}


/* Sets the bytes to targeted register of RTC
 *	registerDS -> address of register
 * 	value -> value in the register
 * 	*/
void setTimeValue(uint8_t registerAddr, uint8_t value) {
    HAL_StatusTypeDef status = HAL_I2C_Mem_Write(rtc_hi2c, RTC_I2C, registerAddr, I2C_MEMADD_SIZE_8BIT, &value, 1, RTC_TIMEOUT);
    if (status != HAL_OK) {
        // Hata durumunda loglama veya hata işlemi yapılabilir
    }
}

/* gets the byte in targeted register of RTC
 * registerDS -> reg address
 * it returns the value of in the register.
 * */
uint8_t getTimeValue(uint8_t registerAddr) {
    uint8_t value = 0;
    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(rtc_hi2c, RTC_I2C, registerAddr, I2C_MEMADD_SIZE_8BIT, &value, 1, RTC_TIMEOUT);
    if (status != HAL_OK) {
        // Hata durumunda loglama veya hata işlemi yapılabilir
    }
    return value;
}

/*
 * it converts the binary value in registers to decimal number
 * range is 0 to 255
 * */
uint16_t convertDEC(uint16_t binaryNum) {
	return (((binaryNum & 0xf0) >> 4) * 10) + (binaryNum & 0x0f);
}

/*
 * it converts the decimal valu to binary number for registers.
 * */
uint16_t convertBCD(uint16_t decimalNum) {
    return ((decimalNum / 10) << 4) | (decimalNum % 10);
}

void getRTC(RTC_TimeDate *timeDate) {
    timeDate->seconds = convertDEC(getTimeValue(RTC_SECOND));
    timeDate->minutes = convertDEC(getTimeValue(RTC_MINUTE));
    timeDate->hours   = convertDEC(getTimeValue(RTC_HOUR));
    timeDate->day     = convertDEC(getTimeValue(RTC_DATE));
    timeDate->month   = convertDEC(getTimeValue(RTC_MONTH));
    timeDate->year    = 2000 + convertDEC(getTimeValue(RTC_YEAR));
}

void setRTC(RTC_TimeDate *timeDate) {
    setTimeValue(RTC_SECOND, convertBCD(timeDate->seconds));
    setTimeValue(RTC_MINUTE, convertBCD(timeDate->minutes));
    setTimeValue(RTC_HOUR, convertBCD(timeDate->hours));
    setTimeValue(RTC_DATE, convertBCD(timeDate->day));
    setTimeValue(RTC_MONTH, convertBCD(timeDate->month));
    setTimeValue(RTC_YEAR, convertBCD(timeDate->year % 100));
}


void setDAY(uint8_t date) {
    setTimeValue(RTC_DATE, convertBCD(date));
}

void setMONTH(uint8_t month) {
    setTimeValue(RTC_MONTH, convertBCD(month));
}

void setYEAR(uint16_t year) {
    setTimeValue(RTC_YEAR, convertBCD(year % 100));
}

void setHOUR(uint8_t hour) {
    setTimeValue(RTC_HOUR, convertBCD(hour));
}

void setMINUTE(uint8_t minute) {
    setTimeValue(RTC_MINUTE, convertBCD(minute));
}

void setSECONDS(uint8_t second) {
    setTimeValue(RTC_SECOND, convertBCD(second));
}


