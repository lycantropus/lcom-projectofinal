#ifndef _JOGO_H_
#define _JOGO_H_

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#include "gameBoard.h"
#include "playTimeCounter.h"
#include "queue.h"
#include "sprite.h"
#include "screenBorder.h"
#include "structs.h"
#include "inicialMenus.h"

extern Square board[9];
extern char* base;
extern unsigned char table[256*CHR_H];
extern Player players[2];
extern Queue scanCodeQueue;
extern char scan;

void inicializar_occupations();  //mete as ocupações do tabuleiro todas vazias

void inicializar_tabuleiro(); //inicia as posições do tabuleiro

void refresh_tabuleiro(Sprite *fig1, Sprite *fig2);  //vai fazer refresh das posições ja jogadas no tabuleiro, fazendo aparecer a respectiva imagem

int checks();  //vai verificar o estado do jogo, returna: 1- Winner 1; 2- Winner 2; 0- Draw; -1 not finished;

int playComputer(); //IA do jogo implementada... Por agora esta isto, depois eu implemento melhor...
	
int analysing(Sprite *fig, int x, int y, int player);  //verifika o qudranate do clique do rato e desenha la a respectiva imagem 
                                                        //retorna true se fez o planeado, false se a posição ja tiver ocupada e -1 se ñ tiver sido klicado um pixel valido

void paint(); // função que imprime as linhas do tabuleiro e afins

int multiPlayer(Sprite* dart, Sprite* ping, int firstPlayer);

int singlePlayer(Sprite* dart, Sprite* ping, int firstPlayer);

int processComputerMove();

int processHumanMove(Sprite* fig, int player);

#endif
