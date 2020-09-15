#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro.h> //Lib allegro
#include <allegro5/allegro_image.h> //Lib para tratamento de imagens
#include <allegro5/allegro_native_dialog.h> // Lib usada para mostrar texto na tela
#include <allegro5/allegro_ttf.h> // Lib para utilizar fontes True type
#include <allegro5/allegro_font.h> // Lib para utilizar fontes

// Utilizando constantes para poder definir um valor global de display
const int LARGURA_TELA = 640;
const int ALTURA_TELA = 480;

// Função que recebe como parâmetro um texto e retorna o erro ocorrido
int error_msg(char *text) {
	al_show_native_message_box(NULL, "ERRO","Ocorreu o seguinte erro e o programa sera finalizado:",text, NULL, ALLEGRO_MESSAGEBOX_ERROR);
	return -1;
}

int main(void)
{
	ALLEGRO_DISPLAY* janela = NULL; 
	ALLEGRO_FONT* fonte = NULL;
	ALLEGRO_EVENT_QUEUE* fila_eventos = NULL;

	if (!al_init()) {
		char erro[] = "Falha ao inicializar o allegro";
		return error_msg(erro);
	}

	al_init_font_addon();

	if (!al_init_ttf_addon()) {
		char erro[] = "Falha ao inicializar o add-on ttf";
		return error_msg(erro);
	}

	janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
	if (!janela) {
		char erro[] = "Falha ao criar a janela";
		return error_msg(erro);
	}

	al_set_window_title(janela, "Ruido temporal");

	fila_eventos = al_create_event_queue();
	if (!fila_eventos) {
		char erro[] = "Falha ao criar a fila de eventos";
		return error_msg(erro);
	}

	fonte = al_load_font("C:\\Users\\chris\\source\\repos\\jogo-senac\\Fontes\\pixel_arial\\Pixel_Arial_11\\PIXEARG_.TTF", 20, 0);
	if (!fonte) {
		al_destroy_display(janela);
		char erro[] = "Erro ao carregar a fonte";
		return error_msg(erro);
	}

	al_register_event_source(fila_eventos, al_get_display_event_source(janela));

	al_clear_to_color(al_map_rgb(255, 255, 255));

	al_draw_text(fonte, al_map_rgb(0, 0, 255), LARGURA_TELA/2, ALTURA_TELA - 270, ALLEGRO_ALIGN_CENTRE, "Ruído Temporal");
	// Desenhando um texto na tela criada com uma variável criada dentro no parãmetro

	float versao = 0.01;
	al_draw_textf(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA/2, ALTURA_TELA/2, ALLEGRO_ALIGN_CENTRE, "versão %.2f", versao);
	// Desenhando uma variável externa dentro do método

	al_flip_display();
	// Atualiza a tela

	while (1) {
		ALLEGRO_EVENT evento;
		al_wait_for_event(fila_eventos, &evento);

		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			int resp = al_show_native_message_box(janela, "Fechar", "Deseja fechar o jogo?", "", NULL, ALLEGRO_MESSAGEBOX_YES_NO);
			
			if (resp)
				break;
		}

		al_flip_display();
	}

	al_destroy_font(fonte);
	al_destroy_display(janela);
	al_destroy_event_queue(fila_eventos);

	return 0;
}