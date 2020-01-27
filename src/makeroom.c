/*                                     ### descritpion ###
	makes each individual room which is on the map. starts in makeRooms(). 
	that intializes ROOM which is a struct which contains an array to contain each room, and the number of rooms in total.
	number of rooms is randomly generated each time makeRooms() is run. the makeRoomInfo() function is run for each room and stored as an element in ROOM array.
	makeRoomInfo() makes an individual room. the shape of room is randomly selected form those in the rooms.h file. the color of the room is also randomly chosen.
	location of each room is randomly selected. when selecting room location it is checked against all other rooms previously created to make sure the room doesnt overlap with another. 
*/

//---------------------------------------- headers --------------------------------------------------
#include "makeroom.h"

//---------------------------------------- prototypes ---------------------------------------------
static  ROOMINFO      *makeRoomInfo        (const unsigned int num_created);
static  ROOMROW        getRoomRow          (NUMROOMS room_num);
static  ROOMCOL        getRoomCol          (NUMROOMS room_num);
static  size_t         getSizeRoom         (NUMROOMS room_num);
static  char           **getRoomAr         (NUMROOMS room_num);
static  unsigned int   checkIfOverlap      (const unsigned int x, const unsigned int y, const unsigned int num_created,const unsigned int row,const unsigned int col);
static  RLOCATION      *makeRanLocation    (const unsigned int num_created,const unsigned int row,const unsigned int col);
static  unsigned int   checkXInside        (const unsigned int x, const unsigned int row, const unsigned int i);
static  unsigned int   checkYInside        (const unsigned int y, const unsigned int col, const unsigned int i);
static  unsigned int   checkYAboveAndBelow (const unsigned int y, const unsigned int col, const unsigned int i);
static  unsigned int   checkXLeftAndRight  (const unsigned int x, const unsigned int row, const unsigned int i);
static  WHAT_COLOR     getColor            (void);

//---------------------------------------- global vars ----------------------------------------------
static const size_t SIZE_ROOMINFO   =   sizeof(ROOMINFO);
static const size_t SIZE_RLOCATION  =   sizeof(RLOCATION);
static const size_t SIZE_ROOM1      =   sizeof(ROOM1);
static const size_t SIZE_ROOM2      =   sizeof(ROOM2);
static const size_t SIZE_ROOM3      =   sizeof(ROOM3);
static const size_t SIZE_ROOM4      =   sizeof(ROOM4);
static const int    MIN_NUM         =   4;
static const int    MAX_NUM         =   NUM_ROOMS;

ROOMSARRAY *ROOMS;

//---------------------------------------- code -----------------------------------------------------

//is the x coordinate of either left or right side of new room inside the x coordinates of a previous rom
static unsigned int checkXInside(const unsigned int x, const unsigned int row, const unsigned int i) {
	if(x >= ROOMS->rooms[i]->loc->x && x <= (ROOMS->rooms[i]->loc->x + ROOMS->rooms[i]->row_len)) {
		return 1;
	}
	else if((x + row)>= ROOMS->rooms[i]->loc->x && (x + row)<= (ROOMS->rooms[i]->loc->x + ROOMS->rooms[i]->row_len)) {
		return 1;
	}
	return 0;
}

//is the y coordinate of either top or bottom of a new room inside the y coordinates of a previous room
static unsigned int checkYInside(const unsigned int y, const unsigned int col, const unsigned int i) {
	if(y >= ROOMS->rooms[i]->loc->y && y <= (ROOMS->rooms[i]->loc->y + ROOMS->rooms[i]->col_len)) {
		return 1;
	}
	else if((y + col)>= ROOMS->rooms[i]->loc->y && (y + col)<= (ROOMS->rooms[i]->loc->y + ROOMS->rooms[i]->col_len)) {
		return 1;
	}
	return 0;
}

//is upper corner above upper corner of previous room and also lower corner below lower corner of previous room
static unsigned int checkYAboveAndBelow(const unsigned int y, const unsigned int col, const unsigned int i) {
	if(y <= ROOMS->rooms[i]->loc->y && (y + col) >= (ROOMS->rooms[i]->loc->y + ROOMS->rooms[i]->col_len)) {
		return 1;
	}
	return 0;
}
//if upper left corner of new room is to the left of previous room and also upper right of new room is to the right of previous room return 1
static unsigned int checkXLeftAndRight(const unsigned int x, const unsigned int row, const unsigned int i) {
	if(x <= ROOMS->rooms[i]->loc->x && (x + row) >= (ROOMS->rooms[i]->loc->x + ROOMS->rooms[i]->row_len)) {
		return 1;
	}
	return 0;
}

//checks if new room will overlap with a previous room, if so, return 1, otherwise return 0
static unsigned int checkIfOverlap(const unsigned int x, const unsigned int y, const unsigned int num_created,const unsigned int row,const unsigned int col) {
	for(unsigned int i = 0; i < num_created; i++) {
		//if x and y locations are inside of a previously made room return 1
		if(checkXInside(x,row,i) && checkYInside(y,col,i)) {
			return 1;
		}
		else if(checkXLeftAndRight(x,row,i) && checkYInside(y,col,i)) {
			return 1;
		}
		else if(checkYAboveAndBelow(y,col,i) && checkXInside(x,row,i)) {
			return 1;
		}
		else if(checkYAboveAndBelow(y,col,i) && checkXLeftAndRight(x,row,i)) {
			return 1;
		}
	}
	return 0;
}

//get random color for that room.
static WHAT_COLOR getColor(void) {
	switch((rand() % 7) +1) {  
		case BLUE   : return BLUE;
		case RED    : return RED;
		case MAGENTA: return MAGENTA;
		case YELLOW : return YELLOW;
		case GREEN  : return GREEN;
		case WHITE  : return MAGENTA;
		case CYAN   : return CYAN;
		default     : return GREEN;
	}

}

//get the width of the room (row length)
static ROOMROW getRoomRow(NUMROOMS room_num) {
	switch(room_num) {
		case R1: 		return ROWR1;
		case R2: 		return ROWR2;
		case R3:		return ROWR3;
		case R4:        return ROWR4;
		case R5:        return ROWR1;
		case R6:        return ROWR2;
		case R7:        return ROWR1;
		case NUM_ROOMS: return 0;
		default:        return 0;		
	}
}

//get hieght of the room (column length)
static ROOMCOL getRoomCol(NUMROOMS room_num) {
	switch(room_num) {
		case R1: 		return COLR1;
		case R2: 		return COLR2;
		case R3:		return COLR3;
		case R4:        return COLR4;
		case R5:        return COLR1;
		case R6:        return COLR2;
		case R7:        return COLR1;
		case NUM_ROOMS: return -1;
		default:        return 0;
	}
}

//get the size of the room array.
static size_t getSizeRoom(NUMROOMS room_num) {
	switch(room_num) {
		case R1: 		return SIZE_ROOM1;
		case R2: 		return SIZE_ROOM2;
		case R3:		return SIZE_ROOM3;
		case R4:        return SIZE_ROOM4;
		case R5:        return SIZE_ROOM1;
		case R6:        return SIZE_ROOM2;
		case R7:        return SIZE_ROOM1;
		case NUM_ROOMS: return 0;
		default:        return 0;	
	}
}

//gets the correct array for that room number
static char **getRoomAr(NUMROOMS room_num) {
	switch(room_num) {
		case R1: 		return ROOM1;
		case R2: 		return ROOM2;
		case R3:		return ROOM3;
		case R4:        return ROOM4;
		case R5:        return ROOM1;
		case R6:        return ROOM2;
		case R7:        return ROOM1;
		case NUM_ROOMS: return NULL;
		default:        return NULL;	
	}	
}


//get a random location to place the room at. 
static RLOCATION *makeRanLocation(const unsigned int num_created,const unsigned int row,const unsigned int col) {
	RLOCATION *loc  =  malloc(SIZE_RLOCATION);
	do {
		loc->x  =  rand() % (WIDTH - row);  //sub row_len to makes sure there is space to fit room
		loc->y  =  rand() % (HEIGHT - col);  //sub col_len to make sure there is space to fit room
	}while(checkIfOverlap(loc->x,loc->y,num_created,row,col) == 1);
	return loc;
}

//make an individual room. fill in all needed data.
static ROOMINFO *makeRoomInfo(const unsigned int num_created) {
	ROOMINFO *room               =  malloc(SIZE_ROOMINFO);
	const unsigned int rand_var  =  rand() % NUM_ROOMS;
	room->col_len                =  getRoomCol(rand_var);
	room->row_len                =  getRoomRow(rand_var);
	room->room                   =  malloc(getSizeRoom(rand_var));
	room->loc                    =  makeRanLocation(num_created,room->row_len,room->col_len);
	room->color                  =  getColor();
	memcpy(room->room,getRoomAr(rand_var),getSizeRoom(rand_var));  //copy the room char array from room.h into the ROOMINFO struct for that room
	return room;
}

//select a random number and make that many rooms on the map.
void makeRooms(void) {
	srand(time(0));
	ROOMS                =  malloc(sizeof(ROOMSARRAY));
	ROOMS->number_rooms  =  (rand() % (MAX_NUM - MIN_NUM)) + MIN_NUM;
	ROOMS->rooms         =  malloc(SIZE_ROOMINFO * ROOMS->number_rooms);

	for(unsigned int i = 0; i < ROOMS->number_rooms; i++) {	
		ROOMS->rooms[i]  =  makeRoomInfo(i);
	}
	
}