//---------------------------------------- headers -----------------------------------------------


//---------------------------------------- define -------------------------------------------------
#pragma  once
#define  HEIGHT  30     //height of main_win   make sure to match these values with the ones in charmodels.h
#define  WIDTH   70	  //width of game_win   make sure to match these values with the ones in charmodels.h
#define  NULLEMS NULL

//---------------------------------------- enums -------------------------------------------------

enum ITEMTYPE     {HEALTHPIPE,POISONPOTION,SLOWHEALTH,FOOD,ARROW,FIRECHARGE,NUM_TYPE};     //type of items. used to sort them
enum CHARTYPE     {SWORDSMAN,MAGE,SPEARMAN,WOLF,ARCHER,BEAR,MONSTER,SKELETON,NUM_CHARTYPE,COMPWOLF,PLAYERTYPE};   //type of character
enum CHARCOLOR    {BLUECHAR = 1,REDCHAR,MAGENTACHAR,YELLOWCHAR,GREENCHAR,CYANCHAR,WHITECHAR,BLACKCHAR};
enum PLAYERCLASS  {WARRIOR,PLAYER_ARCHER,ANIMAL_WHISPER};
enum ATTACKTYPE   {REGULAR,BLEEDING,ELECTRIC,FRIGHTEND};
enum MOVEMENT     {UP,DOWN,LEFT,RIGHT,NO_MOVE};
enum ROOMCOL      {COLR1 = 5,COLR2 = 8,COLR3 = 5,COLR4 = 4,COLR5 = 9};            //number of columns each room has
enum ROOMROW      {ROWR1 = 7,ROWR2 = 5,ROWR3 = 12,ROWR4 = 15,ROWR5 = 17};	        //number of rows each room has
enum NUMROOMS     {R1,R2,R3,R4,R5,NUM_ROOMS};	       
enum ROOMREVEALED {NO,YES};    
enum TILEREVEALED {NOT_REVEALED,REVEALED};
//---------------------------------------- typedefs  -----------------------------------------------
typedef  struct  LOCATION     LOCATION;
typedef  struct  ITEM         ITEM;
typedef  struct  CHARACTER    CHARACTER;
typedef  struct  FLAGS        FLAGS;
typedef  struct  ENEMY        ENEMY;
typedef  struct  ITEMONMAP    ITEMONMAP;
typedef  struct  RLOCATION    RLOCATION;
typedef  struct  ROOMINFO     ROOMINFO;
typedef  struct  ROOMSARRAY   ROOMSARRAY;
typedef  struct  PATH         PATH;
typedef  struct  PATHARRAY    PATHARRAY;
typedef  struct  TILE         TILE;
typedef  enum    TILEREVEALED TILEREVEALED;
typedef  enum    ROOMCOL      ROOMCOL;
typedef  enum    ROOMROW      ROOMROW;
typedef  enum    NUMROOMS     NUMROOMS;
typedef  enum    ROOMREVEALED ROOMREVEALED;
typedef  enum    ITEMTYPE     ITEMTYPE;
typedef  enum    CHARTYPE     CHARTYPE;
typedef  enum    CHARCOLOR    CHARCOLOR;
typedef  enum    ATTACKTYPE   ATTACKTYPE;
typedef  enum 	 PLAYERCLASS  PLAYERCLASS;
typedef  enum    MOVEMENT     MOVEMENT;
typedef  int     (*item_fpointer)   (const ITEM *item,          CHARACTER *character);                        //function pointer which allows character to use an item
typedef  int     (*attack_fpointer) (CHARACTER *const attacker, CHARACTER *const defender);   //function pointer which a character uses to attack
typedef  void    (*model_fpointer)   (void);
//---------------------------------------- global vars ---------------------------------------------------
extern   ROOMSARRAY  *ROOMS;
extern   PATHARRAY   *PATHS;
extern   TILE        *WORLDMAP[HEIGHT][WIDTH];
extern   CHARACTER   *PLAYER;
extern   ITEMONMAP   *LOOSEITEMS;
extern   int         FIRE_DAMAGE;
extern	 int         POISON_DAMAGE;
extern	 int         SLOW_RESTORE;
extern	 int         FOOD_RESTORE;
extern   int         HEALTH_RESTORE;
extern   int         BLEEDING_DAMAGE;
//---------------------------------------- structs ------------------------------------------------------
struct LOCATION {
	unsigned int x,y;
};

struct ITEM {
	char                *name, *description;  //name of item, description of item
	ITEMTYPE            type;                //type of item. 
	unsigned int        number_items;      //number of items
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
	unsigned  short  missedturn;
};

struct CHARACTER {
	char              *name;		                                //name of character
	char              icon;			 	                  	     //icon to displat on screen			   
	CHARTYPE          type;				                  	    //type of character
	int               health,max_health;                         //character health
	int               attack,max_attack;                  	  //character attack values  
	int               defense,max_defense;                   //character defense values
	int               level;                                  //current level of character
	int               dodge;                                 //chance to dodge an attack
	int 			  attack_chance,max_achance;           //max chance to success when attack
	int               has_comp;			                   //flag for if character has a companion
	int 			  incombat;
	MOVEMENT          prev_move;                         //previous direction character moved
	LOCATION          *current_loc;                     //current location for character
	LOCATION          *prev_loc;                        //character's location on the previous turn
	FLAGS             *flags;                           //struct holding status flags
	CHARCOLOR         color;                           //color of the icon to display
	ITEM              **inventory;                     //inventory of items being held
	attack_fpointer   charAttack;                      //function pointer which pointers to function which a character uses to attack
	model_fpointer    printCharModel;
};

struct ENEMY {
	CHARACTER  *character;
	int i;
	ENEMY      *next;
};

struct ITEMONMAP {
	ITEM       *item;
	LOCATION   *loc;
	ITEMONMAP  *next;
};

struct ROOMINFO {
	int          room_size;
	ROOMCOL      col_len;
	ROOMROW      row_len;
	ROOMREVEALED isrevealed;
	NUMROOMS     room_num;
	CHARCOLOR    color;
	char         **room;
	LOCATION    *loc;
};

struct ROOMSARRAY {
	ROOMINFO      **rooms;
	unsigned int  number_rooms;
};

struct TILE {
	char          icon;
	TILEREVEALED  isrevealed;
	ITEM          *item;
	ROOMINFO      *room;
	CHARCOLOR      color;
};

//---------------------------------------- global vars ----------------------------------------------
PLAYERCLASS PLAYER_CLASS;