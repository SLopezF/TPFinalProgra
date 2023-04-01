/* 
 * File:   sprites.h
 * Author: eherrera
 *
 * Created on December 30, 2022, 12:14 PM
 */

#ifndef SPRITES_H
#define SPRITES_H

#include "allegro.h"
#include "a_general.h"

#define INIC_MAT_CARACTERES 61
#define COL_CARACTERES 125
#define AYA_CARACTERES 7 //ancho y alto de los caracteres
#define ANCHO_BALAS 3

#define BLANCO_R 255
#define BLANCO_G 255
#define BLANCO_B 255

#define TURQUESA_R 66
#define TURQUESA_G 235
#define TURQUESA_B 245

#define VIOLETA_R 84
#define VIOLETA_G 85
#define VIOLETA_B 237

#define ROJO_R 252
#define ROJO_G 85
#define ROJO_B 84

#define ROJO_BARR_R 255
#define ROJO_BARR_G 121
#define ROJO_BARR_B 120

#define AMARILLO_R 230
#define AMARILLO_G 206
#define AMARILLO_B 128

#define VERDE_R 94
#define VERDE_G 220
#define VERDE_B 120

#define ROSA_R 201
#define ROSA_G 91
#define ROSA_B 186

typedef struct
{
    
    ALLEGRO_BITMAP* sheet;
    
    ALLEGRO_BITMAP* letra[26];
    ALLEGRO_BITMAP* signo[10];
    ALLEGRO_BITMAP* numero[10];
    ALLEGRO_BITMAP* logo;
    ALLEGRO_BITMAP* animacion_y[2];
    ALLEGRO_BITMAP* animacion_yinv[2];
    
    ALLEGRO_BITMAP* piso[2];
    ALLEGRO_BITMAP* alien1[2];
    ALLEGRO_BITMAP* alien2[2];
    ALLEGRO_BITMAP* alien3[2];
    ALLEGRO_BITMAP* nave;
    ALLEGRO_BITMAP* bala_alien1[4];
    ALLEGRO_BITMAP* bala_alien2[4];
    ALLEGRO_BITMAP* bala_alien3[4];
    ALLEGRO_BITMAP* bala_nave;
    ALLEGRO_BITMAP* nave_nodriza;
    ALLEGRO_BITMAP* explosion_alien;
    ALLEGRO_BITMAP* explosion_nave[2]; //creo
    ALLEGRO_BITMAP* explosion[2];
    ALLEGRO_BITMAP* barrera;

    ALLEGRO_BITMAP* dead_barrera_chico_1x1; //d
    ALLEGRO_BITMAP* dead_barrera_chico_2x2; //d
    ALLEGRO_BITMAP* damage_barrera_mediano[4]; //d
    ALLEGRO_BITMAP* dead_barrera_mediano; //d
    ALLEGRO_BITMAP* damage1_barrera_grande_3x4[4]; //d
    ALLEGRO_BITMAP* damage2_barrera_grande_3x4[4]; //d
    ALLEGRO_BITMAP* dead_barrera_grande_3x4; //d
    ALLEGRO_BITMAP* damage1_barrera_grande_4x3[4]; //d
    ALLEGRO_BITMAP* damage2_barrera_grande_4x3[4]; //d
    ALLEGRO_BITMAP* dead_barrera_grande_4x3; //d
    ALLEGRO_BITMAP* damage1_barrera_grande_4x4[4]; //d
    ALLEGRO_BITMAP* damage2_barrera_grande_4x4[4]; //d
    ALLEGRO_BITMAP* dead_barrera_grande_4x4; //d
}sprites_t;

void sprite_inic(sprites_t* sprite);
void caracteres_inic(sprites_t* sprite);
void entidades_inic(sprites_t* sprite);
ALLEGRO_BITMAP* recorte_caracter(sprites_t* sprite, int x, int y, int ancho, int altura);
void destruir_sprites(sprites_t* sprite);

#endif //SPRITES_H

