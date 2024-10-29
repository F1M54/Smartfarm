/*
 * dht11.c
 *
 *  Created on:
 *      Author:
 */

#include "main.h"
#include "ds18.h"
#include "dht11.h"

uint8_t temperature_integral, temperature_decimal, humidity_integral, humidity_decimal;
uint16_t temperature, humidity, checksum;
uint8_t presence1 = 0;

void dhtStart(void){
	outputSet(DHT11_PORT, DHT11_PIN);
	HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, 0);
	delay(18000);
	HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, 1);
	delay(20);
	inputSet(DHT11_PORT, DHT11_PIN);

uint8_t dhtCheck(void){
	uint8_t response1 = 0;
	delay(40);
	if(!(HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN)))
	{
		delay(80);
		if(HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN))	response1 = 1;
		else response1 = -1;
	}
	while((HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN)));
	return response1;
}

uint8_t dhtRead(void){

	 uint8_t result = 0;
	for( int i = 0; i<8;i++){
		while (!(HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN)));
		delay(40);
		if(!(HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN))){
			result &= ~(1<<(7-i));
		}
		else {
			result |= (1<<(7-i));
		}
		while(HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN));
	}
	return result;
}

void getDHT11(float *temperature, float *humidity){

	dhtStart();
	presence1 = dhtCheck();
	if (presence1 == -1) return -1; // Sensör yanıt vermediğinde -1 döndür

	    humidity_integral = dhtRead();
	    humidity_decimal = dhtRead();
	    temperature_integral = dhtRead();
	    temperature_decimal = dhtRead();
	    checksum = dhtRead();

	    // Checksum doğrulaması
	    if ((humidity_integral + humidity_decimal + temperature_integral + temperature_decimal) != checksum)
	        return -2; // Hatalı veri kontrol toplamı
	RH = RH_1;

	// Tam sayı ve ondalık kısımlarını birleştirerek sıcaklık ve nem değerlerini hesapla
	    *temperature = (float)temperature_integral + (float)temperature_decimal / 10;
	    *humidity = (float)humidity_integral + (float)humidity_decimal / 10;

	    HAL_Delay(1000);  // 1 saniye bekle
	    return 0; // Başarılı okuma
}
