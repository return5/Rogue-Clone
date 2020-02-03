//---------------------------------------- headers -----------------------------------------------


//---------------------------------------- define -------------------------------------------------
#pragma once
//---------------------------------------- enums -------------------------------------------------

enum ITEMTYPE    {HEALTHPIPE,POISONPOTION,SLOWHEALTH,FOOD,ARROW,FIRECHARGE,NUM_TYPE};     //type of items. used to sort them
enum CHARTYPE    {SWORDSMAN,MAGE,SPEARMAN,WOLF,ARCHER,BEAR,MONSTER,SKELETON,NUM_CHARTYPE,COMPWOLF,PLAYERTYPE};   //type of character
enum CHARCOLOR   {BLUECHAR = 1,REDCHAR,MAGENTACHAR,YELLOWCHAR,GREENCHAR,CYANCHAR,WHITECHAR,BLACKCHAR};
enum PLAYERCLASS {WARRIOR,PLAYER_ARCHER,ANIMAL_WHISPER};
enum ATTACKTYPE  {REGULAR,BLEEDING,ELECTRIC,FRIGHTEND};
enum MOVEMENT    {UP,DOWN,LEFT,RIGHT,NO_MOVE};
//---------------------------------------- typedefs  -----------------------------------------------
typedef  struct  LOCATION    LOCATION;
typedef  struct  ITEM        ITEM;
typedef  struct  CHARACTER   CHARACTER;
typedef  struct  FLAGS       FLAGS;
typedef  struct  ENEMY       ENEMY;
typedef  enum    ITEMTYPE    ITEMTYPE;
typedef  enum    CHARTYPE    CHARTYPE;
typedef  enum    CHARCOLOR   CHARCOLOR;
typedef  enum    ATTACKTYPE  ATTACKTYPE;
typedef  enum 	 PLAYERCLASS PLAYERCLASS;
typedef  enum    MOVEMENT    MOVEMENT;
typedef  int     (*item_fpointer)   (const ITEM *item,          CHARACTER *character);                        //function pointer which allows character to use an item
typedef  int     (*attack_fpointer) (CHARACTER *const attacker, CHARACTER *const defender);   //function pointer which a character uses to attack
typedef  void    (*model_fpointer)   (void);
//---------------------------------------- structs -----------------------------------------------

struct LOCATION {
	unsigned int x,y;
};

struct ITEM {
	char                *name, *description;  //name of item, description of item
	ITEMTYPE            type;                //value for type of item. used for sorting items
	int                 value;              //generic value for what it does, like how much health to damage/heal.
	unsigned int        number_items;      //number of items
	item_fpointer       useItem;          //function pointer to function which allows the use of the item
};

struct FLAGS {
	unsigned  short  poisoned;	  //is character poisoned?
	unsigned  short  ate;         //did character eat
	unsigned  short  onfire;      //is character on fire 
	unsigned  short  slowhealth;  //is character under influence of slow health potion    
	unsigned  short  bleeding;    //is character bleeding?
	unsigned  short  defending;
	unsigned  short  electrocuted; 
	unsigned  short  frightend;
	unsigned  short  missedturns;
	unsigned  short  damageperturn;
};
struct CHARACTER {
	char              *name;		              //name of character
	char              icon;			 		     //icon to displat on screen			   
	CHARTYPE          type;					    //type of character
	int               health,max_health;       //character health
	int               attack,max_attack;	  //character attack values  
	int               defense,max_defense;   //character defense values
	int               level;                //current level of character
	int               dodge;               //chance to dodge an attack
	int 			  attack_chance;      //chance to success when attack
	int               has_comp;			 //flag for if character has a companion
	MOVEMENT          prev_move;       //previous direction character moved
	LOCATION          *current_loc;   //current location for character
	LOCATION          *prev_loc;      //character's location on the previous turn
	FLAGS             *flags;         //struct holding status flags
	CHARCOLOR         color;         //color of the icon to display
	ITEM              **inventory;   //inventory of items being held
	attack_fpointer   charAttack;    //function pointer which pointers to function which a character uses to attack
	model_fpointer    printCharModel;
};

struct ENEMY {
	CHARACTER  *character;
	int i;
	ENEMY      *next;
};

//---------------------------------------- global vars ----------------------------------------------
PLAYERCLASS PLAYER_CLASS;