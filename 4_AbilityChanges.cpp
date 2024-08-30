#include "codeinjection_new.h"
#include "kPrint.h"

extern "C"
{

    bool PersonalCheckIfMoveCondition(BattleMon *a1, MoveCondition a2)
    {
        if (a1->HeldItem == 289 && a2 == CONDITION_TAUNT)
        {
            return true;
        }
        else if (a2 == CONDITION_BLOCK && ((a1->Conditions[CONDITION_CURSE] & 7) != 0))
        {
            return true;
        }
        else
        {
            return (a1->Conditions[a2] & 7) != 0;
        }
    }

    void HandlerOvercoatPowders(int a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_Message *v7; // r0
        int moveId;
        int result;
        moveId = BattleEventVar_GetValue(VAR_MOVE_ID);

        if (moveId == 79 || moveId == 147 || moveId == 76 || moveId == 77 || moveId == 139)
        {
            result = BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1);
            if (result)
            {
                BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, (int)a3);
                v7 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
                BattleHandler_StrSetup(&v7->str, 2u, 210);
                BattleHandler_AddArg(&v7->str, (int)a3);
                BattleHandler_PopWork(a2, v7);
                BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, (int)a3);
            }
        }
    }

    bool checksIfWildBattle(ServerFlow *a1)
    {
        // k::Printf("\nBtlType is %d\n", a1->mainModule->btlSetup->BtlType);
        return a1->mainModule->btlSetup->btlType == 0;
    }

    bool checkForPaybackBoost(ServerFlow *a1, BattleMon *AttackingMon, BattleMon *DefendingMon)
    {
        int *ActionOrderAttackingMon;
        int *ActionOrderDefendingMon;

        if (BattleMon_GetTurnFlag(DefendingMon, TURNFLAG_ACTIONDONE))
        {
            return true;
        }
        // k::Printf("\n\nDid we get this far?\n", ActionOrderAttackingMon);
        ActionOrderAttackingMon = ActionOrder_SearchByMonID(a1, AttackingMon->ID);
        ActionOrderDefendingMon = ActionOrder_SearchByMonID(a1, DefendingMon->ID);
        // k::Printf("The action order for the attacking mon is %d\n", ActionOrderAttackingMon);
        // k::Printf("The action order for the defending mon is %d\n\n", ActionOrderDefendingMon);
        if (ActionOrderAttackingMon > ActionOrderDefendingMon)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    int THUMB_BRANCH_HandlerPayback(int a1, ServerFlow *a2, int a3)
    {
        int result; // r0
        int result2;
        unsigned __int8 Value;   // r0
        BattleMon *DefendingMon; // r0
        BattleMon *AttackingMon;
        bool paybackBoost;

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            Value = BattleEventVar_GetValue(VAR_DEFENDING_MON);
            DefendingMon = Handler_GetBattleMon(a2, Value);
            AttackingMon = Handler_GetBattleMon(a2, result);

            paybackBoost = checkForPaybackBoost(a2, AttackingMon, DefendingMon);

            if (paybackBoost)
            {
                return MultiplyBasePower(2);
            }
        }
        return result;
    }

    bool checkIfConsumableItem(int a1)
    {
        return (PML_ItemIsBerry(a1) ||
                a1 == 290 ||
                a1 == 43 ||
                (a1 >= 545 && a1 <= 564) ||
                a1 == 292 ||
                a1 == 291 ||
                a1 == 274 ||
                a1 == 542 ||
                a1 == 294 ||
                a1 == 543 ||
                a1 == 275 ||
                a1 == 219 ||
                a1 == 214 ||
                a1 == 271 ||
                a1 == 541);
    }

    // // For Unnerve
    // // a1 is the position of the pokemon with unnerve
    // // a2 is the ServerFlow
    // // a3 is the type of skip i think
    // // a6 is supposedly the side of
    bool THUMB_BRANCH_SAFESTACK_HandlerUnnerveSkipCheck(BattleEventItem *a1, int a2, int a3, int a4, u16 a5, unsigned __int8 a6)
    {
        int PokeID;  // r0
        bool result; // r0

        result = 0;
        if (a3 == 5)
        {
            PokeID = BattleEventItem_GetPokeID(a1);
            if (!MainModule_IsAllyMonID(PokeID, a6))
            {
                if (checkIfConsumableItem(a5))
                {
                    return 1;
                }
            }
        }
        return result;
    }

    void THUMB_BRANCH_SAFESTACK_HandlerRegenerator(int a1, ServerFlow *a2, unsigned int *a3)
    {
        BattleMon *PokeParam;      // r6
        unsigned int v6;           // r4
        unsigned int v7;           // r0
        HandlerParam_ChangeHP *v8; // r0
        int Value;                 // [sp+0h] [bp-18h]

        if (a3 == (unsigned int *)BattleEventVar_GetValue(VAR_MON_ID))
        {
            PokeParam = Handler_GetBattleMon(a2, (int)a3);
            if (!BattleMon_IsFainted(PokeParam) && !BattleMon_IsFullHP(PokeParam))
            {
                v6 = DivideMaxHPZeroCheck(PokeParam, 4u);
                Value = BattleMon_GetValue(PokeParam, VALUE_MAX_HP);
                v7 = Value - BattleMon_GetValue(PokeParam, VALUE_CURRENT_HP);
                if (v6 > v7)
                {
                    v6 = v7;
                }
                v8 = (HandlerParam_ChangeHP *)BattleHandler_PushWork(a2, EFFECT_CHANGEHP, (int)a3);
                v8->pokeID[0] = (int)a3;
                v8->volume[0] = v6;
                v8->poke_cnt = 1;
                v8->fEffectDisable = 1;
                BattleHandler_PopWork(a2, v8);
            }
        }
    }

    // // For Fluffy
    void HandlerFluffy(int a1, int a2, int a3)
    {
        int result; // r0
        int Value;  // r0
        int isFire;
        int ratio;

        result = BattleEventVar_GetValue(VAR_DEFENDING_MON);
        if (a3 == result)
        {
            Value = BattleEventVar_GetValue(VAR_MOVE_ID);

            isFire = (PML_MoveGetType(Value) == TYPE_FIRE) ? 2 : 1;
            ratio = (getMoveFlag(Value, FLAG_CONTACT)) ? 2048 : 4096;

            // k::Printf("\n\n isFire is %d\nratio is %d\nisFire times Ratio is %d\n\n", isFire, ratio, isFire * ratio);

            BattleEventVar_MulValue(VAR_RATIO, isFire * ratio);
        }
    }

    void HandlerPickupNew(int a1, ServerFlow *a2, int a3)
    {
        BattleMon *BattleMon; // r6
        int UsedItem;
        HandlerParam_SetItem *v8; // r0

        // k::Printf("\nWe are inside the first loop of logic\n");
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            // k::Printf("\nWe are inside the second loop of logic\n");

            BattleMon = Handler_GetBattleMon(a2, a3);
            UsedItem = BattleMon_GetUsedItem(BattleMon);

            if (UsedItem && BattleMon_GetHeldItem(BattleMon) == 0)
            {
                // k::Printf("\nWe are inside the third loop of logic\n");
                v8 = (HandlerParam_SetItem *)BattleHandler_PushWork(a2, EFFECT_SET_HELD_ITEM, a3);
                v8->header.flags |= 0x800000u;
                v8->itemID = UsedItem;
                v8->pokeID = a3;
                v8->fClearConsume = 0;
                BattleHandler_StrSetup(&v8->exStr, 2u, 1162);
                BattleHandler_AddArg(&v8->exStr, a3);
                BattleHandler_AddArg(&v8->exStr, UsedItem);
                BattleHandler_PopWork(a2, v8);
            }
        }
    }

    // // Weak Armor
    void THUMB_BRANCH_HandlerWeakArmor(int a1, ServerFlow *a2, unsigned int *a3)
    {
        BattleMon *PokeParam;             // r7
        int v6;                           // r6
        HandlerParam_ChangeStatStage *v7; // r0
        HandlerParam_ChangeStatStage *v8; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && BattleEventVar_GetValue(VAR_MOVE_CATEGORY) == 1 && !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG))
        {
            PokeParam = Handler_GetBattleMon(a2, (int)a3);
            v6 = 0;
            if (BattleMon_IsStatChangeValid(PokeParam, 2u, -1) || BattleMon_IsStatChangeValid(PokeParam, 5u, 2))
            {
                v6 = 1;
            }
            if (v6)
            {
                if (!BattleMon_IsFainted(PokeParam))
                {
                    BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, (int)a3);
                    v7 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
                    v7->poke_cnt = 1;
                    v7->pokeID[0] = (unsigned int)a3;
                    v7->fMoveAnimation = 1;
                    v7->rankType = STATSTAGE_DEFENSE;
                    v7->rankVolume = -1;
                    BattleHandler_PopWork(a2, v7);
                    v8 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
                    v8->poke_cnt = 1;
                    v8->pokeID[0] = (unsigned int)a3;
                    v8->fMoveAnimation = 1;
                    v8->rankType = STATSTAGE_SPEED;
                    v8->rankVolume = 2;
                    BattleHandler_PopWork(a2, v8);
                    BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, (int)a3);
                }
            }
        }
    }

    // For Tough Claws
    void THUMB_BRANCH_HandlerCuteCharm(int a1, ServerFlow *a2, unsigned int *a3)
    {
        unsigned __int16 Value;           // r0
        int v6;                           // r6
        BattleMon *PokeParam;             // r7
        HandlerParam_ChangeStatStage *v8; // r4

        if (a3 == (unsigned int *)BattleEventVar_GetValue(VAR_DEFENDING_MON) && !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG))
        {
            Value = BattleEventVar_GetValue(VAR_MOVE_ID);
            if (getMoveFlag(Value, FLAG_CONTACT))
            {
                v6 = (unsigned __int8)BattleEventVar_GetValue(VAR_ATTACKING_MON);
                PokeParam = Handler_GetBattleMon(a2, v6);
                if (!BattleMon_IsFainted(PokeParam))
                {
                    BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, (int)a3);
                    v8 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
                    v8->poke_cnt = 1;
                    v8->pokeID[0] = (unsigned int)v6;
                    v8->fMoveAnimation = 1;
                    v8->rankType = STATSTAGE_SPEED;
                    v8->rankVolume = -1;
                    BattleHandler_PopWork(a2, v8);
                    BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, (int)a3);
                }
            }
        }
        return;
    }

    // Slush Rush
    void HandlerSlushRush(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && Handler_GetWeather(a2) == 3) // hail
        {
            BattleEventVar_MulValue(VAR_RATIO, 0x2000);
        }
    }

    // Tough Claws
    void HandlerToughClaws(int a1, int a2, int a3)
    {
        int result; // r0
        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            int MoveID = BattleEventVar_GetValue(VAR_MOVE_ID);
            if (getMoveFlag(MoveID, FLAG_CONTACT))
            {
                BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 5324);
            }
        }
    }

    // Heatproof
    void THUMB_BRANCH_HandlerHeatproofPower(int a1, int a2, int a3)
    {
        int result; // r0

        result = BattleEventVar_GetValue(VAR_DEFENDING_MON);
        if (a3 == result)
        {
            result = BattleEventVar_GetValue(VAR_MOVE_TYPE);
            if (result == 9)
            {
                BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 1024);
            }
        }
    }

    int THUMB_BRANCH_SAFESTACK_HandlerIceBody(int a1, ServerFlow *a2, int a3)
    {
        int result;                 // r0
        BattleMon *PokeParam;       // r7
        HandlerParam_RecoverHP *v8; // r5

        result = BattleEventVar_GetValue(VAR_WEATHER);
        if (result == 3)
        {
            result = BattleEventVar_GetValue(VAR_MON_ID);
            if (a3 == result)
            {
                PokeParam = Handler_GetBattleMon(a2, a3);
                v8 = (HandlerParam_RecoverHP *)BattleHandler_PushWork(a2, EFFECT_RECOVERHP, a3);
                v8->header.flags |= 0x800000u;
                v8->pokeID = a3;
                v8->recoverHP = DivideMaxHPZeroCheck(PokeParam, 0x8u);
                BattleHandler_PopWork(a2, v8);
                return BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
            }
        }
        else
        {
            result = BattleEventVar_GetValue(VAR_MON_ID);
            if (a3 == result)
            {
                PokeParam = Handler_GetBattleMon(a2, a3);
                v8 = (HandlerParam_RecoverHP *)BattleHandler_PushWork(a2, EFFECT_RECOVERHP, a3);
                v8->header.flags |= 0x800000u;
                v8->pokeID = a3;
                v8->recoverHP = DivideMaxHPZeroCheck(PokeParam, 0x10u);
                BattleHandler_PopWork(a2, v8);
                return BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
            }
        }
        return result;
    }

    //
    void HandlerPreBurnOnAI(int a1, ServerFlow *a2, int a3)
    {
        HandlerParam_AddCondition *v6;
        BattleMon *PokeParam; // r7

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && a3 >= 6 && !checksIfWildBattle(a2))
        {
            // k::Printf("\nWe are in, lets see if this works");
            PokeParam = Handler_GetBattleMon(a2, a3);
            if (BattleMon_HasType(PokeParam, TYPE_FIRE))
            {
                v6 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, (int)a3);
                v6->sickID = CONDITION_POISON;
                v6->sickCont = MakeBasicStatus(CONDITION_POISON);
                v6->fAlmost = 0;
                v6->pokeID = (unsigned __int8)a3;
                BattleHandler_StrSetup(&v6->exStr, 1u, 202);
                BattleHandler_AddArg(&v6->exStr, (int)a3);
                BattleHandler_PopWork(a2, v6);
            }
            else
            {
                v6 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, (int)a3);
                v6->sickID = CONDITION_BURN;
                v6->sickCont = MakeBasicStatus(CONDITION_BURN);
                v6->fAlmost = 0;
                v6->pokeID = (unsigned __int8)a3;
                BattleHandler_StrSetup(&v6->exStr, 1u, 201);
                BattleHandler_AddArg(&v6->exStr, (int)a3);
                BattleHandler_PopWork(a2, v6);
            }
        }
    }

    void HandlerPrePoisonOnAI(int a1, ServerFlow *a2, int a3)
    {
        HandlerParam_AddCondition *v6;
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && a3 >= 6 && !checksIfWildBattle(a2))
        {

            v6 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, (int)a3);
            v6->sickID = CONDITION_POISON;
            v6->sickCont = MakeBasicStatus(CONDITION_POISON);
            v6->fAlmost = 0;
            v6->pokeID = (unsigned __int8)a3;
            BattleHandler_StrSetup(&v6->exStr, 1u, 202);
            BattleHandler_AddArg(&v6->exStr, (int)a3);
            BattleHandler_PopWork(a2, v6);
        }
    }

    void HandlerPreParalysisOnAI(int a1, ServerFlow *a2, int a3)
    {
        HandlerParam_AddCondition *v6;
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && a3 >= 6 && !checksIfWildBattle(a2))
        {

            v6 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, (int)a3);
            v6->sickID = CONDITION_POISON;
            v6->sickCont = MakeBasicStatus(CONDITION_PARALYSIS);
            v6->fAlmost = 0;
            v6->pokeID = (unsigned __int8)a3;
            BattleHandler_StrSetup(&v6->exStr, 1u, 203);
            BattleHandler_AddArg(&v6->exStr, (int)a3);
            BattleHandler_PopWork(a2, v6);
        }
    }

    int checkHigher(int a1, int a2)
    {
        if (a1 < a2)
        {
            return a2;
        }
        return a1;
    }

    int HandlerToxicBoostStatus(int a1, int a2, int a3)
    {
        int result; // r0
        int Value;  // r0
        int v6;     // r0

        result = BattleEventVar_GetValue(VAR_MON_ID);
        if (a3 == result)
        {
            result = BattleEventVar_GetValue(VAR_CONDITION_ID);
            if (result == 4)
            {
                Value = BattleEventVar_GetValue(VAR_DAMAGE);
                v6 = checkHigher(Value / 2, 1);
                return BattleEventVar_RewriteValue(VAR_DAMAGE, v6);
            }
        }
        return result;
    }

    int HandlerCorrosion(int a1, ServerFlow *a2, int a3)
    {
        int result;

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result && BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_POISON)
        {
            return BattleEventVar_RewriteValue(VAR_SET_TYPE_EFFECTIVENESS, 4);
        }
        return result;
    }

    void HandlerDrySkinDamage(int a1, int a2, int a3)
    {
        int result; // r0

        result = BattleEventVar_GetValue(VAR_DEFENDING_MON);
        if (a3 == result)
        {
            result = BattleEventVar_GetValue(VAR_MOVE_TYPE);
            if (result == 9)
            {
                 BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 8192);
            }
        }
    }

    void HandlerToxicBoostDamage(int a1, int a2, int a3)
    {
        int result; // r0

        result = BattleEventVar_GetValue(VAR_DEFENDING_MON);
        if (a3 == result)
        {
            result = BattleEventVar_GetValue(VAR_MOVE_TYPE);
            if (result == TYPE_POISON)
            {
                 BattleEventVar_MulValue(VAR_RATIO, 2048);
            }
        }

    }


    typedef struct
    {
        int triggerValue;
        ABILITY_HANDLER_FUNC function;
    } ABILITY_TRIGGERTABLE;

    ABILITY_TRIGGERTABLE AbilityTriggerTable[] =
        {
            // {0x2D, (ABILITY_HANDLER_FUNC)HandlerOvercoatPowders},
            // {0x7F, (ABILITY_HANDLER_FUNC)HandlerOvercoat},

            {0x47, (ABILITY_HANDLER_FUNC)HandlerFriendGuard}, // 0
            {0x2D, (ABILITY_HANDLER_FUNC)HandlerTelepathy},   // 1
            {0x3B, (ABILITY_HANDLER_FUNC)HandlerPlusMinus},   // 2
            {0x2D, (ABILITY_HANDLER_FUNC)HandlerTelepathy},   // 3
            {0x76, (ABILITY_HANDLER_FUNC)HandlerHealer},      // 4
            {0x2D, (ABILITY_HANDLER_FUNC)HandlerTelepathy},   // 5

            {0x38, (ABILITY_HANDLER_FUNC)HandlerToughClaws}, // 6

            {0x13, (ABILITY_HANDLER_FUNC)HandlerSlushRush},        // 7
            {0x7F, (ABILITY_HANDLER_FUNC)HandlerSnowCloakWeather}, // 8

            {0x3B, (ABILITY_HANDLER_FUNC)HandlerThickFat},         // 9
            {0x7F, (ABILITY_HANDLER_FUNC)HandlerSnowCloakWeather}, // 10

            {0x3B, (ABILITY_HANDLER_FUNC)HandlerGuts},        // 11
            {0x55, (ABILITY_HANDLER_FUNC)HandlerPreBurnOnAI}, // 12

            {0x13, (ABILITY_HANDLER_FUNC)HandlerQuickFeet},     // 13
            {0x55, (ABILITY_HANDLER_FUNC)HandlerPrePoisonOnAI}, // 14

            {0x38, (ABILITY_HANDLER_FUNC)HandlerFlareBoost},  // 15
            {0x55, (ABILITY_HANDLER_FUNC)HandlerPreBurnOnAI}, // 16

            {0x6B, (ABILITY_HANDLER_FUNC)HandlerPoisonHeal},    // 17
            {0x55, (ABILITY_HANDLER_FUNC)HandlerPrePoisonOnAI}, // 18

            {0x38, (ABILITY_HANDLER_FUNC)HandlerToxicBoost},       // 19
            {0x55, (ABILITY_HANDLER_FUNC)HandlerPrePoisonOnAI},    // 20
            {0x6B, (ABILITY_HANDLER_FUNC)HandlerToxicBoostStatus}, // 21

            {0x47, (ABILITY_HANDLER_FUNC)HandlerFluffy},           // 22
            {0x7F, (ABILITY_HANDLER_FUNC)HandlerSnowCloakWeather}, // 23

            {0x2D, (ABILITY_HANDLER_FUNC)HandlerOvercoatPowders}, // 24
            {0x7F, (ABILITY_HANDLER_FUNC)HandlerOvercoat},        // 25

            {0x3E, (ABILITY_HANDLER_FUNC)HandlerCorrosion}, // 26

            {0x3C, (ABILITY_HANDLER_FUNC)HandlerMarvelScale},      // 27
            {0x55, (ABILITY_HANDLER_FUNC)HandlerPreParalysisOnAI}, // 28

            {0x7F, (ABILITY_HANDLER_FUNC)HandlerRainDish},              // 29
            {0x65, (ABILITY_HANDLER_FUNC)HandlerWaterVeil},             // 30
            {0x67, (ABILITY_HANDLER_FUNC)HandlerAddStatusFailedCommon}, // 31
            {0x8A, (ABILITY_HANDLER_FUNC)HandlerWaterVeilCureStatus},   // 32
            {0x55, (ABILITY_HANDLER_FUNC)HandlerWaterVeilCureStatus},   // 33
            {2, (ABILITY_HANDLER_FUNC)HandlerWaterVeilActionEnd},       // 34

            {0x5B, (ABILITY_HANDLER_FUNC)HandlerClearBodyCheck}, // 35
            {0x5C, (ABILITY_HANDLER_FUNC)HandlerClearBodyGuard}, // 36
            {0x7F, (ABILITY_HANDLER_FUNC)HandlerOvercoat},       // 37

            {0x7F, (ABILITY_HANDLER_FUNC)HandlerDrySkinWeather}, // 38
            {0x38, (ABILITY_HANDLER_FUNC)HandlerDrySkinDamage},  // 39
            {0x2D, (ABILITY_HANDLER_FUNC)HandlerDrySkinCheck},   // 40

            {0x54, (ABILITY_HANDLER_FUNC)HandlerPickupNew}, // 41

            {0x38, (ABILITY_HANDLER_FUNC)HandlerToxicBoost},       // 42
            {0x55, (ABILITY_HANDLER_FUNC)HandlerPrePoisonOnAI},    // 43
            {0x6B, (ABILITY_HANDLER_FUNC)HandlerToxicBoostStatus}, // 44
            {0x3B, (ABILITY_HANDLER_FUNC)HandlerToxicBoostDamage}
            // {0x81, (ABILITY_HANDLER_FUNC)HandlerPickPocketStart},
            // {0x83, (ABILITY_HANDLER_FUNC)HandlerPickPocketAction}
    };

    int *THUMB_BRANCH_EventAddFriendGuard(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&AbilityTriggerTable[0].triggerValue;
    }

    int *THUMB_BRANCH_EventAddPlus(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&AbilityTriggerTable[2].triggerValue;
    }

    int *THUMB_BRANCH_EventAddHealer(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&AbilityTriggerTable[4].triggerValue;
    }

    int *THUMB_BRANCH_EventAddLightMetal(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&AbilityTriggerTable[6].triggerValue;
    }

    int *THUMB_BRANCH_EventAddHeavyMetal(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&AbilityTriggerTable[7].triggerValue;
    }

    int *THUMB_BRANCH_EventAddThickFat(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&AbilityTriggerTable[9].triggerValue;
    }

    int *THUMB_BRANCH_EventAddGuts(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&AbilityTriggerTable[11].triggerValue;
    }

    int *THUMB_BRANCH_EventAddQuickFeet(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&AbilityTriggerTable[13].triggerValue;
    }

    int *THUMB_BRANCH_EventAddFlareBoost(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&AbilityTriggerTable[15].triggerValue;
    }

    int *THUMB_BRANCH_EventAddPoisonHeal(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&AbilityTriggerTable[17].triggerValue;
    }

    int *THUMB_BRANCH_EventAddToxicBoost(unsigned int *a1)
    {
        *a1 = 4;
        return (int *)&AbilityTriggerTable[42].triggerValue;
    }

    int *THUMB_BRANCH_EventAddImmunity(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&AbilityTriggerTable[22].triggerValue;
    }

    int *THUMB_BRANCH_EventAddOvercoat(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&AbilityTriggerTable[24].triggerValue;
    }

    int *THUMB_BRANCH_EventAddLimber(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&AbilityTriggerTable[26].triggerValue;
    }

    int *THUMB_BRANCH_EventAddMarvelScale(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&AbilityTriggerTable[27].triggerValue;
    }

    int *THUMB_BRANCH_EventAddRainDish(unsigned int *a1)
    {
        *a1 = 6;
        return (int *)&AbilityTriggerTable[29].triggerValue;
    }

    int *THUMB_BRANCH_EventAddClearBody(unsigned int *a1)
    {
        *a1 = 3;
        return (int *)&AbilityTriggerTable[35].triggerValue;
    }

    int *THUMB_BRANCH_EventAddDrySkin(unsigned int *a1)
    {
        *a1 = 3;
        return (int *)&AbilityTriggerTable[38].triggerValue;
    }

    int *THUMB_BRANCH_EventAddPickup(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&AbilityTriggerTable[41].triggerValue;
    }

    

}