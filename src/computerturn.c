/*                                           ### description ###                       

*/

//---------------------------------------------- headers -------------------------------------------------
#include "computerturn.h"
//---------------------------------------------- define --------------------------------------------------

//---------------------------------------------- enums ---------------------------------------------------


//---------------------------------------------- typedefs ------------------------------------------------


//---------------------------------------------- structs -------------------------------------------------


//---------------------------------------------- global vars ---------------------------------------------
static const size_t SIZE_ENEMY = sizeof(ENEMY);

//---------------------------------------------- prototypes ----------------------------------------------
static void characterTurn(CHARACTER *const character);

//---------------------------------------------- code ----------------------------------------------------

static void characterTurn(CHARACTER *const character) {
	if(moveCharacter(getNextMovement(character),character) == 0) {
		while(moveCharacter(rand() % 4,character) == 0);
	}
}

void computerTurn(void) {
	ENEMY *temp = malloc(SIZE_ENEMY);
	temp        = ENEMIES;
	while(temp != NULL) {
		if(WORLDMAP[temp->character->current_loc->y][temp->character->current_loc->x]->isrevealed == REVEALED) {
			characterTurn(temp->character);
		}
		temp = temp->next;
	}
	free(temp);
}