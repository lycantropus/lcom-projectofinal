#include "inicialMenus.h"

#include "pixmap.h"

Bool backSpace;

void drawMenuBorders(char *title, int color, int back_color, char* base, unsigned char *char_table) //desenha as bordas do menu com o texto
{
	int count =0;
	
	draw_line(5, 5, HRES-6, 5, color, base); //upper square line
	draw_line(6, 6, HRES-7, 6, color, base); //upper square line
	draw_line(9, 9, HRES-10, 9, color, base); //upper square line
	draw_line(10, 10, HRES-11, 10, color, base); //upper square line
	
	draw_line(HRES-6, 5, HRES-6, VRES-6, color, base); //right square line
	draw_line(HRES-7, 6, HRES-7, VRES-7, color, base); //right square line
	draw_line(HRES-10, 9, HRES-10, VRES-10, color, base); //right square line
	draw_line(HRES-11, 10, HRES-11, VRES-11, color, base); //right square line
	
	draw_line(5, VRES-6, HRES-6, VRES-6, color, base); //lower square line
	draw_line(6, VRES-7, HRES-7, VRES-7, color, base); //lower square line
	draw_line(9, VRES-10, HRES-10, VRES-10, color, base); //lower square line
	draw_line(10, VRES-11, HRES-11, VRES-11, color, base); //lower square line
	
	draw_line(5, 5, 5, VRES-6, color, base); //left square line
	draw_line(6, 6, 6, VRES-7, color, base); //left square line
	
	draw_line(9, 9, 9, VRES-10, color, base); //left square line
	draw_line(10, 10, 10, VRES-11, color, base); //left square line
	
	char*text = title;
	
	while (*text)
	{
		count++;
		text++;
	}
	
	int x = (HRES - 8* count)/2;
	
	drawStringAt(title, x, 1, color, back_color, base, char_table);
}

void namePlayer(int numberOfPlayers) //função que trata da leitura do nome de um ou de dois jogadores
{	
	char valor=0x0;
	
	clear_screen(BACKGROUNDCOLOR, base);
	drawMenuBorders("NAMES OF THE PLAYERS", WHITE, BACKGROUNDCOLOR, base, table);
	if (numberOfPlayers == 1)
	{
		drawStringAt("Player 1: ", 90, 70, NORMAL, -1, base, table);
		getPlayerName(1);
		drawStringAt("Player 2: COMPUTER", 90, 102, NORMAL, -1, base, table);
		strcpy(players[1].name, "COMPUTER");
		drawStringAt("Press Enter key to continue", 90, 134, NORMAL, -1, base, table);
		do
		{
			valor = queueGet(&scanCodeQueue);
		} while (valor != 0x1c);
	}
	else
	{
		drawStringAt("Player 1: ", 90, 70, NORMAL, -1, base, table);
		getPlayerName(1);
		drawStringAt("Player 2: ", 90, 102, NORMAL, -1, base, table);
		getPlayerName(2);
	}
	clear_screen(BACKGROUNDCOLOR, base);
}


void selectMode(unsigned char *table) //function to select screen resolution
{
	int mode=0x0; //the mode that will be chosen
	int op=-1; //the choice of the user
	char valor=0x00;
	Bool wait = false;
	scan=1;
	do 
	{
		clear_screen(BACKGROUNDCOLOR, base);
		drawMenuBorders("SCREEN AREA", WHITE, BACKGROUNDCOLOR, base, table);
		drawStringAt("1 - 640x480", 90, 70, NORMAL, -1, base, table);
		drawStringAt("2 - 800x600", 90, 86, NORMAL, -1, base, table);
		drawStringAt("3 - 1024x768", 90, 102, NORMAL, -1, base, table);
		drawStringAt("4 - 1280x1024", 90, 118, NORMAL, -1, base, table);
		drawStringAt("0 - Voltar", 90, 134, NORMAL, -1,  base, table);
		drawStringAt("Choose one of the resolutions: ", 90, 166, NORMAL, -1, base, table);
		
		do
		{
			if (scan == 1 && !wait)
			{
				valor = queueGet(&scanCodeQueue);
				scan = 0;
				if (valor==0x02||valor==0x03||valor==0x04||valor==0x05||valor==0x0b||
					valor==0x4f||valor==0x50||valor==0x51||valor==0x4b||valor==0x52)
				//scancodes of keys 1, 2, 3, 4, 0 either in alfanumeric, or numeric kyboard
				{
					if (valor==0x02 || valor==0x4f)
						op = 1;
					if (valor==0x03 || valor==0x50)
						op = 2;
					if (valor==0x04 || valor==0x51)
						op = 3;
					if (valor==0x05 || valor==0x4b)
						op = 4;
					if (valor==0x0b || valor==0x52)
						op = 0;
				}
			}
		} while (valor!=0x02&&valor!=0x03&&valor!=0x04&&valor!=0x05&&valor!=0x0b&&
				valor!=0x4f&&valor!=0x50&&valor!=0x51&&valor!=0x4b&&valor!=0x52);
	} while(op!=1 && op!=2 && op !=3 && op != 4 && op!=0);
	drawCharAt(scancodeToChar(valor), 90+31*8, 182, NORMAL, -1, base, table);
	switch(op)
	{
		case 0:	menuPrincipal(table);
				break;
		case 1: mode=0x101;
				break;
		case 2: mode=0x103;
				break;
		case 3: mode=0x105;
				break;
		case 4: mode=0x107;
				break;
	}
	
	if (mode != 0x0)
	{
		base = enter_graphics(mode, &map);
		menuPrincipal(table);
	}
}


void menuPrincipal(unsigned char *table)   //menu principal do programa
{	
	int op=0;
	inicializar_tabuleiro();
	clear_screen(BACKGROUNDCOLOR, base);
	drawMenuBorders("Jogo do Galo", WHITE, BACKGROUNDCOLOR, base, table);
	drawStringAt("1 - Single Player", 90, 70, NORMAL, -1, base, table);
	drawStringAt("2 - Multyplayer", 90, 86, NORMAL, -1, base, table);
	drawStringAt("3 - Change Resolution", 90, 102, NORMAL, -1, base, table);
	drawStringAt("4 - Exit", 90, 118, NORMAL, -1, base, table);
	drawStringAt("Choose one option: ", 90, 150, NORMAL, -1, base, table);
	
	players[0].score=0;
	players[1].score=0;
	
	char valor=0x00;
	Bool wait = false;
	
	do
	{
		if (scan == 1 && !wait)
		{
			valor = queueGet(&scanCodeQueue);
			scan = 0;
			
			if (valor==0x02||valor==0x03||valor==0x04||valor==0x05||valor==0x4f||valor==0x50||valor==0x51||valor==0x4b)
			//scancodes of keys 1, 2, 3, 4 either in alfanumeric, or numeric kyboard
			{
				if (valor==0x02 || valor==0x4f)
					op = 1;
				if (valor==0x03 || valor==0x50)
					op = 2;
				if (valor==0x04 || valor==0x51)
					op = 3;
				if (valor==0x05 || valor==0x4b)
					op = 4;
			}
		}
	} while (valor==0x0);
	drawCharAt(scancodeToChar(valor), 90+19*8, 150, NORMAL, -1, base, table);
	
	ping = create_sprite(penguin);
	dart = create_sprite(dartacao);
	int end = 1;
	int actualPlayer=0;
	switch(op)
	{
		case 1:
				makeEmpty(&scanCodeQueue);
				namePlayer(1); //pede o nome do jogador
				end = 1;
				actualPlayer=0; //save the player that begun the last match
				do
				{
					actualPlayer=1-actualPlayer;//change the first player to move
					end = singlePlayer(dart, ping, actualPlayer);
				} while (end==1);
				menuPrincipal(table);
				break;
		case 2:
				makeEmpty(&scanCodeQueue);
				namePlayer(2);  //pede o nome dos jogadores
				end = 1;
				actualPlayer=0;//save the player that begun the last match
				do
				{
					actualPlayer=1-actualPlayer;//change the first player to move
					end = multiPlayer(dart, ping, actualPlayer);
				} while (end==1);
				menuPrincipal(table);
				break;
		case 3:
				makeEmpty(&scanCodeQueue);
				selectMode(table);  //entra no menu de alteração de modo grafico
				break;
		case 4:	
				reinstall_asm_irq_handler(KBD_IRQ, &kbd_irq);
				rtcEnd();
				stop_noteRTC();
				exit(0); //sair
				break;
		default:
				makeEmpty(&scanCodeQueue);
				menuPrincipal(table);  //volta a aparecer o menu principal
				break;
	}
	
}

void getPlayerName(int playerNumber) //ler o nome do jogador do teclado
{ 
	
	queueInit(&scanCodeQueue);
	
	char valor;
	Bool wait = false;
	int xToWrite=90+10*8; //x coordinate to write the player's name
	
	int nameIndex=0;
	do
	{
		if (scan == 1 && !wait)
		{
			valor = queueGet(&scanCodeQueue);
			scan = 0;
			
			if (valor > 0 && nameIndex<=19)
			{
				if (valor==0x1c && playerNumber==1) //if enter key was pressed, force the name to be completed
				{
					players[0].name[nameIndex]='\0';
					nameIndex=20;
					break;
				}
				if (valor==0x1c && playerNumber==2) //if enter key was pressed, force the name to be completed
				{
					players[1].name[nameIndex]='\0';
					nameIndex=20;
					break;
				}
				if (playerNumber==1)
				{
					if (scancodeToChar(valor)!=NULL)
					{
						players[0].name[nameIndex]=scancodeToChar(valor);
						drawCharAt(players[0].name[nameIndex], xToWrite, 70, NORMAL, -1, base, table);
						xToWrite+=8;
						nameIndex++;
					}
					else
					{
						if(backSpace == true && players[0].name[0]!=NULL) //if the user pressed the backSpace key
						{ 
							xToWrite-=8;
							//print a space char in the place of the deleted char, with the color of the backgound, so the deleted char will disapear
							drawCharAt(' ', xToWrite, 70, BACKGROUNDCOLOR, BACKGROUNDCOLOR, base, table);
							nameIndex--;
							players[0].name[nameIndex]=NULL;
							backSpace=false;
						}
					}
				}
				else
				{
					if (scancodeToChar(valor)!=NULL)
					{
						players[1].name[nameIndex]=scancodeToChar(valor);
						drawCharAt(players[1].name[nameIndex], xToWrite, 102, NORMAL, -1, base, table);
						xToWrite+=8;
						nameIndex++;
					}
					else
					{
						if(backSpace == true && players[1].name[0]!=NULL) //if the user pressed the backSpace key
						{ 
							xToWrite-=8;
							//print a space char in the place of the deleted char, with the color of the backgound, so the deleted char will disapear
							drawCharAt(' ', xToWrite, 70, BACKGROUNDCOLOR, BACKGROUNDCOLOR, base, table);
							nameIndex--;
							players[1].name[nameIndex]=NULL;
							backSpace=false;
						}
					}
				}
			}
			if (nameIndex==20 && playerNumber==1)
			{
				drawStringAt("MAXIMO ATINGIDO", 90, 86, NORMAL, -1, base, table);
				drawStringAt("Press Enter key to continue", 90, 102, NORMAL, -1, base, table);
				do
				{
					valor = queueGet(&scanCodeQueue);
				} while (valor != 0x1c);
				//imprimir o que foi escrito com a  cor de fundo para 'apagar' o que esta escrito a mais
				drawStringAt("MAXIMO ATINGIDO", 90, 86, BACKGROUNDCOLOR, -1, base, table);
				drawStringAt("Press Enter key to continue", 90, 102, BACKGROUNDCOLOR, -1, base, table);	
				if (playerNumber==1) players[0].name[20]='\0'; else players[1].name[20]='\0';
				valor=1;//forcing the do while cicle to end
				break;
			}
			if (nameIndex==20 && playerNumber==2)
			{
				drawStringAt("MAXIMO ATINGIDO", 90, 118, NORMAL, -1, base, table);
				drawStringAt("Press Enter key to continue", 90, 134, NORMAL, -1, base, table);
				do
				{
					valor = queueGet(&scanCodeQueue);
				} while (valor != 0x1c);
				//imprimir o que foi escrito com a  cor de fundo para 'apagar' o que esta escrito a mais
				drawStringAt("MAXIMO ATINGIDO", 90, 118, BACKGROUNDCOLOR, -1, base, table);
				drawStringAt("Press Enter key to continue", 90, 134, BACKGROUNDCOLOR, -1, base, table);
				if (playerNumber==1) players[0].name[20]='\0'; else players[1].name[20]='\0';
				valor=1;//forcing the do while cicle to end
				break;
			}
		}	
	}
	while (valor != 0x1c); //tecla diferente de enter
}

char scancodeToChar(char scancode)  //verifika o valor char do scancode
{
	char character;
	if (scancode == 0x0e)
	{
		backSpace=true;
		return NULL;
	}
	if (scancode == 0x10)
		return character='Q';
	if (scancode == 0x11)
		return character='W';
	if (scancode == 0x12)
		return character='E';
	if (scancode == 0x13)
		return character='R';
	if (scancode == 0x14)
		return character='T';
	if (scancode == 0x15)
		return character='Y';
	if (scancode == 0x16)
		return character='U';
	if (scancode == 0x17)
		return character='I';
	if (scancode == 0x18)
		return character='O';
	if (scancode == 0x19)
		return character='P';
//
	if (scancode == 0x1e)
		return character='A';
	if (scancode == 0x1f)
		return character='S';
	if (scancode == 0x20)
		return character='D';
	if (scancode == 0x21)
		return character='F';
	if (scancode == 0x22)
		return character='G';
	if (scancode == 0x23)
		return character='H';
	if (scancode == 0x24)
		return character='J';
	if (scancode == 0x25)
		return character='K';
	if (scancode == 0x26)
		return character='L';
	if (scancode == 0x27)
		return character='Ç';
//	
	if (scancode == 0x2c)
		return character='Z';
	if (scancode == 0x2d)
		return character='X';
	if (scancode == 0x2e)
		return character='C';
	if (scancode == 0x2f)
		return character='V';
	if (scancode == 0x30)
		return character='B';
	if (scancode == 0x31)
		return character='N';
	if (scancode == 0x32)
		return character='M';
//
	if (scancode == 0x02 || scancode == 0x4f)
		return character='1';
	if (scancode == 0x03 || scancode == 0x50)
		return character='2';
	if (scancode == 0x04 || scancode == 0x51)
		return character='3';
	if (scancode == 0x05 || scancode == 0x4b)
		return character='4';
	if (scancode == 0x06 || scancode == 0x4c)
		return character='5';
	if (scancode == 0x07 || scancode == 0x4d)
		return character='6';
	if (scancode == 0x08 || scancode == 0x47)
		return character='7';
	if (scancode == 0x09 || scancode == 0x48)
		return character='8';
	if (scancode == 0x0a || scancode == 0x49)
		return character='9';
	if (scancode == 0x0b || scancode == 0x52)
		return character='0';
	
	return NULL;
}
