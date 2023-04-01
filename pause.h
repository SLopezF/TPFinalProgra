#ifndef PAUSE_H
#define PAUSE_H

#include "shipyalien.h"


// Intervalos de tiempo de variacion de animaciones

#define TIME_SCR_INTERFACES 3000
#define TIME_DISP_PAUSE 500
#define TIME_SCR_ANIMATIONS 200


// Limites de seccion a variar en el menu de pausa

#define SECTION_START_ROW 7
#define SECTION_START_COLUMN 0
#define SECTION_END_ROW 15
#define SECTION_END_COLUMN 15

// Elementos a presentar en el display:

enum {POINT_TAG, POINT_NUMBER,
      LEVEL_TAG, LEVEL_NUMBER,
      LIVES_TAG, LIVES_NUMBER,
      PAUSE_TAG, PLAY_TAG, FINISH_TAG};

typedef enum {POINT, LEVEL, VIDAS} screen_cycle_t;

void pcf_screen(char toa, char status);
void section_clear (void);
void pause_screen_constant(char toa);
void pause_screen (game_status_t* game_stat);
void pause_screen_variable(char toa, int printable_value); // !!! Necesito recibir los numeros en int y pasarlos a ascii para despues presentarlos de forma correspondiente de acuerdo con la interfaz

void print_digit(char digit2print, int pos_x, int pos_y);


//seleccion del siguiente modo:

enum {LEFT, RIGHT};
enum {CONTINUE, FINISH};


#endif //PAUSE_H
