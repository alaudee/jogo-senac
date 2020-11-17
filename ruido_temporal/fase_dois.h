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

int num_perspectiva_2;

enum { VISAO_UM_2, VISAO_DOIS_2, VISAO_TRES_2, VISAO_QUATRO_2 };

bool sair_tela_2 = false;

int visao_anterior;

void perspectiva_um_2(ALLEGRO_DISPLAY *janela) {

	bool estado_perspectiva = false;

	ALLEGRO_BITMAP *background;

	Objeto* chave = (Objeto*)malloc(sizeof(Objeto));
	chave->altura = 90;
	chave->largura = 90;
	chave->x = (LARGURA_TELA / 2) - (chave->largura / 2);
	chave->y = (ALTURA_TELA / 2) - (chave->altura / 2) + 220;
	chave->bitmap = al_load_bitmap("imagens\\Fase2\\chave.png");

	al_register_event_source(fila_eventos, al_get_display_event_source(janela));

	al_set_window_title(janela, "Fase dois - Visão um");
	background = al_load_bitmap("imagens\\Fase2\\tela1.png");
	al_flip_display();
	while (!sair_programa && !estado_perspectiva && !sair_tela_2) {
		while (!al_event_queue_is_empty(fila_eventos)) {

			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);

			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				if (IsInside(evento.mouse.x, evento.mouse.y, seta_esquerda)) {
					estado_perspectiva = true;
					num_perspectiva_2 = VISAO_DOIS_2;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, seta_direita)) {
					estado_perspectiva = true;
					num_perspectiva_2 = VISAO_TRES_2;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, chave)) {
					inventario[0] = true;
				}
			}
			if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
				if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
					pause(janela, FASE_DOIS);
				}
				if (evento.keyboard.keycode == ALLEGRO_KEY_J) {
					Notacao(janela, inventario[3], FASE_DOIS);
				}
			}
			sair_programa = fechar_janela(janela, evento);
		}
		al_draw_bitmap(background, 0, 0, 0);
		if (!inventario[0]) {
			al_draw_bitmap(chave->bitmap, chave->x, chave->y, 0);
		}
		al_draw_bitmap(seta_direita->bitmap, seta_direita->x, seta_direita->y, 0);
		al_draw_bitmap(seta_esquerda->bitmap, seta_esquerda->x, seta_esquerda->y, 0);
		al_flip_display();
	}
	al_destroy_bitmap(background);
	al_destroy_bitmap(chave->bitmap);

	free(chave);
}

void perspectiva_dois_2(ALLEGRO_DISPLAY *janela) {

	bool estado_perspectiva = false;

	ALLEGRO_BITMAP *background = al_load_bitmap("imagens\\Fase2\\tela1.png");
	ALLEGRO_SAMPLE *morse = al_load_sample("sons\\morse.ogg");
	
	Objeto* telegrafo = (Objeto*)malloc(sizeof(Objeto));
	telegrafo->altura = 224;
	telegrafo->largura = 225;
	telegrafo->x = (LARGURA_TELA / 2) - (telegrafo->largura / 2);
	telegrafo->y = (ALTURA_TELA / 2) - (telegrafo->altura / 2);
	telegrafo->bitmap = al_load_bitmap("imagens\\Fase2\\telegrafo.png");


	al_register_event_source(fila_eventos, al_get_display_event_source(janela));

	al_set_window_title(janela, "Fase dois - Visão dois");
	al_flip_display();
	while (!sair_programa && !estado_perspectiva && !sair_tela_2) {
		while (!al_event_queue_is_empty(fila_eventos)) {

			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);

			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				if (IsInside(evento.mouse.x, evento.mouse.y, seta_esquerda)) {
					estado_perspectiva = true;
					num_perspectiva_2 = VISAO_QUATRO_2;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, seta_direita)) {
					estado_perspectiva = true;
					num_perspectiva_2 = VISAO_UM_2;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, telegrafo)) {
					al_play_sample(morse, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
			}
			else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
				if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
					pause(janela, FASE_DOIS);
				}
				if (evento.keyboard.keycode == ALLEGRO_KEY_J) {
					Notacao(janela, inventario[3], FASE_DOIS);
				}
			}

			sair_programa = fechar_janela(janela, evento);
		}
		al_draw_bitmap(background, 0, 0, 0);
		al_draw_bitmap(seta_direita->bitmap, seta_direita->x, seta_direita->y, 0);
		al_draw_bitmap(seta_esquerda->bitmap, seta_esquerda->x, seta_esquerda->y, 0);

		al_draw_bitmap(telegrafo->bitmap, telegrafo->x, telegrafo->y, 0);

		al_flip_display();
	}
	al_destroy_bitmap(background);

	free(telegrafo);
}

void perspectiva_tres_2(ALLEGRO_DISPLAY *janela) {

	bool estado_perspectiva = false;

	ALLEGRO_BITMAP *background;

	ALLEGRO_SAMPLE *som_papel2 = al_load_sample("sons\\som_papel.ogg");

	Objeto* objnota2 = (Objeto*)malloc(sizeof(Objeto));
	objnota2->altura = 90;
	objnota2->largura = 90;
	objnota2->x = (LARGURA_TELA / 2) - (objnota2->largura / 2);
	objnota2->y = (ALTURA_TELA / 2) - (objnota2->altura / 2) + 220;
	objnota2->bitmap = al_load_bitmap("imagens\\papeldenota.png");

	al_register_event_source(fila_eventos, al_get_display_event_source(janela));

	al_set_window_title(janela, "Fase dois - Visão três");
	background = al_load_bitmap("imagens\\Fase2\\tela1.png");
	al_flip_display();
	while (!sair_programa && !estado_perspectiva && !sair_tela_2) {
		while (!al_event_queue_is_empty(fila_eventos)) {

			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);

			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				if (IsInside(evento.mouse.x, evento.mouse.y, seta_esquerda)) {
					estado_perspectiva = true;
					num_perspectiva_2 = VISAO_UM_2;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, seta_direita)) {
					estado_perspectiva = true;
					num_perspectiva_2 = VISAO_QUATRO_2;
				}
				if (!inventario[3]) {
					if (IsInside(evento.mouse.x, evento.mouse.y, objnota2)) {
						inventario[3] = true;
						al_play_sample(som_papel2, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					}
				}
			}
			else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
				if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
					pause(janela, FASE_DOIS);
				}
				if (evento.keyboard.keycode == ALLEGRO_KEY_J) {
					Notacao(janela, inventario[3], FASE_DOIS);
				}
			}

			sair_programa = fechar_janela(janela, evento);
		}
		al_draw_bitmap(background, 0, 0, 0);
		al_draw_bitmap(seta_direita->bitmap, seta_direita->x, seta_direita->y, 0);
		al_draw_bitmap(seta_esquerda->bitmap, seta_esquerda->x, seta_esquerda->y, 0);

		if (!inventario[3]) {
			al_draw_bitmap(objnota2->bitmap, objnota2->x, objnota2->y, 0);
		}

		al_flip_display();
	}
	al_destroy_bitmap(background);

	free(objnota2);
}

void perspectiva_quatro_2(ALLEGRO_DISPLAY *janela) {

	bool estado_perspectiva = false;

	ALLEGRO_BITMAP *background;

	al_register_event_source(fila_eventos, al_get_display_event_source(janela));

	al_set_window_title(janela, "Fase dois - Visão quatro");
	background = al_load_bitmap("imagens\\Fase2\\tela1.png");
	al_flip_display();
	while (!sair_programa && !estado_perspectiva && !sair_tela_2) {
		while (!al_event_queue_is_empty(fila_eventos)) {

			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);

			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				if (IsInside(evento.mouse.x, evento.mouse.y, seta_esquerda)) {
					estado_perspectiva = true;
					num_perspectiva_2 = VISAO_TRES_2;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, seta_direita)) {
					estado_perspectiva = true;
					num_perspectiva_2 = VISAO_DOIS_2;
				}
			}
			else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
				if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
					pause(janela, FASE_DOIS);
				}
				if (evento.keyboard.keycode == ALLEGRO_KEY_J) {
					Notacao(janela, inventario[3], FASE_DOIS);
				}
			}

			sair_programa = fechar_janela(janela, evento);
		}
		al_draw_bitmap(background, 0, 0, 0);
		al_draw_bitmap(seta_direita->bitmap, seta_direita->x, seta_direita->y, 0);
		al_draw_bitmap(seta_esquerda->bitmap, seta_esquerda->x, seta_esquerda->y, 0);
		al_flip_display();
	}
	al_destroy_bitmap(background);
}

void fase_dois(ALLEGRO_DISPLAY *janela) {

	init();

	num_perspectiva_2 = VISAO_UM_2;
	sair_programa = false;

	while (!sair_programa && !sair_tela_2) {
		switch (num_perspectiva_2) {

		case VISAO_UM_2:
			perspectiva_um_2(janela);
			break;
		case VISAO_DOIS_2:
			perspectiva_dois_2(janela);
			break;
		case VISAO_TRES_2:
			perspectiva_tres_2(janela);
			break;
		case VISAO_QUATRO_2:
			perspectiva_quatro_2(janela);
			break;
		default:
			break;
		}
	}
}
