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

/*
	inventrario[0] = item -3 da raiz
	inventrario[1] = item +5 do relogio
	inventrario[2] = item -14 do termo
	inventrario[3] = item anotação
	inventrario[4] = item chave
	inventrario[5] = 
*/

bool sair_tela = false;

int visao_anterior;

int enigma_resol[3] = {-3, 5 ,-14};

/*
	textsbox[0] = falas perspectiva 1
	textsbox[1] = fala tela enigma
	textsbox[2] = fala obj-3
	textsbox[3] = fala nota
	textsbox[4] = fala termometro
	textsbox[5] = fala relogio
	textsbox[6] = falas da chave do enigma
	textsbox[7] =
	textsbox[8] =
	textsbox[9] =
	textsbox[10] =

*/

int valida_enigma(int vet_resp[], int res, int cont) {
 	if (vet_resp[cont] == res) {
		cont += 1;
		return cont;
	}

}

void tela_enigma(ALLEGRO_DISPLAY *janela) {

	bool estado_perspectiva = false;

	ALLEGRO_SAMPLE *som_tecla = al_load_sample("sons\\som_teclado.ogg");

	int cont = 0;

	int cont_falas = 1;

	int click = 0;

	ALLEGRO_BITMAP *background = al_load_bitmap("imagens\\Fase1\\enigmatela.png");

	ALLEGRO_BITMAP  *telinha, *telablitz, *telaloading,*falaenigma, *telaerror;
	telinha = al_load_bitmap("imagens\\Fase1\\telacod1.png");
	telablitz = al_load_bitmap("imagens\\Fase1\\blitz.png");
	telaloading = al_load_bitmap("imagens\\Fase1\\loading.png");
	falaenigma = al_load_bitmap("imagens\\Fase1\\texts\\falaenigma.png");
	telaerror = al_load_bitmap("imagens\\Fase1\\error.png");

	ALLEGRO_BITMAP *text1, *text2, *text3;
	text1 = al_load_bitmap("imagens\\Fase1\\texts\\textenigma1.png");
	text2 = al_load_bitmap("imagens\\Fase1\\texts\\textenigma2.png");
	text3 = al_load_bitmap("imagens\\Fase1\\texts\\textenigma3.png");

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

	Objeto* botao15 = (Objeto*)malloc(sizeof(Objeto));
	botao15->largura = 42;
	botao15->altura = 42;
	botao15->x = 289;
	botao15->y = 349;
	botao15->bitmap = al_load_bitmap("imagens\\Fase1\\botao-15.png");

	Objeto* botao4 = (Objeto*)malloc(sizeof(Objeto));
	botao4->largura = 42;
	botao4->altura = 42;
	botao4->x = 476;
	botao4->y = 283;
	botao4->bitmap = al_load_bitmap("imagens\\Fase1\\botao+4.png");

	Objeto* botao3 = (Objeto*)malloc(sizeof(Objeto));
	botao3->largura = 42;
	botao3->altura = 42;
	botao3->x = 87;
	botao3->y = 283;
	botao3->bitmap = al_load_bitmap("imagens\\Fase1\\botao3.png");

	al_flip_display();

	while (!sair_programa && !estado_perspectiva && !sair_tela) {
		while (!al_event_queue_is_empty(fila_eventos)) {
			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);

			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				if (!textsbox[1]) {
					textsbox[1] = true;
				}
				if (inventario[4] && !textsbox[6]) {
					cont_falas++;
				}
				if (IsInside(evento.mouse.x, evento.mouse.y, seta_baixo)) {
					estado_perspectiva = true;
					num_perspectiva = VISAO_UM;
					al_play_sample(som_seta, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
				if (IsInside(evento.mouse.x, evento.mouse.y, botao15)) {
					al_play_sample(som_tecla, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					cont = valida_enigma(enigma_resol, -15, cont);
					click++;
				}
				if (IsInside(evento.mouse.x, evento.mouse.y, botao3)) {
					al_play_sample(som_tecla, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					cont = valida_enigma(enigma_resol, 3, cont);
					click++;
				}
				if (IsInside(evento.mouse.x, evento.mouse.y, botao4)) {
					al_play_sample(som_tecla, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					cont = valida_enigma(enigma_resol, 4, cont);
					click++;
				}
				if (!inventario[4]) {
					if (inventariousado[0] == true) {
						if (IsInside(evento.mouse.x, evento.mouse.y, itemraiz)) {
							al_play_sample(som_tecla, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
							cont = valida_enigma(enigma_resol, -3, cont);
							click++;
						}
					}
					if (inventariousado[1] == true) {
						if (IsInside(evento.mouse.x, evento.mouse.y, itemrelogio)) {
							al_play_sample(som_tecla, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
							cont = valida_enigma(enigma_resol, 5, cont);
							click++;
							}
					}
					if (inventariousado[2] == true) {
						if (IsInside(evento.mouse.x, evento.mouse.y, itemtermo)) {
							al_play_sample(som_tecla, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
							cont = valida_enigma(enigma_resol, -14, cont);
							click++;
						}
					}
				}
			}
			if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
				if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
					pause(janela,10);
					//aqui é um valor designado para indicar que esta na tela da enigma, 
					//podendo usar os itens somente quando esta nela.
				}
			}
			sair_programa = fechar_janela(janela, evento);
		}
		al_draw_bitmap(background, 0, 0, 0);
		if (cont == 3) {
			telinha = telablitz;
		}
		if (cont > 0 && cont < 3) {
			telinha = telaloading;
		}
		al_draw_bitmap(telinha, 0, 0, 0);

		al_draw_bitmap(botao15->bitmap, botao15->x, botao15->y, 0);
		al_draw_bitmap(botao3->bitmap, botao3->x, botao3->y, 0);
		al_draw_bitmap(botao4->bitmap, botao4->x, botao4->y, 0);

		al_draw_bitmap(seta_baixo->bitmap, seta_baixo->x, seta_baixo->y, 0);

		if (click == 3) {
			if (cont == 3) {
				inventario[4] = true;
			}
			else {
				al_draw_bitmap(telaerror, 0, 0, 0);
				al_flip_display();
				cont = 0;
				click = 0;
				al_rest(2.0);
			}
		}

		if (inventariousado[0] == true) {
			al_draw_bitmap(itemraiz->bitmap, itemraiz->x, itemraiz->y, 0);
		}
		if (inventariousado[1] == true) {
			al_draw_bitmap(itemrelogio->bitmap, itemrelogio->x, itemrelogio->y, 0);
		}
		if (inventariousado[2] == true) {
			al_draw_bitmap(itemtermo->bitmap, itemtermo->x, itemtermo->y, 0);
		}
		if (!textsbox[1]) {
			al_draw_bitmap(falaenigma, 0, 0, 0);
		}
		if (inventario[4]) {
			switch (cont_falas)
			{
			case 1:
				al_draw_bitmap(text1, 0, 0, 0);
				break;
			case 2:
				al_draw_bitmap(text2, 0, 0, 0);
				break;
			case 3:
				al_draw_bitmap(text3, 0, 0, 0);
				break;
			case 4:
				textsbox[6] = true;
				break;
			}
		}
		al_flip_display();

		
	}
	al_destroy_bitmap(background);
	al_destroy_bitmap(telinha);
	al_destroy_bitmap(falaenigma);
	al_destroy_bitmap(text1);
	al_destroy_bitmap(text2);
	al_destroy_bitmap(text3);
	al_destroy_sample(som_tecla);

	al_destroy_bitmap(botao15->bitmap);
	al_destroy_bitmap(botao3->bitmap);
	al_destroy_bitmap(botao4->bitmap);
	al_destroy_bitmap(seta_baixo->bitmap);
	al_destroy_bitmap(itemraiz->bitmap);
	al_destroy_bitmap(itemrelogio->bitmap);
	al_destroy_bitmap(itemtermo->bitmap);

	free(itemraiz);
	free(itemrelogio);
	free(itemtermo);
	free(seta_baixo);
	free(botao15);
	free(botao3);
	free(botao4);
}

void perspectiva_um(ALLEGRO_DISPLAY *janela) {

	bool estado_perspectiva = false;

	int cont_falas = 1;

	ALLEGRO_BITMAP *background, *falaini1,*falaini2,*falaini3;
	background = al_load_bitmap("imagens\\Fase1\\tela1.png");
	falaini1 = al_load_bitmap("imagens\\Fase1\\texts\\falaini1.png");
	falaini2 = al_load_bitmap("imagens\\Fase1\\texts\\falaini2.png");
	falaini3 = al_load_bitmap("imagens\\Fase1\\texts\\falaini3.png");


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
				if (!textsbox[0]) {
					cont_falas++;
				}
				if (IsInside(evento.mouse.x, evento.mouse.y, seta_esquerda)) {
					estado_perspectiva = true;
					num_perspectiva = VISAO_DOIS;
					al_play_sample(som_seta, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, seta_direita)) {
					estado_perspectiva = true;
					num_perspectiva = VISAO_TRES;
					al_play_sample(som_seta, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, objenigma)) {
					estado_perspectiva = true;
					num_perspectiva = ENIGMA;
				}
			}
			else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
				if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
					pause(janela, FASE_UM);
				}
				if (evento.keyboard.keycode == ALLEGRO_KEY_J) {
					Notacao(janela, inventario[3], FASE_UM);
				}
			}
		

			sair_programa = fechar_janela(janela, evento);
		}
		al_draw_bitmap(background, 0, 0, 0);
		al_draw_bitmap(objenigma->bitmap, objenigma->x, objenigma->y, 0);
		al_draw_bitmap(seta_direita->bitmap, seta_direita->x, seta_direita->y, 0);
		al_draw_bitmap(seta_esquerda->bitmap, seta_esquerda->x, seta_esquerda->y, 0);
		if (!textsbox[0]) {
			switch (cont_falas)
			{
			case 1:
				al_draw_bitmap(falaini1, 0, 0, 0);
				al_flip_display();
				break;
			case 2:
				al_draw_bitmap(falaini2, 0, 0, 0);
				al_flip_display();
				break;
			case 3:
				al_draw_bitmap(falaini3, 0, 0, 0);
				al_flip_display();
				break;
			default:
				textsbox[0] = true;
				break;
			}
		}
		al_flip_display();
	}

	al_destroy_bitmap(background);
	al_destroy_bitmap(objenigma->bitmap);
	al_destroy_bitmap(falaini1);
	al_destroy_bitmap(falaini2);

	free(objenigma);
}

void perspectiva_dois(ALLEGRO_DISPLAY *janela) {

	bool estado_perspectiva = false;

	ALLEGRO_BITMAP *background,*textlivro,*textnota;
	background = al_load_bitmap("imagens\\Fase1\\tela2.png");
	textlivro = al_load_bitmap("imagens\\Fase1\\texts\\text-3.png");
	textnota = al_load_bitmap("imagens\\Fase1\\texts\\textnota.png");

	ALLEGRO_SAMPLE *som_papel = al_load_sample("sons\\som_papel.ogg");

	al_register_event_source(fila_eventos, al_get_display_event_source(janela));

	Objeto* objnota = (Objeto*)malloc(sizeof(Objeto));
	objnota->altura = 40;
	objnota->largura = 60;
	objnota->x = (LARGURA_TELA / 2) - (objnota->largura / 2) - 230;
	objnota->y = (ALTURA_TELA / 2) - (objnota->altura / 2) + 140;
	objnota->bitmap = al_load_bitmap("imagens\\papeldenota.png");

	Objeto* livro3 = (Objeto*)malloc(sizeof(Objeto));
	livro3->largura = 15;
	livro3->altura = 38;
	livro3->x = 107;
	livro3->y = 238;
	livro3->bitmap = al_load_bitmap("imagens\\Fase1\\livro-3.png");

	al_set_window_title(janela, "Visao dois");

	al_flip_display();
	while (!sair_programa && !estado_perspectiva) {
		while (!al_event_queue_is_empty(fila_eventos)) {

			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);

			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)  {
				if (inventario[0] && !textsbox[2]) {
					textsbox[2] = true;
				}
				if (inventario[3] && !textsbox[3]) {
					textsbox[3] = true;
				}

 				if (IsInside(evento.mouse.x, evento.mouse.y, seta_esquerda)) {
					estado_perspectiva = true;
					num_perspectiva = VISAO_QUATRO;
					al_play_sample(som_seta, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, seta_direita)) {
					estado_perspectiva = true;
					num_perspectiva = VISAO_UM;
					al_play_sample(som_seta, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
				else if (!inventario[0]) {
					if (IsInside(evento.mouse.x, evento.mouse.y, livro3)) {
						inventario[0] = true;
						al_play_sample(som_item, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					}
				}
				if (!inventario[3]) {
					if (IsInside(evento.mouse.x, evento.mouse.y, objnota)) {
						inventario[3] = true;
						al_play_sample(som_papel, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					}
				}
			}
			else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
				if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
					pause(janela, FASE_UM);
				}
				if (evento.keyboard.keycode == ALLEGRO_KEY_J) {
					Notacao(janela,inventario[3], FASE_UM);
				}

			}
			sair_programa = fechar_janela(janela, evento);

			al_draw_bitmap(background, 0, 0, 0);
			if (!inventario[3]) {
				al_draw_bitmap(objnota->bitmap, objnota->x, objnota->y, 0);
			}
			al_draw_bitmap(seta_direita->bitmap, seta_direita->x, seta_direita->y, 0);
			al_draw_bitmap(seta_esquerda->bitmap, seta_esquerda->x, seta_esquerda->y, 0);
			al_draw_bitmap(livro3->bitmap, livro3->x, livro3->y, 0);
			if (inventario[0] && !textsbox[2]) {
				al_draw_bitmap(textlivro, 0, 0, 0);
			}
			if (inventario[3] && !textsbox[3]) {
				al_draw_bitmap(textnota, 0, 0, 0);
			}

			al_flip_display();
		}
	}
	al_destroy_bitmap(background);
	al_destroy_bitmap(livro3->bitmap);
	al_destroy_bitmap(objnota->bitmap);
	al_destroy_bitmap(textlivro);
	al_destroy_bitmap(textnota);
	al_destroy_sample(som_papel);

	free(livro3);
	free(objnota);
}

void perspectiva_tres(ALLEGRO_DISPLAY *janela) {

	bool estado_perspectiva = false;

	al_register_event_source(fila_eventos, al_get_display_event_source(janela));

	ALLEGRO_SAMPLE *som_trancado = al_load_sample("sons\\porta_trancada.ogg");

	ALLEGRO_BITMAP *background,*texttermo,*textnaochave,*textfinal;
	background = al_load_bitmap("imagens\\Fase1\\tela3.png");
	texttermo = al_load_bitmap("imagens\\Fase1\\texts\\text-14.png");
	textnaochave = al_load_bitmap("imagens\\Fase1\\texts\\textnaochave.png");
	textfinal = al_load_bitmap("imagens\\Fase1\\texts\\textfinal.png");

	Objeto* objtermo = (Objeto*)malloc(sizeof(Objeto));
	objtermo->altura = 60;
	objtermo->largura = 40;
	objtermo->x = (LARGURA_TELA / 2) - (objtermo->largura / 2) - 200;
	objtermo->y = (ALTURA_TELA / 2) - (objtermo->altura / 2);
	objtermo->bitmap = al_load_bitmap("imagens\\Fase1\\termometro.png");

	Objeto *objtranca = (Objeto*)malloc(sizeof(Objeto));
	objtranca->largura = 14;
	objtranca->altura = 15;
	objtranca->x = 432;
	objtranca->y = 317;
	objtranca->bitmap = al_load_bitmap("imagens\\Fase1\\tranca.png");

	al_set_window_title(janela, "Visao três");

	al_flip_display();
	while (!sair_programa && !estado_perspectiva && !sair_tela) {
		while (!al_event_queue_is_empty(fila_eventos)) {

			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);			

			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				if (!inventario[4] && textsbox[6]) {
					textsbox[6] = false;
				}
				if (inventario[2] && !textsbox[4]) {
					textsbox[4] = true;
				}
				if (inventario[2] && textsbox[4]) {
					textsbox[6] = false ;
				}
				if (IsInside(evento.mouse.x, evento.mouse.y, seta_esquerda)) {
					estado_perspectiva = true;
					num_perspectiva = VISAO_UM;
					al_play_sample(som_seta, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, seta_direita)) {
					estado_perspectiva = true;
					num_perspectiva = VISAO_QUATRO;
					al_play_sample(som_seta, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
				else if (!inventario[2])
				{
					if (IsInside(evento.mouse.x, evento.mouse.y, objtermo)) {
						inventario[2] = true;	
						al_play_sample(som_item, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					}
				}
				if (IsInside(evento.mouse.x, evento.mouse.y, objtranca)) {
					if (!inventario[4]) {
						textsbox[6] = true;
						al_play_sample(som_trancado, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					}
					else {
						textsbox[6] = true;
						estado_tela = FASE_DOIS;
						sair_tela = true;
					}
				}
			}
			else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
				if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
					pause(janela,FASE_UM);
				}
				if (evento.keyboard.keycode == ALLEGRO_KEY_J) {
					Notacao(janela, inventario[3], FASE_UM);
				}
			}
			sair_programa = fechar_janela(janela, evento);
		}
		al_draw_bitmap(background, 0, 0, 0);
		
		al_draw_bitmap(objtermo->bitmap, objtermo->x, objtermo->y, 0);
		al_draw_bitmap(seta_direita->bitmap, seta_direita->x, seta_direita->y, 0);
		al_draw_bitmap(seta_esquerda->bitmap, seta_esquerda->x, seta_esquerda->y, 0);
		al_draw_bitmap(objtranca->bitmap, objtranca->x, objtranca->y, 0);
		if (inventario[2] && !textsbox[4]) {
			al_draw_bitmap(texttermo,0,0,0);
		}
		if (!inventario[4] && textsbox[6]) {
			al_draw_bitmap(textnaochave, 0, 0, 0);
		}
		if (inventario[4] && textsbox[6]) {
			al_draw_bitmap(textfinal, 0, 0, 0);
		}
		al_flip_display();
	}
	al_destroy_bitmap(background);
	al_destroy_bitmap(objtermo->bitmap);
	al_destroy_bitmap(objtranca->bitmap);
	al_destroy_bitmap(texttermo);
	al_destroy_bitmap(textnaochave);
	al_destroy_bitmap(textfinal);
	al_destroy_sample(som_trancado);

	free(objtermo);
	free(objtranca);

}

void perspectiva_quatro(ALLEGRO_DISPLAY *janela) {

	bool estado_perspectiva = false;

	al_register_event_source(fila_eventos, al_get_display_event_source(janela));
	ALLEGRO_BITMAP *background, *textrelogio;
	background = al_load_bitmap("imagens\\Fase1\\tela4.png");
	textrelogio = al_load_bitmap("imagens\\Fase1\\texts\\text+5.png");

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
				if (inventario[1] && !textsbox[5]) {
					textsbox[5] = true;
				}
				if (IsInside(evento.mouse.x, evento.mouse.y, seta_esquerda)) {
					estado_perspectiva = true;
					num_perspectiva = VISAO_TRES;
					al_play_sample(som_seta, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, seta_direita)) {
					estado_perspectiva = true;
					num_perspectiva = VISAO_DOIS;
					al_play_sample(som_seta, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
				else if (!inventario[1]) {
					if (IsInside(evento.mouse.x, evento.mouse.y, objrelogio)) {
						inventario[1] = true;
						al_play_sample(som_item, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					}
				}
			}
			else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
				if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
					pause(janela, FASE_UM);
				}
				if (evento.keyboard.keycode == ALLEGRO_KEY_J) {
					Notacao(janela, inventario[3], FASE_UM);
				}
			}

			sair_programa = fechar_janela(janela, evento);
		}
		al_draw_bitmap(background, 0, 0, 0);
		
		al_draw_bitmap(objrelogio->bitmap, objrelogio->x, objrelogio->y, 0);
		al_draw_bitmap(seta_direita->bitmap, seta_direita->x, seta_direita->y, 0);
		al_draw_bitmap(seta_esquerda->bitmap, seta_esquerda->x, seta_esquerda->y, 0);
		if (inventario[1] && !textsbox[5]) {
			al_draw_bitmap(textrelogio,0,0,0);
		}
		al_flip_display();
	}
	al_destroy_bitmap(background);
	al_destroy_bitmap(objrelogio->bitmap);
	al_destroy_bitmap(textrelogio);

	free(objrelogio);
}

void fase_um(ALLEGRO_DISPLAY *janela) {

	init();

	num_perspectiva = VISAO_UM;
	sair_programa = false;
	
	while (!sair_programa && !sair_tela) {
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