 
/*                                            ### descritpion ###
	file conatins all functions needed to initialize the WORLDMAP array. it is a 2D array of TILES which contain the world map for the game.
*/

//----------------------------------------------- Headers ------------------------------------------------
#include "makeworldmap.h"

//----------------------------------------------- prototypes -----------------------------------------------
static void makeRoomOnMap  (const ROOMINFO *const room);
static void loopRooms      (void);
static void fillInWorldMap (void);

//----------------------------------------------- global vars ----------------------------------------------

static const size_t SIZE_TILE  =  sizeof(TILE);
static const size_t SIZE_ROOM  =  sizeof(ROOMINFO);
TILE *WORLDMAP[HEIGHT][WIDTH];
//----------------------------------------------- code -----------------------------------------------------

//takes in a room and transfers it to the wWORLDMAP array.
static void makeRoomOnMap(const ROOMINFO *const room) {
	for(unsigned int i = 0; i < room->col_len; i++) {
		for(unsigned int j = 0; j < room->row_len; j++) {
			WORLDMAP[room->loc->y + i][room->loc->x + j]->icon    =  room->room[i][j];
			WORLDMAP[room->loc->y + i][room->loc->x + j]->room =  malloc(SIZE_ROOM);
			*(WORLDMAP[room->loc->y + i][room->loc->x + j]->room) =  *room;
			WORLDMAP[room->loc->y + i][room->loc->x + j]->color   =  room->color;
		}
	}
}

//loops through each room in ROOMS and sends them one by one to makeRoomOnMap()
static void loopRooms(void) {
	for(unsigned int i = 0; i < ROOMS->number_rooms; i++) {
		makeRoomOnMap(ROOMS->rooms[i]);
	}
}
 
//initializes WORLDMAP array with default values. 
static void fillInWorldMap(void) {
	for(int i = 0; i < HEIGHT; i++) {
		for(int j = 0; j < WIDTH; j++) {
			WORLDMAP[i][j]             =  malloc(SIZE_TILE);
			WORLDMAP[i][j]->icon       =  ' ';
			WORLDMAP[i][j]->isrevealed =  NOT_REVELEAD;
			WORLDMAP[i][j]->room       =  NULL;
			WORLDMAP[i][j]->color      =  BLACK;
		}
	}
}

//function to jump into and start initializing things.
void initWorldMap(void) {
	fillInWorldMap();
	loopRooms();
}