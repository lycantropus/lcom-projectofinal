#include <conio.h>
#include <ctype.h>
#include <dos.h>
#include <dpmi.h>
#include <go32.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inicialMenus.h"
#include "ints.h"
#include "rtc.h"
#include "structs.h"
#include "video-graphics.h"

Player players[2]; //struct representating the players
Square board[9]; //struct representing the game board

char scan = 0;
Queue scanCodeQueue; //queue where the scancodes of the pressed keys will de kept
void scancode_isr(void); //keyboard interrupt handler

char* base;
__dpmi_meminfo map;
_go32_dpmi_seginfo kbd_irq;
_go32_dpmi_seginfo mouse_irq;
unsigned char table[256*CHR_H];

int main()
{
	rtcBegin();
	LoadSong();
	queueInit(&scanCodeQueue);
	install_asm_irq_handler(MOUSE_IRQ, scancode_isr, &mouse_irq);
	install_asm_irq_handler(KBD_IRQ, scancode_isr, &kbd_irq);
	
	int mode = 0x103;
	base = enter_graphics(mode, &map);
	
	charTable(table);
	inicializar_tabuleiro();
	menuPrincipal(table);
	
	
	reinstall_asm_irq_handler(MOUSE_IRQ, &mouse_irq);
	reinstall_asm_irq_handler(KBD_IRQ, &kbd_irq);
	leave_graphics(map);
	rtcEnd();
	stop_noteRTC();
	return 0;
}


