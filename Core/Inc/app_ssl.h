/*
 * ssl.h
 *
 *  Created on: Jun 10, 2021
 *      Author: thodo
 */

#ifndef INC_APP_SSL_H_
#define INC_APP_SSL_H_

#include "main.h"
#include "app_uart.h"



void SSL_Init();

void SSL_Configure_Ctx(SSL_Typedef *ssl);

void SSL_Cert_Down(char *filename ,char *certificate_data);

void SSL_Cert_List();

void SSL_Cert_Delete(char *filename );

#endif /* INC_APP_SSL_H_ */
