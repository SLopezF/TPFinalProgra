
#include "main.h"

/*                        VARIABLES GLOBALES                     */
    barr_t barriers[CANT_BARRS];
    ship_t my_ship;
    alien_t alien1 [CANT_1];
    alien_t alien2 [CANT_2];
    alien_t alien3 [CANT_3];
    alien_t nave_nodriza;
    alien_t* aliens[CANT_FIL] = {alien1,alien2,alien3};

    gamemode_t gamemode;
    
    #ifdef ALLEGRO
    ALLEGRO_DISPLAY* disp;
    ALLEGRO_BITMAP* buff;
    sprites_t sevenup;
    ALLEGRO_EVENT event;
    unsigned char key[ALLEGRO_KEY_MAX];
    bloque_barrera_t bloques_barr[CANT_BARRS][CANT_BLOQUES];
    piso_t piso[CANT_PISO];
    #endif //ALLEGRO
 
    #ifdef RASPI
    led_t LEDMatrix[16][16];	//Creo LA matriz de LEDs
    #endif //RASPI

/*                              MAIN                             */

int main (void)
{

    
    /*                   VARIABLES LOCALES                   */
                  /*(que se pasan como punteros)*/
    
    bala_alien_t bala_alien;
    bala_nave_t bala_nave;
    game_status_t game_stat;
    
    #ifdef RASPI
    gamemode= MENU_INICIO;
    #endif //RASPI
    
    #ifdef ALLEGRO    
    gamemode = MENU_INICIO;
    
    inic_chck(al_init(), "allegro");
    inic_chck(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER* t = al_create_timer(1.0 / 60.0);
    inic_chck(t, "timer");
    ALLEGRO_TIMER** timer = &t;

    ALLEGRO_EVENT_QUEUE* q = al_create_event_queue();
    inic_chck(q, "queue");
    ALLEGRO_EVENT_QUEUE** queue = &q;
        
    inic_chck(al_init_primitives_addon(), "primitives");
        
    ALLEGRO_DISPLAY** display = &disp;
    ALLEGRO_BITMAP** buffer = &buff;
    sprites_t* sprite = &sevenup;
        
    a_inic_todo(display, buffer, timer, queue, sprite);       
        
    al_start_timer(t);
    #endif //ALLEGRO
    
    #ifdef RASPI
    led_t LEDMatrix_save[16][16];
    #endif //RASPI

    game_stat.points = 0;
    game_stat.hi_score = 0;
    game_stat.level = 1;
    game_stat.lives= LIVES;
    game_stat.aliens_position=0;
    game_stat.difficulty_calc=0;
    game_stat.deadaliens=0;

    #ifdef RASPI
    joy_init();		
    disp_init();		
    disp_clear();
    LEDM_init();
    #endif //RASPI
    

    while (gamemode != QUIT_GAME )
    {
        if(gamemode == MENU_INICIO)
        {
        #ifdef RASPI
        main_screen();
        #endif //RASPI
        #ifdef ALLEGRO
        menu_inicio(q, game_stat.hi_score);              
        #endif //ALLEGRO
        }
        
        if (gamemode == NORMAL)
        {
            //INICIALIZACIONES UNIVERSALES
                        
            alien_init();
            ship_init();
            barriers_init();
            bala_nave_init(&bala_nave);
            bala_alien_init(&bala_alien);
            #ifdef ALLEGRO
            piso_init();
            #endif //ALLEGRO
                                         
            //FINALIZACIÓN DE INICIALIZACIÓN DE RASPI
            #ifdef RASPI
            disp_update();
            #endif //RASPI
            
            srand(time(NULL));
            unsigned long int time = 1;
            
            while(gamemode == NORMAL)
            {         
                #ifdef ALLEGRO
                al_wait_for_event(q, &event);
                #endif //ALLEGRO
                
                #ifdef RASPI
                static jcoord_t coord = {0,0};
                #endif //RASPI

                game_stat.difficulty_calc = DIFFICULTY(game_stat.deadaliens, game_stat.aliens_position, game_stat.level);
                
                #ifdef RASPI
                if(game_stat.difficulty_calc >= (TIME_ALIENS-200))
                {
                    game_stat.difficulty_calc = TIME_ALIENS-200;
                }
                #endif //RASPI
                
                if(!(time%((TIME_ALIENS)-((game_stat.difficulty_calc)))))
                {
                    aliens_movement(&game_stat);
                }
                
                if((!(time%TIME_NODRIZA)) && (nave_nodriza.spawn_condition == true) )
                {
                    #ifdef ALLEGRO
                    a_nodriza_update();
                    #endif //ALLEGRO

                    #ifdef RASPI
                    if (nave_nodriza.used == false)
                    {                        
                        nave_nodriza.used = check_move_nodriza();                        
                    }
                    else
                    {
                        nave_nodriza.used = advance_a_pixel();
                    }
                    #endif //RASPI
                }

                if(!(time%TIME_JOY))
                {
                    #ifdef ALLEGRO
                    keyboard_update(&event);            
                    #endif //ALLEGRO   

                    #ifdef RASPI
                    joy_update();	//Mide las coordenadas del joystick
                    coord = joy_get_coord();	//Guarda las coordenadas medidas
                    //Establece la próxima posición según las coordenadas medidas
                    #endif //RASPI
                }

                if(!(time%TIME_ALIEN_BALA))
                {
                    bala_alien_update(&bala_alien, &game_stat, &bala_nave);

                    #ifdef RASPI
                    if(game_stat.lives == DEAD) //PONER DEAD
                    {
                        gamemode= GAME_OVER;
                    }
                    #endif //RASPI
                }
                if(!(time%TIME_SHIP))
                {
                    bala_nave_update(&bala_nave, &bala_alien, &game_stat);

                    #ifdef ALLEGRO
                    a_nave_update();
                    game_stat.lives = my_ship.doa;
                    #endif //ALLEGRO

                    #ifdef RASPI
                    r_nave_update(coord);
                    #endif //RASPI
                }

                #ifdef ALLEGRO

                disp_pre_draw(&buff);

                al_clear_to_color(al_map_rgb(0,0,0));

                barriers_draw();
                bala_nave_draw(&bala_nave);
                bala_alien_draw(&bala_alien);
                print_ship(my_ship.centro, D_ON, my_ship.doa);
                aliens_draw();
                piso_draw();
                hud_draw(game_stat.points, game_stat.hi_score);

                disp_post_draw(&disp,&buff);
                #endif //ALLEGRO

                #ifdef RASPI
                if(!(time%TIME_DISP))
                {                      
                    disp_update();	//Actualiza el display con el contenido del buffer  
                }
                if(!(time%CHECK_GAME_OVER))
                {
                    game_over_check();
                }
                
                usleep(1); 		// Setea el tiempo de ciclo a 0.1ms
                #endif //RASPI               
                
                if(time++ == 100000000)// Cada 10.000 segundos (2.7 horas)
                {
                    time = 0;
                }                

                #ifdef ALLEGRO
                if( key[ALLEGRO_KEY_ESCAPE] || event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                {
                    gamemode = QUIT_GAME;
                    break;
                }
                
                if( key[ALLEGRO_KEY_P] )
                {
                    gamemode = PAUSE;
                }
                #endif //ALLEGRO

                if(gamemode == PAUSE)
                {
                    #ifdef ALLEGRO
                    pause_screen(q);
                    #endif //ALLEGRO
                    
                    #ifdef RASPI
                    disp_update();
                    save_state_LEDMatrix(LEDMatrix, LEDMatrix_save);
                    gamemode= PAUSE;
                    joy_update();

                    while(joy_get_switch() == J_PRESS)
                    {
                        joy_update();
                    }
                    
                    pause_screen(&game_stat);
                    save_state_LEDMatrix(LEDMatrix_save, LEDMatrix);
                    manual_update();
                    disp_update();
                    #endif //RASPI
                }
                
                else if(gamemode == GAME_OVER)
                {
                    #ifdef ALLEGRO
                    game_over_screen(q);
                    
                    if(game_stat.points > game_stat.hi_score)
                    {
                        game_stat.hi_score = game_stat.points;
                    }
                    #endif //ALLEGRO

                    #ifdef RASPI
                    game_over_screen(&(game_stat.points));
                    #endif //RASPI
                    game_stat.points = 0;
                    game_stat.level = 1;
                    game_stat.lives= LIVES;
                    game_stat.aliens_position=0;
                    game_stat.difficulty_calc=0;
                    game_stat.deadaliens=0;
                }

                if (game_stat.deadaliens == CANT_ALIENS)
                {   
                    #ifdef ALLEGRO
                    alien_init();
                    ship_init();
                    bala_nave_init(&bala_nave);
                    bala_alien_init(&bala_alien);
                    #endif //ALLEGRO
                    
                    game_stat.deadaliens=0;
                    (game_stat.level)++;
                    game_stat.aliens_position=0;
                    if(game_stat.lives != 9)
                    {
                        (game_stat.lives)++;
                        #ifdef ALLEGRO
                        my_ship.doa++;
                        #endif //ALLEGRO
                    }
                    
                    #ifdef ALLEGRO
                    int wait = 1000;
    
                    while (wait)
                    {
                        disp_pre_draw(&buff);
            
                        al_draw_filled_rectangle(55, 52, 169, 80, al_map_rgb(0, 0, 0));       
            
                        write_display("NEXT", 96, 56, ROJO_R, ROJO_G, ROJO_B);
                        write_display("LEVEL", 92, 68, ROJO_R, ROJO_G, ROJO_B);
                        
                        disp_post_draw(&disp, &buff);
                        
                        wait--;                    
                    }
                    unsigned long int time = 1;
                    #endif //ALLEGRO

                    #ifdef RASPI
                    gral_clear();

                    char phrase[] = {"level"};
                    char* pointer= phrase;

                    pause_screen_variable(LEVEL_NUMBER, game_stat.level);

                    sliding_text(pointer, CANT_LETTER_2, Y_POSITION);
                    gral_clear();
                    
                    gamemode= NORMAL;
                    alien_init();
                    ship_init();
                    bala_nave_init(&bala_nave);
                    bala_alien_init(&bala_alien);
                    barriers_init();
                    #endif //RASPI                   
                }
            }
        }
    }

    return 0;
}

#ifdef ALLEGRO

void a_inic_todo(ALLEGRO_DISPLAY** display, ALLEGRO_BITMAP** buffer, ALLEGRO_TIMER** timer, ALLEGRO_EVENT_QUEUE** queue, sprites_t* sprite)
{
    a_disp_init(display, buffer);
    
    inic_chck(al_init_image_addon(), "image");
    sprite_inic(sprite);
    
    inic_chck(al_init_primitives_addon(), "primitives");
    
    al_register_event_source(*queue, al_get_keyboard_event_source());  
    al_register_event_source(*queue, al_get_display_event_source(*display));
    al_register_event_source(*queue, al_get_timer_event_source(*timer));

    keyboard_init();
}

void a_deinit_todo(sprites_t* sprite, ALLEGRO_DISPLAY** display, ALLEGRO_BITMAP** buffer, ALLEGRO_TIMER** timer, ALLEGRO_EVENT_QUEUE** queue)
{
    destruir_sprites(sprite);
    a_disp_deinit(display, buffer);
    al_destroy_timer(*timer);
    al_destroy_event_queue(*queue);
}

#endif //ALLEGRO


#ifdef RASPI

void gral_write(dcoord_t pos, dlevel_t level, entity_t entity)
{
	if(level == D_OFF)								// Si va a borrar la entidad va a ser void
	{
		entity = VOID;
	}
	LEDMatrix[pos.y][pos.x].level = level;		// Escribe en la matriz virtual de LEDS el valor que recibe
	LEDMatrix[pos.y][pos.x].entity = entity;	// Guarda que tipo de entidad hay en esa posición
	disp_write(pos, level);						// Escribe en la matriz fisica de LEDS el valor que recibe
}

void alien_write(dcoord_t pos, dlevel_t level, entity_t entity, toa_t toa, char ID)	//Sirve unicamente para los aliens
{
	if(level == D_OFF)								// Si va a borrar la entidad va a ser void
	{
		entity = VOID;
        ID = 0;
	}

    LEDMatrix[pos.y][pos.x].ID = ID;   // Guarda el identificador del alien
	LEDMatrix[pos.y][pos.x].level = level;		// Escribe en la matriz virtual de LEDS el valor que recibe
	LEDMatrix[pos.y][pos.x].entity = entity;	// Guarda que tipo de entidad hay en esa posición
	LEDMatrix[pos.y][pos.x].typeofalien = toa;	// Guarda que tipo de alien hay en esa posición

	disp_write(pos, level);						// Escribe en la matriz fisica de LEDS el valor que recibe
}



void LEDM_init (void)							//Setea 
{
	for (int i = 0; i <= DISP_MAX_Y; i++)		//NO ME ACUERDO SI ES MAX X MAX Y O AL REVES
	{
		for(int j = 0; j<= DISP_MAX_X; j++)
		{
			LEDMatrix[i][j].entity = VOID;			// Setea en 0 el estado de todos los LEDs 
			LEDMatrix[i][j].level = D_OFF;			// Y la entidad en VOID
		}
	}
	
}

void gral_write_var(uint8_t x,uint8_t y, dlevel_t d_level)
{
    dcoord_t vector;
    vector.x=x;
    vector.y=y;
	LEDMatrix[y][x].level = d_level;		// Escribe en la matriz virtual de LEDS el valor que recibe
	LEDMatrix[y][x].entity = PIXEL_ART;	// Guarda que tipo de entidad hay en esa posición
	disp_write(vector, d_level);						// Escribe en la matriz fisica de LEDS el valor que recibe
}

void save_state_LEDMatrix (led_t mat_copy [][16], led_t mat_paste [][16])
{
    int i;
    int j;
    int n = 16;
    int m = 16;

    for (i = 0 ; i < n ; i++)
    {
        for (j = 0; j < m; j++)
        {
            mat_paste [i][j] = mat_copy [i][j];
        }
    }
}

void manual_update (void)
{
    dcoord_t pos;
    for (uint8_t i = 0; i <= DISP_MAX_Y; i++)		//NO ME ACUERDO SI ES MAX X MAX Y O AL REVES
    {
	    for(uint8_t j = 0; j<= DISP_MAX_X; j++)
	    {
            pos.x= j;
            pos.y= i;
            disp_write(pos,LEDMatrix[i][j].level);			// Y la entidad en VOID
	    }
    }
}

void game_over_check (void)
{
    char condition=YES;
    for(int i=DISP_MIN; (i<=DISP_MAX_X) && (condition); i++ )
    {
        if(LEDMatrix[DEATH_CONDITION][i].entity == ALIEN)
        {
            gamemode= GAME_OVER;
            condition= NO;
        } 

    }

}

#endif //RASPI
