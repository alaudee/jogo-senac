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

enum{VISAO_UM, VISAO_DOIS, VISAO_TRES, VISAO_QUATRO, ENIGMA};

bool sair_tela = false;

int visao_anterior;

void tela_enigma(ALLEGRO_DISPLAY *janela) {

	bool estado_perspectiva = false;

	ALLEGRO_BITMAP *background = al_load_bitmap("imagens\\Fase1\\enigmatela.png");

	al_register_event_source(fila_eventos, al_get_display_event_source(janela));

	al_set_window_title(janela, "Tela Enigma");

	Objeto* seta_baixo = (Objeto*)malloc(sizeof(Objeto));
	seta_baixo->altura = 90;
	seta_baixo->largura = 90;
	seta_baixo->x = (LARGURA_TELA / 2) - (seta_baixo->largura / 2);
	seta_baixo->y = (ALTURA_TELA / 2) - (seta_baixo->altura / 2) + 220;
	seta_baixo->bitmap = al_load_bitmap("imagens\\seta_baixo.png");

	Objeto* itemraiz = (Objeto*)malloc(sizeof(Objeto));
	itemraiz->largura = 42;
	itemraiz->altura = 42;
	itemraiz->x = 288;
	itemraiz->y = 283;
	itemraiz->bitmap = al_load_bitmap("imagens\\Fase1\\item-3.png");

	Objeto* itemrelogio = (Objeto*)malloc(sizeof(Objeto));
	itemrelogio->largura = 42;
	itemrelogio->altura = 42;
	itemrelogio->x = 161;
	itemrelogio->y = 349;
	itemrelogio->bitmap = al_load_bitmap("imagens\\Fase1\\item+5.png");

	Objeto* itemtermo = (Objeto*)malloc(sizeof(Objeto));
	itemtermo->largura = 42;
	itemtermo->altura = 42;
	itemtermo->x = 604;
	itemtermo->y = 417;
	itemtermo->bitmap = al_load_bitmap("imagens\\Fase1\\item-14.png");

	al_flip_display();

	while (!sair_programa && !estado_perspectiva && !sair_tela) {
		while (!al_event_queue_is_empty(fila_eventos)) {
			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);

			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				if (IsInside(evento.mouse.x, evento.mouse.y, seta_baixo)) {
					estado_perspectiva = true;
					num_perspectiva = VISAO_UM;
				}
			}
			if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
				if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
					pause(janela);
				}
			}
			sair_programa = fechar_janela(janela, evento);
		}
		al_draw_bitmap(background, 0, 0, 0);
		al_draw_bitmap(seta_baixo->bitmap, seta_baixo->x, seta_baixo->y, 0);
		if (inventariousado[0] == true) {
			al_draw_bitmap(itemraiz->bitmap, itemraiz->x, itemraiz->y, 0);
		}
		if (inventariousado[1] == true) {
			al_draw_bitmap(itemrelogio->bitmap, itemrelogio->x, itemrelogio->y, 0);
		}
		if (inventariousado[2] == true) {
			al_draw_bitmap(itemtermo->bitmap, itemtermo->x, itemtermo->y, 0);
		}
		al_flip_display();
		
	}
	al_destroy_bitmap(background);
	al_destroy_bitmap(seta_baixo->bitmap);
	al_destroy_bitmap(itemraiz->bitmap);
	al_destroy_bitmap(itemrelogio->bitmap);
	al_destroy_bitmap(itemtermo->bitmap);

	free(itemraiz);
	free(itemrelogio);
	free(itemtermo);
	free(seta_baixo);
}

void perspectiva_um(ALLEGRO_DISPLAY *janela) {

	bool estado_perspectiva = false;

	ALLEGRO_BITMAP *background;
	background = al_load_bitmap("imagens\\Fase1\\tela1.png");

	al_register_event_source(fila_eventos, al_get_display_event_source(janela));

	al_set_window_title(janela, "Visao um");

	Objeto* objenigma = (Objeto*)malloc(sizeof(Objeto));
	objenigma->altura = 80;
	objenigma->largura = 80;
	objenigma->x = (LARGURA_TELA / 2) - (objenigma->largura / 2) ;
	objenigma->y = (ALTURA_TELA / 2) - (objenigma->altura / 2) + 83;
	objenigma->bitmap =	al_load_bitmap("imagens\\Fase1\\enigma.png");

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
				else if (IsInside(evento.mouse.x, evento.mouse.y, objenigma)) {
					estado_perspectiva = true;
					num_perspectiva = ENIGMA;
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
		al_draw_bitmap(objenigma->bitmap, objenigma->x, objenigma->y, 0);
		al_draw_bitmap(seta_direita->bitmap, seta_direita->x, seta_direita->y, 0);
		al_draw_bitmap(seta_esquerda->bitmap, seta_esquerda->x, seta_esquerda->y, 0);

		al_flip_display();
	}
	al_destroy_bitmap(background);
	free(objenigma);
}

void perspectiva_dois(ALLEGRO_DISPLAY *janela) {

	bool estado_perspectiva = false;

	ALLEGRO_BITMAP *background;
	background = al_load_bitmap("imagens\\Fase1\\tela2.png");

	al_register_event_source(fila_eventos, al_get_display_event_source(janela));

	Objeto* objteste = (Objeto*)malloc(sizeof(Objeto));
	objteste->altura = 80;
	objteste->largura = 80;
	objteste->x = (LARGURA_TELA / 2) - (objteste->largura / 2) - 230;
	objteste->y = (ALTURA_TELA / 2) - (objteste->altura / 2) + 160;
	objteste->bitmap = al_load_bitmap("imagens\\Fase1\\relogiobolso.png");

	al_set_window_title(janela, "Visao dois");

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
					if (IsInside(evento.mouse.x, evento.mouse.y, objteste)) {
						inventario[0] = true;
						Mostrar_mensagem("Item", "Item pego!", "Voce obteve um botao de -3!!");
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
		al_draw_bitmap(background, 0, 0, 0);
		if (!inventario[0]) {
			al_draw_bitmap(objteste->bitmap, objteste->x, objteste->y, 0);
		}
		al_draw_bitmap(seta_direita->bitmap, seta_direita->x, seta_direita->y, 0);
		al_draw_bitmap(seta_esquerda->bitmap, seta_esquerda->x, seta_esquerda->y, 0);
		al_flip_display();
	}
	al_destroy_bitmap(background);

}

void perspectiva_tres(ALLEGRO_DISPLAY *janela) {

	bool estado_perspectiva = false;

	al_register_event_source(fila_eventos, al_get_display_event_source(janela));

	ALLEGRO_BITMAP *background;
	background = al_load_bitmap("imagens\\Fase1\\tela3.png");

	Objeto* objtermo = (Objeto*)malloc(sizeof(Objeto));
	objtermo->altura = 60;
	objtermo->largura = 40;
	objtermo->x = (LARGURA_TELA / 2) - (objtermo->largura / 2) - 200;
	objtermo->y = (ALTURA_TELA / 2) - (objtermo->altura / 2);
	objtermo->bitmap = al_load_bitmap("imagens\\Fase1\\termometro.png");

	al_set_window_title(janela, "Visao três");

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
				else if (!inventario[2])
				{
					if (IsInside(evento.mouse.x, evento.mouse.y, objtermo)) {
						inventario[2] = true;
						Mostrar_mensagem("Item","Item pego!","Voce pegou o botao de -14!");
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
		al_draw_bitmap(background, 0, 0, 0);
		
		al_draw_bitmap(objtermo->bitmap, objtermo->x, objtermo->y, 0);
		al_draw_bitmap(seta_direita->bitmap, seta_direita->x, seta_direita->y, 0);
		al_draw_bitmap(seta_esquerda->bitmap, seta_esquerda->x, seta_esquerda->y, 0);
		al_flip_display();
	}
	al_destroy_bitmap(background);

}

void perspectiva_quatro(ALLEGRO_DISPLAY *janela) {

	bool estado_perspectiva = false;

	al_register_event_source(fila_eventos, al_get_display_event_source(janela));
	ALLEGRO_BITMAP *background;
	background = al_load_bitmap("imagens\\Fase1\\tela4.png");

	al_set_window_title(janela, "Visao quatro");

	Objeto* objrelogio = (Objeto*)malloc(sizeof(Objeto));
	objrelogio->altura = 80;
	objrelogio->largura = 80;
	objrelogio->x = (LARGURA_TELA / 2) - (objrelogio->largura / 2);
	objrelogio->y = (ALTURA_TELA / 2) - (objrelogio->altura / 2)- 150;
	objrelogio->bitmap = al_load_bitmap("imagens\\Fase1\\relogio.png");

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
				else if (!inventario[1]) {
					if (IsInside(evento.mouse.x, evento.mouse.y, objrelogio)) {
						inventario[1] = true;
						Mostrar_mensagem("Item", "Item pego!", "Voce pegou o botao de +5!");
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
		al_draw_bitmap(background, 0, 0, 0);
		
		al_draw_bitmap(objrelogio->bitmap, objrelogio->x, objrelogio->y, 0);
		al_draw_bitmap(seta_direita->bitmap, seta_direita->x, seta_direita->y, 0);
		al_draw_bitmap(seta_esquerda->bitmap, seta_esquerda->x, seta_esquerda->y, 0);
		al_flip_display();
	}
	al_destroy_bitmap(background);
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
		case ENIGMA:
			tela_enigma(janela);
			break;
		default:
			break;
		}
	}
}