
#include "a_display.h"

void a_disp_init(ALLEGRO_DISPLAY** disp, ALLEGRO_BITMAP** buffer)
{
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);  //algo de la calidad de imagen, si no está disponible da igual
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);         //no sé si termino de entender el concepto samples per pixel pero cambio el valor y no noto diferencia así q idk, mejora a relución de imagen supuestamente

    *disp = al_create_display(DISPLAY_ANCHO, DISPLAY_ALTO);
    inic_chck(*disp, "display");
       
    *buffer = al_create_bitmap(BUFFER_ANCHO, BUFFER_ALTO);     //!! hubo problems
    inic_chck(*buffer, "bitmap buffer");
}

void a_disp_deinit(ALLEGRO_DISPLAY** display, ALLEGRO_BITMAP** buffer)
{
    al_destroy_bitmap(*buffer);
    al_destroy_display(*display);
}

void disp_pre_draw(ALLEGRO_BITMAP** buffer)
{
    al_set_target_bitmap(*buffer);
}

void disp_post_draw(ALLEGRO_DISPLAY** disp, ALLEGRO_BITMAP** buffer)
{
    al_set_target_backbuffer(*disp);
    al_draw_scaled_bitmap(*buffer, 0, 0, BUFFER_ANCHO, BUFFER_ALTO, 0, 0, DISPLAY_ANCHO, DISPLAY_ALTO, 0);

    al_flip_display();
}
