/*
 * gpio_hal.cpp
 *
 *  Created on: Mar 5, 2024
 *      Author: gabrys
 */


#include "gpio_hal.h"

bool GPIObase::isInit = false;

GPIObase::GPIObase(){
	GPIObase::init();
}

GPIObase::~GPIObase(){

}
void GPIObase::init(void){
	if(GPIObase::isInit){
		return;
	}
	MX_GPIO_Init();
	GPIObase::isInit = true;
}

Dout::Dout(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState state)
			: _GPIOx(), _GPIO_Pin(){
	write(state);
}

Dout::~Dout(){

}

void Dout::write(GPIO_PinState state){
	 HAL_GPIO_WritePin(_GPIOx,_GPIO_Pin,state);
}

void Dout::toggle(void){
	 HAL_GPIO_TogglePin(_GPIOx, _GPIO_Pin);

}

GPIO_PinState Dout::read(void){
	 return HAL_GPIO_ReadPin( _GPIOx, _GPIO_Pin);

}
