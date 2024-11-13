/*
 * uart_com.h
 *
 *  Created on: Nov 13, 2024
 *      Author: Genki
 */

#ifndef INC_UART_COM_H_
#define INC_UART_COM_H_

extern uint8_t temp;
extern uint8_t buffer_flag;
void command_parser_fsm();
void uart_communication_fsm();
#endif /* INC_UART_COM_H_ */
