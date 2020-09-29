#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

#define LARGURA_TELA 740
#define ALTURA_TELA 500

int error_msg(char *text) {
	al_show_native_message_box(NULL, "ERRO", "Ocorreu o seguinte erro no programa: ", text, NULL, ALLEGRO_MESSAGEBOX_ERROR);
	return -1;
}

int main(void) {

	ALLEGRO_DISPLAY *janela = NULL;
	ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
	ALLEGRO_BITMAP *btn_sair = NULL; // objeto interativo na tela
	int sair = 0;

	al_init();
	al_init_ttf_addon();
	al_install_mouse();

	janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
	fila_eventos = al_create_event_queue();

	// na janela criada, utiliza do mouse padrão do computador
	al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

	// criando as dimensões de largura e altura do botão
	btn_sair = al_create_bitmap(100, 50);

	// dizendo que os eventos serão tratados pelo mouse
	al_register_event_source(fila_eventos, al_get_mouse_event_source());

	al_flip_display();

	while (!sair) 
	{
		while (!al_is_event_queue_empty(fila_eventos)) 
		{
			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);

			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) 
			{
				if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(btn_sair) - 10 &&
					evento.mouse.x <= LARGURA_TELA - 10 && evento.mouse.y <= ALTURA_TELA - 10 &&
					evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(btn_sair) - 10) {
					sair = 1;
				}
			}
		}

		al_clear_to_color(al_map_rgb(0, 0, 0));

		al_set_target_bitmap(btn_sair);
		al_clear_to_color(al_map_rgb(255, 0, 0));

		al_set_target_bitmap(al_get_backbuffer(janela));
		al_draw_bitmap(btn_sair, LARGURA_TELA - al_get_bitmap_width(btn_sair) - 10, ALTURA_TELA - al_get_bitmap_height(btn_sair) - 10, 0);

		al_flip_display();
	}

	al_destroy_bitmap(btn_sair);
	al_destroy_event_queue(fila_eventos);
	al_destroy_display(janela);

	return 0;
}