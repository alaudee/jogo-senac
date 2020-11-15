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

void Mostrar_mensagem(char titulo[50], char titulo_caixa[50], char mensagem[100]) {
	int r = al_show_native_message_box(NULL, titulo, titulo_caixa, mensagem, NULL, ALLEGRO_MESSAGEBOX_OK_CANCEL);
	printf("%i", r);
}

int retornar_sim_nao(char titulo[50], char titulo_caixa[50], char mensagem[1000]) {
	int r = al_show_native_message_box(NULL, titulo, titulo_caixa, mensagem, NULL, ALLEGRO_MESSAGEBOX_OK_CANCEL);
	printf("%i", r);
	return r;
}

bool Verificarmusica(bool musica_fundo) {

	if (musica_fundo == true)
	{
		al_set_audio_stream_gain(musicafundo, 0);
		return false;
	}
	else
	{
		al_set_audio_stream_gain(musicafundo, 0.2);
;		return true;
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

	for (int i = 0; i < 5; i++) {
		inventario[i] = false;
		inventariousado[i] = false;
	}

	al_flip_display();

}