/* 
 * File:   a_impresion_display.h
 * Author: eherrera
 *
 * Created on January 1, 2023, 11:03 PM
 */

#ifndef A_IMPRESION_DISPLAY_H
#define A_IMPRESION_DISPLAY_H

#include "allegro.h"
#include "a_display.h"
#include "a_sprites.h"

extern ALLEGRO_DISPLAY* disp;
extern ALLEGRO_BITMAP* buff;
extern sprites_t sevenup;

#define TO_UPPER(x) ( (((x)>='a') && ((x)<='z'))? ((x)-'a'+'A') : (x) )

void write_display(char* str, int x, int y, int red, int green, int blue);
//char* num2str(int num);

#endif //A_IMPRESION_DISPLAY_H

