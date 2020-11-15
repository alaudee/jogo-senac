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


void pause(ALLEGRO_DISPLAY *janela, int fase) {

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

	//itens da fase 1
	Objeto* itemraiz = (Objeto*)malloc(sizeof(Objeto));
	itemraiz->largura = 42;
	itemraiz->altura = 42;
	itemraiz->x = 70;
	itemraiz->y = 390;
	itemraiz->bitmap = al_load_bitmap("imagens\\Fase1\\item-3.png");

	Objeto* itemrelogio = (Objeto*)malloc(sizeof(Objeto));
	itemrelogio->largura = 42;
	itemrelogio->altura = 42;
	itemrelogio->x = 140;
	itemrelogio->y = 390;
	itemrelogio->bitmap = al_load_bitmap("imagens\\Fase1\\item+5.png");

	Objeto* itemtermo = (Objeto*)malloc(sizeof(Objeto));
	itemtermo->largura = 42;
	itemtermo->altura = 42;
	itemtermo->x = 210;
	itemtermo->y = 390;
	itemtermo->bitmap = al_load_bitmap("imagens\\Fase1\\item-14.png");

	Objeto* itemchave = (Objeto*)malloc(sizeof(Objeto));
	itemchave->largura = 42;
	itemchave->altura = 42;
	itemchave->x = 280;
	itemchave->y = 390;
	itemchave->bitmap = al_load_bitmap("imagens\\Fase1\\chave.png");

	//itens da fase 2

	Objeto* objteste = (Objeto*)malloc(sizeof(Objeto));
	objteste->altura = 90;
	objteste->largura = 90;
	objteste->x = 70;
	objteste->y = 390;
	objteste->bitmap = al_load_bitmap("imagens\\Fase2\\relogiobolso.png");

	al_register_event_source(fila_eventos, al_get_display_event_source(janela));
	background = al_load_bitmap("imagens\\teste2.jpg");

	al_flip_display();

	while (!sair_tela && !sair_programa) {
	
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
				else if (IsInside(evento.mouse.x, evento.mouse.y, itemraiz)) {
					inventariousado[0] = retornar_sim_nao("Item", "Item a ser usado", "Você quer usar este item?");
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, itemrelogio)) {
					inventariousado[1] = retornar_sim_nao("Item", "Item a ser usado", "Você quer usar este item?");
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, itemtermo)) {
					inventariousado[2] = retornar_sim_nao("Item", "Item a ser usado", "Você quer usar este item?");
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
		if (fase == FASE_UM) {
			if (inventario[0] && !inventariousado[0]) {
				al_draw_bitmap(itemraiz->bitmap, itemraiz->x, itemraiz->y, 0);
			}
			if (inventario[1] && !inventariousado[1]) {
				al_draw_bitmap(itemrelogio->bitmap, itemrelogio->x, itemrelogio->y, 0);
			}
			if (inventario[2] && !inventariousado[2]) {
				al_draw_bitmap(itemtermo->bitmap, itemtermo->x, itemtermo->y, 0);
			}
			if (inventario[4]) {
				al_draw_bitmap(itemchave->bitmap, itemchave->x, itemchave->y, 0);
			}
		}
		if (fase == FASE_DOIS) {
			if (inventario[0] && !inventariousado[0]) {
				al_draw_bitmap(objteste->bitmap, objteste->x, objteste->y, 0);
			}
		}

		al_draw_bitmap(btncontinuar->bitmap, btncontinuar->x, btncontinuar->y, 0);
		al_draw_bitmap(btnmusica->bitmap, btnmusica->x, btnmusica->y, 0);
		

		al_flip_display();
	}

	al_destroy_bitmap(background);
	al_destroy_bitmap(btncontinuar->bitmap);
	al_destroy_bitmap(itemraiz->bitmap);
	al_destroy_bitmap(itemrelogio->bitmap);
	al_destroy_bitmap(itemtermo->bitmap);
	al_destroy_bitmap(itemchave->bitmap);
	al_destroy_bitmap(objteste->bitmap);

	free(btncontinuar);
	free(btnmusica);
	free(itemraiz);
	free(itemrelogio);
	free(itemtermo);
	free(itemchave);
	free(objteste);
	
}

void Notacao(ALLEGRO_DISPLAY *janela, bool inventario,int fase) {

	ALLEGRO_BITMAP *nota_fase1 = al_load_bitmap("imagens\\Fase1\\nota.png");

	bool sair_tela = false;

	al_register_event_source(fila_eventos, al_get_display_event_source(janela));

	al_set_window_title(janela, "Anotações");
	al_flip_display();

	if (inventario == false) {
		Mostrar_mensagem("Consiente", "Pensamento", "Você não possui nenhuma anotação");

	}
	else
	{
		while (!sair_programa && !sair_tela) {
			while (!al_event_queue_is_empty(fila_eventos)) {
				ALLEGRO_EVENT evento;
				al_wait_for_event(fila_eventos, &evento);

				if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
					if (evento.keyboard.keycode == ALLEGRO_KEY_J) {
						sair_tela = true;
					}
				}
				sair_programa = fechar_janela(janela, evento);
			}
			if (fase == FASE_UM) {
				al_draw_bitmap(nota_fase1, 0, 0, 0);
			}
			al_flip_display();
		}
		al_destroy_bitmap(nota_fase1);
	}

}