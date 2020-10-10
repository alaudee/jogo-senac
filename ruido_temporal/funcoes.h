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

#include "struct.h"

int IsInside(int x, int y, Objeto *objeto) {

	if (x >= objeto->x && x <= (objeto->x + objeto->largura) && y >= objeto->y && y <= (objeto->y + objeto->altura))
	{
		return 1;
	}
	return 0;
}

bool fechar_janela(ALLEGRO_DISPLAY *janela_atual, ALLEGRO_EVENT evento) {

	if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		return true;
	}
	else {
		return false;
	}
}

void init() {	

	//Inicializar libs e addons
	al_init();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_mouse();
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(5);
	al_install_keyboard();

	//aplicação da fonte
	fontetitulo = al_load_font("fontes\\PIXEARG_.TTF", 48, 0);

	//iniciando a fila de eventos
	fila_eventos = al_create_event_queue();

	//captação dos eventos de mouse e teclado
	al_register_event_source(fila_eventos, al_get_mouse_event_source());
	al_register_event_source(fila_eventos, al_get_keyboard_event_source());

	//inicialização do estado tela do ENUM = MENU
	estado_tela = MENU;

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

	al_flip_display();

}