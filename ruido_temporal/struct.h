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

#ifndef Struct_H
#define Struct_H

//Tamanho da tela
#define LARGURA_TELA 740
#define ALTURA_TELA 500

//variaveis globais usadas em todas as telas
ALLEGRO_FONT *fontetitulo = NULL;
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
ALLEGRO_AUDIO_STREAM *musicafundo = NULL;
//variavel global usada para fechar o programa
bool sair_programa = false;
bool musica_fundo = true;

//criação do invetario(sendo 0 um espaço dele)
bool inventario[5];

//criação da separação das telas
enum { MENU, HISTORIA, FASE_UM};
int estado_tela;

//Struct para imagens
typedef struct Obj
{
	ALLEGRO_BITMAP *bitmap;
	int x;
	int y;
	int largura;
	int altura;
} Objeto;

Objeto *seta_direita = NULL, *seta_esquerda = NULL;

#endif