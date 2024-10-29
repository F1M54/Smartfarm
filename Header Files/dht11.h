/*
 * dht11.h
 *
 *  Created on:
 *      Author
 */


#ifndef INC_DHT11_H_
#define INC_DHT11_H_

#include "main.h"

// DHT11 sensörünün bağlı olduğu pin ve port tanımları
#define DHT11_PIN GPIO_PIN_10
#define DHT11_PORT GPIOA

// DHT11 durum kodları
#define DHT11_OK          0
#define DHT11_ERR_TIMEOUT 1
#define DHT11_ERR_CHECK   2

/**
 * @brief DHT11 sensörünü başlatır.
 */
void dhtStart(void);

/**
 * @brief DHT11 sensörünün yanıt verip vermediğini kontrol eder.
 * @return DHT11_OK (0) - Yanıt alındı, DHT11_ERR_TIMEOUT (1) - Zaman aşımı, DHT11_ERR_CHECK (2) - Yanıt hatası
 */
uint8_t dhtCheck(void);

/**
 * @brief DHT11 sensöründen sıcaklık ve nem verilerini okur.
 * @return DHT11_OK (0) - Başarılı, DHT11_ERR_TIMEOUT (1) - Zaman aşımı, DHT11_ERR_CHECK (2) - Hatalı veri
 */
uint8_t dhtRead(void);

/**
 * @brief DHT11 sensöründen sıcaklık ve nem değerlerini alır.
 * @param temperature Pointer: Sıcaklık değerini tutacak değişken
 * @param humidity Pointer: Nem değerini tutacak değişken
 * @return DHT11_OK (0) - Başarılı, DHT11_ERR_TIMEOUT (1) - Zaman aşımı, DHT11_ERR_CHECK (2) - Hatalı veri
 */
uint8_t getDHT11(float *temperature, float *humidity);

#endif /* INC_DHT11_H_ */
