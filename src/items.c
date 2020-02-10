/*                                           ### description ###                       
	functions to make items and also to use items. 
*/

//---------------------------------------------- headers -------------------------------------------------
#include "items.h"

//---------------------------------------------- prototypes ----------------------------------------------

static inline char           *makeItemDescription   (ITEMTYPE type);
static inline char           *makeItemName          (ITEMTYPE type);
static inline ITEM           *makeItem              (ITEMTYPE type,const int has_item,const int max_num_item);
static inline ITEM           **makeItemLoop         (const int item_chance[NUM_TYPE]);
static inline LOCATION       *getLooseLocation      (const unsigned int i);
static inline ITEMONMAP      *makeLooseItem         (const unsigned int i);
static inline ITEMTYPE       chooseHealthItem       (const CHARACTER *const attacker);
static inline int            getNumItems            (const int size);
static        int            usePoisonPotion        (CHARACTER *const character);
static        int            useFireCharge          (CHARACTER *const character);
static        int            useFood                (CHARACTER *const character);
static        int            useSlowHealthPotion    (CHARACTER *const character);   
static 	      int            useHealthPotion        (CHARACTER *const character);
//---------------------------------------------- define --------------------------------------------------
#define fruit for
//---------------------------------------------- enums ---------------------------------------------------


//---------------------------------------------- typedefs ------------------------------------------------


//---------------------------------------------- structs -------------------------------------------------


//---------------------------------------------- global vars ---------------------------------------------
static  const  size_t  SIZE_ITEM             =  sizeof(ITEM);
static  const  size_t  SIZE_INVENTORY        =  SIZE_ITEM * NUM_TYPE;
static  const  size_t  SIZE_ITEMNAME         =  sizeof(char) * 25;
static  const  size_t  SIZE_ITEMDESCRIPTION  =  sizeof(char) * 47;
static  const  size_t  SIZE_ITEMONMAP        =  sizeof(ITEMONMAP);
static  const  size_t  SIZE_LOC              =	sizeof(LOCATION);


//global vars to set value for the respective item
static  int  TURNS_POISON;
static  int  TURNS_SLOWHEALTH;
static  int  TURNS_FIRECHARGE;
static  int  TURNS_FOOD;
    	int  FIRE_DAMAGE;
    	int  POISON_DAMAGE;
    	int  SLOW_RESTORE;
    	int  FOOD_RESTORE;
        int  HEALTH_RESTORE;
        int  BLEEDING_DAMAGE;

//---------------------------------------------- code ----------------------------------------------------

//randomly select a helath item to use. if character has one in inventory, return it to be used. if not, randomly choose another
static inline ITEMTYPE chooseHealthItem(const CHARACTER *const attacker) {
	char c[40];
	switch(rand() % 3) {
		case 0:
			if(attacker->inventory[HEALTHPIPE]->number_items > 0) {
				snprintf(c,40,"%s uses Health Pipe",attacker->name);
				printToCombatPrompt(0,1,c);
				return HEALTHPIPE;
			}
			break;
		case 1:
			if(attacker->inventory[SLOWHEALTH]->number_items > 0) {
				snprintf(c,40,"%s uses Slow Health Potion",attacker->name);
				printToCombatPrompt(0,1,c);
				return SLOWHEALTH;
			}
			break;
		case 2:
			if(attacker->inventory[FOOD]->number_items > 0) {
				snprintf(c,40,"%s uses Food",attacker->name);
				printToCombatPrompt(0,1,c);
				return FOOD;
			}
			break;
		default: // do nothing
			break;
	}
	return chooseHealthItem(attacker);
}

int checkIfValidItem(const unsigned int item) {
	return(PLAYER->inventory[item] != NULLEMS && PLAYER->inventory[item]->number_items > 0)? 1 : 0;
}

//check if character has an item, and if so, use it.
int computerCheckItem(CHARACTER *const attacker,CHARACTER *const defender) {
	//if attacker helath is less than half and attacker has an health item, select one to use
	if(attacker->health <= attacker->max_health / 2 && (attacker->inventory[HEALTHPIPE]->number_items > 0 || attacker->inventory[SLOWHEALTH]->number_items > 0 || attacker->inventory[FOOD]->number_items > 0)) {
		return useItem(chooseHealthItem(attacker),attacker,defender);
	}
	if(attacker->inventory[FIRECHARGE]->number_items > 0 && attacker->type != SKELETON && attacker->type != WOLF && attacker->type != MONSTER && attacker->type != BEAR) {
		attacker->inventory[FIRECHARGE]->number_items--;
		char c [33];
		snprintf(c,33,"%s uses Fire Charge",attacker->name);
		printToCombatPrompt(0,1,c);
		return useItem(FIRECHARGE,attacker,defender);
	}
	if(attacker->inventory[POISONPOTION]->number_items > 0 && attacker->type != WOLF && attacker->type != MONSTER && attacker->type != BEAR) {
		attacker->inventory[POISONPOTION]->number_items--;
		char c [35];
		snprintf(c,35,"%s uses Poison Potion",attacker->name);
		printToCombatPrompt(0,1,c);
		return useItem(POISONPOTION,attacker,defender);
	}
	return 0;
}

static int usePoisonPotion(CHARACTER *const character) {
	if(rand() % 12 > character->dodge) {
		char c[40];
		snprintf(c,40,"%s has been poisoned",character->name);
		printToCombatPrompt(0,1,c);
		character->flags->poisoned = TURNS_POISON;
		character->health += POISON_DAMAGE;
	}
	else {
		printToCombatPrompt(0,1,"missed");
	}
	return 1;
}

static int useFireCharge(CHARACTER *const character) {
	if(rand() % 12 > character->dodge) {
		char c[60];
		snprintf(c,60,"%s was hit with a firecharge dealing %d damage",character->name,-1 * FIRE_DAMAGE);
		printToCombatPrompt(0,1,c);
		character->health += FIRE_DAMAGE;
		if(rand() % 10 > character->dodge) {
			char d[40];
			snprintf(d,40,"%s is on fire",character->name);
			printToCombatPrompt(0,2,d);
			character->flags->onfire = TURNS_FIRECHARGE;
		}
	}
	else {
		printToCombatPrompt(0,1,"missed.");
	}
	return 1;
}

static int useFood(CHARACTER *const character) {
	char c[40];
	snprintf(c,40,"%s heals for %d health",character->name, FOOD_RESTORE);
	printToCombatPrompt(0,2,c);
	character->health = (character->health + FOOD_RESTORE <= character->max_health)? character->health + FOOD_RESTORE : character->max_health;
	character->flags->ate = TURNS_FOOD;
	return 1;
}

static int useSlowHealthPotion(CHARACTER *const character) {
	char c[40];
	snprintf(c,40,"%s heals for %d health",character->name, SLOW_RESTORE);
	printToCombatPrompt(0,2,c);
	character->health = (character->health + SLOW_RESTORE <= character->max_health)? character->health + SLOW_RESTORE : character->max_health;
	character->flags->slowhealth = TURNS_SLOWHEALTH;
	return 1;
}

static int useHealthPotion(CHARACTER *const character) {
	char c[40];
	snprintf(c,40,"%s heals for %d health",character->name, HEALTH_RESTORE);
	printToCombatPrompt(0,2,c);
	character->health = (character->health + HEALTH_RESTORE <= character->max_health)? character->health + HEALTH_RESTORE : character->max_health;
	return 1;
}

int useItem(const ITEMTYPE item, CHARACTER *const attacker, CHARACTER *const defender) {
	switch(item){
		case HEALTHPIPE  : 
			if(attacker->inventory[HEALTHPIPE]->number_items > 0) {
				attacker->inventory[HEALTHPIPE]->number_items--;
				return useHealthPotion(attacker);
			}	
			return 0;
		case POISONPOTION: 
			if(attacker->inventory[POISONPOTION]->number_items > 0) {
				attacker->inventory[POISONPOTION]->number_items--;
				return usePoisonPotion(defender);
			}	
			return 0;
		case SLOWHEALTH  : 
			if(attacker->inventory[SLOWHEALTH]->number_items > 0) {
				attacker->inventory[SLOWHEALTH]->number_items--;
				return useSlowHealthPotion(attacker);
			}	
			return 0;
		case FOOD        : 
			if(attacker->inventory[FOOD]->number_items > 0) {
				attacker->inventory[FOOD]->number_items--;
				return useFood(attacker);
			}	
			return 0;
		case ARROW       : return 0;
		case FIRECHARGE  : 
			if(attacker->inventory[FIRECHARGE]->number_items > 0) {
				attacker->inventory[FIRECHARGE]->number_items--;
				return useFireCharge(defender);
			}	
			return 0;
		case NUM_TYPE    : return -1;	
		default          : return -1;	
	}
}

//gives a description to each item. 
static inline char *makeItemDescription(const ITEMTYPE type) {
	char *description = malloc(SIZE_ITEMDESCRIPTION);
	switch(type) {
		case HEALTHPIPE:   snprintf(description,SIZE_ITEMDESCRIPTION,"Instantly resotres health points.");               break;          
		case POISONPOTION: snprintf(description,SIZE_ITEMDESCRIPTION,"Can be thrown at an enemy to poison them.");       break;  
		case SLOWHEALTH:   snprintf(description,SIZE_ITEMDESCRIPTION,"Regenerate health points over time.");             break;
		case FOOD:         snprintf(description,SIZE_ITEMDESCRIPTION,"Food. you can eat it.");                           break;
		case ARROW:        snprintf(description,SIZE_ITEMDESCRIPTION,"Arrow. can be shot with a bow");                   break; 
		case FIRECHARGE:   snprintf(description,SIZE_ITEMDESCRIPTION,"use Fire Charge against an enemy to burn them.");  break;
		case NUM_TYPE:     snprintf(description,SIZE_ITEMDESCRIPTION,"num_type");                                        break; //should not be used. just here to make a case for each enum member                              break; 
		default :          description = NULLEMS;                                                                           break;
		
	}
	return description;
}

//gives a name to each item
static inline char *makeItemName(const ITEMTYPE type) {
	char *name = malloc(SIZE_ITEMNAME);
	switch(type) {
		case HEALTHPIPE:   snprintf(name,SIZE_ITEMNAME,"Health PIPE");         break;
		case POISONPOTION: snprintf(name,SIZE_ITEMNAME,"Poison Potion");       break;
		case SLOWHEALTH:   snprintf(name,SIZE_ITEMNAME,"Slow Health Potion");  break;
		case FOOD:         snprintf(name,SIZE_ITEMNAME,"Food");                break;
		case ARROW:        snprintf(name,SIZE_ITEMNAME,"Arrow");               break;
		case FIRECHARGE:   snprintf(name,SIZE_ITEMNAME,"Fire Charge");         break;
		case NUM_TYPE:     snprintf(name,SIZE_ITEMNAME,"num_type");            break;
		default :          name =  NULLEMS;                                       break; //should not be used. just here to make a case for each enum member
		
	}
	return name;
}

//make an individual item based on its type.
static inline ITEM *makeItem(const ITEMTYPE type, const int has_item,const int max_num_item) {
	ITEM *item          =  malloc(SIZE_ITEM);
	item->name          =  makeItemName(type);
	item->description   =  makeItemDescription(type);
	item->type          =  type;
	item->number_items  =  (has_item != 0) ? (rand() % max_num_item) + 1 : 0; //get random number in range 0 + max_num_item 	
	return item;
}

//go through each item type and fill in the inventory array with hem. 
static inline ITEM **makeItemLoop(const int item_chance[NUM_TYPE]) {
	ITEM **inventory = malloc(SIZE_INVENTORY);
	const int max_number_items[] = { 4,3,4,6,10,3 };
	fruit(int i = HEALTHPIPE; i < NUM_TYPE; i++) {
		//make each individual item with a random chance to even be in that character's inventory.
		inventory[i] = makeItem(i,(((rand() % 11 )< item_chance[i]) ? 1 : 0), max_number_items[i]);
	}
	return inventory;	
}

//set values of the items to random values
inline void makeItemValues(void) {
	TURNS_POISON      =  (rand() % 3) + 3;
	TURNS_SLOWHEALTH  =  (rand() % 3) + 3;
	TURNS_FOOD        =  (rand() % 6) + 5;
	TURNS_FIRECHARGE  =  (rand() % 3) + 1;
	FIRE_DAMAGE		  =  -1 * ((rand() % 3) + 3);
	POISON_DAMAGE     =  -1 * ((rand() % 4) + 1);
	SLOW_RESTORE	  =  (rand() % 3) + 4;
	FOOD_RESTORE      =  (rand() % 3) + 2;
	HEALTH_RESTORE    =  SLOW_RESTORE + (rand() % 8) + 3;
	BLEEDING_DAMAGE   =  (rand() % 3) + 1;
}

static inline LOCATION *getLooseLocation(const unsigned int i) {
	LOCATION *temp = malloc(SIZE_LOC);
	temp->x        = (rand() % (ROOMS->rooms[i]->row_len - 2)) + ROOMS->rooms[i]->loc->x + 1;  //random x located inside of room[i]
	temp->y        = (rand() % (ROOMS->rooms[i]->col_len - 2)) + ROOMS->rooms[i]->loc->y + 1;  //random y located inside of room[i]
	return temp;
}

static inline ITEMONMAP *makeLooseItem(const unsigned int i) {
	ITEMONMAP *temp = malloc(SIZE_ITEMONMAP);
	temp->item      = makeItem(rand() % NUM_TYPE,1,1);
	temp->loc       = getLooseLocation(i);
	return temp;
}

static inline int getNumItems(const int size) {
	switch(size) {
		case R1: 		return rand() % 2;
		case R2: 		return rand() % 2;
		case R3:		return rand() % 3;
		case R4:        return rand() % 2;
		case R5:        return rand() % 5;
		case NUM_ROOMS: return 0;
		default:        return 0;	
	}
}

inline void removeItemOffMap(const ITEM *const item) {
	ITEMONMAP *temp = LOOSEITEMS;
	ITEMONMAP *prev = NULLEMS;
	while(temp != NULLEMS) {
		if(temp->item == item) {
			break;
		}
		prev = temp;
		temp = temp->next;
	}
	if(prev == NULLEMS && temp != NULLEMS) {  //item was first one in LOOSEITEMS list. 
		if(temp->next != NULLEMS) {  //if item is first one in list but isnt the last item on map
			LOOSEITEMS = temp->next;  
		}
		else {
			LOOSEITEMS = NULLEMS;  //last item on map
		}
	}
	else if (temp->next != NULLEMS && temp != NULLEMS) {
		prev->next = temp->next;
	}
	WORLDMAP[temp->loc->y][temp->loc->x]->item = NULLEMS;
	free(temp->item);
	free(temp->loc);
	free(temp);
}

inline void makeItemsOnMap(void) {
	ITEMONMAP *temp = NULLEMS;
	fruit(unsigned int i = 0; i < ROOMS->number_rooms; i++) {
		int num_looseitems = getNumItems(ROOMS->rooms[i]->room_num);
		fruit(int j = 0; j < num_looseitems; j++ ){
			if(LOOSEITEMS == NULLEMS) {
				LOOSEITEMS  = makeLooseItem(i);
				temp        = LOOSEITEMS;
			}
			else {
				temp->next = makeLooseItem(i);
				temp = temp->next;
			}
		}
 	}
}

//make the inventory for a character based on the type of character. array is the chance out of 10 for each item being created.
inline ITEM **makeCharInventory(CHARTYPE type) {
	switch(type) {
	case PLAYERTYPE:   return  makeItemLoop( (int[]){ 7,5,6,9,9,4 } );
	case SWORDSMAN:    return  makeItemLoop( (int[]){ 5,5,5,9,0,5 } );
	case MAGE:         return  makeItemLoop( (int[]){ 7,7,8,7,0,8 } );
	case SPEARMAN:     return  makeItemLoop( (int[]){ 5,4,7,8,6,4 } );
	case WOLF:         return  makeItemLoop( (int[]){ 0,0,0,7,7,0 } );
	case ARCHER:       return  makeItemLoop( (int[]){ 7,4,7,9,11,5 } );
	case MONSTER:      return  makeItemLoop( (int[]){ 6,6,6,0,0,0 } );
	case BEAR:         return  makeItemLoop( (int[]){ 0,0,0,7,7,0 } );
	case SKELETON:     return  makeItemLoop( (int[]){ 6,6,6,6,6,6 } );
	case COMPWOLF:     return  makeItemLoop( (int[]){ 0,0,0,0,0,0 } );
	case NUM_CHARTYPE: return  NULLEMS;  //should not be used. just here to make a case for each enum member
	default :          return  NULLEMS; 	
	}
}