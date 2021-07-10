/*
 * test.cpp
 *
 *  Created on: May 1, 2021
 *      Author: Kacper Wołosik
 */
#include "main.h"
#include "Sonar.h"
#include "stdint.h"
#include "stdio.h"
#define IDLE 0
#define ACTIVE 1

Sonar sonar;

int CalcDistance(uint32_t start, uint32_t end, uint16_t OVC){

	return ((end + (OVC*65356)) - start) *1/16 *1/58;
}


void start_calc(void){
	while(1){
		HAL_GPIO_WritePin(Trig1_GPIO_Port, Trig1_Pin, GPIO_PIN_SET);
		HAL_Delay(1);
		HAL_GPIO_WritePin(Trig1_GPIO_Port, Trig1_Pin, GPIO_PIN_RESET);
		HAL_Delay(100);
	}

}

void Sonar_handle(uint32_t time){
	if(sonar.state==IDLE){
			sonar.start = time;
			sonar.TIM2_OVC = 0;
			sonar.state = ACTIVE;
		}
		else if(sonar.state==ACTIVE){
			sonar.end = time;
			sonar.distance = CalcDistance(sonar.start,sonar.end,sonar.TIM2_OVC);
			printf("%d", sonar.distance);
			sonar.state = IDLE;
		}
}

void increase_OVC(){
	sonar.TIM2_OVC++;
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef* htim){
	Sonar_handle(TIM2->CCR1);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim){
	increase_OVC();
}
