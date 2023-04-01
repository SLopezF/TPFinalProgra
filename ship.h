#ifndef SHIP_H
#define SHIP_H

#include "main.h"
#include "disdrv.h"
#include "shipyalien.h"
#include "puntos.h"

#define LIVES 3
#define RESTART 0
#define DURATION_PRESS 10

void ship_init (void);
void print_ship(dcoord_t,dlevel_t,char doa);
void bala_nave_init(bala_nave_t* bala_alien);
void ship_move(direc_t desp_x,direc_t desp_y);
void bala_nave_update(bala_nave_t* bala_nave, bala_alien_t* bala_alien, game_status_t* game_stat);
bool press_chck(void);

#ifdef ALLEGRO

#include "allegro.h"
#include "a_display.h"
#include "a_sprites.h"
#include "a_general.h"
#include "barriers.h"

#define DEAD 0
#define ALIVE 1

#define DESF_BALA_NAVE_Y 4

//EXPLOSIONES

#define BALA_NAVE_EXPLOSION_FRAMES 2 //si se cambia esto habría que cambiar las funciones q lo usan xq si no no va a entrar a ciertos ifs
#define NAVE_ROTA_FRAMES 5

//IN BETWEEN LIVES

#define WAIT 15

//BALA NAVE

#define VEL_BALA_NAVE 2

#define BEGIN 1

void bala_nave_draw(bala_nave_t* bala_nave);
void a_nave_update(void);
void bala_nave_colision(bala_nave_t* bala_nave, bala_alien_t* bala_alien, game_status_t* game_stat);
bool colision_alien(bala_nave_t* bala_nave, game_status_t* game_stat);
bool colision_balas(bala_nave_t* bala_nave, bala_alien_t* bala_alien);
void explosion_bala_nave_draw(bala_nave_t* bala_nave);
void nodriza_draw(void);
bool alienvsnave(void);

#endif //ALLEGRO

#ifdef RASPI

#include "termlib.h"
#include "joydrv.h"




#define CENTRO_X 7
#define CENTRO_Y 14

#define DESF_BALA_NAVE_Y 2

#define WAIT 0 //no sé si ya esperan para revivir la nave

#define VEL_BALA_NAVE 1

#define BEGIN 0

void r_nave_update(jcoord_t coord);
void picanazo (bala_nave_t* bala_nave, game_status_t* game_stat, bala_alien_t* bala_alien);
void delete_alien(uint8_t ID, int* points );
void dead_ship_animation(void);
#endif //RASPI

#endif //SHIP_H
