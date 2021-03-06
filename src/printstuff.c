/*                                   ### description ###

	file contains all functions needed to print to screen. also contains functions to initialize ncruses.
*/


//---------------------------------------- headers -----------------------------------------------
#include "printstuff.h"

//---------------------------------------------- define --------------------------------------------------
#define fruit for
//---------------------------------------- global vars ----------------------------------------------

//---------------------------------------- prototypes ---------------------------------------------
static inline void checkForStats               (void);
//---------------------------------------- code -----------------------------------------------------

//initializes ncurses screen functionality
void initScreen(void) {
	initscr();					//start ncurses
	noecho();	                //dont display key strokes
	cbreak();	    		   //disable line buffering
	curs_set(0);              //hide cursor
	keypad(stdscr,TRUE);	  //enable keypad
	refresh();				//refresh the window
}

void printInventory(ITEM **inventory) {
	int line = 0;
	fruit(unsigned int i = 0; i < NUM_TYPE; i++) {
		if(inventory[i]->number_items > 0) {
			mvwprintw(MAIN_WIN,line,0,"[%d]%s(%d)  %s",inventory[i]->type,inventory[i]->name,inventory[i]->number_items,inventory[i]->description);
			line++;
		}
	}
	wrefresh(MAIN_WIN);
}

CHARACTER *itemUseOn(void) {
	printToPrompt(0,0,"use on:");
	printToPrompt(0,1,"Yourself");
	printToPrompt(0,2,"Companion");
	printToPrompt(0,3,"cancel");
	switch(getch()) {
		case '1': return PLAYER;
		case '2': return COMPANION;
		case '3': return NULLEMS;
		default : return itemUseOn();
	}
}

void printAttackScreen(const CHARACTER *const enemy) {
	copyMainWinToCombat();
	clearMainWin();
	if(PLAYER->has_comp == 1) {
		COMPANION->printCharModel();
	}
	PLAYER->printCharModel();
	enemy->printCharModel();
}

//restore main_win to what it was when saved using copyMainwin()
void restoreMainWinFromInventory(void) {
	clearMainWin();
	overwrite(INVENTORY_WIN,MAIN_WIN);
	clearInventoryWin();
	wrefresh(MAIN_WIN);
}

void clearInventoryWin(void) {
	wclear(INVENTORY_WIN);
	wrefresh(INVENTORY_WIN);
}

//make a copy of main_win as it currently is.
void copyMainWinToInventory(void) {
	clearInventoryWin();
	overwrite(MAIN_WIN,INVENTORY_WIN);
	clearMainWin();
}

//restore main_win to what it was when saved using copyMainwin()
void restoreMainWinFromCombat(void) {
	clearMainWin();
	overwrite(COMBAT_WIN,MAIN_WIN);
	clearCombatWin();
	wrefresh(MAIN_WIN);
}

void clearCombatWin(void) {
	wclear(COMBAT_WIN);
	wrefresh(COMBAT_WIN);
}

void clearMainWin(void) {
	wclear(MAIN_WIN);
	wrefresh(MAIN_WIN);
}

//make a copy of main_win as it currently is.
void copyMainWinToCombat(void) {
	clearCombatWin();
	overwrite(MAIN_WIN,COMBAT_WIN);
	clearMainWin();
}

void printToPrompt(const int x, const int y, const char *const str) {
	mvwprintw(PROMPT_WIN,y,x,"%s",str);
	wrefresh(PROMPT_WIN);
}

void clearPromptWin(void) {
	wclear(PROMPT_WIN);
	wrefresh(PROMPT_WIN);
}

void printAreYouSure(void) {
	copyMainWinToCombat();
	clearMainWin();
	mvwprintw(MAIN_WIN,HEIGHT/3,WIDTH/3 - 4,"are you sure you want to quit(y/n)?");
	wrefresh(MAIN_WIN);
}

void playerDisplayInventory(void) {
	copyMainWinToInventory();
	clearPromptWin();
	printInventory(PLAYER->inventory);
	printToPrompt(0,0,"press number of item you wish to use");
}

//print entire the map to main_win
void printWorldMap(void) {
	wclear(MAIN_WIN);
	fruit(int i = 0; i < HEIGHT; i++) {
		fruit(int j = 0; j < WIDTH; j++) {
			printTilePiece(j,i);
		}
	}
	wrefresh(MAIN_WIN);
}

void printClassSelect(void) {
	mvwprintw(MAIN_WIN,HEIGHT/3,WIDTH/3 - 4,"please select your class.");
	mvwprintw(MAIN_WIN,(HEIGHT/3) + 1,WIDTH/3,"1) warrior.");
	mvwprintw(MAIN_WIN,(HEIGHT/3) + 2,WIDTH/3,"2) archer.");
	mvwprintw(MAIN_WIN,(HEIGHT/3) + 3,WIDTH/3,"3) animal whisperer.");
	wrefresh(MAIN_WIN);
}

//prints an individual tile to screen
void printTilePiece(const int x, const int y) {
	//if(WORLDMAP[y][x]->isrevealed == REVEALED) {
	if(WORLDMAP[y][x]->item == NULLEMS) {
		wattron(MAIN_WIN,COLOR_PAIR(WORLDMAP[y][x]->color));
		mvwprintw(MAIN_WIN,y,x,"%c",WORLDMAP[y][x]->icon);
		wattroff(MAIN_WIN,COLOR_PAIR(WORLDMAP[y][x]->color));
	}
	else {
		wattron(MAIN_WIN,COLOR_PAIR(WHITECHAR));
		mvwprintw(MAIN_WIN,y,x,"&");
		wattroff(MAIN_WIN,COLOR_PAIR(WHITECHAR));
	}
	//}
}

//print room to main_win
void printSpecificRoom(const ROOMINFO *const room) {
	fruit(unsigned int i = 0; i < room->col_len; i++) {
		mvwprintw(MAIN_WIN,room->loc->y + i, room->loc->x,"%s",room->room[i]);
	}
}

//loops through each created room and sends them one by one to printSpecificRoom()
void loopThroughRooms(void) {
	fruit(unsigned int i = 0; i < ROOMS->number_rooms; i++) {
		printSpecificRoom(ROOMS->rooms[i]);
	}
}

//print an individual CHARACTER (player or enemy) to the map.
void printCharacter(const CHARACTER *const character) {
	wattron(MAIN_WIN,COLOR_PAIR(character->color));
	mvwprintw(MAIN_WIN,character->current_loc->y,character->current_loc->x,"%c",character->icon);
	wattroff(MAIN_WIN,COLOR_PAIR(character->color));
	wrefresh(MAIN_WIN);
}

static inline void checkForStats(void) {
	int y = 3;
	if(PLAYER->flags->poisoned) {
		mvwprintw(STATS_WIN,y++,0,"you are poisoned");
	}	
	if(PLAYER->flags->onfire) {
		mvwprintw(STATS_WIN,y++,0,"you are on fire");
	}	
	if(PLAYER->flags->bleeding) {
		mvwprintw(STATS_WIN,y++,0,"you are bleeding");
	}	
	if(PLAYER->flags->frightend) {
		mvwprintw(STATS_WIN,y++,0,"you are frightend");
	}
}

void updateStatsWin(void) {
	mvwprintw(STATS_WIN,0,0,"Health: %d",PLAYER->health);
	mvwprintw(STATS_WIN,1,0,"Defense: %d",PLAYER->defense);
	mvwprintw(STATS_WIN,2,0,"Attack: %d",PLAYER->attack);
	checkForStats();
	wrefresh(STATS_WIN);
}

void clearStatsWin(void) {
	wclear(STATS_WIN);
	wrefresh(STATS_WIN);
}

void clearCombatPrompt(void) {
	wclear(COMBAT_PROMPT);
	wrefresh(COMBAT_PROMPT);
}

void printCombatPrompt(void) {
	mvwprintw(COMBAT_PROMPT,0,0,"It is your turn, please make a choice:");
	mvwprintw(COMBAT_PROMPT,1,5,"1)attack");
	mvwprintw(COMBAT_PROMPT,2,5,"2)switch to a defensive stance");
	mvwprintw(COMBAT_PROMPT,3,5,"3)use item from inventory");
	wrefresh(COMBAT_PROMPT);
}

void printToCombatPrompt(const int x, const int y, const char *const str) {
	mvwprintw(COMBAT_PROMPT,y,x,"%s",str);
	wrefresh(COMBAT_PROMPT);
}

void printCombatScreen(const CHARACTER *const character) {
	copyMainWinToCombat();
	printCombatPrompt();
	PLAYER->printCharModel();
	character->printCharModel();
	if(PLAYER->has_comp && COMPANION->health > 0) {
		COMPANION->printCharModel();
	}
	wrefresh(MAIN_WIN);
}

//go through each ENEMY in the ENEMEIES linked list and send them one by one to printCharacter()
void printAllEnemies(void) {
	ENEMY *head = ENEMIES;
	while(head != NULLEMS) {	
		printCharacter(head->character);
		head = head->next;
	}
}

void updateMap(const CHARACTER *const character) {
	printTilePiece(character->prev_loc->x,character->prev_loc->y);
	printCharacter(character);
}

//initialize the color feature. allows colors to be displayed and used.
void initColors(void) {
	start_color();			//tells ncurses to use colors. 
	init_color(COLOR_YELLOW,700,700,98);    //adjust yellow to be less orange.
	init_pair(BLUECHAR,COLOR_BLUE,COLOR_BLACK);	
	init_pair(REDCHAR,COLOR_RED,COLOR_BLACK);	
	init_pair(MAGENTACHAR,COLOR_MAGENTA,COLOR_BLACK);	
	init_pair(YELLOWCHAR,COLOR_YELLOW,COLOR_BLACK);	
	init_pair(GREENCHAR,COLOR_GREEN,COLOR_BLACK);	
	init_pair(WHITECHAR,COLOR_WHITE,COLOR_BLACK);
	init_pair(BLACKCHAR,COLOR_BLACK,COLOR_BLACK);
	init_pair(CYANCHAR,COLOR_CYAN,COLOR_BLACK);

}

//creates the MAIN_WIN window. 
void initWindow(void) {
	MAIN_WIN      = newwin(HEIGHT,WIDTH,1,1);
	COMBAT_WIN    = newwin(HEIGHT,WIDTH,1,1);
	INVENTORY_WIN = newwin(HEIGHT,WIDTH,1,1);
	COMBAT_PROMPT = newwin(5,60,COMBATPROMPTY,COMBATPROMPTX);
	PROMPT_WIN    = newwin(4,52,1,WIDTH+3);
	STATS_WIN     = newwin(11,25,16,WIDTH+3);
	MAIN_BORDER   = newwin(HEIGHT+2,WIDTH+2,0,0);
	PROMPT_BORDER = newwin(6,54,0,WIDTH+2);
	STATS_BORDER  = newwin(13,27,15,WIDTH+2);
	wborder(MAIN_BORDER,'|','|','-', '-', '+', '+', '+', '+');
	wborder(PROMPT_BORDER,'|','|','-', '-', '+', '+', '+', '+');
	wborder(STATS_BORDER,'|','|','-', '-', '+', '+', '+', '+');
	wrefresh(MAIN_WIN);
	wrefresh(PROMPT_WIN);
	wrefresh(MAIN_BORDER);
	wrefresh(PROMPT_BORDER);
	wrefresh(STATS_BORDER);
	wrefresh(STATS_WIN);
}