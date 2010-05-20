#include "video-graphics.h"
#include <stdio.h>
#include <go32.h>
#include <sys\nearptr.h>



int HRES, VRES;

static unsigned long get_add(int mode)
{
	__dpmi_regs r;
	unsigned long dosbuf, address=0;
	dosbuf = __tb & 0xFFFFF;		// area transf.

	dosmemput(&address, 4, dosbuf+40);	// apaga bytes 40 a 43
	r.x.ax = 0x4F01;                    	// VBE get mode info
	r.x.di = dosbuf & 0xF;              	// LSB da area transf.
	r.x.es = (dosbuf >> 4) & 0xFFFF;   	// MSB
	r.x.cx = mode;                    	// info sobre o modo 105h

	__dpmi_int(0x10, &r);

	if (r.h.ah)
	{
	     printf("Modo não suportado!!!");
		return 0;                 		// tratamento de erro, modo não suportado
	}

	dosmemget(dosbuf+40, 4, &address); 	// lê end. mem. video

	if (!address)
	{
	       printf("Modo não suportado!!!");
		return 0;                		// tratamento de erro, modo não suportado
	}

	return address;
}

char * enter_graphics(int mode, __dpmi_meminfo *map)
{
	switch (mode){
		case 0x101:{
			HRES = 640; VRES = 480;
			break;
		}
		case 0x103:{
			HRES = 800;VRES = 600;
			break;
		}
		case 0x105:{
			HRES = 1024;VRES = 768;
			break;
		}
		case 0x107:{
			HRES = 1280;VRES = 1024;
			break;
		}
		default:
			return NULL;
	}

	__dpmi_regs reg;
	reg.x.ax = 0x4F02;      	
	reg.x.bx = (0x4000 | mode);  
	__dpmi_int(0x10, &reg); 	// activaçao modo grafico
	
	char *video_mem;		// apontador 

	__djgpp_nearptr_enable();

	map->address = get_add(mode);	//address
	map->size = HRES*VRES; //tamanho
	__dpmi_physical_address_mapping(map); //map

	video_mem = (char *)((*map).address + __djgpp_conventional_base);	// endereço

	return video_mem;
}

void leave_graphics(__dpmi_meminfo map)
{
	__dpmi_regs r;
	
	__dpmi_free_physical_address_mapping(&map); 
	__djgpp_nearptr_disable();
	
	r.x.ax = 0x0003; 
	__dpmi_int(0x10, &r); 
}

void set_pixel(int x, int y, int cor, char *base)	
{
	if ((x >= 0 && y >= 0) && (x<HRES && y<VRES))
	{
		*(base+ x + y * HRES) = cor;
	}
	
}

int get_pixel(int x, int y, char *base)
{
	int cor;
	if ((x >= 0 && y >= 0) && (x<HRES && y<VRES))
	{
		cor = *(base+ x + y * HRES);
		return cor;
	}
	else
		return -1;
}

void clear_screen(char color, char *base)
{
	int i,k;
	for(i = 0; i < VRES; i++)
		for (k = 0; k < HRES; k++)
			*(base+ k + i * HRES) = color;
}

void draw_line(int xi, int yi, int xf, int yf, int color, char *base)
{
int e;
	signed int dx,dy,j, temp; //diferenças em x e y
	signed  int s1,s2, xchange;	//incrementos
    signed int x,y; // x e y
        
	x = xi;
	y = yi;
	
	if (xf < xi) {		//caso 1 xi maior que xf, incremento = -1
		dx = xi - xf;
		s1 = -1;
	}

	else if (xf == xi) {	//caso 2 xi == xf incremento =0
		dx = 0;
		s1 = 0;
	}

	else {					//caso 3 xf < xi incremento = 1
		dx = xf - xi;
		s1 = 1;
	}

	if (yf < yi) {			//caso 1 yi maior que yf, incremento = -1
		dy = yi - yf;
		s2 = -1;
	}

	else if (yf == yi) {
		dy = 0;
		s2 = 0;
	}

	else {
		dy = yf - yi;
		s2 = 1;
	}

	xchange = 0;   

	if (dy>dx) {	// de variacao em y maior que em x troca dx por dy
		temp = dx;
		dx = dy;
		dy = temp;
		xchange = 1;
	} 

	e = dy - dx;  // e é sempre negativo para garantir alternancia nos incrementos das coordenadas
	 
	for (j=0; j<=dx; j++) {
		set_pixel(x,y,color,base);
		
		
		if (e>=0) {						//se for positivo
			if (xchange==1) x = x + s1;	// incrementa o x se tiver trocado
			else y = y + s2;			// incrementa o y se nao tiver trocado
			e = e - dx;
		}
	
		
		if (xchange==1) y = y + s2;		//se e for negativo
		else x = x + s1;			

		e = e + dy;
	}
}


void charTable(unsigned char *table)
{
    FILE *fp;
    fp = fopen("po.dat", "rb");
    fread(table, 256*CHR_H, 1, fp);
    fclose(fp);
}    

Bool drawCharAt(char c, int x, int y, int color, int back_color, char *base, unsigned char *char_table)
{
    if((x+8)>HRES || (y+16) > VRES) return false;
    
    int firstX = x;
    int i, j, n;
    unsigned char *indLetter = char_table + c*16;
    for (i=0; i<16; i++)
    {
        n = 0x80;
        for (j=0; j<8; j++)
        {
            if ((*indLetter & n) == n)
                        set_pixel(x, y, color, base);
            else if (back_color != -1)
                        set_pixel(x, y, back_color, base);
            x++;
            n = n >> 1;
        }
        indLetter++;
        y++;
        x = firstX;
    }
    return true;
}

Bool drawStringAt(char *str, int x, int y, int color, int back_color, char *base, unsigned char *char_table)
{
	while (*str)
	{
		if (!drawCharAt(*str, x, y, color, back_color, base, char_table)) return false;
		str++;
		x = x+8;
	}
	return true;
}
