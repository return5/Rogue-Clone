/*                                           ### description ###                       
	controls moveing character around map.  starting at move charater, it checks if the move is valid, that is
	if the location character wants to move to is a valid one, that is the tile is apath, inside a room, or a door.
	if it is valid, character location is updated.  functions return 1 or 0 to indicate success or failure. 
*/

//---------------------------------------------- headers -------------------------------------------------
#include "movement.h"

//---------------------------------------------- prototypes ----------------------------------------------
static int   checkValidPiece     (const int x, const int y);
static int   checkIfValidMove    (const MOVEMENT next_move,const int x,const int y);
//---------------------------------------------- code ----------------------------------------------------


static int checkValidPiece(const int x, const int y) {
	switch(WORLDMAP[y][x]->icon) {
		case '#':
		case '.':
		case '%'://FALLTHROUGH
			return 1;
		default:
			return 0;
	}
}

static int checkIfValidMove(const MOVEMENT next_move,const int x,const int y) {
	switch(next_move) {
		case UP:
			return checkValidPiece(x,y - 1);
		case DOWN:
			return checkValidPiece(x,y + 1);
		case LEFT:
			return checkValidPiece(x - 1,y);
		case RIGHT:
			return checkValidPiece(x + 1,y);
		default:
			return 0;	
	}
}

int moveCharacter(const MOVEMENT next_move,CHARACTER *const character) {
	if(checkIfValidMove(next_move,character->loc->x,character->loc->y)) {
		switch(next_move) {
		case UP   :
			character->loc->y -= 1;
			character->prev_move = next_move;
			return 1;
		case DOWN :
			character->loc->y += 1;
			character->prev_move = next_move;
			return 1;
		case LEFT :
			character->loc->x -= 1;
			character->prev_move = next_move;
			return 1;
		case RIGHT:
			character->loc->x += 1;
			character->prev_move = next_move;
			return 1;
		default:
			return 0;
		}
	}
	return 0;
}
