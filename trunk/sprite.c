#include "sprite.h"

char *read_xpm(char *map[], int *wd, int *ht) //le do pixmap.h a figura que foi requesitada
{
	__attribute__((unused)) static char read_xpm_jcard;
	
	int width, height, colors;
	char sym[256];
	int  col;
	int i, j;
	char *pix, *pixtmp, *tmp, *line;
	char symbol;
	// read width, height, colors
	if (sscanf(map[0],"%d %d %d", &width, &height, &colors) != 3) 
	{
		printf("read_xpm: incorrect width, height, colors\n");
		return NULL;
	}
	#ifdef DEBUG
		printf("%d %d %d\n", width, height, colors);
	#endif
	if (width > HRES || height > VRES || colors > 256) 
	{
		printf("read_xpm: incorrect width, height, colors\n");
		return NULL;
	}
	
	*wd = width;
	*ht = height;

	for (i=0; i<256; i++)
		sym[i] = 0;

	// read symbols <-> colors 
	for (i=0; i<colors; i++) 
	{
		if (sscanf(map[i+1], "%c %d", &symbol, &col) != 2) 
		{
			printf("read_xpm: incorrect symbol, color at line %d\n", i+1);
		return NULL;
		}
		#ifdef DEBUG
			printf("%c %d\n", symbol, col);
		#endif
		if (col > 256) 
		{
			printf("read_xpm: incorrect color at line %d\n", i+1);
			return NULL;
		}
		sym[col] = symbol;
	}
	
	// allocate pixmap memory
	pix = pixtmp = malloc(width*height);

	// parse each pixmap symbol line
	for (i=0; i<height; i++) 
	{
		line = map[colors+1+i];
		#ifdef DEBUG
			printf("\nparsing %s\n", line);
		#endif
		for (j=0; j<width; j++) 
		{
			tmp = memchr(sym, line[j], 256);  // find color of each symbol
			if (tmp == NULL) 
			{
				printf("read_xpm: incorrect symbol at line %d, col %d\n", colors+i+1, j);
				return NULL;
			}
			*pixtmp++ = tmp - sym; // pointer arithmetic! back to books :-)
			#ifdef DEBUG
				printf("%c:%d ", line[j], tmp-sym);
			#endif
		}
	}
	return pix;
}

Sprite * create_sprite(char *pic[]) //cria uma estrutura sprite
{       
	Sprite *spr = (Sprite *) malloc(sizeof(Sprite));
	if (spr == NULL)
		return NULL;
	
	if ((spr->map = read_xpm(pic, &spr->width, &spr->height)) == NULL)
	{
		free(spr);
		return NULL;
	}	
	return spr;
}

void draw_sprite(Sprite *fig, char* base, int x, int y) //desenha o sprite dando as cordenasdas de onde a imagem deve fikar centrada
{
        int hg = fig->height, wd = fig->width, i, j;
        char* map = fig->map;
        
        x = x - wd/2;
        y = y - hg/2;
        
        for (i = 0; i != hg; i++)
                for (j = 0; j != wd; j++)
                        set_pixel(x+j, y+i, map[i*wd + j], base);

}

int get_width(Sprite * fig) //retorna o width
{
	return fig->width;
}

int get_height(Sprite * fig) //retorna o height
{
	return fig->height;
}
	



