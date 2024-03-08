/*
 * uart_hal.cpp
 *
 *  Created on: 6 mar 2024
 *      Author: gabrys
 */

#include "uart_hal.h"
bool UARTBase::is_init[] = {false};

UARTBase::UARTBase(USART_TypeDef *Instance, UART_HandleTypeDef *huart){

}


void UARTBase::init(){

	if(_Instance== USART3){
		if(is_init[0]){
			return;
		}
		is_init[0] = true;
		MX_USART3_UART_Init();

	}

}

UARTBase::~UARTBase(){

	if(_Instance== USART3){
		if(!is_init[0]){
			return;
		}
		is_init[0] = false;
		HAL_UART_MspDeInit(_huart);

	}
}

HAL_StatusTypeDef UARTBase::write(const uint8_t *pData, uint16_t Size, uint32_t Timeout){

	return HAL_UART_Transmit(_huart,  pData,  Size, Timeout);

}


HAL_StatusTypeDef UARTBase::read(const uint8_t *pData, uint16_t Size, uint32_t Timeout){

	return HAL_UART_Transmit(_huart,  pData,  Size, Timeout);

}



















