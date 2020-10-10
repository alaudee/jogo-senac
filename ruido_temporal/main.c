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
	//fase_um();
	while (!sair_programa) {

		switch (estado_tela)
		{
		case MENU:
			tela_menu();
			break;
		case HISTORIA:
			tela_historia();
			break;
		case FASE_UM:
			fase_um();
			break;
		}

	}
}