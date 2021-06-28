/*
 * ssl.c
 *
 *  Created on: Jun 10, 2021
 *      Author: thodo
 */

#include <app_ssl.h>

// Define type

typedef struct {
	uint8_t ssl_ctx_index;
	uint8_t sslversion;
	uint8_t authmode;
	uint8_t ignoreltime;
	uint8_t negotiatetime;
	char 	*ca_file;
	char	*clientcert_file;
	char	*clientkey_file;
}SSL_Typedef;

typedef enum{
	SSL3 = 0,
	TLS1_0,
	TLS1_1,
	TLS1_2,
	ALL
}SSL_Version;


typedef enum {
	SSL_INIT,
	SSL_CONFIGURE_CTX,
	SSL_CERT_DOWN,
	SSL_CERT_LIST,
	SSL_CERT_DELETE,
	SSL_IDLE
}SSL_State;


// Declare variable
uint8_t ssl_at_command[5000];

SSL_Typedef SSL_DEFAULT_CONFIG = {
		.ssl_ctx_index(0),
		.sslversion(ALL),
		.authmode(0),
		.ignoreltime(1),
		.negotiatetime(300),
		.ca_file(""),
		.clientcert_file(""),
		.clientkey_file("")
};




void SSL_Init(){
	SSL_Configure_Ctx(&SSL_DEFAULT_CONFIG);
}

void SSL_Configure_Ctx(SSL_Typedef *ssl){
	sprintf(ssl_at_command,"AT+CSSLCFG=\"sslversion\",%d,%d\r\n",ssl->ssl_ctx_index,(uint8_t)ssl->sslversion);
	UART_SIM7600_Transmit(ssl_at_command, strlen(ssl_at_command));

	sprintf(ssl_at_command,"AT+CSSLCFG=\"authmode\",%d,%d\r\n",ssl->ssl_ctx_index,(uint8_t)ssl->authmode);
	UART_SIM7600_Transmit(ssl_at_command, strlen(ssl_at_command));

	sprintf(ssl_at_command,"AT+CSSLCFG=\"ignoreltime\",%d,%d\r\n",ssl->ssl_ctx_index,(uint8_t)ssl->ignoreltime);
	UART_SIM7600_Transmit(ssl_at_command, strlen(ssl_at_command));

	sprintf(ssl_at_command,"AT+CSSLCFG=\"negotiatetime\",%d,%d\r\n",ssl->ssl_ctx_index,(uint8_t)ssl->negotiatetime);
	UART_SIM7600_Transmit(ssl_at_command, strlen(ssl_at_command));

	sprintf(ssl_at_command,"AT+CSSLCFG=\"ca_file\",%d,%d\r\n",ssl->ssl_ctx_index,(uint8_t)ssl->ca_file);
	UART_SIM7600_Transmit(ssl_at_command, strlen(ssl_at_command));

	sprintf(ssl_at_command,"AT+CSSLCFG=\"clientcert_file\",%d,%d\r\n",ssl->ssl_ctx_index,(uint8_t)ssl->clientcert_file);
	UART_SIM7600_Transmit(ssl_at_command, strlen(ssl_at_command));

	sprintf(ssl_at_command,"AT+CSSLCFG=\"clientkey_file\",%d,%d\r\n",ssl->ssl_ctx_index,(uint8_t)ssl->clientkey_file);
	UART_SIM7600_Transmit(ssl_at_command, strlen(ssl_at_command));
}

void SSL_Cert_Down(char *filename , char *certificate_data ){
	sprintf(ssl_at_command,"AT+CCERTDOWN=%s,%s\r\n",filename,strlen(certificate_data));
	UART_SIM7600_Transmit(ssl_at_command, strlen(ssl_at_command));
}

void SSL_Cert_List(){
	sprintf(ssl_at_command,"AT+CCERTLIST\r\n");
	UART_SIM7600_Transmit(ssl_at_command, strlen(ssl_at_command));
	RxTimeOut()


}

void SSL_Cert_Delete(char *filename){
	sprintf(ssl_at_command,"AT+CCERTLIST=%s\r\n",filename);
	UART_SIM7600_Transmit(ssl_at_command, strlen(ssl_at_command));
}


