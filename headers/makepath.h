
//---------------------------------------------- headers -------------------------------------------------
#pragma   once
#include "gamepieces.h"
#include <stdlib.h>

//----------------------------------------------- define -------------------------------------------------

//----------------------------------------------- enums --------------------------------------------------

enum MOVEPATH {MOVELEFT,MOVERIGHT,MOVEUP,MOVEDOWN};
//----------------------------------------------- typedefs -------------------------------------------------
typedef struct DIRECTIONS   DIRECTIONS;
typedef struct PATHLOCATION PATHLOCATION;
typedef enum   MOVEPATH     MOVEPATH;
//----------------------------------------------- global vars ----------------------------------------------

//----------------------------------------------- structs -------------------------------------------------
struct DIRECTIONS {
	int      num;
	MOVEPATH dir_array[4];
};

struct PATHLOCATION {
	unsigned int      x,y;
	MOVEPATH          previous;
};


//----------------------------------------------- variables -------------------------------------------------

//----------------------------------------------- prototypes -----------------------------------------------
int    makePassages  (void);
void   initWorldMap  (void);
//----------------------------------------------- prototypes in other files --------------------------------

