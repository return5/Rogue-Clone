/*                                           ### description ###                       

*/

//---------------------------------------------- headers -------------------------------------------------
#pragma once
#include "characters.h"
#include "rooms.h"
#include <stdlib.h>
#include <ncurses.h>
//---------------------------------------------- define --------------------------------------------------

//---------------------------------------------- enums ---------------------------------------------------


//---------------------------------------------- typedefs ------------------------------------------------


//---------------------------------------------- structs -------------------------------------------------


//---------------------------------------------- global vars ---------------------------------------------
extern ENEMY *ENEMIES;

//---------------------------------------------- prototypes ----------------------------------------------
void      computerTurn        (void);

//---------------------------------------------- prototypes in other files -------------------------------

extern int       moveCharacter    (const MOVEMENT next_move,CHARACTER *const character);
extern MOVEMENT  getNextMovement  (const CHARACTER *const character);
extern void      printToPrompt    (const int x, const int y, const char *const str);
extern int       checkIfEnemy     (void); 
extern void      engageCombat     (CHARACTER *const character);
//---------------------------------------------- code ----------------------------------------------------