
#include "barriers.h"

extern barr_t barriers[CANT_BARRS];

void barriers_init(void)
{
    for(int i=0 ; i<CANT_BARRS ; i++)
    {
        barriers[i].centro.x = POS_CENTRO_BARRERA_X(i);
	barriers[i].centro.y = POS_CENTRO_BARRERA_Y;
	barriers[i].doa= ALIVE;
        
        #ifdef ALLEGRO
	bloque_barriers_init(i);
	#endif //ALLEGRO
        
        if(i != 1)
        {
            barriers[i].type= BARR_EDGE;
        }
        else
        {
            barriers[i].type= BARR_CENTER;
        }
        
        print_barr(barriers[i].centro, D_ON, barriers[i].type, barriers[i].doa);
    }
}

#ifdef ALLEGRO

extern bloque_barrera_t bloques_barr[CANT_BARRS][CANT_BLOQUES];

void print_barr(dcoord_t coord, dlevel_t value, entity_t type, char doa)
{
    if(doa)
    {       
        al_draw_tinted_bitmap(sevenup.barrera, al_map_rgb(ROJO_BARR_R, ROJO_BARR_G, ROJO_BARR_B), (coord.x)-10 , (coord.y)-7 , 0);
    }
}

void barriers_draw(void)
{
    for(int i=0 ; i<CANT_BARRS ; i++)
    {
        if(barriers[i].doa == ALIVE)
        {
            print_barr(barriers[i].centro, D_ON, barriers[i].type, barriers[i].doa);
            barr_damage_print(i);	
        }
    }
}

void barr_damage_print(int i)
{
	for(int a=0;a<CANT_BLOQUES;a++)
	{
		switch(bloques_barr[i][a].tipo)
		{
			case CHICO_1X1:
			{
				if(!(bloques_barr[i][a].life_status))
				{
					al_draw_bitmap(sevenup.dead_barrera_chico_1x1, bloques_barr[i][a].x0, bloques_barr[i][a].y0, 0);
				}
				break;
			}
			case CHICO_2X2:
			{
				if(!(bloques_barr[i][a].life_status))
				{
					al_draw_bitmap(sevenup.dead_barrera_chico_2x2, bloques_barr[i][a].x0, bloques_barr[i][a].y0, 0);
				}
				break;
			}
			case MEDIANO:
			{
				if(!(bloques_barr[i][a].life_status))				
				{
					al_draw_bitmap(sevenup.dead_barrera_mediano, bloques_barr[i][a].x0, bloques_barr[i][a].y0, 0);
				}
				break;
			}
			case GRANDE_3X4:
			{
				if(bloques_barr[i][a].life_status == (VIDA_BLOQUE_GRANDE-1))
				{
					al_draw_bitmap(sevenup.damage2_barrera_grande_3x4[bloques_barr[i][a].patron_de_damage], bloques_barr[i][a].x0, bloques_barr[i][a].y0, 0);
				}
				else if(!(bloques_barr[i][a].life_status))
				{
					al_draw_bitmap(sevenup.dead_barrera_grande_3x4, bloques_barr[i][a].x0, bloques_barr[i][a].y0, 0);
				}
				break;
			}
			case GRANDE_4X3:
			{
				if(bloques_barr[i][a].life_status == (VIDA_BLOQUE_GRANDE-1))
				{
					al_draw_bitmap(sevenup.damage2_barrera_grande_4x3[bloques_barr[i][a].patron_de_damage], bloques_barr[i][a].x0, bloques_barr[i][a].y0, 0);
				}
				else if(!(bloques_barr[i][a].life_status))
				{
					al_draw_bitmap(sevenup.dead_barrera_grande_4x3, bloques_barr[i][a].x0, bloques_barr[i][a].y0, 0);
				}
				break;
			}
			case GRANDE_4X4:
			{
				if(bloques_barr[i][a].life_status == (VIDA_BLOQUE_GRANDE-1))
				{
					al_draw_bitmap(sevenup.damage2_barrera_grande_4x4[bloques_barr[i][a].patron_de_damage], bloques_barr[i][a].x0, bloques_barr[i][a].y0, 0);
				}
				else if(!(bloques_barr[i][a].life_status))
				{
					al_draw_bitmap(sevenup.dead_barrera_grande_4x4, bloques_barr[i][a].x0, bloques_barr[i][a].y0, 0);
				}
				break;
			}
		}
	}
}

void bloque_barriers_init(int i)
{
	dcoord_t top_left_grid;
	int numero_bloque = 0;
	top_left_grid.x = barriers[i].centro.x - 7;
	top_left_grid.y = barriers[i].centro.y - 7;

	for(int a=0 ; a<CANT_FIL_BLOQUES ; a++)
	{
		for(int b=0 ; b<CANT_COL_BLOQUES ; b++)
		{
			bloques_barr[i][numero_bloque].life_status = VIDA_BLOQUE_MEDIANO;
			bloques_barr[i][numero_bloque].tipo = MEDIANO;
			bloques_barr[i][numero_bloque].fila = a;
			bloques_barr[i][numero_bloque].columna = b;
			bloques_barr[i][numero_bloque].ancho = 3;
			bloques_barr[i][numero_bloque].alto = 3;

			bloques_barr[i][numero_bloque].x0 = top_left_grid.x+b*3;
			bloques_barr[i][numero_bloque].xf = top_left_grid.x+2+b*3;
			bloques_barr[i][numero_bloque].y0 = top_left_grid.y+a*3;
			bloques_barr[i][numero_bloque].yf = top_left_grid.y+2+a*3;

			numero_bloque++;
		}
	}

	dcoord_t top_left_barrier;
	top_left_barrier.x = barriers[i].centro.x - 10;
	top_left_barrier.y = barriers[i].centro.y - 7;

	for(int j=0 ; j<3 ; j++)
	{
		bloques_barr[i][numero_bloque].life_status = VIDA_BLOQUE_MEDIANO;
		bloques_barr[i][numero_bloque].tipo = MEDIANO;
		bloques_barr[i][numero_bloque].ancho = 3;
		bloques_barr[i][numero_bloque].alto = 3;

		bloques_barr[i][numero_bloque].x0 = top_left_barrier.x;
		bloques_barr[i][numero_bloque].xf = top_left_barrier.x+2;
		bloques_barr[i][numero_bloque].y0 = top_left_barrier.y+3+j*3;
		bloques_barr[i][numero_bloque].yf = top_left_barrier.y+5+j*3;

		numero_bloque++;
	}

	for(int k=0 ; k<3 ; k++)
	{
		
		if(k==2)
		{
			bloques_barr[i][numero_bloque].x0 = top_left_barrier.x+15;
			bloques_barr[i][numero_bloque].xf = top_left_barrier.x+17;
		}
		else
		{
			bloques_barr[i][numero_bloque].x0 = top_left_barrier.x+k*3;
			bloques_barr[i][numero_bloque].xf = top_left_barrier.x+2+k*3;
		}

		bloques_barr[i][numero_bloque].y0 = top_left_barrier.y+12;
		bloques_barr[i][numero_bloque].yf = top_left_barrier.y+15;

		bloques_barr[i][numero_bloque].life_status = VIDA_BLOQUE_GRANDE;
		bloques_barr[i][numero_bloque].tipo = GRANDE_3X4;
		bloques_barr[i][numero_bloque].ancho = 3;
		bloques_barr[i][numero_bloque].alto = 4;

		numero_bloque++;
	}

	for(int l=0 ; l<3 ; l++)
	{
		bloques_barr[i][numero_bloque].life_status = VIDA_BLOQUE_GRANDE;
		bloques_barr[i][numero_bloque].tipo = GRANDE_4X3;
		bloques_barr[i][numero_bloque].ancho = 4;
		bloques_barr[i][numero_bloque].alto = 3;

		bloques_barr[i][numero_bloque].x0 = top_left_barrier.x+18;
		bloques_barr[i][numero_bloque].xf = top_left_barrier.x+21;
		bloques_barr[i][numero_bloque].y0 = top_left_barrier.y+3+l*3;
		bloques_barr[i][numero_bloque].yf = top_left_barrier.y+5+l*3;

		numero_bloque++;
	}

	bloques_barr[i][numero_bloque].life_status = VIDA_BLOQUE_CHICO;
	bloques_barr[i][numero_bloque].tipo = CHICO_1X1;
	bloques_barr[i][numero_bloque].ancho = 1;
	bloques_barr[i][numero_bloque].alto = 1;

	bloques_barr[i][numero_bloque].x0 = top_left_barrier.x+2;
	bloques_barr[i][numero_bloque].xf = top_left_barrier.x+2;
	bloques_barr[i][numero_bloque].y0 = top_left_barrier.y+2;
	bloques_barr[i][numero_bloque].yf = top_left_barrier.y+2;

	numero_bloque++;

	bloques_barr[i][numero_bloque].life_status = VIDA_BLOQUE_CHICO;
	bloques_barr[i][numero_bloque].tipo = CHICO_2X2;
	bloques_barr[i][numero_bloque].ancho = 2;
	bloques_barr[i][numero_bloque].alto = 2;

	bloques_barr[i][numero_bloque].x0 = top_left_barrier.x+18;
	bloques_barr[i][numero_bloque].xf = top_left_barrier.x+19;
	bloques_barr[i][numero_bloque].y0 = top_left_barrier.y+1;
	bloques_barr[i][numero_bloque].yf = top_left_barrier.y+2;

	numero_bloque++;

	bloques_barr[i][numero_bloque].life_status = VIDA_BLOQUE_CHICO;
	bloques_barr[i][numero_bloque].tipo = CHICO_1X1;
	bloques_barr[i][numero_bloque].ancho = 1;
	bloques_barr[i][numero_bloque].alto = 1;

	bloques_barr[i][numero_bloque].x0 = top_left_barrier.x+6;
	bloques_barr[i][numero_bloque].xf = top_left_barrier.x+6;
	bloques_barr[i][numero_bloque].y0 = top_left_barrier.y+12;
	bloques_barr[i][numero_bloque].yf = top_left_barrier.y+12;

	numero_bloque++;

	bloques_barr[i][numero_bloque].life_status = VIDA_BLOQUE_CHICO;
	bloques_barr[i][numero_bloque].tipo = CHICO_1X1;
	bloques_barr[i][numero_bloque].ancho = 1;
	bloques_barr[i][numero_bloque].alto = 1;

	bloques_barr[i][numero_bloque].x0 = top_left_barrier.x+14;
	bloques_barr[i][numero_bloque].xf = top_left_barrier.x+14;
	bloques_barr[i][numero_bloque].y0 = top_left_barrier.y+12;
	bloques_barr[i][numero_bloque].yf = top_left_barrier.y+12;

	numero_bloque++;

	bloques_barr[i][numero_bloque].life_status = VIDA_BLOQUE_GRANDE;
	bloques_barr[i][numero_bloque].tipo = GRANDE_4X4;
	bloques_barr[i][numero_bloque].ancho = 4;
	bloques_barr[i][numero_bloque].alto = 4;

	bloques_barr[i][numero_bloque].x0 = top_left_barrier.x+18;
	bloques_barr[i][numero_bloque].xf = top_left_barrier.x+21;
	bloques_barr[i][numero_bloque].y0 = top_left_barrier.y+12;
	bloques_barr[i][numero_bloque].yf = top_left_barrier.y+15;
}

bool colision_barrera(bala_nave_t* bala_nave, bala_alien_t* bala_alien, ent_t entidad, alien_t alien)
{
    bool colision = false;
    int i = NOT_DEFINED;
    
    switch(entidad)
    {
        case BALA_NAVE:
        {
            if(bala_nave->next_pos_centro.y >= BARRERAS_Y0 && bala_nave->next_pos_centro.y <= BARRERAS_YF)
            {
                if(bala_nave->next_pos_centro.x >= BARRERA0_X0 && bala_nave->next_pos_centro.x <= BARRERA0_XF)
                {
                    i=0;                    
                }
                else if(bala_nave->next_pos_centro.x >= BARRERA1_X0 && bala_nave->next_pos_centro.x <= BARRERA1_XF)
                {
                    i=1;                   
                }
                else if(bala_nave->next_pos_centro.x >= BARRERA2_X0 && bala_nave->next_pos_centro.x <= BARRERA2_XF)
                {
                    i=2;                    
                }
                else if(bala_nave->next_pos_centro.x >= BARRERA3_X0 && bala_nave->next_pos_centro.x <= BARRERA3_XF)
                {
                    i=3;                    
                }
            
                if(i != NOT_DEFINED)
                {
                    for(int j=0; j<CANT_BLOQUES && !colision; j++)
                    {
                        if(bloques_barr[i][j].life_status &&
                               collission_chck(BALA_NAVE_X0(bala_nave->next_pos_centro.x),
                                               BALA_NAVE_Y0(bala_nave->next_pos_centro.y),
                                               BALA_NAVE_XF(bala_nave->next_pos_centro.x),
                                               BALA_NAVE_YF(bala_nave->next_pos_centro.y),
                                               bloques_barr[i][j].x0,
                                               bloques_barr[i][j].y0,
                                               bloques_barr[i][j].xf,
                                               bloques_barr[i][j].yf))
                        {
                                bloques_barr[i][j].patron_de_damage = rand()% 4;
                                bloques_barr[i][j].life_status--;
                                colision = true;
                        }
                    }
                }
            
            }
            
            break;
        }
        case BALA_ALIEN:
        {
            if(bala_alien->next_pos_centro.y >= BARRERAS_Y0 && bala_alien->next_pos_centro.y <= BARRERAS_YF)
            {
                if(bala_alien->next_pos_centro.x >= BARRERA0_X0 && bala_alien->next_pos_centro.x <= BARRERA0_XF)
                {
                    i=0;  
                }
                else if(bala_alien->next_pos_centro.x >= BARRERA1_X0 && bala_alien->next_pos_centro.x <= BARRERA1_XF)
                {
                    i=1;                   
                }
                else if(bala_alien->next_pos_centro.x >= BARRERA2_X0 && bala_alien->next_pos_centro.x <= BARRERA2_XF)
                {
                    i=2;                    
                }
                else if(bala_alien->next_pos_centro.x >= BARRERA3_X0 && bala_alien->next_pos_centro.x <= BARRERA3_XF)
                {
                    i=3;                    
                }
                
                if(i != NOT_DEFINED)
                {
                    for(int j=0; j<CANT_BLOQUES && !colision; j++)
                    {
                        if( (bloques_barr[i][j].life_status != 0) &&
                           collission_chck(BALA_ALIEN_X0(bala_alien->next_pos_centro.x),
                                           BALA_ALIEN_Y0(bala_alien->next_pos_centro.y),
                                           BALA_ALIEN_XF(bala_alien->next_pos_centro.x),
                                           BALA_ALIEN_YF(bala_alien->next_pos_centro.y),
                                           bloques_barr[i][j].x0,
                                           bloques_barr[i][j].y0,
                                           bloques_barr[i][j].xf,
                                           bloques_barr[i][j].yf))
                        {
                            bloques_barr[i][j].patron_de_damage = rand()% 4;
                            bloques_barr[i][j].life_status--;
                            colision=true;
                        }                                  
                    }
                }
            }
            break;
        }
        case ALIENS:
        {
            if((alien.centro.y+4) >= BARRERAS_Y0 && (alien.centro.y-3) <= BARRERAS_YF)
            {
                if((alien.centro.x+6) >= BARRERA0_X0 && (alien.centro.x-5) <= BARRERA0_XF)
                {
                    i=0;  
                }
                else if((alien.centro.x+6) >= BARRERA1_X0 && (alien.centro.x-5) <= BARRERA1_XF)
                {
                    i=1;                   
                }
                else if((alien.centro.x+6) >= BARRERA2_X0 && (alien.centro.x-5) <= BARRERA2_XF)
                {
                    i=2;                    
                }
                else if((alien.centro.x+6) >= BARRERA3_X0 && (alien.centro.x-5) <= BARRERA3_XF)
                {
                    i=3;                    
                }
                
                if(i != NOT_DEFINED)
                {
                    for(int j=0; j<CANT_BLOQUES; j++)
                    {
                        switch(alien.typeofalien)
                        {
                            case ALIEN1:
                            {
                                if((bloques_barr[i][j].life_status != 0) &&
                                   collission_chck(ALIEN1_X0(alien.centro.x),
                                                   ALIEN1_Y0(alien.centro.y),
                                                   ALIEN1_XF(alien.centro.x),
                                                   ALIEN1_YF(alien.centro.y),
                                                   bloques_barr[i][j].x0,
                                                   bloques_barr[i][j].y0,
                                                   bloques_barr[i][j].xf,
                                                   bloques_barr[i][j].yf))
                                {
                                    bloques_barr[i][j].life_status = 0;
                                    colision=true;
                                }                                                     
                                break;
                            }
                            case ALIEN2:
                            {
                                if((bloques_barr[i][j].life_status != 0) &&
                                   collission_chck(ALIEN2_X0(alien.centro.x),
                                                   ALIEN2_Y0(alien.centro.y),
                                                   ALIEN2_XF(alien.centro.x),
                                                   ALIEN2_YF(alien.centro.y),
                                                   bloques_barr[i][j].x0,
                                                   bloques_barr[i][j].y0,
                                                   bloques_barr[i][j].xf,
                                                   bloques_barr[i][j].yf))
                                {
                                    bloques_barr[i][j].life_status = 0;
                                    colision=true;
                                }                                                     
                                break;
                            }
                            case ALIEN3:
                            {
                                if((bloques_barr[i][j].life_status != 0) &&
                                   collission_chck(ALIEN3_X0(alien.centro.x),
                                                   ALIEN3_Y0(alien.centro.y),
                                                   ALIEN3_XF(alien.centro.x),
                                                   ALIEN3_YF(alien.centro.y),
                                                   bloques_barr[i][j].x0,
                                                   bloques_barr[i][j].y0,
                                                   bloques_barr[i][j].xf,
                                                   bloques_barr[i][j].yf))
                                {
                                    bloques_barr[i][j].life_status = 0;
                                    colision=true;
                                }                                                     
                                break;
                            }
                        }
             
                    }
                }
            }
            break;
        }
    }
    
    return colision;
}

#endif //ALLEGRO

#ifdef RASPI

void print_barr(dcoord_t center, dlevel_t value, entity_t type, char doa)
{
	switch(type)
	{
		case BARR_EDGE:
		{
			dcoord_t aux;

			gral_write(center, value, WALL);

			aux.x= center.x+1;
			aux.y= center.y;

			gral_write(aux, value, WALL);

			aux.x= center.x-1;
			aux.y= center.y;

			gral_write(aux, value, WALL);

			aux.x= center.x-1;
			aux.y= center.y+1;

			gral_write(aux, value, WALL);

			aux.x= center.x+1;
			aux.y= center.y+1;

			gral_write(aux, value, WALL);

			break;

		}

		case BARR_CENTER:
		{
			dcoord_t aux;

			gral_write(center, value, WALL);

			aux.x= center.x+1;
			aux.y= center.y;

			gral_write(aux, value, WALL);

			aux.x= center.x+1;
			aux.y= center.y+1;

			gral_write(aux, value, WALL);

			aux.x= center.x;
			aux.y= center.y+1;

			gral_write(aux, value, WALL);

		}
		default:
		{
			//TO AVOID WARNINGS
		}
	}
}

#endif //RASPI
