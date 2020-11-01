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

//includes das telas
#include "menu.h"
#include "historia.h"
#include "fase_um.h"

int main(void) {
	init();

	ALLEGRO_DISPLAY *janela = NULL;

	janela = al_create_display(LARGURA_TELA, ALTURA_TELA);

	//implementação da musica
	musicafundo = al_load_audio_stream("sons\\03 A Tempo.ogg", 4, 1024);
	al_attach_audio_stream_to_mixer(musicafundo, al_get_default_mixer());
	al_set_audio_stream_playmode(musicafundo, ALLEGRO_PLAYMODE_LOOP);
	al_set_audio_stream_gain(musicafundo, 0.2);

	//Iniciando o Mouse, sendo usado em todas as janelas
	al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

	//Objetos a serem usados em todas as janelas(seta esquerda e direita por hora)
	seta_direita = (Objeto*)malloc(sizeof(Objeto));
	seta_direita->bitmap = al_load_bitmap("imagens\\seta_direita.png");
	seta_direita->altura = 100;
	seta_direita->largura = 100;
	seta_direita->x = 667;
	seta_direita->y = (ALTURA_TELA / 2) - (seta_direita->largura / 2);

	seta_esquerda = (Objeto*)malloc(sizeof(Objeto));
	seta_esquerda->bitmap = al_load_bitmap("imagens\\seta_esquerda.png");
	seta_esquerda->altura = 100;
	seta_esquerda->largura = 100;
	seta_esquerda->x = -40;
	seta_esquerda->y = (ALTURA_TELA / 2) - (seta_esquerda->largura / 2);

	while (!sair_programa) {
		
		switch (estado_tela)
		{
		case MENU:
			tela_menu(janela);
			break;
		case HISTORIA:
			tela_historia(janela);
			break;
		case FASE_UM:
			fase_um(janela);
			break;
		default:
			break;
		}
	
	}
	al_destroy_display(janela);
	al_destroy_event_queue(fila_eventos);
	al_destroy_audio_stream(musicafundo);
	al_destroy_bitmap(seta_direita->bitmap);
	al_destroy_bitmap(seta_esquerda->bitmap);

	free(seta_direita);
	free(seta_esquerda);
}