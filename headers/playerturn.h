/*                                           ### description ###                       

*/

//---------------------------------------------- headers -------------------------------------------------
#include "rooms.h"
#include "characters.h"
#include <ncurses.h>
//---------------------------------------------- define --------------------------------------------------

//---------------------------------------------- enums ---------------------------------------------------


//---------------------------------------------- typedefs ------------------------------------------------


//---------------------------------------------- structs -------------------------------------------------


//---------------------------------------------- global vars ---------------------------------------------
extern int         PLAY;
extern CHARACTER  *PLAYER;
extern CHARACTER  *COMPANION;
extern PLAYERCLASS PLAYER_CLASS;

//---------------------------------------------- prototypes ----------------------------------------------
void  selectClass   (void);
int   playerTurn    (void);
//---------------------------------------------- prototypes in other files -------------------------------
void      printToPrompt          (const int x, const int y, const char *const str);
void      clearPromptWin         (void);
int       moveCharacter          (const MOVEMENT next_move,CHARACTER *const character);
int       playerDisplayInventory (void);
void      initalizeWorld		 (void);
void      printAllEnemies        (void);
void      printWorldMap          (void);
void      restoreMainWin	     (void);
int        playerUseItem         (CHARACTER *const character);
CHARACTER *itemUseOn             (void);
void       printAreYouSure       (void);