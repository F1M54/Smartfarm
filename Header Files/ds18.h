/*
 * ds18.h
 *
 *  Created on:
 *      Author:
 */

#ifndef INC_DS18_H_
#define INC_DS18_H_

#define DS18B20_PIN GPIO_PIN_7
#define DS18B20_PORT GPIOE

void outputSet(GPIO_TypeDef *GPIOx, uint16_t pin);
void inputSet(GPIO_TypeDef *GPIOx, uint16_t pin);
uint8_t startDS(void);
void writeDS(uint8_t data);
uint8_t readDS(void);
uint8_t checkSensor(void);
void readWaterTemp(float *temperature);

#endif /* INC_DS18_H_ */
