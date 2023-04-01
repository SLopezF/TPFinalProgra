#ifndef R_MAIN_H
#define R_MAIN_H
#include "disdrv.h"
#include "start.h"

#define THRESHOLD 40	//Límite a partir del cual se mueve el LED encendido
#define H 16
#define W 16
#define DEATH_CONDITION 13

typedef struct
{
	dlevel_t level;			//LED PRENDIDO O APAGADO
	entity_t entity;		//Que hay en ese LED, empieza siendo void
	toa_t typeofalien;		//I,V, --- , Nodriza
	dcoord_t centroalien;	//Número del Alien (0 Nave nodriza)
	char ID;			 
}led_t;


void gral_write(dcoord_t pos, dlevel_t level, entity_t entity);
void LEDM_init (void);
void save_state_LEDMatrix (led_t mat_copy [][16], led_t mat_paste [][16]);
void gral_write_var(uint8_t x,uint8_t y, dlevel_t d_level);
void alien_write(dcoord_t pos, dlevel_t level, entity_t entity, toa_t toa, char ID);
void manual_update (void);
void game_over_check (void);


#endif //MAIN_H