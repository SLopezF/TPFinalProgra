
#include "a_keyboard.h"

extern unsigned char key[ALLEGRO_KEY_MAX];

void keyboard_init(void)  //pone en cero un arreglo key que tiene tantos espacios como cantidad de teclas disponibles para presionar
{
    memset(key, 0, sizeof(key));
}

void keyboard_update(ALLEGRO_EVENT* event)
{
    switch(event->type)
    {
        case ALLEGRO_EVENT_TIMER:
            for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
            {
                key[i] &= KEY_SEEN;      
            }

            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            key[event->keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
            break;
        case ALLEGRO_EVENT_KEY_UP:
            key[event->keyboard.keycode] &= KEY_RELEASED;
            break;
    }
}
