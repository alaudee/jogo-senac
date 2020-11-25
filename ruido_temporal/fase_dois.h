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

/*
	inventrario[0] = chave
	inventrario[1] = fone
	inventrario[2] = 
	inventrario[3] = nota
	inventrario[4] = 
	inventrario[5] =
*/

int num_perspectiva_2;

enum { VISAO_UM_2, VISAO_DOIS_2, VISAO_TRES_2, VISAO_QUATRO_2, VISAO_COFRE };

bool sair_tela_2 = false;

int visao_anterior;

void visao_cofre(ALLEGRO_DISPLAY *janela) {

	int passa_tela = 0;
	int res= 0 , click = 0;

	bool estado_perspectiva = false;
	
	ALLEGRO_BITMAP *background = al_load_bitmap("imagens\\Fase2\\perspec_cofre.png");

	ALLEGRO_BITMAP *primeira_tela, *segunda_tela, *terceira_tela, *quarta_tela, *vitoria, *derrota;
	primeira_tela = al_load_bitmap("imagens\\Fase2\\le_ou_te.png");
	segunda_tela = al_load_bitmap("imagens\\Fase2\\a_ou_i.png");
	terceira_tela = al_load_bitmap("imagens\\Fase2\\au_ou_la.png");
	quarta_tela = al_load_bitmap("imagens\\Fase2\\rea_ou_era.png");
	vitoria = al_load_bitmap("imagens\\Fase2\\gg_cofre.png");
	derrota = al_load_bitmap("imagens\\Fase2\\erro_cofre.png");

	al_register_event_source(fila_eventos, al_get_display_event_source(janela));

	al_set_window_title(janela, "Fase dois - visão cofre");

	Objeto* seta_baixo = (Objeto*)malloc(sizeof(Objeto));
	seta_baixo->altura = 90;
	seta_baixo->largura = 90;
	seta_baixo->x = (LARGURA_TELA / 2) - (seta_baixo->largura / 2);
	seta_baixo->y = (ALTURA_TELA / 2) - (seta_baixo->altura / 2) + 220;
	seta_baixo->bitmap = al_load_bitmap("imagens\\seta_baixo.png");

	Objeto* btn_esquerdo = (Objeto*)malloc(sizeof(Objeto));
	btn_esquerdo->altura = 76;
	btn_esquerdo->largura = 76;
	btn_esquerdo->x = 38;
	btn_esquerdo->y = 182;
	btn_esquerdo->bitmap = al_load_bitmap("imagens\\Fase2\\btn_cofre.png");

	Objeto* btn_direito = (Objeto*)malloc(sizeof(Objeto));
	btn_direito->altura = 76;
	btn_direito->largura = 76;
	btn_direito->x = 628;
	btn_direito->y = 182;
	btn_direito->bitmap = al_load_bitmap("imagens\\Fase2\\btn_cofre.png");

	al_flip_display();

	while (!sair_programa && !estado_perspectiva && !sair_tela_2) {
		while (!al_is_event_queue_empty(fila_eventos)) {

			ALLEGRO_EVENT evento;

			al_wait_for_event(fila_eventos, &evento);

			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				if (IsInside(evento.mouse.x, evento.mouse.y, seta_baixo)) {
					estado_perspectiva = true;
					num_perspectiva_2 = VISAO_TRES_2;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, btn_esquerdo)) {
					passa_tela++;
					click++;
					res = esq_ou_dir(1, passa_tela, res);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, btn_direito)) {
					passa_tela++;
					click++;
					res = esq_ou_dir(2, passa_tela, res);
				}
			}

			sair_programa = fechar_janela(janela, evento);
		}

		al_draw_bitmap(background, 0, 0, 0);

		al_draw_bitmap(seta_baixo->bitmap, seta_baixo->x, seta_baixo->y, 0);
		al_draw_bitmap(btn_esquerdo->bitmap, btn_esquerdo->x, btn_esquerdo->y, 0);
		al_draw_bitmap(btn_direito->bitmap, btn_direito->x, btn_direito->y, 0);
		

		if (click == 4) {
			if (res == 4) {
				al_draw_bitmap(vitoria, 0, 0, 0);
			}
			else {
				al_draw_bitmap(derrota, 0, 0, 0);
				al_flip_display();
				passa_tela = 0;
				res = 0;
				click = 0;
				al_rest(2.0);
			}
		}
		
		switch (passa_tela)
		{
		case 0:
			al_draw_bitmap(primeira_tela, 0, 0, 0);
			break;
		case 1:
			al_draw_bitmap(segunda_tela, 0, 0, 0);
			break;
		case 2:
			al_draw_bitmap(terceira_tela, 0, 0, 0);
			break;
		case 3:
			al_draw_bitmap(quarta_tela, 0, 0, 0);
			break;
		default:
			break;
		}

		al_flip_display();
	}

	al_destroy_bitmap(background);
	al_destroy_bitmap(seta_baixo->bitmap);
	al_destroy_bitmap(btn_esquerdo->bitmap);
	al_destroy_bitmap(btn_direito->bitmap);
	
	free(seta_baixo);
	free(btn_esquerdo);
	free(btn_direito);
}

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

	ALLEGRO_BITMAP *background = al_load_bitmap("imagens\\Fase2\\tela_telegrafo.png");
	ALLEGRO_SAMPLE *morse = al_load_sample("sons\\morse.ogg");
	
	Objeto* telegrafo = (Objeto*)malloc(sizeof(Objeto));
	telegrafo->altura = 224;
	telegrafo->largura = 225;
	telegrafo->x = (LARGURA_TELA / 2) - (telegrafo->largura / 2) + 150;
	telegrafo->y = (ALTURA_TELA / 2) - (telegrafo->altura / 2) + 26;
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
				else if (inventario[1] && inventariousado[1]) {
					if (IsInside(evento.mouse.x, evento.mouse.y, telegrafo)) {
						al_play_sample(morse, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
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

		al_draw_bitmap(telegrafo->bitmap, telegrafo->x, telegrafo->y, 0);

		al_flip_display();
	}
	al_destroy_bitmap(background);
	al_destroy_bitmap(telegrafo->bitmap);

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

	Objeto* cofre = (Objeto*)malloc(sizeof(Objeto));
	cofre->altura = 90;
	cofre->largura = 90;
	cofre->x = (LARGURA_TELA / 2) - (cofre->largura / 2)+100;
	cofre->y = (ALTURA_TELA / 2) - (cofre->altura / 2)+60;
	cofre->bitmap = al_load_bitmap("imagens\\Fase2\\cofre.png");

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
				else if (IsInside(evento.mouse.x, evento.mouse.y, cofre)) {
					estado_perspectiva = true;
					num_perspectiva_2 = VISAO_COFRE;
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
		al_draw_bitmap(cofre->bitmap, cofre->x, cofre->y, 0);

		if (!inventario[3]) {
			al_draw_bitmap(objnota2->bitmap, objnota2->x, objnota2->y, 0);
		}

		al_flip_display();
	}
	al_destroy_bitmap(background);
	al_destroy_bitmap(objnota2->bitmap);
	al_destroy_bitmap(cofre->bitmap);

	free(objnota2);
	free(cofre);
}

void perspectiva_quatro_2(ALLEGRO_DISPLAY *janela) {

	bool estado_perspectiva = false;

	ALLEGRO_BITMAP *background;

	al_register_event_source(fila_eventos, al_get_display_event_source(janela));
	
	Objeto* gaveta88 = (Objeto*)malloc(sizeof(Objeto));
	gaveta88->altura = 21;
	gaveta88->largura = 45;
	gaveta88->x = 386;
	gaveta88->y = 309;
	gaveta88->bitmap = al_load_bitmap("imagens\\Fase2\\88.png");

	al_set_window_title(janela, "Fase dois - Visão quatro");
	background = al_load_bitmap("imagens\\Fase2\\gaveteiro.png");
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
				if (inventario[0] && inventariousado[0]) {
					if (IsInside(evento.mouse.x, evento.mouse.y, gaveta88)) {
						inventario[1] = true;
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
		al_draw_bitmap(gaveta88->bitmap, gaveta88->x, gaveta88->y, 0);
		al_flip_display();
	}
	al_destroy_bitmap(background);
	al_destroy_bitmap(gaveta88->bitmap);

	free(gaveta88);
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
		case VISAO_COFRE:
			visao_cofre(janela);
		default:
			break;
		}
	}
}
