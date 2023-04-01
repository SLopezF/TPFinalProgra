/* 
 * File:   a_general.h
 * Author: eherrera
 
 * Created on December 31, 2022, 11:36 AM
 */

#ifndef A_GENERAL_H
#define A_GENERAL_H

#include "allegro.h"
#include "a_display.h"

int inic_chck(bool test, const char *descripcion);
bool collission_chck(int a_x0, int a_y0, int a_xf, int a_yf, int b_x0, int b_y0, int b_xf, int b_yf);

#endif //A_GENERAL_H

