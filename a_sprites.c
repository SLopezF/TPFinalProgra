
/******************************************************************************
 *                                    SPRITES                                 *
 ******************************************************************************/

/* 
 * File:   sprites.c
 * Author: eherrera
 *
 * Created on December 28, 2022, 9:17 PM
 */

#include "a_sprites.h"

ALLEGRO_BITMAP* recorte_sprite(sprites_t* sprite, int x, int y, int ancho, int altura) 
{
    ALLEGRO_BITMAP* sprites = al_create_sub_bitmap(sprite->sheet, x, y, ancho, altura);
    inic_chck(sprites, "recorte sprite");
    return sprites;
    
}

void sprite_inic(sprites_t* sprite)
{
    sprite->sheet = al_load_bitmap("spritesheet.png");
    inic_chck(sprite->sheet, "spritesheet");
    
    caracteres_inic(sprite);
    entidades_inic(sprite);
}

void caracteres_inic(sprites_t* sprite)
{
    int ii,jj;
    int i=0 , j=INIC_MAT_CARACTERES;
    
    for(ii=0; ii<3; ii++)
    {
      for (jj=0; jj< 9; jj++)
        {
            if (ii==2 && jj==8)
            {
                sprite->signo[0] = recorte_sprite(sprite, j,i,AYA_CARACTERES,AYA_CARACTERES);
            }
            
            else
            {                
                sprite->letra[(jj+ii*9)] = recorte_sprite(sprite, j,i,AYA_CARACTERES,AYA_CARACTERES);
                
                j += AYA_CARACTERES+1;
            }   
        }
        
        j = INIC_MAT_CARACTERES;
        i += AYA_CARACTERES+1;
    }
    
    i = (AYA_CARACTERES+1)*3;
    j = INIC_MAT_CARACTERES;
    
    for(jj=0; jj<9; jj++)
    {
        if( jj == 6 || jj == 7)
        {
            sprite->signo[(jj+1)] = recorte_sprite(sprite, j,i,AYA_CARACTERES,8);
        }
        else
        {
            sprite->signo[(jj+1)] = recorte_sprite(sprite, j,i,AYA_CARACTERES,AYA_CARACTERES);
        }       
        j += AYA_CARACTERES+1;
    }
    
    i = (AYA_CARACTERES+1)*4+2;
    j = INIC_MAT_CARACTERES;
    
    for(jj=0; jj<10; jj++)
    {
        sprite->numero[jj] = recorte_sprite (sprite, j,i,AYA_CARACTERES,AYA_CARACTERES);
        
        j += AYA_CARACTERES+1;
    }
    
    sprite->animacion_y[0] = recorte_sprite(sprite, 105,43,16,8);
    sprite->animacion_y[1] = recorte_sprite(sprite, 105,54,16,8);
    
    sprite->animacion_yinv[0] = recorte_sprite(sprite, 122,43,16,8);
    sprite->animacion_yinv[1] = recorte_sprite(sprite, 122,54,16,8);
    
    sprite->logo = recorte_sprite(sprite, 13,66,119,42);
}

void entidades_inic(sprites_t* sprite)
{
    sprite->piso[0] = recorte_sprite(sprite, 71, 45, 8, 1);
    sprite->piso[1] = recorte_sprite(sprite, 71, 47, 8, 1);
    
    sprite->alien1[0] = recorte_sprite(sprite, 2,0,8,8);
    sprite->alien1[1] = recorte_sprite(sprite, 2,9,8,8);
    
    sprite->alien2[0] = recorte_sprite(sprite, 11,0,11,8);
    sprite->alien2[1] = recorte_sprite(sprite, 11,9,11,8);
    
    sprite->alien3[0] = recorte_sprite(sprite, 23,0,12,8);
    sprite->alien3[1] = recorte_sprite(sprite, 23,9,12,8);
    
    sprite->explosion_alien = recorte_sprite(sprite, 36,0,13,8);
    
    sprite->nave_nodriza = recorte_sprite(sprite, 36,9,16,7);
    
    sprite->nave = recorte_sprite(sprite, 2,27,13,8);
    
    sprite->explosion_nave[0] = recorte_sprite(sprite, 16,27,15,8);
    sprite->explosion_nave[1] = recorte_sprite(sprite, 32,27,16,8);
    
    sprite->explosion[0] = recorte_sprite(sprite, 50,18,6,8);
    sprite->explosion[1] = recorte_sprite(sprite, 51,27,8,8);
    
    sprite->barrera = recorte_sprite(sprite, 2,36,22,16);
    
    sprite->bala_nave = recorte_sprite(sprite, 49,31,1,4);
    
    int i, j;
    int ii=18, jj=2;
    
    for(j=0; j<12; j++)
    {
        if(j<4)
        {
            sprite->bala_alien1[j] = recorte_sprite(sprite, jj,ii,3,7);
            jj += ANCHO_BALAS+1;
        }
        
        else if (j>=4 && j<8)
        {
            sprite->bala_alien2[j-4] = recorte_sprite(sprite, jj,ii,3,7);
            jj += ANCHO_BALAS+1;
        }
        
        else if (j>=8 && j<12)
        {
            sprite->bala_alien3[j-8] = recorte_sprite(sprite, jj,ii,3,7);
            jj += ANCHO_BALAS+1;
        }
    }

    int y = 36;
    int x = 45;

    sprite->dead_barrera_chico_1x1 = recorte_sprite(sprite, x, y, 1, 1);
    sprite->dead_barrera_chico_2x2 = recorte_sprite(sprite, 49, y, 2, 2);

    for(i=0; i<4; i++)
    {
        x = 25;
        if(i == 0)
        {
            for(j=0; j<5; j++)
            {
                if(j == 4)
                {
                    sprite->dead_barrera_mediano = recorte_sprite(sprite, x, y, 3, 3);
                }
                else
                {
                    sprite->damage_barrera_mediano[j] = recorte_sprite(sprite, x, y, 3, 3);
                }
                x += 4;
            }
        }
        else if(i == 1)
        {
            y += 4;
            for(j=0; j<9; j++)
            {
                if(j<4)
                {
                    sprite->damage1_barrera_grande_3x4[j] = recorte_sprite(sprite, x, y, 3, 4);
                }
                else if(j>=4 && j<8)
                {
                    sprite->damage2_barrera_grande_3x4[j-4] = recorte_sprite(sprite, x, y, 3, 4);
                }
                else
                {
                    sprite->dead_barrera_grande_3x4 = recorte_sprite(sprite, x, y, 3, 4);
                }
                x += 4;
            }
        }
        else if(i == 2)
        {
            y += 5;
            for(j=0; j<9; j++)
            {
                if(j<4)
                {
                    sprite->damage1_barrera_grande_4x3[j] = recorte_sprite(sprite, x, y, 4, 3);
                }
                else if(j>=4 && j<8)
                {
                    sprite->damage2_barrera_grande_4x3[j-4] = recorte_sprite(sprite, x, y, 4, 3);
                }
                else
                {
                    sprite->dead_barrera_grande_4x3 = recorte_sprite(sprite, x, y, 4, 3);
                }
                x += 5;
            }
        }
        else if(i == 3)
        {
            y += 4;
            for(j=0; j<9; j++)
            {
                if(j<4)
                {
                    sprite->damage1_barrera_grande_4x4[j] = recorte_sprite(sprite, x, y, 4, 4);
                }
                else if(j>=4 && j<8)
                {
                    sprite->damage2_barrera_grande_4x4[j-4] = recorte_sprite(sprite, x, y, 4, 4);
                }
                else
                {
                    sprite->dead_barrera_grande_4x4 = recorte_sprite(sprite, x, y, 4, 4);
                }
                x += 5;
            }
        }
    }
    
}

void destruir_sprites(sprites_t* sevenup)
{
    int i;
    
    for(i=0; i<26; i++)
    {   
        al_destroy_bitmap(sevenup->letra[i]);
    }
    
    for(i=0; i<10; i++)
    {
        al_destroy_bitmap(sevenup->signo[i]);
    }
    
    for(i=0; i<10; i++)
    {
        al_destroy_bitmap(sevenup->numero[i]);
    }
    
    al_destroy_bitmap(sevenup->logo);
    
    al_destroy_bitmap(sevenup->animacion_y[0]);
    al_destroy_bitmap(sevenup->animacion_y[1]);
    
    al_destroy_bitmap(sevenup->animacion_yinv[0]);
    al_destroy_bitmap(sevenup->animacion_yinv[1]);
    
    al_destroy_bitmap(sevenup->piso[0]);
    al_destroy_bitmap(sevenup->piso[1]);
        
    al_destroy_bitmap(sevenup->alien1[0]);
    al_destroy_bitmap(sevenup->alien1[1]);
    
    al_destroy_bitmap(sevenup->alien2[0]);
    al_destroy_bitmap(sevenup->alien2[1]);
    
    al_destroy_bitmap(sevenup->alien3[0]);
    al_destroy_bitmap(sevenup->alien3[1]);
    
    al_destroy_bitmap(sevenup->nave);
    
    for(i=0; i<4; i++)
    {
        al_destroy_bitmap(sevenup->bala_alien1[i]);
    }
    
    for(i=0; i<4; i++)
    {
        al_destroy_bitmap(sevenup->bala_alien2[i]);
    }
    
    for(i=0; i<4; i++)
    {
        al_destroy_bitmap(sevenup->bala_alien3[i]);
    }
    
    al_destroy_bitmap(sevenup->bala_nave);
    
    al_destroy_bitmap(sevenup->nave_nodriza);
    
    al_destroy_bitmap(sevenup->explosion_alien);
    
    al_destroy_bitmap(sevenup->explosion_nave[0]);
    al_destroy_bitmap(sevenup->explosion_nave[1]);
    
    al_destroy_bitmap(sevenup->explosion[0]);
    al_destroy_bitmap(sevenup->explosion[1]);
    
    al_destroy_bitmap(sevenup->barrera);

    al_destroy_bitmap(sevenup->dead_barrera_chico_1x1);
    al_destroy_bitmap(sevenup->dead_barrera_chico_2x2);

    for(i=0;i<4;i++)
    {
        al_destroy_bitmap(sevenup->damage_barrera_mediano[i]);
    }
    al_destroy_bitmap(sevenup->dead_barrera_mediano);

    for(i=0;i<4;i++)
    {
        al_destroy_bitmap(sevenup->damage1_barrera_grande_3x4[i]);
    }
    for(i=0;i<4;i++)
    {
        al_destroy_bitmap(sevenup->damage2_barrera_grande_3x4[i]);
    }
    al_destroy_bitmap(sevenup->dead_barrera_grande_3x4);

    for(i=0;i<4;i++)
    {
        al_destroy_bitmap(sevenup->damage1_barrera_grande_4x3[i]);
    }
    for(i=0;i<4;i++)
    {
        al_destroy_bitmap(sevenup->damage2_barrera_grande_4x3[i]);
    }
    al_destroy_bitmap(sevenup->dead_barrera_grande_4x3);

    for(i=0;i<4;i++)
    {
        al_destroy_bitmap(sevenup->damage1_barrera_grande_4x4[i]);
    }
    for(i=0;i<4;i++)
    {
        al_destroy_bitmap(sevenup->damage2_barrera_grande_4x4[i]);
    }
    al_destroy_bitmap(sevenup->dead_barrera_grande_4x4);
}
