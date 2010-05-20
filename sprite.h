#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "video-graphics.h"

int HRES, VRES, YMIN;

/** A Sprite is an "object" that contains all needed information to
 * create, animate, and destroy a pixmap.  The functions assume that
 * the background is BLACK and they take into account collision with
 * other graphical objects or the screen limits. 
 */
typedef struct
{
  int width, height;   ///< sprite dimensions
  char *map;           ///< the sprite pixmap (use read_xpm())
} Sprite;

Sprite* dart;
Sprite* ping;

#define MAX_SPEED 5    /**< each sprite maximum speed in pixels/frame */
#define RIGHT_HIT 2    /**< collision with right block (WHITE)  */
#define LEFT_HIT 3     /**< collision with left block (WHITE)   */
#define MOUSE_HIT 4    /**< collision with mouse (LIGHTMAGENTA) */


char *read_xpm(char *map[], int *width, int *height);

Sprite * create_sprite(char *pic[]);

void draw_sprite(Sprite *fig, char* base, int x, int y);

int get_width(Sprite * fig);
int get_height(Sprite * fig);

/** @} end of sprite */

#endif
