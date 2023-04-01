/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   a_points.h
 * Author: mgalante
 *
 * Created on February 6, 2023, 12:36 AM
 */

#ifndef A_POINTS_H
#define A_POINTS_H

#include "main.h"

#ifdef RASPI
#define SMALLER_NUMBER_FOR_RASPI 10
#endif //RASPI

#ifdef ALLEGRO
#include <stdio.h>
#include "a_sprites.h"
#include "a_impresion_display.h"
#include "a_display.h"
#define SMALLER_NUMBER_FOR_RASPI 1
#endif //ALLEGRO

#define ALIEN1_SCORE    (30/(SMALLER_NUMBER_FOR_RASPI))
#define ALIEN2_SCORE    (20/(SMALLER_NUMBER_FOR_RASPI))
#define ALIEN3_SCORE    (10/(SMALLER_NUMBER_FOR_RASPI))
#define NODRIZA_SCORE   (((rand()% 6 + 5)*10)/(SMALLER_NUMBER_FOR_RASPI)) //valor random entre 50 y 100

#ifdef ALLEGRO
extern ALLEGRO_DISPLAY* disp;
extern ALLEGRO_BITMAP* buff;
extern sprites_t sevenup;
extern ship_t my_ship;

int points(int toa, int points);
void hud_draw(int points, int hi_score);
#endif //ALLEGRO

#endif /* A_POINTS_H */
