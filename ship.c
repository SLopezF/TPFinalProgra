
#include "ship.h"

extern ship_t my_ship;

extern alien_t alien1 [CANT_1];
extern alien_t alien2 [CANT_2];
extern alien_t alien3 [CANT_3];
extern alien_t nave_nodriza;
extern alien_t* aliens[CANT_FIL];

extern gamemode_t gamemode;

#ifdef ALLEGRO
extern unsigned char key[ALLEGRO_KEY_MAX];
extern ALLEGRO_DISPLAY* disp;
extern ALLEGRO_BITMAP* buff;
extern sprites_t sevenup;

#endif //ALLEGRO

#ifdef RASPI
extern led_t LEDMatrix[16][16];

#endif

void ship_init(void)
{
    /*
    Forma de la nave
     *
    *X*
    X= Centro
    */

    my_ship.centro.x= CENTRO_X;	//Inicializo el centro en la mitad de las coordenadas en x
    my_ship.centro.y= CENTRO_Y;	//Inicializo el centro en el anteúltimo pixel
    my_ship.doa= LIVES;		//LO seteo ocmo vivo
    my_ship.explode = false;
    my_ship.wait_for_revival = 0;

    print_ship(my_ship.centro, D_ON, my_ship.doa);

}

void bala_nave_init(bala_nave_t* bala_nave)
{
    bala_nave->used = false;
    bala_nave->show_explosion = 0;
}

void bala_nave_update(bala_nave_t* bala_nave, bala_alien_t* bala_alien, game_status_t* game_stat)
{
    if( press_chck() && !(bala_nave->used) )
    {
        bala_nave->pos_centro = my_ship.centro;
	bala_nave->pos_centro.y -= DESF_BALA_NAVE_Y;
        bala_nave->used = true;
    }
    else if(bala_nave->used)
    {
        bala_nave->next_pos_centro = bala_nave->pos_centro;
        bala_nave->next_pos_centro.y -= VEL_BALA_NAVE;
        
        if( BEGIN>=(bala_nave->next_pos_centro.y) || (bala_nave->next_pos_centro.y)>=H )
        {
            bala_nave->used = false;
            
            #ifdef ALLEGRO
            bala_nave->show_explosion = BALA_NAVE_EXPLOSION_FRAMES;
            bala_nave->coord_explosion.x = bala_nave->pos_centro.x;
            bala_nave->coord_explosion.y = 4;
            #endif //ALLEGRO
                    
            #ifdef RASPI
            gral_write(bala_nave->pos_centro, D_OFF, BALA);
            #endif //RASPI
        }
        
        else
        {
            #ifdef ALLEGRO
            bala_nave_colision(bala_nave, bala_alien, game_stat);
            #endif //ALLEGRO

            #ifdef RASPI
            
            picanazo(bala_nave, game_stat, bala_alien);
            
            if(bala_nave->used)
            { 
                gral_write(bala_nave->pos_centro, D_ON, BALA);
                bala_nave->pos_centro.y +=1;

                gral_write(bala_nave->pos_centro, D_OFF, BALA);
                bala_nave->pos_centro.y -=1;
            }   
            #endif //RASPI
        }   
    }
}

void ship_move(direc_t desp_x,direc_t desp_y)
{
    #ifdef RASPI
    print_ship(my_ship.centro, D_OFF, NAVE);
    #endif //RASPI
    
    my_ship.centro.x += desp_x;
    my_ship.centro.y += desp_y;

    #ifdef RASPI
    print_ship(my_ship.centro, D_ON, NAVE);
    #endif //RASPI
}

#ifdef ALLEGRO

void print_ship(dcoord_t coord, dlevel_t value, char doa) //ANIMACION DE EXPLOSION!!
{
    if(!(my_ship.explode) && doa && !(my_ship.wait_for_revival))
    {        
        al_draw_tinted_bitmap(sevenup.nave, al_map_rgb(TURQUESA_R, TURQUESA_G, TURQUESA_B), (coord.x)-6 , (coord.y)-4 , 0);
    }
    else if (my_ship.explode)
    {
        if(my_ship.explosion_animation == 0)
        {
            al_draw_tinted_bitmap(sevenup.explosion_nave[0], al_map_rgb(TURQUESA_R, TURQUESA_G, TURQUESA_B), (coord.x)-6 , (coord.y)-4 , 0);
        }
        else if(my_ship.explosion_animation == 1)
        {
            al_draw_tinted_bitmap(sevenup.explosion_nave[1], al_map_rgb(TURQUESA_R, TURQUESA_G, TURQUESA_B), (coord.x)-6 , (coord.y)-4 , 0);
        }
    }
}

void bala_nave_draw(bala_nave_t* bala_nave)
{
    if(bala_nave->used)
    {        
        al_draw_tinted_bitmap(sevenup.bala_nave, al_map_rgb(BLANCO_R, BLANCO_G, BLANCO_B), bala_nave->pos_centro.x , bala_nave->pos_centro.y , 0);
    }
    else
    {
        explosion_bala_nave_draw(bala_nave);
    }
}

void a_nave_update(void)
{
    if(my_ship.doa && !(my_ship.explode) && !(my_ship.wait_for_revival))
    {
        if(key[ALLEGRO_KEY_RIGHT] && my_ship.centro.x+1 <= (DISP_MAX_X-6))	//Analiza si la nave se puede mover a la Izquierda
        {
            ship_move(DER, 0);	//Mueve la nave a la derecha
        }

        if(key[ALLEGRO_KEY_LEFT] && my_ship.centro.x-1 >= (DISP_MIN+6))	//Analiza se la nave se puede mover a la derecha
        {
            ship_move(IZQ, 0);	//Mueve la nave a la izquierda
        }        
    }
    
    if(my_ship.doa && !(my_ship.explode) && !(my_ship.wait_for_revival) && alienvsnave())
    {
        gamemode = GAME_OVER;
    }

    else if(my_ship.explode)
    {
        if( (my_ship.explosion_animation == 0) && my_ship.explosion_animation_duration)
        {
            my_ship.explosion_animation_duration--;
        }
        else if((my_ship.explosion_animation == 0) && !(my_ship.explosion_animation_duration))
        {
            my_ship.explosion_animation_duration = NAVE_ROTA_FRAMES;
            my_ship.explosion_animation = 1;
        }
        else if((my_ship.explosion_animation == 1) && my_ship.explosion_animation_duration)
        {
            my_ship.explosion_animation_duration--;
        }
        else if((my_ship.explosion_animation == 1) && !(my_ship.explosion_animation_duration))
        {
            my_ship.explode = false;
            
            my_ship.centro.x= CENTRO_X;
            my_ship.centro.y= CENTRO_Y;
            my_ship.wait_for_revival = WAIT;            
        }
    }
    else if(my_ship.wait_for_revival)
    {
        my_ship.wait_for_revival--;
    }
    else if(!(my_ship.doa))
    {
        gamemode = GAME_OVER;
    }
}

bool press_chck(void)   //se podría adaptar para los movimientos de la nave pero se me sigue sin ocurrir cómo pasarle el dato q necesitan los chicos, a menos que usemos memoria dinámica y le pasemos el puntero...?
{
    bool press_status = false;
    
    if(key[ALLEGRO_KEY_SPACE])
    {
        press_status = true;
    }
    return press_status;
}

void bala_nave_colision(bala_nave_t* bala_nave, bala_alien_t* bala_alien, game_status_t* game_stat)
{
    bool col_al = colision_alien(bala_nave, game_stat); 
    if( col_al || colision_barrera(bala_nave, bala_alien, BALA_NAVE, aliens[0][0]) || colision_balas(bala_nave, bala_alien))
    {
        bala_nave->used = false;
        bala_nave->show_explosion = BALA_NAVE_EXPLOSION_FRAMES;
        
        if(!col_al)
        {
            bala_nave->coord_explosion = bala_nave->next_pos_centro;
        }        
    }
    
    else
    {
        bala_nave->pos_centro = bala_nave->next_pos_centro;
    }
}

bool colision_alien(bala_nave_t* bala_nave, game_status_t* game_stat)
{
    bool colisiono = false;
    
    if( nave_nodriza.doa && collission_chck(nave_nodriza.centro.x-7,
                                            nave_nodriza.centro.y-3,
                                            nave_nodriza.centro.x+8,
                                            nave_nodriza.centro.y+3,
                                            BALA_NAVE_X0(bala_nave->next_pos_centro.x),
                                            BALA_NAVE_Y0(bala_nave->next_pos_centro.y),
                                            BALA_NAVE_XF(bala_nave->next_pos_centro.x),
                                            BALA_NAVE_YF(bala_nave->next_pos_centro.y)))
    {
        nave_nodriza.doa = DEAD;
        bala_nave->coord_explosion = nave_nodriza.centro;
        colisiono = true;
        game_stat->points = points(NODRIZA, game_stat->points); 
    }
    
    else
    {
        for( int i=0 ; i<CANT_FIL && !colisiono ; i++)
        {
            switch(i)
            {
                case ALIEN1:
                {
                    for(int a=0 ; a<CANT_1 && !colisiono ; a++)
                    {
                        if( (aliens[ALIEN1][a].doa == ALIVE) && 
                            (collission_chck(ALIEN1_X0(aliens[ALIEN1][a].centro.x),
                                             ALIEN1_Y0(aliens[ALIEN1][a].centro.y),
                                             ALIEN1_XF(aliens[ALIEN1][a].centro.x),
                                             ALIEN1_YF(aliens[ALIEN1][a].centro.y),
                                             BALA_NAVE_X0(bala_nave->next_pos_centro.x),
                                             BALA_NAVE_Y0(bala_nave->next_pos_centro.y),
                                             BALA_NAVE_XF(bala_nave->next_pos_centro.x),
                                             BALA_NAVE_YF(bala_nave->next_pos_centro.y))
                            )
                          )
                        {
                            aliens[ALIEN1][a].doa--;
                            bala_nave->coord_explosion = aliens[ALIEN1][a].centro;
                            colisiono = true;
                            game_stat->points = points(ALIEN1, game_stat->points); 
                            game_stat->deadaliens++; 
                        }
                    }
                    break;                
                }
                case ALIEN2:
                {
                    for(int b=0 ; b<CANT_2 && !colisiono ; b++)
                    {
                        if( (aliens[ALIEN2][b].doa == ALIVE) && 
                            (collission_chck(ALIEN2_X0(aliens[ALIEN2][b].centro.x),
                                             ALIEN2_Y0(aliens[ALIEN2][b].centro.y),
                                             ALIEN2_XF(aliens[ALIEN2][b].centro.x),
                                             ALIEN2_YF(aliens[ALIEN2][b].centro.y),
                                             BALA_NAVE_X0(bala_nave->next_pos_centro.x),
                                             BALA_NAVE_Y0(bala_nave->next_pos_centro.y),
                                             BALA_NAVE_XF(bala_nave->next_pos_centro.x),
                                             BALA_NAVE_YF(bala_nave->next_pos_centro.y))
                            )
                          )
                        {
                            aliens[ALIEN2][b].doa--;
                            bala_nave->coord_explosion = aliens[ALIEN2][b].centro;
                            colisiono = true;
                            game_stat->points = points(ALIEN2, game_stat->points); 
                            game_stat->deadaliens++;
                        }
                    }
                    break;                
                }
                case ALIEN3:
                {
                    for(int c=0 ; c<CANT_3 && !colisiono ; c++)
                    {
                        if( (aliens[ALIEN3][c].doa == ALIVE) && 
                            (collission_chck(ALIEN3_X0(aliens[ALIEN3][c].centro.x),
                                             ALIEN3_Y0(aliens[ALIEN3][c].centro.y),
                                             ALIEN3_XF(aliens[ALIEN3][c].centro.x),
                                             ALIEN3_YF(aliens[ALIEN3][c].centro.y),
                                             BALA_NAVE_X0(bala_nave->next_pos_centro.x),
                                             BALA_NAVE_Y0(bala_nave->next_pos_centro.y),
                                             BALA_NAVE_XF(bala_nave->next_pos_centro.x),
                                             BALA_NAVE_YF(bala_nave->next_pos_centro.y))
                            )
                          )
                        {
                            aliens[ALIEN3][c].doa--;
                            bala_nave->coord_explosion = aliens[ALIEN3][c].centro;
                            colisiono = true;
                            game_stat->points = points(ALIEN3, game_stat->points); 
                            game_stat->deadaliens++;
                        }
                    }
                    break;                
                }
            }
        }        
    }
   
    return colisiono;
}

bool colision_balas(bala_nave_t* bala_nave, bala_alien_t* bala_alien)
{
    bool colisionaron = false;

    if( bala_nave->used && bala_alien->used && collission_chck(BALA_NAVE_X0(bala_nave->next_pos_centro.x),
                                                               BALA_NAVE_Y0(bala_nave->next_pos_centro.y),
                                                               BALA_NAVE_XF(bala_nave->next_pos_centro.x),
                                                               BALA_NAVE_YF(bala_nave->next_pos_centro.y),
                                                               BALA_ALIEN_X0(bala_alien->next_pos_centro.x),
                                                               BALA_ALIEN_Y0(bala_alien->next_pos_centro.y),
                                                               BALA_ALIEN_XF(bala_alien->next_pos_centro.x),
                                                               BALA_ALIEN_YF(bala_alien->next_pos_centro.y)))
    {
        colisionaron = true;
        bala_alien->used = false;
        bala_alien->show_explosion = 0;
    }
    return colisionaron;
}

void explosion_bala_nave_draw(bala_nave_t* bala_nave)
{
    if(bala_nave->show_explosion)
    {
        al_draw_tinted_bitmap(sevenup.explosion_alien, al_map_rgb(BLANCO_R, BLANCO_G, BLANCO_B), (bala_nave->coord_explosion.x)-6 , (bala_nave->coord_explosion.y)-4 , 0);
        bala_nave->show_explosion--;
    }
}

bool alienvsnave(void)
{
    bool colisiono = false;
    
    for(int a=0 ; a<CANT_1 && !colisiono ; a++)
    {
        if( (aliens[ALIEN1][a].doa == ALIVE) && 
            (collission_chck(ALIEN1_X0(aliens[ALIEN1][a].centro.x),
                             ALIEN1_Y0(aliens[ALIEN1][a].centro.y),
                             ALIEN1_XF(aliens[ALIEN1][a].centro.x),
                             ALIEN1_YF(aliens[ALIEN1][a].centro.y),
                             (my_ship.centro.x-6),
                             (my_ship.centro.y-4),
                             (my_ship.centro.x+6),
                             (my_ship.centro.y+3))))
        {
            gamemode= GAME_OVER;
            colisiono = true;
        }
    }
    for(int b=0 ; b<CANT_2 && !colisiono ; b++)
    {
        if( (aliens[ALIEN2][b].doa == ALIVE) && 
            (collission_chck(ALIEN2_X0(aliens[ALIEN2][b].centro.x),
                             ALIEN2_Y0(aliens[ALIEN2][b].centro.y),
                             ALIEN2_XF(aliens[ALIEN2][b].centro.x),
                             ALIEN2_YF(aliens[ALIEN2][b].centro.y),
                             (my_ship.centro.x-6),
                             (my_ship.centro.y-4),
                             (my_ship.centro.x+6),
                             (my_ship.centro.y+3))))
        {
            gamemode= GAME_OVER;
            colisiono = true;
        }
    }
    for(int c=0 ; c<CANT_3 && !colisiono ; c++)
    {
        if( (aliens[ALIEN3][c].doa == ALIVE) && 
            (collission_chck(ALIEN3_X0(aliens[ALIEN3][c].centro.x),
                             ALIEN3_Y0(aliens[ALIEN3][c].centro.y),
                             ALIEN3_XF(aliens[ALIEN3][c].centro.x),
                             ALIEN3_YF(aliens[ALIEN3][c].centro.y),
                             (my_ship.centro.x-6),
                             (my_ship.centro.y-4),
                             (my_ship.centro.x+6),
                             (my_ship.centro.y+3))))
        {
            gamemode= GAME_OVER;
            colisiono = true;
        }
    }
    return colisiono;
}

#endif //ALLEGRO

#ifdef RASPI

void print_ship(dcoord_t center, dlevel_t value, char doa)
{
	ship_t aux;
	aux.centro.y= center.y;
	gral_write(center, value , NAVE);
	aux.centro.x= center.x + 1;
	gral_write(aux.centro, value , NAVE);
	aux.centro.x= center.x - 1;
	gral_write(aux.centro, value , NAVE);
	aux.centro.y= center.y - 1;
	aux.centro.x= center.x;
	gral_write(aux.centro, value , NAVE);

}
	
void r_nave_update(jcoord_t coord)
{
    if(coord.x > THRESHOLD && my_ship.centro.x+1 < DISP_MAX_X)	//Analiza si la nave se puede mover a la Izquierda
    {
	ship_move(DER, 0);	//Mueve la nave a la derecha
    }
			
    if(coord.x < -THRESHOLD && my_ship.centro.x-1 > DISP_MIN)	//Analiza se la nave se puede mover a la derecha
    {
	ship_move(IZQ, 0);	//Mueve la nave a la izquierda
    }
			
    joy_update();
}

bool press_chck(void)
{
    bool press_status = false;
    static int press = RESTART;
    
    if(joy_get_switch() != J_NOPRESS)
    {
        press_status = true;
        press +=1;

        if(press >= DURATION_PRESS)
        {
            gamemode=PAUSE;
            press = RESTART;
        }
    }
    else
    {
        press=RESTART;
    }

    
    return press_status;
}

void picanazo (bala_nave_t* bala_nave, game_status_t* game_stat, bala_alien_t* bala_alien)       //Detecta si una bala mato un alien o al jugador o chocó otra bala
{ 
    //Chequea si van a chocar dos balas
    //printf("PICANAZO: Chequeo si hay bala en next pos \n");
    if ((LEDMatrix[bala_nave->next_pos_centro.y][bala_nave->next_pos_centro.x].entity == BALA) )  //Si hay una bala arriba
    {
                //printf("PICANAZO: Imprimo en pantalla, entro a función con POS: [%d][%d] C  \n", bala_nave->pos_centro.x,bala_nave->pos_centro.y);
        gral_write(bala_nave->pos_centro, D_OFF, VOID);    //Elimina esta bala
                //printf("PICANAZO: Imprimo en pantalla, NEXTPOS: [%d][%d] \n",bala_nave->next_pos_centro.x,bala_nave->next_pos_centro.y);
        gral_write(bala_nave->next_pos_centro, D_OFF, VOID);     //Y la otra

        bala_nave->used= false;
        bala_alien->used= false;  
    }

    else if((LEDMatrix[bala_nave->next_pos_centro.y][bala_nave->next_pos_centro.x].entity == ALIEN) || (LEDMatrix[bala_nave->pos_centro.y][bala_nave->pos_centro.x].entity == ALIEN))
    {
            //printf("PICANAZO: Es un Alien, entro a función con POS A: [%d][%d]  \n", bala_nave->pos_centro.x,bala_nave->pos_centro.y);
            if((LEDMatrix[bala_nave->next_pos_centro.y][bala_nave->next_pos_centro.x].entity == ALIEN))
            {
                delete_alien(LEDMatrix[bala_nave->next_pos_centro.y][bala_nave->next_pos_centro.x].ID, &(game_stat->points));
            }
            else
            {
                delete_alien(LEDMatrix[bala_nave->pos_centro.y][bala_nave->pos_centro.x].ID, &(game_stat->points));
            }
            //getchar();
        
            //printf("ID: %d  toa: %d  center.x: %d  center.y: %d \n ", ID, aliens[0][ID-1].typeofalien, aliens[0][ID-1].centro.x, aliens[0][ID-1].centro.y);
        
        gral_write(bala_nave->pos_centro, D_OFF, VOID);    //Elimina esta bala
        bala_nave->used= false;
        (game_stat->deadaliens)++;
            //disp_update();
            //getchar();
    }

    else if(LEDMatrix[bala_nave->next_pos_centro.y][bala_nave->next_pos_centro.x].entity == WALL)
    {
                //printf("PICANAZO: Es un Wall, entro a función con POS B: [%d][%d]  \n", bala_nave->pos_centro.x,bala_nave->pos_centro.y);
        gral_write(bala_nave->pos_centro, D_OFF, VOID);    //Elimina esta bala
                //printf("PICANAZO: Es un Wall, NEXTPOS: [%d][%d] \n",bala_nave->next_pos_centro.x,bala_nave->next_pos_centro.y);
        gral_write(bala_nave->next_pos_centro, D_OFF, VOID);     //Y el pixel de barrera

        bala_nave->used= false;
    }

    else if((LEDMatrix[bala_nave->next_pos_centro.y][bala_nave->next_pos_centro.x].entity == NODRIZA) || (LEDMatrix[bala_nave->pos_centro.y][bala_nave->pos_centro.x].entity == NODRIZA))
    {
        gral_write(bala_nave->pos_centro, D_OFF, VOID);    //Elimina esta bala
        game_stat->points += NODRIZA_SCORE;
        bala_nave->used= false;
        print_alien(nave_nodriza.centro, 0 ,nave_nodriza.typeofalien, ALIVE, D_OFF, ID_Nodriza);
        nave_nodriza.doa=DEAD;
    }

    bala_nave->pos_centro = bala_nave->next_pos_centro;

}

void delete_alien(uint8_t ID, int* points )
{
    printf("ID= [%d] \n", ID);
    if((ID <= CANT_1) && (ID >= 0))
    {
        //printf("Enters Here A \n");
        ID--;
        print_alien(aliens[ALIEN1][ID].centro, aliens[ALIEN1][ID].animacion, ALIEN1, aliens[ALIEN1][ID].doa, D_OFF, ID);
        aliens[ALIEN1][ID].doa=DEAD;
        (*points) += ALIEN1_SCORE;

    }
    else if ((ID <= (CANT_2 + CANT_1) ) && (ID > CANT_1))
    {
        //printf("Enters Here B \n");
        ID -= (CANT_1+1);
        print_alien(aliens[ALIEN2][ID].centro, aliens[ALIEN2][ID].animacion, ALIEN2, aliens[ALIEN2][ID].doa, D_OFF, ID);
        aliens[ALIEN2][ID].doa=DEAD;
        (*points) += ALIEN2_SCORE;

    }
    else if ((ID <= (CANT_3 + CANT_2 + CANT_1 )) && (ID > (CANT_2 + CANT_1)))
    {
        //printf("Enters Here C \n");
        ID -= (CANT_1+CANT_2+1);
        print_alien(aliens[ALIEN3][ID].centro, aliens[ALIEN3][ID].animacion, ALIEN3, aliens[ALIEN3][ID].doa, D_OFF, ID);
        aliens[ALIEN3][ID].doa=DEAD;
        (*points) += ALIEN3_SCORE;

    }
    else
    {
        printf("Error in ID Alien \n");
        getchar();
    }
}

void dead_ship_animation(void)
{
    int ship_time_animation=1;
    disp_update();

    while(ship_time_animation%SHIP_DEATH_ANIMATION)
    {
        ship_time_animation++;
        usleep(1);
    }
    ship_time_animation=1;

    dcoord_t aux= my_ship.centro;
    aux.x++;
    aux.y--;

    print_ship(my_ship.centro, D_OFF, NAVE);
    
    gral_write(aux, D_ON, PIXEL_ART);
    aux.x -=2;
    gral_write(aux, D_ON, PIXEL_ART);
    aux.y +=2;
    gral_write(aux, D_ON, PIXEL_ART);
    aux.x +=2;
    gral_write(aux, D_ON, PIXEL_ART);

    disp_update();
    while(ship_time_animation%SHIP_DEATH_ANIMATION)
    {
        ship_time_animation++;
        usleep(1);
    }
    ship_time_animation=1;
    gral_write(aux, D_OFF, VOID);
    aux.x -=2;
    gral_write(aux, D_OFF, VOID);
    aux.y -=2;
    gral_write(aux, D_OFF, VOID);
    aux.x +=2;
    gral_write(aux, D_OFF, VOID);

    print_ship(my_ship.centro, D_ON, NAVE);

    disp_update();
    while(ship_time_animation%SHIP_DEATH_ANIMATION)
    {
        ship_time_animation++;
        usleep(1);
    }

}

#endif //RASPI
