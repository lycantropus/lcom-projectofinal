#include "gameBoard.h"

void drawGameBoard(int color, char* base)
{
	//drawing the vertical lines
	draw_line(firstLineCoordinate, GAP, firstLineCoordinate, lenghtSide, color, base);
	draw_line(secondLineCoordinate, GAP, secondLineCoordinate, lenghtSide, color, base);
	
	//drawing the horizontal lines
	draw_line(GAP, firstLineCoordinate, lenghtSide, firstLineCoordinate, color, base);
	draw_line(GAP, secondLineCoordinate, lenghtSide, secondLineCoordinate, color, base);
}
