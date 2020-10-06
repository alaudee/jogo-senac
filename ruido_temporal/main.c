#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include "evento_mouse.h"

#define LARGURA_TELA 740
#define ALTURA_TELA 500

ALLEGRO_BITMAP *btn_sair = NULL;

int main(void) {

	inicia_mouse();

	int sair = 0;

	al_init();

	btn_sair = al_create_bitmap(100, 50);

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