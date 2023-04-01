
#include "main.h"
#include "r_main.h"
#include "disdrv.h"
#include <stdio.h>
#include "start.h"
#include "joydrv.h"
#include <time.h>
#include <unistd.h>

extern gamemode_t gamemode;

void main_screen (void)
{
    jcoord_t coords_joy;
    gral_clear();
    str_screen();

    unsigned long int time_scr = 0;
	do
		{
            if(!(time_scr%TIME_SCR_ANIMATIONS_ALIEN))   
            {
                menu_screen_animations(ALIEN_ANIMATION, (time_scr%(TIME_SCR_ANIMATIONS_ALIEN*2) ? A_OFF : A_ON));
            }

            if(!(time_scr%TIME_SCR_ANIMATIONS_BUTTON))   
            {
                menu_screen_animations(BUTTON_ANIMATION, (time_scr%(TIME_SCR_ANIMATIONS_BUTTON*2) ? A_OFF : A_ON));
            }

		    if(!(time_scr%TIME_DISP_MENU))
		    {
		    	disp_update();	//Actualiza el display con el contenido del buffer
                joy_update();
		    }

            if(!(time_scr%TIME_DISP_MENU))
            {
                coords_joy=joy_get_coord();
                if(coords_joy.x > 100)
                {
                    time_scr=0;
                    main_screen_right();
                    str_screen();
                }
            }

		    usleep(1); 		// Setea el tiempo de ciclo a 0.1ms
		    if(time_scr++ == 100000000)// Cada 10.000 segundos (2.7 horas)
		    {
		    	time_scr = 0;
		    }
	} while( (joy_get_switch() == J_NOPRESS) && (gamemode != QUIT_GAME));
    gral_clear();
    if(gamemode != QUIT_GAME)
    {
        gamemode= NORMAL;
    }
    
}

void main_screen_right(void)
{
    int return_to_main_menu =1;
    jcoord_t vector_right;
    gral_clear();
    str_screen_2();

    unsigned long int time_scr = 0;
	do
		{
            if(!(time_scr%TIME_SCR_ANIMATIONS_DOTS))   
            {
                menu_screen_animations(DOTS_ANIMATION, (time_scr%(TIME_SCR_ANIMATIONS_DOTS*2) ? A_OFF : A_ON));
            }
            if(!(time_scr%TIME_SCR_ANIMATIONS_DOTS_2))   
            {
                menu_screen_animations(DOTS_ANIMATION_2, (time_scr%(TIME_SCR_ANIMATIONS_DOTS*2) ? A_OFF : A_ON));
            }

            if(!(time_scr%TIME_SCR_ANIMATIONS_BUTTON))   
            {
                menu_screen_animations(BUTTON_ANIMATION, (time_scr%(TIME_SCR_ANIMATIONS_BUTTON*2) ? A_OFF : A_ON));
            }

            if(!(time_scr%TIME_SCR_ANIMATIONS_ALIEN_V))   
            {
                menu_screen_animations(ALIEN_V_ANIMATION, (time_scr%(TIME_SCR_ANIMATIONS_ALIEN_V*2) ? A_OFF : A_ON));
            }

		    if(!(time_scr%TIME_DISP_MENU))
		    {
		    	disp_update();	//Actualiza el display con el contenido del buffer
                joy_update();
		    }

		    usleep(1); 		// Setea el tiempo de ciclo a 0.1ms
		    if(time_scr++ == 100000000)// Cada 10.000 segundos (2.7 horas)
		    {
		    	time_scr = 0;
		    }

            if(joy_get_switch() == J_PRESS)
            {
                gamemode=QUIT_GAME;
                return_to_main_menu=0;

            }

            if(!(time_scr%TIME_DISP_MENU))
            {
                vector_right=joy_get_coord();
                if(vector_right.x<-100)
                {
                    return_to_main_menu=0;
                }

            }



	} while(return_to_main_menu);

    gral_clear();



}

void str_screen(void)
{
    dcoord_t vector;

    static char menu_scr[16][16]=  {
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                {1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1},
                                {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1},
                                {1,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1},
                                {1,0,0,1,1,0,1,1,1,1,0,1,1,0,0,1},
                                {1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
                                {1,0,1,0,1,1,1,1,1,1,1,1,0,1,0,1},
                                {1,0,1,0,1,0,0,0,0,0,0,1,0,1,0,1},
                                {1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,1},
                                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                {1,0,0,1,0,0,0,1,1,0,0,0,1,0,0,1},
                                {1,0,1,1,0,0,1,1,1,1,0,0,1,1,0,1},
                                {1,0,0,1,0,0,0,1,1,0,0,0,1,0,0,1},
                                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                               };

    for(int i=0; i<=15; i++)
    {
        for(int j=0; j<=15; j++)
        {
            vector.x= j;
            vector.y= i;

            gral_write(vector, menu_scr[i][j], PIXEL_ART );
        }

    }

    disp_update();

}

void str_screen_2(void)
{
    dcoord_t vector;

    static char menu_scr[16][16]=  {
                                {1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
                                {1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,1},
                                {1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1},
                                {1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
                                {1,0,1,1,1,0,1,0,1,0,1,0,0,0,0,1},
                                {1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
                                {1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1},
                                {1,0,0,1,0,0,1,0,1,0,0,0,0,0,0,1},
                                {1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                {1,0,0,1,0,0,0,1,1,0,0,0,1,0,0,1},
                                {1,0,1,1,0,0,1,1,1,1,0,0,1,1,0,1},
                                {1,0,0,1,0,0,0,1,1,0,0,0,1,0,0,1},
                                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                               };

    for(int i=0; i<=15; i++)
    {
        for(int j=0; j<=15; j++)
        {
            vector.x= j;
            vector.y= i;

            gral_write(vector, menu_scr[i][j], PIXEL_ART );
        }

    }

    disp_update();

}

void gral_clear(void)
{
    dcoord_t vector;


    for(int i=0; i<=DISP_MAX_Y; i++)
    {
        for(int j=0; j<=DISP_MAX_X; j++)
        {
            vector.x= j;
            vector.y= i;
            gral_write(vector, D_OFF, VOID );
        }

    }

    disp_update();

}

void menu_screen_animations(char toa, char status)
{
    dcoord_t vector;
    switch(toa)
    {
        case ALIEN_ANIMATION:
        {
            gral_write_var(2,4,(status == A_ON ? D_ON : D_OFF));
            gral_write_var(2,5,(status == A_ON ? D_ON : D_OFF));
            gral_write_var(2,7,(status == A_ON ? D_OFF : D_ON));
            gral_write_var(2,8,(status == A_ON ? D_OFF : D_ON));
            gral_write_var(3,7,(status == A_ON ? D_ON : D_OFF));
            gral_write_var(3,9,(status == A_ON ? D_ON : D_OFF));
            gral_write_var(5,9,(status == A_ON ? D_OFF : D_ON));
            gral_write_var(6,9,(status == A_ON ? D_OFF : D_ON));
            gral_write_var(9,9,(status == A_ON ? D_OFF : D_ON));
            gral_write_var(10,9,(status == A_ON ? D_OFF : D_ON));
            gral_write_var(12,9,(status == A_ON ? D_ON : D_OFF));
            gral_write_var(12,7,(status == A_ON ? D_ON : D_OFF));
            gral_write_var(13,4,(status == A_ON ? D_ON : D_OFF));
            gral_write_var(13,5,(status == A_ON ? D_ON : D_OFF));
            gral_write_var(13,7,(status == A_ON ? D_OFF : D_ON));
            gral_write_var(13,8,(status == A_ON ? D_OFF : D_ON));
            break;
        }

        case BUTTON_ANIMATION:
        {
            gral_write_var(7,12,(status == A_ON ? D_OFF : D_ON));
            gral_write_var(8,12,(status == A_ON ? D_OFF : D_ON));
            break;
        }

        case BORDER_ANIMATION:
        {

            //WORK IN PROGRESS

        }

        case DOTS_ANIMATION:
        {
            gral_write_var(8,1,(status == A_ON ? D_OFF : D_ON));
            //gral_write_var(12,7,(status == A_ON ? D_OFF : D_ON));     
        }

        case ALIEN_V_ANIMATION:
        {
            gral_write_var(2,1,(status == A_ON ? D_OFF : D_ON));
            gral_write_var(4,1,(status == A_ON ? D_OFF : D_ON));
            gral_write_var(3,2,(status == A_ON ? D_OFF : D_ON));
            gral_write_var(2,2,(status == A_ON ? D_ON : D_OFF));
            gral_write_var(3,1,(status == A_ON ? D_ON : D_OFF));
            gral_write_var(4,2,(status == A_ON ? D_ON : D_OFF));
        }
        case DOTS_ANIMATION_2:
        {
            gral_write_var(10,4,(status == A_ON ? D_OFF : D_ON));   
        }
        default:
        {
            break;
        }
        
    }



}
