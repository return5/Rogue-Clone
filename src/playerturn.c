/*                                           ### description ###      

*/
//---------------------------------------------- headers -------------------------------------------------
#include "playerturn.h"

//---------------------------------------------- prototypes ----------------------------------------------
static int   getPlayerInputWolrMap (void);
static void  accessPlayerInventory (void);
static void  quitGame              (void);
static void  resetMap              (void);

//---------------------------------------------- code ----------------------------------------------------


static void quitGame(void) {
	printAreYouSure();
	switch(getch()) {
		case 'y'://FALLTHROUGH
		case 'Y':
			PLAY = 0;
			break;
		default:
			restoreMainWin();
			break;
	}
}

static void resetMap(void) {
	initalizeWorld();
	printWorldMap();
	printAllEnemies();
}

static void accessPlayerInventory(void) {
	playerDisplayInventory();
	if(PLAYER->has_comp == 1) {
		playerUseItem(itemUseOn());
	}
	else {
		playerUseItem(PLAYER);
	}
	restoreMainWin();
}

void selectClass(void) {
	switch(getch()) {
		case '1':
			clearPromptWin();
			printToPrompt(0,0,"you selected Warrior");
			PLAYER_CLASS = WARRIOR;
			break;
		case '2':
			clearPromptWin();
			printToPrompt(0,0,"you selected Archer");
			PLAYER_CLASS = PLAYER_ARCHER;
			break;
		case '3':
			clearPromptWin();
			printToPrompt(0,0,"you selected Animal Whisperer");
			PLAYER_CLASS = ANIMAL_WHISPER;
			break;
		default: 
			clearPromptWin();
			printToPrompt(0,0,"sorry,wrong choice");
			selectClass();
	}
}
//when player is on world map, get the input
static int getPlayerInputWolrMap(void) {
	switch(getch()) {
		case 'w':
			return moveCharacter(UP,PLAYER);
		case 'a':
			return moveCharacter(DOWN,PLAYER);
		case 's':
			return moveCharacter(LEFT,PLAYER);
		case 'd':
			return moveCharacter(RIGHT,PLAYER);	
		case 'q':
			quitGame();
			break;
		case 't':
			resetMap();
			break;
		case 'i':
			accessPlayerInventory();
			break;
		default: 
			return 0;	
	}
	return 1;
}

int playerTurn(void) {
	clearPromptWin();
	printToPrompt(0,0,"'w','a','s','d' to move around.");
	printToPrompt(0,1,"'i' to open inventory");
	printToPrompt(0,2,"'q' to quit game");
	return getPlayerInputWolrMap();
}