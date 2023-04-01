#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>
#include <unistd.h>
#include "alien.h"
#include "barriers.h"
#include "ship.h"

#ifdef ALLEGRO
#include "puntos.h"
#endif //ALLEGRO

//ESTRUCTURAS DEL FUNCIONAMIENTO DEL JUEGO

typedef enum {GAME_OVER, NORMAL, PAUSE, HARD, QUIT_GAME, MENU_INICIO, NEXT_LEVEL} gamemode_t;

#ifdef ALLEGRO
#include "a_main.h"

//CONSTANTES UNIVERSALES
#define     TIME_ALIENS		20
#define     TIME_JOY		1
#define     TIME_SHIP		1
#define     TIME_NODRIZA    5
#define     TIME_ALIEN_BALA 2

#define DIFFICULTY(x,y,z) ((!((z)-1))? ((x)/3+19*((z)-1)) : (12))

void a_inic_todo(ALLEGRO_DISPLAY** display, ALLEGRO_BITMAP** buffer, ALLEGRO_TIMER** timer, ALLEGRO_EVENT_QUEUE** queue, sprites_t* sprite);
void a_deinit_todo(sprites_t* sprite, ALLEGRO_DISPLAY** display, ALLEGRO_BITMAP** buffer, ALLEGRO_TIMER** timer, ALLEGRO_EVENT_QUEUE** queue);

#endif //ALLEGRO

#ifdef RASPI
#include "disdrv.h"
#include <stdio.h>
#include "termlib.h"
#include "joydrv.h"
#include <time.h>
#include <unistd.h>
#include "r_main.h"
#include "alien.h"
#include "barriers.h"
#include "ship.h"
#include "pause.h"
#include "game_over.h"

//CONSTANTES UNIVERSALES RASPI
#define 	TIME_ALIENS		2251
#define 	TIME_DISP		150
#define 	TIME_JOY		150
#define 	TIME_SHIP		225
#define     TIME_NODRIZA    1250
#define     TIME_ALIEN_BALA 450
#define     CHECK_GAME_OVER 100

#define D_DEAD 50
#define D_ALIPOS 125
#define D_LEVEL 100
#define DIFFICULTY(x,y,z) (D_DEAD*(x)+D_ALIPOS*(y)+D_LEVEL*(z))
#endif //RASPI

#endif //MAIN_H

