//---------------------------------------------- headers -------------------------------------------------


//---------------------------------------------- define -------------------------------------------------
#define  HEIGHT 30     //height of main_win   make sure to match these values with the ones in charmodels.h
#define  WIDTH  70	  //width of game_win   make sure to match these values with the ones in charmodels.h

   //get random number in range [min,max]

//----------------------------------------------- enums --------------------------------------------------

enum ROOMCOL      {COLR1 = 5,COLR2 = 8,COLR3 = 5,COLR4 = 4};            //number of columns each room has
enum ROOMROW      {ROWR1 = 7,ROWR2 = 5,ROWR3 = 12,ROWR4 = 15};	        //number of rows each room has
enum NUMROOMS     {R1,R2,R3,R4,R5,R6,R7,NUM_ROOMS};	       
enum ROOMREVEALED {NO,YES};    
enum TILEREVEALED {NOT_REVEALED,REVEALED};
enum MOVEPATH     {MOVELEFT,MOVERIGHT,MOVEUP,MOVEDOWN};
enum WHAT_COLOR   {BLUE = 1,RED,MAGENTA,YELLOW,GREEN,CYAN,WHITE,BLACK,NUM_COLORS};
//---------------------------------------------- typedefs -------------------------------------------------

typedef struct  RLOCATION    RLOCATION;
typedef struct  ROOMINFO     ROOMINFO;
typedef struct  ROOMSARRAY   ROOMSARRAY;
typedef struct  PATH         PATH;
typedef struct  PATHARRAY    PATHARRAY;
typedef struct  TILE         TILE;
typedef enum    TILEREVEALED TILEREVEALED;
typedef enum    ROOMCOL      ROOMCOL;
typedef enum    ROOMROW      ROOMROW;
typedef enum    NUMROOMS     NUMROOMS;
typedef enum    ROOMREVEALED ROOMREVEALED;
typedef enum    MOVEPATH     MOVEPATH;
typedef enum 	WHAT_COLOR   WHAT_COLOR;

//---------------------------------------- global vars ----------------------------------------------
extern          ROOMSARRAY  *ROOMS;
extern          PATHARRAY   *PATHS;
extern 			TILE        *WORLDMAP[HEIGHT][WIDTH];
//----------------------------------------------- structs -------------------------------------------------
struct RLOCATION {
	unsigned int x,y;
};

struct ROOMINFO {
	int          room_size;
	ROOMCOL      col_len;
	ROOMROW      row_len;
	ROOMREVEALED isrevealed;
	WHAT_COLOR   color;
	char         **room;
	RLOCATION    *loc;
};

struct ROOMSARRAY {
	ROOMINFO      **rooms;
	unsigned int  number_rooms;
};

struct TILE {
	char          icon;
	TILEREVEALED  isrevealed;
	ROOMINFO      *room;
	WHAT_COLOR     color;
};


//----------------------------------------------- variables -------------------------------------------------

