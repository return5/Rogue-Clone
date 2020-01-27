//---------------------------------------------- headers----------------------------------------------------
#include "characters.h"
#include "rooms.h"
#include <stdlib.h>
#include <stdio.h>  //snprintf

//---------------------------------------------- define ----------------------------------------------------

//---------------------------------------------- typedefs ---------------------------------------------------


//----------------------------------------------- enums ----------------------------------------------------


//----------------------------------------------- structs --------------------------------------------------


//--------------------------------------------- global vars ------------------------------------------------

extern ENEMY     *ENEMIES;    //linked list which holds enemies
extern CHARACTER *PLAYER;
extern CHARACTER *COMPANION;
//----------------------------------------------- prototypes -----------------------------------------------

void  makeEnemies  (void);
void  makePlayer   (void);

//----------------------------------------------- prototypes in other files --------------------------------
ITEM             **makeCharInventory   (CHARTYPE type);
attack_fpointer  makeCharAtack         (CHARTYPE type);
void             makeItemValues        (void);
model_fpointer   getCharModel          (CHARTYPE type);