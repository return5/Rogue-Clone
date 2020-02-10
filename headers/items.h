/*                                           ### description ###                       

*/

//---------------------------------------------- headers -------------------------------------------------
#pragma  once
#include "gamepieces.h"
#include <stdlib.h>	   //malloc
#include <stdio.h>  //snprintf
#include <ncurses.h>
//---------------------------------------------- define --------------------------------------------------

//---------------------------------------------- enums ---------------------------------------------------


//---------------------------------------------- typedefs ------------------------------------------------


//---------------------------------------------- structs -------------------------------------------------


//---------------------------------------------- global vars ---------------------------------------------
extern CHARACTER  *PLAYER;
extern ROOMSARRAY *ROOMS;
       ITEMONMAP  *LOOSEITEMS;

//---------------------------------------------- prototypes ----------------------------------------------
       ITEM     **makeCharInventory    (CHARTYPE type);
       void     makeItemValues         (void);
       void     printInventory         (ITEM **inventory);
       int      checkIfHEALTHPIPE      (CHARACTER *const attacker);
       int      playerUseItem          (CHARACTER *const character);
       int      checkIfValidItem       (const unsigned int item);
       int      playerDisplayInventory (void);
       int      computerCheckItem      (CHARACTER *const attacker,CHARACTER *const defender);
       void     makeItemsOnMap         (void);
       void     removeItemOffMap       (const ITEM *const item);
       void     printToPrompt          (const int x, const int y, const char *const str);
       void     clearPromptWin         (void);
       int      useItem                (const ITEMTYPE item, CHARACTER *const attacker,CHARACTER *const defender);

//---------------------------------------------- prototypes in other files -------------------------------

extern void  clearCombatPrompt    (void);
extern void  printToCombatPrompt  (const int x, const int y, const char *const str);
extern void  printCombatPrompt    (void);