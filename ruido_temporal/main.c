#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

#define LARGURA_TELA 740
#define ALTURA_TELA 500

int error_msg(char *text) {
	al_show_native_message_box(NULL, "ERRO", "Ocorreu o seguinte erro no programa: ", text, NULL, ALLEGRO_MESSAGEBOX_ERROR);
	return -1;
}

int main(void) {

	ALLEGRO_DISPLAY *janela = NULL;
	ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;

	al_init();
	al_init_font_addon();
	al_init_ttf_addon();

	janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
	fila_eventos = al_create_event_queue();

	al_register_event_source(fila_eventos, al_get_display_event_source(janela));
	al_clear_to_color(al_map_rgb(255, 255, 255));

	al_flip_display();

	while (1) {
		ALLEGRO_EVENT evento;
		al_wait_for_event(fila_eventos, &evento);

		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			int resp = al_show_native_message_box(janela, "Fechar", "Deseja sair do programa?", "", NULL, ALLEGRO_MESSAGEBOX_YES_NO);
			if (resp)
				break;
		}

		al_flip_display();
	}

	al_destroy_event_queue(fila_eventos);
	al_destroy_display(janela);

	return 0;
}