/*
 * htppserver_hal.h
 *
 *  Created on: Mar 7, 2024
 *      Author: gabrys
 */

#ifndef INC_HTTPSERVER_HAL_H_
#define INC_HTTPSERVER_HAL_H_

#include "main.h"
#include "httpserver.h"

class HTTPserverBase{
public:
	HTTPserverBase();
	~HTTPserverBase();

	void init(void);

private:
	static bool isInitt;

};

#endif /* INC_HTTPSERVER_HAL_H_ */




