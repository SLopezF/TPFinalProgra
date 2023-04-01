
#include "main.h"
#include "r_main.h"
#include "disdrv.h"
#include <stdio.h>
#include "pause.h"
#include "start.h"
#include "joydrv.h"
#include <time.h>
#include <unistd.h>



extern gamemode_t gamemode;
void pause_screen (game_status_t* game_stat)
{
    jcoord_t coords_joy;
    jswitch_t switch_joy;

    int joy_pos = LEFT;   //el joystick se encuentra inicialmente seleccionando la posicion de la derecha (reanudar juego)
    screen_cycle_t ciclos = POINT;

    gral_clear();
    pcf_screen(PAUSE_TAG, A_ON);

    unsigned long int time_scr = 0;
	do
		{
            if(!(time_scr%TIME_SCR_INTERFACES))   
            {
                if (((!(time_scr%(TIME_SCR_INTERFACES))) && (ciclos == POINT ))) //puntos
                {
                    section_clear ();
                    pause_screen_constant(POINT_TAG);
                    pause_screen_variable(POINT_NUMBER, game_stat->points );
                    time_scr= 0;
                    ciclos= LEVEL;

                }

                else if (((!(time_scr%(TIME_SCR_INTERFACES))) && (ciclos == LEVEL ))) //nivel
                {
                    section_clear ();
                    pause_screen_constant(LEVEL_TAG);
                    pause_screen_variable(LEVEL_NUMBER, game_stat->level );
                    time_scr= 0;
                    ciclos= VIDAS;
                }

                else if (((!(time_scr%(TIME_SCR_INTERFACES))) && (ciclos == VIDAS ))) //vidas
                {
                    section_clear ();
                    pause_screen_constant(LIVES_TAG);
                    pause_screen_variable(LIVES_NUMBER, game_stat->lives );
                    time_scr= 0;
                    ciclos= POINT;
                }
            }


            if(!(time_scr%TIME_SCR_ANIMATIONS))   
            {
                if (joy_pos == LEFT)
                {
                    pcf_screen(PLAY_TAG, (time_scr%(TIME_SCR_ANIMATIONS*2) ? A_OFF : A_ON));
                }

                else
                {
                    pcf_screen(FINISH_TAG, (time_scr%(TIME_SCR_ANIMATIONS*2) ? A_OFF : A_ON));
                }

            }

		    if(!(time_scr%TIME_DISP_PAUSE))
		    {
		    	disp_update();	//Actualiza el display con el contenido del buffer
                joy_update();
		    }

            if(!(time_scr%TIME_DISP_PAUSE))
            {
                coords_joy = joy_get_coord();

                if (joy_pos == LEFT && coords_joy.x > 100)
                {
                    joy_pos = RIGHT;
                }

                else if (joy_pos == RIGHT && coords_joy.x < -100)
                {
                    joy_pos = LEFT;
                }
            }

            if(!(time_scr%TIME_DISP_PAUSE))
            {
                switch_joy = joy_get_switch();

                if (switch_joy == J_PRESS)
                {
                    if (joy_pos == LEFT)
                    {
                        gamemode = NORMAL;
                    }
                    else
                    {
                        gamemode = MENU_INICIO;
                        game_stat->points = 0;
                        game_stat->level = 1;
                        game_stat->lives= LIVES;
                        game_stat->aliens_position=0;
                        game_stat->difficulty_calc=0;
                        game_stat->deadaliens=0;
                    }
                }
            }

            
		    usleep(1); 		// Setea el tiempo de ciclo a 0.1ms
		    if(time_scr++ == 3100)// Cada 10.000 segundos (2.7 horas)
		    {
		    	time_scr = 0;
		    }

	} while( !(((gamemode == NORMAL) || (gamemode == MENU_INICIO))) );

    gral_clear();

}

void pcf_screen(char toa, char status)        //NUMEROS MAGICOS, ARREGLAR
{
    switch (toa)
    {
        case PAUSE_TAG:
        {
            int ancho, alto;                  //deberia imprimir simbolo de pausa arriba a la izq (II II)

            for (int i=0 ; i<=3 ; i+=3)
            {
                for ( ancho=(1+i) ; ancho<=(2+i) ; ancho++ )
                {
                    for ( alto=1+i ; alto<=5 ; alto++ )
                    {
                        gral_write_var (ancho,alto,status);
                    }
                }
            }

            break;
        }

        case PLAY_TAG:                          //imprime triangulito
        {
            gral_write_var (8,1,status);
            gral_write_var (8,2,status);
            gral_write_var (8,3,status);
            gral_write_var (8,4,status);
            gral_write_var (8,5,status);
            gral_write_var (9,2,status);
            gral_write_var (9,3,status);
            gral_write_var (9,4,status);
            gral_write_var (10,3,status);

            break;
        }

        case FINISH_TAG:                        //imprime 'X'
        {
            gral_write_var (12,1,status);
            gral_write_var (12,2,status);
            gral_write_var (12,4,status);
            gral_write_var (12,5,status);
            gral_write_var (13,3,status);
            gral_write_var (14,1,status);
            gral_write_var (14,2,status);
            gral_write_var (14,4,status);
            gral_write_var (14,5,status);

            break;
        }

    }

}

void section_clear (void)
{
    dcoord_t vector;

    for(int i=SECTION_START_ROW; i<=SECTION_END_ROW; i++)
    {
        for(int j=SECTION_START_COLUMN; j<=SECTION_END_COLUMN; j++)
        {
            vector.x= j;
            vector.y= i;
            gral_write(vector, D_OFF, VOID );
        }

    }

    disp_update();    
}

void pause_screen_constant(char toa)
{
    switch (toa)
    {
        case POINT_TAG:
        {
            gral_write_var (0,7, A_ON);      //Imprime 'P'
            gral_write_var (1,7, A_ON);
            gral_write_var (2,7, A_ON);
            gral_write_var (0,8, A_ON);
            gral_write_var (2,8, A_ON);
            gral_write_var (0,9, A_ON);
            gral_write_var (1,9, A_ON);
            gral_write_var (2,9, A_ON);
            gral_write_var (0,10, A_ON);
            gral_write_var (0,11, A_ON);

            gral_write_var (1,14, A_ON);    //Imprime primera barra
            gral_write_var (2,14, A_ON);
            gral_write_var (3,14, A_ON);
            gral_write_var (4,14, A_ON);

            break;
        }

        case LEVEL_TAG:
        {
            gral_write_var (1,7, A_ON);     //Imprime 'L'
            gral_write_var (1,8, A_ON);
            gral_write_var (1,9, A_ON);
            gral_write_var (1,10, A_ON);
            gral_write_var (1,11, A_ON);
            gral_write_var (2,11, A_ON);
            gral_write_var (3,11, A_ON);
            gral_write_var (5,9, A_ON);
            gral_write_var (5,11, A_ON);

            gral_write_var (1,14, A_ON);    //Imprime primera y segunda barra
            gral_write_var (2,14, A_ON);
            gral_write_var (3,14, A_ON);
            gral_write_var (4,14, A_ON);

            gral_write_var (6,14, A_ON);
            gral_write_var (7,14, A_ON);
            gral_write_var (8,14, A_ON);
            gral_write_var (9,14, A_ON);

            break;
        }

        case LIVES_TAG:
        {
            gral_write_var (2,7, A_ON);     //Imprime un corazon de 7x5
            gral_write_var (3,7, A_ON);
            gral_write_var (5,7, A_ON);
            gral_write_var (6,7, A_ON);
            gral_write_var (1,8, A_ON);
            gral_write_var (2,8, A_ON);
            gral_write_var (3,8, A_ON);
            gral_write_var (4,8, A_ON);
            gral_write_var (5,8, A_ON);
            gral_write_var (6,8, A_ON);
            gral_write_var (7,8, A_ON);
            gral_write_var (2,9, A_ON);
            gral_write_var (3,9, A_ON);
            gral_write_var (4,9, A_ON);
            gral_write_var (5,9, A_ON);
            gral_write_var (6,9, A_ON);
            gral_write_var (3,10, A_ON);
            gral_write_var (4,10, A_ON);
            gral_write_var (5,10, A_ON);
            gral_write_var (4,11, A_ON);
            
            gral_write_var (8,9, A_ON);     //Imprime 'x'
            gral_write_var (10,9, A_ON);
            gral_write_var (9,10, A_ON);
            gral_write_var (8,11, A_ON);
            gral_write_var (10,11, A_ON);

            gral_write_var (1,14, A_ON);    //Imprime primera, segunda y tercera barra
            gral_write_var (2,14, A_ON);
            gral_write_var (3,14, A_ON);
            gral_write_var (4,14, A_ON);

            gral_write_var (6,14, A_ON);
            gral_write_var (7,14, A_ON);
            gral_write_var (8,14, A_ON);
            gral_write_var (9,14, A_ON);

            gral_write_var (11,14, A_ON);
            gral_write_var (12,14, A_ON);
            gral_write_var (13,14, A_ON);
            gral_write_var (14,14, A_ON);
            
            break;
        }
    }
}

//NUMEROS MAGICOS ARREGLAR

void pause_screen_variable(char toa, int printable_value)
{
    int num;

    switch(toa)
    {
        case POINT_NUMBER:
        {
            num = printable_value/100;

            if (num)
            {
                print_digit(num,4,7);
                printable_value = printable_value%100;
            }            
        }

        case LEVEL_NUMBER:
        {
            num = printable_value/10;

            if(num)
            {
                print_digit(num,8,7);
                printable_value = printable_value%10;
            }
        }

        case LIVES_NUMBER:
        {
            print_digit(printable_value,12,7);

            break;
        }
    }

} 


void print_digit(char digit2print, int pos_x, int pos_y)
{
    if (digit2print == 1 || digit2print == 7)
    {
        gral_write_var (pos_x+2,pos_y, A_ON);
        gral_write_var (pos_x+2,pos_y+1, A_ON);
        gral_write_var (pos_x+2,pos_y+2, A_ON);
        gral_write_var (pos_x+2,pos_y+3, A_ON);
        gral_write_var (pos_x+2,pos_y+4, A_ON);

        if(digit2print == 7)
        {
            gral_write_var (pos_x,pos_y, A_ON);
            gral_write_var (pos_x+1,pos_y, A_ON);
        }
    }

    else
    {
        gral_write_var (pos_x,pos_y, A_ON);
        gral_write_var (pos_x+1,pos_y, A_ON);
        gral_write_var (pos_x+2,pos_y, A_ON);
        gral_write_var (pos_x,pos_y+1, A_ON);
        gral_write_var (pos_x+2,pos_y+1, A_ON);
        gral_write_var (pos_x,pos_y+2, A_ON);
        gral_write_var (pos_x+1,pos_y+2, A_ON);
        gral_write_var (pos_x+2,pos_y+2, A_ON);
        gral_write_var (pos_x,pos_y+3, A_ON);
        gral_write_var (pos_x+2,pos_y+3, A_ON);
        gral_write_var (pos_x,pos_y+4, A_ON);
        gral_write_var (pos_x+1,pos_y+4, A_ON);
        gral_write_var (pos_x+2,pos_y+4, A_ON);

        switch(digit2print)
        {
            case 0:
            {
                gral_write_var (pos_x+1,pos_y+2, A_OFF);

                break;
            }

            case 2:
            {
                gral_write_var (pos_x,pos_y+1, A_OFF);
                gral_write_var (pos_x+2,pos_y+3, A_OFF);

                break;
            }

            case 3:
            {
                gral_write_var (pos_x,pos_y+1, A_OFF);
                gral_write_var (pos_x,pos_y+3, A_OFF);

                break;
            }

            case 4:
            {
                gral_write_var (pos_x+1,pos_y, A_OFF);
                gral_write_var (pos_x,pos_y+3, A_OFF);
                gral_write_var (pos_x,pos_y+4, A_OFF);
                gral_write_var (pos_x+1,pos_y+4, A_OFF);

                break;
            }

            case 5:
            {
                gral_write_var (pos_x+2,pos_y+1, A_OFF);
                gral_write_var (pos_x,pos_y+3, A_OFF);

                break;
            }

            case 6:
            {
                gral_write_var (pos_x+2,pos_y+1, A_OFF);

                break;
            }

            case 9:
            {
                gral_write_var (pos_x,pos_y+3, A_OFF);

                break;
            }
        }
    }
}
