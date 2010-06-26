/*
 * Sun++ Scripts for Aspire MMORPG Server
 * Copyright (C) 2005-2007 Ascent Team <http://www.ascentemu.com/>
 * Copyright (C) 2007-2008 Moon++ Team <http://www.moonplusplus.info/>
 * Copyright (C) 2008-2010 Sun++ Team <http://www.sunscripting.com/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "StdAfx.h"
#include "Setup.h"

/************************************************************************/
/* Instance_DireMaul.cpp Script											*/
/************************************************************************/

class AlzzinTheWildshaper : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(AlzzinTheWildshaper);
	SP_AI_Spell spells[3];
 bool m_spellcheck[3];

    AlzzinTheWildshaper(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		     spells[0].info = dbcSpell.LookupEntry(22689);
		     spells[0].cooldown = 10;
		     spells[0].targettype = TARGET_ATTACKING;
		     spells[0].instant = true;
		     spells[0].perctrigger = (float)RandomFloat(20.0f);
		     spells[0].attackstoptimer = 3000;
		     m_spellcheck[0] = true;


		     spells[1].info = dbcSpell.LookupEntry(22662);
		     spells[1].cooldown = 10;
		     spells[1].targettype = TARGET_ATTACKING;
		     spells[1].instant = true;
		     spells[1].perctrigger = (float)RandomFloat(20.0f);
		     spells[1].attackstoptimer = 3000;
		     m_spellcheck[1] = true;


		     spells[2].info = dbcSpell.LookupEntry(19319);
		     spells[2].cooldown = 10;
		     spells[2].targettype = TARGET_ATTACKING;
		     spells[2].instant = true;
		     spells[2].perctrigger = (float)RandomFloat(20.0f);
		     spells[2].attackstoptimer = 3000;
		     m_spellcheck[2] = true;

  }
    
    void OnCombatStart(UnitPointer mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(UnitPointer mTarget)
    {
    }

    void OnCombatStop(UnitPointer mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    UnitPointer target = NULLUNIT;
			for(int i=0;i<nrspells;i++)
			{
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

	void Destroy()
	{
		delete this;
	};

protected:

	int nrspells;
};



class CaptainKromcrush : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(CaptainKromcrush);
	SP_AI_Spell spells[2];
 bool m_spellcheck[2];

    CaptainKromcrush(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		     spells[0].info = dbcSpell.LookupEntry(15708);
		     spells[0].cooldown = 10;
		     spells[0].targettype = TARGET_ATTACKING;
		     spells[0].instant = true;
		     spells[0].perctrigger = (float)RandomFloat(20.0f);
		     spells[0].attackstoptimer = 3000;
		     m_spellcheck[0] = true;


		     spells[1].info = dbcSpell.LookupEntry(23511);
		     spells[1].cooldown = 10;
		     spells[1].targettype = TARGET_ATTACKING;
		     spells[1].instant = true;
		     spells[1].perctrigger = (float)RandomFloat(20.0f);
		     spells[1].attackstoptimer = 3000;
		     m_spellcheck[1] = true;

  }
    
    void OnCombatStart(UnitPointer mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(UnitPointer mTarget)
    {
    }

    void OnCombatStop(UnitPointer mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    UnitPointer target = NULLUNIT;
			for(int i=0;i<nrspells;i++)
			{
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

	void Destroy()
	{
		delete this;
	};

protected:

	int nrspells;
};



class ChoRushTheObserver : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(ChoRushTheObserver);
	SP_AI_Spell spells[2];
 bool m_spellcheck[2];

    ChoRushTheObserver(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		     spells[0].info = dbcSpell.LookupEntry(10947);
		     spells[0].cooldown = 10;
		     spells[0].targettype = TARGET_ATTACKING;
		     spells[0].instant = true;
		     spells[0].perctrigger = (float)RandomFloat(20.0f);
		     spells[0].attackstoptimer = 3000;
		     m_spellcheck[0] = true;


		     spells[1].info = dbcSpell.LookupEntry(10151);
		     spells[1].cooldown = 10;
		     spells[1].targettype = TARGET_ATTACKING;
		     spells[1].instant = true;
		     spells[1].perctrigger = (float)RandomFloat(20.0f);
		     spells[1].attackstoptimer = 3000;
		     m_spellcheck[1] = true;

  }
    
    void OnCombatStart(UnitPointer mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(UnitPointer mTarget)
    {
    }

    void OnCombatStop(UnitPointer mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    UnitPointer target = NULLUNIT;
			for(int i=0;i<nrspells;i++)
			{
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

	void Destroy()
	{
		delete this;
	};

protected:

	int nrspells;
};



class GuardFengus : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(GuardFengus);
	SP_AI_Spell spells[4];
 bool m_spellcheck[4];

    GuardFengus(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 4;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		     spells[0].info = dbcSpell.LookupEntry(15580);
		     spells[0].cooldown = 10;
		     spells[0].targettype = TARGET_ATTACKING;
		     spells[0].instant = true;
		     spells[0].perctrigger = (float)RandomFloat(20.0f);
		     spells[0].attackstoptimer = 3000;
		     m_spellcheck[0] = true;


		     spells[1].info = dbcSpell.LookupEntry(15655);
		     spells[1].cooldown = 10;
		     spells[1].targettype = TARGET_ATTACKING;
		     spells[1].instant = true;
		     spells[1].perctrigger = (float)RandomFloat(20.0f);
		     spells[1].attackstoptimer = 3000;
		     m_spellcheck[1] = true;


		     spells[2].info = dbcSpell.LookupEntry(22572);
		     spells[2].cooldown = 10;
		     spells[2].targettype = TARGET_ATTACKING;
		     spells[2].instant = true;
		     spells[2].perctrigger = (float)RandomFloat(20.0f);
		     spells[2].attackstoptimer = 3000;
		     m_spellcheck[2] = true;


		     spells[3].info = dbcSpell.LookupEntry(20691);
		     spells[3].cooldown = 10;
		     spells[3].targettype = TARGET_ATTACKING;
		     spells[3].instant = true;
		     spells[3].perctrigger = (float)RandomFloat(20.0f);
		     spells[3].attackstoptimer = 3000;
		     m_spellcheck[3] = true;

  }
    
    void OnCombatStart(UnitPointer mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(UnitPointer mTarget)
    {
    }

    void OnCombatStop(UnitPointer mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    UnitPointer target = NULLUNIT;
			for(int i=0;i<nrspells;i++)
			{
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

	void Destroy()
	{
		delete this;
	};

protected:

	int nrspells;
};



class GuardMolDar : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(GuardMolDar);
	SP_AI_Spell spells[3];
 bool m_spellcheck[3];

    GuardMolDar(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		     spells[0].info = dbcSpell.LookupEntry(15580);
		     spells[0].cooldown = 10;
		     spells[0].targettype = TARGET_ATTACKING;
		     spells[0].instant = true;
		     spells[0].perctrigger = (float)RandomFloat(20.0f);
		     spells[0].attackstoptimer = 3000;
		     m_spellcheck[0] = true;


		     spells[1].info = dbcSpell.LookupEntry(15655);
		     spells[1].cooldown = 10;
		     spells[1].targettype = TARGET_ATTACKING;
		     spells[1].instant = true;
		     spells[1].perctrigger = (float)RandomFloat(20.0f);
		     spells[1].attackstoptimer = 3000;
		     m_spellcheck[1] = true;


		     spells[2].info = dbcSpell.LookupEntry(20691);
		     spells[2].cooldown = 10;
		     spells[2].targettype = TARGET_ATTACKING;
		     spells[2].instant = true;
		     spells[2].perctrigger = (float)RandomFloat(20.0f);
		     spells[2].attackstoptimer = 3000;
		     m_spellcheck[2] = true;

  }
    
    void OnCombatStart(UnitPointer mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(UnitPointer mTarget)
    {
    }

    void OnCombatStop(UnitPointer mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    UnitPointer target = NULLUNIT;
			for(int i=0;i<nrspells;i++)
			{
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

	void Destroy()
	{
		delete this;
	};

protected:

	int nrspells;
};


class GuardSlipKik : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(GuardSlipKik);
	SP_AI_Spell spells[3];
 bool m_spellcheck[3];

    GuardSlipKik(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		     spells[0].info = dbcSpell.LookupEntry(15580);
		     spells[0].cooldown = 10;
		     spells[0].targettype = TARGET_ATTACKING;
		     spells[0].instant = true;
		     spells[0].perctrigger = (float)RandomFloat(20.0f);
		     spells[0].attackstoptimer = 3000;
		     m_spellcheck[0] = true;


		     spells[1].info = dbcSpell.LookupEntry(17307);
		     spells[1].cooldown = 10;
		     spells[1].targettype = TARGET_ATTACKING;
		     spells[1].instant = true;
		     spells[1].perctrigger = (float)RandomFloat(20.0f);
		     spells[1].attackstoptimer = 3000;
		     m_spellcheck[1] = true;


		     spells[2].info = dbcSpell.LookupEntry(20691);
		     spells[2].cooldown = 10;
		     spells[2].targettype = TARGET_ATTACKING;
		     spells[2].instant = true;
		     spells[2].perctrigger = (float)RandomFloat(20.0f);
		     spells[2].attackstoptimer = 3000;
		     m_spellcheck[2] = true;

  }
    
    void OnCombatStart(UnitPointer mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(UnitPointer mTarget)
    {
    }

    void OnCombatStop(UnitPointer mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    UnitPointer target = NULLUNIT;
			for(int i=0;i<nrspells;i++)
			{
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

	void Destroy()
	{
		delete this;
	};

protected:

	int nrspells;
};


class Hydrospawn : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(Hydrospawn);
	SP_AI_Spell spells[3];
 bool m_spellcheck[3];

    Hydrospawn(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		     spells[0].info = dbcSpell.LookupEntry(22419);
		     spells[0].cooldown = 10;
		     spells[0].targettype = TARGET_ATTACKING;
		     spells[0].instant = true;
		     spells[0].perctrigger = (float)RandomFloat(20.0f);
		     spells[0].attackstoptimer = 3000;
		     m_spellcheck[0] = true;


		     spells[1].info = dbcSpell.LookupEntry(22420);
		     spells[1].cooldown = 10;
		     spells[1].targettype = TARGET_ATTACKING;
		     spells[1].instant = true;
		     spells[1].perctrigger = (float)RandomFloat(20.0f);
		     spells[1].attackstoptimer = 3000;
		     m_spellcheck[1] = true;


		     spells[2].info = dbcSpell.LookupEntry(22421);
		     spells[2].cooldown = 10;
		     spells[2].targettype = TARGET_ATTACKING;
		     spells[2].instant = true;
		     spells[2].perctrigger = (float)RandomFloat(20.0f);
		     spells[2].attackstoptimer = 3000;
		     m_spellcheck[2] = true;

  }
    
    void OnCombatStart(UnitPointer mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(UnitPointer mTarget)
    {
    }

    void OnCombatStop(UnitPointer mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    UnitPointer target = NULLUNIT;
			for(int i=0;i<nrspells;i++)
			{
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

	void Destroy()
	{
		delete this;
	};

protected:

	int nrspells;
};



class MassiveGeyser : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(MassiveGeyser);
	SP_AI_Spell spells[1];
 bool m_spellcheck[1];

    MassiveGeyser(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		     spells[0].info = dbcSpell.LookupEntry(22422);
		     spells[0].cooldown = 10;
		     spells[0].targettype = TARGET_ATTACKING;
		     spells[0].instant = true;
		     spells[0].perctrigger = (float)RandomFloat(20.0f);
		     spells[0].attackstoptimer = 3000;
		     m_spellcheck[0] = true;

  }
    
    void OnCombatStart(UnitPointer mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(UnitPointer mTarget)
    {
    }

    void OnCombatStop(UnitPointer mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    UnitPointer target = NULLUNIT;
			for(int i=0;i<nrspells;i++)
			{
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

	void Destroy()
	{
		delete this;
	};

protected:

	int nrspells;
};



class IllyanaRavenoak : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(IllyanaRavenoak);
	SP_AI_Spell spells[4];
 bool m_spellcheck[4];

    IllyanaRavenoak(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 4;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		     spells[0].info = dbcSpell.LookupEntry(5116);
		     spells[0].cooldown = 10;
		     spells[0].targettype = TARGET_ATTACKING;
		     spells[0].instant = true;
		     spells[0].perctrigger = (float)RandomFloat(20.0f);
		     spells[0].attackstoptimer = 3000;
		     m_spellcheck[0] = true;


		     spells[1].info = dbcSpell.LookupEntry(20904);
		     spells[1].cooldown = 10;
		     spells[1].targettype = TARGET_ATTACKING;
		     spells[1].instant = true;
		     spells[1].perctrigger = (float)RandomFloat(20.0f);
		     spells[1].attackstoptimer = 3000;
		     m_spellcheck[1] = true;


		     spells[2].info = dbcSpell.LookupEntry(14290);
		     spells[2].cooldown = 10;
		     spells[2].targettype = TARGET_ATTACKING;
		     spells[2].instant = true;
		     spells[2].perctrigger = (float)RandomFloat(20.0f);
		     spells[2].attackstoptimer = 3000;
		     m_spellcheck[2] = true;


		     spells[3].info = dbcSpell.LookupEntry(14295);
		     spells[3].cooldown = 10;
		     spells[3].targettype = TARGET_ATTACKING;
		     spells[3].instant = true;
		     spells[3].perctrigger = (float)RandomFloat(20.0f);
		     spells[3].attackstoptimer = 3000;
		     m_spellcheck[3] = true;

  }
    
    void OnCombatStart(UnitPointer mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(UnitPointer mTarget)
    {
    }

    void OnCombatStop(UnitPointer mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    UnitPointer target = NULLUNIT;
			for(int i=0;i<nrspells;i++)
			{
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

	void Destroy()
	{
		delete this;
	};

protected:

	int nrspells;
};



class Immolthar : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(Immolthar);
	SP_AI_Spell spells[3];
 bool m_spellcheck[3];

    Immolthar(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		     spells[0].info = dbcSpell.LookupEntry(16128);
		     spells[0].cooldown = 10;
		     spells[0].targettype = TARGET_ATTACKING;
		     spells[0].instant = true;
		     spells[0].perctrigger = (float)RandomFloat(20.0f);
		     spells[0].attackstoptimer = 3000;
		     m_spellcheck[0] = true;


		     spells[1].info = dbcSpell.LookupEntry(15550);
		     spells[1].cooldown = 10;
		     spells[1].targettype = TARGET_ATTACKING;
		     spells[1].instant = true;
		     spells[1].perctrigger = (float)RandomFloat(20.0f);
		     spells[1].attackstoptimer = 3000;
		     m_spellcheck[1] = true;


		     spells[2].info = dbcSpell.LookupEntry(22899);
		     spells[2].cooldown = 10;
		     spells[2].targettype = TARGET_ATTACKING;
		     spells[2].instant = true;
		     spells[2].perctrigger = (float)RandomFloat(20.0f);
		     spells[2].attackstoptimer = 3000;
		     m_spellcheck[2] = true;

  }
    
    void OnCombatStart(UnitPointer mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(UnitPointer mTarget)
    {
    }

    void OnCombatStop(UnitPointer mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    UnitPointer target = NULLUNIT;
			for(int i=0;i<nrspells;i++)
			{
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

	void Destroy()
	{
		delete this;
	};

protected:

	int nrspells;
};



class EyeOfImmolThar : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(EyeOfImmolThar);
	SP_AI_Spell spells[1];
 bool m_spellcheck[1];

    EyeOfImmolThar(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		     spells[0].info = dbcSpell.LookupEntry(22909);
		     spells[0].cooldown = 10;
		     spells[0].targettype = TARGET_ATTACKING;
		     spells[0].instant = true;
		     spells[0].perctrigger = (float)RandomFloat(20.0f);
		     spells[0].attackstoptimer = 3000;
		     m_spellcheck[0] = true;

  }
    
    void OnCombatStart(UnitPointer mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(UnitPointer mTarget)
    {
    }

    void OnCombatStop(UnitPointer mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    UnitPointer target = NULLUNIT;
			for(int i=0;i<nrspells;i++)
			{
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

	void Destroy()
	{
		delete this;
	};

protected:

	int nrspells;
};



class KingGordok : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(KingGordok);
	SP_AI_Spell spells[2];
 bool m_spellcheck[2];

    KingGordok(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		     spells[0].info = dbcSpell.LookupEntry(15708);
		     spells[0].cooldown = 10;
		     spells[0].targettype = TARGET_ATTACKING;
		     spells[0].instant = true;
		     spells[0].perctrigger = (float)RandomFloat(20.0f);
		     spells[0].attackstoptimer = 3000;
		     m_spellcheck[0] = true;


		     spells[1].info = dbcSpell.LookupEntry(24375);
		     spells[1].cooldown = 10;
		     spells[1].targettype = TARGET_ATTACKING;
		     spells[1].instant = true;
		     spells[1].perctrigger = (float)RandomFloat(20.0f);
		     spells[1].attackstoptimer = 3000;
		     m_spellcheck[1] = true;

  }
    
    void OnCombatStart(UnitPointer mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(UnitPointer mTarget)
    {
    }

    void OnCombatStop(UnitPointer mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    UnitPointer target = NULLUNIT;
			for(int i=0;i<nrspells;i++)
			{
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

	void Destroy()
	{
		delete this;
	};

protected:

	int nrspells;
};



class Lethtendris : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(Lethtendris);
	SP_AI_Spell spells[2];
 bool m_spellcheck[2];

    Lethtendris(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		     spells[0].info = dbcSpell.LookupEntry(11668);
		     spells[0].cooldown = 10;
		     spells[0].targettype = TARGET_ATTACKING;
		     spells[0].instant = true;
		     spells[0].perctrigger = (float)RandomFloat(20.0f);
		     spells[0].attackstoptimer = 3000;
		     m_spellcheck[0] = true;


		     spells[1].info = dbcSpell.LookupEntry(14887);
		     spells[1].cooldown = 10;
		     spells[1].targettype = TARGET_ATTACKING;
		     spells[1].instant = true;
		     spells[1].perctrigger = (float)RandomFloat(20.0f);
		     spells[1].attackstoptimer = 3000;
		     m_spellcheck[1] = true;

  }
    
    void OnCombatStart(UnitPointer mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(UnitPointer mTarget)
    {
    }

    void OnCombatStop(UnitPointer mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    UnitPointer target = NULLUNIT;
			for(int i=0;i<nrspells;i++)
			{
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

	void Destroy()
	{
		delete this;
	};

protected:

	int nrspells;
};



class LordHelNurath : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(LordHelNurath);
	SP_AI_Spell spells[1];
 bool m_spellcheck[1];

    LordHelNurath(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		     spells[0].info = dbcSpell.LookupEntry(10984);
		     spells[0].cooldown = 10;
		     spells[0].targettype = TARGET_ATTACKING;
		     spells[0].instant = true;
		     spells[0].perctrigger = (float)RandomFloat(20.0f);
		     spells[0].attackstoptimer = 3000;
		     m_spellcheck[0] = true;

  }
    
    void OnCombatStart(UnitPointer mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(UnitPointer mTarget)
    {
    }

    void OnCombatStop(UnitPointer mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    UnitPointer target = NULLUNIT;
			for(int i=0;i<nrspells;i++)
			{
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

	void Destroy()
	{
		delete this;
	};

protected:

	int nrspells;
};



class MagisterKalendris : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(MagisterKalendris);
	SP_AI_Spell spells[3];
 bool m_spellcheck[3];

    MagisterKalendris(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		     spells[0].info = dbcSpell.LookupEntry(10894);
		     spells[0].cooldown = 10;
		     spells[0].targettype = TARGET_ATTACKING;
		     spells[0].instant = true;
		     spells[0].perctrigger = (float)RandomFloat(20.0f);
		     spells[0].attackstoptimer = 3000;
		     m_spellcheck[0] = true;


		     spells[1].info = dbcSpell.LookupEntry(10947);
		     spells[1].cooldown = 10;
		     spells[1].targettype = TARGET_ATTACKING;
		     spells[1].instant = true;
		     spells[1].perctrigger = (float)RandomFloat(20.0f);
		     spells[1].attackstoptimer = 3000;
		     m_spellcheck[1] = true;


		     spells[2].info = dbcSpell.LookupEntry(18807);
		     spells[2].cooldown = 10;
		     spells[2].targettype = TARGET_ATTACKING;
		     spells[2].instant = true;
		     spells[2].perctrigger = (float)RandomFloat(20.0f);
		     spells[2].attackstoptimer = 3000;
		     m_spellcheck[2] = true;

  }
    
    void OnCombatStart(UnitPointer mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(UnitPointer mTarget)
    {
    }

    void OnCombatStop(UnitPointer mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    UnitPointer target = NULLUNIT;
			for(int i=0;i<nrspells;i++)
			{
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

	void Destroy()
	{
		delete this;
	};

protected:

	int nrspells;
};


class PrinceTortheldrin : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(PrinceTortheldrin);
	SP_AI_Spell spells[2];
 bool m_spellcheck[2];

    PrinceTortheldrin(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		     spells[0].info = dbcSpell.LookupEntry(20691);
		     spells[0].cooldown = 10;
		     spells[0].targettype = TARGET_ATTACKING;
		     spells[0].instant = true;
		     spells[0].perctrigger = (float)RandomFloat(20.0f);
		     spells[0].attackstoptimer = 3000;
		     m_spellcheck[0] = true;


		     spells[1].info = dbcSpell.LookupEntry(22920);
		     spells[1].cooldown = 10;
		     spells[1].targettype = TARGET_ATTACKING;
		     spells[1].instant = true;
		     spells[1].perctrigger = (float)RandomFloat(20.0f);
		     spells[1].attackstoptimer = 3000;
		     m_spellcheck[1] = true;

  }
    
    void OnCombatStart(UnitPointer mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(UnitPointer mTarget)
    {
    }

    void OnCombatStop(UnitPointer mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    UnitPointer target = NULLUNIT;
			for(int i=0;i<nrspells;i++)
			{
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

	void Destroy()
	{
		delete this;
	};

protected:

	int nrspells;
};


class Pusillin : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(Pusillin);
	SP_AI_Spell spells[3];
 bool m_spellcheck[3];

    Pusillin(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		     spells[0].info = dbcSpell.LookupEntry(22424);
		     spells[0].cooldown = 10;
		     spells[0].targettype = TARGET_ATTACKING;
		     spells[0].instant = true;
		     spells[0].perctrigger = (float)RandomFloat(20.0f);
		     spells[0].attackstoptimer = 3000;
		     m_spellcheck[0] = true;


		     spells[1].info = dbcSpell.LookupEntry(10151);
		     spells[1].cooldown = 10;
		     spells[1].targettype = TARGET_ATTACKING;
		     spells[1].instant = true;
		     spells[1].perctrigger = (float)RandomFloat(20.0f);
		     spells[1].attackstoptimer = 3000;
		     m_spellcheck[1] = true;


		     spells[2].info = dbcSpell.LookupEntry(16144);
		     spells[2].cooldown = 10;
		     spells[2].targettype = TARGET_ATTACKING;
		     spells[2].instant = true;
		     spells[2].perctrigger = (float)RandomFloat(20.0f);
		     spells[2].attackstoptimer = 3000;
		     m_spellcheck[2] = true;

  }
    
    void OnCombatStart(UnitPointer mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(UnitPointer mTarget)
    {
    }

    void OnCombatStop(UnitPointer mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    UnitPointer target = NULLUNIT;
			for(int i=0;i<nrspells;i++)
			{
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

	void Destroy()
	{
		delete this;
	};

protected:

	int nrspells;
};



class SkarrTheUnbreakable : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(SkarrTheUnbreakable);
	SP_AI_Spell spells[2];
 bool m_spellcheck[2];

    SkarrTheUnbreakable(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		     spells[0].info = dbcSpell.LookupEntry(20691);
		     spells[0].cooldown = 10;
		     spells[0].targettype = TARGET_ATTACKING;
		     spells[0].instant = true;
		     spells[0].perctrigger = (float)RandomFloat(20.0f);
		     spells[0].attackstoptimer = 3000;
		     m_spellcheck[0] = true;


		     spells[1].info = dbcSpell.LookupEntry(24375);
		     spells[1].cooldown = 10;
		     spells[1].targettype = TARGET_ATTACKING;
		     spells[1].instant = true;
		     spells[1].perctrigger = (float)RandomFloat(20.0f);
		     spells[1].attackstoptimer = 3000;
		     m_spellcheck[1] = true;

  }
    
    void OnCombatStart(UnitPointer mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(UnitPointer mTarget)
    {
    }

    void OnCombatStop(UnitPointer mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    UnitPointer target = NULLUNIT;
			for(int i=0;i<nrspells;i++)
			{
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

	void Destroy()
	{
		delete this;
	};

protected:

	int nrspells;
};



class TendrisWarpwood : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(TendrisWarpwood);
	SP_AI_Spell spells[3];
 bool m_spellcheck[3];

    TendrisWarpwood(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		     spells[0].info = dbcSpell.LookupEntry(15550);
		     spells[0].cooldown = 10;
		     spells[0].targettype = TARGET_ATTACKING;
		     spells[0].instant = true;
		     spells[0].perctrigger = (float)RandomFloat(20.0f);
		     spells[0].attackstoptimer = 3000;
		     m_spellcheck[0] = true;


		     spells[1].info = dbcSpell.LookupEntry(22924);
		     spells[1].cooldown = 10;
		     spells[1].targettype = TARGET_ATTACKING;
		     spells[1].instant = true;
		     spells[1].perctrigger = (float)RandomFloat(20.0f);
		     spells[1].attackstoptimer = 3000;
		     m_spellcheck[1] = true;


		     spells[2].info = dbcSpell.LookupEntry(22994);
		     spells[2].cooldown = 10;
		     spells[2].targettype = TARGET_ATTACKING;
		     spells[2].instant = true;
		     spells[2].perctrigger = (float)RandomFloat(20.0f);
		     spells[2].attackstoptimer = 3000;
		     m_spellcheck[2] = true;

  }
    
    void OnCombatStart(UnitPointer mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(UnitPointer mTarget)
    {
    }

    void OnCombatStop(UnitPointer mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();

	   //spawn Ancient Equine Spirit
		_unit->GetMapMgr()->GetInterface()->SpawnCreature(14566, _unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), 0, true, false, 0, 0); 
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    UnitPointer target = NULLUNIT;
			for(int i=0;i<nrspells;i++)
			{
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

	void Destroy()
	{
		delete this;
	};

protected:

	int nrspells;
};



class ZevrimThornhoof : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(ZevrimThornhoof);
	SP_AI_Spell spells[2];
 bool m_spellcheck[2];

    ZevrimThornhoof(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		     spells[0].info = dbcSpell.LookupEntry(22478);
		     spells[0].cooldown = 10;
		     spells[0].targettype = TARGET_ATTACKING;
		     spells[0].instant = true;
		     spells[0].perctrigger = (float)RandomFloat(20.0f);
		     spells[0].attackstoptimer = 3000;
		     m_spellcheck[0] = true;


		     spells[1].info = dbcSpell.LookupEntry(22651);
		     spells[1].cooldown = 10;
		     spells[1].targettype = TARGET_ATTACKING;
		     spells[1].instant = true;
		     spells[1].perctrigger = (float)RandomFloat(20.0f);
		     spells[1].attackstoptimer = 3000;
		     m_spellcheck[1] = true;

  }
    
    void OnCombatStart(UnitPointer mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(UnitPointer mTarget)
    {
    }

    void OnCombatStop(UnitPointer mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    UnitPointer target = NULLUNIT;
			for(int i=0;i<nrspells;i++)
			{
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

	void Destroy()
	{
		delete this;
	};

protected:

	int nrspells;
};



class GordokMageLord : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(GordokMageLord);
	SP_AI_Spell spells[4];
 bool m_spellcheck[4];

    GordokMageLord(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 4;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		     spells[0].info = dbcSpell.LookupEntry(20832);
		     spells[0].cooldown = 10;
		     spells[0].targettype = TARGET_ATTACKING;
		     spells[0].instant = true;
		     spells[0].perctrigger = (float)RandomFloat(20.0f);
		     spells[0].attackstoptimer = 3000;
		     m_spellcheck[0] = true;


		     spells[1].info = dbcSpell.LookupEntry(16102);
		     spells[1].cooldown = 10;
		     spells[1].targettype = TARGET_ATTACKING;
		     spells[1].instant = true;
		     spells[1].perctrigger = (float)RandomFloat(20.0f);
		     spells[1].attackstoptimer = 3000;
		     m_spellcheck[1] = true;


		     spells[2].info = dbcSpell.LookupEntry(15530);
		     spells[2].cooldown = 10;
		     spells[2].targettype = TARGET_ATTACKING;
		     spells[2].instant = true;
		     spells[2].perctrigger = (float)RandomFloat(20.0f);
		     spells[2].attackstoptimer = 3000;
		     m_spellcheck[2] = true;


		     spells[3].info = dbcSpell.LookupEntry(16170);
		     spells[3].cooldown = 10;
		     spells[3].targettype = TARGET_ATTACKING;
		     spells[3].instant = true;
		     spells[3].perctrigger = (float)RandomFloat(20.0f);
		     spells[3].attackstoptimer = 3000;
		     m_spellcheck[3] = true;

  }
    
    void OnCombatStart(UnitPointer mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(UnitPointer mTarget)
    {
    }

    void OnCombatStop(UnitPointer mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    UnitPointer target = NULLUNIT;
			for(int i=0;i<nrspells;i++)
			{
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

	void Destroy()
	{
		delete this;
	};

protected:

	int nrspells;
};



class GordokReaver : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(GordokReaver);
	SP_AI_Spell spells[2];
 bool m_spellcheck[2];

    GordokReaver(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		     spells[0].info = dbcSpell.LookupEntry(22572);
		     spells[0].cooldown = 10;
		     spells[0].targettype = TARGET_ATTACKING;
		     spells[0].instant = true;
		     spells[0].perctrigger = (float)RandomFloat(20.0f);
		     spells[0].attackstoptimer = 3000;
		     m_spellcheck[0] = true;


		     spells[1].info = dbcSpell.LookupEntry(22916);
		     spells[1].cooldown = 10;
		     spells[1].targettype = TARGET_ATTACKING;
		     spells[1].instant = true;
		     spells[1].perctrigger = (float)RandomFloat(20.0f);
		     spells[1].attackstoptimer = 3000;
		     m_spellcheck[1] = true;

  }
    
    void OnCombatStart(UnitPointer mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(UnitPointer mTarget)
    {
    }

    void OnCombatStop(UnitPointer mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    UnitPointer target = NULLUNIT;
			for(int i=0;i<nrspells;i++)
			{
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

	void Destroy()
	{
		delete this;
	};

protected:

	int nrspells;
};



class GordokBrute : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(GordokBrute);
	SP_AI_Spell spells[3];
 bool m_spellcheck[3];

    GordokBrute(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		     spells[0].info = dbcSpell.LookupEntry(13737);
		     spells[0].cooldown = 10;
		     spells[0].targettype = TARGET_ATTACKING;
		     spells[0].instant = true;
		     spells[0].perctrigger = (float)RandomFloat(20.0f);
		     spells[0].attackstoptimer = 3000;
		     m_spellcheck[0] = true;


		     spells[1].info = dbcSpell.LookupEntry(20677);
		     spells[1].cooldown = 10;
		     spells[1].targettype = TARGET_ATTACKING;
		     spells[1].instant = true;
		     spells[1].perctrigger = (float)RandomFloat(20.0f);
		     spells[1].attackstoptimer = 3000;
		     m_spellcheck[1] = true;


		     spells[2].info = dbcSpell.LookupEntry(24317);
		     spells[2].cooldown = 10;
		     spells[2].targettype = TARGET_ATTACKING;
		     spells[2].instant = true;
		     spells[2].perctrigger = (float)RandomFloat(20.0f);
		     spells[2].attackstoptimer = 3000;
		     m_spellcheck[2] = true;

  }
    
    void OnCombatStart(UnitPointer mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(UnitPointer mTarget)
    {
    }

    void OnCombatStop(UnitPointer mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    UnitPointer target = NULLUNIT;
			for(int i=0;i<nrspells;i++)
			{
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

	void Destroy()
	{
		delete this;
	};

protected:

	int nrspells;
};



class FelLash : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(FelLash);
	SP_AI_Spell spells[2];
 bool m_spellcheck[2];

    FelLash(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		     spells[0].info = dbcSpell.LookupEntry(22460);
		     spells[0].cooldown = 10;
		     spells[0].targettype = TARGET_ATTACKING;
		     spells[0].instant = true;
		     spells[0].perctrigger = (float)RandomFloat(20.0f);
		     spells[0].attackstoptimer = 3000;
		     m_spellcheck[0] = true;


		     spells[1].info = dbcSpell.LookupEntry(22272);
		     spells[1].cooldown = 10;
		     spells[1].targettype = TARGET_ATTACKING;
		     spells[1].instant = true;
		     spells[1].perctrigger = (float)RandomFloat(20.0f);
		     spells[1].attackstoptimer = 3000;
		     m_spellcheck[1] = true;

  }
    
    void OnCombatStart(UnitPointer mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(UnitPointer mTarget)
    {
    }

    void OnCombatStop(UnitPointer mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    UnitPointer target = NULLUNIT;
			for(int i=0;i<nrspells;i++)
			{
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

	void Destroy()
	{
		delete this;
	};

protected:

	int nrspells;
};

void SetupDireMaul(ScriptMgr * mgr)
{
//mgr->register_creature_script(11492, &AlzzintheWildshaper::Create); - ai should be added
mgr->register_creature_script(14325, &CaptainKromcrush::Create);
mgr->register_creature_script(14324, &ChoRushTheObserver::Create);
mgr->register_creature_script(14321, &GuardFengus::Create);
mgr->register_creature_script(14326, &GuardMolDar::Create);
mgr->register_creature_script(14323, &GuardSlipKik::Create);
mgr->register_creature_script(13280, &Hydrospawn::Create);
mgr->register_creature_script(14122, &MassiveGeyser::Create);
mgr->register_creature_script(11488, &IllyanaRavenoak::Create);
mgr->register_creature_script(11496, &Immolthar::Create);
mgr->register_creature_script(14396, &EyeOfImmolThar::Create);
mgr->register_creature_script(11501, &KingGordok::Create);
mgr->register_creature_script(14327, &Lethtendris::Create);
mgr->register_creature_script(14506, &LordHelNurath::Create);
mgr->register_creature_script(11487, &MagisterKalendris::Create);
mgr->register_creature_script(11486, &PrinceTortheldrin::Create);
mgr->register_creature_script(14354, &Pusillin::Create);
mgr->register_creature_script(11498, &SkarrTheUnbreakable::Create);
mgr->register_creature_script(11489, &TendrisWarpwood::Create);
mgr->register_creature_script(11490, &ZevrimThornhoof::Create);
mgr->register_creature_script(11444, &GordokMageLord::Create); 
mgr->register_creature_script(11450, &GordokReaver::Create);
mgr->register_creature_script(11441, &GordokBrute::Create);
mgr->register_creature_script(13197, &FelLash::Create);
}