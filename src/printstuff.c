/*                                   ### description ###

	file contains all functions needed to print to screen. also contains functions to initialize ncruses.
*/


//---------------------------------------- headers -----------------------------------------------
#include "printstuff.h"

//---------------------------------------- global vars ----------------------------------------------

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
	for(unsigned int i = 0; i < NUM_TYPE; i++) {
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
		case '3': return NULL;
		default: return itemUseOn();
	}
}

void printAttackScreen(const CHARACTER *const enemy) {
	copyMainWin();
	clearMainWin();
	if(PLAYER->has_comp == 1) {
		COMPANION->printCharModel();
	}
	PLAYER->printCharModel();
	enemy->printCharModel();
}

//restore main_win to what it was when saved using copyMainwin()
void restoreMainWin(void) {
	wclear(MAIN_WIN);
	overwrite(TEMP_WIN,MAIN_WIN);
	wrefresh(MAIN_WIN);
}

void clearMainWin(void) {
	wclear(MAIN_WIN);
	wrefresh(MAIN_WIN);
}

//make a copy of main_win as it currently is.
void copyMainWin(void) {
	wclear(TEMP_WIN);
	overwrite(MAIN_WIN,TEMP_WIN);
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
	copyMainWin();
	clearMainWin();
	mvwprintw(MAIN_WIN,HEIGHT/3,WIDTH/3 - 4,"are you sure you want to quit(y/n)?");
	wrefresh(MAIN_WIN);
}

void playerDisplayInventory(void) {
	copyMainWin();
	clearMainWin();
	clearPromptWin();
	printInventory(PLAYER->inventory);
	printToPrompt(0,0,"press number of item you wish to use");
}

//print entire the map to main_win
void printWorldMap(void) {
	wclear(MAIN_WIN);
	for(int i = 0; i < HEIGHT; i++) {
		for(int j = 0; j < WIDTH; j++) {
			wattron(MAIN_WIN,COLOR_PAIR(WORLDMAP[i][j]->color));
			mvwprintw(MAIN_WIN,i,j,"%c",WORLDMAP[i][j]->icon);
			wattroff(MAIN_WIN,COLOR_PAIR(WORLDMAP[i][j]->color));
		}
	}
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
	wattron(MAIN_WIN,COLOR_PAIR(WORLDMAP[y][x]->color));
	mvwprintw(MAIN_WIN,y,x,"%c",WORLDMAP[y][x]->icon);
	wattroff(MAIN_WIN,COLOR_PAIR(WORLDMAP[y][x]->color));
	wrefresh(MAIN_WIN);
}

//print room to main_win
void printSpecificRoom(const ROOMINFO *const room) {
	for(unsigned int i = 0; i < room->col_len; i++) {
		mvwprintw(MAIN_WIN,room->loc->y + i, room->loc->x,"%s",room->room[i]);
	}
}

//loops through each created room and sends them one by one to printSpecificRoom()
void loopThroughRooms(void) {
	for(unsigned int i = 0; i < ROOMS->number_rooms; i++) {
		printSpecificRoom(ROOMS->rooms[i]);
	}
}

//print an individual CHARACTER (player or enemy) to the map.
void printCharacter(const CHARACTER *const character) {
	wattron(MAIN_WIN,COLOR_PAIR(character->color));
	mvwprintw(MAIN_WIN,character->loc->y,character->loc->x,"%c",character->icon);
	wattroff(MAIN_WIN,COLOR_PAIR(character->color));
	wrefresh(MAIN_WIN);
}

//go through each ENEMY in the ENEMEIES linked list and send them one by one to printCharacter()
void printAllEnemies(void) {
	ENEMY *head = ENEMIES;
	while(head != NULL) {	
		printCharacter(head->character);
		head = head->next;
	}
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
	TEMP_WIN      = newwin(HEIGHT,WIDTH,1,1);
	PROMPT_WIN    = newwin(3,50,1,WIDTH+3);
	MAIN_BORDER   = newwin(HEIGHT+2,WIDTH+2,0,0);
	PROMPT_BORDER = newwin(5,52,0,WIDTH+2);
	wborder(MAIN_BORDER,'|','|','-', '-', '+', '+', '+', '+');
	wborder(PROMPT_BORDER,'|','|','-', '-', '+', '+', '+', '+');
	wrefresh(MAIN_WIN);
	wrefresh(PROMPT_WIN);
	wrefresh(MAIN_BORDER);
	wrefresh(PROMPT_BORDER);
}