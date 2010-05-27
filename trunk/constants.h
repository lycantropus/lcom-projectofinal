#define BACKGROUNDCOLOR BLUE
#define NORMAL (RED_FOREG | GREEN_FOREG | BLUE_FOREG)
#define BLUE_FOREG  (1 << 0)  ///< Foreground blue bit
#define GREEN_FOREG (1 << 1)  ///< Foreground green bit
#define RED_FOREG   (1 << 2)  ///< Foreground red bit

//gap between screen limit and screenborders
#define GAP 4

//timer's led and border thickness
#define BORDERTHICKNESS(HRES) ((HRES>=1024)? 3:2)
#define LEDHEIGHT(HRES) ((HRES>=1024)? 9:7)

//definitions for the coordinates of the timer's border
//upper left x
#define LEFTX(HRES) (HRES-2*GAP-6*BORDERTHICKNESS(HRES)-2*LEDHEIGHT(HRES)-8)
//upper left y
#define LEFTY GAP*2
//lower right x
#define RIGHTX(HRES) (HRES-GAP*2-1)
//lower right y
#define RIGHTY(HRES) (LEFTY+2*LEDHEIGHT(HRES)+4*BORDERTHICKNESS(HRES)+4)


//values of the dimensions of the square and rectangle drawn in the screen
//extern int lenghtSide;
//extern int xtremeX;
#define lenghtSide VRES-GAP-1 //coordinates for the corners of the square
#define extremeX HRES - GAP - 1 //rectangle's extreme x value

//corodinates for the lines in the game board
#define firstLineCoordinate ((int)(lenghtSide-GAP)/3+GAP)
#define secondLineCoordinate ((int)2*(lenghtSide-GAP)/3+GAP)

//cordenadas dos centros dos quadrados e da constante de soma
#define firstCenterXY ((int)((firstLineCoordinate - GAP)/2 + GAP + 1))
#define sumPosicion ((int)(firstLineCoordinate - GAP - 1))
