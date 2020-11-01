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

	Objeto* itemraiz = (Objeto*)malloc(sizeof(Objeto));
	itemraiz->largura = 60;
	itemraiz->altura = 60;
	itemraiz->x = 70;
	itemraiz->y = 390;
	itemraiz->bitmap = al_load_bitmap("imagens\\Fase1\\item-3.png");

	Objeto* itemrelogio = (Objeto*)malloc(sizeof(Objeto));
	itemrelogio->largura = 60;
	itemrelogio->altura = 60;
	itemrelogio->x = 140;
	itemrelogio->y = 390;
	itemrelogio->bitmap = al_load_bitmap("imagens\\Fase1\\item+5.png");

	Objeto* itemtermo = (Objeto*)malloc(sizeof(Objeto));
	itemtermo->largura = 60;
	itemtermo->altura = 60;
	itemtermo->x = 210;
	itemtermo->y = 390;
	itemtermo->bitmap = al_load_bitmap("imagens\\Fase1\\item-14.png");


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
			al_draw_bitmap(itemraiz->bitmap, itemraiz->x, itemraiz->y, 0);
		}
		if (inventario[1]) {
			al_draw_bitmap(itemrelogio->bitmap, itemrelogio->x, itemrelogio->y, 0);
		}
		if (inventario[2]) {
			al_draw_bitmap(itemtermo->bitmap, itemtermo->x, itemtermo->y, 0);
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