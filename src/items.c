/*                                           ### description ###                       
	functions to make items and also to use items. 
*/

//---------------------------------------------- headers -------------------------------------------------
#include "items.h"

//---------------------------------------------- prototypes ----------------------------------------------

static  item_fpointer  getItemFPointer        (ITEMTYPE type);
static  int            getItemValue           (ITEMTYPE type);
static  char           *makeItemDescription   (ITEMTYPE type);
static  char           *makeItemName          (ITEMTYPE type);
static  ITEM           *makeItem              (ITEMTYPE type,const int has_item,const int max_num_item);
static  ITEM           **makeItemLoop         (const int item_chance[NUM_TYPE]);
//---------------------------------------------- define --------------------------------------------------

//---------------------------------------------- enums ---------------------------------------------------


//---------------------------------------------- typedefs ------------------------------------------------


//---------------------------------------------- structs -------------------------------------------------


//---------------------------------------------- global vars ---------------------------------------------
static  const  size_t  SIZE_ITEM             =  sizeof(ITEM);
static  const  size_t  SIZE_INVENTORY        =  SIZE_ITEM * NUM_TYPE;
static  const  size_t  SIZE_ITEMNAME         =  sizeof(char) * 25;
static  const  size_t  SIZE_ITEMDESCRIPTION  =  sizeof(char) * 47;


//global vars to set value for the respective item
static  int  TURNS_POISON;
static  int  TURNS_SLOWHEALTH;
static  int  TURNS_FIRECHARGE;
static  int  TURNS_FOOD;
static	int  FIRE_DAMAGE;
static	int  POISON_DAMAGE;
static	int  SLOW_RESTORE;
static	int  FOOD_RESTORE;
static  int  HEALTH_RESTORE;

//---------------------------------------------- code ----------------------------------------------------

//randomly select a helath item to use. if character has one in inventory, return it to be used. if not, randomly choose another
ITEMTYPE chooseHealthItem(const CHARACTER *const attacker) {
	switch(rand() % 3) {
		case 0:
			if(attacker->inventory[HEALTHPIPE]->number_items > 0) {
				return HEALTHPIPE;
			}
			break;
		case 1:
			if(attacker->inventory[SLOWHEALTH]->number_items > 0) {
				return SLOWHEALTH;
			}
			break;
		case 2:
			if(attacker->inventory[FOOD]->number_items > 0) {
				return FOOD;
			}
			break;
		default: // do nothing
			break;
	}
	return chooseHealthItem(attacker);
}

int checkIfValidItem(const unsigned int item) {
	return(PLAYER->inventory[item] != NULL && PLAYER->inventory[item]->number_items > 0)? 1 : 0;
}

int charUseItem(CHARACTER *const character, CHARACTER *const defender,ITEMTYPE item) {
	char c[50];
	switch(item) {
		case HEALTHPIPE  ://FALLTHROUGH
		case SLOWHEALTH  ://FALLTHROUGH
		case FOOD        :
			snprintf(c,50,"%s uses %s",character->name,character->inventory[item]->name);
			printToCombatPrompt(0,0,c);
			character->inventory[item]->useItem(character->inventory[item],character);
			character->inventory[item]->number_items--;
			return 1;
		case POISONPOTION://FALLTHROUGH
		case FIRECHARGE  :
			snprintf(c,50,"%s uses %s",character->name,character->inventory[item]->name);
			printToCombatPrompt(0,0,c);
			character->inventory[item]->useItem(character->inventory[item],defender);
			character->inventory[item]->number_items--;
			return 1;
		case ARROW   : //FALLTHROUGH
		case NUM_TYPE://FALLTHROUGH
		default: return 0;
	}
}

//check if character has an item, and if so, use it.
int computerCheckItem(CHARACTER *const attacker,CHARACTER *const defender) {
	//if attacker helath is less than half and attacker has an health item, select one to use
	if(attacker->health <= attacker->max_health / 2 && (attacker->inventory[HEALTHPIPE]->number_items > 0 || attacker->inventory[SLOWHEALTH]->number_items > 0 ||attacker->inventory[FOOD]->number_items > 0)) {
		return charUseItem(attacker,defender,chooseHealthItem(attacker));
	}
	if(attacker->inventory[FIRECHARGE]->number_items > 0 && attacker->type != SKELETON) {
		attacker->inventory[FIRECHARGE]->number_items--;
		return charUseItem(defender,defender,FIRECHARGE);
	}
	if(attacker->inventory[POISONPOTION]->number_items > 0) {
		attacker->inventory[POISONPOTION]->number_items--;
		return charUseItem(defender,defender,POISONPOTION);
	}
	return 0;
}

int useHEALTHPIPE(const ITEM *const item,CHARACTER *const character) {
	char c[22];
	snprintf(c,22,"restored %d health",item->value);
	printToCombatPrompt(0,1,c);
	character->health += item->value;
	character->health = (character->health > character->max_health)? character->max_health : character->health;
	return 1;
}

int usePoisonPotion(const ITEM *const item,CHARACTER *const character) {
	if(rand() % 10 > character->dodge) {
		char c[40];
		snprintf(c,40,"%s has been poisoned",character->name);
		printToCombatPrompt(0,1,c);
		character->flags->poisoned = TURNS_POISON;
		character->health += item->value;
		character->flags->damageperturn = item->value;
		return 1;
	}
	printToCombatPrompt(0,1,"missed");
	return 0;
}

int useSlowHEALTHPIPE(const ITEM *const item,CHARACTER *const character) {
	character->flags->slowhealth = TURNS_SLOWHEALTH;
	character->flags->damageperturn = item->value;
	return 1;
}

int useFood(const ITEM *const item,CHARACTER *const character) {
	char c[22];
	snprintf(c,22,"restored %d health",item->value);
	printToCombatPrompt(0,1,c);
	character->flags->ate = TURNS_FOOD;
	character->health += FOOD_RESTORE;
	character->flags->damageperturn = item->value;
	character->health = (character->health > character->max_health)? character->max_health : character->health;
	return 1;
}

int useArrow(__attribute__((unused))const ITEM *const item,__attribute__((unused))CHARACTER *const character) {
	return 0;
}

int useFireCharge(const ITEM *const item,CHARACTER *const character) {
	if(rand() % 10 > character->dodge) {
		char c[40];
		snprintf(c,40,"%s was hit with a firecharge",character->name);
		printToCombatPrompt(0,1,c);
		character->health += item->value;
		if(rand() % 10 > character->dodge) {
			char d[40];
			snprintf(d,40,"%s is on fire",character->name);
			printToCombatPrompt(0,2,d);
			character->flags->onfire = TURNS_FIRECHARGE;
			character->flags->damageperturn = item->value;
			return 1;
		}
		return 0;
	}
	printToCombatPrompt(0,1,"missed.");
	return -1;
}

//sets the function pointer to the function which governs that item's use. 
static item_fpointer getItemFPointer(ITEMTYPE type) {
	switch(type) {
		case HEALTHPIPE:   return  useHEALTHPIPE;
		case POISONPOTION: return  usePoisonPotion;
		case SLOWHEALTH:   return  useSlowHEALTHPIPE;
		case FOOD:         return  useFood;
		case ARROW:        return  useArrow;
		case FIRECHARGE:   return  useFireCharge;
		case NUM_TYPE:     return  NULL;        //should not be used. just here to make a case for each enum member
		default :          return  NULL; 
	}
}

//sets the 'value' variable for each item. this is used when the item is used by a character
static int getItemValue(ITEMTYPE type) {
	switch(type) {
		case HEALTHPIPE:   return  HEALTH_RESTORE;
		case POISONPOTION: return  POISON_DAMAGE;
		case SLOWHEALTH:   return  SLOW_RESTORE;
		case FOOD:         return  FOOD_RESTORE;
		case ARROW:        return  5;
		case FIRECHARGE:   return  FIRE_DAMAGE;
		case NUM_TYPE:     return  -1;         //should not be used. just here to make a case for each enum member
		default :          return  -1; 
	}
}

//gives a description to each item. 
static char *makeItemDescription(ITEMTYPE type) {
	char *description = malloc(SIZE_ITEMDESCRIPTION);
	switch(type) {
		case HEALTHPIPE:   snprintf(description,SIZE_ITEMDESCRIPTION,"Instantly resotres health points.");               break;          
		case POISONPOTION: snprintf(description,SIZE_ITEMDESCRIPTION,"Can be thrown at an enemy to poison them.");       break;  
		case SLOWHEALTH:   snprintf(description,SIZE_ITEMDESCRIPTION,"Regenerate health points over time.");             break;
		case FOOD:         snprintf(description,SIZE_ITEMDESCRIPTION,"Food. you can eat it.");                           break;
		case ARROW:        snprintf(description,SIZE_ITEMDESCRIPTION,"Arrow. can be shot with a bow");                   break; 
		case FIRECHARGE:   snprintf(description,SIZE_ITEMDESCRIPTION,"use Fire Charge against an enemy to burn them.");  break;
		case NUM_TYPE:     snprintf(description,SIZE_ITEMDESCRIPTION,"num_type");                                        break; //should not be used. just here to make a case for each enum member                              break; 
		default :          description = NULL;                                                                           break;
		
	}
	return description;
}

//gives a name to each item
static char *makeItemName(ITEMTYPE type) {
	char *name = malloc(SIZE_ITEMNAME);
	switch(type) {
		case HEALTHPIPE:   snprintf(name,SIZE_ITEMNAME,"Health PIPE");               break;
		case POISONPOTION: snprintf(name,SIZE_ITEMNAME,"Poison Potion");             break;
		case SLOWHEALTH:   snprintf(name,SIZE_ITEMNAME,"Slow Health Potion");        break;
		case FOOD:         snprintf(name,SIZE_ITEMNAME,"Food");                      break;
		case ARROW:        snprintf(name,SIZE_ITEMNAME,"Arrow");                     break;
		case FIRECHARGE:   snprintf(name,SIZE_ITEMNAME,"Fire Charge");               break;
		case NUM_TYPE:     snprintf(name,SIZE_ITEMNAME,"num_type");                  break;
		default :          name =  NULL;                                             break; //should not be used. just here to make a case for each enum member
		
	}
	return name;
}

//make an individual item based on its type.
static ITEM *makeItem(ITEMTYPE type, const int has_item,const int max_num_item) {
	ITEM *item          =  malloc(SIZE_ITEM);
	item->name          =  makeItemName(type);
	item->description   =  makeItemDescription(type);
	item->type          =  type;
	item->value         =  getItemValue(type);
	item->number_items  =  (has_item != 0) ? (rand() % max_num_item) + 1 : 0;//get random number in range [has_item - (max_num_item * has_item)
	item->useItem       =  getItemFPointer(type);
	return item;
}

//go through each item type and fill in the inventory array with hem. 
static ITEM **makeItemLoop(const int item_chance[NUM_TYPE]) {
	ITEM **inventory = malloc(SIZE_INVENTORY);
	const int max_number_items[] = { 4,3,4,6,10,3 };
	for(int i = HEALTHPIPE; i < NUM_TYPE; i++) {
		//make each individual item with a random chance to even be in that character's inventory.
		inventory[i] = makeItem(i,(((rand() % 11 )< item_chance[i]) ? 1 : 0), max_number_items[i]);
	}
	return inventory;	
}

//set values of the items to random values
void makeItemValues(void) {
	TURNS_POISON      =  (rand() % 3) + 3;
	TURNS_SLOWHEALTH  =  (rand() % 3) + 3;
	TURNS_FOOD        =  (rand() % 6) + 5;
	TURNS_FIRECHARGE  =  (rand() % 3) + 1;
	FIRE_DAMAGE		  =  -1 * (rand() % 3) + 3;
	POISON_DAMAGE     =  -1 * (rand() % 4) + 1;
	SLOW_RESTORE	  =  (rand() % 3) + 4;
	FOOD_RESTORE      =  (rand() % 3) + 2;
	HEALTH_RESTORE    =  (rand() % 6) + 5;
}
//make the inventory for a character based on teh type of character. array is the chance out of 10 for each item being created.
ITEM **makeCharInventory(CHARTYPE type) {
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
	case NUM_CHARTYPE: return  NULL;  //should not be used. just here to make a case for each enum member
	default :          return  NULL; 	
	}
}