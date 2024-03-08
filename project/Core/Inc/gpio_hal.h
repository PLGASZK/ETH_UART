/*
 * gpio_hal.h
 *
 *  Created on: Mar 5, 2024
 *      Author: gabrys
 */

#ifndef INC_GPIO_HAL_H_
#define INC_GPIO_HAL_H_

#include "gpio.h"

class GPIObase{
public:
	GPIObase();//konstruktor
	~GPIObase();//destruktor po co ? co to klasa i po co

	static void init(void);

private:


	static bool isInit;

};

class Dout: public GPIObase{

public:
	Dout(GPIO_TypeDef* GPIOx,
			uint16_t GPIO_Pin,
			GPIO_PinState state = GPIO_PIN_SET);
	~Dout();

	void write(GPIO_PinState state);
	void toggle();
	GPIO_PinState read(void);
private:
	GPIO_TypeDef* _GPIOx;
	uint16_t _GPIO_Pin;// po co ten underscore tutaj


};


#endif /* INC_GPIO_HAL_H_ */
