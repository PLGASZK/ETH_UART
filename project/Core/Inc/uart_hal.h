/*
 * uart_hal.h
 *
 *  Created on: 6 mar 2024
 *      Author: gabrys
 */

#ifndef INC_UART_HAL_H_
#define INC_UART_HAL_H_

#include "main.h"
#include "usart.h"

#define UART_COUNT (1)

class UARTBase{
public:
	UARTBase(USART_TypeDef *Instance, UART_HandleTypeDef *huart);
	~UARTBase();

	void init();

	HAL_StatusTypeDef write(const uint8_t *pData, uint16_t Size, uint32_t Timeout = 1000);
	HAL_StatusTypeDef read(const uint8_t *pData, uint16_t Size, uint32_t Timeout = 1000);

protected:
	USART_TypeDef *_Instance;
	UART_HandleTypeDef *_huart;

private:

	static bool is_init[];

};



#endif /* INC_UART_HAL_H_ */
