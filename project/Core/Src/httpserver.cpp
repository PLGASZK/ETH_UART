/*
 * httpserver.cpp
 *
 *  Created on: Mar 7, 2024
 *      Author: gabrys
 */


#include "httpserver_hal.h"

bool HTTPserverBase::isInitt = false;

HTTPserverBase::HTTPserverBase(){
	HTTPserverBase::init();
}

HTTPserverBase::~HTTPserverBase(){

}

void HTTPserverBase::init(void){
	if(HTTPserverBase::isInitt){
		return;
	}
	http_server_init();
	HTTPserverBase::isInitt = true;
}





