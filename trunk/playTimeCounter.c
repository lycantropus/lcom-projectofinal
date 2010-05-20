#include "playTimeCounter.h"

void drawTimerBorder(int xi, int yi, int xf, int yf, int thickness, int color, char *base){
	draw_line(xi, yi, xi, yf, color, base); //upper line
	draw_line(xi, yf, xf, yf, color, base); //right line
	draw_line(xf, yf, xf, yi, color, base); //dower line
	draw_line(xf, yi, xi, yi, color, base); //left line
	
	int i=2; //the control variable is initialized with value 2, because the second line of the border is already drawn. let's make the second, the third...
	for (; i<=thickness; i++){
		//every coordinates are decreased/increased, in order to draw the inner lines of the border
		xi++;
		yi++;
		xf--;
		yf--;
		draw_line(xi, yi, xi, yf, color, base); //upper line
		draw_line(xi, yf, xf, yf, color, base); //right line
		draw_line(xf, yf, xf, yi, color, base); //dower line
		draw_line(xf, yi, xi, yi, color, base); //left line
	}
}

/*schematic representation of the leds
	    _    _
	   |_| |_|
	   |_| |_|	  
*/

void drawNumber(int xi, int yi, int offsetX, int offsetY, int number, char *base){
	int first=0;
	int second=0;
	int third=0;
	int fourth=0;
	int fifth=0;
	int sixth=0;
	int seventh=0;
	switch(number){
		case 0:	first=second=third=fourth=sixth=fifth=4;
				break;
		case 1:	fifth=sixth=4;
				break;
		case 2:	first=fifth=seventh=third=fourth=4;
				break;
		case 3:	first=fifth=seventh=sixth=fourth=4;
				break;
		case 4:	second=seventh=fifth=sixth=4;
				break;
		case 5:	first=second=seventh=sixth=fourth=4;
				break;
		case 6:	first=second=third=fourth=sixth=seventh=4;
				break;
		case 7:	first=fifth=sixth=4;
				break;
		case 8:	first=second=third=fourth=fifth=sixth=seventh=4;
				break;
		case 9:	first=second=fifth=sixth=seventh=4;
				break;
	}
	int first_led_initX=xi+offsetX+2;
	int first_led_initY=yi+offsetY;
	drawFirstOrSeventhLed(first_led_initX, first_led_initY, BLACK+first, base);
	
	int second_led_initX=xi+offsetX;
	int second_led_initY=yi+offsetY+1;
	drawSecondOrThirdLed(second_led_initX, second_led_initY, BLACK+second, base);
	
	int third_led_initX=xi+offsetX;
	int third_led_initY=yi+offsetY+LEDHEIGHT(HRES)+3;
	drawSecondOrThirdLed(third_led_initX, third_led_initY, BLACK+third, base);
	
	int fourth_led_initX=xi+offsetX+2;
	int fourth_led_initY=yi+offsetY+2*LEDHEIGHT(HRES)+4;
	drawFourthLed(fourth_led_initX, fourth_led_initY, BLACK+fourth, base);
	
	int fifth_led_initX=xi+offsetX+LEDHEIGHT(HRES)+4;
	int fifth_led_initY=yi+offsetY+1;
	drawFifthOrSixthLed(fifth_led_initX, fifth_led_initY, BLACK+fifth, base);
	
	int sixth_led_initX=xi+offsetX+LEDHEIGHT(HRES)+4;
	int sixth_led_initY=yi+offsetY+LEDHEIGHT(HRES)+3;
	drawFifthOrSixthLed(sixth_led_initX, sixth_led_initY, BLACK+sixth, base);
	
	int seventh_led_initX=xi+offsetX+2;
	int seventh_led_initY=yi+offsetY+LEDHEIGHT(HRES)+2;
	drawFirstOrSeventhLed(seventh_led_initX, seventh_led_initY, BLACK+seventh, base);
}

void drawFirstOrSeventhLed(int xi, int yi, int color, char* base){
	//lenght of the bigger line of the led
	int lenght=LEDHEIGHT(HRES);
	draw_line(xi, yi, xi+lenght, yi, color, base);
	++xi;
	++yi;
	draw_line(xi, yi, xi+lenght-2, yi, color, base);
}

void drawSecondOrThirdLed(int xi, int yi, int color, char* base){
	//lenght of the bigger line of the led
	int lenght=LEDHEIGHT(HRES);
	draw_line(xi, yi, xi, yi+lenght, color, base);
	++xi;
	++yi;
	draw_line(xi, yi, xi, yi+lenght-2, color, base);
}



void drawFourthLed(int xi, int yi, int color, char* base){
	//lenght of the bigger line of the led
	int lenght=LEDHEIGHT(HRES);
	draw_line(xi, yi, xi+lenght, yi, color, base);
	++xi;
	--yi;
	draw_line(xi, yi, xi+lenght-2, yi, color, base);
}


void drawFifthOrSixthLed(int xi, int yi, int color, char* base){
	//lenght of the bigger line of the led
	int lenght=LEDHEIGHT(HRES);
	draw_line(xi, yi, xi, yi+lenght, color, base);
	--xi;
	++yi;
	draw_line(xi, yi, xi, yi+lenght-2, color, base);
}

void drawWatch(int lastRtc){
	if (rtc_update<10)
	{
		drawNumber(LEFTX(HRES), LEFTY, BORDERTHICKNESS(HRES)*2, BORDERTHICKNESS(HRES)*2, 0, base);
		drawNumber(LEFTX(HRES), LEFTY, BORDERTHICKNESS(HRES)*3+LEDHEIGHT(HRES)+5, BORDERTHICKNESS(HRES)*2, lastRtc, base);
	}else{
		drawNumber(LEFTX(HRES), LEFTY, BORDERTHICKNESS(HRES)*2, BORDERTHICKNESS(HRES)*2, 1, base);
		drawNumber(LEFTX(HRES), LEFTY, BORDERTHICKNESS(HRES)*3+LEDHEIGHT(HRES)+5, BORDERTHICKNESS(HRES)*2, lastRtc-10, base);
		
	}
}
