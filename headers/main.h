//---------------------------------------- headers -----------------------------------------------
#include "rooms.h"


//----------------------------------------------- variables ---------------------------------------
extern int START_OVER;

//---------------------------------------- prototypes ---------------------------------------------

void  initalizeWorld  (void);
void  gameLoop       (void);
//---------------------------------------- prototypes in other files ------------------------------

void  makeRooms         (void);
void  initWindow        (void);
void  initScreen        (void);
void  printSpecificRoom (const ROOMINFO *const room);
void  makeItemValues    (void);
void  makeEnemies       (void);
void  printAllEnemies   (void);
void  initWorldMap      (void);
void  printWorldMap     (void);
int   makePassages      (void);
void  initColors        (void);
void  makePlayer        (void);
void  selectClass       (void);
void  printClassSelect  (void);
void  playerTurn        (void);