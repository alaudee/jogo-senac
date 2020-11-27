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
#include "funcoes.h"

void tela_menu(ALLEGRO_DISPLAY *janela) {

	init();

	//objetos
	Objeto* btnjogar;
	Objeto* btnmusica;
	ALLEGRO_BITMAP *background = NULL;
	//ALLEGRO_BITMAP *musicaon = al_load_bitmap("imagens\\on.png");
	//ALLEGRO_BITMAP *musicaoff = al_load_bitmap("imagens\\off.jpg");

	bool sair_tela = false;

	al_register_event_source(fila_eventos, al_get_display_event_source(janela));
	background = al_load_bitmap("imagens\\menu.png");
	al_draw_bitmap(background, 0, 0,0);

	//atribuindo valores ao objeto
	btnjogar = (Objeto*)malloc(sizeof(Objeto));
	btnjogar->largura = 245;
	btnjogar->altura = 84;
	btnjogar->x = LARGURA_TELA / 2 - (btnjogar->largura / 2);
	btnjogar->y = 200;
	btnjogar->bitmap = al_load_bitmap("imagens\\btnjogar.jpg");

	btnmusica = (Objeto*)malloc(sizeof(Objeto));
	btnmusica->largura = 50;
	btnmusica->altura = 50;
	btnmusica->x = LARGURA_TELA - (btnmusica->largura) - 10;
	btnmusica->y = 10;
	btnmusica->bitmap = al_load_bitmap("imagens\\on.png");;

	while (!sair_tela && !sair_programa)
	{
		while (!al_event_queue_is_empty(fila_eventos))
		{
			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);
			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
			{
				if (IsInside(evento.mouse.x, evento.mouse.y, btnjogar))
				{
					estado_tela = FASE_UM;
					sair_tela = true;
				}
				else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
					if (IsInside(evento.mouse.x, evento.mouse.y, btnmusica)) {
						musica_fundo = Verificarmusica(musica_fundo);
					}
				}
			}
			sair_programa = fechar_janela(janela, evento);
		}

		al_draw_text(fontetitulo, al_map_rgb(44, 148, 86), LARGURA_TELA / 2, 90, ALLEGRO_ALIGN_CENTRE, "Ruido Temporal");
		al_set_target_bitmap(al_get_backbuffer(janela));
		al_draw_bitmap(btnjogar->bitmap, btnjogar->x, btnjogar->y, 0);
		al_draw_bitmap(btnmusica->bitmap, btnmusica->x, btnmusica->y, 0);

		al_flip_display();
	}
	al_destroy_bitmap(background);
	al_destroy_bitmap(btnjogar->bitmap);
	al_destroy_bitmap(btnmusica->bitmap);
	//al_destroy_bitmap(musicaon);
	//al_destroy_bitmap(musicaoff);

	free(btnjogar);
	free(btnmusica);
}
