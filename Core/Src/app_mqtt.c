/*
 * mqtt.c
 *
 *  Created on: Jun 10, 2021
 *      Author: thodo
 */

#include <app_mqtt.h>

//Result of respone from MQTT message
Result_TypeDef _result = {NULL,ERROR};

MQTT_Machine_TypeDef mqtt_state_machine[]={
		{MQTT_START				, 			MQTT_Start			},

};

void MQTT_Start(){
	return _write_command(huart,huart2, "CMQTTSTART", NULL, 0 ,false,NULL);
}

void MQTT_Stop(UART_HandleTypeDef *huart){
	return write_command(huart, "CMQTTSTOP", NULL, 0 ,false,NULL);
}

void MQTT_Accquire_Client(UART_HandleTypeDef *huart , uint8_t client_index , uint8_t *client_id){
	char _client_index[3];
	sprintf(_client_index,"%d",client_index);
	char *args[2] = {_client_index,client_id};
	return write_command(huart, "CMQTTACCQ", args , 2 ,false,NULL);
}

void MQTT_Release_Client(UART_HandleTypeDef *huart ,uint8_t client_index){
	char _client_index[3];
	sprintf(_client_index,"%d",client_index);
	char *args[1] = {_client_index};
	return write_command(huart, "CMQTTREL", args , 1 ,false,NULL);
}

void MQTT_Set_Ssl(UART_HandleTypeDef *huart ,SSL_Typedef *ssl){
	char _ssl_ctx_index[3];
	sprintf(_ssl_ctx_index,"%d",ssl->ssl_ctx_index);

	char *args[2] = {"0",_ssl_ctx_index};
	return write_command(huart, "CMQTTSSLCFG", args , 2 ,false,NULL);
}

void MQTT_Will_Topic(UART_HandleTypeDef *huart ,uint8_t client_index ,  char * topic){
	char _client_index[3];
	sprintf(_client_index,"%d",client_index);

	char _topic_length[3];
	sprintf(_topic_length,"%d",strlen(topic));

	char *args[2] = {_client_index , _topic_length};
	return write_command(huart, "CMQTTWILLTOPIC", args,2, true ,topic);
}

void MQTT_Will_Message(UART_HandleTypeDef *huart , uint8_t client_index , char * message){
	char _client_index[3];
	sprintf(_client_index,"%d",client_index);

	char _message_length[3];
	sprintf(_message_length,"%d",strlen(message));

	char *args[2] = {_client_index , _message_length};
	return write_command(huart, "CMQTTWILLMSG", args ,2, true ,message);
}

void MQTT_Connect(UART_HandleTypeDef *huart , MQTTClient_TypeDef *mqtt_client){
	char _client_index[3];
	sprintf(_client_index,"%d",mqtt_client->client_index);
	char _clean_session[3];
	sprintf(_clean_session,"%d",mqtt_client->clean_session);
	char _keepAlive[3];
	sprintf(_keepAlive,"%d",mqtt_client->keepAlive);

	char *args[6] = {_client_index,mqtt_client->server_address,_keepAlive
					,_clean_session,mqtt_client->user,mqtt_client->pass};
	return write_command(huart, "CMQTTCONNECT", args , 6,false,NULL);
}

void MQTT_Disonnect(UART_HandleTypeDef *huart , uint8_t client_index , uint8_t time_out){
	char _client_index[3];
	sprintf(_client_index,"%d",client_index);
	char _time_out[3];
	sprintf(_time_out,"%d",time_out);

	char *args[2] = {_client_index , _time_out};
	return write_command(huart, "CMQTTDISC", args , 2,false,NULL);
}

void MQTT_Topic(UART_HandleTypeDef *huart ,uint8_t client_index ,  char * topic){
	char _client_index[3];
	sprintf(_client_index,"%d",client_index);

	char _topic_length[3];
	sprintf(_topic_length,"%d",strlen(topic));

	char *args[2] = {_client_index, _topic_length};
	return write_command(huart, "CMQTTTOPIC", args , 2 ,true,topic);
}

AT_Result MQTT_Payload(UART_HandleTypeDef *huart ,uint8_t client_index ,  char * payload){
	char _client_index[3];
	sprintf(_client_index,"%d",client_index);

	char _payload_length[3];
	sprintf(_payload_length,"%d",strlen(payload));

	char *args[2] = {_client_index ,_payload_length};
	return write_command(huart, "CMQTTPAYLOAD", args , 2, true,payload);
}

void MQTT_Publish(UART_HandleTypeDef *huart ,uint8_t client_index , MESSAGE_TypeDef *message ){

	char * topic 	= 	message->topic;
	char * payload 	=	message->payload;
	uint8_t qos 	= 	message->qos;
	uint8_t pub_time	= 	message->pub_timeout;
	uint8_t retain 		= message->retain;
	uint8_t dup			= message->dup;

	char _client_index[3];
	sprintf(_client_index,"%d",client_index);
	char _qos[3];
	sprintf(_qos,"%d",qos);
	char _pub_time[3];
	sprintf(_pub_time,"%d",pub_time);
	char _retain[3];
	sprintf(_retain,"%d",retain);
	char _dup[3];
	sprintf(_dup,"%d",dup);

	if(MQTT_Topic(huart, client_index, topic) == AT_ERROR){
		return AT_ERROR;
	}
	if(MQTT_Payload(huart, client_index, payload)==AT_ERROR){
		return AT_ERROR;
	}
	char *args[6]={topic,payload,_qos,_pub_time,_retain,_dup};

	return write_command(huart, "CMQTTPUB", args,6 ,false,NULL);
}

AT_Result MQTT_Subcribe_Topic(UART_HandleTypeDef *huart ,uint8_t client_index , char *topic ){
	char _client_index[3];
	sprintf(_client_index,"%d",client_index);
	uint8_t qos = 1;
	char _qos[3];
	sprintf(_qos,"%d",qos);

	char _topic_length[3];
	sprintf(_topic_length,"%d",strlen(topic));

	char *args[3] = {_client_index , _topic_length ,_qos};
	return write_command(huart, "CMQTTSUBTOPIC", args , 3 ,true ,topic);
}

void MQTT_Subcribe(UART_HandleTypeDef *huart ,uint8_t client_index ){
	char _client_index[3];
	sprintf(_client_index,"%d",client_index);
	char *args[1] = {_client_index};
	return write_command(huart, "CMQTTSUB", args , 1,false,NULL);
}

void MQTT_UnSubcribe_Topic(UART_HandleTypeDef *huart ,uint8_t client_index , char *topic ){
	char _client_index[3];
	sprintf(_client_index,"%d",client_index);
	char _topic_length[3];
	sprintf(_topic_length,"%d",strlen(topic));

	char *args[2] = {_client_index,_topic_length};
	return write_command(huart, "CMQTTUNSUBTOPIC", args , 2,true,topic);
}

void MQTT_UnSubcribe(UART_HandleTypeDef *huart ,uint8_t client_index){
	char _client_index[3];
	sprintf(_client_index,"%d",client_index);

	char *args[1] = {_client_index};
	return write_command(huart, "CMQTTUNSUB", args , 1,false,NULL);
}


void Wait_For_Respone(uint8_t * expect_result){
	while(1){
		_result.result = Result_From_Buffer("OK\r\n");
		if(_result.result!=NULL){
			_result.at_result = OK;
			break;
		}
		_result.result = Result_From_Buffer("ERROR\r\n");
		if(_result.result!=NULL){
			_result.at_result = ERROR;
			break;
		}
	}
	return;
}
