//---------------------------------------- headers -----------------------------------------------
#pragma once
#include "rooms.h"
//----------------------------------------------- variables ---------------------------------------
extern int START_OVER;
//---------------------------------------- prototypes ---------------------------------------------

void  initalizeWorld  (void);
void  gameLoop        (void);
//---------------------------------------- prototypes in other files ------------------------------

extern void  makeRooms         (void);
extern void  initWindow        (void);
extern void  initScreen        (void);
extern void  printSpecificRoom (const ROOMINFO *const room);
extern void  makeItemValues    (void);
extern void  makeEnemies       (void);
extern void  printAllEnemies   (void);
extern void  initWorldMap      (void);
extern void  printWorldMap     (void);
extern int   makePassages      (void);
extern void  initColors        (void);
extern void  makePlayer        (void);
extern void  selectClass       (void);
extern void  printClassSelect  (void);
extern void  playerTurn        (void);
extern void  computerTurn      (void);
extern void  initPlayerOnMap   (void);