/*
 * app_string.c
 *
 *  Created on: Jun 25, 2021
 *      Author: thodo
 */

#include "app_string.h"

uint8_t String_Result[RXBUFFERSIZE];


void clear_String_Buffer(void){
	String_Result="";
	return;
}

uint8_t* get_Match_Previous_String(uint8_t* buffer , uint8_t tail , uint8_t head , uint8_t buffer_len , uint8_t * pattern){
	clear_String_Buffer();
	int j = 0 ;
	int pattern_len = strlen(pattern);
	for (int var = tail; var != head; (++var)%buffer_len){
		for(j = 0 ; j< pattern_len ; j++){
			if(buffer[var+j]!=pattern[j]){
				String_Result[var-tail] = buffer[var];
				break;
			}
		}
		if(j==pattern_len){
			return String_Result;
		}
	}
	return NULL;
}
