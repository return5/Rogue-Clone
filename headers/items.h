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
int      useHEALTHPIPE          (const ITEM  *const item, CHARACTER *const character);
int      usePoisonPotion        (const ITEM  *const item, CHARACTER *const character);
int      useSlowHEALTHPIPE      (const ITEM  *const item, CHARACTER *const character);
int      useFood                (const ITEM  *const item, CHARACTER *const character);
int      useArrow               (const ITEM  *const item, CHARACTER *const character);
int      useFireCharge          (const ITEM  *const item, CHARACTER *const character);
void     makeItemValues         (void);
void     printInventory         (ITEM **inventory);
int      checkIfHEALTHPIPE      (CHARACTER *const attacker);
int      playerUseItem          (CHARACTER *const character);
int      checkIfValidItem       (const unsigned int item);
int      useItem                (CHARACTER *const attacker,CHARACTER *const defender);
int      playerDisplayInventory (void);
int      computerCheckItem      (CHARACTER *const attacker,CHARACTER *const defender);
int      charUseItem            (CHARACTER *const attacker,CHARACTER *const defender,ITEMTYPE item);  
void     makeItemsOnMap         (void);
void     removeItemOffMap       (const ITEM *const item);
//---------------------------------------------- prototypes in other files -------------------------------

extern void  clearCombatPrompt    (void);
extern void  printToCombatPrompt  (const int x, const int y, const char *const str);
extern void  printCombatPrompt    (void);