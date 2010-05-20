#include "screenBorder.h"

void drawScreenBorder(int color, char *base)
{
	//square
    draw_line(GAP, GAP, lenghtSide, GAP, color, base); //upper square line
	draw_line(lenghtSide, GAP, lenghtSide, lenghtSide, color, base); //right square line
	draw_line(lenghtSide, lenghtSide, GAP, lenghtSide, color, base); //lower square line
	draw_line(GAP, lenghtSide, GAP, GAP, color, base); //left square line
	
	//rectangle
	draw_line(lenghtSide + GAP, GAP, extremeX, GAP, color, base); //upper rectangle line
	draw_line(extremeX, GAP, extremeX, lenghtSide, color, base); //right rectangle line
	draw_line(extremeX, lenghtSide, lenghtSide + GAP, lenghtSide, color, base); //lower rectangle line
	draw_line(lenghtSide + GAP, lenghtSide, lenghtSide + GAP, GAP, color, base); //lower rectangle line
}

