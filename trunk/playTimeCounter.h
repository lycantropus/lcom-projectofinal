#ifndef _PLAYTIMECOUNTER_H_
#define _PLAYTIMECOUNTER_H_

#include <conio.h>

#include "video-graphics.h"
#include "constants.h"
#include "rtc.h"

extern char* base;

/*(xi, yi)-> ccordinates of the upper left corner
(xf, yf)->coordinates of the  lower right corner
thickness-> number of pixels in each border line
color->color of the border
*/
void drawTimerBorder(int xi, int yi, int xf, int yf, int thickness, int color, char *base);

/*

(xi, yi)-> ccordinates of the upper left corner of the timer's border
(xf, yf)->coordinates of the  lower right corner of the timer's border
thickness-> thickness of the led
offsetX or Y-> offset that must be aplied, in order to draw the number in the correct place. the reference point is the left upper exterior corner of the timer border
number-> the numder to draw
when the leds are turned off, their color is red. when on, they're light red


schematic representation of the leds
	    _    _
	   |_| |_|
	   |_| |_|	  
*/

void drawNumber(int xi, int yi, int offsetX, int offsetY, int number, char *base);

/*the following funcions serve the purpose of drawing each one of the leds
The group that is making this project decided to number every led, in order to make easier to schematicaly represent the implementation made
The reason why there are functions associated whith many numbers is that the leds are similar in shape, but are positioned in a different place.
So, the same funtion is called, but whith different cooordinates
*/
/*schematic representation of the led that the following funcion draws
	    _	 _
	   |_|
	   |_|
*/
/*or
	    _
	   |_|	_
	   |_|
*/
void drawFirstOrSeventhLed(int xi, int yi, int color, char* base);

/*schematic representation of the led that the following funcion draws
	    _
	   |_|	| 
	   |_|
*/
/*or
	    _
	   |_|
	   |_|	|
*/
void drawSecondOrThirdLed(int xi, int yi, int color, char* base);


/*schematic representation of the led that the following funcion draws
	    _
	   |_|
	   |_|	_
*/
void drawFourthLed(int xi, int yi, int color, char* base);

/*schematic representation of the led that the following funcion draws
	    _
	   |_|	  |
	   |_|
*/
/*or
	    _
	   |_|
	   |_|	  |
*/
void drawFifthOrSixthLed(int xi, int yi, int color, char* base);

void drawWatch(int lastRtc);
#endif
