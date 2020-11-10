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
	inventrario[3] = item anota��o
	inventrario[4] = item chave
	inventrario[5] = 
*/

bool sair_tela = false;

int visao_anterior;

int enigma_resol[3] = {-3, 5 ,-14};

bool primeira_entrada[5];

int valida_enigma(int vet_resp[], int res, int cont) {
 	if (vet_resp[cont] == res) {
		cont += 1;

		if (cont == 3) {
			Mostrar_mensagem("GANHO", "DEU CERTO", "CATAPIMBAS");
			Mostrar_mensagem("conciente", "Pensamento", "A ENIGMA abriu um compartimento secreto, dentro dele contendo uma chave");
			Mostrar_mensagem("Item", "Item pego", "Adquirida uma chave");
			inventario[4] = true;
		}
		return cont;
	}
	else {
		Mostrar_mensagem("ERRO", "DEU ERRO", "CATAPIMBAS");
		return 0;
	}	
}

void tela_enigma(ALLEGRO_DISPLAY *janela) {

	bool estado_perspectiva = false;

	int cont = 0;

	ALLEGRO_BITMAP *background = al_load_bitmap("imagens\\Fase1\\enigmatela.png");

	ALLEGRO_BITMAP  *telinha, *telablitz, *telaloading;
	telinha = al_load_bitmap("imagens\\Fase1\\telacod1.png");
	telablitz = al_load_bitmap("imagens\\Fase1\\blitz.png");
	telaloading = al_load_bitmap("imagens\\Fase1\\loading.png");

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
				if (inventariousado[0] == true) {
					if (IsInside(evento.mouse.x, evento.mouse.y, itemraiz)) {
						cont = valida_enigma(enigma_resol, -3, cont);
					}
				}
				if (inventariousado[1] == true) {
					if (IsInside(evento.mouse.x, evento.mouse.y, itemrelogio)) {
						cont = valida_enigma(enigma_resol, 5, cont);
					}
				}
				if (inventariousado[2] == true) {
					if (IsInside(evento.mouse.x, evento.mouse.y, itemtermo)) {
						cont = valida_enigma(enigma_resol, -14, cont);

					}
				}
			}
			if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
				if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
					pause(janela);
				}
			}
			if (!primeira_entrada[1]) {
				Mostrar_mensagem("R�dio","Ci�ntista amigo","Parece que esta m�quina � a ENIGMA!Ela foi usada para encriptografar as mensagens nazistas.");
				primeira_entrada[1] = true;
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
	al_destroy_bitmap(telinha);

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
				if (evento.keyboard.keycode == ALLEGRO_KEY_J) {
					Notacao(janela, inventario[3]);
				}
			}

			else if (!primeira_entrada[0]) {
				Mostrar_mensagem("Conci�ncia", "Pensamento", "Voc� Acorda Em uma sala desnorteado, sem entender o que esta acontecendo");
				Mostrar_mensagem("Radio", "Ci�ntista amigo", "ALO!!! Voc� esta bem? Gra�as a newton. Voc� esta em 1941, em uma base nazista, voc� foi telestransportado para ai por acharmos alguns erros temporais. TENTA ARRUMA AI E SAI DAI O MAIS RAPIDO POSSIVEL!");
				primeira_entrada[0] = true;
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
	al_destroy_bitmap(objenigma->bitmap);

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
 				if (IsInside(evento.mouse.x, evento.mouse.y, seta_esquerda)) {
					estado_perspectiva = true;
					num_perspectiva = VISAO_QUATRO;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, seta_direita)) {
					estado_perspectiva = true;
					num_perspectiva = VISAO_UM;
				}
				else if (!inventario[0]) {
					if (IsInside(evento.mouse.x, evento.mouse.y, livro3)) {
						inventario[0] = true;
						Mostrar_mensagem("Conci�ncia", "Pensamento", "Voc� abriu o Livro e de repente caiu um bot�o.");
						Mostrar_mensagem("Item", "Item pego!", "Voce obteve um botao de -3!!");
					}
				}
				if (!inventario[3]) {
					if (IsInside(evento.mouse.x, evento.mouse.y, objteste)) {
						inventario[3] = true;
						Mostrar_mensagem("Conci�ncia", "Pensamento", "Voc� acha uma anota��o.");
						Mostrar_mensagem("Radio", "Ci�ntista amigo", "Na sua mochila, al�m deste r�dio, voc� tem um caderno para fazer anota��es.(Aperte J para abrir o caderno)");
					}
				}
			}
			else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
				if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
					pause(janela);
				}
				if (evento.keyboard.keycode == ALLEGRO_KEY_J) {
					Notacao(janela,inventario[3]);
				}

			}
			sair_programa = fechar_janela(janela, evento);

			al_draw_bitmap(background, 0, 0, 0);
			if (!inventario[3]) {
				al_draw_bitmap(objteste->bitmap, objteste->x, objteste->y, 0);
			}
			al_draw_bitmap(seta_direita->bitmap, seta_direita->x, seta_direita->y, 0);
			al_draw_bitmap(seta_esquerda->bitmap, seta_esquerda->x, seta_esquerda->y, 0);
			al_draw_bitmap(livro3->bitmap, livro3->x, livro3->y, 0);

			al_flip_display();
		}
	}
	al_destroy_bitmap(background);
	al_destroy_bitmap(livro3->bitmap);
	al_destroy_bitmap(objteste->bitmap);
	
	free(livro3);
	free(objteste);
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

	Objeto *objtranca = (Objeto*)malloc(sizeof(Objeto));
	objtranca->largura = 14;
	objtranca->altura = 15;
	objtranca->x = 432;
	objtranca->y = 317;
	objtranca->bitmap = al_load_bitmap("imagens\\Fase1\\tranca.png");

	al_set_window_title(janela, "Visao tr�s");

	al_flip_display();
	while (!sair_programa && !estado_perspectiva && !sair_tela) {
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
				if (IsInside(evento.mouse.x, evento.mouse.y, objtranca)) {
					if (!inventario[4]) {
						Mostrar_mensagem("Conciente", "Pensamento", "Voc� n�o possui nenhuma chave");
					}
					else {
						Mostrar_mensagem("Conciente", "Pensamento", "Parab�ns, passou de fase");
						estado_tela = FASE_DOIS;
						sair_tela = true;
					}
				}
			}
			else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
				if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
					pause(janela);
				}
				if (evento.keyboard.keycode == ALLEGRO_KEY_J) {
					Notacao(janela, inventario[3]);
				}
			}
			sair_programa = fechar_janela(janela, evento);
		}
		al_draw_bitmap(background, 0, 0, 0);
		
		al_draw_bitmap(objtermo->bitmap, objtermo->x, objtermo->y, 0);
		al_draw_bitmap(seta_direita->bitmap, seta_direita->x, seta_direita->y, 0);
		al_draw_bitmap(seta_esquerda->bitmap, seta_esquerda->x, seta_esquerda->y, 0);
		al_draw_bitmap(objtranca->bitmap, objtranca->x, objtranca->y, 0);
		al_flip_display();
	}
	al_destroy_bitmap(background);
	al_destroy_bitmap(objtermo->bitmap);
	al_destroy_bitmap(objtranca->bitmap);


	free(objtermo);
	free(objtranca);

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
				if (evento.keyboard.keycode == ALLEGRO_KEY_J) {
					Notacao(janela, inventario[3]);
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
	al_destroy_bitmap(objrelogio->bitmap);

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