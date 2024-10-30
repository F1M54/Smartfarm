/*
 * isik.c
 *
 *  Created on:
 *      Author:
 */

/*
 * system_lighting.c
 *
 *  Created on:
 *      Author:
 *      colors: 1 -> Green , 2 -> Red , 3 -> Blue 0 -> RESET state
 */
#include "isik.h"
#include "main.h"
#include "math.h"
/*
 * these parameters is used for configuration of led
 * flag for dma pwm
 * */
int lightFLAG = 0;
int Lednum;
extern TIM_HandleTypeDef htim8;
uint8_t channelFLAG = 0;
uint8_t brightness = 100;


void setColor(uint8_t* colorData, uint8_t red, uint8_t green, uint8_t blue) {
    uint8_t hState = (255 * brightness) / 100;
    colorData[1] = hState * green / 255;
    colorData[2] = hState * blue / 255;
}

void colorLS(uint8_t red, uint8_t green, uint8_t blue,  uint16_t ledNUMBER, uint32_t channel){

	uint8_t data_lighting[ledNUMBER][3];

	for (int i = 0; i < ledNUMBER; i++) {
	        setColor(data_lighting[i], red, green, blue, brightness);
	    }

	 uint16_t* pwmData = (uint16_t*) malloc(((24 * ledNUMBER) + 50) * sizeof(uint16_t));
	    if (pwmData == NULL) {
	        return; // Hata: Bellek tahsisi başarısız
	    }



	uint32_t index = 0;

		for(int i = 0 ; i<ledNUMBER; i++){
			uint32_t sendingcolor = ((data_lighting[i][0]<<16) | (data_lighting[i][1]<<8) | (data_lighting[i][2]));

			for (int j = 23; j >= 0; j--) {
			            pwmData[index++] = (sendingcolor & (1 << j)) ? 67 : 33;
			        }
		}


		for (int i = 0; i < 50; i++) {
		        pwmData[index++] = 0;
		    }


		HAL_TIM_PWM_Start_DMA(&htim8, channel, pwmData,index);
		if (channel == TIM_CHANNEL_2){
			channelFLAG = 1;
		}
		else if (channel == TIM_CHANNEL_3) {
			channelFLAG = 0;
		}

		uint32_t timeout = HAL_GetTick();
		while (!lightFLAG) {
		    // Timeout kontrolü
		    if ((HAL_GetTick() - timeout) > MAX_WAIT_TIME) {
		        break; // Zaman aşımı
		    }
		}

		lightFLAG = 0;

		 HAL_TIM_PWM_Stop_DMA(&htim8, channel);
		 HAL_TIM_Base_Stop(&htim8);

		 free(pwmData);
}

/*
 * Function to turn off WS2812B LEDs
 */
void turnOffLS(uint16_t ledNUMBER, uint32_t channel) {
    uint16_t pwmData[(24 * ledNUMBER) + 50];

    if (pwmData == NULL) {
           return; // Hata: Bellek tahsisi başarısız
       }


    for (uint32_t i = 0; i < (24 * ledNUMBER) + 50; i++) {
        pwmData[i] = 0;
    }


       for (uint32_t i = (24 * ledNUMBER); i < (24 * ledNUMBER) + 50; i++) {
           pwmData[i] = 0;
       }


    HAL_TIM_PWM_Start_DMA(&htim8, channel, (uint16_t *)pwmData, (24 * ledNUMBER) + 50);


    if (channel == TIM_CHANNEL_1) {
        channelFLAG = 1;
    } else {
        channelFLAG = 0;
    }


    uint32_t timeout = HAL_GetTick();
        while (!lightFLAG) {
            if ((HAL_GetTick() - timeout) > MAX_WAIT_TIME) {
                break; // Zaman aşımı
            }
        }
        lightFLAG = 0;

    HAL_TIM_PWM_Stop_DMA(&htim8, channel);
    HAL_TIM_Base_Stop(&htim8);
}




