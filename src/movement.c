/*                                           ### description ###                       
	controls moving character around map.  starting at move charater, it checks if the move is valid, that is
	if the location character wants to move to is a valid one, that is the tile is a path, inside a room, or a door.
	if it is valid, character location is updated.  functions return 1 or 0 to indicate success or failure. 
*/

//---------------------------------------------- headers -------------------------------------------------
#include "movement.h"
//---------------------------------------------- prototypes ----------------------------------------------
static inline int   checkIfValidMove    (const MOVEMENT next_move,const int x,const int y);
static        int   updateCharacterLoc  (const MOVEMENT next_move,CHARACTER *const character);
static inline int   checkValidPiece     (const int x, const int y);
//---------------------------------------------- code ----------------------------------------------------

//computer players get their next movement direction here. they move towards player if they can.
MOVEMENT getNextMovement(const CHARACTER *const character) {
	if(character->current_loc->y > PLAYER->current_loc->y && checkIfValidMove(UP,character->current_loc->x,character->current_loc->y)) {
		return UP;
	}
	else if(character->current_loc->y < PLAYER->current_loc->y && checkIfValidMove(DOWN,character->current_loc->x,character->current_loc->y)) {
		return DOWN;
	}

	else if(character->current_loc->x > PLAYER->current_loc->x && checkIfValidMove(LEFT,character->current_loc->x,character->current_loc->y)) {
		return LEFT;		
	}

	else if(character->current_loc->x < PLAYER->current_loc->x && checkIfValidMove(RIGHT,character->current_loc->x,character->current_loc->y)) {
		return RIGHT;		
	}
	else {
		return NO_MOVE;		
	}
}

//is the location the character is trying to move to a valid title to move to?
static inline int checkValidPiece(const int x, const int y) {
	if( y >= 0 && y < HEIGHT && x < WIDTH && x >= 0) {
		switch(WORLDMAP[y][x]->icon) {
			case '#':
			case '.':
			case '%'://FALLTHROUGH
				return 1;
			default:
				return 0;
		}
	}
	return 0;
}

//checks the tile in the direction character is trying to move to.
static inline int checkIfValidMove(const MOVEMENT next_move,const int x,const int y) {
	switch(next_move) {
		case UP:
			return checkValidPiece(x,y - 1);
		case DOWN:
			return checkValidPiece(x,y + 1);
		case LEFT:
			return checkValidPiece(x - 1,y);
		case RIGHT:
			return checkValidPiece(x + 1,y);
		case NO_MOVE:
			return 0;
		default:
			return 0;	
	}
}

static int updateCharacterLoc(const MOVEMENT next_move,CHARACTER *const character) {
	if(checkIfValidMove(next_move,character->current_loc->x,character->current_loc->y)) {
		switch(next_move) {
		case UP   :
			*(character->prev_loc)     =  *(character->current_loc);
			character->current_loc->y -= 1;
			character->prev_move       = next_move;
			return 1;
		case DOWN :
			*(character->prev_loc)     =  *(character->current_loc);
			character->current_loc->y += 1;
			character->prev_move       = next_move;
			return 1;
		case LEFT :
			*(character->prev_loc)     =  *(character->current_loc);		
			character->current_loc->x -=  1;
			character->prev_move       =  next_move;
			return 1;
		case RIGHT:
			*(character->prev_loc)     =  *(character->current_loc);
			character->current_loc->x +=  1;
			character->prev_move       =  next_move;
			return 1;
		case NO_MOVE:
			return 0;
		default:
			return 0;
		}
	}
	return 0;
}
int moveCharacter(const MOVEMENT next_move,CHARACTER *const character) {
	if(updateCharacterLoc(next_move,character) == 1) {
		updateMap(character);
		return 1;
	}
	return 0;
}
