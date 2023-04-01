
#include "main.h"
#include "alien.h"

#ifdef RASPI
#include "ship.h"
#endif //RASPI

#ifdef ALLEGRO
#include "a_main.h"
#include "puntos.h"

// VARIABLES GLOBALES DEL MAIN

    extern ALLEGRO_DISPLAY* disp;
    extern ALLEGRO_BITMAP* buff;
    extern sprites_t sevenup;
    extern unsigned char key[ALLEGRO_KEY_MAX];

    extern ship_t my_ship;
#endif //ALLEGRO

#ifdef RASPI
#include "r_main.h"
extern led_t LEDMatrix[16][16];
extern char deadAliens;
extern ship_t my_ship;
#endif // RASPI

extern alien_t alien1 [CANT_1];
extern alien_t alien2 [CANT_2];
extern alien_t alien3 [CANT_3];
extern alien_t nave_nodriza;
extern alien_t* aliens[CANT_FIL];

void alien_init(void)
{
    
   for(int i=0; i<CANT_1; i++ )
    {        
        (aliens[ALIEN1][i]).centro.x = POS_CENTRO_ALIEN1_X(i);          //Inicializa el centro X de cada ALien en X de los aliens de la primera fila
        aliens[ALIEN1][i].centro.y = POS_CENTRO_ALIEN1_Y(i);            //Inicializa el centro Y de cada ALien en X de los aliens de la primera fila
        aliens[ALIEN1][i].doa = ALIVE;                                  //Le asigna que está vivo
        aliens[ALIEN1][i].typeofalien = ALIEN1;                         //Asigna que tipo de Alien es
        aliens[ALIEN1][i].ID = i+1;

        aliens[ALIEN1][i].animacion = 1;
       
        print_alien(aliens[ALIEN1][i].centro, aliens[ALIEN1][i].animacion, ALIEN1, aliens[ALIEN1][i].doa, D_ON, i+1);      //Se suma 1 porque 0 es que no hay alien
    } 

    for(int j=0; j<CANT_2; j++ )
    {
        aliens[ALIEN2][j].centro.x = POS_CENTRO_ALIEN2_X(j);                         
        aliens[ALIEN2][j].centro.y = POS_CENTRO_ALIEN2_Y(j);                             
        aliens[ALIEN2][j].doa = ALIVE;                              
        aliens[ALIEN2][j].typeofalien = ALIEN2; 
        aliens[ALIEN2][j].ID = j+CANT_1+1;                    
        
        aliens[ALIEN2][j].animacion = 1;
        
        print_alien(aliens[ALIEN2][j].centro, aliens[ALIEN2][j].animacion, ALIEN2, aliens[ALIEN2][j].doa, D_ON, j+CANT_1+1);       
    }
    

    for(int k=0; k<CANT_3; k++ )                                                 
    {
        aliens[ALIEN3][k].centro.x = POS_CENTRO_ALIEN3_X(k);
        aliens[ALIEN3][k].centro.y = POS_CENTRO_ALIEN3_Y(k);
        aliens[ALIEN3][k].doa = ALIVE;
        aliens[ALIEN3][k].typeofalien = ALIEN3;
        aliens[ALIEN3][k].ID = k+(CANT_1+CANT_2+1);
        
        aliens[ALIEN3][k].animacion = 1;
        
        print_alien(aliens[ALIEN3][k].centro, aliens[ALIEN3][k].animacion, ALIEN3, aliens[ALIEN3][k].doa, D_ON, k+CANT_1+CANT_2+1);
    }

    
    nave_nodriza.centro.x = NODRIZA_FAR_RIGHT;
    nave_nodriza.centro.y = NODRIZA_Y_POS;
    #ifdef ALLEGRO
    nave_nodriza.doa = DEAD;
    #endif //ALLEGRO
    #ifdef RASPI
    nave_nodriza.doa = ALIVE;
    #endif //RASPI
    nave_nodriza.typeofalien = NODRIZA;
    nave_nodriza.used= false;
    nave_nodriza.spawn_condition= SPAWN_CONDITION;
    print_alien(nave_nodriza.centro, 0 ,nave_nodriza.typeofalien, ALIVE, D_ON, ID_Nodriza);
    
}

void bala_alien_init(bala_alien_t* bala_alien)
{
    bala_alien->used = false;
    bala_alien->animacion = BALA1;
    bala_alien->show_explosion = 0;
}

void bala_alien_update(bala_alien_t* bala_alien, game_status_t* game_stat, bala_nave_t* bala_nave )
{
    if(!(bala_alien->used) && !(bala_alien->show_explosion))
    {
        *bala_alien = gen_alien_bala();
    }
    else if(bala_alien->used)
    {
        bala_alien->next_pos_centro = bala_alien->pos_centro;
        #ifdef RASPI
        bala_alien->next_pos_centro.y += PASO_BALA_ALIEN;
        #endif //RASPI

        #ifdef ALLEGRO
        if(game_stat->level>2)
        {
            bala_alien->next_pos_centro.y += PASO_BALA_ALIEN_DIFICIL;
        }
        else
        {
            bala_alien->next_pos_centro.y += PASO_BALA_ALIEN;
        }
        #endif //ALLEGRO
        
        if( 0>=(bala_alien->next_pos_centro.y) || (bala_alien->next_pos_centro.y)>=H)
        {
            bala_alien->used = false;
            #ifdef ALLEGRO
            piso_update(bala_alien);
            bala_alien->show_explosion = BALA_ALIEN_EXPLOSION_FRAMES;
            bala_alien->coord_explosion.x = bala_alien->pos_centro.x;
            bala_alien->coord_explosion.y = 206;
            #endif //ALLEGRO
            
            #ifdef RASPI
            gral_write(bala_alien->pos_centro, D_OFF, BALA);
            #endif //RASPI
        }
        
        else
        {
            #ifdef ALLEGRO
            bala_alien_colision(bala_alien);
            #endif //ALLEGRO
            
            #ifdef RASPI
            alien_picanazo(bala_alien, game_stat, bala_nave); //si no hay colisión, devuelve siguiente posición

            if(bala_alien->used)
            { 
                gral_write(bala_alien->pos_centro, D_ON, BALA);
                bala_alien->pos_centro.y -=1;

                gral_write(bala_alien->pos_centro, D_OFF, BALA);
                bala_alien->pos_centro.y +=1;
            }                         
            
            #endif //RASPI
        } 
    }
}                       
                        
bala_alien_t gen_alien_bala(void) //debería entrar acá sólo si hay aliens vivos pues no chequea que todos lo estén, asume que hay
{
    bala_alien_t bala_generada;
    bool generada = false;
      
    while (!generada)
    {
        int n_col = rand()% CANT_1;

        for(int i=CANT_FIL-1 ; ((i>=0) && (!generada)); i--)
        {
            switch(i)
            {
                case ALIEN3:
                {
                    
                    if(aliens[i][(int) (COL_ALIEN_2y3_a(n_col))].doa == ALIVE)
                    {
                        bala_generada.pos_centro.x = aliens[i][(int) (COL_ALIEN_2y3_a(n_col))].centro.x;
                        bala_generada.pos_centro.y = aliens[i][(int) (COL_ALIEN_2y3_a(n_col))].centro.y + DESPL3_Y;
                        generada = true;
                        bala_generada.used = true;
                    }
                    #ifdef ALLEGRO
                    else if(aliens[i][(int) (COL_ALIEN_2y3_b(n_col))].doa == ALIVE)
                    {
                        bala_generada.pos_centro.x = aliens[i][(int) (COL_ALIEN_2y3_b(n_col))].centro.x;
                        bala_generada.pos_centro.y = aliens[i][(int) (COL_ALIEN_2y3_b(n_col))].centro.y + DESPL3_Y;
                        generada = true;
                        bala_generada.used = true;                            
                    }
                    #endif //ALLEGRO
                    break;
                    
                }

                case ALIEN2:
                {                    
                    if(aliens[i][(int) (COL_ALIEN_2y3_a(n_col))].doa == ALIVE)
                    {
                        bala_generada.pos_centro.x = aliens[i][(int) (COL_ALIEN_2y3_a(n_col))].centro.x;
                        bala_generada.pos_centro.y = aliens[i][(int) (COL_ALIEN_2y3_a(n_col))].centro.y + DESPL2_Y;
                        generada = true;
                        bala_generada.used = true;
                    }
                    #ifdef ALLEGRO
                    else if(aliens[i][(int) (COL_ALIEN_2y3_b(n_col))].doa == ALIVE)
                    {
                        bala_generada.pos_centro.x = aliens[i][(int) (COL_ALIEN_2y3_b(n_col))].centro.x;
                        bala_generada.pos_centro.y = aliens[i][(int) (COL_ALIEN_2y3_b(n_col))].centro.y + DESPL2_Y;
                        generada = true;
                        bala_generada.used = true;                            
                    }
                    #endif //ALLEGRO
                    break;
                }

                case ALIEN1:
                {                    
                    if(aliens[i][(int) (COL_ALIEN_1(n_col))].doa == ALIVE)
                    {
                        bala_generada.pos_centro.x = aliens[i][(int) (n_col)].centro.x;
                        bala_generada.pos_centro.y = aliens[i][(int) (n_col)].centro.y + DESPL1_Y;
                        generada = true;
                        bala_generada.used = true;
                    }
                    break;
                }
            }
                
            #ifdef ALLEGRO
            tipo_bala_alien(&bala_generada);
            bala_alien_animacion(&bala_generada);
            #endif //ALLEGRO
            
        }        
    }
  
    return bala_generada;
}


#ifdef ALLEGRO

void print_alien(dcoord_t coord, char animacion, toa_t toa, char doa, dlevel_t value_type, char ID)
{ 
    if(doa)
    {       
        switch(toa)
        {
            case ALIEN1:
            {
                al_draw_tinted_bitmap(sevenup.alien1[animacion], al_map_rgb(VERDE_R, VERDE_G, VERDE_B), (coord.x)-3 , (coord.y)-3 , 0);
                break;
            }
            
            case ALIEN2:
            {
                al_draw_tinted_bitmap(sevenup.alien2[animacion], al_map_rgb(AMARILLO_R, AMARILLO_G, AMARILLO_B), (coord.x)-5 , (coord.y)-3 , 0);
                break;
            }
            
            case ALIEN3:
            {
                al_draw_tinted_bitmap(sevenup.alien3[animacion], al_map_rgb(ROJO_R, ROJO_G, ROJO_B), (coord.x)-5 , (coord.y)-3 , 0);
                break;
            }
            
            case NODRIZA:
            {
                al_draw_tinted_bitmap(sevenup.nave_nodriza, al_map_rgb(ROSA_R, ROSA_G, ROSA_B), (coord.x)-7 , (coord.y)-3 , 0);
                break;
            }
        }
    }
}

void tipo_bala_alien(bala_alien_t* bala_alien)
{    
    bala_alien->tipo_bala = rand()% CANT_BALAS;
    
    /*
    if(bala_alien->tipo_bala < BALA3)
    {
        bala_alien->tipo_bala++;
    }
    else
    {
        bala_alien->tipo_bala = BALA1;
    }
    */
}

void bala_alien_animacion(bala_alien_t* bala_alien)
{
    if(bala_alien->animacion < (CANT_BALA_ANIM-1) )
    {
        bala_alien->animacion++; //probablemente haya q cambiar los frames
    }
    else
    {
        bala_alien->animacion = 0;
    }
}

void bala_alien_draw(bala_alien_t* bala_alien) //centro abajo de todo de la bala al centro de x
{
    if(bala_alien->used)
    {       
        switch(bala_alien->tipo_bala)
        {
            case BALA1:
            {
                al_draw_tinted_bitmap(sevenup.bala_alien1[bala_alien->animacion], al_map_rgb(BLANCO_R, BLANCO_G, BLANCO_B), (bala_alien->pos_centro.x-1) , (bala_alien->pos_centro.y-6) , 0);
                break;
            }
            case BALA2:
            {
                al_draw_tinted_bitmap(sevenup.bala_alien2[bala_alien->animacion], al_map_rgb(BLANCO_R, BLANCO_G, BLANCO_B), (bala_alien->pos_centro.x-1) , (bala_alien->pos_centro.y-6) , 0);
                break;
            }
            case BALA3:
            {
                al_draw_tinted_bitmap(sevenup.bala_alien3[bala_alien->animacion], al_map_rgb(BLANCO_R, BLANCO_G, BLANCO_B), (bala_alien->pos_centro.x-1) , (bala_alien->pos_centro.y-6) , 0);
                break;
            }
        }
    }
    else
    {
        explosion_bala_alien_draw(bala_alien);
    }
    
}

void bala_alien_colision(bala_alien_t* bala_alien)
{
    bala_nave_t* bala_nave; //es para no cambiar prototipos de las funciones que ya hice, colision_barrera no lo va a usar
    
    bool col_nave = colision_nave(bala_alien);
    
    if( col_nave || colision_barrera(bala_nave, bala_alien, BALA_ALIEN, aliens[0][0]) )
    {
        bala_alien->used = false;
        if(col_nave)
        {            
            explosion_por_bala_alien(bala_alien, COL_NAVE);
        }
        else
        {
            explosion_por_bala_alien(bala_alien, COL_BARR);
        }
    }
    else
    {
        bala_alien->pos_centro = bala_alien->next_pos_centro;
        bala_alien_animacion(bala_alien);
    }
}

bool colision_nave(bala_alien_t* bala_alien)
{
    bool collided = false;
    if(collission_chck(BALA_ALIEN_X0(bala_alien->next_pos_centro.x),
                       BALA_ALIEN_Y0(bala_alien->next_pos_centro.y),
                       BALA_ALIEN_XF(bala_alien->next_pos_centro.x),
                       BALA_ALIEN_YF(bala_alien->next_pos_centro.y),
                       (my_ship.centro.x-6),
                       (my_ship.centro.y-4),
                       (my_ship.centro.x+6),
                       (my_ship.centro.y+3))
        && my_ship.doa) //chequeo esto siquiera?
    {
        my_ship.doa--;
        collided = true;
        bala_alien->show_explosion = 0;
    }
    return collided;
}

void explosion_por_bala_alien(bala_alien_t* bala_alien, int entity)
{
    switch(entity)
    {
        case COL_NAVE:
        {
            my_ship.explode = true;
            my_ship.explosion_animation = 0;
            my_ship.explosion_animation_duration = NAVE_ROTA_FRAMES;
            break;
        }
        case COL_BARR:
        {
            bala_alien->show_explosion = BALA_ALIEN_EXPLOSION_FRAMES;
            bala_alien->coord_explosion = bala_alien->pos_centro;
            break;
        }
    }
}

void explosion_bala_alien_draw(bala_alien_t* bala_alien)
{
    if(bala_alien->show_explosion)
    {
        al_draw_tinted_bitmap(sevenup.explosion[0], al_map_rgb(BLANCO_R, BLANCO_G, BLANCO_B), (bala_alien->coord_explosion.x)-3 , (bala_alien->coord_explosion.y)-4 , 0);
        bala_alien->show_explosion--;
    }
}

void aliens_movement (game_status_t* game_stat)
{
    static int despX = DER;
    int despY = 0;
    static char animacion = 0;
    
    if(animacion == 0)
    {
        animacion = 1;
    }
    else
    {
        animacion = 0;
    }

    if(despX == DER && ((max_coord() + ANCHO_ALIENS/2) == BUFFER_ANCHO))  //si va a la derecha y llego al limite
    {
        despX = IZQ;    //cambia de direccion
        despY = AB;     //se mueven uno hacia abajo
        game_stat->aliens_position++;
    }
    else if(despX == IZQ && ((min_coord() - ANCHO_ALIENS/2) == 0))    //si va a la izquierda y llegó al limite
    {
        despX = DER;    //cambia de dirección
        despY = AB;     //se mueven uno hacia abajo
        game_stat->aliens_position++;
    }

    bala_nave_t* bala1;
    bala_alien_t* bala2;
    
    for (int a = 0; a < CANT_1; a++)
    {
        if(aliens[ALIEN1][a].doa == ALIVE)
        {
            aliens[ALIEN1][a].centro.x += despX;
            aliens[ALIEN1][a].centro.y += despY;
            aliens[ALIEN1][a].animacion = animacion;
                                         
            if(!(colision_barrera(bala1, bala2,ALIENS,aliens[ALIEN1][a])) && (aliens[ALIEN1][a].centro.y>=CENTRO_Y))
            {
                gamemode = GAME_OVER;
            }
        }
    }
    for (int b = 0; b < CANT_2; b++)
    {
        if(aliens[ALIEN2][b].doa == ALIVE)
        {
            aliens[ALIEN2][b].centro.x += despX;
            aliens[ALIEN2][b].centro.y += despY;
            aliens[ALIEN2][b].animacion = animacion;

            colision_barrera(bala1, bala2,ALIENS,aliens[ALIEN2][b]);
            
            if(!(colision_barrera(bala1, bala2,ALIENS,aliens[ALIEN2][b])) && (aliens[ALIEN2][b].centro.y>=CENTRO_Y))
            {
                gamemode = GAME_OVER;
            }
        }
    } 
    for (int c = 0; c < CANT_3; c++)
    {
        if(aliens[ALIEN3][c].doa == ALIVE)
        {
            aliens[ALIEN3][c].centro.x += despX;
            aliens[ALIEN3][c].centro.y += despY;
            aliens[ALIEN3][c].animacion = animacion;

            if(!(colision_barrera(bala1, bala2,ALIENS,aliens[ALIEN3][c])) && (aliens[ALIEN3][c].centro.y>=CENTRO_Y))
            {
                gamemode = GAME_OVER;
            }          
        }
    }
}

int max_coord(void)
{
    uint8_t coord = DISP_MIN;

    for(int a = 0; a < CANT_1; a++)
    {
        if(aliens[ALIEN1][a].doa == ALIVE && aliens[ALIEN1][a].centro.x > coord)
        {
            coord = aliens[ALIEN1][a].centro.x;
        }
    }

    for(int b = 0; b < CANT_2; b++)
    {
        if(aliens[ALIEN2][b].doa == ALIVE && aliens[ALIEN2][b].centro.x > coord)
        {
            coord = aliens[ALIEN2][b].centro.x;
        }
    }

    for(int c = 0; c < CANT_3; c++)
    {
        if(aliens[ALIEN3][c].doa == ALIVE && aliens[ALIEN3][c].centro.x > coord)
        {
            coord = aliens[ALIEN3][c].centro.x;
        }
    }

    return coord;
}

int min_coord(void)
{
    uint8_t coord = DISP_MAX_X;

    for(int a = 0; a < CANT_1; a++)
    {
        if(aliens[ALIEN1][a].doa == ALIVE && aliens[ALIEN1][a].centro.x < coord)
        {
            coord = aliens[ALIEN1][a].centro.x;
        }
    }

    for(int b = 0; b < CANT_2; b++)
    {
        if(aliens[ALIEN2][b].doa == ALIVE && aliens[ALIEN2][b].centro.x < coord)
        {
            coord = aliens[ALIEN2][b].centro.x;
        }
    }

    for(int c = 0; c < CANT_3; c++)
    {
        if(aliens[ALIEN3][c].doa == ALIVE && aliens[ALIEN3][c].centro.x < coord)
        {
            coord = aliens[ALIEN3][c].centro.x;
        }
    }

    return coord;
}

void aliens_draw(void)
{
    for (int a = 0; a < CANT_1; a++)
    {
        print_alien(aliens[ALIEN1][a].centro, aliens[ALIEN1][a].animacion, aliens[ALIEN1][a].typeofalien, aliens[ALIEN1][a].doa, D_ON, 'A');
    }
    for (int b = 0; b < CANT_2; b++)
    {
        print_alien(aliens[ALIEN2][b].centro, aliens[ALIEN2][b].animacion, aliens[ALIEN2][b].typeofalien, aliens[ALIEN2][b].doa, D_ON, 'A');
    } 
    for (int c = 0; c < CANT_3; c++)
    {
        print_alien(aliens[ALIEN3][c].centro, aliens[ALIEN3][c].animacion, aliens[ALIEN3][c].typeofalien, aliens[ALIEN3][c].doa, D_ON, 'A');
    }
    
    print_alien(nave_nodriza.centro, 0, nave_nodriza.typeofalien, nave_nodriza.doa, D_ON, 'A');
}

void a_nodriza_update(void)
{    
    static int intentos_spawn = 0;
    
    if( (nave_nodriza.doa == DEAD) && ((rand()%PROB) == HARDCODEADO) && (intentos_spawn>100))
    {
        nave_nodriza.doa = ALIVE;
        nave_nodriza.centro.x = NODRIZA_FAR_RIGHT;
    }
    else if(nave_nodriza.doa == ALIVE)
    {
        nave_nodriza.centro.x--;
        if((nave_nodriza.centro.x) == 0)
        {
            nave_nodriza.doa = DEAD;
        }
    }
    else
    {
        intentos_spawn++;
    }
}

void piso_init(void)
{
    for(int i = 0; i<CANT_PISO; i++)
    {
        piso[i].esq_izq.x = i*LONG_PISO;
        piso[i].esq_izq.y = 209;
        piso[i].intacta = true;
    }
}

void piso_update(bala_alien_t* bala_alien)
{
    bool colisiono = false;
    
    for(int i = 0; i<CANT_PISO && !colisiono; i++)
    {
        if(piso[i].intacta && collission_chck(BALA_ALIEN_X0(bala_alien->pos_centro.x),
                                              BALA_ALIEN_Y0(bala_alien->pos_centro.y),
                                              BALA_ALIEN_XF(bala_alien->pos_centro.x),
                                              BALA_ALIEN_YF(bala_alien->pos_centro.y),
                                              piso[i].esq_izq.x,
                                              piso[i].esq_izq.y,
                                              (piso[i].esq_izq.x+LONG_PISO),
                                              piso[i].esq_izq.y))
        {
            piso[i].intacta = false;
            colisiono = true;
        }        
    }
}

void piso_draw(void)
{
    for(int i = 0; i<CANT_PISO; i++)
    {
        if(piso[i].intacta)
        {
            al_draw_tinted_bitmap(sevenup.piso[0], al_map_rgb(ROJO_R, ROJO_G, ROJO_B), piso[i].esq_izq.x , piso[i].esq_izq.y , 0);
        }
        else
        {
            al_draw_tinted_bitmap(sevenup.piso[1], al_map_rgb(ROJO_R, ROJO_G, ROJO_B), piso[i].esq_izq.x , piso[i].esq_izq.y , 0);
        }
    }
}

#endif //ALLEGRO

#ifdef RASPI

void print_alien(dcoord_t center, char animacion, toa_t toa, char doa, dlevel_t value_type, char ID ) 
{
    switch(toa)     //Dependiendo de que tipo de alien es los imprime según la forma del alien
    {
        case ALIEN1:
        {
            /*
            Forma del Alien:
                    *
                    X
            X= Centro
            */
            alien_write(center, value_type, ALIEN, ALIEN1, ID);      //Imprime el primer pixel (*X)
            center.y= (center.y)-1;                     //Asigna el segundo pixel para luego Imprimirlo
            alien_write(center, value_type, ALIEN, ALIEN1, ID);      //Imprime el Segundo Pixel (X*)
            break;
        }
        case ALIEN2:
        {
            /*
            Forma del Alien:
                *X*
            X= Centro
            */
            dcoord_t aux = center;                  //Uso coords auxiliares para ir asignando los nuevos píxeles
            alien_write(center, value_type, ALIEN, ALIEN2, ID);  //Imprime el primer pixel (*X*)
            aux.x= (center.x)+1;        
            alien_write(aux, value_type, ALIEN, ALIEN2, ID);     //Imprime el segundo pixel (**X)
            aux.x= (center.x)-1;
            alien_write(aux, value_type, ALIEN, ALIEN2, ID);     //Imprime el tercer pixel (X**)
            break;
        }
        case ALIEN3:
        {
            /*
            Forma del Alien:
                *X*
                 *
            X= Centro
            */          
            dcoord_t aux =center;                   //Uso coords auxiliares para ir asignando los nuevos píxeles
            aux.x= (center.x)+1;
            alien_write(aux, value_type, ALIEN, ALIEN3, ID);     //Imprime el primer pixel (* X)/(*)
            aux.x= (center.x)-1;
            alien_write(aux, value_type, ALIEN, ALIEN3, ID);     //Imprime el segundo pixel (X *)/(*)
            aux.x= center.x;
            aux.y= (center.y)+1;
            alien_write(aux, value_type, ALIEN, ALIEN3, ID);     //Imprime el segundo pixel (* *)/(X)
            break;
        }
        case NODRIZA:
        {
            /*
            Forma del Alien:
                **
               **X*
               X= Centro
            */
            if( (center.x != NODRIZA_FAR_RIGHT) && (center.x != NODRIZA_FAR_LEFT) )   //si se encuentra en el extremo, no se imprime
            {
                alien_t aux_nodriza;
                for(int j=0; j<=1; j++) //Para los pixeles en Y=0 e Y=1
                {
                    for(int i=2; i>=-1; i--)    //Para los Píxeles desplazados respecto del centro
                    {
                        if( ((j==1) && (i==(2))) || ((j==1) && (i==(-1))) )
                        {

                        }
                        else if(((center.x-i)<= DISP_MAX_X) && ((center.x-i) >= DISP_MIN))
                        {
                            aux_nodriza.centro.x= (center.x-i);
                            aux_nodriza.centro.y= (center.y-j);

                            alien_write(aux_nodriza.centro, value_type, NODRIZA, NODRIZA, ID);
                        }
                
                    }

                }
        
            }
            else
            {
                //printf("No debo imprimir la nave en este caso \n");
            }
            break;
        }
        default:
        {
            //Not Needed
        }
    }
}

void alien_move (direc_t desp_x,direc_t desp_y)      //recibe las coordenadas actuales, la dirección y el tipo de alien a mover
{    
    for(int i=0; i<CANT_1; i++)
    {     
            //printf("Entro a Alien Move \n");
            //printf("Alien Move DEBUG, centro: x=[%i] y=[%i] entity: [%i] ", aliens[ALIEN1][i].centro.x, aliens[ALIEN1][i].centro.y,LEDMatrix[aliens[ALIEN1][i].centro.y][aliens[ALIEN1][i].centro.x].entity);
        //getchar();
        if(aliens[ALIEN1][i].doa != DEAD)
        {
            //printf("Entro en el primer if \n");
            char ID = aliens[ALIEN1][i].ID;
            print_alien(aliens[ALIEN1][i].centro, aliens[ALIEN1][i].animacion, ALIEN1, aliens[ALIEN1][i].doa, D_OFF, ID);
            aliens[ALIEN1][i].centro.x += desp_x;      //Desplaza el alien en X
            aliens[ALIEN1][i].centro.y += desp_y;      //Desplaza el alien en Y
            print_alien(aliens[ALIEN1][i].centro, aliens[ALIEN1][i].animacion, ALIEN1, aliens[ALIEN1][i].doa, D_ON, ID);            
        }else
        {
            aliens[ALIEN1][i].centro.x += desp_x;      //Desplaza el alien en X
            aliens[ALIEN1][i].centro.y += desp_y;      //Desplaza el alien en Y
        }
    } 

    for(int i=0; i<CANT_2; i++ )
    {        
        if(aliens[ALIEN2][i].doa != DEAD)
        {
            //printf("Entro en el segundo if \n");
            char ID = aliens[ALIEN2][i].ID;
            print_alien(aliens[ALIEN2][i].centro, aliens[ALIEN2][i].animacion, ALIEN2, aliens[ALIEN2][i].doa, D_OFF, ID);
            aliens[ALIEN2][i].centro.x += desp_x;      //Desplaza el alien en X
            aliens[ALIEN2][i].centro.y += desp_y;      //Desplaza el alien en Y
            print_alien(aliens[ALIEN2][i].centro, aliens[ALIEN2][i].animacion, ALIEN2, aliens[ALIEN2][i].doa, D_ON, ID);
        }
        else
        {

            aliens[ALIEN2][i].centro.x += desp_x;      //Desplaza el alien en X
            aliens[ALIEN2][i].centro.y += desp_y;      //Desplaza el alien en Y
        }
    } 
    for(int i=0; i<CANT_3; i++ )
    {        

        if(aliens[ALIEN3][i].doa != DEAD)
        {
            //printf("Entro en el tercer if \n");
            char ID = aliens[ALIEN3][i].ID;
            print_alien(aliens[ALIEN3][i].centro, aliens[ALIEN3][i].animacion, ALIEN3, aliens[ALIEN3][i].doa, D_OFF, ID);
            aliens[ALIEN3][i].centro.x += desp_x;      //Desplaza el alien en X
            aliens[ALIEN3][i].centro.y += desp_y;      //Desplaza el alien en Y
            print_alien(aliens[ALIEN3][i].centro, aliens[ALIEN3][i].animacion, ALIEN3, aliens[ALIEN3][i].doa, D_ON, ID);         
        }
        else
        {
            aliens[ALIEN3][i].centro.x += desp_x;      //Desplaza el alien en X
            aliens[ALIEN3][i].centro.y += desp_y;      //Desplaza el alien en Y
        }
    } 
}

void aliens_movement (game_status_t* game_stat) //Es un ciclo de movivmiento de los aliens
{

    //printf("ALIEN MOVEMENTS: Entro a Aliens Movement \n");

    //timer();
    //printf("ALIEN MOVEMENTS: Termino el delay \n");    

    static int despX = DER;
    static int condition= 2;
    static char vueltas = 0;
    int despY = 0;

    //printf("ALIEN MOVEMENTS: Comparación, LLego al borde derecho, entonces debe moverse a la izquierda  \n"); 
    //printf("ALIEN MOVEMENTS: despX=[%i]  \n",despX);
    if(alien_comp() == DER && despX == DER) //LLego al borde derecho, entonces debe moverse a la izquier
    {
        despX = IZQ;
        vueltas++;
    }
    //printf("ALIEN MOVEMENTS: Comparación, LLLego al borde izquierdo, entonces debe moverse a la derecha  \n"); 
    if(alien_comp() == IZQ && despX == IZQ) //LLego al borde izquierdo, entonces debe moverse a la derecha
    {
        //printf("ALIEN MOVEMENTS: CAMBIO A LA IZQUIERDA  \n");
        despX = DER;
        vueltas++;
    }
    //printf("ALIEN MOVEMENTS: Comparación, Complete el número de Vueltas?  \n"); 
    if(vueltas == condition)    //Número de Vueltas se cumplio, entonces baja
    {
            //printf("si  \n"); 
        despY = AB;
        if(nave_nodriza.spawn_condition != 1)
        {
            --(nave_nodriza.spawn_condition);
        }
        (game_stat->aliens_position)++;
        vueltas = 0;
        condition= (rand()%4)+1;
    }
    //printf("ALIEN MOVEMENTS: no, procedo a mover los aliens a [%i][%i] \n", despX, despY); 

    alien_move(despX, despY);
    disp_update();
    //printf("ALIEN MOVEMENTS, fin de función  \n");
    
//typedef enum {IZQ=-1, DER=1, ARR=-1, AB=1} direc_t;
    
}  

int alien_comp (void)   //Esta funcion se fija si algún alien está en el borde izquierdo o derecho
{   
    //printf("ALIEN_COMP: Entro a la Comparación  \n");  
    int borde = 0;   
    for(int i = 0; i<=DISP_MAX_Y; i++)       //Se fija si hay un alien en algún borde
    {
 
        //printf("ALIEN_COMP: ciclo[%d] \n ",i);
        //printf("ALIEN_COMP: Borde Izquierdo [%d] \n ",LEDMatrix[i][DISP_MIN].entity);
        //printf("ALIEN_COMP: Borde derecho [%d] \n ",LEDMatrix[i][DISP_MAX_X].entity);             
        if(LEDMatrix[i][DISP_MIN].entity == ALIEN)
        {
            //printf("ALIEN_COMP: ciclo [%d], coloco borde = IZQ  \n",i);
            borde = IZQ; //Aliens en la izquierda
        }
        else if(LEDMatrix[i][DISP_MAX_X].entity == ALIEN)
        {
            //printf("ALIEN_COMP: ciclo [%d], coloco borde = DER  \n",i);
            borde = DER;  //Aliens en la derecha
        }
    }
    //printf("ALIEN_COMP: Devuelvo %d  \n \n",borde); 
    return borde;   //Devuelve 0 si no hay aliens en los bordes o -1 o 1 si hay
}


void alien_picanazo (bala_alien_t* bala_alien, game_status_t* game_stat, bala_nave_t* bala_nave)
{
    //Chequea si van a chocar dos balas
    //printf("ALIEN_PICANAZO: Chequeo si hay bala en next pos, pos=[%d][%d], next_pos=[%d][%d] \n", bala_alien->pos_centro.x, bala_alien->pos_centro.y, bala_alien->next_pos_centro.x, bala_alien->next_pos_centro.y);
    if (LEDMatrix[bala_alien->next_pos_centro.y][bala_alien->next_pos_centro.x].entity == BALA)  //Si hay una bala arriba
    {
                //printf("ALIEN_PICANAZO: Imprimo en pantalla, entro a función con POS: [%d][%d]  \n", bala_alien->pos_centro.x,bala_alien->pos_centro.y);
        gral_write(bala_alien->pos_centro, D_OFF, VOID);    //Elimina esta bala
                //printf("ALIEN_PICANAZO: Imprimo en pantalla, NEXTPOS: [%d][%d] \n",bala_alien->next_pos_centro.x,bala_alien->next_pos_centro.y);
        gral_write(bala_alien->next_pos_centro, D_OFF, VOID);     //Y la otra

        bala_alien->used= false;
        bala_nave->used=false;  
    }

    else if(LEDMatrix[bala_alien->next_pos_centro.y][bala_alien->next_pos_centro.x].entity == WALL)
    {
                //printf("ALIEN_PICANAZO: Es un Wall, entro a función con POS: [%d][%d]  \n", bala_alien->pos_centro.x,bala_alien->pos_centro.y);
        gral_write(bala_alien->pos_centro, D_OFF, VOID);    //Elimina esta bala
                //printf("ALIEN_PICANAZO: Es un Wall, NEXTPOS: [%d][%d] \n",bala_alien->next_pos_centro.x,bala_alien->next_pos_centro.y);
        gral_write(bala_alien->next_pos_centro, D_OFF, VOID);     //Y el pixel de barrera

        bala_alien->used= false;
    }

    else if((LEDMatrix[bala_alien->next_pos_centro.y][bala_alien->next_pos_centro.x].entity == NAVE) || (LEDMatrix[bala_alien->pos_centro.y][bala_alien->pos_centro.x].entity == NAVE))
    {
        

        dead_ship_animation();
        gral_write(bala_alien->pos_centro, D_OFF, VOID);
        (game_stat->lives)--;
        bala_alien->used= false;
    }
    bala_alien->pos_centro = bala_alien->next_pos_centro;

}

char check_move_nodriza(void)
{
    int spawn = NO;
    if( (rand()% CHANCE) == SPAWN )
    {
        spawn= YES;
    }
    else
    {
        spawn= NO;
    }
    return spawn;
}

char advance_a_pixel(void)
{
    char keep_moving;

    if((nave_nodriza.centro.x != NODRIZA_FAR_LEFT) && (nave_nodriza.doa == ALIVE))
    {
        keep_moving=YES;

        print_alien(nave_nodriza.centro, 0 ,nave_nodriza.typeofalien, ALIVE, D_OFF,ID_Nodriza);
        --(nave_nodriza.centro.x);
        print_alien(nave_nodriza.centro, 0 ,nave_nodriza.typeofalien, ALIVE, D_ON, ID_Nodriza);

    }
    else
    {
        ++nave_nodriza.spawn_condition;
        nave_nodriza.centro.x= NODRIZA_FAR_RIGHT;
        nave_nodriza.doa=ALIVE;
        keep_moving= NO;
    }
    return keep_moving;
}
#endif //RASPI
