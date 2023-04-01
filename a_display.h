/* 
 * File:   a_display.h
 * Author: eherrera
 *
 * Created on December 30, 2022, 2:49 PM
 */

#ifndef A_DISPLAY_H
#define A_DISPLAY_H

#include "allegro.h"
#include "a_general.h"

#define BUFFER_ANCHO 224
#define BUFFER_ALTO 256

#define W BUFFER_ANCHO //para alien.c -> generalizar límites del display entre raspi y allegro
#define H 210

#define DISP_MIN        0
#define DISP_MAX_X      (BUFFER_ANCHO-1)
#define DISP_MAX_Y      (BUFFER_ALTO-1)

#define DISPLAY_ESCALA 2.1 //capaz que se puede agrandar pero se ve raro en mi compu
#define DISPLAY_ANCHO (BUFFER_ANCHO * DISPLAY_ESCALA)
#define DISPLAY_ALTO (BUFFER_ALTO * DISPLAY_ESCALA)

typedef struct {
    uint8_t x;		//coordenada x del display  
    uint8_t y;		//coordenada y del display 
} dcoord_t;

void a_disp_init(ALLEGRO_DISPLAY** disp, ALLEGRO_BITMAP** buffer);
void a_disp_deinit(ALLEGRO_DISPLAY** disp, ALLEGRO_BITMAP** buffer);
void disp_pre_draw(ALLEGRO_BITMAP** buffer);
void disp_post_draw(ALLEGRO_DISPLAY** disp, ALLEGRO_BITMAP** buffer);

#endif //A_DISPLAY_H


