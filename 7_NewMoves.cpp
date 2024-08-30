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

    void THUMB_BRANCH_HandlerSkullBash(int a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_Message *v5;         // r6
        HandlerParam_ChangeStatStage *v6; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
            BattleHandler_StrSetup(&v5->str, 2u, 556);
            BattleHandler_AddArg(&v5->str, (int)a3);
            BattleHandler_PopWork(a2, v5);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (int)a3;
            v6->rankType = STATSTAGE_DEFENSE;
            v6->rankVolume = 1;
            v6->fMoveAnimation = 1;
            BattleHandler_PopWork(a2, v6);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (int)a3;
            v6->rankType = STATSTAGE_ATTACK;
            v6->rankVolume = 1;
            BattleHandler_PopWork(a2, v6);
        }
    }

    void HandlerMeteorBeam(int a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_Message *v5;         // r6
        HandlerParam_ChangeStatStage *v6; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
            BattleHandler_StrSetup(&v5->str, 2u, 863);
            BattleHandler_AddArg(&v5->str, (int)a3);
            BattleHandler_PopWork(a2, v5);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (int)a3;
            v6->rankType = STATSTAGE_SPECIAL_ATTACK;
            v6->rankVolume = 1;
            v6->fMoveAnimation = 1;
            BattleHandler_PopWork(a2, v6);
        }
    }

    // // void HandlerSkyAttack
    void HandlerSkyAttack(int a1, ServerFlow *a2, unsigned int *a3)
    {
        k::Printf("\nAre we inside?\n");
        HandlerParam_Message *v5;         // r6
        HandlerParam_ChangeStatStage *v6; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
            BattleHandler_StrSetup(&v5->str, 2u, 550);
            BattleHandler_AddArg(&v5->str, (int)a3);
            BattleHandler_PopWork(a2, v5);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (int)a3;
            v6->rankType = STATSTAGE_ATTACK;
            v6->rankVolume = 1;
            v6->fMoveAnimation = 1;
            BattleHandler_PopWork(a2, v6);
        }
    }

    int HandlerElectroShotRain(int a1, int a2, int a3)
    {
        int result; // r0

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            result = Handler_GetWeather(a2);
            if (result == 2)
            {
                return BattleEventVar_RewriteValue(VAR_GENERAL_USE_FLAG, 1);
            }
        }
        return result;
    }

    // // void HandlerElectroShot
    void HandlerElectroShotCharge(int a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_Message *v5;         // r6
        HandlerParam_ChangeStatStage *v6; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
            BattleHandler_StrSetup(&v5->str, 2u, 866);
            BattleHandler_AddArg(&v5->str, (int)a3);
            BattleHandler_PopWork(a2, v5);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (int)a3;
            v6->rankType = STATSTAGE_SPECIAL_ATTACK;
            v6->rankVolume = 1;
            v6->fMoveAnimation = 1;
            BattleHandler_PopWork(a2, v6);
        }
    }

    // // void HandlerIngrain

    int NewHandlerSkyUppercut(int a1, ServerFlow *a2, int a3)
    {
        int result; // r0
        // int PokeType;
        // int v6;               // r6
        // BattleMon *PokeParam; // r7
        // int resultdata;

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            // v6 = (unsigned __int8)BattleEventVar_GetValue(VAR_DEFENDING_MON);
            // PokeParam = Handler_GetPokeParam(a2, v6);
            // PokeType = BattleMon_GetPokeType(PokeParam);
            // // k::Printf("\n4. Result is Type Effectiveness is %d\n", result);
            // result = GetTypeEffectivenesssVsMonAltered(TYPE_FIGHTING, PokeType);
            // k::Printf("\nFinal Type Effectiveness is %d\n\n", result);
            // BattleEventVar_RewriteValue(VAR_SET_TYPE_EFFECTIVENESS, result);
            // result = BattleEventVar_RewriteValue(VAR_TYPEEFFECTIVENESS, result);
            // k::Printf("\nReturn value is %d\n\n", result);
            return BattleEventVar_RewriteValue(VAR_SET_TYPE_EFFECTIVENESS, 3);
        }
        return result;
    }

    int HandlerFreezeDry(int a1, ServerFlow *a2, int a3)
    {
        int result; // r0
        int PokeType;
        int v6;               // r6
        BattleMon *PokeParam; // r7

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            // v6 = (unsigned __int8)BattleEventVar_GetValue(VAR_DEFENDING_MON);
            // PokeParam = Handler_GetPokeParam(a2, v6);
            // PokeType = BattleMon_GetPokeType(PokeParam);
            // result = GetTypeEffectivenesssVsMonAltered(TYPE_ICE, PokeType);
            return BattleEventVar_RewriteValue(VAR_SET_TYPE_EFFECTIVENESS, 2);
        }
        return result;
    }

    int HandlerSwallowCheckFail(int a1, ServerFlow *a2, int a3)
    {
        int result;           // r0
        BattleMon *PokeParam; // r0
        int HeldItem;         // r0

        result = BattleEventVar_GetValue(VAR_MON_ID);
        if (a3 == result)
        {
            PokeParam = Handler_GetBattleMon(a2, a3);
            HeldItem = BattleMon_GetHeldItem(PokeParam);
            if (!HeldItem)
            {
                return BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, 26);
            }
            if (!PML_ItemIsBerry(HeldItem))
            {
                return BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, 26);
            }
            if (!Handler_CheckItemUsable(a2, a3))
            {
                return BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, 26);
            }
        }
        return result;
    }

    int HandlerSwallowHeal(int a1, ServerFlow *a2, int a3)
    {
        int result;           // r0
        BattleMon *PokeParam; // r0
        int Count;            // r0
        int v8;               // r1

        result = BattleEventVar_GetValue(VAR_MON_ID);
        if (a3 == result)
        {
            PokeParam = Handler_GetBattleMon(a2, a3);

            if (PML_ItemIsBerry(PokeParam->HeldItem))
            {
                return BattleEventVar_RewriteValue(VAR_RATIO, 3072);
            }
            // return BattleEventVar_RewriteValue(VAR_RATIO, 1024);
        }
        return result;
    }

    int THUMB_BRANCH_HandlerElectroBall(int a1, ServerFlow *a2, int a3)
    {
        int result;            // r0
        BattleMon *PokeParam;  // r5
        unsigned __int8 Value; // r0
        BattleMon *v8;         // r6
        int v9;                // r5
        int v10;               // r0
        int v11;               // r1

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            PokeParam = Handler_GetBattleMon(a2, a3);
            Value = BattleEventVar_GetValue(VAR_DEFENDING_MON);
            v8 = Handler_GetBattleMon(a2, Value);
            v9 = Handler_CalculateSpeed(a2, PokeParam, 0);
            v10 = Handler_CalculateSpeed(a2, v8, 0);
            if (v9 > v10)
            {
                v11 = 120;
            }
            else
            {
                v11 = 60;
            }
            return BattleEventVar_RewriteValue(VAR_MOVE_POWER, v11);
        }
        return result;
    }

    int THUMB_BRANCH_HandlerGyroBall(int a1, ServerFlow *a2, int a3)
    {
        int result;            // r0
        BattleMon *PokeParam;  // r5
        unsigned __int8 Value; // r0
        BattleMon *v8;         // r6
        int v9;                // r5
        int v10;               // r0
        int v11;               // r1

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            PokeParam = Handler_GetBattleMon(a2, a3);
            Value = BattleEventVar_GetValue(VAR_DEFENDING_MON);
            v8 = Handler_GetBattleMon(a2, Value);
            v9 = Handler_CalculateSpeed(a2, PokeParam, 0);
            v10 = Handler_CalculateSpeed(a2, v8, 0);
            if (v9 < v10)
            {
                v11 = 120;
            }
            else
            {
                v11 = 60;
            }
            return BattleEventVar_RewriteValue(VAR_MOVE_POWER, v11);
        }
        return result;
    }

    int THUMB_BRANCH_HandlerSleepTalk(int r0_0, ServerFlow *r1_0, int a3, int *a4)
    {
        int result;             // r0
        unsigned int v6;        // r5
        unsigned int i;         // r6
        int ID;                 // r4
        unsigned int v9;        // r1
        int v10;                // r5
        int v11;                // r4
        unsigned int MoveCount; // [sp+8h] [bp-20h]
        BattleMon *PokeParam;   // [sp+Ch] [bp-1Ch]

        result = BattleEventVar_GetValue(VAR_MON_ID);
        if (a3 == result)
        {
            PokeParam = Handler_GetBattleMon(r1_0, a3);
            // result = BattleMon_CheckIfMoveCondition(PokeParam, CONDITION_SLEEP);
            // if (result)
            // {
            MoveCount = BattleMon_GetMoveCount(PokeParam);
            v6 = 0;
            for (i = 0; v6 < MoveCount; v6 = (v6 + 1))
            {
                ID = Move_GetID(PokeParam, v6);
                if (!j_j_IsSleepTalkUncallableMove(ID) && ID != 156 && !getMoveFlag(ID, FLAG_REQUIRES_CHARGE))
                {
                    v9 = i;
                    i = (i + 1);
                    a4[v9] = ID;
                }
            }
            if (i)
            {
                v10 = *(a4 + ((4 * BattleRandom(i)) & 0x3FF));
                v11 = Handler_ReqMoveTargetAuto(r1_0, a3, v10);
                BattleEventVar_RewriteValue(VAR_MOVE_ID, v10);
                return BattleEventVar_RewriteValue(VAR_POKE_POS, v11);
            }
            else
            {
                return BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
            }
            //}
        }
        return result;
    }

    void HandlerSwallowEnd(int a1, ServerFlow *a2, int a3, int *a4)
    {
        BattleMon *PokeParam;     // r0
        HandlerParam_Header *v8;  // r0
        HandlerParam_Message *v7; // r4
        HandlerParam_ActivateItem *v9;

        u16 HeldItem;

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && !*a4)
        {
            PokeParam = Handler_GetBattleMon(a2, a3);
            HeldItem = BattleMon_GetHeldItem(PokeParam);

            if (PML_ItemIsBerry(HeldItem))
            {
                v7 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, a3);
                BattleHandler_StrSetup(&v7->str, 2u, 1159);
                BattleHandler_AddArg(&v7->str, a3);
                BattleHandler_AddArg(&v7->str, HeldItem);
                BattleHandler_PopWork(a2, v7);

                v9 = (HandlerParam_ActivateItem *)BattleHandler_PushWork(a2, EFFECT_ACTIVATEITEM, a3);
                v9->header.flags |= 0x1000000u;
                v9->itemID = (int)HeldItem;
                v9->pokeID = a3;
                BattleHandler_PopWork(a2, v9);

                v8 = (HandlerParam_Header *)BattleHandler_PushWork(a2, EFFECT_CONSUMEITEM, a3);
                v8[1].flags = 1;
                BattleHandler_PopWork(a2, v8);
            }
        }
    }

    void HandlerTeleportEffect(int a1, ServerFlow *a2, int a3)
    {
        HandlerParam_Message *v5; // r5
        HandlerParam_Switch *v7;  // r0

        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON) && Handler_GetFightEnableBenchPokeNum(a2, a3))
        {
            if (Handler_CheckReservedMemberChangeAction(a2))
            {
                v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, a3);
                BattleHandler_StrSetup(&v5->str, 2u, 767);
                BattleHandler_AddArg(&v5->str, a3);
                BattleHandler_PopWork(a2, v5);
                v7 = (HandlerParam_Switch *)BattleHandler_PushWork(a2, EFFECT_SWITCH, a3);
                v7->pokeID = a3;
                v7->fIntrDisable = 1;
                BattleHandler_PopWork(a2, v7);
            }
        }
    }

    void THUMB_BRANCH_HandlerIronFist(int a1, int a2, int a3)
    {
        int result;             // r0
        unsigned __int16 Value; // r0

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            Value = BattleEventVar_GetValue(VAR_MOVE_ID);
            result = getMoveFlag(Value, FLAG_PUNCH);
            if (result)
            {
                BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 5325);
            }
        }
    }

    // void HandlerStickyWeb(int a1, ServerFlow *a2, unsigned int a3, int a4)
    // {
    //     int Permanent;      // r4           // r4
    //     bool SideFromMonID; // r0
    //     Permanent = 1;
    //     SideFromMonID = GetSideFromOpposingMonID(a3);
    //     CommonCreateSideEffect(a1, a2, a3, a4, SideFromMonID, 5, Permanent, 148);
    // }

    // void HandlerSideStickyWeb(BattleEventItem *a1, ServerFlow *serverFlow, int currentSide, int *work)
    // {
    //     HandlerParam_ChangeStatStage *v3;
    //     int currentSlot = BattleEventVar_GetValue(VAR_MON_ID);
    //     if (currentSide == GetSideFromMonID(currentSlot))
    //     {
    //         BattleMon *currentMon = Handler_GetBattleMon(serverFlow, currentSlot);
    //         v3 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(serverFlow, EFFECT_CHANGESTATSTAGE, currentSlot);
    //         v3->poke_cnt = 1;
    //         v3->pokeID[0] = currentSlot;
    //         v3->rankType = STATSTAGE_SPEED;
    //         v3->rankVolume = -1;
    //         BattleHandler_PopWork(serverFlow, v3);
    //     }
    // }

    typedef struct
    {
        int triggerValue;
        MOVE_HANDLER_FUNC function;
    } MOVE_TRIGGERTABLE;

    MOVE_TRIGGERTABLE MoveTriggerTable[] =
        {
            {0x96, (MOVE_HANDLER_FUNC)HandlerMeteorBeam},
            {0x3E, (MOVE_HANDLER_FUNC)NewHandlerSkyUppercut}, // BattleEvent_CheckTypeEffectiveness
            {0x3E, (MOVE_HANDLER_FUNC)HandlerFreezeDry},
            {0x94, (MOVE_HANDLER_FUNC)HandlerElectroShotRain},
            {0x96, (MOVE_HANDLER_FUNC)HandlerElectroShotCharge},
            {0x96, (MOVE_HANDLER_FUNC)HandlerSkyAttack},

            {0x1F, (MOVE_HANDLER_FUNC)HandlerSwallowCheckFail},
            {0x8F, (MOVE_HANDLER_FUNC)HandlerSwallowHeal},
            {0x27, (MOVE_HANDLER_FUNC)HandlerSwallowEnd},

            {0x1F, (MOVE_HANDLER_FUNC)HandlerSwallowCheckFail},
            {0x81, (MOVE_HANDLER_FUNC)HandlerSwallowEnd},
            {0x27, (MOVE_HANDLER_FUNC)HandlerSwallowEnd},
            //{0x39, (MOVE_HANDLER_FUNC)HandlerBodyPress}

            {0x96, (MOVE_HANDLER_FUNC)HandlerSkyAttack},

            {0x1F, (MOVE_HANDLER_FUNC)HandlerSwallowCheckFail},
            {0x81, (MOVE_HANDLER_FUNC)HandlerSwallowEnd},
            {0x27, (MOVE_HANDLER_FUNC)HandlerSwallowEnd},

            {0xA0, (MOVE_HANDLER_FUNC)HandlerTeleportEffect},
            //{0x78, (MOVE_HANDLER_FUNC)HandlerUturn},
            {0x86, (MOVE_HANDLER_FUNC)HandlerUturn},
            //{0x27, (MOVE_HANDLER_FUNC)HandlerUturn}
            //{0xA1, (MOVE_HANDLER_FUNC)HandlerStickyWeb},

            //{0x55, (MOVE_HANDLER_FUNC)HandlerSideStickyWeb}
    };

    // typedef struct
    // {
    //     int triggerValue;
    //     SIDE_HANDLER_FUNC function;
    // } SIDE_TRIGGERTABLE;

    // SIDE_TRIGGERTABLE SideTriggerTable[] =
    //     {
    //         {0x55, (SIDE_HANDLER_FUNC)HandlerSideStickyWeb}
    // };

    // int *THUMB_BRANCH_EventAddSideLuckyChant(int *a1)
    // {
    //     *a1 = 1;
    //     return (int *)&SideTriggerTable[0].triggerValue;
    // }

    // Meteor Beam
    int *THUMB_BRANCH_EventAddFreezeShock(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&MoveTriggerTable[0].triggerValue;
    }

    int *THUMB_BRANCH_EventAddSkyUppercut(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&MoveTriggerTable[1].triggerValue;
    }

    int *THUMB_BRANCH_EventAddMiracleEye(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&MoveTriggerTable[2].triggerValue;
    }

    int *THUMB_BRANCH_EventAddForesight(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&MoveTriggerTable[3].triggerValue;
    }

    int *THUMB_BRANCH_EventAddSwallow(unsigned int *a1)
    {
        *a1 = 3;
        return (int *)&MoveTriggerTable[6].triggerValue;
    }

    int *THUMB_BRANCH_EventAddSpitUp(unsigned int *a1)
    {
        *a1 = 3;
        return (int *)&MoveTriggerTable[13].triggerValue;
    }

    int *THUMB_BRANCH_EventAddSkyAttack(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&MoveTriggerTable[12].triggerValue;
    }

    int *THUMB_BRANCH_EventAddStockpile(unsigned int *a1)
    {
        *a1 = 3;
        return (int *)&MoveTriggerTable[13].triggerValue;
    }

    int *THUMB_BRANCH_EventAddTeleport(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&MoveTriggerTable[16].triggerValue;
    }

    int *THUMB_BRANCH_EventAddLockOn(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&MoveTriggerTable[17].triggerValue;
    }

    int THUMB_BRANCH_SAFESTACK_ServerControl_MoveExecuteCheck1(ServerFlow *a1, BattleMon *a2, int a3, int a4)
    {
        MoveFailCause v7;                          // r6
        ActionIgnoreReason actionIgnoreReason;                          // r0
        int v9;                          // r1
        ConditionData MoveConditionData; // r0
        int PreviousMove;                // r0
        int ID;                          // r0
        int v15;                         // [sp+Ch] [bp-24h]
        MoveCondition Status;            // [sp+10h] [bp-20h]

        v15 = 0;
        ServerControl_CheckMoveExeSleepCure(a1, a2);
        Status = BattleMon_GetStatus(a2);
        if (Status != CONDITION_SLEEP || (v7 = MOVEFAIL_SLEEP, ServerEvent_MoveExecuteFail(a1, a2, a3, 2)))
        {
            v15 = ServerControl_CheckMoveExeFreezeThaw(a1, a2, a3);
            Status = BattleMon_GetStatus(a2);
            if (Status == CONDITION_FREEZE && !v15)
            {
                v7 = MOVEFAIL_FREEZE;
                goto LABEL_50;
            }
            actionIgnoreReason = a1->actionIgnoreReason;
            if (actionIgnoreReason == REASON_OVERLEVELED)
            {
                v7 = MOVEFAIL_IGNORE;
                goto LABEL_50;
            }
            if (actionIgnoreReason == REASON_FALL_ASLEEP)
            {
                v7 = MOVEFAIL_IGNORE_FALL_ASLEEP;
                goto LABEL_50;
            }
            if (!a4)
            {
                v9 = Move_SearchIndex(a2, a3);
                if (v9 != 4 && !Move_GetPP(a2, v9))
                {
                    v7 = MOVEFAIL_PPZERO;
                    goto LABEL_50;
                }
            }
            v7 = (MoveFailCause)ServerEvent_CheckMoveExecute(a1, a2, a3, BattleEvent_MoveExecuteCheck1);
            if (v7 == MOVEFAIL_NULL)
            {
                if (BattleMon_GetTurnFlag(a2, TURNFLAG_FOCUSPUNCHFAIL))
                {
                    v7 = MOVEFAIL_FOCUSPUNCHFAIL;
                    goto LABEL_50;
                }
                if (BattleMon_GetTurnFlag(a2, TURNFLAG_FLINCH))
                {
                    v7 = MOVEFAIL_FLINCH;
                    goto LABEL_50;
                }
                if (PersonalCheckIfMoveCondition(a2, CONDITION_DISABLEMOVE) && a3 != 165)
                {
                    MoveConditionData = BattleMon_GetMoveCondition(a2, CONDITION_DISABLEMOVE);
                    if (a3 == Condition_GetParam(MoveConditionData))
                    {
                        v7 = MOVEFAIL_DISABLE;
                        goto LABEL_50;
                    }
                }
                if (PersonalCheckIfMoveCondition(a2, CONDITION_HEALBLOCK) && getMoveFlag(a3, FLAG_HEALING))
                {
                    v7 = MOVEFAIL_HEALBLOCK;
                    goto LABEL_50;
                }
                if (BattleField_CheckEffect(EFFECT_GRAVITY) && getMoveFlag(a3, FLAG_GROUNDED_BY_GRAVITY))
                {
                    v7 = MOVEFAIL_GRAVITY;
                    goto LABEL_50;
                }
                if (a3 == 165)
                {
                    goto LABEL_60;
                }
                if (PersonalCheckIfMoveCondition(a2, CONDITION_ENCORE) && (PreviousMove = BattleMon_GetPreviousMove(a2), PreviousMove != 165) && PreviousMove != a3 || PersonalCheckIfMoveCondition(a2, CONDITION_MOVELOCK) && a3 != BattleMon_GetPreviousMoveID(a2))
                {
                    v7 = MOVEFAIL_MOVELOCK;
                    goto LABEL_50;
                }
                if (PersonalCheckIfMoveCondition(a2, CONDITION_TAUNT) && !PML_MoveIsDamaging(a3))
                {
                    v7 = MOVEFAIL_TAUNT;
                    goto LABEL_50;
                }
                if (BattleField_CheckEffect(EFFECT_IMPRISON) && BattleField_CheckImprison(a1->pokeCon, a2, a3))
                {
                    v7 = MOVEFAIL_IMPRISON;
                }
                else
                {
                LABEL_60:
                    if (ServerControl_CheckConfusionHit(a1, a2))
                    {
                        v7 = MOVEFAIL_CONFUSION;
                    }
                    else if (Status == CONDITION_PARALYSIS && a2->Ability != 63 && RollEffectChance(0x19u))
                    {
                        v7 = MOVEFAIL_PARALYSIS;
                    }
                    else if (ServerControl_CheckAttract(a1, a2))
                    {
                        v7 = MOVEFAIL_ATTRACT;
                    }
                }
            }
        }
    LABEL_50:
        if (v7)
        {
            ServerControl_MoveExecuteFail(a1, a2, a3, v7);
            return 1;
        }
        else
        {
            if (Status == CONDITION_SLEEP)
            {
                ServerDisplay_MoveExecuteFailMessage(a1, (int)a2, a3, 2u);
                ServerDisplay_AddEffectAtPosition(a1, a2, 598);
            }
            else if (v15)
            {
                if (Status == CONDITION_FREEZE)
                {
                    ServerDisplay_CureStatus(a1, a2, 3, 0);
                    ID = BattleMon_GetID(a2);
                    ServerDisplay_AddMessageImpl(a1->serverCommandQueue, 91, 303, ID, a3, -65536);
                }
            }
            return 0;
        }
    }

    // void EndOfCharge()
    // {
    // }

    // int checkState(BattleMon *PokeParam)
    // {
    //     if (BattleMon_GetConditionFlag(PokeParam, CONDITIONFLAG_SHADOWFORCE))
    //     {
    //         return 1;
    //     }
    //     if (BattleMon_GetConditionFlag(PokeParam, CONDITIONFLAG_FLY))
    //     {
    //         return 2;
    //     }
    //     if (BattleMon_GetConditionFlag(PokeParam, CONDITIONFLAG_DIG))
    //     {
    //         return 3;
    //     }
    //     if (BattleMon_GetConditionFlag(PokeParam, CONDITIONFLAG_DIVE))
    //     {
    //         return 4;
    //     }
    //     else
    //     {
    //         return 0;
    //     }
    // }

    // int checkScript(int a1)
    // {
    //     if (a1 == 1)
    //     {
    //         return 1168;
    //     }
    //     if (a1 == 2)
    //     {
    //         return 1171;
    //     }
    //     if (a1 == 3)
    //     {
    //         return 1165;
    //     }
    //     if (a1 == 4)
    //     {
    //         return 1177;
    //     }
    //     else
    //     {
    //         return 0;
    //     }
    // }

    // int HandlerPursuitStartCharge(int a1, ServerFlow *a2, unsigned int a3, int a4)
    // {
    //     int result;         // r0
    //     unsigned int Value; // r6
    //     int v8[6];          // [sp+0h] [bp-18h] BYREF
    //     int moveID;
    //     int state;
    //     BattleMon *PokeParam;
    //     HandlerParam_Message *v5; // r6

    //     PokeParam = Handler_GetPokeParam(a2, a3);
    //     k::Printf("\nLayer One: We are inside the function did we get this far?\n");
    //     if (checkState(PokeParam))
    //     {
    //         v8[1] = a4;
    //         result = Handler_GetThisTurnAction(a2, a3, v8);
    //         k::Printf("\nLayer Two: We are inside the function did we get this far?\n");
    //         if (result)
    //         {
    //             Value = BattleEventVar_GetValue(VAR_TARGETMONID);
    //             result = MainModule_IsAllyMonID(Value, a3);
    //             if (!result)
    //             {
    //                 k::Printf("\nLayer Three: We are inside the function did we get this far?\n");
    //                 Handler_PokeIDToPokePos(a2, Value);
    //                 Handler_PokeIDToPokePos(a2, a3);
    //                 result = Handler_IsTargetInRange(a2, a3, Value, 0);
    //                 if (!result)
    //                 {
    //                     k::Printf("\nWe are inside the function did we get this far?\n");
    //                     v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
    //                     BattleHandler_StrSetup(&v5->str, 2u, checkScript(checkState(PokeParam)));
    //                     BattleHandler_AddArg(&v5->str, (int)a3);
    //                     BattleHandler_PopWork(a2, v5);

    //                     return Handler_AddSwitchOutInterrupt((int)&a2, a3);
    //                 }
    //             }
    //         }
    //     }
    //     return result;
    // }

    // void SwitchOutInterruptDig(int a1, ServerFlow *a2, unsigned int a3, int a4)
    // {
    //     HandlerParam_Message *v5; // r6

    //     if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    //     {
    //         v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
    //         BattleHandler_StrSetup(&v5->str, 2u, 1165);
    //         BattleHandler_AddArg(&v5->str, (int)a3);
    //         BattleHandler_PopWork(a2, v5);
    //     }
    // }

    // void SwitchOutInterruptShadowForce(int a1, ServerFlow *a2, unsigned int a3, int a4)
    // {
    //     HandlerParam_Message *v5; // r6

    //     if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    //     {
    //         v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
    //         BattleHandler_StrSetup(&v5->str, 2u, 1168);
    //         BattleHandler_AddArg(&v5->str, (int)a3);
    //         BattleHandler_PopWork(a2, v5);
    //     }
    // }

    // void SwitchOutInterruptFly(int a1, ServerFlow *a2, unsigned int a3, int a4)
    // {
    //     HandlerParam_Message *v5; // r6

    //     if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    //     {
    //         v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
    //         BattleHandler_StrSetup(&v5->str, 2u, 1171);
    //         BattleHandler_AddArg(&v5->str, (int)a3);
    //         BattleHandler_PopWork(a2, v5);
    //     }
    // }

    // void SwitchOutInterruptBounce(int a1, ServerFlow *a2, unsigned int a3, int a4)
    // {
    //     HandlerParam_Message *v5; // r6

    //     if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    //     {
    //         v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
    //         BattleHandler_StrSetup(&v5->str, 2u, 1174);
    //         BattleHandler_AddArg(&v5->str, (int)a3);
    //         BattleHandler_PopWork(a2, v5);
    //     }
    // }

    // void SwitchOutInterruptDive(int a1, ServerFlow *a2, unsigned int a3, int a4)
    // {
    //     HandlerParam_Message *v5; // r6

    //     if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    //     {
    //         v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
    //         BattleHandler_StrSetup(&v5->str, 2u, 1177);
    //         BattleHandler_AddArg(&v5->str, (int)a3);
    //         BattleHandler_PopWork(a2, v5);
    //     }
    // }

    // MOVE_TRIGGERTABLE MoveTriggerTable2[] =
    //     {
    //         {0x53, (MOVE_HANDLER_FUNC)HandlerPursuitStartCharge},
    //         {0x95, (MOVE_HANDLER_FUNC)HandlerDig},
    //         {0x98, (MOVE_HANDLER_FUNC)EndOfCharge},

    //         {0x53, (MOVE_HANDLER_FUNC)HandlerPursuitStartCharge},
    //         {0x95, (MOVE_HANDLER_FUNC)HandlerShadowForce},
    //         {0x98, (MOVE_HANDLER_FUNC)EndOfCharge},
    //         {0x2E, (MOVE_HANDLER_FUNC)HandlerFeintBreakProtect},
    //         {0x81, (MOVE_HANDLER_FUNC)HandlerFeintResetProtectCounter},
    //         {0x84, (MOVE_HANDLER_FUNC)HandlerShadowForceEnd},

    //         {0x53, (MOVE_HANDLER_FUNC)HandlerPursuitStartCharge},
    //         {0x95, (MOVE_HANDLER_FUNC)HandlerFly},
    //         {0x98, (MOVE_HANDLER_FUNC)EndOfCharge},

    //         {0x53, (MOVE_HANDLER_FUNC)HandlerPursuitStartCharge},
    //         {0x95, (MOVE_HANDLER_FUNC)HandlerBounce},
    //         {0x98, (MOVE_HANDLER_FUNC)EndOfCharge},

    //         {0x53, (MOVE_HANDLER_FUNC)HandlerPursuitStartCharge},
    //         {0x95, (MOVE_HANDLER_FUNC)HandlerDive},
    //         {0x98, (MOVE_HANDLER_FUNC)EndOfCharge},

    // };

    // int *THUMB_BRANCH_EventAddDig(unsigned int *a1)
    // {
    //     *a1 = 3;
    //     return (int *)&MoveTriggerTable2[0].triggerValue;
    // }

    // int *THUMB_BRANCH_EventAddShadowForce(unsigned int *a1)
    // {
    //     *a1 = 6;
    //     return (int *)&MoveTriggerTable2[3].triggerValue;
    // }

    // int *THUMB_BRANCH_EventAddFly(unsigned int *a1)
    // {
    //     *a1 = 3;
    //     return (int *)&MoveTriggerTable2[9].triggerValue;
    // }

    // int *THUMB_BRANCH_EventAddBounce(unsigned int *a1)
    // {
    //     *a1 = 3;
    //     return (int *)&MoveTriggerTable2[12].triggerValue;
    // }

    // int *THUMB_BRANCH_EventAddDive(unsigned int *a1)
    // {
    //     *a1 = 3;
    //     return (int *)&MoveTriggerTable2[15].triggerValue;
    // }
}