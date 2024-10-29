/*
 * ds18.c
 *
 *  Created on:
 *      Author:
 *      add a pull up 4.7k resistor between data and vcc pin
 */
#include "main.h"
#include "ds18.h"

uint8_t Temp_byte1,Temp_byte2;
uint16_t TEMP;
float Temperature = 0;
uint8_t Presence = 0;

void outputSet(GPIO_TypeDef *GPIOx, uint16_t pin){
	GPIO_InitTypeDef ds;
	ds.Pin = pin;
	ds.Mode = GPIO_MODE_OUTPUT_PP;
	ds.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &ds);
}

void inputSet(GPIO_TypeDef *GPIOx, uint16_t pin){
	GPIO_InitTypeDef ds;
	ds.Pin = pin;
	ds.Mode = GPIO_MODE_INPUT;
	ds.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOx, &ds);
}


uint8_t startDS(void){
	uint8_t response = -1;
	outputSet(DS18B20_PORT, DS18B20_PIN);
	HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN,0);
	HAL_Delay(480);

	inputSet(DS18B20_PORT, DS18B20_PIN);
	HAL_Delay(80);

	if(!(HAL_GPIO_ReadPin(DS18B20_PORT, DS18B20_PIN))){
		response = 1;
	}
	HAL_Delay(400); // Wait for 400ms
	return response;
}

void writeDS(uint8_t data) {
    outputSet(DS18B20_PORT, DS18B20_PIN);

    for (int i = 0; i < 8; i++) {
        outputSet(DS18B20_PORT, DS18B20_PIN);
        HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_RESET);

        if ((data & (1 << i)) != 0) {
            HAL_Delay(1); // Delay for 1ms if writing a 1 bit
            inputSet(DS18B20_PORT, DS18B20_PIN);
            HAL_Delay(60); // Wait for 60ms to read
        } else {
            HAL_Delay(60); // Delay for 60ms if writing a 0 bit
            inputSet(DS18B20_PORT, DS18B20_PIN);
        }
    }
}

/**
 * @brief Reads a byte of data from the DS18B20 sensor.
 * @return uint8_t: The byte read from the sensor.
 */

uint8_t readDS(void){

	uint8_t value = 0;
	inputSet(DS18B20_PORT, DS18B20_PIN);

	for(int i = 0; i<8;i++){
		outputSet(DS18B20_PORT, DS18B20_PIN);
		HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN,GPIO_PIN_RESET);
		HAL_Delay(2);

		inputSet(DS18B20_PORT, DS18B20_PIN);
		if(HAL_GPIO_ReadPin(DS18B20_PORT, DS18B20_PIN)){

			value |= (1 << i);
		}
		HAL_Delay(60);
	}
	return value;
}

/**
 * @brief Reads the water temperature from the DS18B20 sensor.
 * @param temperature: Pointer to the float variable to store the temperature.
 */

void readWaterTemp(float *temperature){
		Presence = startDS();
		HAL_Delay(1);
		writeDS(0xCC);  // skip ROM
		writeDS(0x44);  // convert t
		HAL_Delay(800);

		Presence = startDS();
		HAL_Delay(1);
		writeDS(0xCC);  // skip ROM
		writeDS(0xBE);  // Read Scratch-pad

		Temp_byte1 = readDS();
		Temp_byte2 = readDS();
		TEMP = (Temp_byte2<<8)|(Temp_byte1);
		*temperature = (float) TEMP/16;
		HAL_Delay(3000);
}
