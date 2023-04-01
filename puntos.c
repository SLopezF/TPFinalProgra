
#include "puntos.h"
#ifdef ALLEGRO

int points(int toa, int points)
{
    switch (toa)							//dependiendo del tipo de alien, guarda una puntuación especifica en points
    {
        case 0:
        {
            points += ALIEN1_SCORE;
            break;
        }

        case 1:
        {
            points += ALIEN2_SCORE;
            break;
        }

        case 2:
        {
            points += ALIEN3_SCORE;
            break;
        }

        case 10:
        {
            points += NODRIZA_SCORE;
            break;
        }
    }
    return points;
}

void hud_draw(int score, int hi_score)
{
    char char_points[7];
    char char_hiscore[7];
    char ship_life[2] = {(my_ship.doa + '0'), '\0'};

    sprintf(char_points, "%06d", score); 					//toma points y lo vuelve un string que guarda en char_points
    sprintf(char_hiscore, "%06d", hi_score);
    
    write_display("SCORE<1>", 6, 6, TURQUESA_R, TURQUESA_G, TURQUESA_B);
    write_display(char_points, 14, 14, BLANCO_R, BLANCO_G, BLANCO_B);

    write_display("HI-SCORE", 81, 6, VIOLETA_R, VIOLETA_G, VIOLETA_B);
    write_display(char_hiscore, 89, 14, BLANCO_R, BLANCO_G, BLANCO_B); //HI-SCORE
    
    write_display("SCORE<2>", 156, 6, AMARILLO_R, AMARILLO_G, AMARILLO_B);
    write_display("000000", 164, 14, BLANCO_R, BLANCO_G, BLANCO_B);//SCORE<2>
    
    write_display(ship_life, 6, 241, BLANCO_R, BLANCO_G, BLANCO_B);	//imprime la cantidad de vidas restantes
    
    for(int i = 0; i < my_ship.doa-1; i++)
    {
       al_draw_tinted_bitmap(sevenup.nave, al_map_rgb(TURQUESA_R, TURQUESA_G, TURQUESA_B), (17*(i+1)) , 240 , 0);
    }
}

#endif //ALLEGRO
