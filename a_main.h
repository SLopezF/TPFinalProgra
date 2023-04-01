/* 
 * File:   main.h
 * Author: eherrera
 *
 * Created on December 31, 2022, 10:55 AM
 */

#ifndef A_MAIN_H
#define A_MAIN_H

#include "allegro.h"
#include "a_general.h"
#include "a_display.h"
#include "a_sprites.h"
#include "a_keyboard.h"
#include "a_menus.h"

extern gamemode_t gamemode;

void a_inic_todo(ALLEGRO_DISPLAY** disp, ALLEGRO_BITMAP** buffer, ALLEGRO_TIMER** timer, ALLEGRO_EVENT_QUEUE** queue, sprites_t* sprite);
void a_deinit_todo(sprites_t* sprite, ALLEGRO_DISPLAY** disp, ALLEGRO_BITMAP** buffer, ALLEGRO_TIMER** timer, ALLEGRO_EVENT_QUEUE** queue);

#endif //A_MAIN_H

