/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TRINITY_PASSIVEAI_H
#define TRINITY_PASSIVEAI_H

#include "CreatureAI.h"

class TC_GAME_API PassiveAI : public CreatureAI
{
    public:
        explicit PassiveAI(Creature* c);

        void MoveInLineOfSight(Unit*) {}
        void AttackStart(Unit*) {}
        void UpdateAI(uint32);

        static int Permissible(const Creature*) { return PERMIT_BASE_IDLE;  }
};

class TC_GAME_API PossessedAI : public CreatureAI
{
    public:
        explicit PossessedAI(Creature* c);

        void MoveInLineOfSight(Unit*) {}
        void AttackStart(Unit* target);
        void UpdateAI(uint32);
        void EnterEvadeMode() {}

        void JustDied(Unit*);
        void KilledUnit(Unit* victim);

        static int Permissible(const Creature*) { return PERMIT_BASE_IDLE;  }
};

class TC_GAME_API NullCreatureAI : public CreatureAI
{
    public:
        explicit NullCreatureAI(Creature* c);

        void MoveInLineOfSight(Unit*) {}
        void AttackStart(Unit*) {}
        void UpdateAI(uint32) {}
        void EnterEvadeMode() {}
        void OnCharmed(bool /*apply*/) {}
        void EnterCombat(Unit* who) {}

        static int Permissible(const Creature*) { return PERMIT_BASE_IDLE;  }
};

class TC_GAME_API CritterAI : public PassiveAI
{
    public:
        explicit CritterAI(Creature* c) : PassiveAI(c) {}

        void InitializeAI() override;
        void EnterCombat(Unit* who) override;
        void DamageTaken(Unit* done_by, uint32& /*damage*/, DamageEffectType dmgType) override;
        void EnterEvadeMode() override;
        void AttackedBy(Unit* who) override;
};

class TC_GAME_API TriggerAI : public NullCreatureAI
{
    public:
        explicit TriggerAI(Creature* c) : NullCreatureAI(c) {}
        void IsSummonedBy(Unit* summoner);
};

#endif

