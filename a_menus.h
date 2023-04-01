/* 
 * File:   a_menu_inicio.h
 * Author: eherrera
 
 * Created on January 1, 2023, 10:11 PM
 */

#ifndef A_MENU_INICIO_H
#define A_MENU_INICIO_H

#include "allegro.h"
#include "a_sprites.h"
#include "a_impresion_display.h"
#include "a_general.h"
#include "main.h"
#include "puntos.h"

#define SENSIBILIDAD 6

typedef enum {PLAY, QUIT}mm_selection_t; //ship color?? ANIMACION DEL ALIEN CON LA Y!!
//ORDEN: PLAY, QUIT GAME, CHANGE SHIPI COLOR, SCOREBOARD, SCORE ADVANCED TABLE

typedef enum {RESUME, MAIN_MENU}ps_selection_t;

typedef struct
{
    dcoord_t centro;
    char     animacion;
    bool     coming_in;
    bool     used;
}animation_t;

typedef enum {Y_INV, EMPTY, Y}y_state_t;

extern ALLEGRO_DISPLAY* disp;
extern ALLEGRO_BITMAP* buff;
extern sprites_t sevenup;
extern ALLEGRO_EVENT event;
extern unsigned char key[ALLEGRO_KEY_MAX];

extern gamemode_t gamemode;
extern game_status_t game_stat;

void menu_inicio(ALLEGRO_EVENT_QUEUE* q, int hi_score);
void pause_screen(ALLEGRO_EVENT_QUEUE* q);
void game_over_screen(ALLEGRO_EVENT_QUEUE* q);

#endif //A_MENU_INICIO_H

