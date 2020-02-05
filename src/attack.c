/*                                           ### description ###                       

*/

//---------------------------------------------- headers -------------------------------------------------
#include "attack.h"

//---------------------------------------------- prototypes ----------------------------------------------
static inline void   printCharRegularAttack    (const CHARTYPE type, const char *const defender_name);
static inline void   printCharReducedAttack    (const CHARTYPE type, const char *const defender_name);
static inline void   resetAttributes           (CHARACTER *const character);
static inline void   combatLoop                (CHARACTER *const character1, CHARACTER *const character2);
static inline void   removeEnemy               (CHARACTER *character);
static inline void   printCharTurn             (const CHARTYPE type);
static inline void   printCharAttack           (const char *const name);
static inline void   charTurn                  (CHARACTER *const attacker, CHARACTER *const defender);
static inline char   *playerRegularAttack      (const char *const defender_name);
static inline char   *playerReducedAttack      (const char *const defender_name);
static        int    dealDamage                (const CHARACTER *const attacker,CHARACTER *const defender,const int attack_offset,const int crit);
static        void   makeElectrocuted          (CHARACTER *const character);
static        void   makeBleeding              (CHARACTER *const defender);
static        void   makeFrightened            (CHARACTER *const defender);
static        int    regularAttack             (const CHARACTER *const attacker,const CHARACTER *const defender);
static        void   counterAttack             (CHARACTER *const attacker, const CHARACTER *const defender);
static        void   applyEffect               (CHARACTER *const defender,ATTACKTYPE type);
static        void   regularDamage             (CHARACTER *const attacker,CHARACTER *const defender,const int attack_offset,ATTACKTYPE attacktype);
static        int    switchToDefenseStance     (CHARACTER *const attacker);


//---------------------------------------------- define --------------------------------------------------

//---------------------------------------------- enums ---------------------------------------------------

//---------------------------------------------- typedefs ------------------------------------------------

//---------------------------------------------- structs -------------------------------------------------


//---------------------------------------------- global vars ---------------------------------------------

//---------------------------------------------- code ----------------------------------------------------

static inline char *playerRegularAttack(const char *const defender_name) {
	char *const c = malloc(43);
	switch(PLAYER_CLASS) {
		case WARRIOR       : 
			snprintf(c,42,"cleaves %s with their axe",defender_name);
			break;
		case PLAYER_ARCHER : 
			snprintf(c,42,"shot %s with an arrow",defender_name); 
			break;
		case ANIMAL_WHISPER: 
			snprintf(c,42,"hit %s with their staff",defender_name); 
			break;
		default:
			snprintf(c,6,"error");
			break;
	}
	return c;
}

static inline char *playerReducedAttack(const char *const defender_name) {
	char *const c = malloc(43);
	switch(PLAYER_CLASS) {
		case WARRIOR       : 
			snprintf(c,45,"hit %s with back of the axe",defender_name);
			break;
		case PLAYER_ARCHER : 
			snprintf(c,45,"cut %s with their short sowrd",defender_name); 
			break;
		case ANIMAL_WHISPER: 
			snprintf(c,45,"hit %s with a small rock",defender_name); 
			break;
		default:
			snprintf(c,6,"error");
			break;
	}
	return c;
}

static inline void printCharTurn(const CHARTYPE type) {
	char *c = malloc(18);
	switch(type) {
		case SWORDSMAN: 
			snprintf(c,18,"Swordsman's turn");
			break;
		case SPEARMAN:  
			snprintf(c,18,"Spearman's turn");
			break;
		case MAGE:      
			snprintf(c,18,"Mage's turn");
			break;
		case WOLF:      
			snprintf(c,18,"Wolf's turn");
			break;
		case ARCHER:    
			snprintf(c,18,"Archer's turn");
			break;
		case BEAR:      
			snprintf(c,18,"Bear's turn");
			break;
		case MONSTER:   
			snprintf(c,18,"Monster's turn");
			break;
		case SKELETON: 
			snprintf(c,18,"Skeleton's turn");
			break;
		case COMPWOLF:
			snprintf(c,18,"pet wolf's turn");
			break;
		case PLAYERTYPE:    
			snprintf(c,18,"Player's turn");
			break;
		case NUM_CHARTYPE: //FALLTHROUGH
		default: snprintf(c,6,"error"); //shouldnt get here, but if it does ill know.
			 break;
	}
	printToCombatPrompt(0,0,c);
	free(c);
}

static inline void printCharAttack(const char *const name) {
	char c[25];
	snprintf(c,25,"%s attacks",name);
	printToCombatPrompt(0,1,c);
}

//print primary attack message for character
static inline void printCharRegularAttack(const CHARTYPE type, const char *const defender_name) {
	char *c = malloc(47);
	switch(type) {
		case SWORDSMAN: 
			snprintf(c,47,"struck %s with his sword",defender_name);
			break;
		case SPEARMAN:  
			snprintf(c,47,"stabbed %s with his spear",defender_name);
			break;
		case MAGE:      
			snprintf(c,47,"hit %s with a bolt of lightning",defender_name);
			break;
		case WOLF:      
			snprintf(c,47,"bit %s with its sharp fangs",defender_name);
			break;
		case ARCHER:    
			snprintf(c,47,"shot %s with an arrow",defender_name);
			break;
		case BEAR:      
			snprintf(c,47,"scratched %s with his big paws",defender_name);
			break;
		case MONSTER:   
			snprintf(c,47,"attacked %s with his monster body",defender_name);
			break;
		case SKELETON: 
			snprintf(c,47,"hit %s with his big ass sword",defender_name);
			break;
		case COMPWOLF:    
			snprintf(c,47,"bit %s with its sharp fangs",defender_name);
			break;
		case PLAYERTYPE:    
			free(c);
			c = playerRegularAttack(defender_name);
			break;
		case NUM_CHARTYPE: //FALLTHROUGH
		default: snprintf(c,6,"error"); //shouldnt get here, but if it does ill know.
			 break;
	}
	printToCombatPrompt(0,2,c);
	free(c);
}

//print the alternative attack message for a character
static inline void printCharReducedAttack(const CHARTYPE type, const char *const defender_name) {
	char *c = malloc(50);
	switch(type) {
		case SWORDSMAN: 
			snprintf(c,50,"hit %s with his sword pommel",defender_name);
			break;
		case SPEARMAN:  
			snprintf(c,50,"bashed %s with his spear staff",defender_name);
			break;
		case MAGE:      
			snprintf(c,50,"hit %s with a bolt of lightning",defender_name);
			break;
		case WOLF:      
			snprintf(c,50,"scratched %s with its sharp claws",defender_name);
			break;
		case ARCHER:    
			snprintf(c,50,"stabbed %s with her short sword",defender_name);
			break;
		case BEAR:      
			snprintf(c,50,"bit %s with his fangs",defender_name);
			break;
		case MONSTER:   
			snprintf(c,50,"clawed %s with his monster claws",defender_name);
			break;
		case SKELETON: 
			snprintf(c,50,"did a spooky attack on %s",defender_name);
			break;
		case COMPWOLF:    
			snprintf(c,50,"scratched %s with its sharp claws",defender_name);
			break;
		case PLAYERTYPE: 
			free(c);   
			c = playerReducedAttack(defender_name);
			break;
		case NUM_CHARTYPE: //FALLTHROUGH
		default: snprintf(c,6,"error"); //shouldnt get here, but if it does ill know.
			 break;
	}
	printToCombatPrompt(0,2,c);
	free(c);
}

//calculate damage done and apply it to defender.
static int dealDamage(const CHARACTER *const attacker,CHARACTER *const defender,const int attack_offset,const int crit) {
	int damage = (attacker->attack - defender->defense) - attacker->flags->defending - attack_offset;
	if(crit != 0) {
		damage += defender->defense;   //crits ignore defense rating
	}
	if(damage < 1) {
		damage = 1;   //should do a min of 1 damage. 
	}
	defender->health -= damage;
	return damage;
}

//apply eleoctrocuted to defender
static void makeElectrocuted(CHARACTER *const defender) {
	char c[37];
	defender->flags->electrocuted = 1;
	snprintf(c,37,"%s is now electrocuted",defender->name);
	printToCombatPrompt(0,3,c);	
}

//apply bleeding to defender
static void makeBleeding(CHARACTER *const defender) {
	char c[32];
	defender->flags->bleeding = 3;
	snprintf(c,32,"%s is now bleeding",defender->name);
	printToCombatPrompt(0,3,c);
}

//apply the frightened attribute to defender
static void makeFrightened(CHARACTER *const defender) {
	char c[35];
	defender->flags->frightend = 1;
	snprintf(c,35,"%s is now frightened",defender->name);
	printToCombatPrompt(0,3,c);
}

//carry out a regular attack. roll twice, returns the number of successes.
static int regularAttack(const CHARACTER *const attacker,const CHARACTER *const defender) {
	if(rand() % 10 + attacker->attack_chance > defender->dodge) {
		return (rand() % 10 > defender->dodge)? 2 : 1;
	}
	return (rand() % 10 + defender->attack > attacker->dodge)? 3 : 0;  //if atttacker misses, chance for defender to do a counter attack.
}

//if defender does a counter attack against attacker
static void counterAttack(CHARACTER *const attacker, const CHARACTER *const defender) {
	char c[52];
	char d[42];
	snprintf(c,52,"%s dodges and counters with an attack",defender->name);
	snprintf(d,42,"dealing %d to %s",dealDamage(defender,attacker,2,0),attacker->name);
	printToCombatPrompt(0,2,c);
	printToCombatPrompt(0,3,d);
}

//if attack does some effect, then apply it to defender by calling the corresponding function
static void applyEffect(CHARACTER *const defender,ATTACKTYPE type) {
	switch(type) {
		case REGULAR  : //do nothing
			break;
		case BLEEDING : makeBleeding(defender);
			break;
		case ELECTRIC : makeElectrocuted(defender);
			break;
		case FRIGHTEND: makeFrightened(defender);
			break;
		default: //do nothing
			break;
	}
}

//after doing a regular attack, do damage and print out the info to prompt win
static void regularDamage(CHARACTER *const attacker,CHARACTER *const defender,const int attack_offset,ATTACKTYPE attacktype) {
	int crit = 0;
	char c[42];
	printCharAttack(attacker->name);
	switch(regularAttack(attacker,defender)) {
		case 0: printToCombatPrompt(0,2,"missed.");
			break;
		case 2:	
			crit = 1;	//critical hits ignore defender's defense rating.
			printToCombatPrompt(0,3,"scoring ciritcal hit.");
			applyEffect(defender,attacktype);
			//FALLTHROUGH
		case 1:
			if (attack_offset) {
				printCharRegularAttack(attacker->type,defender->name);
			}
			else {
				printCharReducedAttack(attacker->type,defender->name);
			}
			snprintf(c,42,"dealing %d damage to %s",dealDamage(attacker,defender,attack_offset,crit),defender->name);
			printToCombatPrompt(0,3+crit,c);
			break;
		case 3:
			counterAttack(attacker,defender);
			break;
		default: //do nothing
			break;
	}
}

//if attacker isnt in a defensive stance, then switch to one.
static int switchToDefenseStance(CHARACTER *const attacker) {
	if (attacker->flags->defending == 0) {
		attacker->flags->defending = 1;
		char c[50];
		snprintf(c,50,"%s switches to a defensive stance.",attacker->name);
		printToCombatPrompt(0,1,c);
		attacker->defense += 3;
		return 1;
	}
	return 0;
}

//the player's turn while engaged in combat. 
int playerAttack(CHARACTER *const attacker,CHARACTER *const defender) {
	printCombatPrompt();
	clearStatsWin();
	updateStatsWin();
	switch(getch()) {
		case '1': 
			clearCombatPrompt();
			if(rand() % 5 > 1) {
				regularDamage(attacker,defender,0,REGULAR);
			}
			else {
				regularDamage(attacker,defender,2,REGULAR);
			}
			break;
		case '2': 
			clearCombatPrompt();
			if(switchToDefenseStance(attacker)) {
				return 1;
			}
			else {
				printToCombatPrompt(0,1,"sorry, already in defensive stance");
				getch();
				return 0;
			}
		case '3': 
			clearCombatPrompt();
			return accessPlayerInventory();
		default: return 0; 
	}
	return 1;

}

int swordsmanAttack(CHARACTER *const attacker,CHARACTER *const defender) {
	printCharTurn(attacker->type);
	switch(rand() % 10) {
		case 0:
		case 1:
		case 2:
		case 3://FALLTHROUGH
			
			regularDamage(attacker,defender,0,REGULAR); //attack with sword
			break;
		case 4: 
		case 5://FALLTHROUGH
			regularDamage(attacker,defender,3,REGULAR); //attack with pommel
			break;
		case 6:
		case 7://FALLTHROUGH
			return (switchToDefenseStance(attacker) == 1)? 1 : swordsmanAttack(attacker,defender);
		case 8:
		case 9://FALLTHROUGH
			return (computerCheckItem(attacker,defender) == 1)? 1 : swordsmanAttack(attacker,defender);
		default:
			return 1;		
	}
	return 1;
}

int mageAttack(CHARACTER *const attacker,CHARACTER *const defender) {
	printCharTurn(attacker->type);
	switch(rand() % 10) {
		case 0:
		case 1:
		case 2://FALLTHROUGH
			
			regularDamage(attacker,defender,0,ELECTRIC); //use lightening bolt
			break;
		case 3:
		case 4: //FALLTHRUGH
			regularDamage(attacker,defender,3,REGULAR); //attack with staff, does 2 less damage than lightning
			break;
		case 5:
		case 6://FALLTHROUGH
			return (switchToDefenseStance(attacker) == 1)? 1 : mageAttack(attacker,defender);
		case 7:
		case 8:
		case 9://FALLTHROUGH
			return (computerCheckItem(attacker,defender) == 1)? 1 : mageAttack(attacker,defender);
		default: 
			return 0;		
	}
	return 1;
}

int spearmanAttack(CHARACTER *const attacker,CHARACTER *const defender) {
	printCharTurn(attacker->type);
	switch(rand() % 8) {
		case 0:
		case 1:
		case 2://FALLTHROUGH
			
			regularDamage(attacker,defender,0,REGULAR); //atacks with spear point
			break;
		case 3:
		case 4://FALLTHROUGH
			regularDamage(attacker,defender,3,REGULAR);  //attacks with staff of spear
			break;
		case 5:
			return (switchToDefenseStance(attacker) == 1)? 1 : spearmanAttack(attacker,defender);
		case 6:
		case 7://FALLTHRUGH
			return (computerCheckItem(attacker,defender) == 1)? 1 : spearmanAttack(attacker,defender);
		default: 
			return 0;
	}
	return 1;
}

int wolfAttack(CHARACTER *const attacker,CHARACTER *const defender) {
	printCharTurn(attacker->type);
	switch(rand() % 6) {
		case 0:
		case 1:
		case 2://FALLTHROUGH
			
			regularDamage(attacker,defender,0,BLEEDING); //attacks with biting
			break;
		case 3:
		case 4://FALLTHROUGH
			regularDamage(attacker,defender,2,REGULAR); //attacks with claws.
			break;
		case 5:
			return (switchToDefenseStance(attacker) == 1)? 1 : wolfAttack(attacker,defender);
		default: 
			return 0;
	}
	return 1;
}

int archerAttack(CHARACTER *const attacker,CHARACTER *const defender) {
	printCharTurn(attacker->type);
	switch(rand() % 9) {
		case 0:
		case 1:
		case 2://FALLTHROUGH
			if(attacker->inventory[ARROW]->number_items > 0) {  //if archer has arrows, attack with them, else fall through to attack with short sword
					
				regularDamage(attacker,defender,0,REGULAR); //attacks with arrow
				break;
			}
			//FALLTHROUGH
		case 3://FALLTHROUGH
		case 4://FALLTHROUGH
			regularDamage(attacker,defender,2,REGULAR);  //attacking with short sword
			break;
		case 5:
			return (switchToDefenseStance(attacker) == 1)? 1 : archerAttack(attacker,defender);
		case 6:
		case 7:
		case 8://FALLTHRUGH
			return (computerCheckItem(attacker,defender) == 1)? 1 : archerAttack(attacker,defender);
		default: 
			return 0;
		}
	return 1;
}

int bearAttack(CHARACTER *const attacker,CHARACTER *const defender) {
	printCharTurn(attacker->type);
	switch(rand() % 6) {
		case 0:
		case 1:
		case 2://FALLTHROUGH
			
			regularDamage(attacker,defender,0,BLEEDING); //attacks with claws
			break;
		case 3:
		case 4://FALLTHROUGH
			regularDamage(attacker,defender,2,FRIGHTEND); //attacks with biting.
			break;
		case 5:
			return (switchToDefenseStance(attacker) == 1)? 1 : bearAttack(attacker,defender);
		default: 
			return 0;
	}
	return 1;
}

int skeletonAttack(CHARACTER *const attacker,CHARACTER *const defender) {
	printCharTurn(attacker->type);
	switch(rand() % 8) {
		case 0:
		case 1:
		case 2: //FALLTHROUGH
			
			regularDamage(attacker,defender,0,REGULAR);  //attack with big ass sword
			break;
		case 3:
		case 4:
		case 5://FALLTHROUGH
			regularDamage(attacker,defender,3,FRIGHTEND);  //do spooky asttack.
			break;
		case 6:
		case 7://FALLTHROUGH
			return (computerCheckItem(attacker,defender) == 1)? 1 : skeletonAttack(attacker,defender);
		default:
			return 0;
	}
	return 1;
}

int monsterAttack(CHARACTER *const attacker,CHARACTER *const defender) {
	printCharTurn(attacker->type);
		switch(rand() % 6) {
		case 0:
		case 1:
		case 2://FALLTHROUGH
			regularDamage(attacker,defender,0,FRIGHTEND); //attacks with body
			break;
		case 3:
		case 4://FALLTHROUGH
			regularDamage(attacker,defender,3,FRIGHTEND); //attacks with claws.
			break;
		case 5:
			return (switchToDefenseStance(attacker) == 1)? 1 : monsterAttack(attacker,defender);
		default: 
			return 0;
	}
	return 1;

}

//after battle, restore attributes to normal value in case they were changed.
static inline void resetAttributes(CHARACTER *const character) {
	character->defense            =  character->max_defense;
	character->attack             =  character->max_attack;
	character->flags->missedturns =  0;
	character->flags->frightend   =  0;
	character->flags->defending   =  0;
}

static inline void removeEnemy(CHARACTER *character) {
	ENEMY *temp = ENEMIES;
	if(temp->character == character) {
		ENEMIES = ENEMIES->next;
	}
	else {
		while (temp->next->character != character) {
			temp = temp->next;
		}
		temp->next = (temp->next->next != NULL)?  temp->next->next : NULL;
	}
	printTilePiece(character->current_loc->x,character->current_loc->y);
}

static inline void charTurn(CHARACTER *const attacker, CHARACTER *const defender) {
	clearCombatPrompt();
	while(attacker->charAttack(attacker,defender) == 0);
	getch();
}

//loop through until one or both of combatants are dead. 
static inline void combatLoop(CHARACTER *const character1, CHARACTER *const character2) {
	while(character1->health > 0 && character2->health > 0 && PLAY) {
		//if player is character2 and has a living companion, give random chance companion will be attacked instead of player

		charTurn(character1,(character2 == PLAYER && character2->has_comp && COMPANION->health > 0) ? ((rand() % 5 < 3)? character2 : COMPANION) : character2);

		if(character2->health > 0) {
		//if player is character1 and has a living companion, give random chance companion will be attacked instead of player
			charTurn(character2,(character1 == PLAYER && character1->has_comp && COMPANION->health > 0) ? ((rand() % 5 < 3)? character1 : COMPANION) : character1);
		}
		if(COMPANION != NULL && COMPANION->health > 0) {
			charTurn(COMPANION,(character1 == PLAYER)? character2 : character1);
		}
	}
	if(PLAYER->health > 0) {
		resetAttributes(PLAYER);
		if(PLAYER->has_comp) {
			resetAttributes(COMPANION);
		}
		removeEnemy((character1 != PLAYER)? character1 : character2);
	}
}

void engageCombat(CHARACTER *const character) {
	if(character != PLAYER) {
		printCombatScreen(character);
		combatLoop(character,PLAYER);
	}
	else {
		ENEMY *temp = ENEMIES;
		while(temp != NULL) {
			if(temp->character->current_loc->y == PLAYER->current_loc->y && temp->character->current_loc->x == PLAYER->current_loc->x){
				printCombatScreen(temp->character);
				combatLoop(PLAYER,temp->character);
				break;
			} 
			temp = temp->next;
		}
	}
	clearMainWin();
	restoreMainWin();
}

//sets the function pointer to the function which governs that character's attack
attack_fpointer makeCharAtack(CHARTYPE type) {
	switch(type) {
		case PLAYERTYPE:   return  playerAttack;
		case SWORDSMAN:    return  swordsmanAttack;
		case MAGE:         return  mageAttack;
		case SPEARMAN:     return  spearmanAttack;
		case WOLF:         return  wolfAttack;
		case ARCHER:       return  archerAttack;
		case BEAR:         return  bearAttack;
		case SKELETON:	   return  skeletonAttack;
		case MONSTER:      return  monsterAttack;
		case COMPWOLF:     return  wolfAttack;
		case NUM_CHARTYPE: return  NULL; //should not be used. just here to make a case for each enum member
		default :          return  NULL; 
	}
}