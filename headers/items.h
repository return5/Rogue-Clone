/*                                           ### description ###                       

*/

//---------------------------------------------- headers -------------------------------------------------
#include "characters.h"
#include <stdlib.h>	   //malloc
#include <stdio.h>  //snprintf
#include <ncurses.h>
//---------------------------------------------- define --------------------------------------------------

//---------------------------------------------- enums ---------------------------------------------------


//---------------------------------------------- typedefs ------------------------------------------------


//---------------------------------------------- structs -------------------------------------------------


//---------------------------------------------- global vars ---------------------------------------------
extern CHARACTER *PLAYER;

//---------------------------------------------- prototypes ----------------------------------------------
ITEM   **makeCharInventory    (CHARTYPE type);
int    useHealthPotion        (const ITEM  *const item, CHARACTER *const character);
int    usePoisonPotion        (const ITEM  *const item, CHARACTER *const character);
int    useSlowHealthPotion    (const ITEM  *const item, CHARACTER *const character);
int    useFood                (const ITEM  *const item, CHARACTER *const character);
int    useArrow               (const ITEM  *const item, CHARACTER *const character);
int    useFireCharge          (const ITEM  *const item, CHARACTER *const character);
void   makeItemValues         (void);
void   printInventory         (ITEM **inventory);
int    checkIfHealthPotion    (CHARACTER *const attacker);
int    playerUseItem          (CHARACTER *const character);
int    checkIfValidItem       (const unsigned int item);
int    useItem                (CHARACTER *const attacker,CHARACTER *const defender);
int    playerDisplayInventory (void);
//---------------------------------------------- prototypes in other files -------------------------------
void  printToPrompt      (const int x, const int y, const char *const str);
void  restoreMainWin     (void); 
void  clearMainWin       (void);
void  copyMainWin        (void);
void  clearPromptWin     (void);