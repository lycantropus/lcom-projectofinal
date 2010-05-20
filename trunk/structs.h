#ifndef _STRUCTS_H_
#define _STRUCTS_H_

#define EMPTY 0
#define CROSS 1
#define CIRCLE 2

typedef struct
{
	int x; //coordenada x central do quadrado
	int y; //coordenada y central do quadrado
	int occupation; //livre, ocupado pelo jogador um, ocupado pelo jogador 2
} Square;

typedef struct
{
	int score; //pontuação do jogador
	char name[21]; //nome
} Player;

#endif
