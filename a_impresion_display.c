
#include "a_impresion_display.h"

void write_display(char* str, int x, int y, int red, int green, int blue)
{
    char* str_aux = str;
    char char_aux;
    int x_q_avanza = x;
    
    while (*str_aux != '\0')
    {        
        char_aux = TO_UPPER(*str_aux);
               
        if( (char_aux>='A') && (char_aux<='Z') )
        {            
            al_draw_tinted_bitmap(sevenup.letra[((char_aux)-'A')], al_map_rgb(red, green, blue), x_q_avanza, y, 0);                      
        }
        
        else if ( (char_aux >= '0') && (char_aux <= '9') )
        {
            al_draw_tinted_bitmap(sevenup.numero[((char_aux)-'0')], al_map_rgb(red, green, blue), x_q_avanza, y, 0);
        }
        
        else if (char_aux == '-')
        {
            al_draw_tinted_bitmap(sevenup.signo[0], al_map_rgb(red, green, blue), x_q_avanza, y, 0);
        }
        
        else if (char_aux == '<')
        {
            al_draw_tinted_bitmap(sevenup.signo[1], al_map_rgb(red, green, blue), x_q_avanza, y, 0);
        }
        
        else if (char_aux == '>')
        {
            al_draw_tinted_bitmap(sevenup.signo[2], al_map_rgb(red, green, blue), x_q_avanza, y, 0);
        }
        
        else if (char_aux == ':')
        {
            al_draw_tinted_bitmap(sevenup.signo[3], al_map_rgb(red, green, blue), x_q_avanza, y, 0);
        }
        
        else if (char_aux == '=')
        {
            al_draw_tinted_bitmap(sevenup.signo[4], al_map_rgb(red, green, blue), x_q_avanza, y, 0);
        }
        
        else if (char_aux == '*')
        {
            al_draw_tinted_bitmap(sevenup.signo[5], al_map_rgb(red, green, blue), x_q_avanza, y, 0);
        }
        
        else if (char_aux == '|')
        {
            al_draw_tinted_bitmap(sevenup.signo[6], al_map_rgb(red, green, blue), x_q_avanza, y, 0);
        }
        
        else if (char_aux == '?')
        {
            al_draw_tinted_bitmap(sevenup.signo[7], al_map_rgb(red, green, blue), x_q_avanza, y, 0);
        }
        
        else if (char_aux == '!')
        {
            al_draw_tinted_bitmap(sevenup.signo[8], al_map_rgb(red, green, blue), x_q_avanza, y, 0);
        }
        
        else if (char_aux == '.')
        {
            al_draw_tinted_bitmap(sevenup.signo[9], al_map_rgb(red, green, blue), x_q_avanza, y, 0);
        }
        
        if(x_q_avanza > DISPLAY_ANCHO)      //sirve? no le voy a pedir que me de error
        {
            break;
        }

        x_q_avanza += (AYA_CARACTERES+1);
        str_aux++;
    }
}
/*
char* num2str(int num)
{
    char* new_str;
    char* aux_str = new_str;
    int result, divisor = 100000;

    for(int i; i<6; i++)
    {
        result = num/divisor;
        num -= result*divisor;
        *aux_str = result;

        divisor /= 10;
        aux_str++;
    }
    *aux_str++ = '\0';
}
*/
