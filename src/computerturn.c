/*                                           ### description ###                       

*/

//---------------------------------------------- headers -------------------------------------------------
#include "computerturn.h"
//---------------------------------------------- define --------------------------------------------------

//---------------------------------------------- enums ---------------------------------------------------


//---------------------------------------------- typedefs ------------------------------------------------


//---------------------------------------------- structs -------------------------------------------------


//---------------------------------------------- global vars ---------------------------------------------

//---------------------------------------------- prototypes ----------------------------------------------
static void characterTurn(CHARACTER *const character);

//---------------------------------------------- code ----------------------------------------------------

static void characterTurn(CHARACTER *const character) {
	if(checkIfEnemy()) {
		engageCombat(character);
	}
	else {
		if(moveCharacter(getNextMovement(character),character) == 0) {
			while(moveCharacter(rand() % 4,character) == 0);
		}
		if(checkIfEnemy()) {
			engageCombat(character);
		}
	}
}

void computerTurn(void) {
	ENEMY *temp = ENEMIES;
	while(temp != NULLEMS) {
		//if(WORLDMAP[temp->character->current_loc->y][temp->character->current_loc->x]->isrevealed == REVEALED) {
			characterTurn(temp->character);
		//}
		temp = temp->next;
	}
}