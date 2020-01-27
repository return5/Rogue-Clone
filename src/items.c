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
static  int  VALUE_HEALTH;
static  int  VALUE_POISON;
static  int  VALUE_SLOWHEALTH;
static  int  VALUE_FIRECHARGE;
static  int  VALUE_FOOD;

//---------------------------------------------- code ----------------------------------------------------

//check if attacker has health items, and if so, use them
int checkIfHealthPotion(CHARACTER *const attacker) {
	if(attacker->inventory[HEALTHPOTION]->number_items > 0) {
		attacker->inventory[HEALTHPOTION]->useItem(attacker->inventory[HEALTHPOTION],attacker);
		attacker->inventory[HEALTHPOTION]->number_items--;
		return 1;
	}
	else if(attacker->inventory[SLOWHEALTH]->number_items > 0) {
		attacker->inventory[SLOWHEALTH]->useItem(attacker->inventory[SLOWHEALTH],attacker);
		attacker->inventory[SLOWHEALTH]->number_items--;
		return 1;
	}
	else if(attacker->inventory[FOOD]->number_items > 0) {
		attacker->inventory[FOOD]->useItem(attacker->inventory[FOOD],attacker);
		attacker->inventory[FOOD]->number_items--;
		return 1;
	}
	return 0;
}

int checkIfValidItem(const unsigned int item) {
	return(PLAYER->inventory[item] != NULL && PLAYER->inventory[item]->number_items > 0)? 1 : 0;
}

int playerUseItem(CHARACTER *const character) {
	if(character!= NULL) {
		unsigned int item = (unsigned int) (getch() - '0');
		if (checkIfValidItem(item))  {
			switch(PLAYER->inventory[item]->type) {
				case HEALTHPOTION://FALLTHROUGH
				case SLOWHEALTH  ://FALLTHROUGH
				case FOOD        ://FALLTHROUGH
				case POISONPOTION://FALLTHROUGH
				case FIRECHARGE  ://FALLTHROUGH
					PLAYER->inventory[item]->useItem(PLAYER->inventory[item],character);
					PLAYER->inventory[item]->number_items--;
					getch();
					return 1;
				case ARROW:
					PLAYER->inventory[item]->useItem(PLAYER->inventory[item],character);
					//FALLTHROUGH
				case NUM_TYPE://FALLTHROUGH
				default: return 0;
			}
		}
	}
	return 0;
}

//check if character has an item, and if so, use it.
int useItem(CHARACTER *const attacker,CHARACTER *const defender) {
	if(attacker->health <= attacker->max_health / 2 && checkIfHealthPotion(attacker)) {
		return 1;
	}
	if(attacker->inventory[FIRECHARGE]->number_items > 0 && attacker->type != SKELETON) {
		attacker->inventory[FIRECHARGE]->useItem(attacker->inventory[FIRECHARGE],defender);
		return 1;
	}
	if(attacker->inventory[POISONPOTION]->number_items > 0) {
		attacker->inventory[POISONPOTION]->useItem(attacker->inventory[POISONPOTION],defender);
		return 1;
	}
	return 0;
}

int useHealthPotion(const ITEM *const item,CHARACTER *const character) {
	char c[40];
	snprintf(c,50,"%s used a %s",character->name,item->name);
	printToPrompt(0,0,c);
	character->health += item->value;
	character->health = (character->health > character->max_health)? character->max_health : character->health;
	return 1;
}

int usePoisonPotion(const ITEM *const item,CHARACTER *const character) {
	if(rand() % 10 > character->dodge) {
		char c[40];
		snprintf(c,40,"%s has been poisoned",character->name);
		printToPrompt(0,0,c);
		character->flags->poisoned = item->value;
		return 1;
	}
	return 0;
}

int useSlowHealthPotion(const ITEM *const item,CHARACTER *const character) {
	char c[40];
	snprintf(c,40,"%s used a %s",character->name,item->name);
	printToPrompt(0,0,c);
	character->flags->slowhealth = item->value;
	return 1;
}

int useFood(const ITEM *const item,CHARACTER *const character) {
	char c[40];
	snprintf(c,40,"%s used a %s",character->name,item->name);
	printToPrompt(0,0,c);
	character->flags->ate = item->value;
	return 1;
}

int useArrow(__attribute__((unused))const ITEM *const item,__attribute__((unused))CHARACTER *const character) {
	return 0;
}

int useFireCharge(const ITEM *const item,CHARACTER *const character) {
	if(rand() % 10 > character->dodge) {
		char c[40];
		snprintf(c,40,"%s was hit with a firecharge",character->name);
		printToPrompt(0,0,c);
		character->health -= 5;
		if(rand() % 10 > character->dodge) {
			char d[40];
			snprintf(d,40,"%s is on fire",character->name);
			printToPrompt(0,1,d);
			character->flags->onfire = item->value;
			return 1;
		}
		return 0;
	}
	return -1;
}

//sets the function pointer to the function which governs that item's use. 
static item_fpointer getItemFPointer(ITEMTYPE type) {
	switch(type) {
		case HEALTHPOTION: return  useHealthPotion;
		case POISONPOTION: return  usePoisonPotion;
		case SLOWHEALTH:   return  useSlowHealthPotion;
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
		case HEALTHPOTION: return  VALUE_HEALTH;
		case POISONPOTION: return  VALUE_POISON;
		case SLOWHEALTH:   return  VALUE_SLOWHEALTH;
		case FOOD:         return  VALUE_FOOD;
		case ARROW:        return  5;
		case FIRECHARGE:   return  VALUE_FIRECHARGE;
		case NUM_TYPE:     return  -1;         //should not be used. just here to make a case for each enum member
		default :          return  -1; 
	}
}

//gives a description to each item. 
static char *makeItemDescription(ITEMTYPE type) {
	char *description = malloc(SIZE_ITEMDESCRIPTION);
	switch(type) {
		case HEALTHPOTION: snprintf(description,SIZE_ITEMDESCRIPTION,"Instantly resotres health points.");               break;          
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
		case HEALTHPOTION: snprintf(name,SIZE_ITEMNAME,"Instant Health Potion");     break;
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
	for(int i = HEALTHPOTION; i < NUM_TYPE; i++) {
		//make each individual item with a random chance to even be in that character's inventory.
		inventory[i] = makeItem(i,(((rand() % 11 )< item_chance[i]) ? 1 : 0), max_number_items[i]);
	}
	return inventory;	
}

//set values of the items to random values
void makeItemValues(void) {
	VALUE_HEALTH      =  (rand() % 6) + 5;
	VALUE_POISON      =  (rand() % 4) + 2;
	VALUE_SLOWHEALTH  =  (rand() % 7) + 4;
	VALUE_FOOD        =  (rand() % 2) + 2;
	VALUE_FIRECHARGE  =  (rand() % 5) + 4;
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
	case NUM_CHARTYPE: return  NULL;  //should not be used. just here to make a case for each enum member
	default :          return  NULL; 	
	}
}