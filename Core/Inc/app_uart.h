/*
 * app_uart.h
 *
 *  Created on: Jun 23, 2021
 *      Author: thodo
 */

#ifndef INC_APP_UART_H_
#define INC_APP_UART_H_

#include "main.h"

// UART for SIM7600 - UART1
void UART_SIM7600_Init(void);
void UART_SIM7600_Transmit(uint8_t *buffer , uint8_t buffer_len);
uint8_t UART_SIM7600_Received_Buffer_Available(void);
uint8_t UART_SIM7600_Read_Received_Buffer(void);

// UART for 485 Board Control - UART2
void UART_485_Init(void);
void UART_485_Transmit(uint8_t *buffer , uint8_t buffer_len);
uint8_t UART_485_Received_Buffer_Available(void);
uint8_t UART_485_Read_Received_Buffer(void);


// UART for DEBUG - UART3
void UART_DEBUG_Init(void);
void UART_DEBUG_Transmit(uint8_t *buffer);



HAL_StatusTypeDef Custom_UART_Receive_IT(UART_HandleTypeDef *huart);


// Get buffer content with expect_result for stop
uint8_t* Result_From_Buffer(uint8_t * expect_result);
//Clear buffer after receive from 1 respone AT command

void Clear_Buffer(void);
// Time out for RxCallBack
void RxTimeOut();

#endif /* INC_APP_UART_H_ */
