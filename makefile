ifdef compile_allegro
LIBRERIAS_ALLEGRO = $$(pkg-config allegro-5 allegro_image-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5 --libs --cflags)

ALLEGRO: main.o alien.o ship.o barriers.o puntos.o a_display.o a_general.o a_impresion_display.o a_keyboard.o a_menus.o a_sprites.o
	gcc main.o alien.o ship.o barriers.o puntos.o a_display.o a_general.o a_impresion_display.o a_keyboard.o a_menus.o a_sprites.o $(LIBRERIAS_ALLEGRO) -o TP_FINAL -g -Wall 

main.o: main.c main.h ship.h alien.h barriers.h puntos.h a_main.h
	gcc -D ALLEGRO main.c -c $(LIBRERIAS_ALLEGRO)

alien.o: alien.h shipyalien.h
	gcc -D ALLEGRO alien.c -c $(LIBRERIAS_ALLEGRO)

ship.o: ship.h shipyalien.h
	gcc -D ALLEGRO ship.c -c $(LIBRERIAS_ALLEGRO)

barriers.o: barriers.h
	gcc -D ALLEGRO barriers.c -c $(LIBRERIAS_ALLEGRO)

puntos.o: puntos.h
	gcc -D ALLEGRO puntos.c -c $(LIBRERIAS_ALLEGRO)

a_display.o: a_display.h
	gcc -D ALLEGRO a_display.c -c $(LIBRERIAS_ALLEGRO)

a_general.o: a_general.h
	gcc -D ALLEGRO a_general.c -c $(LIBRERIAS_ALLEGRO)

a_impresion_display.o: a_impresion_display.h
	gcc -D ALLEGRO a_impresion_display.c -c $(LIBRERIAS_ALLEGRO)

a_keyboard.o: a_keyboard.h
	gcc -D ALLEGRO a_keyboard.c -c $(LIBRERIAS_ALLEGRO)

a_menus.o: a_menus.h
	gcc -D ALLEGRO a_menus.c -c $(LIBRERIAS_ALLEGRO)

a_sprites.o: a_sprites.h
	gcc -D ALLEGRO a_sprites.c -c $(LIBRERIAS_ALLEGRO)

clean:
	rm main.o alien.o ship.o barriers.o puntos.o a_display.o a_general.o a_impresion_display.o a_keyboard.o a_menus.o a_sprites.o

endif

ifdef compile_raspi

RASPI:	main.o alien.o ship.o barriers.o puntos.o start.o pause.o game_over.o 
	gcc -g -Wall main.o alien.o ship.o barriers.o puntos.o start.o pause.o game_over.o joydrv.o termlib.o disdrv.o -o TP_FINAL

main.o: main.c main.h r_main.h ship.h start.h game_over.h pause.h alien.h shipyalien.h barriers.h
	gcc -D RASPI main.c -c

alien.o: alien.h shipyalien.h
	gcc -D RASPI alien.c -c

ship.o: ship.h shipyalien.h
	gcc -D RASPI ship.c -c

barriers.o: barriers.h
	gcc -D RASPI barriers.c -c

puntos.o: puntos.h
	gcc -D RASPI puntos.c -c  

start.o: start.h
	gcc -D RASPI start.c -c 

pause.o: pause.h
	gcc -D RASPI pause.c -c 

game_over.o: game_over.h
	gcc -D RASPI game_over.c -c 

clean:
	rm main.o alien.o ship.o barriers.o puntos.o start.o pause.o game_over.o

endif



