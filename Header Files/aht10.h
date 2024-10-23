/*
 * aht10.h
 *
 *  Created on:
 *      Author: 
 *      This file was created for AHT10 temp&hum sensor. The I2C protocol was used.
 */

#ifndef INC_AHT10_H_
#define INC_AHT10_H_

#include <stdint.h>
#include <stdbool.h>
#include "main.h"

#define ADRESS_AHT10 	0x39	// I2C address
#define TIMEOUT_I2C 	50 		// Timeout for I2C
#define ERROR_AHT10		0xFF	// return 255

#define INIT_AHT10			0xE1  // init command for AHT10/AHT15
#define START_MEAS_AHT10	0xAC  // start measurement command
#define NORMAL_CYCLE_AHT10	0xA8  // normal cycle mode command, no info in datasheet!!!

#define INIT_CAL_EN_AHT10	0x08  // load factory calibration coeff
#define DATA_MEAS_AHT10 	0x33
#define AHT10_DATA_NOP		0x00

#define MEAS_DELAY_AHT10	80    // 75 ms
#define PWR_DELAY_AHT10     40    // 20-40 ms
#define AHT10_CMD_DELAY		350   // 300 ms

#define FORCE_READ_AHT10	1  	// force to read data
#define USE_READ_AHT10		0 	// force to use data from previous read

void initAHT10(I2C_HandleTypeDef  *);

bool     beginAHT10();
uint8_t  readRawD();
float    readTemp(bool);
float    readHum(bool);
bool     modeNormal();

uint8_t  readStatus();
uint8_t  getCalBit(bool);
bool     FactoryCalCoeff_EN();
uint8_t  getBusyBit(bool);
void getAHT10(float *temp,float *hum);
#endif /* INC_AHT10_H_ */  Bu kodu satır satır açıkla
