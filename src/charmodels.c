/*                                     ### description ###

		
*/
//---------------------------------------- headers---------------------------------------------------
#include "charmodels.h"

//---------------------------------------- global vars ----------------------------------------------

//---------------------------------------- prototypes -----------------------------------------------
static void	 printSwordsmanAttackScreen     (void);
static void	 printMageAttackScreen          (void);
static void	 printSpearmanAttackScreen      (void);
static void	 printWolfAttackScreen          (void);
static void	 printArcherAttackScreen        (void);
static void	 printBearAttackScreen          (void);
static void	 printMonsterAttackScreen       (void);
static void	 printSkeletonAttackScreen      (void);
static void	 printPlayerAttackScreen        (void);
static void  printCompanionWolfAttackScreen (void);

//---------------------------------------- code -----------------------------------------------------

model_fpointer getCharModel(CHARTYPE type) {
	switch(type) {
		case PLAYERTYPE:   return printPlayerAttackScreen;
		case SWORDSMAN:    return printSwordsmanAttackScreen;
		case SPEARMAN:     return printSpearmanAttackScreen;
		case WOLF:         return printWolfAttackScreen;
		case ARCHER:       return printArcherAttackScreen;
		case SKELETON:     return printSkeletonAttackScreen;	
		case MAGE:		   return printMageAttackScreen;
		case BEAR:	       return printBearAttackScreen;
		case MONSTER:      return printMonsterAttackScreen;
		case COMPWOLF:     return printCompanionWolfAttackScreen;
		case NUM_CHARTYPE: return printPlayerAttackScreen;  //should never be used, just to fill out all enum types
		default:           return printPlayerAttackScreen;  //just a default case. shouldnt get here.
	}
}

static void printSwordsmanAttackScreen(void) {
	wattron(MAIN_WIN,COLOR_PAIR(GREENCHAR));
	mvwprintw(MAIN_WIN,SWORDSMAN_Y    ,SWORDSMAN_X + 3,"O"); //head
	mvwprintw(MAIN_WIN,SWORDSMAN_Y + 1,SWORDSMAN_X + 1,"__"); //left arm
	mvwprintw(MAIN_WIN,SWORDSMAN_Y + 1,SWORDSMAN_X + 4,"__"); //right arm
	mvwprintw(MAIN_WIN,SWORDSMAN_Y + 3,SWORDSMAN_X + 2,"/ \\ "); //legs
	mvwprintw(MAIN_WIN,SWORDSMAN_Y + 4,SWORDSMAN_X + 1,"/   \\"); //lower legs
	wattroff(MAIN_WIN,COLOR_PAIR(GREENCHAR));
	wattron(MAIN_WIN,COLOR_PAIR(BLUECHAR));
	mvwprintw(MAIN_WIN,SWORDSMAN_Y + 1,SWORDSMAN_X,"|"); //top of shield
	mvwprintw(MAIN_WIN,SWORDSMAN_Y + 2,SWORDSMAN_X,"|"); //bottom of shield
	wattroff(MAIN_WIN,COLOR_PAIR(BLUECHAR));
	wattron(MAIN_WIN,COLOR_PAIR(REDCHAR));
	mvwprintw(MAIN_WIN,SWORDSMAN_Y + 1,SWORDSMAN_X + 3,"|"); //top of torso
	mvwprintw(MAIN_WIN,SWORDSMAN_Y + 2,SWORDSMAN_X + 3,"|"); ///bottom of torso
	wattroff(MAIN_WIN,COLOR_PAIR(REDCHAR));
	wattron(MAIN_WIN,COLOR_PAIR(WHITECHAR));
	mvwprintw(MAIN_WIN,SWORDSMAN_Y    ,SWORDSMAN_X + 7,"/"); //top of sword
	mvwprintw(MAIN_WIN,SWORDSMAN_Y + 1,SWORDSMAN_X + 6,"/"); //bottom of sword
	wattroff(MAIN_WIN,COLOR_PAIR(WHITECHAR));
}

static void printMageAttackScreen(void) {
	wattron(MAIN_WIN,COLOR_PAIR(BLUECHAR));
	mvwprintw(MAIN_WIN,MAGE_Y    ,MAGE_X + 2,"O"); //head
	mvwprintw(MAIN_WIN,MAGE_Y + 1,MAGE_X    ,"__|__"); //upper torso and arms
	mvwprintw(MAIN_WIN,MAGE_Y + 2,MAGE_X + 2,"|"); //lower torso
	mvwprintw(MAIN_WIN,MAGE_Y + 3,MAGE_X + 1,"/ \\"); //upper legs
	mvwprintw(MAIN_WIN,MAGE_Y + 4,MAGE_X    ,"/   \\"); //lower legs
	wattroff(MAIN_WIN,COLOR_PAIR(BLUECHAR));
	wattron(MAIN_WIN,COLOR_PAIR(YELLOWCHAR));
	wattroff(MAIN_WIN,COLOR_PAIR(YELLOWCHAR));
	wattron(MAIN_WIN,COLOR_PAIR(WHITECHAR));
	mvwprintw(MAIN_WIN,MAGE_Y + 1,MAGE_X + 5,"|"); //staff handle
	mvwprintw(MAIN_WIN,MAGE_Y + 2,MAGE_X + 5,"|"); //staff handle
	mvwprintw(MAIN_WIN,MAGE_Y + 3,MAGE_X + 5,"|"); //staff handle
	mvwprintw(MAIN_WIN,MAGE_Y + 4,MAGE_X + 5,"|"); //staff handle
	wattroff(MAIN_WIN,COLOR_PAIR(WHITECHAR));
	wattron(MAIN_WIN,COLOR_PAIR(CYANCHAR));
	mvwprintw(MAIN_WIN,MAGE_Y,MAGE_X + 5,"+"); //staff head
	wattroff(MAIN_WIN,COLOR_PAIR(CYANCHAR));

}

static void printSpearmanAttackScreen(void) {
	wattron(MAIN_WIN,COLOR_PAIR(YELLOWCHAR));
	mvwprintw(MAIN_WIN,SPEARMAN_Y + 2,SPEARMAN_X + 1,"____ _ _ __"); //spear
	wattroff(MAIN_WIN,COLOR_PAIR(YELLOWCHAR));	
	wattron(MAIN_WIN,COLOR_PAIR(WHITECHAR));
	mvwprintw(MAIN_WIN,SPEARMAN_Y    ,SPEARMAN_X + 7,"O"); //head
	mvwprintw(MAIN_WIN,SPEARMAN_Y + 1,SPEARMAN_X + 5,"__|__"); //upper torso and arms
	mvwprintw(MAIN_WIN,SPEARMAN_Y + 2,SPEARMAN_X    ,"_"); //spearpoint
	mvwprintw(MAIN_WIN,SPEARMAN_Y + 2,SPEARMAN_X + 7,"|"); //lower torso
	mvwprintw(MAIN_WIN,SPEARMAN_Y + 2,SPEARMAN_X + 5,"\\"); //hands
	mvwprintw(MAIN_WIN,SPEARMAN_Y + 2,SPEARMAN_X + 9,"/"); //other hands
	mvwprintw(MAIN_WIN,SPEARMAN_Y + 3,SPEARMAN_X + 6,"/ \\"); //legs
	mvwprintw(MAIN_WIN,SPEARMAN_Y + 4,SPEARMAN_X + 5,"/   \\"); //lower legs
	wattroff(MAIN_WIN,COLOR_PAIR(WHITECHAR));
}

static void printWolfAttackScreen(void) {
	wattron(MAIN_WIN,COLOR_PAIR(WHITECHAR));
	mvwprintw(MAIN_WIN,WOLF_Y    ,WOLF_X + 1,"_"); //top of head
	mvwprintw(MAIN_WIN,WOLF_Y + 1,WOLF_X    ,"<"); //snout
	wattroff(MAIN_WIN,COLOR_PAIR(WHITECHAR));
	wattron(MAIN_WIN,COLOR_PAIR(REDCHAR));
	mvwprintw(MAIN_WIN,WOLF_Y + 1,WOLF_X + 1,"="); //eyes?
	wattroff(MAIN_WIN,COLOR_PAIR(REDCHAR));	
	wattron(MAIN_WIN,COLOR_PAIR(YELLOWCHAR));
	mvwprintw(MAIN_WIN,WOLF_Y    ,WOLF_X + 2,"/"); //ears
	mvwprintw(MAIN_WIN,WOLF_Y + 1,WOLF_X + 2,"\\_______/"); //upperbody
	mvwprintw(MAIN_WIN,WOLF_Y + 2,WOLF_X + 3,"/\\    /\\"); //upper legs
	mvwprintw(MAIN_WIN,WOLF_Y + 3,WOLF_X + 2,"/  \\  /  \\"); //lower legs
	wattroff(MAIN_WIN,COLOR_PAIR(YELLOWCHAR));
}

static void printCompanionWolfAttackScreen(void) {
	wattron(  MAIN_WIN,COLOR_PAIR(WHITECHAR));
	mvwprintw(MAIN_WIN,COMPWOLF_Y    ,COMPWOLF_X + 9 ,"_"); //top of head
	mvwprintw(MAIN_WIN,COMPWOLF_Y + 1,COMPWOLF_X + 10 ,">"); //snout
	wattroff( MAIN_WIN,COLOR_PAIR(WHITECHAR));
	wattron(  MAIN_WIN,COLOR_PAIR(REDCHAR));
	mvwprintw(MAIN_WIN,COMPWOLF_Y + 1,COMPWOLF_X + 9,"="); //eyes?
	wattroff( MAIN_WIN,COLOR_PAIR(REDCHAR));	
	wattron(  MAIN_WIN,COLOR_PAIR(CYANCHAR));
	mvwprintw(MAIN_WIN,COMPWOLF_Y    ,COMPWOLF_X + 8,"/"); //ears
	mvwprintw(MAIN_WIN,COMPWOLF_Y + 1,COMPWOLF_X    ,"\\_______/"); //upperbody
	mvwprintw(MAIN_WIN,COMPWOLF_Y + 2,COMPWOLF_X + 1,"/\\    /\\"); //upper legs
	mvwprintw(MAIN_WIN,COMPWOLF_Y + 3,COMPWOLF_X    ,"/  \\  /  \\"); //lower legs
	wattroff( MAIN_WIN,COLOR_PAIR(CYANCHAR));
}

static void printArcherAttackScreen(void) {
	wattron(MAIN_WIN,COLOR_PAIR(BLUECHAR));
	mvwprintw(MAIN_WIN,ARCHER_Y    ,ARCHER_X + 4,")"); //bow
	mvwprintw(MAIN_WIN,ARCHER_Y + 1,ARCHER_X + 3,"/"); //bow
	mvwprintw(MAIN_WIN,ARCHER_Y + 2,ARCHER_X + 2,"/"); //bow
	mvwprintw(MAIN_WIN,ARCHER_Y + 3,ARCHER_X + 2,"\\"); //bow
	mvwprintw(MAIN_WIN,ARCHER_Y + 4,ARCHER_X + 3,"\\"); //bow
	mvwprintw(MAIN_WIN,ARCHER_Y + 5,ARCHER_X + 4,")"); //bow
	wattroff(MAIN_WIN,COLOR_PAIR(BLUECHAR));
	wattron(MAIN_WIN,COLOR_PAIR(WHITECHAR));
	mvwprintw(MAIN_WIN,ARCHER_Y + 1,ARCHER_X + 4,"|"); //bowstring
	mvwprintw(MAIN_WIN,ARCHER_Y + 2,ARCHER_X + 4,"|"); //bowstring
	mvwprintw(MAIN_WIN,ARCHER_Y + 3,ARCHER_X + 4,"|"); //bowstring
	mvwprintw(MAIN_WIN,ARCHER_Y + 4,ARCHER_X + 4,"|"); //bowstring
	mvwprintw(MAIN_WIN,ARCHER_Y + 2,ARCHER_X - 1,"_"); //arrowhead
	wattroff(MAIN_WIN,COLOR_PAIR(WHITECHAR));
	wattron(MAIN_WIN,COLOR_PAIR(YELLOWCHAR));
	mvwprintw(MAIN_WIN,ARCHER_Y + 2,ARCHER_X + 3,"_"); //arow shaft
	mvwprintw(MAIN_WIN,ARCHER_Y + 2,ARCHER_X   ,"__"); //arow shaft
	mvwprintw(MAIN_WIN,ARCHER_Y + 1,ARCHER_X + 7,"O"); //head
	wattroff(MAIN_WIN,COLOR_PAIR(YELLOWCHAR));
	wattron(MAIN_WIN,COLOR_PAIR(CYANCHAR));
	mvwprintw(MAIN_WIN,ARCHER_Y + 2,ARCHER_X + 5,"__"); //arms
	wattroff(MAIN_WIN,COLOR_PAIR(CYANCHAR));
	wattron(MAIN_WIN,COLOR_PAIR(MAGENTACHAR));
	mvwprintw(MAIN_WIN,ARCHER_Y + 2,ARCHER_X + 7,"|"); //torso
	mvwprintw(MAIN_WIN,ARCHER_Y + 3,ARCHER_X + 7,"|"); //torso
	wattroff(MAIN_WIN,COLOR_PAIR(MAGENTACHAR));
	wattron(MAIN_WIN,COLOR_PAIR(GREENCHAR));
	mvwprintw(MAIN_WIN,ARCHER_Y + 4,ARCHER_X + 6,"/ \\"); //legs
	mvwprintw(MAIN_WIN,ARCHER_Y + 5,ARCHER_X + 5,"/   \\"); //lower legs
	wattroff(MAIN_WIN,COLOR_PAIR(GREENCHAR));
}

static void printBearAttackScreen(void) {
	wattron(MAIN_WIN,COLOR_PAIR(REDCHAR));
	mvwprintw(MAIN_WIN,BEAR_Y    ,BEAR_X + 2,".");    //eyes 
	wattroff(MAIN_WIN,COLOR_PAIR(REDCHAR));
	wattron(MAIN_WIN,COLOR_PAIR(YELLOWCHAR));
	mvwprintw(MAIN_WIN,BEAR_Y    ,BEAR_X + 3,"^");    //ears
	mvwprintw(MAIN_WIN,BEAR_Y + 1,BEAR_X    ,"<== )"); //nose
    mvwprintw(MAIN_WIN,BEAR_Y + 2,BEAR_X + 5,"#########"); //upper body
    mvwprintw(MAIN_WIN,BEAR_Y + 2,BEAR_X + 15,"*"); //tail
	mvwprintw(MAIN_WIN,BEAR_Y + 3,BEAR_X + 5,"#########");  //mid body
	mvwprintw(MAIN_WIN,BEAR_Y + 4,BEAR_X + 5,"---------");  //lower body
	wattroff(MAIN_WIN,COLOR_PAIR(YELLOWCHAR));
    //mvwprintw(MAIN_WIN,BEAR_Y + 1,BEAR_X + 4,"|"); //throat
    mvwprintw(MAIN_WIN,BEAR_Y + 2,BEAR_X + 4,"|"); //upper body
	mvwprintw(MAIN_WIN,BEAR_Y + 3,BEAR_X + 4,"|");  //mid body
	mvwprintw(MAIN_WIN,BEAR_Y + 4,BEAR_X + 4,"|");  //lower body
	mvwprintw(MAIN_WIN,BEAR_Y + 5,BEAR_X + 4,"|");  //legs
    mvwprintw(MAIN_WIN,BEAR_Y + 2,BEAR_X + 14,"|"); //rear of upper body 
	mvwprintw(MAIN_WIN,BEAR_Y + 3,BEAR_X + 14,"|");  //rear of mid body
	mvwprintw(MAIN_WIN,BEAR_Y + 4,BEAR_X + 14,"|");  //rear of lower body
	mvwprintw(MAIN_WIN,BEAR_Y + 5,BEAR_X + 14,"|");  //rear of legs
}

static void printMonsterAttackScreen(void) {
	wattron(MAIN_WIN,COLOR_PAIR(YELLOWCHAR));
	mvwprintw(MAIN_WIN,MONSTER_Y    ,MONSTER_X + 5,"(   )");   //face
	mvwprintw(MAIN_WIN,MONSTER_Y + 2,MONSTER_X + 4 ,"\\-----/");  //upper body
	mvwprintw(MAIN_WIN,MONSTER_Y + 3,MONSTER_X + 4,"|     |");   //mid body
	mvwprintw(MAIN_WIN,MONSTER_Y + 4,MONSTER_X + 4,"|_____|");   //lower body
	mvwprintw(MAIN_WIN,MONSTER_Y + 5,MONSTER_X + 3,"/       \\");  //upper legs
	mvwprintw(MAIN_WIN,MONSTER_Y + 7,MONSTER_X + 1,"/           \\");  //lower legs
	wattroff(MAIN_WIN,COLOR_PAIR(YELLOWCHAR));
	wattron(MAIN_WIN,COLOR_PAIR(GREENCHAR));
	mvwprintw(MAIN_WIN,MONSTER_Y + 2,MONSTER_X     ,"____");  //left arm
	mvwprintw(MAIN_WIN,MONSTER_Y + 2,MONSTER_X + 11,"____");	 //right arm
	mvwprintw(MAIN_WIN,MONSTER_Y + 6,MONSTER_X + 2 ,"/         \\");  //mid section of legs
	wattroff(MAIN_WIN,COLOR_PAIR(GREENCHAR));
	wattron(MAIN_WIN,COLOR_PAIR(BLUECHAR));
	mvwprintw(MAIN_WIN,MONSTER_Y + 1,MONSTER_X + 7 ,"|");  //neck
	mvwprintw(MAIN_WIN,MONSTER_Y + 4,MONSTER_X + 6,"_");    //lower body
	mvwprintw(MAIN_WIN,MONSTER_Y + 4,MONSTER_X + 8,"_");    //lower body
	mvwprintw(MAIN_WIN,MONSTER_Y + 2,MONSTER_X + 5 ,"-"); //upper body
	mvwprintw(MAIN_WIN,MONSTER_Y + 2,MONSTER_X + 7 ,"-"); //upper body
	wattroff(MAIN_WIN,COLOR_PAIR(BLUECHAR));
	wattron(MAIN_WIN,COLOR_PAIR(MAGENTACHAR));
	mvwprintw(MAIN_WIN,MONSTER_Y    ,MONSTER_X + 6,". ."); //eyes
	wattroff(MAIN_WIN,COLOR_PAIR(MAGENTACHAR));
	wattron(MAIN_WIN,COLOR_PAIR(REDCHAR));
	mvwprintw(MAIN_WIN,MONSTER_Y   ,MONSTER_X + 7,"_"); //mouth
	wattroff(MAIN_WIN,COLOR_PAIR(REDCHAR));
}

static void printSkeletonAttackScreen(void) {
	wattron(MAIN_WIN,COLOR_PAIR(CYANCHAR));
	mvwprintw(MAIN_WIN,SKELETON_Y + 3,SKELETON_X + 1,"|"); //sword handle
	mvwprintw(MAIN_WIN,SKELETON_Y + 4,SKELETON_X + 1,"|"); //sword handle
	wattroff(MAIN_WIN,COLOR_PAIR(CYANCHAR));
	wattron(MAIN_WIN,COLOR_PAIR(BLUECHAR));
	mvwprintw(MAIN_WIN,SKELETON_Y + 3,SKELETON_X    ,"-"); //handgaurd
	mvwprintw(MAIN_WIN,SKELETON_Y + 3,SKELETON_X + 2,"-"); //handgaurd
	wattroff(MAIN_WIN,COLOR_PAIR(BLUECHAR));
	wattron(MAIN_WIN,COLOR_PAIR(WHITECHAR));
	mvwprintw(MAIN_WIN,SKELETON_Y    ,SKELETON_X + 1,"|"); //sword blade
	mvwprintw(MAIN_WIN,SKELETON_Y + 1,SKELETON_X + 1,"|"); //sword blade
	mvwprintw(MAIN_WIN,SKELETON_Y + 2,SKELETON_X + 1,"|"); //sword blade
	mvwprintw(MAIN_WIN,SKELETON_Y + 3,SKELETON_X + 4,"0"); //head
	mvwprintw(MAIN_WIN,SKELETON_Y + 4,SKELETON_X + 2,"--|"); //upper torso and arms
	mvwprintw(MAIN_WIN,SKELETON_Y + 5,SKELETON_X + 4,"|"); //lower torso
	mvwprintw(MAIN_WIN,SKELETON_Y + 6,SKELETON_X + 3,"/ \\"); //leg
	mvwprintw(MAIN_WIN,SKELETON_Y + 7,SKELETON_X + 2,"/   \\"); //lower leg
	wattroff(MAIN_WIN,COLOR_PAIR(WHITECHAR));
}

static void printPlayerAttackScreen(void) {	
	wattron(MAIN_WIN,COLOR_PAIR(WHITECHAR));
	mvwprintw(MAIN_WIN,PLAYER_Y    ,PLAYER_X,"\\"); //sword
	mvwprintw(MAIN_WIN,PLAYER_Y + 1,PLAYER_X +1,"\\"); //sword
	wattroff(MAIN_WIN,COLOR_PAIR(WHITECHAR));
	wattron(MAIN_WIN,COLOR_PAIR(GREENCHAR));
	mvwprintw(MAIN_WIN,PLAYER_Y + 1,PLAYER_X + 4,"|"); //upper torso
	mvwprintw(MAIN_WIN,PLAYER_Y + 2,PLAYER_X + 4,"|"); //lower torso
	wattroff(MAIN_WIN,COLOR_PAIR(GREENCHAR));
	wattron(MAIN_WIN,COLOR_PAIR(YELLOWCHAR));
	mvwprintw(MAIN_WIN,PLAYER_Y    ,PLAYER_X + 4,"O"); //head
	mvwprintw(MAIN_WIN,PLAYER_Y + 1,PLAYER_X + 2,"__"); //arms
	mvwprintw(MAIN_WIN,PLAYER_Y + 1,PLAYER_X + 5,"__"); //arms
	mvwprintw(MAIN_WIN,PLAYER_Y + 3,PLAYER_X + 3,"/ \\"); //legs
	mvwprintw(MAIN_WIN,PLAYER_Y + 4,PLAYER_X + 2,"/   \\"); //lowr legs
	wattroff(MAIN_WIN,COLOR_PAIR(YELLOWCHAR));
	wattron(MAIN_WIN,COLOR_PAIR(REDCHAR));
	mvwprintw(MAIN_WIN,PLAYER_Y + 1,PLAYER_X + 7,"|"); //sheild
	mvwprintw(MAIN_WIN,PLAYER_Y + 2,PLAYER_X + 7,"|"); //sheild
	wattroff(MAIN_WIN,COLOR_PAIR(REDCHAR));
}
