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
#include "pause.h"

int num_perspectiva;
ALLEGRO_DISPLAY *perspectiva = NULL;

enum{VISAO_UM, VISAO_DOIS, VISAO_TRES, VISAO_QUATRO};

bool sair_tela = false;

int visao_anterior;

void perspectiva_um(ALLEGRO_DISPLAY *janela) {

	bool estado_perspectiva = false;

	ALLEGRO_BITMAP *background;
	background = al_load_bitmap("imagens\\Alemanha_1.png");

	al_register_event_source(fila_eventos, al_get_display_event_source(janela));

	al_set_window_title(janela, "Visao um");

	al_flip_display();
	while (!sair_programa && !estado_perspectiva && !sair_tela) {
		while (!al_event_queue_is_empty(fila_eventos)) {
			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);

			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				if (IsInside(evento.mouse.x, evento.mouse.y, seta_esquerda)) {
					estado_perspectiva = true;
					num_perspectiva = VISAO_DOIS;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, seta_direita)) {
					estado_perspectiva = true;
					num_perspectiva = VISAO_TRES;
				}
			}
			else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
				if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
					pause(janela);
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

void perspectiva_dois(ALLEGRO_DISPLAY *janela) {

	bool estado_perspectiva = false;

	al_register_event_source(fila_eventos, al_get_display_event_source(janela));

	al_set_window_title(janela, "Visao dois");

	Objeto* btnchave;

	btnchave = (Objeto*)malloc(sizeof(Objeto));
	btnchave->largura = 174;
	btnchave->altura = 182;
	btnchave->x = LARGURA_TELA / 2 - (btnchave->largura / 2);
	btnchave->y = 100;
	btnchave->bitmap = al_load_bitmap("imagens\\chav.png");

	al_flip_display();
	while (!sair_programa && !estado_perspectiva) {
		while (!al_event_queue_is_empty(fila_eventos)) {

			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);

			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				if (IsInside(evento.mouse.x, evento.mouse.y, seta_esquerda)) {
					estado_perspectiva = true;
					num_perspectiva = VISAO_QUATRO;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, seta_direita)) {
					estado_perspectiva = true;
					num_perspectiva = VISAO_UM;
				}
				else if (!inventario[0]) {
					if (IsInside(evento.mouse.x, evento.mouse.y, btnchave)) {
						inventario[0] = true;
						Mostrar_mensagem("Chave", "Situação da chave", "Obtida!");
					}
				}
			}
			else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
				if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
					pause(janela);
				}
			}
			sair_programa = fechar_janela(janela, evento);
		}
		al_clear_to_color(al_map_rgb(255, 255, 255));
		if (!inventario[0]) {
			al_draw_bitmap(btnchave->bitmap, btnchave->x, btnchave->y, 0);
		}
		al_draw_bitmap(seta_direita->bitmap, seta_direita->x, seta_direita->y, 0);
		al_draw_bitmap(seta_esquerda->bitmap, seta_esquerda->x, seta_esquerda->y, 0);
		al_flip_display();
	}

	al_destroy_bitmap(btnchave->bitmap);

	free(btnchave);
}

void perspectiva_tres(ALLEGRO_DISPLAY *janela) {

	bool estado_perspectiva = false;

	al_register_event_source(fila_eventos, al_get_display_event_source(janela));

	al_set_window_title(janela, "Visao três");

	Objeto* btncofre;
	btncofre = (Objeto*)malloc(sizeof(Objeto));
	btncofre->largura = 61;
	btncofre->altura = 59;
	btncofre->x = LARGURA_TELA / 2 - (btncofre->largura / 2);
	btncofre->y = 300;
	btncofre->bitmap = al_load_bitmap("imagens\\cofre.jpg");

	al_flip_display();
	while (!sair_programa && !estado_perspectiva) {
		while (!al_event_queue_is_empty(fila_eventos)) {

			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);

			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				if (IsInside(evento.mouse.x, evento.mouse.y, seta_esquerda)) {
					estado_perspectiva = true;
					num_perspectiva = VISAO_UM;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, seta_direita)) {
					estado_perspectiva = true;
					num_perspectiva = VISAO_QUATRO;
				}
				if (IsInside(evento.mouse.x, evento.mouse.y, btncofre)) {
					if (inventario[0] == false) {
						Mostrar_mensagem("Cofre", "Situação do cofre", "Bloqueado!");
					}
					else {
						Mostrar_mensagem("Cofre", "Situação do cofre", "Desbloqueado!");
					}
				}

			}
			else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
				if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
					pause(janela);
				}
			}

			sair_programa = fechar_janela(janela, evento);
		}
		al_clear_to_color(al_map_rgb(0, 255, 0));
		al_draw_bitmap(btncofre->bitmap, btncofre->x, btncofre->y, 0);
		al_draw_bitmap(seta_direita->bitmap, seta_direita->x, seta_direita->y, 0);
		al_draw_bitmap(seta_esquerda->bitmap, seta_esquerda->x, seta_esquerda->y, 0);
		al_flip_display();
	}
	al_destroy_bitmap(btncofre->bitmap);

	free(btncofre);
}

void perspectiva_quatro(ALLEGRO_DISPLAY *janela) {

	bool estado_perspectiva = false;

	al_register_event_source(fila_eventos, al_get_display_event_source(janela));

	al_set_window_title(janela, "Visao quatro");

	al_flip_display();
	while (!sair_programa && !estado_perspectiva) {
		while (!al_event_queue_is_empty(fila_eventos)) {

			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);

			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				if (IsInside(evento.mouse.x, evento.mouse.y, seta_esquerda)) {
					estado_perspectiva = true;
					num_perspectiva = VISAO_TRES;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, seta_direita)) {
					estado_perspectiva = true;
					num_perspectiva = VISAO_DOIS;
				}
			}
			else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
				if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
					pause(janela);
				}
			}

			sair_programa = fechar_janela(janela, evento);
		}
		al_clear_to_color(al_map_rgb(0, 0,255));
		al_draw_bitmap(seta_direita->bitmap, seta_direita->x, seta_direita->y, 0);
		al_draw_bitmap(seta_esquerda->bitmap, seta_esquerda->x, seta_esquerda->y, 0);
		al_flip_display();
	}
}

void fase_um(ALLEGRO_DISPLAY *janela) {

	init();

	num_perspectiva = VISAO_UM;
	sair_programa = false;
	
	while (!sair_programa) {
		switch (num_perspectiva) {

		case VISAO_UM:
			perspectiva_um(janela);
			break;

		case VISAO_DOIS:
			perspectiva_dois(janela);
			break;

		case VISAO_TRES:
			perspectiva_tres(janela);
			break;

		case VISAO_QUATRO:
			perspectiva_quatro(janela);
			break;

		default:
			break;
		}
	}
}