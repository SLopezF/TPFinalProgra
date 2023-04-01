
#ifndef SHIPYALIEN_H
#define SHIPYALIEN_H

#include "main.h"

#ifdef ALLEGRO
#include "a_display.h"
#endif //ALLEGRO

//ESTRUCTURAS DE LA NAVE

typedef struct
{
    dcoord_t centro;
    char     doa;	//Dead Or Alive
    bool     explode;
    char     explosion_animation;
    int      explosion_animation_duration;
    int      wait_for_revival;
}ship_t;

typedef struct
{
    dcoord_t    pos_centro;
    dcoord_t    next_pos_centro;
    bool        used;
    int         show_explosion;
    dcoord_t    coord_explosion;
}bala_nave_t;

typedef struct
{
    int level;
    int points;
    int hi_score;
    int deadaliens;
    int lives;
    int difficulty_calc;
    int aliens_position;
}game_status_t;


//ESTRUCTURAS DE LOS ALIENS

typedef enum {VOID, ALIEN, NAVE, BALA, WALL, PIXEL_ART}entity_t;
typedef enum {ALIEN1, ALIEN2, ALIEN3, NODRIZA= 10, NONE} toa_t;
typedef enum {BALA1, BALA2, BALA3}tipo_bala_alien_t;

typedef struct
{
    dcoord_t    centro;
    char        doa;            //Dead Or Alive
    toa_t       typeofalien;
    char        animacion;       //qué animación tiene
    char        used;
    char        spawn_condition;
    char        ID;
}alien_t;


typedef struct
{
    dcoord_t    pos_centro;
    dcoord_t    next_pos_centro;
    bool        used;
    char        tipo_bala;  //hay tres tipos de balas
    char        animacion;  //hay cuatro frames para cada bala
    int         show_explosion;
    dcoord_t    coord_explosion;
}bala_alien_t;

//ESTRUCTURAS PARA EL MOVIMIENTO DE LOS ALIENS Y LA NAVE

#ifdef ALLEGRO
typedef enum {IZQ=-1, DER=1, ARR=-1, AB=6} direc_t;
#endif

//DEFINES (CASI) UNIVERSALES
#define DEAD 0
#define ALIVE 1

#ifdef ALLEGRO

#define CENTRO_X 112
#define CENTRO_Y 187

//DEFINES PARA LA ADMINISTRACIÓN DE LOS ALIENS

// ALIEN_INIT

#define CANT_1 11 
#define CANT_2 22
#define CANT_3 22

#define CANT_FIL_1 1
#define CANT_FIL_2 2
#define CANT_FIL_3 2

#define CANT_FIL 3      //no lo uso como filas posta xq no c cómo adaptarlo si no

//MACROS PARA COLISIONES

#define ALIEN1_X0(x) ((x)-3)
#define ALIEN1_XF(x) ((x)+4)
#define ALIEN1_Y0(y) ((y)-3)
#define ALIEN1_YF(y) ((y)+4)

#define ALIEN2_X0(x) ((x)-5)
#define ALIEN2_XF(x) ((x)+5)
#define ALIEN2_Y0(y) ((y)-3)
#define ALIEN2_YF(y) ((y)+4)

#define ALIEN3_X0(x) ((x)-5)
#define ALIEN3_XF(x) ((x)+6)
#define ALIEN3_Y0(y) ((y)-3)
#define ALIEN3_YF(y) ((y)+4)

#define BALA_NAVE_X0(x) (x)
#define BALA_NAVE_XF(x) (x)
#define BALA_NAVE_Y0(y) (y)
#define BALA_NAVE_YF(y) ((y)+3)

#define BALA_ALIEN_X0(x) ((x)-1)
#define BALA_ALIEN_XF(x) ((x)+1)
#define BALA_ALIEN_Y0(y) ((y)-6)
#define BALA_ALIEN_YF(y) (y)

#endif //ALLEGRO

#endif //SHIPYALIEN_H
