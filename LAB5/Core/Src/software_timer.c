/*
 * software_timer.c
 *
 *  Created on: 19 Sep 2024
 *      Author: Genki
 */
#include "software_timer.h"
#include "main.h"
const int MAX_LED = 4;
int index_led = 0;
int led_buffer[4] = {1, 2, 3, 4};

int timer1_counter = 0;
int timer1_flag = 0;
int timer2_counter = 0;
int timer2_flag = 0;
void setTimer1(int duration){
	timer1_counter = duration;
	timer1_flag = 0;
}
void setTimer2(int duration){
	timer2_counter = duration;
	timer2_flag = 0;
}
void timerRun(void){
	if(timer1_counter > 0){
		timer1_counter--;
		if(timer1_counter <= 0){
			timer1_flag = 1;
		}
	}
	if(timer2_counter > 0){
		timer2_counter--;
		if(timer2_counter <= 0){
			timer2_flag = 1;
		}
	}
}
void timerExpire(void){
	timer1_flag = 0;
	timer1_counter = 0;
}
