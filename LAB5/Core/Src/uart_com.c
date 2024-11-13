/*
 * uart_com.c
 *
 *  Created on: Nov 13, 2024
 *      Author: Genki
 */
#include "main.h"
#include "stdio.h"
#include "string.h"
#include "uart_com.h"
#include "software_timer.h"

#define MAX_BUFFER_SIZE 30
uint8_t command_flag = 0;
uint32_t ADC_value = 0;
uint8_t temp = 0;
uint8_t buffer[MAX_BUFFER_SIZE];
uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;
extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart2;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart){
	if(huart -> Instance == USART2){
		HAL_UART_Transmit(&huart2 , &temp , 1, 50);
		buffer[index_buffer++] = temp;
		if(index_buffer == 30) index_buffer = 0;
		buffer_flag = 1;
		HAL_UART_Receive_IT(&huart2,&temp,1);
	}
}
void clear_buffer() {
	for (int i = 0; i < 30; i++) {
		buffer[i] = 0;
	}
	index_buffer = 0;
}
void command_parser_fsm(){
	if (strncmp((char*)buffer, "!RST#", 5) == 0) {
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		timer1_flag = 1;
		clear_buffer();
	}
	else if(strncmp((char*)buffer, "!OK#", 4) == 0) {
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		timerExpire();
		clear_buffer();
	}
}
void uart_communication_fsm(){
	static char str[50];
	if(timer1_flag == 1){
		ADC_value = HAL_ADC_GetValue(&hadc1);
		sprintf(str, "\r\n!ADC=%lu#", ADC_value);
		HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), 1000);
		setTimer1(300);
	}
}
