
#include "a_general.h"

int inic_chck(bool test, const char *descripcion)
{
    if(!test)
    {
        printf("No se pudo inicializar %s\n", descripcion);
        exit(1);
    }
    
    else
    {
        return 0;
    }  
}

/*                           COLLISSION_CHCK                         */
/*  Usando el método de "Hit Box" se calcula si hubo una colisión o
 *  no entre dos entidades.
 * 
 *  a: entidad A
 *  b: entidad B
 * 
 *  x0: inicio de entidad en x (lado derecho)
 *  xf: fin de entidad en x (lado izquierdo)
 *  y0: inicio de entidad en y (lado superior)
 *  yf: fin de entidad en y (lado inferior)
 * 
*/

bool collission_chck(int a_x0, int a_y0, int a_xf, int a_yf, int b_x0, int b_y0, int b_xf, int b_yf)
{   
    bool status;
        
    if( (a_x0 > b_xf) || (a_xf < b_x0) || (a_y0 > b_yf) || (a_yf < b_y0) )
    {
        status = false;
    }
    else
    {
        status = true;
    }

    return status;
}
