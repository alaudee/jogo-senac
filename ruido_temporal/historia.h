//Includes do C
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Includes Allegro
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

#include "Struct.h"

void tela_historia(ALLEGRO_DISPLAY *janela) {

	init();

	//backgrounds
	ALLEGRO_BITMAP *his1, *his2, *his3, *his4, *his5, *his6, *his7;

	//atribuindo as imagens no background (tela historia)
	his1 = al_load_bitmap("imagens\\historia\\his1.jpg");
	his2 = al_load_bitmap("imagens\\historia\\his2.jpg");
	his3 = al_load_bitmap("imagens\\historia\\his3.jpg");
	his4 = al_load_bitmap("imagens\\historia\\his4.jpg");
	his5 = al_load_bitmap("imagens\\historia\\his5.jpg");
	his6 = al_load_bitmap("imagens\\historia\\his6.jpg");
	his7 = al_load_bitmap("imagens\\historia\\his7.jpg");

	sair_programa = false;
	bool sair_tela = false;
	int historia = 1;
	al_draw_bitmap(his1, 0, 0, 0);
	al_register_event_source(fila_eventos, al_get_display_event_source(janela));

	al_flip_display();
	while (!sair_tela && !sair_programa)
	{
		while (!al_event_queue_is_empty(fila_eventos))
		{
			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);

			if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				sair_programa = true;
				sair_tela = true;
			}
			else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
			{
				historia++;
			}
			sair_programa = fechar_janela(janela, evento);
		}
		switch (historia)
		{
		case 2:
			al_draw_bitmap(his2, 0, 0, 0);
			al_flip_display();
			break;
		case 3:
			al_draw_bitmap(his3, 0, 0, 0);
			al_flip_display();
			break;
		case 4:
			al_draw_bitmap(his4, 0, 0, 0);
			al_flip_display();
			break;
		case 5:
			al_draw_bitmap(his5, 0, 0, 0);
			al_flip_display();
			break;
		case 6:
			al_draw_bitmap(his6, 0, 0, 0);
			al_flip_display();
			break;
		case 7:
			al_draw_bitmap(his7, 0, 0, 0);
			al_flip_display();
			break;
		case 8:
			estado_tela = FASE_UM;
			sair_tela = true;
			break;
		}
			
	}

	al_flip_display();

	// Finaliza a janela
	al_destroy_bitmap(his1);
	al_destroy_bitmap(his2);
	al_destroy_bitmap(his3);
	al_destroy_bitmap(his4);
	al_destroy_bitmap(his5);
	al_destroy_bitmap(his6);
	al_destroy_bitmap(his7);
}
