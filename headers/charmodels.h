#include "characters.h"
#include <stdlib.h>
#include <ncurses.h>
//---------------------------------------------- define ----------------------------------------------------
#define  HEIGHT 30     //height of main_win  makes sure they make with what is in rooms.h
#define  WIDTH  70	  //width of game_win  makes sure they make with what is in rooms.h
//---------------------------------------------- typedefs ---------------------------------------------------


//----------------------------------------------- enums ----------------------------------------------------


//----------------------------------------------- structs --------------------------------------------------


//--------------------------------------------- global vars ------------------------------------------------
extern WINDOW *MAIN_WIN;

//----------------------------------------------- prototypes -----------------------------------------------
model_fpointer	getCharModel                (CHARTYPE type);
void			printSwordsmanAttackScreen  (void);
void			printMageAttackScreen       (void);
void			printSpearmanAttackScreen   (void);
void			printWolfAttackScreen       (void);
void			printArcherAttackScreen     (void);
void			printBearAttackScreen       (void);
void			printMonsterAttackScreen    (void);
void			printSkeletonAttackScreen   (void);
void			printPlayerAttackScreen     (void);

//----------------------------------------------- prototypes in other files --------------------------------