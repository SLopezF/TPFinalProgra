
#include "main.h"
#ifdef RASPI

#include "r_main.h"
#include "disdrv.h"
#include <stdio.h>
#include "start.h"
#include "joydrv.h"
#include <time.h>
#include <unistd.h>
#include "game_over.h"
#include "pause.h"

extern gamemode_t gamemode;


#define CHECK_POS(x) ((((x)<=DISP_MAX_X) && ((x) >= DISP_MIN )))

void game_over_screen (int* points)
{
    disp_clear();
    
    pause_screen_constant(POINT_TAG);
    for(int h=DISP_MIN; h<=DISP_MAX_X; h++)
    {
        gral_write_var (h,14, A_ON);  
    }

    pause_screen_variable(POINT_NUMBER, *points );
     

    char phrase[] = {"game over"};
    char* pointer= phrase;
    sliding_text(pointer, CANT_LETTER, Y_POSITION);
    gamemode= MENU_INICIO;

}

void sliding_text(char* l_point, int number_letters, char poss_y)
{
    int first_center_pos = COORD_ORIGIN;
    int last_center_pos = COORD_ORIGIN + ( 4 * (number_letters-1) ); 

    while(last_center_pos != COORD_END)
    {
        section_clear_2();
        for(int i=0; i<number_letters; i++)
        {
            //if( (((first_center_pos + (4* (i))) - 1) < (16)) && (((first_center_pos + (4* (i))) - 1) > (-3)) )
            
                
                printf("Before Print_letter, c=(%c), i=(%d), first_venter_pos=(%d) \n",l_point[i],i, first_center_pos + (4* (i)));
                print_letter(l_point[i], (first_center_pos + (4* (i))), D_ON , poss_y );
             
        }


    disp_update();
    first_center_pos--;
    last_center_pos--;
    screen_animations_over();
    }
    disp_clear();




}

void print_letter(char letter, int pos, char level, char poss_y)
{
    printf("Entered to Pront_Letter \n");
    switch (letter)
    {
        case 'g':
        {

            if(CHECK_POS(pos))
            {
                printf("gonna Print = (%d), (%d), (%d) \n", pos, poss_y-2, poss_y+2);
                gral_write_var(pos,poss_y-2,level);
                gral_write_var(pos,poss_y+2,level);
            }

            if(CHECK_POS((pos+1)))
            {
                printf("gonna Print = (%d) \n", pos+1);
                gral_write_var(pos+1,poss_y-2,level);
                gral_write_var(pos+1,poss_y+2,level);
                gral_write_var(pos+1,poss_y,level);
                gral_write_var(pos+1,poss_y+1,level);
            }

            if(CHECK_POS((pos-1)))
            {
                printf("gonna Print = (%d) \n", pos-1);
                gral_write_var(pos-1,poss_y,level);
                gral_write_var(pos-1,poss_y+1,level);
                gral_write_var(pos-1,poss_y-1,level);
            }
            break;

        }

        case 'a':
        {

            if(CHECK_POS(pos))
            {
                printf("gonna Print = (%d), (%d), (%d) \n", pos, poss_y-2, poss_y+2);
                gral_write_var(pos,poss_y,level);
                gral_write_var(pos,poss_y-2,level);
            }

            if(CHECK_POS((pos+1)))
            {
                printf("gonna Print = (%d) \n", pos+1);
                gral_write_var(pos+1,poss_y-2,level);
                gral_write_var(pos+1,poss_y+2,level);
                gral_write_var(pos+1,poss_y,level);
                gral_write_var(pos+1,poss_y+1,level);
                gral_write_var(pos+1,poss_y-1,level);
            }

            if(CHECK_POS((pos-1)))
            {
                printf("gonna Print = (%d) \n", pos-1);
                gral_write_var(pos-1,poss_y-2,level);
                gral_write_var(pos-1,poss_y+2,level);
                gral_write_var(pos-1,poss_y,level);
                gral_write_var(pos-1,poss_y+1,level);
                gral_write_var(pos-1,poss_y-1,level);
            }
            break;
        }
        case 'm':
        {

            if(CHECK_POS(pos))
            {
                printf("gonna Print = (%d), (%d), (%d) \n", pos, poss_y-2, poss_y+2);
                gral_write_var(pos,poss_y-1,level);
            }

            if(CHECK_POS((pos+1)))
            {
                printf("gonna Print = (%d) \n", pos+1);
                gral_write_var(pos+1,poss_y-2,level);
                gral_write_var(pos+1,poss_y+2,level);
                gral_write_var(pos+1,poss_y,level);
                gral_write_var(pos+1,poss_y+1,level);
                gral_write_var(pos+1,poss_y-1,level);
            }

            if(CHECK_POS((pos-1)))
            {
                printf("gonna Print = (%d) \n", pos-1);
                gral_write_var(pos-1,poss_y-2,level);
                gral_write_var(pos-1,poss_y+2,level);
                gral_write_var(pos-1,poss_y,level);
                gral_write_var(pos-1,poss_y+1,level);
                gral_write_var(pos-1,poss_y-1,level);
            }
            break;
        }

        case 'e':
        {

            if(CHECK_POS(pos))
            {
                printf("gonna Print = (%d), (%d), (%d) \n", pos, poss_y-2, poss_y+2);
                gral_write_var(pos,poss_y,level);
                gral_write_var(pos,poss_y-2,level);
                gral_write_var(pos,poss_y+2,level);

            }

            if(CHECK_POS((pos+1)))
            {
                printf("gonna Print = (%d) \n", pos+1);
                gral_write_var(pos+1,poss_y-2,level);
                gral_write_var(pos+1,poss_y+2,level);
                gral_write_var(pos+1,poss_y,level);
            }

            if(CHECK_POS((pos-1)))
            {
                printf("gonna Print = (%d) \n", pos-1);
                gral_write_var(pos-1,poss_y-2,level);
                gral_write_var(pos-1,poss_y+2,level);
                gral_write_var(pos-1,poss_y,level);
                gral_write_var(pos-1,poss_y+1,level);
                gral_write_var(pos-1,poss_y-1,level);
            }
            break;
        }

        case 'o':
        {

            if(CHECK_POS(pos))
            {
                printf("gonna Print = (%d), (%d), (%d) \n", pos, poss_y-2, poss_y+2);
                gral_write_var(pos,poss_y-2,level);
                gral_write_var(pos,poss_y+2,level);

            }

            if(CHECK_POS((pos+1)))
            {
                printf("gonna Print = (%d) \n", pos+1);
                gral_write_var(pos+1,poss_y-2,level);
                gral_write_var(pos+1,poss_y+2,level);
                gral_write_var(pos+1,poss_y,level);
                gral_write_var(pos+1,poss_y+1,level);
                gral_write_var(pos+1,poss_y-1,level);
            }

            if(CHECK_POS((pos-1)))
            {
                printf("gonna Print = (%d) \n", pos-1);
                gral_write_var(pos-1,poss_y-2,level);
                gral_write_var(pos-1,poss_y+2,level);
                gral_write_var(pos-1,poss_y,level);
                gral_write_var(pos-1,poss_y+1,level);
                gral_write_var(pos-1,poss_y-1,level);
            }
            break;
        }

        case 'v':
        {

            if(CHECK_POS(pos))
            {
                printf("gonna Print = (%d), (%d), (%d) \n", pos, poss_y-2, poss_y+2);
                gral_write_var(pos,poss_y+2,level);

            }

            if(CHECK_POS((pos+1)))
            {
                printf("gonna Print = (%d) \n", pos+1);
                gral_write_var(pos+1,poss_y-2,level);
                gral_write_var(pos+1,poss_y,level);
                gral_write_var(pos+1,poss_y+1,level);
                gral_write_var(pos+1,poss_y-1,level);
            }

            if(CHECK_POS((pos-1)))
            {
                printf("gonna Print = (%d) \n", pos-1);
                gral_write_var(pos-1,poss_y-2,level);
                gral_write_var(pos-1,poss_y+2,level);
                gral_write_var(pos-1,poss_y,level);
                gral_write_var(pos-1,poss_y+1,level);
                gral_write_var(pos-1,poss_y-1,level);
            }
            break;
        }

        case 'r':
        {

            if(CHECK_POS(pos))
            {
                printf("gonna Print = (%d), (%d), (%d) \n", pos, poss_y-2, poss_y+2);
                gral_write_var(pos,poss_y-2,level);
                gral_write_var(pos,poss_y,level);

            }

            if(CHECK_POS((pos+1)))
            {
                printf("gonna Print = (%d) \n", pos+1);
                gral_write_var(pos+1,poss_y+2,level);
                gral_write_var(pos+1,poss_y+1,level);
                gral_write_var(pos+1,poss_y-1,level);
            }

            if(CHECK_POS((pos-1)))
            {
                printf("gonna Print = (%d) \n", pos-1);
                gral_write_var(pos-1,poss_y-2,level);
                gral_write_var(pos-1,poss_y+2,level);
                gral_write_var(pos-1,poss_y,level);
                gral_write_var(pos-1,poss_y+1,level);
                gral_write_var(pos-1,poss_y-1,level);
            }
            break;
        }
                case 'l':
        {

            if(CHECK_POS(pos))
            {
                printf("gonna Print = (%d), (%d), (%d) \n", pos, poss_y-2, poss_y+2);
                gral_write_var(pos,poss_y+2,level);
            }

            if(CHECK_POS((pos+1)))
            {
                printf("gonna Print = (%d) \n", pos+1);
                gral_write_var(pos+1,poss_y+2,level);
            }

            if(CHECK_POS((pos-1)))
            {
                printf("gonna Print = (%d) \n", pos-1);
                gral_write_var(pos-1,poss_y-2,level);
                gral_write_var(pos-1,poss_y+2,level);
                gral_write_var(pos-1,poss_y,level);
                gral_write_var(pos-1,poss_y+1,level);
                gral_write_var(pos-1,poss_y-1,level);
            }
            break;
        }

        case ' ':
        {
            break;
        }


    }


}

void screen_animations_over (void)
{
    long int timer_game_over=1;
    while((timer_game_over%SLIDING_LETTERS_DELAY))
    {
        timer_game_over++;
    }
}


void section_clear_2 (void)
{
    dcoord_t vector;

    for(int i=SECTION_START_ROW_2; i<=SECTION_END_ROW_2; i++)
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

#endif //RASPI
