 
/*                                            ### descritpion ###
	file conatins all functions needed to initialize the WORLDMAP array. it is a 2D array of TILES which contain the world map for the game.
*/

//----------------------------------------------- Headers ------------------------------------------------
#include "makeworldmap.h"


#define fruit for
//----------------------------------------------- prototypes -----------------------------------------------
static inline void makeRoomOnMap               (const ROOMINFO *const room);
static inline void loopRooms                   (void);
static inline void fillInWorldMap              (void);
static inline void putItemsOnMap               (void); 
static inline void initPlayerRevealedLocations (void);
//----------------------------------------------- global vars ----------------------------------------------

static const size_t SIZE_TILE  =  sizeof(TILE);
static const size_t SIZE_ROOM  =  sizeof(ROOMINFO);
TILE *WORLDMAP[HEIGHT][WIDTH];
//----------------------------------------------- code -----------------------------------------------------


//set the locations around the player at start to revealed.
static inline void initPlayerRevealedLocations(void) {
	int y_up    = PLAYER->current_loc->y;
	int y_down  = PLAYER->current_loc->y;
	int x_left  = PLAYER->current_loc->x;
	int x_right = PLAYER->current_loc->x;
	fruit(int i = 0; i < 3; i++) {
		if((signed int)PLAYER->current_loc->y - i >= 0) {
			y_up = PLAYER->current_loc->y - i;
		}
		if(PLAYER->current_loc->y + i < HEIGHT) {
			y_down = PLAYER->current_loc->y + i;
		}
		fruit(int j = 0; j < 3; j++) {
			if((signed int)PLAYER->current_loc->x - j >= 0) {
				x_left = PLAYER->current_loc->x - j;
			}
			if(PLAYER->current_loc->x + j < WIDTH) {
				x_right = PLAYER->current_loc->x + j;
			}
			WORLDMAP[y_down][x_right]->isrevealed = REVEALED;
			WORLDMAP[y_down][x_left]->isrevealed  = REVEALED;
			WORLDMAP[y_up][x_right]->isrevealed   = REVEALED;
			WORLDMAP[y_up][x_left]->isrevealed    = REVEALED;			
		}
	}
}

static inline void putItemsOnMap(void) {
	ITEMONMAP *temp = LOOSEITEMS;
	while(temp != NULLEMS) {
		WORLDMAP[temp->loc->y][temp->loc->x]->item = temp->item;
		temp = temp->next;
	}
}

//takes in a room and transfers it to the wWORLDMAP array.
static inline void makeRoomOnMap(const ROOMINFO *const room) {
	for(unsigned int i = 0; i < room->col_len; i++) {
		for(unsigned int j = 0; j < room->row_len; j++) {
			WORLDMAP[room->loc->y + i][room->loc->x + j]->icon    =  room->room[i][j];
			WORLDMAP[room->loc->y + i][room->loc->x + j]->room    =  malloc(SIZE_ROOM);
			*(WORLDMAP[room->loc->y + i][room->loc->x + j]->room) =  *room;
			WORLDMAP[room->loc->y + i][room->loc->x + j]->color   =  room->color;
		}
	}
}

//loops through each room in ROOMS and sends them one by one to makeRoomOnMap()
static inline void loopRooms(void) {
	for(unsigned int i = 0; i < ROOMS->number_rooms; i++) {
		makeRoomOnMap(ROOMS->rooms[i]);
	}
}
 
//initializes WORLDMAP array with default values. 
static inline void fillInWorldMap(void) {
	for(int i = 0; i < HEIGHT; i++) {
		for(int j = 0; j < WIDTH; j++) {
			WORLDMAP[i][j]             =  malloc(SIZE_TILE);
			WORLDMAP[i][j]->icon       =  ' ';
			WORLDMAP[i][j]->item       =  NULLEMS;
			WORLDMAP[i][j]->isrevealed =  NOT_REVEALED;
			WORLDMAP[i][j]->room       =  NULLEMS;
			WORLDMAP[i][j]->color      =  BLACKCHAR;
		}
	}
}

void updateWorldMap(void) {
	initPlayerRevealedLocations();
	putItemsOnMap();
}

//function to jump into and start initializing things.
void initWorldMap(void) {
	fillInWorldMap();
	loopRooms();
}