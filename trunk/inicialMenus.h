#ifndef _INICIALMENUS_H_
#define _INICIALMENUS_H_

#include <conio.h>
#include <string.h>
#include <stdlib.h>

#include "rtc.h"
#include "ints.h"
#include "jogo.h"
#include "queue.h"
#include "structs.h"
#include "video-graphics.h"

extern char scan;
extern _go32_dpmi_seginfo kbd_irq;
extern Player players[2];
extern Queue scanCodeQueue;
extern void scancode_isr(void);
extern char* base;
extern unsigned char table[256*CHR_H];
extern __dpmi_meminfo map;

void drawMenuBorders(char *title, int color, int back_color, char* base, unsigned char *char_table);
void namePlayer(int numberOfPlayers);
void selectMode(unsigned char *table);
void menuPrincipal(unsigned char *table);
void getPlayerName(int playerNumber);//arrays player1 and player2 ara global, so this function doesn't need to recieve them as arguments.
									  //passing an integer is faster than the array of char's
char scancodeToChar(char scancode);

#endif
