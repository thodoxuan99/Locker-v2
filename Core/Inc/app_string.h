/*
 * app_string.h
 *
 *  Created on: Jun 25, 2021
 *      Author: thodo
 */

#ifndef INC_APP_STRING_H_
#define INC_APP_STRING_H_

#include "main.h"


void clear_String_Buffer(void);

// Get result util match pattern
uint8_t* get_Match_Previous_String(uint8_t* buffer , uint8_t tail , uint8_t head , uint8_t * pattern);

#endif /* INC_APP_STRING_H_ */
