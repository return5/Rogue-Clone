/*                                           ### description ###                       

*/

//---------------------------------------------- headers -------------------------------------------------
#include "characters.h"
#include <stdlib.h> 
#include <ncurses.h>

//---------------------------------------------- enums ---------------------------------------------------

//---------------------------------------------- define --------------------------------------------------

//---------------------------------------------- typedefs ------------------------------------------------

//---------------------------------------------- structs -------------------------------------------------


//---------------------------------------------- global vars ---------------------------------------------
extern CHARACTER *PLAYER;
//---------------------------------------------- prototypes ----------------------------------------------
int  playerAttack              (CHARACTER *const attacker,CHARACTER *const defender);
int  swordsmanAttack           (CHARACTER *const attacker,CHARACTER *const defender);
int  mageAttack                (CHARACTER *const attacker,CHARACTER *const defender);
int  spearmanAttack            (CHARACTER *const attacker,CHARACTER *const defender);
int  wolfAttack                (CHARACTER *const attacker,CHARACTER *const defender);
int  archerAttack              (CHARACTER *const attacker,CHARACTER *const defender);
int  bearAttack                (CHARACTER *const attacker,CHARACTER *const defender);
int  skeletonAttack            (CHARACTER *const attacker,CHARACTER *const defender);
int  monsterAttack             (CHARACTER *const attacker,CHARACTER *const defender);
void combatLoop            	   (CHARACTER *const character1,CHARACTER *const character2);
void resetAttributes           (CHARACTER *const character);
attack_fpointer   makeCharAtack(CHARTYPE type);

//---------------------------------------------- prototypes in other files -------------------------------
void  printToPrompt       (const int x, const int y, const char *const str);
void  restoreMainWin      (void); 
void  clearMainWin        (void);
void  copyMainWin         (void);
void  clearPromptWin      (void);
int   checkIfHealthPotion (CHARACTER *const attacker);
int   playerUseItem       (void);
int   checkIfValidItem    (const unsigned int item);
int   useItem             (CHARACTER *const attacker,CHARACTER *const defender);
int   playerDisplayInventory (void);