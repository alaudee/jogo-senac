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
	ALLEGRO_BITMAP *his1, *his2;

	//atribuindo as imagens no background (tela historia)
	his1 = al_load_bitmap("imagens\\historia\\Telafinal1.png");
	his2 = al_load_bitmap("imagens\\historia\\Telafinal2.png");


	sair_programa = false;
	bool sair_tela = false;
	int historia = 0;
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
		case 1:
			al_draw_bitmap(his2, 0, 0, 0);
			al_flip_display();
			break;
		case 2:
			sair_programa = true;
			break;
		}
			
	}

	al_flip_display();

	// Finaliza a janela
	al_destroy_bitmap(his1);
	al_destroy_bitmap(his2);
}
