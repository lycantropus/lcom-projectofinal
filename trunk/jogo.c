#include "jogo.h"

void inicializar_occupations() //mete que todas as posições do tabuleiro estão livres
{
	int i = 0;
	for (; i< 9; i++)  //define que as posições todas do tabuleiro tão limpas
		board[i].occupation = 0;
}

void inicializar_tabuleiro() //inicia as posições do tabuleiro
{
	inicializar_occupations();
	
	int i = 0;
    int valueX = firstCenterXY;
    for (; i<3; i++)   //define as coordenadas x centrais dos quadrados
    {
        board[i].x = valueX;
        board[i+3].x = valueX;
        board[i+6].x = valueX;
        valueX += sumPosicion;
    }    
    
    int valueY = firstCenterXY;
	i =  0;
	for (; i<7; )   //define as coordenadas y centrais dos quadrados
    {
        board[i].y = valueY;
        board[i+1].y = valueY;
        board[i+2].y = valueY;
        valueY += sumPosicion;
        i += 3;
    } 
}

void refresh_tabuleiro(Sprite *fig1, Sprite *fig2)  //vai fazer refresh das posições ja jogadas no tabuleiro, fazendo aparecer a respectiva imagem
{
    if (board[0].occupation == 1) draw_sprite(fig1, base, board[0].x, board[0].y);
    else if (board[0].occupation == 2) draw_sprite(fig2, base, board[0].x, board[0].y);
   
    if (board[1].occupation == 1) draw_sprite(fig1, base, board[1].x, board[1].y);
    else if (board[1].occupation == 2) draw_sprite(fig2, base, board[1].x, board[1].y);
    
    if (board[2].occupation == 1) draw_sprite(fig1, base, board[2].x, board[2].y);
    else if (board[2].occupation == 2) draw_sprite(fig2, base, board[2].x, board[2].y);
    
    if (board[3].occupation == 1) draw_sprite(fig1, base, board[3].x, board[3].y);
    else if (board[3].occupation == 2) draw_sprite(fig2, base, board[3].x, board[3].y);
    
    if (board[4].occupation == 1) draw_sprite(fig1, base, board[4].x, board[4].y);
    else if (board[4].occupation == 2) draw_sprite(fig2, base, board[4].x, board[4].y);
    
    if (board[5].occupation == 1) draw_sprite(fig1, base, board[5].x, board[5].y);
    else if (board[5].occupation == 2) draw_sprite(fig2, base, board[5].x, board[5].y);
    
    if (board[6].occupation == 1) draw_sprite(fig1, base, board[6].x, board[6].y);
    else if (board[6].occupation == 2) draw_sprite(fig2, base, board[6].x, board[6].y);
    
    if (board[7].occupation == 1) draw_sprite(fig1, base, board[7].x, board[7].y);
    else if (board[7].occupation == 2) draw_sprite(fig2, base, board[7].x, board[7].y);
    
    if (board[8].occupation == 1) draw_sprite(fig1, base, board[8].x, board[8].y);
    else if (board[8].occupation == 2) draw_sprite(fig2, base, board[8].x, board[8].y);
}

int checks()  //vai verificar o estado do jogo, returna: 1- Winner 1; 2- Winner 2; 0- Draw; -1 not finished;
{
	int count = 0;
    if (board[0].occupation == board[3].occupation && board[3].occupation == board[6].occupation && board[6].occupation != 0)
        return board[0].occupation;
    else if (board[1].occupation == board[4].occupation && board[4].occupation == board[7].occupation && board[7].occupation != 0)
        return board[1].occupation;
    else if (board[2].occupation == board[5].occupation && board[5].occupation == board[8].occupation && board[8].occupation != 0)
        return board[2].occupation;
    else if (board[0].occupation == board[1].occupation && board[1].occupation == board[2].occupation && board[2].occupation != 0)
        return board[0].occupation;
    else if (board[3].occupation == board[4].occupation && board[4].occupation == board[5].occupation && board[5].occupation != 0)
        return board[3].occupation;
    else if (board[6].occupation == board[7].occupation && board[7].occupation == board[8].occupation && board[8].occupation != 0)
        return board[6].occupation;
    else if (board[0].occupation == board[4].occupation && board[4].occupation == board[8].occupation && board[8].occupation != 0)
        return board[0].occupation;
    else if (board[2].occupation == board[4].occupation && board[4].occupation == board[6].occupation && board[6].occupation != 0)
        return board[2].occupation;
	else
	{
		int i=0;
		for (; i < 9; i++)   //verfifika aqui se as posições ja tão todas ocupadas
		{
			if (board[i].occupation != 0)  
				count ++;
		}
		if (count == 9)
			return 0;
	}		
	return -1;
}

int playComputer() //IA do jogo implementada... Por agora esta isto, depois eu implemento melhor...
{
	if (board[4].occupation == 0)  //joga na posição inicial se tiver livre
	{
		board[4].occupation = 2;
		return 0;
	}
	
	//Verificação da possibilidade de ganhar - daki pra baixo até aviso do contrário
	
	//verifica se consegue ganhar para as possibilidades na horizontal
	int i=0;
	while(i<9)
	{
    	if(board[i].occupation == board[i+2].occupation && board[i+1].occupation == 0 && board[i].occupation == 2)
    	{
    	    board[i+1].occupation = 2;
    	    return 0;
    	}
    	else if (board[i].occupation == board[i+1].occupation && board[i+2].occupation == 0 && board[i].occupation == 2)
    	{
    	    board[i+2].occupation = 2;
    	    return 0;
    	}
        else if (board[i+1].occupation == board[i+2].occupation && board[i].occupation == 0 && board[i+2].occupation == 2)
        {
            board[i].occupation = 2;
            return 0;
        }
        i = i+3;
    }
    
    //verifica se consegue ganhar para as possibilidades na vertical
	i = 0;
	while (i<3)
    {
        if(board[i].occupation == board[i+6].occupation && board[i+3].occupation == 0 && board[i].occupation == 2)
    	{
    	    board[i+3].occupation = 2;
    	    return 0;
    	}
    	else if (board[i].occupation == board[i+3].occupation && board[i+6].occupation == 0 && board[i].occupation == 2)
    	{
    	    board[i+6].occupation = 2;
    	    return 0;
    	}
        else if (board[i+3].occupation == board[i+6].occupation && board[i].occupation == 0 && board[i+3].occupation == 2)
        {
            board[i].occupation = 2;
            return 0;
        }
        i = i+1;
    }
    
    //verifica se consegue ganhar na diagonal principal
    if(board[0].occupation == board[4].occupation && board[8].occupation == 0 && board[0].occupation == 2)
    {
        board[8].occupation = 2;
        return 0;
    }
    else if(board[0].occupation == board[8].occupation && board[4].occupation == 0 && board[0].occupation == 2)
    {
        board[4].occupation = 2;
        return 0;
    }
    else if(board[4].occupation == board[8].occupation && board[0].occupation == 0 && board[4].occupation == 2)
    {
        board[0].occupation = 2;
        return 0;
    }
    
    //verifica se consegue ganhar na diagonal secundária
    if(board[2].occupation == board[4].occupation && board[6].occupation == 0 && board[2].occupation == 2)
    {
        board[6].occupation = 2;
        return 0;
    }
    else if(board[2].occupation == board[6].occupation && board[4].occupation == 0 && board[2].occupation == 2)
    {
        board[4].occupation = 2;
        return 0;
    }
    else if(board[4].occupation == board[6].occupation && board[2].occupation == 0 && board[4].occupation == 2)
    {
        board[2].occupation = 2;
        return 0;
    }
	
	//Tratamento dos casos de defesa - daki pra baixo até sinal do contrário
    
    //verifica se o adversario consegue ganhar para as possibilidades na horizontal e bloqueia o adversário
	i = 0;
	while (i<9)
	{
    	if(board[i].occupation == board[i+2].occupation && board[i+1].occupation == 0 && board[i].occupation == 1)
    	{
    	    board[i+1].occupation = 2;
    	    return 0;
    	}
    	else if (board[i].occupation == board[i+1].occupation && board[i+2].occupation == 0 && board[i].occupation == 1)
    	{
    	    board[i+2].occupation = 2;
    	    return 0;
    	}
        else if (board[i+1].occupation == board[i+2].occupation && board[i].occupation == 0 && board[i+2].occupation == 1)
        {
            board[i].occupation = 2;
            return 0;
        }
        i = i+3;
    }
    
    //verifica se o adversario consegue ganhar para as possibilidades na vertical e bloqueia o adversário
	i = 0;
	while (i<3)
    {
        if(board[i].occupation == board[i+6].occupation && board[i+3].occupation == 0 && board[i].occupation == 1)
    	{
    	    board[i+3].occupation = 2;
    	    return 0;
    	}
    	else if (board[i].occupation == board[i+3].occupation && board[i+6].occupation == 0 && board[i].occupation == 1)
    	{
    	    board[i+6].occupation = 2;
    	    return 0;
    	}
        else if (board[i+3].occupation == board[i+6].occupation && board[i].occupation == 0 && board[i+3].occupation == 1)
        {
            board[i].occupation = 2;
            return 0;
        }
        i = i+1;
    }
       
    //verifica se o adversário consegue criar duplas possiblidades de vitória e bloqueias antes k seja tarde - daki pra baixo verifica diferentes casos
    //até aviso contrário
    if (board[1].occupation == board[6].occupation && board[1].occupation == 1 && board[0].occupation == 0)
    {
        board[0].occupation = 2;
        return 0;
    } 
    else if (board[1].occupation == board[8].occupation && board[1].occupation == 1 && board[2].occupation == 0) 
    {
        board[2].occupation = 2;
        return 0;
    }
    else if (board[0].occupation == board[7].occupation && board[0].occupation == 1 && board[6].occupation == 0) 
    {
        board[6].occupation = 2;
        return 0;
    }
    else if (board[2].occupation == board[7].occupation && board[2].occupation == 1 && board[8].occupation == 0) 
    {
        board[8].occupation = 2;
        return 0;
    }
    else if (board[2].occupation == board[3].occupation && board[2].occupation == 1 && board[0].occupation == 0) 
    {
        board[0].occupation = 2;
        return 0;
    }
    else if (board[3].occupation == board[8].occupation && board[3].occupation == 1 && board[6].occupation == 0) 
    {
        board[6].occupation = 2;
        return 0;
    }
    else if (board[0].occupation == board[5].occupation && board[0].occupation == 1 && board[2].occupation == 0) 
    {
        board[2].occupation = 2;
        return 0;
    }
    else if (board[5].occupation == board[6].occupation && board[5].occupation == 1 && board[8].occupation == 0) 
    {
        board[8].occupation = 2;
        return 0;
    }
    else if (board[0].occupation == board[8].occupation && board[0].occupation == 1) 
    {
        if (board[2].occupation == 0)
        {
            board[2].occupation = 2;
            return 0;
        }
        else if (board[6].occupation == 0)
        {
            board[6].occupation = 2;
            return 0;
        }
    }
     else if (board[2].occupation == board[6].occupation && board[2].occupation == 1) 
    {
        if (board[0].occupation == 0)
        {
            board[0].occupation = 2;
            return 0;
        }
        else if (board[8].occupation == 0)
        {
            board[8].occupation = 2;
            return 0;
        }
    }
	else if (board[1].occupation == board[5].occupation && board[1].occupation == 1 && board[2].occupation == 0) 
    {
        board[2].occupation = 2;
        return 0;
    }
	else if (board[1].occupation == board[3].occupation && board[1].occupation == 1 && board[0].occupation == 0) 
    {
        board[0].occupation = 2;
        return 0;
    }
	else if (board[5].occupation == board[7].occupation && board[5].occupation == 1 && board[8].occupation == 0) 
    {
        board[8].occupation = 2;
        return 0;
    }
	else if (board[3].occupation == board[7].occupation && board[3].occupation == 1 && board[6].occupation == 0) 
    {
        board[6].occupation = 2;
        return 0;
    }
	
	//Computador inicia o ataque pra tentar ganhar o jogo  
	
	if (board[4].occupation == 2 && board[0].occupation == 0 && board[8].occupation == 0)
	{
		board[0].occupation = 2;
		return 0;
	}
	else if (board[4].occupation == 2 && board[2].occupation == 0 && board[6].occupation == 0)
	{
		board[2].occupation = 2;
		return 0;
	}
	else if (board[0].occupation == 2 && board[4].occupation == 2)
	{
		if (board[1].occupation == 0 && board[2].occupation == 0 && board[7].occupation == 0)
		{
			board[1].occupation = 2;
			return 0;
		}
		else if (board[2].occupation == 0 && board[1].occupation == 0 && board[6].occupation == 0)
		{
			board[2].occupation = 2;
			return 0;
		}
		else if (board[3].occupation == 0 && board[5].occupation == 0 && board[6].occupation == 0)
		{
			board[3].occupation = 2;
			return 0;
		}
		else if (board[6].occupation == 0 && board[3].occupation == 0 && board[2].occupation == 0)
		{
			board[6].occupation = 2;
			return 0;
		}
	}
	else if (board[2].occupation == 2 && board[4].occupation == 2)
	{
		if (board[0].occupation == 0 && board[1].occupation == 0 && board[8].occupation == 0)
		{
			board[0].occupation = 2;
			return 0;
		}
		else if (board[1].occupation == 0 && board[0].occupation == 0 && board[7].occupation == 0)
		{
			board[1].occupation = 2;
			return 0;
		}
		else if (board[5].occupation == 0 && board[3].occupation == 0 && board[8].occupation == 0)
		{
			board[5].occupation = 2;
			return 0;
		}
		else if (board[8].occupation == 0 && board[0].occupation == 0 && board[5].occupation == 0)
		{
			board[8].occupation = 2;
			return 0;
		}
	}
	
	//se ja ñ houver possiblidade de vitória, e o empate for a unica solução, ocupa uma das restantes casas ainda vazias
	i = 0;
	for (; i < 9; i++)
	{
		if (board[i].occupation == 0)
		{
			board[i].occupation = 2;
			return 0;
		}
	}
	return -1; //nunka deve acontecer isto
}
	

int analysing(Sprite *fig, int x, int y, int player)  //verifika o qudranate do clique do rato e desenha la a respectiva imagem 
                                                        //retorna true se fez o planeado, false se a posição ja tiver ocupada e -1 se ñ tiver sido klicado um pixel valido
{
    int i;
	if (x > GAP && x < lenghtSide && y > GAP && y < lenghtSide)  //verifika se as coordenadas estão dentro do tabuleiro
	{
		if (x < firstLineCoordinate)    //verifika se esta dentro da coluna 1
		{
			i = 0;
		}
		else if (x > firstLineCoordinate && x < secondLineCoordinate) //verifika se esta dentro da coluna 2
		{
			i = 1;
		}
		else if (x > secondLineCoordinate)  //verifika se esta dentro da coluna 3
		{
			i = 2;
		}
		else
		{
			//linha neutra vertical
			return -1;
		}
		
		if(y < firstLineCoordinate); //verifika se esta dentro da linha 1
		else if (y > firstLineCoordinate && y < secondLineCoordinate) //verifika se esta dentro da linha 2
		{
		    i = i + 3;
		}
		else if (y > secondLineCoordinate)  // verifika se esta dentro da linha 3
		{
		    i = i + 6;
		}
		else 
		{
              //linha neutra horizontal
              return -1;
		}	
	}
	else 
	{
		//fora do tabuleiro
		return -1;
	}
	
	// se nada for retonada com -1 verifica se consegue desenhar o simbolo
	
	if (board[i].occupation == 0)
    {
        draw_sprite(fig, base, board[i].x, board[i].y);  //desenha o simbolo da posição
        board[i].occupation = player;   //declara que akela posição foi ocupada
    }
    else return false;  //retorna false se a posição ja tiver ocupada
	
	return true;
}

void paint() // função que imprime as das linhas do tabuleiro e afins
{	
	drawScreenBorder(WHITE, base);
	drawTimerBorder(LEFTX(HRES), LEFTY, RIGHTX(HRES), RIGHTY(HRES), BORDERTHICKNESS(HRES), YELLOW, base);
	drawGameBoard(YELLOW, base);
}

int singlePlayer(Sprite* dart, Sprite* ping, int firstPlayer)
{
	clear_screen(BACKGROUNDCOLOR, base);
	
	int end = -1;
	rtc_update=0;
	
	inicializar_occupations();
	
	paint();
	while (rtc_update<= 15 && end == -1)
	{
		//pc moves
		//pc is playe number 2
		if (firstPlayer==1)
		{
			end=processComputerMove();
			if (end==-1)//if the game doesnt reach a final state with the previou's move
			{	
				end=processHumanMove(dart, 0);
			}
		}
		if (firstPlayer==0)
		{
			end=processHumanMove(dart, 0);
			if (end==-1)//if the game doesnt reach a final state with the previous's move
			{	
				end=processComputerMove();
			}
		}
	}
	makeEmpty(&scanCodeQueue);
	char valor=0x00;
	drawStringAt("press enter key", VRES+GAP,  VRES-10*GAP, WHITE, BACKGROUNDCOLOR, base, table);
	do 
	{
		valor = queueGet(&scanCodeQueue);
	} while (valor != 0x1c); //wait for enter key
	
	clear_screen(BACKGROUNDCOLOR, base);
	drawMenuBorders("Game ScoreGame Score", WHITE, BACKGROUNDCOLOR, base, table);
	if (end == 2)
	{
		drawStringAt("COMPUTER WINS", 90, 70, NORMAL, -1, base, table);   //isto depois vai aparecr como um menu, dando os resultados e a possibilidade de começar novo jogo
		players[1].score++;
	}
	else if (end == 1)
	{
		drawStringAt("YOU WIN", 90, 70, NORMAL, -1, base, table);
		players[0].score++;
	}
	else drawStringAt("DRAW", 90, 70, NORMAL, -1, base, table);
	
	char score1[3];
	char score2[3];
	itoa(players[0].score, score1, 10);
	itoa(players[1].score, score2, 10);
	//player1
	drawStringAt(players[0].name, 90, 86, NORMAL, -1, base, table);
	drawStringAt(score1, 90+strlen(players[0].name)*8+8, 86, NORMAL, -1, base, table);
	//player2
	drawStringAt(players[1].name, 90, 102, NORMAL, -1, base, table);
	drawStringAt(score2, 162, 102, NORMAL, -1, base, table);
	drawStringAt("Deseja Continuar o jogo?", 90, 134, NORMAL, -1, base, table);
	drawStringAt("1 - Sim", 90, 150, NORMAL, -1, base, table);
	drawStringAt("2 - Nao", 90, 166, NORMAL, -1,  base, table);
	drawStringAt("Choose one of the options: ", 90, 182, NORMAL, -1, base, table);
	
	int op = 0;
	makeEmpty(&scanCodeQueue);
	valor = 0x00;
	do
	{
		if (scan == 1)
		{
			valor = queueGet(&scanCodeQueue);
			scan = 0;
			
			if (valor==0x02||valor==0x03||valor==0x4f||valor==0x50)
			//scancodes of keys 1, 2, either in alfanumeric, or numeric kyboard
			{
				if (valor==0x02 || valor==0x4f)
					op = 1;
				if (valor==0x03 || valor==0x50)
					op = 2;
			}
		}
	} while (valor!=0x02&&valor!=0x03&&valor!=0x4f&&valor!=0x50);
	
	return op;
}

int multiPlayer(Sprite* dart, Sprite* ping, int firstPlayer) //firstPlayer= 1 ou 2
{
	clear_screen(BACKGROUNDCOLOR, base);
	
	int end = -1;
	rtc_update=0;

	inicializar_occupations();
	
	paint();
	
	while (rtc_update<= 15 && end == -1)
	{
		if (firstPlayer==1)
		{
			end=processHumanMove(dart, 0); //first player to move
			if (end==-1)//if the game doesnt reach a final state with the previou's move
			{	
				end=processHumanMove(ping, 1);
			}
		}
		if (firstPlayer==0)
		{
			end=processHumanMove(ping, 1); //first player to move
			if (end==-1)//if the game doesnt reach a final state with the previous's move
			{	
				end=processHumanMove(dart, 0);
			}
		}
	}
	//by this time, the game is already finished (end!=-1)
	makeEmpty(&scanCodeQueue);
	char valor=0x00;
	drawStringAt("press enter key", VRES+GAP,  VRES-10*GAP, WHITE, BACKGROUNDCOLOR, base, table);
	do
	{
		valor = queueGet(&scanCodeQueue);
	} while (valor != 0x1c); //wait for enter key
	
	clear_screen(BACKGROUNDCOLOR, base);
	drawMenuBorders("Game Score", WHITE, BACKGROUNDCOLOR, base, table);
	if (end == 2)
	{
		drawStringAt(players[1].name, 90, 70, NORMAL, -1, base, table);   //isto depois vai aparecr como um menu, dando os resultados e a possibilidade de começar novo jogo
		players[1].score++;
	}
	else if (end == 1)
	{
		drawStringAt(players[0].name, 90, 70, NORMAL, -1, base, table);
		players[0].score++;
	}
	else drawStringAt("DRAW", 90, 70, NORMAL, -1, base, table);
	
	char score1[3];
	char score2[3];
	itoa(players[0].score, score1, 10);
	itoa(players[1].score, score2, 10);
	//player1
	drawStringAt(players[0].name, 90, 86, NORMAL, -1, base, table);
	drawStringAt(score1, 90+strlen(players[0].name)*8+8, 86, NORMAL, -1, base, table);
	//player2
	drawStringAt(players[1].name, 90, 102, NORMAL, -1, base, table);
	drawStringAt(score2, 90+strlen(players[1].name)*8+8, 102, NORMAL, -1, base, table);
	drawStringAt("Deseja Continuar o jogo?", 90, 134, NORMAL, -1, base, table);
	drawStringAt("1 - Sim", 90, 150, NORMAL, -1, base, table);
	drawStringAt("2 - Nao", 90, 166, NORMAL, -1,  base, table);
	drawStringAt("Choose one of the options: ", 90, 182, NORMAL, -1, base, table);
	
	int op = 0;
	makeEmpty(&scanCodeQueue);
	valor = 0x00;
	do
	{
		if (scan == 1)
		{
			valor = queueGet(&scanCodeQueue);
			scan = 0;
			
			if (valor==0x02||valor==0x03||valor==0x4f||valor==0x50)
			//scancodes of keys 1, 2, either in alfanumeric, or numeric kyboard
			{
				if (valor==0x02 || valor==0x4f)
					op = 1;
				if (valor==0x03 || valor==0x50)
					op = 2;
			}
		}
	} while (valor!=0x02&&valor!=0x03&&valor!=0x4f&&valor!=0x50);
	
	return op;
}

int processComputerMove()
{
	drawStringAt("COMPUTER", lenghtSide + 4*GAP, VRES-6*GAP, NORMAL, -1, base, table);
	playComputer();
	refresh_tabuleiro(dart, ping);
	drawStringAt("COMPUTER", lenghtSide + 4*GAP, VRES-6*GAP, BACKGROUNDCOLOR, BACKGROUNDCOLOR, base, table);
	return checks();
}

int processHumanMove(Sprite* fig, int player)
{
	int lastRtc=0;
	int x, y;
	char chosenPosition;
	
	draw_sprite(fig, base, VRES+(HRES-VRES)/2, VRES/2);
	drawStringAt(players[player].name, lenghtSide + 4*GAP, VRES-6*GAP, NORMAL, -1, base, table);
	rtc_update=0;
	makeEmpty(&scanCodeQueue);
	chosenPosition=NULL;
	//codigo para obter a posicao em que se joga
	do
	{
		lastRtc=rtc_update; //lastRtc is used in order not to draw different numbers in the calls to drawNumber below. it can happen if a rtc update interrupt ocours while drawing
		drawWatch(lastRtc);
		//aqui devia entrar o rato
		chosenPosition=scancodeToChar(queueGet(&scanCodeQueue)); //funcao scancode to char AINDA nao tem os numeros todos
	}while(chosenPosition==NULL && rtc_update<=15);
	//entradas provisorias pelo teclado porque ñ conseguimos por o rato a dar
	if (chosenPosition=='1')
	{
		x=firstLineCoordinate/2;
		y=firstLineCoordinate/2;
	}
	else if (chosenPosition=='2')
	{
		x=3*firstLineCoordinate/2;
		y=firstLineCoordinate/2;
	}
	else if (chosenPosition=='3')
	{
		x=5*firstLineCoordinate/2;
		y=firstLineCoordinate/2;
	}
	else if (chosenPosition=='4')
	{
		x=firstLineCoordinate/2;
		y=3*firstLineCoordinate/2;                                  
	}
	else if (chosenPosition=='5')
	{
		x=3*firstLineCoordinate/2;
		y=3*firstLineCoordinate/2;
	}
	else if (chosenPosition=='6')
	{
		x=5*firstLineCoordinate/2;
		y=3*firstLineCoordinate/2;
	}
	else if (chosenPosition=='7')
	{
		x=firstLineCoordinate/2;
		y=5*firstLineCoordinate/2;
	}
	else if (chosenPosition=='8')
	{
		x=3*firstLineCoordinate/2;
		y=5*firstLineCoordinate/2;
	}
	else if (chosenPosition=='9')
	{
		x=5*firstLineCoordinate/2;
		y=5*firstLineCoordinate/2;
	}
	if (rtc_update <= 15)
		if (analysing(fig, x, y, player+1)==0) //if the move is in an non free position
			return processHumanMove(fig, player);
	if (rtc_update>15)
	{
		return 2;
	}
	else
	{
		drawStringAt(players[player].name, lenghtSide + 4*GAP, VRES-6*GAP, BACKGROUNDCOLOR, BACKGROUNDCOLOR, base, table);
		return checks();
	}
}
