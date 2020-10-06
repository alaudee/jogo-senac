#include <allegro5/allegro.h>

#define LARGURA_TELA 740
#define ALTURA_TELA 500

ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;

int inicia_mouse() {
	al_init();
	al_install_mouse();

	janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
	fila_eventos = al_create_event_queue();

	al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

	al_register_event_source(fila_eventos, al_get_mouse_event_source());

	return 1;
}