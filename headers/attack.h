/*                                           ### description ###                       

*/

//---------------------------------------------- headers -------------------------------------------------
#pragma  once
#include "gamepieces.h"
#include <stdlib.h> 
#include <ncurses.h>

//---------------------------------------------- enums ---------------------------------------------------

//---------------------------------------------- define --------------------------------------------------

//---------------------------------------------- typedefs ------------------------------------------------

//---------------------------------------------- structs -------------------------------------------------


//---------------------------------------------- global vars ---------------------------------------------
extern CHARACTER  *PLAYER;
extern CHARACTER  *COMPANION;
extern ENEMY      *ENEMIES;
extern int         PLAY;
//---------------------------------------------- prototypes ----------------------------------------------

        void             checkEffects        (CHARACTER *const character);
inline  void             applyPosionDamage   (CHARACTER *const character);
inline  void             recoverSlowHealth   (CHARACTER *const character);
inline  void             applyFireDamage     (CHARACTER *const character);
inline  void             applyBleedingDamage (CHARACTER *const character);
inline  void             applyElectrocution  (CHARACTER *const character);
inline  void             applyFrightend      (CHARACTER *const character);
inline  void             recoverFoodHealth   (CHARACTER *const character);
        int              playerAttack        (CHARACTER *const attacker,CHARACTER *const defender);
        int              swordsmanAttack     (CHARACTER *const attacker,CHARACTER *const defender);
        int              mageAttack          (CHARACTER *const attacker,CHARACTER *const defender);
        int              spearmanAttack      (CHARACTER *const attacker,CHARACTER *const defender);
        int              wolfAttack          (CHARACTER *const attacker,CHARACTER *const defender);
        int              archerAttack        (CHARACTER *const attacker,CHARACTER *const defender);
        int              bearAttack          (CHARACTER *const attacker,CHARACTER *const defender);
        int              skeletonAttack      (CHARACTER *const attacker,CHARACTER *const defender);
        int              monsterAttack       (CHARACTER *const attacker,CHARACTER *const defender);
        void             engageCombat        (CHARACTER *const character);
        attack_fpointer  makeCharAtack       (CHARTYPE type);

//---------------------------------------------- prototypes in other files -------------------------------
extern void         printToPrompt               (const int x, const int y, const char *const str);
extern void         restoreMainWin              (void); 
extern void         clearMainWin                (void);
extern void         copyMainWin                 (void);
extern void         clearPromptWin              (void);
extern int          checkIfHealthPotion         (CHARACTER *const attacker);
extern int          playerUseItem               (void);
extern int          checkIfValidItem            (const unsigned int item);
extern int          UseItem                     (ITEMTYPE item,CHARACTER *const attacker,CHARACTER *const defender);
extern int          computerCheckItem           (CHARACTER *const attacker,CHARACTER *const defender);
extern int          playerDisplayInventory      (void);
extern int          accessPlayerInventory       (void);
extern void         printTilePiece              (const int x, const int y);
extern void         clearPromptWin              (void);
extern void         printCombatScreen           (const CHARACTER *const character);
extern void         restoreMainWinFromCombat    (void); 
extern void         copyMainWin                 (void);
extern void         clearCombatPrompt           (void);
extern void         printToCombatPrompt         (const int x, const int y, const char *const str);
extern void         printCombatPrompt           (void);
extern void         updateStatsWin              (void);
extern void         clearStatsWin               (void);
extern int          useItem                     (const ITEMTYPE item, CHARACTER *const attacker,CHARACTER *const defender);
extern CHARACTER    *itemUseOn                  (void);
extern void         restoreMainWinFromInventory (void);


