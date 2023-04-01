#ifndef ALIEN_H
#define ALIEN_H

#include <stdlib.h>
#include "main.h"
#include "disdrv.h"
#include "shipyalien.h"
#include "puntos.h"

void alien_init(void);
void aliens_movement (game_status_t* game_stat);
void print_alien(dcoord_t center, char animacion, toa_t toa, char doa, dlevel_t value_type, char ID );
void bala_alien_init(bala_alien_t*);
void bala_alien_update(bala_alien_t* bala_alien, game_status_t* game_stat, bala_nave_t* bala_nave );
bala_alien_t gen_alien_bala(void);


#ifdef ALLEGRO

#include "allegro.h"
#include "a_display.h"
#include "a_sprites.h"
#include "a_general.h"
#include "barriers.h"

#define ANCHO_ALIENS 12
#define ALTO_ALIENS 8

#define DIST_ALIENS_X 3
#define DIST_ALIENS_Y ALTO_ALIENS

#define CENTRADO_X 34
#define ALTURA 46

#define DIST_ENTRE_CENTROS_X ((ANCHO_ALIENS-1)+DIST_ALIENS_X)
#define DIST_ENTRE_CENTROS_Y ((ALTO_ALIENS-1)+DIST_ALIENS_Y)

#define POS_CENTRO_ALIEN1_X(i) ( (i)*( DIST_ENTRE_CENTROS_X +1)+ CENTRADO_X )
#define POS_CENTRO_ALIEN2_X(i) ( ((i)>=( CANT_2 /2 ))? (((i)-( CANT_2 /2 ))*( DIST_ENTRE_CENTROS_X +1)+ CENTRADO_X ) : ((i)*( DIST_ENTRE_CENTROS_X +1 )+ CENTRADO_X ) )    //hay una mejor forma de haacer esto?
#define POS_CENTRO_ALIEN3_X(i) ( ((i)>=( CANT_3 /2 ))? (((i)-( CANT_3 /2 ))*( DIST_ENTRE_CENTROS_X +1)+ CENTRADO_X ) : ((i)*( DIST_ENTRE_CENTROS_X +1 )+ CENTRADO_X ) )

#define POS_CENTRO_ALIEN1_Y(i) ALTURA
#define POS_CENTRO_ALIEN2_Y(i) ( ((i)>=(CANT_2/2))? (ALTURA+DIST_ENTRE_CENTROS_Y*2) : (ALTURA+DIST_ENTRE_CENTROS_Y) )
#define POS_CENTRO_ALIEN3_Y(i) ( ((i)>=(CANT_3/2))? (ALTURA+DIST_ENTRE_CENTROS_Y*4) : (ALTURA+DIST_ENTRE_CENTROS_Y*3) )

#define NODRIZA_FAR_RIGHT 231
#define NODRIZA_FAR_LEFT -6
#define NODRIZA_Y_POS (ALTURA-16)
    
// BALA_ALIEN_UPDATE

#define PASO_BALA_ALIEN 1
#define PASO_BALA_ALIEN_DIFICIL 2

// GEN_ALIEN_BALA

#define CANT_COL 11
#define COL_ALIEN_2y3_a(x) ((x)+CANT_COL)
#define COL_ALIEN_2y3_b(x) (x)   
#define COL_ALIEN_1(x) (x)
#define DESPL3_Y (3+6)
#define DESPL2_Y (2+6)
#define DESPL1_Y (2+6)

#define CANT_BALAS 3    
#define CANT_BALA_ANIM 4

// COLISIONES

#define COL_NAVE 0
#define COL_BARR 1

// EXPLOSIONES

#define BALA_ALIEN_EXPLOSION_FRAMES 2

#define CANT_ALIENS 55

//NODRIZA

#define ID_Nodriza 42
#define SPAWN_CONDITION 1 
#define PROB 999
#define HARDCODEADO 15

//PISO

#define CANT_PISO 28
#define LONG_PISO 8

typedef struct
{
    dcoord_t esq_izq;
    bool     intacta;
}piso_t;

extern piso_t piso[CANT_PISO];

void tipo_bala_alien(bala_alien_t* bala_generada);    
void bala_alien_animacion(bala_alien_t* bala_alien);    
void bala_alien_draw(bala_alien_t* bala_alien);
void bala_alien_colision(bala_alien_t* bala_alien);

int max_coord(void);
int min_coord(void);
void aliens_draw(void);

bool colision_nave(bala_alien_t* bala_alien);
void explosion_por_bala_alien(bala_alien_t* bala_alien, int entity);
void explosion_bala_alien_draw(bala_alien_t* bala_alien);

void a_nodriza_update(void);

void piso_init(void);
void piso_update(bala_alien_t* bala_alien);
void piso_draw(void);

#endif //ALLEGRO

#ifdef RASPI


#include "r_main.h"

typedef enum {IZQ=-1, DER=1, ARR=-1, AB=1} direc_t;
    
#define POS_CENTRO_ALIEN1_X(x) (2*(x))
#define POS_CENTRO_ALIEN2_X(x) ((4*(x))+(1))
#define POS_CENTRO_ALIEN3_X(x) ((4*(x))+(1))
#define POS_CENTRO_ALIEN1_Y(x) 1
#define POS_CENTRO_ALIEN2_Y(x) 3
#define POS_CENTRO_ALIEN3_Y(x) 5
#define CANT_1 6 
#define CANT_2 3
#define CANT_3 3
#define CANT_FIL 3
#define ALIVE 1
#define DEAD 0
#define NODRIZA_FAR_RIGHT 18
#define NODRIZA_FAR_LEFT 254
#define NODRIZA_Y_POS 1 
#define SPAWN_CONDITION 4 
#define ID_Nodriza 42
#define SHIP_DEATH_ANIMATION 6000
    
// BALA_ALIEN_UPDATE

#define PASO_BALA_ALIEN 1

// GEN_ALIEN_BALA
#define CANT_COL 6
#define COL_ALIEN_2y3_a(x) ((x)/2)
#define COL_ALIEN_2y3_b(x) ((x)/2)
#define COL_ALIEN_1(x) (x)
#define DESPL3_Y 2
#define DESPL2_Y 1
#define DESPL1_Y 1
#define NO 0
#define YES 1
#define CHANCE 3
#define SPAWN 2
#define ID_Nodriza 42
#define CANT_ALIENS 12


/*
PROTOTIPOS DE FUNCIONES
*/ 


void alien_move(direc_t desp_x,direc_t desp_y);
int alien_comp (void);
void alien_picanazo (bala_alien_t* bala_alien, game_status_t* game_stat, bala_nave_t* bala_nave);
char advance_a_pixel(void);
char check_move_nodriza(void);
void alien_write(dcoord_t pos, dlevel_t level, entity_t entity, toa_t toa, char ID);

#endif //RASPI

#endif //ALIEN_H
