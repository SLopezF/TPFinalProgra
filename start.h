
#ifndef START_H
#define START_H
#include "r_main.h"

#define TIME_SCR_ANIMATIONS_ALIEN 450
#define TIME_SCR_MOVE_SCREEN 50
#define TIME_SCR_ANIMATIONS_BUTTON 200
#define TIME_SCR_ANIMATIONS_BORDER 50
#define TIME_SCR_UPDATE 50
#define TIME_DISP_MENU 50
#define TIME_SCR_ANIMATIONS_DOTS 450
#define TIME_SCR_ANIMATIONS_ALIEN_V 700
#define TIME_SCR_ANIMATIONS_DOTS_2 135

enum {ALIEN_ANIMATION,BORDER_ANIMATION,BUTTON_ANIMATION, DOTS_ANIMATION, ALIEN_V_ANIMATION, DOTS_ANIMATION_2};
enum {A_OFF, A_ON};


void main_screen (void);
void gral_clear(void);
void str_screen(void);
void menu_screen_animations(char toa, char status);
void main_screen_right(void);
void str_screen_2(void);

#endif //START_H