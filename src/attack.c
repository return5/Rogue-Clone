/*                                           ### description ###                       

*/

//---------------------------------------------- headers -------------------------------------------------
#include "attack.h"

//---------------------------------------------- prototypes ----------------------------------------------
static void printCharRegularAttack    (CHARTYPE type, const char *const defender_name);
static void printCharReducedAttack    (CHARTYPE type, const char *const defender_name);
static int  dealDamage                (const CHARACTER *const attacker,CHARACTER *const defender,const int attack_offset,const int crit);
static void makeElectrocuted          (CHARACTER *const character);
static void makeBleeding              (CHARACTER *const defender);
static void makeFrightened            (CHARACTER *const defender);
static int  regularAttack             (const CHARACTER *const attacker,const CHARACTER *const defender);
static void counterAttack             (CHARACTER *const attacker, const CHARACTER *const defender);
static void applyEffect               (CHARACTER *const defender,ATTACKTYPE type);
static void regularDamage             (CHARACTER *const attacker,CHARACTER *const defender,const int attack_offset,ATTACKTYPE attacktype);
static int  switchToDefenseStance     (CHARACTER *const attacker);

//---------------------------------------------- define --------------------------------------------------

//---------------------------------------------- enums ---------------------------------------------------


//---------------------------------------------- typedefs ------------------------------------------------


//---------------------------------------------- structs -------------------------------------------------


//---------------------------------------------- global vars ---------------------------------------------

//---------------------------------------------- code ----------------------------------------------------

//print primary attack message for character
static void printCharRegularAttack(CHARTYPE type, const char *const defender_name) {
	char c[47];
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
		case PLAYERTYPE:    
			snprintf(c,47,"hit %s with their sword",defender_name);
			break;
		case NUM_CHARTYPE: //FALLTHROUGH
		default: snprintf(c,6,"error"); //shouldnt get here, but if it does ill know.
			 break;
	}
	printToPrompt(0,1,c);
}

//print the alternative attack message for a character
static void printCharReducedAttack(CHARTYPE type, const char *const defender_name) {
	char c[50];
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
		case PLAYERTYPE:    
			snprintf(c,50,"hit %s with their sword",defender_name);
			break;
		case NUM_CHARTYPE: //FALLTHROUGH
		default: snprintf(c,6,"error"); //shouldnt get here, but if it does ill know.
			 break;
	}
	printToPrompt(0,1,c);
}

//calculate damage done and apply it to defender.
static int dealDamage(const CHARACTER *const attacker,CHARACTER *const defender,const int attack_offset,const int crit) {
	char c[52];
	int damage = attacker->attack - defender->defense - attacker->flags->defending - attack_offset;
	if(attack_offset == 0) {
		printCharRegularAttack(attacker->type,defender->name);
	}
	else {
		printCharReducedAttack(attacker->type,defender->name);
	}
	if(crit != 0) {
		damage += defender->defense;   //crits ignore defense rating
	}
	if(damage < 1) {
		damage = 1;   //should do a min of 1 damage. 
	}
	defender->health -= damage;
	snprintf(c,52,"dealing %d damage to %s",damage,defender->name);
	printToPrompt(0,3,c);
	return damage;
}

//apply eleoctrocuted to defender
static void makeElectrocuted(CHARACTER *const defender) {
	char c[37];
	defender->flags->electrocuted = 1;
	snprintf(c,37,"%s is now electrocuted",defender->name);
	printToPrompt(0,3,c);	
}

//apply bleeding to defender
static void makeBleeding(CHARACTER *const defender) {
	char c[32];
	defender->flags->bleeding = 3;
	snprintf(c,32,"%s is now bleeding",defender->name);
	printToPrompt(0,3,c);
}

//apply the frightened attribute to defender
static void makeFrightened(CHARACTER *const defender) {
	char c[35];
	defender->flags->frightend = 1;
	snprintf(c,35,"%s is now frightened",defender->name);
	printToPrompt(0,3,c);
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
	printToPrompt(0,2,c);
	printToPrompt(0,3,d);
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
	switch(regularAttack(attacker,defender)) {
		case 0: printToPrompt(0,2,"missed.");
			break;
		case 2:	
			crit = 1;	//critical hits ignore defender's defense rating.
			printToPrompt(0,2,"scoring ciritcal hit.");
			applyEffect(defender,attacktype);
			//FALLTHROUGH
		case 1:
				dealDamage(attacker,defender,crit,attack_offset);
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
		printToPrompt(0,0,c);
		attacker->defense += 3;
		return 1;
	}
	return 0;
}

//the player's turn while engaged in combat. 
int playerAttack(CHARACTER *const attacker,CHARACTER *const defender) {
	switch(getch()) {
		case 1: regularDamage(attacker,defender,0,attacker->attacktype);
			break;
		case 2: 
			if(switchToDefenseStance(attacker)) {
				return 1;
			}
			else {
				printToPrompt(0,0,"sorry, already in defensive stance");
				getch();
				return 0;
			}
		case 3: return accessPlayerInventory();
		default: return 0; 
	}
	return 1;

}

int swordsmanAttack(CHARACTER *const attacker,CHARACTER *const defender) {
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
void resetAttributes(CHARACTER *const character) {
	character->defense            =  character->max_defense;
	character->attack             =  character->max_attack;
	character->flags->missedturns =  0;
	character->flags->frightend   =  0;
	character->flags->defending   =  0;
}

//loop through until one or both of combatants are dead. 
void combatLoop(CHARACTER *const character1, CHARACTER *const character2) {
	while(character1->health > 0 && character2->health > 0) {
		//if player is character2 and has a living companion, give random chance companion will be attacked instead of player
		if(character2->has_comp && COMPANION->health > 0 && character1 != PLAYER) {
			character1->charAttack(character1,(rand() % 5 < 3)? character2 : COMPANION);
		}
		else {
			character1->charAttack(character1,character2);
		}
		if(character2->health > 0) {
		//if player is character1 and has a living companion, give random chance companion will be attacked instead of player
			if(character1->has_comp && COMPANION->health > 0 && character2 != PLAYER) {
				character2->charAttack(character1,(rand() % 5 < 3)? character1 : COMPANION);
			}
			else {
				character2->charAttack(character1,character2);
			}
		}
	}
	resetAttributes((character1->health > 0)? character1 : character2);

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
		case NUM_CHARTYPE: return  NULL; //should not be used. just here to make a case for each enum member
		default :          return  NULL; 
	}
}