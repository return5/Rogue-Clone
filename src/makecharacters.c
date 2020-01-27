/*                                     ### description ###
	randomly make enemy characters. starts with makeEnemeis() which selects a random number of enemies to make. also initialized ENEMIES linked list.
	each character is made with the makeCharacter() function. the type of enemy is randomly chosen. makeCharacter() sets all values to that of the chosen enemy type.
	each character has an inventory of items. when created, each character has a specific chance of getting each item, with each item having its own chance. 
	each item has a function pointer to the function which covers its use.  
	each character has a function pointer to the function which governs its attack.
		
*/
//---------------------------------------- headers---------------------------------------------------
#include "makecharacters.h"
//----------------------------------------------- prototypes -----------------------------------------------
static  char             makeCharIcon               (CHARTYPE type);
static  char             *makeCharName              (CHARTYPE type);
static  CHARACTER        *makeCharacter             (CHARTYPE type);
static  int              makeCharDodge              (CHARTYPE type);
static  int              makeCharMaxDefense         (CHARTYPE type);
static  int              makeCharMaxAttack          (CHARTYPE type);
static  int              makeCharMaxHealth          (CHARTYPE type);
static  int              checkXRow                  (const int x);
static  FLAGS            *makeCharFlags             (void);
static  LOCATION         *makeCharLocation          (void);
static  int              getPlayerAttackChance      (void);
static  int              getPlayerDodge             (void);
static  int              getPlayerMaxDefense        (void);
static  int              getPlayerMaxAttack         (void);
static  int              getPlayerMaxHealth         (void);

//---------------------------------------- global vars ----------------------------------------------
static  const  size_t  SIZE_CHARACTER  =  sizeof(CHARACTER);
static  const  size_t  SIZE_LOCATION   =  sizeof(LOCATION);
static  const  size_t  SIZE_FLAGS      =  sizeof(FLAGS);
static  const  size_t  SIZE_NAME	   =  sizeof(char) * 13;
static  const  size_t  SIZE_ENEMY      =  sizeof(ENEMY);

ENEMY     *ENEMIES;    //linked list which holds enemies
CHARACTER *PLAYER;
CHARACTER *COMPANION;
//---------------------------------------- code -----------------------------------------------------

//get attack chance for player character based on player class
static int getPlayerAttackChance(void) {
	switch(PLAYER_CLASS) {
		case WARRIOR       : return (rand() % 4) + 3;
		case PLAYER_ARCHER : return (rand() % 4) + 2;
		case ANIMAL_WHISPER: return (rand() % 3) + 2;
		default:             return 0;
	}
}

//get dodge chance for layer based on player class
static int getPlayerDodge(void) {
	switch(PLAYER_CLASS) {
		case WARRIOR       : return (rand() % 5) + 4;
		case PLAYER_ARCHER : return (rand() % 4) + 6;
		case ANIMAL_WHISPER: return (rand() % 3) + 4;
		default:             return 0;
	}
}

//get max defense for player based upon player class
static int getPlayerMaxDefense(void) {
	switch(PLAYER_CLASS) {
		case WARRIOR       : return (rand() % 4) + 4;
		case PLAYER_ARCHER : return (rand() % 4) + 2;
		case ANIMAL_WHISPER: return (rand() % 3) + 2;
		default:             return 0;
	}
}

//get player max attack based upon player class
static int getPlayerMaxAttack(void) {
	switch(PLAYER_CLASS) {
		case WARRIOR       : return (rand() % 4) + 6;
		case PLAYER_ARCHER : return (rand() % 5) + 4;
		case ANIMAL_WHISPER: return (rand() % 3) + 4;
		default:             return 0;
	}
}

//get max health for player backed upon player class
static int getPlayerMaxHealth(void) {
	switch(PLAYER_CLASS) {
		case WARRIOR       : return (rand() % 10) + 14;
		case PLAYER_ARCHER : return (rand() % 9) + 12;
		case ANIMAL_WHISPER: return (rand() % 6) + 10;
		default:             return 0;
	}
}

//get color for that character.
static CHARCOLOR getCharColor(CHARTYPE type) {
	switch(type) {  
		case SWORDSMAN:    return  BLUECHAR;
		case SPEARMAN:     return  REDCHAR;
		case MAGE:         return  MAGENTACHAR;
		case WOLF:         return  YELLOWCHAR;
		case ARCHER:       return  GREENCHAR;
		case BEAR:         return  REDCHAR;
		case MONSTER:      return  GREENCHAR;
		case SKELETON:     return  YELLOWCHAR;
		case PLAYERTYPE:   return  BLUECHAR;
		case NUM_CHARTYPE: return  0;  //should not be used. just here to make a case for each enum member
		default :          return  0;  //should also not be used, just to give a default case. 
	}
}

//get the value for attack_chance for each character type
static int makeCharAttackChance(CHARTYPE type) {
	switch(type) {
		case PLAYERTYPE:   return  getPlayerAttackChance();
		case SWORDSMAN:    return  2;
		case MAGE:         return  2;
		case SPEARMAN:     return  3;
		case WOLF:         return  4;
		case ARCHER:       return  3;
		case BEAR:         return  4;
		case MONSTER:      return  2;
		case SKELETON:     return  3;
		case NUM_CHARTYPE: return  0; //should not be used. just here to make a case for each enum member
		default :          return  0; 
	}
}

//chance to dodge an attack. each character type has its own chance with the player being random each game.
static int makeCharDodge(CHARTYPE type) {
	switch(type) {
		case PLAYERTYPE:   return  getPlayerDodge();
		case SWORDSMAN:    return  5;
		case MAGE:         return  6;
		case SPEARMAN:     return  6;
		case WOLF:         return  7;
		case ARCHER:       return  7;
		case BEAR:         return  4;
		case MONSTER:      return  4;
		case SKELETON:     return  6;
		case NUM_CHARTYPE: return  0; //should not be used. just here to make a case for each enum member
		default :          return  0; 
	}
}

//set the defense rating for each character type.
static int makeCharMaxDefense(CHARTYPE type) {
	switch(type) {
		case PLAYERTYPE:   return  getPlayerMaxDefense();
		case SWORDSMAN:    return  3;
		case MAGE:         return  2;
		case SPEARMAN:     return  3;
		case WOLF:         return  2;
		case ARCHER:       return  1;
		case BEAR:         return  3;
		case MONSTER:      return  3;
		case SKELETON:     return  2;
		case NUM_CHARTYPE: return  0; //should not be used. just here to make a case for each enum member
		default :          return  0; 
	}
}

//sets the attack value for each character type
static int makeCharMaxAttack(CHARTYPE type) {
	switch(type) {
		case PLAYERTYPE:   return  getPlayerMaxAttack();
		case SWORDSMAN:    return  6;
		case MAGE:         return  5;
		case SPEARMAN:     return  7;
		case WOLF:         return  5;
		case ARCHER:       return  6;
		case BEAR:         return  6;
		case MONSTER:      return  7;
		case SKELETON:     return  8;
		case NUM_CHARTYPE: return  0; //should not be used. just here to make a case for each enum member
		default :          return  0; 
	}
}

//sets the health value for each character type
static int makeCharMaxHealth(CHARTYPE type) {
	switch(type) {
		case PLAYERTYPE:   return  getPlayerMaxHealth();
		case SWORDSMAN:    return  12;
		case MAGE:         return  7;
		case SPEARMAN:     return  10;
		case WOLF:         return  8;
		case ARCHER:       return  9;
		case BEAR:         return  11;
		case MONSTER:      return  12;
		case SKELETON:     return  8;
		case NUM_CHARTYPE: return  0; //should not be used. just here to make a case for each enum member
		default :      	   return  0; 
	}
}

//set default values to each of the flags in FLAGS struct
static FLAGS *makeCharFlags(void) {
	//by default all flags should be 0
	FLAGS *flags         =  malloc(SIZE_FLAGS);
	flags->poisoned      =  0;
	flags->ate           =  0;
	flags->onfire        =  0;
	flags->slowhealth    =  0;
	flags->bleeding      =  0;
	flags->defending     =  0;
	flags->missedturns   =  0;
	flags->electrocuted  =  0;
	flags->frightend     =  0;
	return flags;
}

//check all icons at that x loction, if one is a '.'' or a '#' then return 1;
static int checkXRow(const int x) {
	for(int i = 0; i < HEIGHT; i++) {
		switch(WORLDMAP[i][x]->icon) {
			case '#':
			case '.': return 1;
			default: //do nothing
				break;
		}
	}
	return 0;
}

//get a random location for a character inside one of the rooms.
static LOCATION *makeCharLocation(void) {
	LOCATION *loc  =  malloc(SIZE_LOCATION);
	do {
		loc->x = rand() % WIDTH;
		//while no icon on world map with this x location is a '.' or '#'
	}while(checkXRow(loc->x) != 1);

	do {
		loc->y = rand() % HEIGHT;
		//while y is not a '.' or a '#' 
	}while(WORLDMAP[loc->y][loc->x]->icon != '#' && WORLDMAP[loc->y][loc->x]->icon != '.');
	return loc;
}

//make the icon which will appear on screen for each characters
static char makeCharIcon(CHARTYPE type) {
	switch(type) {
		case PLAYERTYPE:   return '@';
		case SWORDSMAN:    return 'S';
		case MAGE:         return 'M';
		case SPEARMAN:     return 'P';
		case WOLF:         return 'W';
		case ARCHER:       return 'A'; 
		case BEAR:         return 'B'; 
		case MONSTER:      return 'X';
		case SKELETON:     return 'K';
		case NUM_CHARTYPE: return '\0';  //should not be used. just here to make a case for each enum member	
		default :          return '\0'; 	
	}
}

//give each character a name.
static char *makeCharName(CHARTYPE type) {
	char *name = malloc(SIZE_NAME);
	switch(type) {
		case PLAYERTYPE:   snprintf(name,SIZE_NAME,"Player");       break;
		case SWORDSMAN:    snprintf(name,SIZE_NAME,"Swordsman");    break;
		case MAGE:         snprintf(name,SIZE_NAME,"Mage");         break;
		case SPEARMAN:     snprintf(name,SIZE_NAME,"Spearman");     break;
		case WOLF:         snprintf(name,SIZE_NAME,"Wolf");         break;
		case ARCHER:       snprintf(name,SIZE_NAME,"Archer");       break;
		case BEAR:         snprintf(name,SIZE_NAME,"Bear");         break;
		case MONSTER:      snprintf(name,SIZE_NAME,"Monster");      break;
		case SKELETON:     snprintf(name,SIZE_NAME,"Skeleton");	    break;
		case NUM_CHARTYPE: snprintf(name,SIZE_NAME,"Num_chartype"); break;//should not be used. just here to make a case for each enum member
		default :          /*do nothing    */                       break; 	
	}
	return name;
}

//make a character. 
static CHARACTER *makeCharacter(CHARTYPE type) {
	CHARACTER *character      =  malloc(SIZE_CHARACTER);
	character->type	          =  type;
	character->name           =  makeCharName(type);
	character->icon           =  makeCharIcon(type);
	character->loc            =  makeCharLocation();
	character->flags          =  makeCharFlags();
	character->inventory      =  makeCharInventory(type);
	character->charAttack     =  makeCharAtack(type);
	character->dodge 	      =  makeCharDodge(type);
	character->attack_chance  =  makeCharAttackChance(type);
	character->color          =  getCharColor(type);
	character->printCharModel =  getCharModel(type);
	character->has_comp       =  0;
	character->prev_move      =  rand() % 4;
	character->health         =  character->max_health   =  makeCharMaxHealth(type);
	character->attack         =  character->max_attack   =  makeCharMaxAttack(type);
	character->defense        =  character->max_defense  =  makeCharMaxDefense(type);
	return character;
}

//make the enemies which will be on the map.
void makeEnemies(void) {
	const int num_enemies  =  (rand() % 4) + ROOMS->number_rooms;
	ENEMIES                =  malloc(SIZE_ENEMY);
	ENEMY *newenemy        =  ENEMIES;
	newenemy->character    =  makeCharacter((rand() % NUM_CHARTYPE));

	for(int i = 0; i < num_enemies; i++) {
		newenemy->next       =  malloc(SIZE_ENEMY);
		newenemy             =  newenemy->next;
		newenemy->character  =  makeCharacter((rand() % NUM_CHARTYPE));
	}
}
//make player, and if needed, make companion as well
void makePlayer(void) {
	PLAYER = makeCharacter(PLAYERTYPE);
	if(PLAYER_CLASS == ANIMAL_WHISPER) {
		COMPANION        = makeCharacter(WOLF);
		COMPANION->loc   = PLAYER->loc;
		PLAYER->has_comp = 1;
	}
}