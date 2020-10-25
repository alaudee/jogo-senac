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


void pause(ALLEGRO_DISPLAY *janela) {

	Objeto* btnmusica;
	Objeto* btncontinuar;
	Objeto* chaveinv;
	ALLEGRO_BITMAP *background = NULL;

	bool sair_tela = false;

	btnmusica = (Objeto*)malloc(sizeof(Objeto));
	btnmusica->largura = 50;
	btnmusica->altura = 50;
	btnmusica->x = LARGURA_TELA - (btnmusica->largura) - 10;
	btnmusica->y = 10;
	btnmusica->bitmap = al_load_bitmap("imagens\\on.png");

	btncontinuar = (Objeto*)malloc(sizeof(Objeto));
	btncontinuar->largura = 245;
	btncontinuar->altura = 84;
	btncontinuar->x = LARGURA_TELA / 2 - (btncontinuar->largura / 2);
	btncontinuar->y = 200;
	btncontinuar->bitmap = al_load_bitmap("imagens\\imgcontinuar.png");

	chaveinv = (Objeto*)malloc(sizeof(Objeto));
	chaveinv->largura = 50;
	chaveinv->altura = 50;
	chaveinv->x = 100;
	chaveinv->y = 390;
	chaveinv->bitmap = al_load_bitmap("imagens\\chavinv.png");

	al_register_event_source(fila_eventos, al_get_display_event_source(janela));
	background = al_load_bitmap("imagens\\teste2.jpg");

	al_flip_display();

	while (!sair_tela) {
	
		while (!al_event_queue_is_empty(fila_eventos)) {
			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);
			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {

				if (IsInside(evento.mouse.x, evento.mouse.y, btncontinuar))
				{				
					sair_tela = true;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, btnmusica)) {
					if (musica_fundo == true)
					{
						al_set_audio_stream_gain(musicafundo, 0);
						musica_fundo = false;
					}
					else
					{
						al_set_audio_stream_gain(musicafundo, 0.2);
						musica_fundo = true;
					}
				}
			}
			else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
				if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
					sair_tela = true;

				}
			}
			sair_programa = fechar_janela(janela, evento);
		}

		al_draw_bitmap(background, 0, 0, 0);
		if (inventario[0]) {
			al_draw_bitmap(chaveinv->bitmap, chaveinv->x, chaveinv->y, 0);
		}
		al_draw_bitmap(btncontinuar->bitmap, btncontinuar->x, btncontinuar->y, 0);
		al_draw_bitmap(btnmusica->bitmap, btnmusica->x, btnmusica->y, 0);
		

		al_flip_display();
	}

	al_destroy_bitmap(background);
	al_destroy_bitmap(btncontinuar->bitmap);
	al_destroy_bitmap(btnmusica->bitmap);

	free(btncontinuar);
	free(btnmusica);

}