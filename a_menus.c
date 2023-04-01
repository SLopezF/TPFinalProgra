
#include "a_menus.h"

void menu_inicio(ALLEGRO_EVENT_QUEUE* q, int hi_score) //cambiar orden de score advanced table
{
    mm_selection_t selected = PLAY;
    char char_hiscore[7];
    bool update = true;
    int frame_change = SENSIBILIDAD;
    key[ALLEGRO_KEY_ENTER] = 0;
    keyboard_update(&event);
    
    static int loopeo = 0;
    y_state_t y_inverted = Y_INV;
    animation_t alieny = {{235, 36}, 0, false, false};
        
    while (gamemode == MENU_INICIO)
    {
        al_wait_for_event(q, &event);
                
        if(key[ALLEGRO_KEY_UP] && update)
        {
            if( selected != PLAY )
            {
                selected--;
            }
            else
            {
                selected = QUIT;
            }
        }
        else if(key[ALLEGRO_KEY_DOWN] && update)
        {
            if( selected != QUIT)
            {
                selected++;
            }
            else
            {
                selected = PLAY;
            }
        }
        else if(key[ALLEGRO_KEY_ENTER] && update)
        {
            if(selected == PLAY)
            {
                gamemode = NORMAL;
            }
            else if(selected == QUIT)
            {
                gamemode = QUIT_GAME;
            }
        }
                
        keyboard_update(&event);
        
        //DETECCIÓN DE TECLADO
        
        if(update || frame_change != SENSIBILIDAD)
        {
            update = false;
            frame_change--;
        }
        if(!frame_change)
        {
            update = true;
            frame_change = SENSIBILIDAD;
        }
        
        //ANIMACIÓN ALIEN
        
        if( (y_inverted==Y_INV) && !(alieny.used) && (loopeo>15) )
        {
            alieny.used = true;
            alieny.coming_in = true;
        }
        else if(alieny.used && !(loopeo%5))
        {
            if(alieny.animacion == 0)
            {
                alieny.animacion = 1;
            }
            else
            {
                alieny.animacion = 0;
            }
            if(alieny.coming_in)
            {
                alieny.centro.x--;
            }
            else
            {
                alieny.centro.x++;
            }
        }
        else if(alieny.centro.x <= 141 && alieny.used && alieny.coming_in)
        {
            if(y_inverted  == Y_INV)
            {
                y_inverted = EMPTY;
            }
            else if(y_inverted == EMPTY)
            {
                y_inverted = Y;
            }
            
            alieny.coming_in = false;
        }
        else if(!(alieny.coming_in) && alieny.centro.x >= 235)
        {
            switch(y_inverted)
            {
                case Y_INV:
                case EMPTY:
                {
                    alieny.coming_in = true;
                    break;
                }
                case Y:
                {
                   alieny.used = false;
                   break;
                }                
            }                     
        }
        
        //DIBUJO DE PANTALLA
        
            disp_pre_draw(&buff);
            
            al_clear_to_color(al_map_rgb(0, 0, 0));

            write_display("SCORE<1>", 6, 6, TURQUESA_R, TURQUESA_G, TURQUESA_B);
            write_display("HI-SCORE", 81, 6, VIOLETA_R, VIOLETA_G, VIOLETA_B);
            write_display("SCORE<2>", 156, 6, AMARILLO_R, AMARILLO_G, AMARILLO_B);
            
            sprintf(char_hiscore, "%06d", hi_score);
                        
            write_display("000000", 14, 14, BLANCO_R, BLANCO_G, BLANCO_B); //SCORE<1>
            write_display(char_hiscore, 89, 14, BLANCO_R, BLANCO_G, BLANCO_B); //HI-SCORE
            write_display("000000", 164, 14, BLANCO_R, BLANCO_G, BLANCO_B);//SCORE<2>
                               
            al_draw_bitmap(sevenup.logo, 53, 57, 0);

            write_display("ORIGINAL GAME:| TAITO 1979", 3, 238, ROJO_R, ROJO_G, ROJO_B);
            write_display("REPROGRAMMED GAME:|sem 2023", 3, 246, ROJO_R, ROJO_G, ROJO_B);           

            if(selected != PLAY)
            {
                write_display("PLA", 98, 33, ROJO_R, ROJO_G, ROJO_B);               
            }
            else
            {
                write_display("* PLA  *", 82, 33, ROJO_R, ROJO_G, ROJO_B);
            }          
            if(selected == QUIT)
            {
                write_display("* QUIT GAME *", 60, 119, BLANCO_R, BLANCO_G, BLANCO_B);
            }
            else
            {
                write_display("QUIT GAME", 76, 119, BLANCO_R, BLANCO_G, BLANCO_B);
            }
            
            write_display("< SCORE ADVANCED TABLE >", 17, 155, TURQUESA_R, TURQUESA_G, TURQUESA_B);

            al_draw_tinted_bitmap(sevenup.nave_nodriza, al_map_rgb(ROSA_R, ROSA_G, ROSA_B), 56, 171, 0);
            write_display(" = ? MYSTERY", 72, 171,ROSA_R, ROSA_G, ROSA_B);

            al_draw_tinted_bitmap(sevenup.alien1[0], al_map_rgb(VERDE_R, VERDE_G, VERDE_B), 64, 187, 0);
            write_display(" = 30 POINTS", 72, 187,VERDE_R, VERDE_G, VERDE_B);

            al_draw_tinted_bitmap(sevenup.alien2[0], al_map_rgb(AMARILLO_R, AMARILLO_G, AMARILLO_B), 61, 203, 0);
            write_display(" = 20 POINTS", 72, 203,AMARILLO_R, AMARILLO_G, AMARILLO_B);

            al_draw_tinted_bitmap(sevenup.alien3[0], al_map_rgb(ROJO_R, ROJO_G, ROJO_B), 60, 219, 0);
            write_display(" = 10 POINTS", 72, 219, ROJO_R, ROJO_G, ROJO_B);
                        
            if(y_inverted==Y_INV)
            {
                al_draw_tinted_rotated_bitmap(sevenup.letra[24], al_map_rgb(ROJO_R, ROJO_G, ROJO_B), 3, 3, 126, 37, 512,0);
            }
            else if(y_inverted==Y)
            {
                write_display("Y", 122, 33, ROJO_R, ROJO_G, ROJO_B);
            }
            if(alieny.used)
            {
                if( (alieny.coming_in && y_inverted==Y_INV) || (!(alieny.coming_in) && y_inverted==Y))
                {
                    al_draw_tinted_bitmap(sevenup.alien1[alieny.animacion], al_map_rgb(VERDE_R, VERDE_G, VERDE_B), alieny.centro.x-3, alieny.centro.y-3 , 0);
                }
                else if(alieny.coming_in && y_inverted==EMPTY)
                {
                    al_draw_bitmap(sevenup.animacion_y[alieny.animacion], alieny.centro.x-11, alieny.centro.y-3, 0);
                }
                else if(!(alieny.coming_in) && y_inverted==EMPTY)
                {
                    al_draw_bitmap(sevenup.animacion_yinv[alieny.animacion], alieny.centro.x-11, alieny.centro.y-3, 0);
                }                
            }
            disp_post_draw(&disp, &buff);
        
        
        if(key[ALLEGRO_KEY_ESCAPE] || event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            gamemode = QUIT_GAME;
        }
        
        loopeo++;
    }     
}

void pause_screen(ALLEGRO_EVENT_QUEUE* q)
{
    ps_selection_t selected = RESUME;
    bool update = true;
    int frame_change = SENSIBILIDAD;
    
    while (gamemode == PAUSE)
    {
        al_wait_for_event(q, &event);
        
        if(key[ALLEGRO_KEY_UP] && update)
        {
            if( selected != RESUME )
            {
                selected--;
            }
            else
            {
                selected = MAIN_MENU;
            }
        }
        else if(key[ALLEGRO_KEY_DOWN] && update)
        {
            if( selected != MAIN_MENU)
            {
                selected++;
            }
            else
            {
                selected = RESUME;
            }
        }
        else if(key[ALLEGRO_KEY_ENTER] && update)
        {
            if(selected == RESUME)
            {
                gamemode = NORMAL;
            }
            else if(selected == MAIN_MENU)
            {               
                gamemode = MENU_INICIO;                
            }
        }
                
        keyboard_update(&event);
        
        if(update || frame_change != SENSIBILIDAD)
        {
            update = false;
            frame_change--;
        }
        if(!frame_change)
        {
            update = true;
            frame_change = SENSIBILIDAD;
        }
             
        if(!key[ALLEGRO_KEY_ENTER])
        {            
            disp_pre_draw(&buff);
            
            al_draw_filled_rectangle(55, 52, 169, 112, al_map_rgb(0, 0, 0));       
            
            write_display("GAME", 96, 56, ROJO_R, ROJO_G, ROJO_B);
            write_display("PAUSED", 88, 68, ROJO_R, ROJO_G, ROJO_B);
            
            if(selected == RESUME)
            {
                write_display("* RESUME *", 72, 84, BLANCO_R, BLANCO_G, BLANCO_B);
            }
            else
            {
                write_display("RESUME", 88, 84, BLANCO_R, BLANCO_G, BLANCO_B);    
            }

            if(selected == MAIN_MENU)
            {
                write_display("* MAIN MENU *", 60, 100, BLANCO_R, BLANCO_G, BLANCO_B);
            }
            else
            {
                write_display("MAIN MENU", 76, 100, BLANCO_R, BLANCO_G, BLANCO_B);
            }            
            disp_post_draw(&disp, &buff);
        }
        
        if(key[ALLEGRO_KEY_ESCAPE] || event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            gamemode = QUIT_GAME;
        }       
    }
}

void game_over_screen(ALLEGRO_EVENT_QUEUE* q) //agregar lo del puntaje en scoreboard!
{    
    int wait = 1000;
    
    while (key[ALLEGRO_KEY_ENTER] || wait)
    {
        disp_pre_draw(&buff);
            
        al_draw_filled_rectangle(55, 52, 169, 80, al_map_rgb(0, 0, 0));       
            
        write_display("GAME", 96, 56, ROJO_R, ROJO_G, ROJO_B);
        write_display("OVER", 96, 68, ROJO_R, ROJO_G, ROJO_B);
            
        disp_post_draw(&disp, &buff);
        
        wait--;                
    }
    gamemode = MENU_INICIO;
}
