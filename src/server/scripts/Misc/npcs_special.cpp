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
SDName: Npcs_Special
SD%Complete: 100
SDComment: To be used for special NPCs that are located globally. Support for quest 3861 (Cluck!), 6622 and 6624 (Triage)
SDCategory: NPCs
EndScriptData
*/

/* ContentData
npc_chicken_cluck       100%    support for quest 3861 (Cluck!)
npc_dancing_flames      100%    midsummer event NPC
npc_guardian            100%    guardianAI used to prevent players from accessing off-limits areas. Not in use by SD2
npc_injured_patient     100%    patients for triage-quests (6622 and 6624)
npc_doctor              100%    Gustaf Vanhowzen and Gregory Victor, quest 6622 and 6624 (Triage)
npc_mount_vendor        100%    Regular mount vendors all over the world. Display gossip if player doesn't meet the requirements to buy
npc_rogue_trainer       80%     Scripted trainers, so they are able to offer item 17126 for class quest 6681
npc_sayge               100%    Darkmoon event fortune teller, buff player based on answers given
npc_snake_trap_serpents 80%     AI for snakes that summoned by Snake Trap
npc_goblin_land_mine    100%    Engineering item. Should explode when an hostile creature comes in range, more than 10 seconds after it's been spawned
npc_mojo                100%    Vanity pet that morph you in frog if you /kiss it
npc_explosive_sheep
npc_pet_bomb
npc_metzen
npc_clockwork_rocket_bot
npc_halaa_bomb_target
trigger_omen
lunar_large_spotlight
npc_rocket_chicken
npc_midsummer_bonfire
npc_egbert
npc_babypanda
npc_willy
EndContentData */


#include "PetAI.h"
#include "Pet.h"

/*########
# npc_chicken_cluck
#########*/

#define QUEST_CLUCK         3861
#define EMOTE_A_HELLO       "looks up at you quizzically. Maybe you should inspect it?"
#define EMOTE_H_HELLO       "looks at you unexpectadly."
#define CLUCK_TEXT2         "starts pecking at the feed."
#define FACTION_FRIENDLY    84
#define FACTION_CHICKEN     31


class npc_chicken_cluck : public CreatureScript
{
public:
    npc_chicken_cluck() : CreatureScript("npc_chicken_cluck")
    { }

    class npc_chicken_cluckAI : public ScriptedAI
    {
        public:
        npc_chicken_cluckAI(Creature *c) : ScriptedAI(c) {}
    
        uint32 ResetFlagTimer;
    
        void Reset()
        override {
            ResetFlagTimer = 120000;
    
            me->SetFaction(FACTION_CHICKEN);
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
        }
    
        void EnterCombat(Unit *who) override {}
    
        void UpdateAI(const uint32 diff)
        override {
            // Reset flags after a certain time has passed so that the next player has to start the 'event' again
            if(me->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER))
            {
                if(ResetFlagTimer < diff)
                {
                    EnterEvadeMode();
                    return;
                }else ResetFlagTimer -= diff;
            }
    
            if(UpdateVictim())
                DoMeleeAttackIfReady();
        }

        virtual void ReceiveEmote(Player* player, uint32 emote) override
        {
            if( emote == TEXTEMOTE_CHICKEN )
            {
                if( player->GetTeam() == ALLIANCE )
                {
                    if( rand()%30 == 1 )
                    {
                        if( player->GetQuestStatus(QUEST_CLUCK) == QUEST_STATUS_NONE )
                        {
                            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                            me->SetFaction(FACTION_FRIENDLY);
                            me->TextEmote(EMOTE_A_HELLO);
                        }
                    }
                } else
                me->TextEmote(EMOTE_H_HELLO);
            }
            if( emote == TEXTEMOTE_CHEER && player->GetTeam() == ALLIANCE )
                if( player->GetQuestStatus(QUEST_CLUCK) == QUEST_STATUS_COMPLETE )
            {
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                me->SetFaction(FACTION_FRIENDLY);
                me->TextEmote(CLUCK_TEXT2);
            }
        }


        virtual void QuestAccept(Player* player, Quest const* _Quest) override
        {
            if(_Quest->GetQuestId() == QUEST_CLUCK)
                Reset();
        }


        virtual void QuestReward(Player* player, Quest const* _Quest, uint32 opt) override
        {
            if(_Quest->GetQuestId() == QUEST_CLUCK)
                Reset();
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_chicken_cluckAI(creature);
    }
};





/*######
## npc_dancing_flames
######*/

#define SPELL_BRAZIER       45423
#define SPELL_SEDUCTION     47057
#define SPELL_FIERY_AURA    45427


class npc_dancing_flames : public CreatureScript
{
public:
    npc_dancing_flames() : CreatureScript("npc_dancing_flames")
    { }

    class npc_dancing_flamesAI : public ScriptedAI
    {
        public:
        npc_dancing_flamesAI(Creature *c) : ScriptedAI(c) {}
    
        bool active;
        uint32 can_iteract;
    
        void Reset()
        override {
            active = true;
            can_iteract = 3500;
            DoCast(me,SPELL_BRAZIER,true);
            DoCast(me,SPELL_FIERY_AURA,false);
            float x, y, z;
            me->GetPosition(x,y,z);
            me->Relocate(x,y,z + 0.94f);
            me->SetDisableGravity(true);
            me->HandleEmoteCommand(EMOTE_ONESHOT_DANCE);
            WorldPacket data;                       //send update position to client
            me->BuildHeartBeatMsg(&data);
            me->SendMessageToSet(&data,true);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (!active)
            {
                if(can_iteract <= diff){
                    active = true;
                    can_iteract = 3500;
                    me->HandleEmoteCommand(EMOTE_ONESHOT_DANCE);
                }else can_iteract -= diff;
            }
        }
    
        void EnterCombat(Unit* who)override {}

        virtual void ReceiveEmote(Player* player, uint32 emote) override
        {
            if ( ((npc_dancing_flames::npc_dancing_flamesAI*)me->AI())->active &&
                me->IsWithinLOS(player->GetPositionX(),player->GetPositionY(),player->GetPositionZ()) && me->IsWithinDistInMap(player,30.0f))
            {
                me->SetInFront(player);
                ((npc_dancing_flames::npc_dancing_flamesAI*)me->AI())->active = false;

                WorldPacket data;
                me->BuildHeartBeatMsg(&data);
                me->SendMessageToSet(&data,true);
                switch(emote)
                {
                    case TEXTEMOTE_KISS:    me->HandleEmoteCommand(EMOTE_ONESHOT_SHY); break;
                    case TEXTEMOTE_WAVE:    me->HandleEmoteCommand(EMOTE_ONESHOT_WAVE); break;
                    case TEXTEMOTE_BOW:     me->HandleEmoteCommand(EMOTE_ONESHOT_BOW); break;
                    case TEXTEMOTE_JOKE:    me->HandleEmoteCommand(EMOTE_ONESHOT_LAUGH); break;
                    case TEXTEMOTE_DANCE:
                    {
                        if (!player->HasAuraEffect(SPELL_SEDUCTION,0))
                            me->CastSpell(player,SPELL_SEDUCTION,true);
                    }
                    break;
                }
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_dancing_flamesAI(creature);
    }
};



/*######
## Triage quest
######*/

#define SAY_DOC1 "I'm saved! Thank you, doctor!"
#define SAY_DOC2 "HOORAY! I AM SAVED!"
#define SAY_DOC3 "Sweet, sweet embrace... take me..."

struct Location
{
    float x, y, z, o;
};

#define DOCTOR_ALLIANCE     12939

static Location AllianceCoords[]=
{
    {                                                       // Top-far-right bunk as seen from entrance
        -3757.38f, -4533.05f, 14.16f, 3.62f
    },
    {                                                       // Top-far-left bunk
        -3754.36f, -4539.13f, 14.16f, 5.13f
    },
    {                                                       // Far-right bunk
        -3749.54f, -4540.25f, 14.28f, 3.34f
    },
    {                                                       // Right bunk near entrance
        -3742.10f, -4536.85f, 14.28f, 3.64f
    },
    {                                                       // Far-left bunk
        -3755.89f, -4529.07f, 14.05f, 0.57f
    },
    {                                                       // Mid-left bunk
        -3749.51f, -4527.08f, 14.07f, 5.26f
    },
    {                                                       // Left bunk near entrance
        -3746.37f, -4525.35f, 14.16f, 5.22f
    },
};

#define ALLIANCE_COORDS     7

//alliance run to where
#define A_RUNTOX -3742.96
#define A_RUNTOY -4531.52
#define A_RUNTOZ 11.91

#define DOCTOR_HORDE    12920

static Location HordeCoords[]=
{
    {                                                       // Left, Behind
        -1013.75, -3492.59, 62.62, 4.34
    },
    {                                                       // Right, Behind
        -1017.72, -3490.92, 62.62, 4.34
    },
    {                                                       // Left, Mid
        -1015.77, -3497.15, 62.82, 4.34
    },
    {                                                       // Right, Mid
        -1019.51, -3495.49, 62.82, 4.34
    },
    {                                                       // Left, front
        -1017.25, -3500.85, 62.98, 4.34
    },
    {                                                      // Right, Front
        -1020.95, -3499.21, 62.98, 4.34
    }
};

#define HORDE_COORDS        6

//horde run to where
#define H_RUNTOX -1016.44
#define H_RUNTOY -3508.48
#define H_RUNTOZ 62.96

const uint32 AllianceSoldierId[3] =
{
    12938,                                                  // 12938 Injured Alliance Soldier
    12936,                                                  // 12936 Badly injured Alliance Soldier
    12937                                                   // 12937 Critically injured Alliance Soldier
};

const uint32 HordeSoldierId[3] =
{
    12923,                                                  //12923 Injured Soldier
    12924,                                                  //12924 Badly injured Soldier
    12925                                                   //12925 Critically injured Soldier
};

/*######
## npc_doctor (handles both Gustaf Vanhowzen and Gregory Victor)
######*/


/*#####
## npc_injured_patient (handles all the patients, no matter Horde or Alliance)
#####*/


/*
npc_doctor (continue)
*/

class npc_doctor : public CreatureScript
{
public:
    npc_doctor() : CreatureScript("npc_doctor")
    { }

    class npc_doctorAI : public ScriptedAI
    {
        public:
        uint64 Playerguid;
    
        uint32 SummonPatient_Timer;
        uint32 SummonPatientCount;
        uint32 PatientDiedCount;
        uint32 PatientSavedCount;
    
        bool Event;
    
        std::list<uint64> Patients;
        std::vector<Location*> Coordinates;
    
        npc_doctorAI(Creature *c) : ScriptedAI(c) {}
    
        void Reset()override {}
    
        void BeginEvent(Player* player);
        void PatientDied(Location* Point);
        void PatientSaved(Creature* soldier, Player* player, Location* Point);
        void UpdateAI(const uint32 diff) override;
    
        void EnterCombat(Unit* who)override {}

        virtual void QuestAccept(Player* player, Quest const* quest) override
        {
            if((quest->GetQuestId() == 6624) || (quest->GetQuestId() == 6622))
                ((npc_doctor::npc_doctorAI*)me->AI())->BeginEvent(player);
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_doctorAI(creature);
    }
};


class npc_injured_patient : public CreatureScript
{
public:
    npc_injured_patient() : CreatureScript("npc_injured_patient")
    { }

    class npc_injured_patientAI : public ScriptedAI
    {
    public:
        npc_injured_patientAI(Creature *c) : ScriptedAI(c) {}

        uint64 Doctorguid;

        Location* Coord;

        void Reset()
            override {
            Doctorguid = 0;

            Coord = nullptr;
            //no select
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            //no regen health
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IN_COMBAT);
            //to make them lay with face down
            me->SetUInt32Value(UNIT_FIELD_BYTES_1, PLAYER_STATE_DEAD);

            uint32 mobId = me->GetEntry();

            switch (mobId)
            {                                                   //lower max health
            case 12923:
            case 12938:                                     //Injured Soldier
                me->SetHealth(uint32(me->GetMaxHealth()*.75));
                break;
            case 12924:
            case 12936:                                     //Badly injured Soldier
                me->SetHealth(uint32(me->GetMaxHealth()*.50));
                break;
            case 12925:
            case 12937:                                     //Critically injured Soldier
                me->SetHealth(uint32(me->GetMaxHealth()*.25));
                break;
            }
        }

        void EnterCombat(Unit* who)override {}

        void SpellHit(Unit *caster, const SpellInfo *spell)
            override {
            if (caster->GetTypeId() == TYPEID_PLAYER && me->IsAlive() && spell->Id == 20804)
            {
                if (((caster->ToPlayer())->GetQuestStatus(6624) == QUEST_STATUS_INCOMPLETE) || ((caster->ToPlayer())->GetQuestStatus(6622) == QUEST_STATUS_INCOMPLETE))
                {
                    if (Doctorguid)
                    {
                        Creature* Doctor = (ObjectAccessor::GetCreature((*me), Doctorguid));
                        if (Doctor)
                            ((npc_doctor::npc_doctorAI*)Doctor->AI())->PatientSaved(me, (caster->ToPlayer()), Coord);
                    }
                }
                //make not selectable
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                //regen health
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IN_COMBAT);
                //stand up
                me->SetUInt32Value(UNIT_FIELD_BYTES_1, PLAYER_STATE_NONE);
                me->Say(SAY_DOC1, LANG_UNIVERSAL, nullptr);

                uint32 mobId = me->GetEntry();
                me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                switch (mobId)
                {
                case 12923:
                case 12924:
                case 12925:
                    me->GetMotionMaster()->MovePoint(0, H_RUNTOX, H_RUNTOY, H_RUNTOZ);
                    break;
                case 12936:
                case 12937:
                case 12938:
                    me->GetMotionMaster()->MovePoint(0, A_RUNTOX, A_RUNTOY, A_RUNTOZ);
                    break;
                }
            }
            return;
        }

        void UpdateAI(const uint32 diff)
            override {
            if (me->IsAlive() && me->GetHealth() > 6)
            {                                                   //lower HP on every world tick makes it a useful counter, not officlone though
                me->SetHealth(uint32(me->GetHealth() - 5));
            }

            if (me->IsAlive() && me->GetHealth() <= 6)
            {
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IN_COMBAT);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->SetDeathState(JUST_DIED);
                me->SetFlag(UNIT_DYNAMIC_FLAGS, 32);

                if (Doctorguid)
                {
                    Creature* Doctor = (ObjectAccessor::GetCreature((*me), Doctorguid));
                    if (Doctor)
                        ((npc_doctor::npc_doctorAI*)Doctor->AI())->PatientDied(Coord);
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_injured_patientAI(creature);
    }
};



void npc_doctor::npc_doctorAI::BeginEvent(Player* player)
{
    Playerguid = player->GetGUID();

    SummonPatient_Timer = 10000;
    SummonPatientCount = 0;
    PatientDiedCount = 0;
    PatientSavedCount = 0;

    switch (me->GetEntry())
    {
    case DOCTOR_ALLIANCE:
        for (auto & AllianceCoord : AllianceCoords)
            Coordinates.push_back(&AllianceCoord);
        break;

    case DOCTOR_HORDE:
        for (auto & HordeCoord : HordeCoords)
            Coordinates.push_back(&HordeCoord);
        break;
    }

    Event = true;

    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
}

void npc_doctor::npc_doctorAI::PatientDied(Location* Point)
{
    Player* player = ObjectAccessor::GetPlayer(*me, Playerguid);
    if (player && ((player->GetQuestStatus(6624) == QUEST_STATUS_INCOMPLETE) || (player->GetQuestStatus(6622) == QUEST_STATUS_INCOMPLETE)))
    {
        PatientDiedCount++;
        if (PatientDiedCount > 5 && Event)
        {
            if (player->GetQuestStatus(6624) == QUEST_STATUS_INCOMPLETE)
                player->FailQuest(6624);
            else if (player->GetQuestStatus(6622) == QUEST_STATUS_INCOMPLETE)
                player->FailQuest(6622);

            Event = false;
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }

        Coordinates.push_back(Point);
    }
    else        // No player, disconnected ? Stopping event.
        Event = false;
}

void npc_doctor::npc_doctorAI::PatientSaved(Creature* soldier, Player* player, Location* Point)
{
    if (player && Playerguid == player->GetGUID())
    {
        if ((player->GetQuestStatus(6624) == QUEST_STATUS_INCOMPLETE) || (player->GetQuestStatus(6622) == QUEST_STATUS_INCOMPLETE))
        {
            PatientSavedCount++;
            if (PatientSavedCount == 15)
            {
                if (!Patients.empty())
                {
                    std::list<uint64>::iterator itr;
                    for (itr = Patients.begin(); itr != Patients.end(); ++itr)
                    {
                        Creature* Patient = (ObjectAccessor::GetCreature((*me), *itr));
                        if (Patient)
                            Patient->SetDeathState(JUST_DIED);
                    }
                }

                if (player->GetQuestStatus(6624) == QUEST_STATUS_INCOMPLETE)
                    player->AreaExploredOrEventHappens(6624);
                else if (player->GetQuestStatus(6622) == QUEST_STATUS_INCOMPLETE)
                    player->AreaExploredOrEventHappens(6622);

                Event = false;
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            }

            Coordinates.push_back(Point);
        }
    }
    else        // No player, disconnected ? Stopping event.
        Event = false;
}

void npc_doctor::npc_doctorAI::UpdateAI(const uint32 diff)
{
    if(Event && SummonPatientCount >= 20)
    {
        Event = false;
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    }

    if(Event)
    {
        if(SummonPatient_Timer < diff)
        {
            Creature* Patient = nullptr;
            Location* Point = nullptr;

            if(Coordinates.empty())
                return;

            auto itr = Coordinates.begin()+rand()%Coordinates.size();
            uint32 patientEntry = 0;

            switch(me->GetEntry())
            {
                case DOCTOR_ALLIANCE: patientEntry = AllianceSoldierId[rand()%3]; break;
                case DOCTOR_HORDE:    patientEntry = HordeSoldierId[rand()%3]; break;
                default:
                    error_log("TSCR: Invalid entry for Triage doctor. Please check your database");
                    return;
            }

            Point = *itr;

            Patient = me->SummonCreature(patientEntry, Point->x, Point->y, Point->z, Point->o, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
            if(Patient)
            {
                Patients.push_back(Patient->GetGUID());
                ((npc_injured_patient::npc_injured_patientAI*)Patient->AI())->Doctorguid = me->GetGUID();
                if(Point)
                    ((npc_injured_patient::npc_injured_patientAI*)Patient->AI())->Coord = Point;
                Coordinates.erase(itr);
            }
            SummonPatient_Timer = 10000;
            SummonPatientCount++;
        } 
        else 
        { 
            SummonPatient_Timer -= diff; 
        }
    } 
    else //!Event
    {
        if (me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    }
}


/*######
## npc_guardian
######*/

#define SPELL_DEATHTOUCH                5
#define SAY_AGGRO                        "This area is closed!"


class npc_guardian : public CreatureScript
{
public:
    npc_guardian() : CreatureScript("npc_guardian")
    { }

    class npc_guardianAI : public ScriptedAI
    {
        public:
        npc_guardianAI(Creature *c) : ScriptedAI(c) {}
    
        void Reset()
        override {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }
    
        void EnterCombat(Unit *who)
        override {
            me->Yell(SAY_AGGRO,LANG_UNIVERSAL,nullptr);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (!UpdateVictim())
                return;
    
            if (me->IsAttackReady())
            {
                me->CastSpell(me->GetVictim(),SPELL_DEATHTOUCH, true);
                me->ResetAttackTimer();
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_guardianAI(creature);
    }
};


/*######
## npc_mount_vendor
######*/

class npc_mount_vendor : public CreatureScript
{
public:
    npc_mount_vendor() : CreatureScript("npc_mount_vendor")
    { }

    class npc_mount_vendorAI : public ScriptedAI
    {
    public:
        npc_mount_vendorAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            if (me->IsQuestGiver())
                player->PrepareQuestMenu( me->GetGUID() );

            bool canBuy;
            canBuy = false;
            uint32 vendor = me->GetEntry();
            uint8 race = player->GetRace();

            switch (vendor)
            {
                case 384:                                           //Katie Hunter
                case 1460:                                          //Unger Statforth
                case 2357:                                          //Merideth Carlson
                case 4885:                                          //Gregor MacVince
                    if (player->GetReputationRank(72) != REP_EXALTED && race != RACE_HUMAN)
                        player->SEND_GOSSIP_MENU_TEXTID(5855, me->GetGUID());
                    else canBuy = true;
                    break;
                case 1261:                                          //Veron Amberstill
                    if (player->GetReputationRank(47) != REP_EXALTED && race != RACE_DWARF)
                        player->SEND_GOSSIP_MENU_TEXTID(5856, me->GetGUID());
                    else canBuy = true;
                    break;
                case 3362:                                          //Ogunaro Wolfrunner
                    if (player->GetReputationRank(76) != REP_EXALTED && race != RACE_ORC)
                        player->SEND_GOSSIP_MENU_TEXTID(5841, me->GetGUID());
                    else canBuy = true;
                    break;
                case 3685:                                          //Harb Clawhoof
                    if (player->GetReputationRank(81) != REP_EXALTED && race != RACE_TAUREN)
                        player->SEND_GOSSIP_MENU_TEXTID(5843, me->GetGUID());
                    else canBuy = true;
                    break;
                case 4730:                                          //Lelanai
                    if (player->GetReputationRank(69) != REP_EXALTED && race != RACE_NIGHTELF)
                        player->SEND_GOSSIP_MENU_TEXTID(5844, me->GetGUID());
                    else canBuy = true;
                    break;
                case 4731:                                          //Zachariah Post
                    if (player->GetReputationRank(68) != REP_EXALTED && race != RACE_UNDEAD_PLAYER)
                        player->SEND_GOSSIP_MENU_TEXTID(5840, me->GetGUID());
                    else canBuy = true;
                    break;
                case 7952:                                          //Zjolnir
                    if (player->GetReputationRank(530) != REP_EXALTED && race != RACE_TROLL)
                        player->SEND_GOSSIP_MENU_TEXTID(5842, me->GetGUID());
                    else canBuy = true;
                    break;
                case 7955:                                          //Milli Featherwhistle
                    if (player->GetReputationRank(54) != REP_EXALTED && race != RACE_GNOME)
                        player->SEND_GOSSIP_MENU_TEXTID(5857, me->GetGUID());
                    else canBuy = true;
                    break;
                case 16264:                                         //Winaestra
                    if (player->GetReputationRank(911) != REP_EXALTED && race != RACE_BLOODELF)
                        player->SEND_GOSSIP_MENU_TEXTID(10305, me->GetGUID());
                    else canBuy = true;
                    break;
                case 17584:                                         //Torallius the Pack Handler
                    if (player->GetReputationRank(930) != REP_EXALTED && race != RACE_DRAENEI)
                        player->SEND_GOSSIP_MENU_TEXTID(10239, me->GetGUID());
                    else canBuy = true;
                    break;
            }

            if (canBuy)
            {
                if (me->IsVendor())
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);

                SEND_PREPARED_GOSSIP_MENU(player, me);
            }
            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            if (action == GOSSIP_ACTION_TRADE)
                player->SEND_VENDORLIST( me->GetGUID() );

            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_mount_vendorAI(creature);
    }
};



/*######
## npc_rogue_trainer
######*/

class npc_rogue_trainer : public CreatureScript
{
public:
    npc_rogue_trainer() : CreatureScript("npc_rogue_trainer")
    { }

    class npc_rogue_trainerAI : public ScriptedAI
    {
    public:
        npc_rogue_trainerAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            if( me->IsQuestGiver() )
                player->PrepareQuestMenu( me->GetGUID() );

            if( me->IsTrainer() )
                player->ADD_GOSSIP_ITEM(2, GOSSIP_TEXT_TRAIN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRAIN);

            if( me->canResetTalentsOf(player) )
                player->ADD_GOSSIP_ITEM(2, "I wish to unlearn my talents", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_UNLEARNTALENTS);

            if( player->GetClass() == CLASS_ROGUE && player->GetLevel() >= 24 && !player->HasItemCount(17126,1) && !player->GetQuestRewardStatus(6681) )
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "<Take the letter>", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                player->SEND_GOSSIP_MENU_TEXTID(5996, me->GetGUID());
            } else
                SEND_DEFAULT_GOSSIP_MENU(player, me);

            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            switch( action )
            {
                case GOSSIP_ACTION_INFO_DEF+1:
                    player->CLOSE_GOSSIP_MENU();
                    player->CastSpell(player,21100,false);
                    break;
                case GOSSIP_ACTION_TRAIN:
                    player->SEND_TRAINERLIST( me->GetGUID() );
                    break;
                case GOSSIP_OPTION_UNLEARNTALENTS:
                    player->CLOSE_GOSSIP_MENU();
                    player->SendTalentWipeConfirm( me->GetGUID() );
                    break;
            }
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_rogue_trainerAI(creature);
    }
};



/*######
## npc_sayge
######*/

#define SPELL_DMG       23768                               //dmg
#define SPELL_RES       23769                               //res
#define SPELL_ARM       23767                               //arm
#define SPELL_SPI       23738                               //spi
#define SPELL_INT       23766                               //int
#define SPELL_STM       23737                               //stm
#define SPELL_STR       23735                               //str
#define SPELL_AGI       23736                               //agi
#define SPELL_FORTUNE   23765                               //faire fortune

class npc_sayge : public CreatureScript
{
public:
    npc_sayge() : CreatureScript("npc_sayge")
    { }

    class npc_saygeAI : public ScriptedAI
    {
    public:
        npc_saygeAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            if(me->IsQuestGiver())
                player->PrepareQuestMenu( me->GetGUID() );

            if( player->HasSpellCooldown(SPELL_INT) ||
                player->HasSpellCooldown(SPELL_ARM) ||
                player->HasSpellCooldown(SPELL_DMG) ||
                player->HasSpellCooldown(SPELL_RES) ||
                player->HasSpellCooldown(SPELL_STR) ||
                player->HasSpellCooldown(SPELL_AGI) ||
                player->HasSpellCooldown(SPELL_STM) ||
                player->HasSpellCooldown(SPELL_SPI) )
                player->SEND_GOSSIP_MENU_TEXTID(7393, me->GetGUID());
            else
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Yes", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                player->SEND_GOSSIP_MENU_TEXTID(7339, me->GetGUID());
            }

            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            switch(sender)
            {
                case GOSSIP_SENDER_MAIN:
                    SendAction_npc_sayge(player, me, action);
                    break;
                case GOSSIP_SENDER_MAIN+1:
                    me->CastSpell(player, SPELL_DMG, false);
                    player->AddSpellCooldown(SPELL_DMG,0,time(nullptr) + 7200);
                    SendAction_npc_sayge(player, me, action);
                    break;
                case GOSSIP_SENDER_MAIN+2:
                    me->CastSpell(player, SPELL_RES, false);
                    player->AddSpellCooldown(SPELL_RES,0,time(nullptr) + 7200);
                    SendAction_npc_sayge(player, me, action);
                    break;
                case GOSSIP_SENDER_MAIN+3:
                    me->CastSpell(player, SPELL_ARM, false);
                    player->AddSpellCooldown(SPELL_ARM,0,time(nullptr) + 7200);
                    SendAction_npc_sayge(player, me, action);
                    break;
                case GOSSIP_SENDER_MAIN+4:
                    me->CastSpell(player, SPELL_SPI, false);
                    player->AddSpellCooldown(SPELL_SPI,0,time(nullptr) + 7200);
                    SendAction_npc_sayge(player, me, action);
                    break;
                case GOSSIP_SENDER_MAIN+5:
                    me->CastSpell(player, SPELL_INT, false);
                    player->AddSpellCooldown(SPELL_INT,0,time(nullptr) + 7200);
                    SendAction_npc_sayge(player, me, action);
                    break;
                case GOSSIP_SENDER_MAIN+6:
                    me->CastSpell(player, SPELL_STM, false);
                    player->AddSpellCooldown(SPELL_STM,0,time(nullptr) + 7200);
                    SendAction_npc_sayge(player, me, action);
                    break;
                case GOSSIP_SENDER_MAIN+7:
                    me->CastSpell(player, SPELL_STR, false);
                    player->AddSpellCooldown(SPELL_STR,0,time(nullptr) + 7200);
                    SendAction_npc_sayge(player, me, action);
                    break;
                case GOSSIP_SENDER_MAIN+8:
                    me->CastSpell(player, SPELL_AGI, false);
                    player->AddSpellCooldown(SPELL_AGI,0,time(nullptr) + 7200);
                    SendAction_npc_sayge(player, me, action);
                    break;
            }
            return true;

        }

        void SendAction_npc_sayge(Player *player, Creature *_Creature, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Slay the Man", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Turn him over to liege", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Confiscate the corn", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Let him go and have the corn", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->SEND_GOSSIP_MENU_TEXTID(7340, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Execute your friend painfully", GOSSIP_SENDER_MAIN + 1, GOSSIP_ACTION_INFO_DEF);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Execute your friend painlessly", GOSSIP_SENDER_MAIN + 2, GOSSIP_ACTION_INFO_DEF);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Let your friend go", GOSSIP_SENDER_MAIN + 3, GOSSIP_ACTION_INFO_DEF);
                player->SEND_GOSSIP_MENU_TEXTID(7341, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Confront the diplomat", GOSSIP_SENDER_MAIN + 4, GOSSIP_ACTION_INFO_DEF);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Show not so quiet defiance", GOSSIP_SENDER_MAIN + 5, GOSSIP_ACTION_INFO_DEF);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Remain quiet", GOSSIP_SENDER_MAIN + 2, GOSSIP_ACTION_INFO_DEF);
                player->SEND_GOSSIP_MENU_TEXTID(7361, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Speak against your brother openly", GOSSIP_SENDER_MAIN + 6, GOSSIP_ACTION_INFO_DEF);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Help your brother in", GOSSIP_SENDER_MAIN + 7, GOSSIP_ACTION_INFO_DEF);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Keep your brother out without letting him know", GOSSIP_SENDER_MAIN + 8, GOSSIP_ACTION_INFO_DEF);
                player->SEND_GOSSIP_MENU_TEXTID(7362, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Take credit, keep gold", GOSSIP_SENDER_MAIN + 5, GOSSIP_ACTION_INFO_DEF);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Take credit, share the gold", GOSSIP_SENDER_MAIN + 4, GOSSIP_ACTION_INFO_DEF);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Let the knight take credit", GOSSIP_SENDER_MAIN + 3, GOSSIP_ACTION_INFO_DEF);
                player->SEND_GOSSIP_MENU_TEXTID(7363, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Thanks", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->SEND_GOSSIP_MENU_TEXTID(7364, _Creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:
                _Creature->CastSpell(player, SPELL_FORTUNE, false);
                player->SEND_GOSSIP_MENU_TEXTID(7365, _Creature->GetGUID());
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_saygeAI(creature);
    }
};



class npc_steam_tonk : public CreatureScript
{
public:
    npc_steam_tonk() : CreatureScript("npc_steam_tonk")
    { }

    class npc_steam_tonkAI : public ScriptedAI
    {
        public:
        npc_steam_tonkAI(Creature *c) : ScriptedAI(c) {}
    
        void Reset() override {}
        void EnterCombat(Unit *who) override {}
    
        void OnPossess(Unit* charmer, bool apply) override
        {
            if (apply)
            {
                // Initialize the action bar without the melee attack command
                me->InitCharmInfo();
                me->GetCharmInfo()->InitEmptyActionBar(false);
    
                me->SetReactState(REACT_PASSIVE);
            }
            else
                me->SetReactState(REACT_AGGRESSIVE);
        }
    
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_steam_tonkAI(creature);
    }
};


#define SPELL_TONK_MINE_DETONATE 25099


class npc_tonk_mine : public CreatureScript
{
public:
    npc_tonk_mine() : CreatureScript("npc_tonk_mine")
    { }

    class npc_tonk_mineAI : public ScriptedAI
    {
        public:
        npc_tonk_mineAI(Creature *c) : ScriptedAI(c)
        {
            me->SetReactState(REACT_PASSIVE);
        }
    
        uint32 ExplosionTimer;
    
        void Reset()
        override {
            ExplosionTimer = 3000;
        }
    
        void EnterCombat(Unit *who) override {}
        void AttackStart(Unit *who) override {}
        void MoveInLineOfSight(Unit *who) override {}
    
        void UpdateAI(const uint32 diff)
        override {
            if (ExplosionTimer < diff)
            {
                me->CastSpell(me, SPELL_TONK_MINE_DETONATE, true);
                me->SetDeathState(DEAD); // unsummon it
            } else
                ExplosionTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_tonk_mineAI(creature);
    }
};


/*####
## npc_winter_reveler
####*/

class npc_winter_reveler : public CreatureScript
{
public:
    npc_winter_reveler() : CreatureScript("npc_winter_reveler")
    { }

    class npc_winter_revelerAI : public ScriptedAI
    {
    public:
        npc_winter_revelerAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual void ReceiveEmote(Player* player, uint32 emote) override
        {
            if (player->GetDummyAura(26218))
                return;

            if( emote == TEXTEMOTE_KISS )
            {
                me->CastSpell(me, 26218, false);
                player->CastSpell(player, 26218, true);
                switch(rand()%3)
                {
                case 0: me->CastSpell(player, 26207, false); break;
                case 1: me->CastSpell(player, 26206, false); break;
                case 2: me->CastSpell(player, 45036, false); break;
                }
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_winter_revelerAI(creature);
    }
};


/*####
## npc_brewfest_reveler
####*/

class npc_brewfest_reveler : public CreatureScript
{
public:
    npc_brewfest_reveler() : CreatureScript("npc_brewfest_reveler")
    { }

    class npc_brewfest_revelerAI : public ScriptedAI
    {
    public:
        npc_brewfest_revelerAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual void ReceiveEmote(Player* player, uint32 emote) override
        {
            if( emote == TEXTEMOTE_DANCE )
                me->CastSpell(player, 41586, false);
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_brewfest_revelerAI(creature);
    }
};


/*####
## npc_snake_trap_serpents
####*/

#define SPELL_MIND_NUMBING_POISON    8692    //Viper
#define SPELL_DEADLY_POISON          34655   //Venomous Snake
#define SPELL_CRIPPLING_POISON       3409    //Viper

#define VENOMOUS_SNAKE_TIMER 1200
#define VIPER_TIMER 3000

#define C_VIPER 19921

#define RAND 5


class npc_snake_trap_serpents : public CreatureScript
{
public:
    npc_snake_trap_serpents() : CreatureScript("npc_snake_trap_serpents")
    { }

    class npc_snake_trap_serpentsAI : public ScriptedAI
    {
        public:
        npc_snake_trap_serpentsAI(Creature *c) : ScriptedAI(c) {}
    
        uint32 SpellTimer;
        Unit *Owner;
        bool IsViper;
    
        void EnterCombat(Unit *who) override {}
    
        void Reset()
        override {
            Owner = me->GetOwner();
    
            if (!me->IsPet() || !Owner)
                return;
    
            CreatureTemplate const *Info = me->GetCreatureTemplate();
    
            if(Info->Entry == C_VIPER)
                IsViper = true;
    
            //Add delta to make them not all hit the same time
            me->SetAttackTimer(BASE_ATTACK,(me->GetAttackTimer(BASE_ATTACK) * frand(0.0f,1.0f)));
        }
    
        //Redefined for random target selection:
        void MoveInLineOfSight(Unit *who)
        override {
            if (!me->IsPet() || !Owner)
                return;
    
            if( !me->GetVictim() && me->CanAttack(who) == CAN_ATTACK_RESULT_OK && ( me->IsHostileTo( who )) && who->isInAccessiblePlaceFor(me) && Owner->IsHostileTo(who))//don't attack not-pvp-flaged
            {
                if (me->GetDistanceZ(who) > CREATURE_Z_ATTACK_RANGE)
                    return;
    
                float attackRadius = me->GetAggroRange(who);
                if( me->IsWithinDistInMap(who, attackRadius) && me->IsWithinLOSInMap(who) )
                {
                    if (!(rand() % RAND) )
                    {
                        me->SetAttackTimer(BASE_ATTACK, (rand() % 10) * 100);
                        SpellTimer = (rand() % 10) * 100;
                        AttackStart(who);
                    }
                }
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (!me->IsPet() || !Owner)
                return;
    
            //Follow if not in combat
            if (!me->HasUnitState(UNIT_STATE_FOLLOW)&& !me->IsInCombat())
            {
                me->GetMotionMaster()->Clear();
                me->GetMotionMaster()->MoveFollow(Owner,PET_FOLLOW_DIST,me->GetFollowAngle());
            }
    
            //No victim -> get new from owner (need this because MoveInLineOfSight won't work while following -> corebug)
            if (!me->GetVictim())
            {
                if (me->IsInCombat())
                    DoStopAttack();
    
                if(Owner->GetAttackerForHelper())
                    AttackStart(Owner->GetAttackerForHelper());
    
                return;
            }
    
            if (SpellTimer < diff)
            {
                if (IsViper) //Viper
                {
                    if (rand() % 3 == 0) //33% chance to cast
                    {
                        uint32 spell;
                        if( rand() % 2 == 0)
                            spell = SPELL_MIND_NUMBING_POISON;
                        else
                            spell = SPELL_CRIPPLING_POISON;
    
                        DoCast(me->GetVictim(),spell);
                    }
    
                    SpellTimer = VIPER_TIMER;
                }
                else //Venomous Snake
                {
                    if (rand() % 10 < 8) //80% chance to cast
                        DoCast(me->GetVictim(),SPELL_DEADLY_POISON);
                    SpellTimer = VENOMOUS_SNAKE_TIMER + (rand() %5)*100;
                }
            }else SpellTimer-=diff;
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_snake_trap_serpentsAI(creature);
    }
};


#define SPELL_DETONATION        4043

/*######
## npc_goblin_land_mine
######*/


class npc_goblin_land_mine : public CreatureScript
{
public:
    npc_goblin_land_mine() : CreatureScript("npc_goblin_land_mine")
    { }

    class npc_goblin_land_mineAI : public ScriptedAI
    {
        public:
        npc_goblin_land_mineAI(Creature* c) : ScriptedAI(c) {}
        
        uint32 armTimer;
        bool isArmed;
        
        void Reset ()
        override {
            armTimer = 10000;       // 10 seconds before it can explode when hostile creature comes in range
            isArmed = false;
            
            me->SetSpeedRate(MOVE_RUN, 0.0f);
        }
        
        void EnterCombat(Unit* pWho) override {}
        
        void JustDied(Unit* pKiller)
        override {
            me->ForcedDespawn();
        }
        
        void MoveInLineOfSight(Unit* pWho)
        override {
            if (!isArmed)
                return;
                
            if (!pWho)
                return;
            
            if (me->GetDistance2d(pWho) < 3 && pWho->IsHostileTo(me)) {
                DoCast(pWho, SPELL_DETONATION);     // Explode and deal damage to pWho
                me->DealDamage(me, me->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NONE, nullptr, false);      // Diseappear
                me->ForcedDespawn();
            }
        }
        
        void UpdateAI(uint32 const diff)
        override {
            me->SetSpeedRate(MOVE_RUN, 0.0f);
            
            if (!isArmed)
                armTimer -= diff;
                
            if (!isArmed && armTimer < diff)
                isArmed = true;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_goblin_land_mineAI(creature);
    }
};


/*######
## npc_mojo
######*/

#define SPELL_FEELING_FROGGY    43906
#define SPELL_HEARTS            20372

#define INDECENT_WHISPER1 -1999926
//...
#define INDECENT_WHISPER7 -1999932


class npc_mojo : public CreatureScript
{
public:
    npc_mojo() : CreatureScript("npc_mojo")
    { }

    class npc_mojoAI : public PetAI
    {
        public:
        npc_mojoAI(Creature *c) : PetAI(c) {}
        
        uint32 MorphTimer;      /* new hooks OwnerGainedAura and OwnerLostAura? Useless in this case, as morphed player may not be owner, but keep the idea. */
        uint64 PlayerGUID;
        
        void EnterCombat(Unit *pWho) override {}
        void Reset()
        override {
            me->GetMotionMaster()->MoveFollow(me->GetOwner(), PET_FOLLOW_DIST, me->GetFollowAngle());
            MorphTimer = 0;
            PlayerGUID = 0;
        }
        
        void UpdateAI(uint32 const diff)
        override {
            PetAI::Minipet_DistanceCheck(diff);
            if (MorphTimer) {
                if (Player *plr = ObjectAccessor::GetPlayer(*me, PlayerGUID))
                    me->SetInFront(plr);
                if (MorphTimer <= diff) {
                    me->RemoveAurasDueToSpell(SPELL_HEARTS);
                    me->GetMotionMaster()->MoveFollow(me->GetOwner(), PET_FOLLOW_DIST, me->GetFollowAngle());
                    MorphTimer = 0;
                    PlayerGUID = 0;
                }
                else
                    MorphTimer -= diff;
            }
        }

        virtual void ReceiveEmote(Player* pPlayer, uint32 emote) override
        {
            if (me->GetOwner()->GetTypeId() == TYPEID_PLAYER && pPlayer->GetTeam() != me->GetOwner()->ToPlayer()->GetTeam())
                return;
                
            if (((npc_mojo::npc_mojoAI*)me->AI())->PlayerGUID != 0)
                return;
            
            if (emote == TEXTEMOTE_KISS) {
                ((npc_mojo::npc_mojoAI*)me->AI())->MorphTimer = 15000;
                ((npc_mojo::npc_mojoAI*)me->AI())->PlayerGUID = pPlayer->GetGUID();
                me->AddAura(SPELL_HEARTS, me);
                if (!pPlayer->IsInCombat())
                    pPlayer->CastSpell(pPlayer, SPELL_FEELING_FROGGY, true);
                me->old_Whisper(irand(INDECENT_WHISPER7, INDECENT_WHISPER1), pPlayer->GetGUID());
                me->SetInFront(pPlayer);
                me->GetMotionMaster()->MoveFollow(pPlayer, PET_FOLLOW_DIST/3.0f, M_PI/4);
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_mojoAI(creature);
    }
};



/*######
## npc_explosive_sheep
######*/

#define SPELL_EXPLODE       4050


class npc_explosive_sheep : public CreatureScript
{
public:
    npc_explosive_sheep() : CreatureScript("npc_explosive_sheep")
    { }

    class npc_explosive_sheepAI : public ScriptedAI
    {
        public:
        npc_explosive_sheepAI(Creature *c) : ScriptedAI(c) {}
        
        void Reset()
        override {
            me->GetMotionMaster()->MoveFollow(me->GetOwner(), PET_FOLLOW_DIST, me->GetFollowAngle());
        }
        
        void EnterCombat(Unit *pWho)
        override {
            me->GetMotionMaster()->MoveChase(pWho);
        }
        
        void UpdateAI(uint32 const diff)
        override {            
            if (UpdateVictim()) 
            {
                if (me->IsWithinDistInMap(me->GetVictim(), 5.0f)) 
                {
                    DoCast(me->GetVictim(), SPELL_EXPLODE);
                    if (TempSummon* summon = me->ToTempSummon())
                        summon->UnSummon();
                    else
                        me->DisappearAndDie();
    
                    if (me->GetOwner() && me->GetOwner()->ToPlayer()) {
                        me->GetOwner()->ToPlayer()->SendCooldownEvent(sSpellMgr->GetSpellInfo(4074));
                    }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_explosive_sheepAI(creature);
    }
};


/*######
## npc_pet_bomb
######*/

#define SPELL_MALFUNCTION_EXPLOSION       13261


class npc_pet_bomb : public CreatureScript
{
public:
    npc_pet_bomb() : CreatureScript("npc_pet_bomb")
    { }

    class npc_pet_bombAI : public PetAI
    {
        public:
        npc_pet_bombAI(Creature *c) : PetAI(c) {}
        
        void Reset()
        override {
            me->GetMotionMaster()->MoveFollow(me->GetOwner(), PET_FOLLOW_DIST, me->GetFollowAngle());
        }
        
        void EnterCombat(Unit *pWho)
        override {
            me->GetMotionMaster()->MoveChase(pWho);
        }
        
        void UpdateAI(uint32 const diff)
        override {        
            PetAI::Minipet_DistanceCheck(diff);
            if (me->GetVictim()) {
                if (me->IsWithinDistInMap(me->GetVictim(), 3.0f)) {
                    me->CastSpell(me->GetVictim(), SPELL_MALFUNCTION_EXPLOSION, false);
                    me->DisappearAndDie();
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_pet_bombAI(creature);
    }
};


class npc_morph : public CreatureScript
{
public:
    npc_morph() : CreatureScript("npc_morph")
    { }

    class npc_morphAI : public ScriptedAI
    {
    public:
        npc_morphAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Illusion de gnome mâle", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Illusion de gnome femelle", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            
            player->SEND_GOSSIP_MENU_TEXTID(7339, me->GetGUID());
            
            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            switch (action) {
            case GOSSIP_ACTION_INFO_DEF:
                player->CastSpell(player, 37808, true);
                break;
            case GOSSIP_ACTION_INFO_DEF+1:
                player->CastSpell(player, 37809, true);
                break;
            }
            
            player->CLOSE_GOSSIP_MENU();
            
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_morphAI(creature);
    }
};



/*######
## npc_metzen
######*/

class npc_metzen : public CreatureScript
{
public:
    npc_metzen() : CreatureScript("npc_metzen")
    { }

    class npc_metzenAI : public ScriptedAI
    {
    public:
        npc_metzenAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            if (player->GetQuestStatus(8746) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(8762) == QUEST_STATUS_INCOMPLETE)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Secouer un peu de la poudre de renne sur Metzen.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                
            SEND_PREPARED_GOSSIP_MENU(player, me);

            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            player->CLOSE_GOSSIP_MENU();

            if (action == GOSSIP_ACTION_INFO_DEF) {
                player->KilledMonsterCredit(me->GetEntry(), me->GetGUID());
                me->CastSpell(me, 25952, false);
            }
            
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_metzenAI(creature);
    }
};



/*######
## npc_clockwork_rocket_bot
######*/


class npc_clockwork_rocket_bot : public CreatureScript
{
public:
    npc_clockwork_rocket_bot() : CreatureScript("npc_clockwork_rocket_bot")
    { }

    class npc_clockwork_rocket_botAI : public PetAI
    {
        public:
        npc_clockwork_rocket_botAI(Creature* c) : PetAI(c) {}
        
        void Reset()
        override {
            if (Unit* owner = me->GetOwner())
                me->GetMotionMaster()->MoveFollow(owner, PET_FOLLOW_DIST, me->GetFollowAngle());
        }
    
        void EnterCombat(Unit* who) override {}
        
        void MoveInLineOfSight(Unit* who)
        override {
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
                
            if (who->ToCreature() && who->GetEntry() == me->GetEntry() && who->IsWithinDistInMap(me, 15.0f))
                me->CastSpell(who, 45269, false);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_clockwork_rocket_botAI(creature);
    }
};


/*######
## npc_halaa_bomb_target
######*/


class npc_halaa_bomb_target : public CreatureScript
{
public:
    npc_halaa_bomb_target() : CreatureScript("npc_halaa_bomb_target")
    { }

    class npc_halaa_bomb_targetAI : public ScriptedAI
    {
        public:
        npc_halaa_bomb_targetAI(Creature* c) : ScriptedAI(c) 
        {
            SetCombatMovementAllowed(false);
        }
        
        uint32 despawnTimer;
        
        void Reset()
        override {
            me->SetKeepActive(5 * MINUTE*IN_MILLISECONDS);
            despawnTimer = 300000; // 5 min
            DoCast(me, 31963, true);
            HandleAOE();
        }
        
        void HandleAOE()
        {
            std::list<WorldObject*> targets;
            float dist = 10.0f;
            Trinity::AllWorldObjectsInRange u_check(me, dist);
            Trinity::WorldObjectListSearcher<Trinity::AllWorldObjectsInRange> searcher(me, targets, u_check);
            Cell::VisitAllObjects(me, searcher, dist);
    
            for (std::list<WorldObject*>::const_iterator itr = targets.begin(); itr != targets.end(); itr++) {
                if ((*itr)->ToPlayer())
                    ((Unit*)(*itr))->CastSpell((Unit*)(*itr), 31961, true);
                else if ((*itr)->ToCreature())
                    ((Unit*)(*itr))->AddAura(31961, (Unit*)(*itr));
            }
        }
        
        void EnterCombat(Unit* who) override {}
        
        void UpdateAI(uint32 const diff)
        override {
            if (despawnTimer <= diff) {
                me->DisappearAndDie();
                despawnTimer = 999999;
            }
            else
                despawnTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_halaa_bomb_targetAI(creature);
    }
};


/*######
## trigger_omen
######*/

float omenSpawnPos[][4] = { {7556.229492, -2830.243164, 448.822937, 3.877239},
                            {7554.257324, -2827.974121, 449.009674, 3.877239},
                            {7552.139648, -2825.533203, 449.265167, 3.877239},
                            {7550.149414, -2823.249023, 449.503662, 3.877239},
                            {7548.523438, -2821.410645, 449.628235, 3.877239},
                            {7549.447754, -2826.799072, 450.329956, 3.877239},
                            {7548.183594, -2825.402100, 450.329956, 3.877239},
                            {7546.125488, -2823.120850, 450.347137, 3.877239},
                            {7544.830078, -2821.656494, 450.429199, 3.877239},
                            {7543.526367, -2820.192139, 450.487335, 3.877239}};



class trigger_omen : public CreatureScript
{
public:
    trigger_omen() : CreatureScript("trigger_omen")
    { }

    class trigger_omenAI : public ScriptedAI
    {
        public:
        trigger_omenAI(Creature* c) : ScriptedAI(c) 
        {
            SetCombatMovementAllowed(false);
        }
        
        uint32 step;
        uint32 counter;
        
        void Reset()
        override {
            step = 0;
            counter = 0;
        }
        
        void SetData(uint32 field, uint32 value, Unit* setter)
        override {
            counter++;
            
            if (counter == 5) {
                DoSpawnWave(step);
                if (step > 3)
                    Reset();
            }
        }
        
        void JustSummoned(Creature* summoned)
        override {
            /*if (Creature* target = summoned->SelectNearestTarget(30.0f))
                summoned->AI()->AttackStart(target);*/
            summoned->GetMotionMaster()->MovePoint(0, 7539.403809, -2841.265381, 457.147766/*, false*/);
        }
        
        void DoSpawnWave(uint32 pStep)
        {
            switch (pStep) {
            case 0:
                for (uint8 i = 5; i < 10; i++)
                    me->SummonCreature(15466, omenSpawnPos[i][0], omenSpawnPos[i][1], omenSpawnPos[i][2], omenSpawnPos[i][3], TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000);
                    
                break;
            case 1:
            case 2:
                for (auto & omenSpawnPo : omenSpawnPos)
                    me->SummonCreature(15466, omenSpawnPo[0], omenSpawnPo[1], omenSpawnPo[2], omenSpawnPo[3], TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000);
                    
                break;
            case 3:
                me->SummonCreature(15467, omenSpawnPos[2][0], omenSpawnPos[2][1], omenSpawnPos[2][2], omenSpawnPos[2][3], TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000);
                break;
            }
            
            counter = 0;
            ++step;
        }
        
        void EnterCombat(Unit* who) override {}
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new trigger_omenAI(creature);
    }
};


/*######
## lunar_large_spotlight
######*/

struct lunar_large_spotlightAI: public ScriptedAI
{

    void EnterCombat(Unit* who) override {}

    void SpellHit(Unit* caster, const SpellInfo* spell)
    override {
        if (caster->GetTypeId() != TYPEID_PLAYER)
            return;

        if (spell->Id != 26373)
            return;

        if (me->GetZoneId() == 493) {
            Creature* reveler = nullptr;
            if ((reveler = caster->FindNearestCreature(15694, 2.0f, true)) && caster->ToPlayer()->GetTeam() == ALLIANCE)
                caster->ToPlayer()->TeleportTo(0, -8748.578125, 1074.502808, 90.559525, TELE_TO_NOT_UNSUMMON_PET, 0);
            else if ((reveler = caster->FindNearestCreature(15719, 2.0f, true)) && caster->ToPlayer()->GetTeam() == HORDE)
                caster->ToPlayer()->TeleportTo(1, -1031.914673, -230.591858, 160.152725, TELE_TO_NOT_UNSUMMON_PET, 0);
            else if ((reveler = caster->FindNearestCreature(15905, 2.0f, true)) && caster->ToPlayer()->GetTeam() == ALLIANCE)
                caster->ToPlayer()->TeleportTo(1, 10150.287109, 2602.150879, 1330.827271, TELE_TO_NOT_UNSUMMON_PET, 0);
            else if ((reveler = caster->FindNearestCreature(15906, 2.0f, true)) && caster->ToPlayer()->GetTeam() == ALLIANCE)
                caster->ToPlayer()->TeleportTo(0, -4663.084473, -956.074341, 500.376801, TELE_TO_NOT_UNSUMMON_PET, 0);
            else if ((reveler = caster->FindNearestCreature(15907, 2.0f, true)) && caster->ToPlayer()->GetTeam() == HORDE)
                caster->ToPlayer()->TeleportTo(0, 1642.087036, 239.751450, 62.591553, TELE_TO_NOT_UNSUMMON_PET, 0);
            else if ((reveler = caster->FindNearestCreature(15908, 2.0f, true)) && caster->ToPlayer()->GetTeam() == HORDE)
                caster->ToPlayer()->TeleportTo(1, 1983.555298, -4255.447266, 31.666471, TELE_TO_NOT_UNSUMMON_PET, 0);
        }
        else {
            switch (caster->GetZoneId()) {
            case 85: // Undercity
                caster->ToPlayer()->TeleportTo(1, 7575.282715, -2239.033691, 469.744263, TELE_TO_NOT_UNSUMMON_PET, 0);
                break;
            case 1638: // Thunder Bluff
                caster->ToPlayer()->TeleportTo(1, 7603.741699, -2211.346924, 471.583405, TELE_TO_NOT_UNSUMMON_PET, 0);
                break;
            case 1637: // Orgrimmar
                caster->ToPlayer()->TeleportTo(1, 7595.355957, -2247.288330, 466.825836, TELE_TO_NOT_UNSUMMON_PET, 0);
                break;
            case 1: // Ironforge
                caster->ToPlayer()->TeleportTo(1, 7570.259766, -2221.030273, 473.404785, TELE_TO_NOT_UNSUMMON_PET, 0);
                break;
            case 1519: // Stormwind
                caster->ToPlayer()->TeleportTo(1, 7585.179688, -2204.956055, 475.351837, TELE_TO_NOT_UNSUMMON_PET, 0);
                break;
            case 1657: // Darnassus
                caster->ToPlayer()->TeleportTo(1, 7610.898438, -2228.915283, 468.704956 , TELE_TO_NOT_UNSUMMON_PET, 0);
                break;
            }
        }
    }
};

class lunar_large_spotlight : public CreatureScript
{
public:
    lunar_large_spotlight() : CreatureScript("lunar_large_spotlight")
    { }

    class lunar_large_spotlightAI: public ScriptedAI
    {
        public:
        lunar_large_spotlightAI(Creature* c) : ScriptedAI(c) 
        {
            SetCombatMovementAllowed(false);
        }
    
        void EnterCombat(Unit* who) override {}
    
        void SpellHit(Unit* caster, const SpellInfo* spell)
        override {
            if (caster->GetTypeId() != TYPEID_PLAYER)
                return;
    
            if (spell->Id != 26373)
                return;
    
            if (me->GetZoneId() == 493) {
                Creature* reveler = nullptr;
                if ((reveler = caster->FindNearestCreature(15694, 2.0f, true)) && caster->ToPlayer()->GetTeam() == ALLIANCE)
                    caster->ToPlayer()->TeleportTo(0, -8748.578125, 1074.502808, 90.559525, TELE_TO_NOT_UNSUMMON_PET, 0);
                else if ((reveler = caster->FindNearestCreature(15719, 2.0f, true)) && caster->ToPlayer()->GetTeam() == HORDE)
                    caster->ToPlayer()->TeleportTo(1, -1031.914673, -230.591858, 160.152725, TELE_TO_NOT_UNSUMMON_PET, 0);
                else if ((reveler = caster->FindNearestCreature(15905, 2.0f, true)) && caster->ToPlayer()->GetTeam() == ALLIANCE)
                    caster->ToPlayer()->TeleportTo(1, 10150.287109, 2602.150879, 1330.827271, TELE_TO_NOT_UNSUMMON_PET, 0);
                else if ((reveler = caster->FindNearestCreature(15906, 2.0f, true)) && caster->ToPlayer()->GetTeam() == ALLIANCE)
                    caster->ToPlayer()->TeleportTo(0, -4663.084473, -956.074341, 500.376801, TELE_TO_NOT_UNSUMMON_PET, 0);
                else if ((reveler = caster->FindNearestCreature(15907, 2.0f, true)) && caster->ToPlayer()->GetTeam() == HORDE)
                    caster->ToPlayer()->TeleportTo(0, 1642.087036, 239.751450, 62.591553, TELE_TO_NOT_UNSUMMON_PET, 0);
                else if ((reveler = caster->FindNearestCreature(15908, 2.0f, true)) && caster->ToPlayer()->GetTeam() == HORDE)
                    caster->ToPlayer()->TeleportTo(1, 1983.555298, -4255.447266, 31.666471, TELE_TO_NOT_UNSUMMON_PET, 0);
            }
            else {
                switch (caster->GetZoneId()) {
                case 85: // Undercity
                    caster->ToPlayer()->TeleportTo(1, 7575.282715, -2239.033691, 469.744263, TELE_TO_NOT_UNSUMMON_PET, 0);
                    break;
                case 1638: // Thunder Bluff
                    caster->ToPlayer()->TeleportTo(1, 7603.741699, -2211.346924, 471.583405, TELE_TO_NOT_UNSUMMON_PET, 0);
                    break;
                case 1637: // Orgrimmar
                    caster->ToPlayer()->TeleportTo(1, 7595.355957, -2247.288330, 466.825836, TELE_TO_NOT_UNSUMMON_PET, 0);
                    break;
                case 1: // Ironforge
                    caster->ToPlayer()->TeleportTo(1, 7570.259766, -2221.030273, 473.404785, TELE_TO_NOT_UNSUMMON_PET, 0);
                    break;
                case 1519: // Stormwind
                    caster->ToPlayer()->TeleportTo(1, 7585.179688, -2204.956055, 475.351837, TELE_TO_NOT_UNSUMMON_PET, 0);
                    break;
                case 1657: // Darnassus
                    caster->ToPlayer()->TeleportTo(1, 7610.898438, -2228.915283, 468.704956 , TELE_TO_NOT_UNSUMMON_PET, 0);
                    break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new lunar_large_spotlightAI(creature);
    }
};


/*######
## npc_rocket_chicken
######*/


class npc_rocket_chicken : public CreatureScript
{
public:
    npc_rocket_chicken() : CreatureScript("npc_rocket_chicken")
    { }

    class npc_rocket_chickenAI : public PetAI
    {
        public:
        npc_rocket_chickenAI(Creature* c) : PetAI(c) {}
        
        uint32 animTimer;
        
        void Reset()
        override {
            animTimer = 2000+rand()%3000;
            me->GetMotionMaster()->MoveFollow(me->GetOwner(), PET_FOLLOW_DIST, me->GetFollowAngle());
        }
        
        void EnterCombat(Unit* who) override {}
        
        void OnSpellFinish(Unit* caster, uint32 spellId, Unit* target, bool ok)
        override {
            me->GetMotionMaster()->MoveFollow(me->GetOwner(), PET_FOLLOW_DIST, me->GetFollowAngle());
            
            if (rand()%5 == 0)
                me->Kill(me);
        }
        
        void UpdateAI(uint32 const diff)
        override {
            PetAI::Minipet_DistanceCheck(diff);
            if (animTimer <= diff) {
                me->GetMotionMaster()->MoveIdle();
                me->CastSpell(me, 45255, false);
                animTimer = 20000 + rand()%10000;
            }
            else
                animTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_rocket_chickenAI(creature);
    }
};


/*######
## npc_midsummer_bonfire
######*/


class npc_midsummer_bonfire : public CreatureScript
{
public:
    npc_midsummer_bonfire() : CreatureScript("npc_midsummer_bonfire")
    { }

    class npc_midsummer_bonfireAI : public ScriptedAI
    {
        public:
        npc_midsummer_bonfireAI(Creature* c) : ScriptedAI(c) {}
        
        uint32 auraTimer;
        uint32 unauraTimer;
        
        void Reset()
        override {
            auraTimer = urand(2000, 17000);
            unauraTimer = 0;
        }
        
        void EnterCombat(Unit* who) override {}
        
        void SpellHit(Unit* caster, SpellInfo const* spell)
        override {
            if (spell->Id == 46054 && me->HasAuraEffect(34832) && caster->ToPlayer()) {
                caster->ToPlayer()->KilledMonsterCredit(me->GetEntry(), me->GetGUID());
                unauraTimer = 1;
            }
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (auraTimer) {
                if (auraTimer <= diff) {
                    DoCast(me, 34832, true);
                    unauraTimer = 3500;
                    auraTimer = 0;
                }
                else
                    auraTimer -= diff;
            }
                
            if (unauraTimer) {
                if (unauraTimer <= diff) {
                    me->RemoveAurasDueToSpell(34832);
                    auraTimer = urand(10000, 25000);
                    unauraTimer = 0;
                }
                else
                    unauraTimer -= diff;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_midsummer_bonfireAI(creature);
    }
};


/*######
## npc_egbert
######*/

//todo, make use of 40670 instead

class npc_egbert : public CreatureScript
{
public:
    npc_egbert() : CreatureScript("npc_egbert")
    { }

    class npc_egbertAI : public PetAI
    {
        public:
        npc_egbertAI(Creature* c) : 
            PetAI(c), 
            following(false),
            owner(me->GetOwner())
        {}
        
        bool following;
        Unit* owner;
        float homeX, homeY, homeZ;
        float whatever;
        
        void Reset()
        override {
            if(owner)
            {
                me->GetMotionMaster()->MoveFollow(owner, PET_FOLLOW_DIST, me->GetFollowAngle());
                following = true;
            } else {
                me->GetPosition(homeX,homeY,homeZ,whatever);
                me->SetWalk(false);
            }
        }
        
        void UpdateAI(uint32 const diff)
        override {
            PetAI::Minipet_DistanceCheck(diff);
            if (owner && following && me->GetDistance(owner) < 10)
                following = false;
    
            if(!following)
            {
                if (!me->GetMotionMaster()->GetDestination(whatever,whatever,whatever)) //has no destination
                {
                    if(!owner)
                    {
                        if (me->GetDistance(homeX,homeY,homeZ) > 25)
                        {
                            me->GetMotionMaster()->MovePoint(0,homeX,homeY,homeZ,true);
                            return;
                        }
                    } else {
                        if (me->GetDistance(owner) > 20)
                        {
                            me->GetMotionMaster()->MoveFollow(owner, PET_FOLLOW_DIST, me->GetFollowAngle());
                            following = true;
                            return;
                        }
                    }
                    float newX, newY, newZ;
                    me->GetRandomPoint(me,10.0f,newX,newY,newZ);
                    me->GetMotionMaster()->MovePoint(0,newX,newY,newZ);
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_egbertAI(creature);
    }
};


/*######
## npc_babypanda
######*/

#define SPELL_SLEEP 32951
#define PANDA_SLEEP_TIMER urand(5000, 30000)


class npc_babypanda : public CreatureScript
{
public:
    npc_babypanda() : CreatureScript("npc_babypanda")
    { }

    class npc_babypandaAI : public PetAI
    {
        public:
        npc_babypandaAI(Creature* c) : 
            PetAI(c), 
            owner(me->GetOwner())
        {}
        
        Unit* owner;
        uint32 restingTimer;
        bool sleeping;
        
        void Reset()
        override {
            restingTimer = PANDA_SLEEP_TIMER;
            sleeping = false;
            if(owner)
                me->GetMotionMaster()->MoveFollow(owner, PET_FOLLOW_DIST, me->GetFollowAngle());
        }
        
        void UpdateAI(uint32 const diff)
        override {   
            PetAI::Minipet_DistanceCheck(diff);
    
            //stop sleeping if too far
            if(owner && sleeping && me->GetDistance(owner) > 20)
            {
                sleeping = false;
                me->RemoveAurasDueToSpell(SPELL_SLEEP);
                me->GetMotionMaster()->MoveFollow(owner, PET_FOLLOW_DIST, me->GetFollowAngle());
            }
    
            if(!sleeping)
            {
                //reset timer if moving
                if(me->isMoving())     
                {
                    if(restingTimer < 5000)
                        restingTimer = PANDA_SLEEP_TIMER;
    
                    return;
                }   
            
                //sleep if waited enough
                if(restingTimer <= diff)
                {           
                    sleeping = true;
                    me->GetMotionMaster()->MoveIdle();
                    me->CastSpell(me,SPELL_SLEEP,true);
                    restingTimer = PANDA_SLEEP_TIMER;
                } else restingTimer -= diff;
            }     
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_babypandaAI(creature);
    }
};


/*######
## npc_willy
######*/

#define SPELL_SLEEP 32951
#define WILLY_SLEEP_TIMER urand(15000, 40000)
#define DEATHRAY_TIMER 180000
#define DEATHRAY_CHECK_TIMER 10000
#define DEATHRAY_DURATION 800
#define SPELL_DEATHRAY 40639 //not the right spell. Only visual
#define SPELL_DEATHTOUCH 5


class npc_willy : public CreatureScript
{
public:
    npc_willy() : CreatureScript("npc_willy")
    { }

    class npc_willyAI : public PetAI
    {
        public:
        npc_willyAI(Creature* c) : 
            PetAI(c), 
            owner(me->GetOwner())
        {}
        
        Unit* owner;
    
        bool sleeping;
        uint32 restingTimer;
    
        Unit* target;
        uint32 deathRayDurationTimer;
        uint32 deathRayTimer;
        uint32 deathRayCheckTimer;
        
        void Reset()
        override {
            sleeping = false;
            me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
            restingTimer = WILLY_SLEEP_TIMER;
            deathRayDurationTimer = DEATHRAY_DURATION;
            deathRayTimer = 0;
            deathRayCheckTimer = DEATHRAY_CHECK_TIMER;
            target = nullptr;
            if(owner)
                me->GetMotionMaster()->MoveFollow(owner, PET_FOLLOW_DIST, me->GetFollowAngle());
        }
        
        void UpdateAI(uint32 const diff)
        override {   
            PetAI::Minipet_DistanceCheck(diff);
    
            //stop sleeping if too far
            if(owner && sleeping && me->GetDistance(owner) > 20)
            {
                sleeping = false;
                me->RemoveAurasDueToSpell(SPELL_SLEEP);
                me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
                me->GetMotionMaster()->MoveFollow(owner, PET_FOLLOW_DIST, me->GetFollowAngle());
            }
    
            if(!sleeping)
            {
                if(me->isMoving())     
                {
                    //reset timer if moving
                    if(restingTimer < 5000)
                        restingTimer = WILLY_SLEEP_TIMER;
                } else {
                    //sleep if waited enough
                    if(!target)
                    {
                        if(restingTimer <= diff)
                        {           
                            sleeping = true;
                            me->GetMotionMaster()->MoveIdle();
                            me->CastSpell(me,SPELL_SLEEP,true);
                            //death anim is used for willy's sleep
                            me->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH); 
                            restingTimer = WILLY_SLEEP_TIMER;
                        } else restingTimer -= diff;
                    }
                }
            
                if(deathRayTimer <= diff) //ray ready
                {
                    if(deathRayCheckTimer <= diff)
                    {
                        if (Unit* critter = FindACritterToNuke())
                        {
                            me->CastSpell(critter,SPELL_DEATHRAY,false);
                            target = critter;
                            deathRayTimer = DEATHRAY_TIMER;
                            restingTimer = WILLY_SLEEP_TIMER;
                        }
                        deathRayCheckTimer = DEATHRAY_CHECK_TIMER;
                    } else deathRayCheckTimer -= diff;
                } else deathRayTimer -= diff;
    
                
                //kill target if any (having target = started casting ray). This has to be delayed for the ray to be visible.
                if(target)
                {
                    if(deathRayDurationTimer <= diff)
                    {
                        me->CastSpell(target,SPELL_DEATHTOUCH,true);
                        target = nullptr;
                        deathRayDurationTimer = DEATHRAY_DURATION;
                    } else deathRayDurationTimer -= diff;
                }
            }     
        }
    
        Unit* FindACritterToNuke()
        {
            std::list<Unit*> list;
    
            Trinity::AnyUnfriendlyUnitInObjectRangeCheck unit_check(me, me, 15.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnfriendlyUnitInObjectRangeCheck> searcher(me, list, unit_check);
            Cell::VisitGridObjects(me, searcher, 20.0f);
    
            //return first critter if any
            for (auto & it : list)
            {
                if (it->GetCreatureType() == CREATURE_TYPE_CRITTER)
                    return it;
            }
    
            return nullptr;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_willyAI(creature);
    }
};


/*######
## grissomMorpher
######*/

class grissommorpher : public CreatureScript
{
public:
    grissommorpher() : CreatureScript("grissommorpher")
    { }

    class grissommorpherAI : public ScriptedAI
    {
    public:
        grissommorpherAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Costume 1", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Costume 2", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Costume 3", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Costume 4", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);

            pPlayer->SEND_GOSSIP_MENU_TEXTID(907, me->GetGUID());

            return true;

        }


        virtual bool GossipSelect(Player* pPlayer, uint32 sender, uint32 action) override
        {
            uint32 displayid = 19937;
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF:
                displayid = 19937;
                break;
            case GOSSIP_ACTION_INFO_DEF + 1:
                displayid = 19926;
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                displayid = 19750;
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:
                displayid = 19928;
                break;
            }
            if (displayid)
                pPlayer->SetDisplayId(displayid);

            pPlayer->PlayerTalkClass->SendCloseGossip();
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new grissommorpherAI(creature);
    }
};



void AddSC_npcs_special()
{

    new grissommorpher();

    new npc_chicken_cluck();

    new npc_dancing_flames();

    new npc_injured_patient();

    new npc_doctor();

    new npc_guardian();

    new npc_mount_vendor();

    new npc_rogue_trainer();

    new npc_sayge();

    new npc_steam_tonk();

    new npc_tonk_mine();

    new npc_winter_reveler();

    new npc_brewfest_reveler();

    new npc_snake_trap_serpents();
    
    new npc_goblin_land_mine();
    
    new npc_mojo();
    
    new npc_explosive_sheep();
    
    new npc_pet_bomb();
    
    new npc_morph();
    
    new npc_metzen();
    
    new npc_clockwork_rocket_bot();
    
    new npc_halaa_bomb_target();
    
    new trigger_omen();
    
    new lunar_large_spotlight();
    
    new npc_rocket_chicken();
    
    new npc_midsummer_bonfire();

    new npc_egbert();

    new npc_babypanda();

    new npc_willy();
}

