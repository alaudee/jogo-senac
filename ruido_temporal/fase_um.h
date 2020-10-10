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

//enum{VISAO_UM,VISAO_DOIS, VISAO_TRES, VISAO_QUATRO};

void fase_um() {

	init();

	ALLEGRO_BITMAP *background;
	background = al_load_bitmap("imagens\\Alemanha_1.png");

	sair_programa = false;
	bool sair_tela = false;

	ALLEGRO_DISPLAY *janela_jogo = NULL;
	janela_jogo = al_create_display(LARGURA_TELA, ALTURA_TELA);
	al_draw_bitmap(background, 0, 0, 0);
	al_register_event_source(fila_eventos, al_get_display_event_source(janela_jogo));

	//iniciando o mouse
	al_set_system_mouse_cursor(janela_jogo, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

	al_flip_display();
	while (!sair_tela && !sair_programa)
	{
		while (!al_event_queue_is_empty(fila_eventos))
		{
			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);

			sair_programa = fechar_janela(janela_jogo, evento);
		}

		al_draw_bitmap(seta_direita->bitmap, seta_direita->x, seta_direita->y, 0);
		al_draw_bitmap(seta_esquerda->bitmap, seta_esquerda->x, seta_esquerda->y, 0);
		al_flip_display();
	}

	// Finaliza a janela
	al_destroy_display(janela_jogo);
	al_destroy_bitmap(background);
}