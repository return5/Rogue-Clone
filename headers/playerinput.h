/*                                           ### description ###                       

*/

//---------------------------------------------- headers -------------------------------------------------
#include <ncurses.h>
#include "characters.h"
//---------------------------------------------- define --------------------------------------------------

//---------------------------------------------- enums ---------------------------------------------------


//---------------------------------------------- typedefs ------------------------------------------------


//---------------------------------------------- structs -------------------------------------------------


//---------------------------------------------- global vars ---------------------------------------------
extern PLAYERCLASS PLAYER_CLASS;
//---------------------------------------------- prototypes ----------------------------------------------
void  selectClass           (void);
int   getPlayerInputWolrMap (void);
//---------------------------------------------- prototypes in other files -------------------------------
void  printToPrompt         (const int x, const int y, const char *const str);
void  clearPromptWin        (void);
int   moveCharacter         (const MOVEMENT next_move,CHARACTER *const character);
void  quitGame              (void);
void  resetMap              (void);
void  accessPlayerInventory (void);