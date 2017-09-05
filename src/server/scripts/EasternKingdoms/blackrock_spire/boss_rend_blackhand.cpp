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
SDName: Boss_Rend_Blackhand
SD%Complete: 100
SDComment: Intro event NYI
SDCategory: Blackrock Spire
EndScriptData */


#include "GameEventMgr.h"

#define SPELL_WHIRLWIND                 26038
#define SPELL_CLEAVE                    20691
#define SPELL_THUNDERCLAP               23931               //Not sure if he cast this spell


class boss_rend_blackhand : public CreatureScript
{
public:
    boss_rend_blackhand() : CreatureScript("boss_rend_blackhand")
    { }

    class boss_rend_blackhandAI : public ScriptedAI
    {
        public:
        boss_rend_blackhandAI(Creature *c) : ScriptedAI(c) {}
    
        uint32 WhirlWind_Timer;
        uint32 cleaveTimer;
        uint32 Thunderclap_Timer;
    
        bool isEventActive()
        {
            const GameEventMgr::ActiveEvents& activeEvents = sGameEventMgr->GetActiveEventList();
            bool active = activeEvents.find(57) != activeEvents.end();
    
            return active;
        }
    
        void Reset()
        override {
            WhirlWind_Timer = 20000;
            cleaveTimer = 5000;
            Thunderclap_Timer = 9000;
            
            if (isEventActive())
                me->SetDisplayId(15736);
        }
    
        void EnterCombat(Unit *who)
        override {
        }
    
        void UpdateAI(const uint32 diff)
        override {
            //Return since we have no target
            if (!UpdateVictim() )
                return;
    
            //WhirlWind_Timer
            if (WhirlWind_Timer < diff)
            {
                DoCast(me->GetVictim(), SPELL_WHIRLWIND);
                WhirlWind_Timer = 18000;
            }else WhirlWind_Timer -= diff;
    
            //cleave Timer
            if (cleaveTimer < diff)
            {
                DoCast(me->GetVictim(), SPELL_CLEAVE);
                cleaveTimer = 10000;
            }else cleaveTimer -= diff;
    
            //Thunderclap_Timer
            if (Thunderclap_Timer < diff)
            {
                DoCast(me->GetVictim(), SPELL_THUNDERCLAP);
                Thunderclap_Timer = 16000;
            }else Thunderclap_Timer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_rend_blackhandAI(creature);
    }
};


void AddSC_boss_rend_blackhand()
{
    new boss_rend_blackhand();
}

