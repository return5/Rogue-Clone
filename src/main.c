/*                                     ### description ###
	Rogue clone.  a clone of the classic game Rogue with a few slight differences. should be compiled with script 'compilerogueclone.sh'
	author:        github/return5
			       gitlab/return5
	license:       GPL 2.0
	dependencies:  ncurses.
				   C compiler with GNU C11 support.
	version:       0.5
*/

//---------------------------------------- headers----------------------------------------------------
#include "main.h"
//---------------------------------------- global vars ----------------------------------------------
int PLAY = 1;
//---------------------------------------- code -----------------------------------------------------

void initalizeWorld(void) {
	do {  //make the map,rooms, and paths
		makeRooms();
		initWorldMap();
		START_OVER = 0;       //initialize this value to 0. it is used in makePassages inside makepath.c
	} while(makePassages() > 100); //if makePasses gets stuck in loop,ususally because it can't connect two rooms, then make new map.
	makeEnemies();	
}

void gameLoop(void) {
	while(PLAY) {
		playerTurn();
	}
	endwin();
}

int main(void) {	
	initScreen();
	initWindow();
	initColors();
	makeItemValues();  //set initial values for all the items 
	printClassSelect();
	selectClass();
	initalizeWorld();	
	makePlayer();
	printWorldMap();
	printAllEnemies();
	gameLoop();
	return 0;
}