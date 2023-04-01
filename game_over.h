#ifndef GAME_OVER_H
#define GAME_OVER_H

#include "main.h"
#include "r_main.h"
#include "disdrv.h"
#include "joydrv.h"
#include "start.h"
#include "pause.h"

#ifdef RASPI

#define CANT_LETTER 9
#define CANT_LETTER_2 5
#define Y_POSITION 3
#define COORD_ORIGIN 17
#define COORD_END -2
#define SLIDING_LETTERS_DELAY 1250
#define SECTION_START_ROW_2 0
#define SECTION_END_ROW_2 6

void sliding_text(char* l_point, int number_letters, char pos_y);
void print_letter(char letter, int pos, char level, char pos_y);
void game_over_screen (int* points);
void screen_animations_over (void);
void section_clear_2 (void);

#endif //RASPI

#endif //GAME_OVER_H