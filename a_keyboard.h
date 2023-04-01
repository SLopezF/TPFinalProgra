/* 
 * File:   a_keyboard.h
 * Author: eherrera
 
 * Created on December 31, 2022, 11:28 AM
 */

#ifndef A_KEYBOARD_H
#define A_KEYBOARD_H

#include "allegro.h"

#define KEY_SEEN     0x01
#define KEY_RELEASED 0x02

void keyboard_init(void);
void keyboard_update(ALLEGRO_EVENT* event);


#endif //A_KEYBOARD_H

