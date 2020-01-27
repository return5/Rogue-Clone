
/*                                    ### descrption ###
	This file makes a path between rooms on the map.  it starts with makePassages() which assignes a random number of paths to be started at that room. 
	it then randomly selects another room and starts the process of building a path there.it does this for each room. the next step is in buildPath().
	the process of building a path is to start at current location. the start of the path is a door, indicated by a '5'. the next step is to check if up,down,left,and right are valid(they dont run off map, nor do they run into a room).
	if the move is valid,it is stored in the array in the directions struct as a collection of all valid moves for that location. the next step is getNextPath();
	getNextPath looks through the list of valid directions combined with the direction the path needs to go and selects a lcoation ofr the next piece of the path. 
	to keep it a bit random, each move, if valid, has a 2/3 chance of being the next path. the next path is then printed to map. 
	the while loop in buildPath runs until either the path conects with the correct room, or it loops through 120 + START_OVER times, at which point i consider it a failure and the process starts over. 
	in an attempt to keep path generation form looping forever, each start over increases the possible length of a path before it has to start over

*/

//---------------------------------------- Headers --------------------------------------------------
#include "makepath.h"

//----------------------------------------------- prototypes -----------------------------------------------
static  int            pickYCoordinate       (const int i);
static  int            pickXCoordinate       (const int i);
static  int            checkNewLocation      (const int x,     const int y);
static  PATHLOCATION  *getNextPath       (const DIRECTIONS *const dir,  const PATHLOCATION *const path, const unsigned int end_x, const unsigned int end_y);
static  int            checkIfPathConnects   (const unsigned int x, const unsigned int y, const unsigned int end_i);
static  int            checkIfValid          (const int new_x,const int new_y,const int end_i);
static  DIRECTIONS     *getValidMoves        (const PATHLOCATION *const path,const int end_i);
static  void           pathRandomDirection   (const DIRECTIONS *const dir, PATHLOCATION *const path); 
static  int            isValidMove           (const DIRECTIONS *const dir, MOVEPATH direction); 
static  int            buildPath             (const PATHLOCATION  *const start,const int end_i);
static  int            checkIfInBounds       (const int x,     const int y);    
static  int             isPreviousMoveValid   (const DIRECTIONS *const dir,const PATHLOCATION *const path, const int unsigned end_x,const unsigned int end_y);
static  PATHLOCATION   *repeatPreviousMove    (PATHLOCATION *const new_path);
static  void           startOver             (void);
static  int            checkIfPrevious       (const int j, const int rom_connect,int *const previous);
static  int            chooseEndOfPath       (const int i, const int j, int *const previous);

//---------------------------------------- global vars ----------------------------------------------

static const size_t        SIZE_PATHLOCATION  =  sizeof(PATHLOCATION);
static const size_t        SIZE_DIRECTIONS    =  sizeof(DIRECTIONS);
             unsigned int  START_OVER         =  0;       //counts the number of times it starts over

//---------------------------------------- code ----------------------------------------------------

//checks if new location is within map bounds
static int checkIfInBounds(const int x, const int y) {
	if(x < 0 || x >= WIDTH) {
		return 0;
	}
	if(y < 0 || y >= HEIGHT) {
		return 0;
	}
	return 1;
}

//checks if next location is a valid one, that is it isnt located inside a room. 
static int checkNewLocation(const int x, const int y) {
	switch(WORLDMAP[y][x]->icon) {
		case '#': //FALLTHRU
		case ' ': return 0;
		default : return 1;
	}
}

//checks if path connects with the outside of the correct room.
static int checkIfPathConnects(const unsigned int x, const unsigned int y, const unsigned int end_i) {
	if(WORLDMAP[y][x]->icon == '+') {
		return 0;
	}

	if(x >= ROOMS->rooms[end_i]->loc->x && x <= (ROOMS->rooms[end_i]->loc->x + ROOMS->rooms[end_i]->row_len - 1) && y >= ROOMS->rooms[end_i]->loc->y && y <= (ROOMS->rooms[end_i]->loc->y + ROOMS->rooms[end_i]->col_len - 1)) {
		return 1;
	}

	 return 0;

}

//checks if the next possible move would be valid. 
static int checkIfValid(const int new_x,const int new_y,const int end_i) {
	if(checkIfInBounds(new_x,new_y) &&(!checkNewLocation(new_x,new_y) || checkIfPathConnects(new_x,new_y,end_i))) {
		return 1;
	}
	return 0;
}

//fills the DIRECTIONS struct with all possible valid moves. 
static DIRECTIONS *getValidMoves(const PATHLOCATION *const path,const int end_i) {
	DIRECTIONS *valid_dir = malloc(SIZE_DIRECTIONS);
	valid_dir->num        = 0;
	if(checkIfValid(path->x + 0,path->y + 1,end_i)) {
		valid_dir->dir_array[valid_dir->num++] = MOVEDOWN;
	}
	if(checkIfValid(path->x + 0,path->y - 1,end_i)) {
		valid_dir->dir_array[valid_dir->num++] = MOVEUP;
	}
	if(checkIfValid(path->x - 1,path->y + 0,end_i)) {
		valid_dir->dir_array[valid_dir->num++] = MOVELEFT;
	}
	if(checkIfValid(path->x + 1,path->y + 0,end_i)) {
		valid_dir->dir_array[valid_dir->num++] = MOVERIGHT;
	}
	return valid_dir;
}

//loops through dir_array to see if direction is in it s a valid move for this path.
static int isValidMove(const DIRECTIONS *const dir, MOVEPATH direction) {
	for(int i = 0; i < dir->num; i++) {
		if(dir->dir_array[i] == direction) {
			return 1;
		}
	}
	return 0;
}

//gets a random direction from the dir_array in DIRECTIONS struct.
static void pathRandomDirection(const DIRECTIONS *const dir, PATHLOCATION *const path) {
	if(dir->num > 0 ){ 
		switch(dir->dir_array[rand() % dir->num]) {
				case MOVEDOWN:  
					path->y++;
					path->previous = MOVEDOWN;	
					break;
				case MOVEUP:    
					path->y--;
					path->previous = MOVEUP;	
					break;
				case MOVERIGHT: 
					path->x++; 
					path->previous = MOVERIGHT;	 
					break;
				case MOVELEFT:  
					path->x--;
					path->previous = MOVELEFT;	
					break;
				default: //do nothing
					break;

		}
	}
}

static int isPreviousMoveValid(const DIRECTIONS *const dir,const PATHLOCATION *const path, const int unsigned end_x,const unsigned int end_y){
	if(isValidMove(dir,path->previous)) {
		switch(path->previous) {
			case MOVEUP   : return (path->y > end_y - 5)? 1 : 0;
			case MOVEDOWN : return (path->y < end_y + 5)? 1 : 0;
			case MOVELEFT : return (path->x > end_x - 5)? 1 : 0;
			case MOVERIGHT:	return (path->x < end_x + 5)? 1 : 0;
			default       : return 0;	
		}
	}
	return 0;
}

static PATHLOCATION *repeatPreviousMove(PATHLOCATION *const new_path) {
	switch(new_path->previous) {
		case MOVEUP   : new_path->y--;
			break;
		case MOVEDOWN : new_path->y++;
			break;
		case MOVELEFT : new_path->x--;
			break;
		case MOVERIGHT:	new_path->x++;
			break;
		default: //do nothing
			break;	
	}
	return new_path;
}

//get the enxt path location for current path.
static PATHLOCATION *getNextPath(const DIRECTIONS *const dir, const PATHLOCATION *const path, const unsigned int end_x,const unsigned int end_y) {
	PATHLOCATION *new_path = malloc(SIZE_PATHLOCATION);
	*new_path           = *path;            //initialize new_path to current path.
	if(isPreviousMoveValid(dir,path,end_x,end_y)){
		if(rand() % 15 < 13 ) {
			return repeatPreviousMove(new_path);
		}
	}

	if(isValidMove(dir,MOVEDOWN) && path->y < end_y) {
		if(rand() % 3 < 2) {
			new_path->y++;
			new_path->previous = MOVEDOWN;
			return new_path;
		}
	}
	else if(isValidMove(dir,MOVEUP) && path->y > end_y) {
		if(rand() % 3 < 2) {
			new_path->y--;
			new_path->previous = MOVEUP;
			return new_path;
		}
	}
	if(isValidMove(dir,MOVELEFT) && path->x > end_x) {
		if(rand() % 3 < 2) {
			new_path->x--;
			new_path->previous = MOVELEFT;
			return new_path;
		}
	}
	else if(isValidMove(dir,MOVERIGHT) && path->x < end_x) {
		if(rand() % 3 < 2) {
			new_path->x++;
			new_path->previous = MOVERIGHT;
			return new_path;
		}
	}
	pathRandomDirection(dir,new_path);  //if none of those were valid or passed the 2/3 random chance, then get a random direction from dir_array
	return new_path;

}

//build the path one piece at a time. 
static int buildPath(const PATHLOCATION *const start,const int end_i) {
	DIRECTIONS *dir;
	PATHLOCATION  *path                 =  malloc(SIZE_PATHLOCATION);
	*path                               =  *start;		//init path to the start location
	WORLDMAP[start->y][start->x]->icon  =  '%';			 //start door. 	
	WORLDMAP[path->y][path->x]->color   =  WHITE;			
	const unsigned int end_x            =  ROOMS->rooms[end_i]->loc->x + (ROOMS->rooms[end_i]->row_len) / 2;  //middle x coordinate of the room where path will end
	const unsigned int end_y            =  ROOMS->rooms[end_i]->loc->y + (ROOMS->rooms[end_i]->col_len) / 2;  //middle y coordinate of room where path will end
	unsigned int count                  =  0;  //counter for counting number of times it loops
	while(checkIfPathConnects(path->x,path->y,end_i) == 0 && count < 100 + START_OVER) {
		dir = getValidMoves(path,end_i);
		path = getNextPath(dir,path,end_x,end_y);
		WORLDMAP[path->y][path->x]->icon = '#';
		WORLDMAP[path->y][path->x]->color = WHITE;
		count++;
	}
	WORLDMAP[path->y][path->x]->icon = '%';
	return (count >= 100 + START_OVER)? 0 : 1;	//if looped more than 150 times, return 0 to indicate failure. 
}

//pick where start door should be along y cordinate
static int pickYCoordinate(const int i) {
	return (rand() % (ROOMS->rooms[i]->col_len)) + ROOMS->rooms[i]->loc->y;
}

//pick where start door should be along the x-axis
static int pickXCoordinate(const int i) {
	return (rand() % (ROOMS->rooms[i]->row_len))  + ROOMS->rooms[i]->loc->x;
}

//checks to see if room pick for end of path has already previously been chosen, and if so, return 1
static int checkIfPrevious(const int j, const int room_connect,int *const previous) {
	for(int i = 0; i < j; i++) {
		if(previous[i] == room_connect) {
			return 1;
		}
	}
	return 0;
}

//pick a room at random to connect to.  keep picking a new room if it is the same as the onne start_door is at
static int chooseRoomEndPath(const int i) {
	int room_connect;
	do {
		room_connect = rand() % ROOMS->number_rooms;
	}while(room_connect == i);

	return room_connect;   //returns index number for room to conect to.
	
}
//pick room where the path will end
static int chooseEndOfPath(const int i, const int j, int *const previous) {
	int room_connect;
	do {
		room_connect = chooseRoomEndPath(i);
	}while(checkIfPrevious(j,room_connect,previous));
	previous[j] = room_connect;  //put chosen room as most recent element in previous array
	return room_connect;
}


//picks the starting location of the path by selecting a room at random. then selecting a location on the edge of that room for the start door.
static PATHLOCATION *pickStartLocation(const int i) {
	PATHLOCATION *loc = malloc(SIZE_PATHLOCATION);   //location of start door for path.
	if(rand() % 2 == 0) {
		loc->x = pickXCoordinate(i);
		loc->y = (rand() % 2 == 0) ? ROOMS->rooms[i]->loc->y : ROOMS->rooms[i]->loc->y + ROOMS->rooms[i]->col_len - 1;
	}
	else {
		loc->y = pickYCoordinate(i);
		loc->x = (rand() % 2 == 0) ? ROOMS->rooms[i]->loc->x : ROOMS->rooms[i]->loc->x + ROOMS->rooms[i]->row_len - 1;
	}
	switch(WORLDMAP[loc->y][loc->x]->icon) {
		case '-':
		case '|': return loc;
		default:  return pickStartLocation(i);  //if the location isnt an edge piece, try again.
	}
}

//start the process over again if the loop was a failure. 
static void startOver(void) {
		START_OVER += 20;
		initWorldMap();
		makePassages();
}

//start making paths. for each room assign a random number of paths to start there then connect them to a randomly selected room.
int makePassages(void) {
	if (START_OVER < 100) {  //if process hasnt been tried more than 4 times, then try to make some paths.
		int *previous;  //holds list of previous rooms which has been connected to. 
		for(unsigned int i = 0; i < ROOMS->number_rooms; i++) { //for each room on map
			const unsigned int num_doors = (rand() % 2) + 1;       //assign random number of doors to start path on for each room
			previous                     = malloc(sizeof(int) * num_doors);	     //make it correct size to hold number of doors
			for(unsigned int j = 0; j < num_doors; j++) {	  //for each door in that room
				PATHLOCATION *start_loc = pickStartLocation(i);  //pick the starting location for the path
				int end_i               = chooseEndOfPath(i,j,previous);  //pick the room to end the path on.
				if (buildPath(start_loc,end_i) == 0) {          //if buildPath fails. 
					free(previous);
					startOver();
					break;
				}
			}
			free(previous);
		}
	}
	return START_OVER;  //return value of start over so the loop in main.c can decide if new map should be made or not.
}