/*
 * ledflash.h
 *
 *  Created on: Jun 5, 2013
 *      Author: dell
 */

#ifndef LED_H_
#define LED_H_

typedef enum {RED, RED_AMBER, GREEN, AMBER} eLED_STATE;

void led_init(void);
void led_change_state(void);

#endif /* LED_H_ */
