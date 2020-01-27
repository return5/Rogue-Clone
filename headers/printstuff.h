//---------------------------------------- headers -----------------------------------------------

#include <ncurses.h>
#include "characters.h"
#include "worldmap.h"
#include "rooms.h"

//---------------------------------------- global vars ----------------------------------------------
WINDOW  *MAIN_WIN, *PROMPT_WIN,*MAIN_BORDER,*PROMPT_BORDER,*TEMP_WIN;
extern ROOMSARRAY *ROOMS;
extern ENEMY      *ENEMIES;
extern CHARACTER  *PLAYER;
extern CHARACTER  *COMPANION;
//---------------------------------------- prototypes ---------------------------------------------

void  initScreen        (void);
void  printWorldMap     (void);
void  initWindow        (void);
void  printSpecificRoom (const ROOMINFO  *const room);
void  printCharacter    (const CHARACTER *const character);
void  printAllEnemies   (void);
void  initColors        (void);
void  loopThroughRooms  (void);
void  printTilePiece    (const int x, const int y);
void  printToPrompt     (const int x, const int y, const char *const str);
void  restoreMainWin    (void); 
void  clearMainWin      (void);
void  copyMainWin       (void);
void  printInventory    (ITEM **inventory);
void  clearPromptWin    (void);
void  printAttackScreen (const CHARACTER *const enemy);
void  printClassSelect  (void);
void  playerDisplayInventory(void);
CHARACTER *itemUseOn    (void);
void  printAreYouSure   (void);
//---------------------------------------- prototypes in other files ------------------------------
void  printSwordsmanAttackScreen  (void);
void  printMageAttackScreen       (void);
void  printSpearmanAttackScreen   (void);
void  printWolfAttackScreen       (void);
void  printArcherAttackScreen     (void);
void  printBearAttackScreen       (void);
void  printMonsterAttackScreen    (void);
void  printSkeletonAttackScreen   (void);
void  printPlayerAttackScreen     (void);