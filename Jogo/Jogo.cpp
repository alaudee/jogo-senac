#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro.h> //Lib allegro
#include <allegro5/allegro_image.h> //Lib para tratamento de imagens

int main(void)
{
	ALLEGRO_DISPLAY* janela = NULL; //Cria um ponteiro referênciando ao struct ALLEGRO_DISPLAY

	al_init(); //Inicia a lib do allegro dentro do escopo main

	janela = al_create_display(640, 480); //Cria uma janela com 640 px de altura e 48- px de largura

	al_clear_to_color(al_map_rgb(0, 0, 0)); //Colorir o display pelo padrão RGB

	al_flip_display(); //Diz ao compilador que o display criado deve ser mostrado na tela do PC

	al_rest(5.0); //A tela fica ativa por 5 segundos

	al_destroy_display(janela); //Destrói a display criada

	return 0;
}