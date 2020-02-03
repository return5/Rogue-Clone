#pragma  once
#include "characters.h"
#include <stdlib.h>
#include <ncurses.h>
//---------------------------------------------- define ----------------------------------------------------
#define  HEIGHT 30     //height of main_win  makes sure they make with what is in rooms.h
#define  WIDTH  70	  //width of game_win  makes sure they make with what is in rooms.h
#define SWORDSMAN_X WIDTH  - 24
#define SWORDSMAN_Y HEIGHT - 21
#define MAGE_X WIDTH  - 25
#define MAGE_Y HEIGHT - 21
#define SPEARMAN_X WIDTH  - 25
#define SPEARMAN_Y HEIGHT - 21
#define WOLF_X WIDTH  - 25
#define WOLF_Y HEIGHT - 20
#define COMPWOLF_X 10
#define COMPWOLF_Y HEIGHT - 15
#define ARCHER_X WIDTH  - 25
#define ARCHER_Y HEIGHT - 22
#define BEAR_X WIDTH  - 25
#define BEAR_Y HEIGHT - 22
#define MONSTER_X WIDTH  - 25
#define MONSTER_Y HEIGHT - 23
#define SKELETON_X WIDTH  - 25
#define SKELETON_Y HEIGHT - 24
#define PLAYER_X 15
#define PLAYER_Y HEIGHT - 21

//---------------------------------------------- typedefs ---------------------------------------------------


//----------------------------------------------- enums ----------------------------------------------------


//----------------------------------------------- structs --------------------------------------------------


//--------------------------------------------- global vars ------------------------------------------------
extern WINDOW *MAIN_WIN;

//----------------------------------------------- prototypes -----------------------------------------------
model_fpointer	    getCharModel                (CHARTYPE type);

//----------------------------------------------- prototypes in other files --------------------------------