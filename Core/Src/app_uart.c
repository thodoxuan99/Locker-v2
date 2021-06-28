/*
 * app_uart.c
 *
 *  Created on: Jun 23, 2021
 *      Author: thodo
 */

#include "app_uart.h"
#include "app_string.h"


UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;


/* Buffer used for reception */
uint8_t aUART_RxBuffer[RXBUFFERSIZE];
uint8_t receiveBufferIndexHead = 0;
uint8_t receiveBufferIndexTail = 0;

// Buffer for get result and timeout flag
uint8_t timeout_flag;
uint8_t atResult[RXBUFFERSIZE];


__IO ITStatus UartTransmitReady = SET;
__IO ITStatus UartReceiveReady = RESET;


void UART_SIM7600_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}
void UART_SIM7600_Transmit(uint8_t *buffer , uint8_t buffer_len){
	if(buffer_len == 0) {
		return;
	} else {
		if(HAL_UART_Transmit_IT(&huart1, (uint8_t*)buffer, buffer_len)!= HAL_OK){
			Error_Handler();
		}
		UartTransmitReady = RESET;
	}
	return;
}


uint8_t UART_SIM7600_Received_Buffer_Available(void){
	if(receiveBufferIndexTail != receiveBufferIndexHead){
		return 1;
	} else {
		return 0;
	}
}

uint8_t UART_SIM7600_Read_Received_Buffer(void){
	if(receiveBufferIndexTail == receiveBufferIndexHead) return 0xff;
	uint8_t ch = aUART_RxBuffer[receiveBufferIndexTail];
	receiveBufferIndexTail = (receiveBufferIndexTail + 1) % RXBUFFERSIZE;
	return ch;
}


/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */

void UART_485_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

void UART_485_Transmit(uint8_t *buffer , uint8_t buffer_len){
	if(buffer_len == 0) {
		return;
	} else {
		if(HAL_UART_Transmit_IT(&huart2, (uint8_t*)buffer, buffer_len)!= HAL_OK){
			Error_Handler();
		}
		UartTransmitReady = RESET;
	}
	return;
}

uint8_t UART_485_Received_Buffer_Available(void){
	if(receiveBufferIndexTail != receiveBufferIndexHead){
		return 1;
	} else {
		return 0;
	}
}

uint8_t UART_485_Read_Received_Buffer(void){
	if(receiveBufferIndexTail == receiveBufferIndexHead) return 0xff;
	uint8_t ch = aUART_RxBuffer[receiveBufferIndexTail];
	receiveBufferIndexTail = (receiveBufferIndexTail + 1) % RXBUFFERSIZE;
	return ch;
}


/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
void UART_DEBUG_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

void UART_DEBUG_Transmit(uint8_t *buffer){
	if(HAL_UART_Transmit_IT(&huart3, (uint8_t*)buffer, strlen(buffer))!= HAL_OK){
		Error_Handler();
	}
	UartTransmitReady = RESET;
}


HAL_StatusTypeDef Custom_UART_Receive_IT(UART_HandleTypeDef *huart)
{
  /* Check that a Rx process is ongoing */
  if (huart->RxState == HAL_UART_STATE_BUSY_RX)
  {
	  huart->ErrorCode = HAL_UART_ERROR_NONE;
	  huart->RxState = HAL_UART_STATE_BUSY_RX;
	  aUART_RxBuffer[receiveBufferIndexHead] = (uint8_t)(huart->Instance->DR & (uint8_t)0x00FF);
	  receiveBufferIndexHead = (receiveBufferIndexHead + 1) % RXBUFFERSIZE;
	  return HAL_OK;
  } else {
    return HAL_BUSY;
  }
}


uint8_t* Result_From_Buffer(char * expect_result){
	clear_String_Buffer();
	if(UART_485_Received_Buffer_Available()){
		return get_Match_Previous_String(aUART_RxBuffer, receiveBufferIndexTail, receiveBufferIndexHead, RXBUFFERSIZE, expect_result);
	}
	return NULL;
}


