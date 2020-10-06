#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

int error_msg(char *text) {
	al_show_native_message_box(NULL, "ERRO", "Ocorreu o seguinte erro no programa: ", text, NULL, ALLEGRO_MESSAGEBOX_ERROR);
	return -1;
}