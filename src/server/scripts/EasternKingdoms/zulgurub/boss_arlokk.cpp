/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/* ScriptData
SDName: Boss_Arlokk
SD%Complete: 95
SDComment: Wrong cleave and red aura is missing.
SDCategory: Zul'Gurub
EndScriptData */


#include "def_zulgurub.h"

#define SAY_AGGRO                   -1309011
#define SAY_FEAST_PANTHER           -1309012
#define SAY_DEATH                   -1309013

#define SPELL_SHADOWWORDPAIN       23952
#define SPELL_GOUGE                24698
#define SPELL_MARK                 24210
#define SPELL_CLEAVE               26350                    //Perhaps not right. Not a red aura...
#define SPELL_PANTHER_TRANSFORM    24190

class boss_arlokk : public CreatureScript
{
public:
    boss_arlokk() : CreatureScript("boss_arlokk")
    { }

    class boss_arlokkAI : public ScriptedAI
    {
        public:
        boss_arlokkAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
    
        InstanceScript *pInstance;
    
        uint32 ShadowWordPain_Timer;
        uint32 Gouge_Timer;
        uint32 Mark_Timer;
        uint32 Cleave_Timer;
        uint32 Vanish_Timer;
        uint32 Summon_Timer;
        uint32 Visible_Timer;
    
        Unit* markedTarget;
        Creature *Panther;
        uint32 Counter;
    
        bool PhaseTwo;
        bool VanishedOnce;
    
        void Reset()
        override {
            ShadowWordPain_Timer = 8000;
            Gouge_Timer = 14000;
            Mark_Timer = 35000;
            Cleave_Timer = 4000;
            Vanish_Timer = 60000;
            Summon_Timer = 5000;
            Visible_Timer = 6000;
    
            Counter = 0;
    
            markedTarget = nullptr;
            PhaseTwo = false;
            VanishedOnce = false;
    
            me->SetUInt32Value(UNIT_FIELD_DISPLAYID,15218);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }
    
        void EnterCombat(Unit *who) override
        {
            DoScriptText(SAY_AGGRO, me);
        }
    
        void JustDied(Unit* Killer) override
        {
            DoScriptText(SAY_DEATH, me);
            me->SetUInt32Value(UNIT_FIELD_DISPLAYID,15218);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    
            if(pInstance)
                pInstance->SetData(DATA_ARLOKK_DEATH, 0);
        }
    
        void UpdateAI(const uint32 diff) override
        {
            if (!UpdateVictim())
                return;
    
            if( me->GetVictim() && me->IsAlive())
            {
                if (!PhaseTwo && ShadowWordPain_Timer < diff)
                {
                    DoCast(me->GetVictim(),SPELL_SHADOWWORDPAIN);
                    ShadowWordPain_Timer = 15000;
                }else ShadowWordPain_Timer -= diff;
    
                if (!PhaseTwo && Mark_Timer < diff)
                {
                    markedTarget = SelectTarget(SELECT_TARGET_RANDOM,0);
    
                    DoCast(markedTarget,SPELL_MARK);
                    Mark_Timer = 15000;
                }else Mark_Timer -= diff;
    
                if (Summon_Timer < diff && Counter < 31)
                {
                    Unit* target = nullptr;
                    target = SelectTarget(SELECT_TARGET_RANDOM,0);
    
                    Panther = me->SummonCreature(15101,-11532.79980,-1649.6734,41.4800,0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 15000);
    
                    if(markedTarget && Panther )
                    {
                        DoScriptText(SAY_FEAST_PANTHER, me, markedTarget);
                        Panther ->AI()->AttackStart(markedTarget);
                    }else if(Panther && target) Panther ->AI()->AttackStart(target);
    
                    Panther = me->SummonCreature(15101,-11532.9970,-1606.4840,41.2979,0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 15000);
    
                    if(markedTarget && Panther )
                        Panther ->AI()->AttackStart(markedTarget);
                    else if(Panther && target)
                         Panther ->AI()->AttackStart(target);
    
                    Counter++;
                    Summon_Timer = 5000;
                }else Summon_Timer -= diff;
    
                if (Vanish_Timer < diff)
                {
                    //Invisble Model
                    me->SetUInt32Value(UNIT_FIELD_DISPLAYID,11686);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    //me->CombatStop();
                    DoResetThreat();
                    VanishedOnce = true;
                    Vanish_Timer = 45000;
                    Visible_Timer = 6000;
                }else Vanish_Timer -= diff;
    
                if (VanishedOnce)
                {
                    if(Visible_Timer < diff)
                    {
                        Unit* target = nullptr;
                        target = SelectTarget(SELECT_TARGET_RANDOM,0);
                        //The Panther Model
                        me->SetUInt32Value(UNIT_FIELD_DISPLAYID,15215);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    
                       /* FIXMEDMG  const CreatureTemplate *cinfo = me->GetCreatureTemplate();
                        me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, (cinfo->mindmg +((cinfo->mindmg/100) * 35)));
                        me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, (cinfo->maxdmg +((cinfo->maxdmg/100) * 35)));
                        me->UpdateDamagePhysical(BASE_ATTACK);
                        */
                        if(target)
                            AttackStart(target);
                        //The Panther Model
                        me->SetUInt32Value(UNIT_FIELD_DISPLAYID,15215);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        PhaseTwo = true;
                    }else Visible_Timer -= diff;
                }
    
                //Cleave_Timer
                if(PhaseTwo && Cleave_Timer < diff)
                {
                    DoCast(me->GetVictim(), SPELL_CLEAVE);
                    Cleave_Timer = 16000;
                }Cleave_Timer -=diff;
    
                //Gouge_Timer
                if(PhaseTwo && Gouge_Timer < diff)
                {
                    DoCast(me->GetVictim(), SPELL_GOUGE);
                    if(me->GetThreat(me->GetVictim()))
                        DoModifyThreatPercent(me->GetVictim(),-80);
    
                    Gouge_Timer = 17000+rand()%10000;
                }else Gouge_Timer -= diff;
    
                DoMeleeAttackIfReady();
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_arlokkAI(creature);
    }
};


void AddSC_boss_arlokk()
{
    new boss_arlokk();
}

