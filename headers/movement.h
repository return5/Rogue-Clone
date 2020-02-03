/*                                           ### description ###                       

*/

//---------------------------------------------- headers -------------------------------------------------
#pragma once
#include "characters.h"
#include "rooms.h"
#include<stdlib.h>
//---------------------------------------------- define --------------------------------------------------

//---------------------------------------------- enums ---------------------------------------------------


//---------------------------------------------- typedefs ------------------------------------------------


//---------------------------------------------- structs -------------------------------------------------


//---------------------------------------------- global vars ---------------------------------------------
extern CHARACTER *PLAYER;
extern ENEMY     *ENEMIES;

//---------------------------------------------- prototypes ----------------------------------------------
int          moveCharacter       (const MOVEMENT next_move,CHARACTER *const character);
void         updateMap           (const CHARACTER *const character);
MOVEMENT     getNextMovement     (const CHARACTER *const character);
int          checkIfEnemy        (void);
//---------------------------------------------- prototypes in other files -------------------------------