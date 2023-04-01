
#ifndef BARRIERS_H
#define BARRIERS_H

#include "main.h"

typedef struct
{
	dcoord_t centro;
	char doa;
	char type;
        
}barr_t;

#define DEAD 0
#define ALIVE 1

#define BARR_EDGE 1
#define BARR_CENTER 2

#ifdef ALLEGRO

#include "allegro.h"
#include "a_display.h"
#include "a_sprites.h"
#include "a_general.h"
#include "shipyalien.h"

extern ALLEGRO_DISPLAY* disp;
extern ALLEGRO_BITMAP* buff;
extern sprites_t sevenup;

typedef enum {CHICO_1X1, CHICO_2X2, MEDIANO, GRANDE_3X4, GRANDE_4X3, GRANDE_4X4}tipo_barrera_t;

typedef struct
{
	tipo_barrera_t	tipo;		//puede no estar en la grilla, por lo tanto no tiene fila ni columna (no entraría en el for)
	char			fila;		//4 en total
	char			columna;	//5 en total
	int				ancho;
	int				alto;
	int				x0;
	int				xf;
	int				y0;
	int				yf;
	int				life_status;
	int				patron_de_damage;

}bloque_barrera_t;

typedef enum {BALA_NAVE, BALA_ALIEN, ALIENS}ent_t;


#define CANT_BARRS 4
#define ANCHO_BARRERA 22

#define DIST_BARRERAS ANCHO_BARRERA
#define DIST_ENTRE_CENTROS ((ANCHO_BARRERA-1) + DIST_BARRERAS)

#define CORRIMIENTO_X 45

#define POS_CENTRO_BARRERA_X(i) ( (i) * ( DIST_ENTRE_CENTROS + 1) + CORRIMIENTO_X )
#define POS_CENTRO_BARRERA_Y 158

#define BARRERAS_Y0 151
#define BARRERAS_YF 166
#define BARRERA0_X0 35
#define BARRERA0_XF 56
#define BARRERA1_X0 79
#define BARRERA1_XF 100
#define BARRERA2_X0 123
#define BARRERA2_XF 144
#define BARRERA3_X0 167
#define BARRERA3_XF 188

#define NOT_DEFINED -1

//COLISIONES

//bloques

#define CANT_FIL_BLOQUES 4
#define CANT_COL_BLOQUES 5
#define CANT_BLOQUES 34
#define VIDA_BLOQUE_CHICO 1
#define VIDA_BLOQUE_MEDIANO 1
#define VIDA_BLOQUE_GRANDE 2

void barriers_draw(void);
void barr_damage_print(int i);
void bloque_barriers_init(int i);
bool colision_barrera(bala_nave_t* bala_nave, bala_alien_t* bala_alien, ent_t entidad, alien_t);

#endif //ALLEGRO

#ifdef RASPI

#define POS_CENTRO_BARRERA_X(i) (2+5*(i))
#define POS_CENTRO_BARRERA_Y 10
#define CANT_BARRS 3
#define BARRERA 1

#endif // RASPI


void print_barr(dcoord_t center, dlevel_t value, entity_t type, char doa);
void barriers_init(void);

#endif //BARRIERS_H
