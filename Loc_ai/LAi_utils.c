
//�������� ������ �� ���������
bool LAi_CheckCharacter(aref chr, string out)
{
	if(!TestRef(chr))
	{
		Trace("LAi_CheckCharacter -> invalide aref, call from " + out);
		return false;
	};
	if(CheckAttribute(chr, "index") == false)
	{
		Trace(out + " -> invalide character, no field <index>");
		return false;
	}
	if(CheckAttribute(chr, "chr_ai.type") == false)
	{
		Trace(out + " -> invalide character, no field <chr_ai.type>");
		return false;
	}
	if(CheckAttribute(chr, "chr_ai.tmpl") == false)
	{
		Trace(out + " -> invalide character, no field <chr_ai.tmpl>");
		return false;
	}
	return true;
}

//��������� �� �������� � ���������
bool LAi_CharacterCanFrie(aref chr)
{
	if(!CheckAttribute(chr, "chr_ai.chargeprc"))
	{
		chr.chr_ai.chargeprc = "1";
		chr.chr_ai.charge = 0;
		return false;
	}
	if(stf(chr.chr_ai.chargeprc) == 0)
	{
		if(stf(chr.chr_ai.charge) >= 1.0) return true;
	}
	return false;
}

//����� �� ��������� �������� � �������� �������
bool LAi_LocationCanFight()
{
	if(IsEntity(loadedLocation) != true) return true;
	if(CheckAttribute(loadedLocation, "noFight") != true)  return true;
	if(sti(loadedLocation.noFight) != false) return false;
	return true;
}

//����� ��������� ������� � �������� ������ ���������
string LAi_FindRandomLocator(string group)
{
	if(IsEntity(loadedLocation) != true) return "";
	string at = "locators." + group;
	if(CheckAttribute(loadedLocation, at) == 0) return "";
	aref grp;
	makearef(grp, loadedLocation.(at));
	int num = GetAttributesNum(grp);
	if(num <= 0) return "";
	num = rand(num - 1);
	return GetAttributeName(GetAttributeN(grp, num));
}

//����� ������� ������� � �������� ������ ���������
string LAi_FindFarLocator(string group, float x, float y, float z)
{
	if(IsEntity(loadedLocation) != true) return "";
	string at = "locators." + group;
	if(CheckAttribute(loadedLocation, at) == 0) return "";
	aref grp;
	makearef(grp, loadedLocation.(at));
	int num = GetAttributesNum(grp);
	if(num <= 0) return "";
	int j = -1;
	float dist;
	for(int i = 0; i < num; i++)
	{
		aref loc = GetAttributeN(grp, i);
		float dx = x - stf(loc.x);
		float dy = y - stf(loc.y);
		float dz = z - stf(loc.z);
		float d = dx*dx + dy*dy + dz*dz;
		if(j >= 0)
		{
			if(d > dist)
			{
				dist = d;
				j = i;
			}
		}else{
			j = i;
			dist = d;
		}
	}
	if(j < 0) return "";
	return GetAttributeName(GetAttributeN(grp, j));
}

//����� ������� ��������� ������� � �������� ������ ���������
string LAi_FindFarFreeLocator(string group, float x, float y, float z)
{
	if(IsEntity(loadedLocation) != true) return "";
	string at = "locators." + group;
	if(CheckAttribute(loadedLocation, at) == 0) return "";
	aref grp;
	makearef(grp, loadedLocation.(at));
	int num = GetAttributesNum(grp);
	if(num <= 0) return "";
	int j = -1;
	float dist;
	for(int i = 0; i < num; i++)
	{
		aref loc = GetAttributeN(grp, i);
		float lx = stf(loc.x);
		float ly = stf(loc.y);
		float lz = stf(loc.z);
		if(CheckLocationPosition(loadedLocation, lx, ly, lz))
		{
			float dx = x - lx;
			float dy = y - ly;
			float dz = z - lz;
			float d = dx*dx + dy*dy + dz*dz;
			if(j >= 0)
			{
				if(d > dist)
				{
					dist = d;
					j = i;
				}
			}else{
				j = i;
				dist = d;
			}
		}
	}
	if(j < 0) return "";
	return GetAttributeName(GetAttributeN(grp, j));
}

//����� ��������� ��������� �������
string LAi_FindNearestFreeLocator(string group, float x, float y, float z)
{
	if(IsEntity(loadedLocation) != true) return "";
	string at = "locators." + group;
	if(CheckAttribute(loadedLocation, at) == 0) return "";
	aref grp;
	makearef(grp, loadedLocation.(at));
	int num = GetAttributesNum(grp);
	if(num <= 0) return "";
	int j = -1;
	float dist;
	for(int i = 0; i < num; i++)
	{
		aref loc = GetAttributeN(grp, i);
		float lx = stf(loc.x);
		float ly = stf(loc.y);
		float lz = stf(loc.z);
		if(CheckLocationPosition(loadedLocation, lx, ly, lz))
		{
			float dx = x - lx;
			float dy = y - ly;
			float dz = z - lz;
			float d = dx*dx + dy*dy + dz*dz;
			if(j >= 0)
			{
				if(d < dist)
				{
					dist = d;
					j = i;
				}
			}else{
				j = i;
				dist = d;
			}
		}
	}
	if(j < 0) return "";
	return GetAttributeName(GetAttributeN(grp, j));
}

//����� ���������� �������� ��������� � �������� �������
int LAi_FindNearestCharacter(aref chr, float radius)
{
	int res = FindNearCharacters(chr, radius, -1.0, -1.0, 0.01, false, true);
	if(res <= 0) return -1;
	return sti(chrFindNearCharacters[0].index);
}

//����� ���������� �������� ��������� � �������� �������
int LAi_FindNearestVisCharacter(aref chr, float radius)
{
	int res = FindNearCharacters(chr, radius, -1.0, -1.0, 0.01, true, true);
	if(res <= 0) return -1;
	return sti(chrFindNearCharacters[0].index);
}

//�������� ������� ����� ��������� � 0..1
float LAi_GetCharacterFightLevel(aref character)
{
	//Fencing skill
	float fgtlevel = 0.0;
	if(isBoardingLoading == false)
	{
		if(CheckAttribute(character, "skill.Fencing") != 0)
		{
			fgtlevel = stf(character.skill.Fencing);
		}
	}else{
		fgtlevel = GetSummonSkillFromName(character, SKILL_FENCING);
	}
	//Level
	if(fgtlevel < 0.0) fgtlevel = 0.0;
	if(fgtlevel > SKILL_MAX) fgtlevel = SKILL_MAX;
	fgtlevel = fgtlevel/SKILL_MAX;
	return fgtlevel;
}

//��������� ����������� � ���������
void LAi_ApplyCharacterDamage(aref chr, int dmg)
{
	float damage = MakeFloat(dmg);
	//�������� ��������� �����������
	if(CheckAttribute(chr, "chr_ai.type"))
	{
		if(chr.chr_ai.type == LAI_TYPE_OFFICER)
		{
			damage = damage*0.7;
		}
	}
	//�������� ������� ���������
	if(!CheckAttribute(chr, "chr_ai.hp")) chr.chr_ai.hp = LAI_DEFAULT_HP;
	if(!CheckAttribute(chr, "chr_ai.hp_max")) chr.chr_ai.hp_max = LAI_DEFAULT_HP_MAX;
	float maxhp = stf(chr.chr_ai.hp_max);
	float hp = stf(chr.chr_ai.hp);
	//�������������
	hp = hp - damage;
	if(hp < 1.0) hp = 0.0;
	chr.chr_ai.hp = hp;
	//�������� �����
	LAi_ProcessCheckMinHP(chr);
	//������� � ��������� �����������
	int chrIndex = sti(chr.index);
	ref mainChr = GetMainCharacter();
	if(sti(mainChr.index) == chrIndex) return;
	for(int i = 1; i < 4; i++)
	{
		if(GetOfficersIndex(mainChr, i) == chrIndex) return;
	}
	SendMessage(chr, "lfff", MSG_CHARACTER_VIEWDAMAGE, dmg, MakeFloat(MakeInt(hp)), MakeFloat(MakeInt(maxhp)));
}

//����� ���������, ���� ����������� hp
void LAi_CheckKillCharacter(aref chr)
{
	if(SendMessage(chr, "ls", MSG_CHARACTER_EX_MSG, "IsDead")) return;
	if(!CheckAttribute(chr, "chr_ai.hp")) chr.chr_ai.hp = 0.0;
	//���������
	if(stf(chr.chr_ai.hp) < 1.0)
	{
		//�������, ���� �������
		if(CheckAttribute(chr, "chr_ai.immortal"))
		{
			if(sti(chr.chr_ai.immortal) != 0)
			{
				chr.chr_ai.hp = 1.0;
				return;
			}
		}
		chr.chr_ai.hp = "0";
		SetCharacterTask_Dead(chr);
		Postevent("EventCharacterDead", 1, "i", chr);
		//�������������� ���������
		if(CheckAttribute(chr, "chr_ai.type"))
		{
			string func = chr.chr_ai.type;
			chr.chr_ai.type = "";
			chr.chr_ai.tmpl = "";
			if(func != "")
			{
				func = "LAi_type_" + func + "_Init";
				call func(chr);
			}
			if(sti(chr.index) == GetMainCharacterIndex())
			{
				//���� ����� ������, �� �������� ���������
				InterfaceStates.Launched = true;
			}
		}
		LAi_Character_Dead_Process(chr);
	}
}

//������� ���������� ���������
ref LAi_CreateFantomCharacter(string model, string group, string locator)
{
	return LAi_CreateFantomCharacterEx(model, "man", group, locator);
}

//������� ���������� ���������
ref LAi_CreateFantomCharacterEx(string model, string ani, string group, string locator)
{
	//���� ��������� ����� ��� ���������
	for(int i = 0; i < 32; i++)
	{
		if(CheckAttribute(&Characters[LOC_FANTOM_CHARACTERS + i], "id") == false) break;
		if(Characters[LOC_FANTOM_CHARACTERS + i].id == "") break;
	}
	if(i >= 32)
	{
		for(i = 0; i < 32; i++)
		{
			if(!IsEntity(&Characters[LOC_FANTOM_CHARACTERS + i])) break;
		}
		if(i >= 32) i = 0;
	}
	ref chr = &Characters[LOC_FANTOM_CHARACTERS + i];
	//��������� ���� ���������
	chr.id = "Location fantom character <" + i + ">";
	chr.index = LOC_FANTOM_CHARACTERS + i;
	//address
	if(IsEntity(loadedLocation) != true)
	{
		chr.location = "none";
	}else{
		chr.location = loadedLocation.id;
	}
	chr.location.group = "";
	chr.location.locator = "";
	chr.location.from_sea = "";
	chr.location.fantom = "1";
	//model
	if(model != "") chr.model = model; else chr.model = "man1";
	chr.model.entity = "NPCharacter";
	chr.model.animation = ani;
	chr.model.height = 1.8;
	chr.FaceId = "0";
	chr.headModel = "h_" + chr.model;
	//game params
	chr.sex = "man";
	chr.skill.Leadership = "1";
	chr.skill.Fencing = "1";
	chr.skill.Sailing = "1";
	chr.skill.Accuracy = "1";
	chr.skill.Cannons = "1";
	chr.skill.Grappling = "1";
	chr.skill.Repair = "1";
	chr.skill.Defence = "1";
	chr.skill.Commerce = "1";
	chr.skill.Sneak = "1";
	chr.money = 100 + rand(500);
	chr.reputation = 20 + rand(70);
	chr.rank = 1;
	chr.skill.freeskill = 0;
	chr.experience = 0;
	chr.luck = 4;
	chr.spyglass.itemID = COMMON_SPYGLASS;
	//Quest data
	chr.Dialog.CurrentNode = "First time";
	chr.Dialog.TempNode = chr.Dialog.CurrentNode;
	chr.quest.meeting = "0";
	chr.quest = "True";
	//blade
	GiveItem2Character(chr, BLADE_SABER);
	chr.equip.blade = BLADE_SABER;
	//nation
	int nat = GetLocationNation(loadedLocation);
	if(nat >= 0)
	{
		chr.nation = nat;
	}else{
		chr.nation = GetMainCharacter().nation;
	}
	//name
	SetRandomNameToCharacter(chr);
	//������� ��������� � �������
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	chr.chr_ai.tmpl = LAI_DEFAULT_TEMPLATE;
	chr.chr_ai.group = LAI_DEFAULT_GROUP;
	chr.chr_ai.alarmreact = LAI_DEFAULT_ALARMREACT;
	chr.chr_ai.grpalarmr = LAI_DEFAULT_GRPALARMR;
	chr.chr_ai.hp = LAI_DEFAULT_HP;
	chr.chr_ai.hp_max = LAI_DEFAULT_HP_MAX;
	chr.chr_ai.charge = LAI_DEFAULT_CHARGE;
	if(LAi_numloginedcharacters >= 32)
	{
		Trace("LAi_CreateFantomCharacter -> many logined characters in location (>32)");
		return chr;
	}
	LAi_AddLoginedCharacter(chr);
	if(!CreateCharacter(chr))
	{
		Trace("LAi_CreateFantomCharacter -> CreateCharacter return false");
		return chr;
	}
	//�������� ��������� �� �������
	if(group == "")
	{
		group = "goto";
		locator = "";
	}
	if(locator == "")
	{
		//�������� ������� �������
		float posX, posY, posZ;
		posX = 0.0; posY = 0.0; posZ = 0.0;
		if(GetCharacterPos(GetMainCharacter(), &posX, &posY, &posZ))
		{
			locator = LAi_FindFarFreeLocator(group, posX, posY, posZ);
			if(locator == "")
			{
				locator = LAi_FindFarLocator(group, posX, posY, posZ);
				if(locator == "")
				{
					locator = LAi_FindRandomLocator(group);
				}
			}
		}else{
			locator = LAi_FindRandomLocator(group);
		}
	}
	chr.location.group = group;
	chr.location.locator = locator;
	if(SendMessage(chr, "lss", MSG_CHARACTER_ENTRY_TO_LOCATION, group, locator) == false)
	{
		Trace("LAi_CreateFantomCharacter -> can't teleportation character to <" + group + "::" + locator + ">");
	}
	return chr;
}


object lai_questdelays;
void LAi_QuestDelay(string quest, float delayTime)
{
	int num = GetAttributesNum(&lai_questdelays);
	string atr = "e";
	for(int i = 0; i < num + 10; i++)
	{
		atr = "e" + i;
		if(!CheckAttribute(&lai_questdelays, atr)) break;
	}
	lai_questdelays.(atr) = delayTime;
	lai_questdelays.(atr).quest = quest;
}

void LAi_QuestDelayProcess(float dltTime)
{
	string atr;
	int num = GetAttributesNum(&lai_questdelays);
	//����������� �������
	for(int i = 0; i < num; i++)
	{
		atr = GetAttributeName(GetAttributeN(&lai_questdelays, i));
		lai_questdelays.(atr) = stf(lai_questdelays.(atr)) - dltTime;
	}
	//��������� ���������� � �������� ���������
	for(i = 0; i < num; i++)
	{
		atr = GetAttributeName(GetAttributeN(&lai_questdelays, i));
		if(atr == "root")
		{
			Trace("LAi_QuestDelayProcess -> invalide attibute field: root!!!");
			continue;
		}
		float time = stf(lai_questdelays.(atr));
		if(time > 0)
		{
			lai_questdelays.(atr) = time;
		}else{
			string quest = lai_questdelays.(atr).quest;
			DeleteAttribute(&lai_questdelays, atr);
			CompleteQuestName(quest);
			i = -1;
			num = GetAttributesNum(&lai_questdelays);
		}
	}
}

void LAi_ChangeReputation(aref chr, int repPoints)
{
	if(chr.reputation != "None")
	{
		if(chr.reputation != "")
		{
			int reput = sti(chr.reputation) + repPoints;
			if(reput < REPUTATION_MIN) reput = REPUTATION_MIN;
			if(reput > REPUTATION_MAX) reput = REPUTATION_MAX;
			chr.reputation = reput;
		}
	}

}

void LAi_CheckCharacterID(aref chr)
{
	SendMessage(chr, "ss", "CheckID", chr.id);
}

void LAi_SetDefaultStayAnimation(aref chr)
{
	if(IsEntity(chr))
	{
		BeginChangeCharacterActions(chr);
		SetDefaultStayIdle(chr);
		SetDefaultNormWalk(chr);
		SetDefaultFight(chr);
		SetDefaultDead(chr);
		SetDefaultFightDead(chr);
		EndChangeCharacterActions(chr);
	}
}

void LAi_SetDefaultDead(aref chr)
{
	if(IsEntity(chr))
	{
		BeginChangeCharacterActions(chr);
		SetDefaultDead(chr);
		EndChangeCharacterActions(chr);
	}
}

void LAi_SetAfraidDead(aref chr)
{
	if(IsEntity(chr))
	{
		BeginChangeCharacterActions(chr);
		SetAfraidDead(chr);
		EndChangeCharacterActions(chr);
	}
}

void LAi_SetDefaultSitAnimation(aref chr)
{
	if(IsEntity(chr))
	{
		BeginChangeCharacterActions(chr);
		SetDefaultSitIdle(chr);
		SetDefaultSitDead(chr);
		EndChangeCharacterActions(chr);
	}
}

void LAi_SetHuberSitAnimation(aref chr)
{
	if(IsEntity(chr))
	{
		BeginChangeCharacterActions(chr);
		SetHuberAnimation(chr);		
		EndChangeCharacterActions(chr);
	}
}


//������� ����� � �������, ��������� ����� questFadeOut, ������� �� �������, ��������� ����� questFadeIn
object LAi_QuestFader;
void LAi_Fade(string questFadeOut, string questFadeIn)
{
	if(questFadeOut != "") LAi_QuestDelay(questFadeOut, 0.5);
	if(questFadeIn != "") LAi_QuestDelay(questFadeIn, 1.0);
	
	if(IsEntity(&LAi_QuestFader))
	{
		Trace("LAi_Fade -> previous fade operation not ended!");
		return;
	}
	//Fader
	SetEventHandler("FaderEvent_EndFade", "LAi_FadeEndFadeOut", 0);
	SetEventHandler("FaderEvent_EndFadeIn", "LAi_FadeEndFadeIn", 0);
	CreateEntity(&LAi_QuestFader, "fader");
	SendMessage(&LAi_QuestFader, "lfl", FADER_OUT, 0.5, false);
	LAi_QuestFader.oldSaveState = InterfaceStates.Buttons.Save.enable;
	InterfaceStates.Buttons.Save.enable = 0;
}

void LAi_FadeEndFadeOut()
{
	DelEventHandler("FaderEvent_EndFade", "LAi_FadeEndFadeOut");
	SendMessage(&LAi_QuestFader, "lfl", FADER_IN, 0.5, true);
}

void LAi_FadeEndFadeIn()
{
	DelEventHandler("FaderEvent_EndFadeIn", "LAi_FadeEndFadeIn");
	InterfaceStates.Buttons.Save.enable = LAi_QuestFader.oldSaveState;
}

//���� �� ������ � ���������
bool LAi_IsSetBale(aref chr)
{
	return (SendMessage(chr, "ls", MSG_CHARACTER_EX_MSG, "IsSetBalde") != 0);
}

//� ������ ���
bool LAi_IsFightMode(aref chr)
{
	return (SendMessage(chr, "ls", MSG_CHARACTER_EX_MSG, "IsFightMode") != 0);
}

//���������� ����� ��� ������������� ���������� � ���������
#event_handler("EventWorldMapInit", "LAi_SetRestoreStates");
#event_handler(EVENT_SEA_LOGIN, "LAi_SetRestoreStates");
void LAi_SetRestoreStates()
{
	LAi_restoreStates = true;
}

#event_handler("EventSGMode", "LAi_GetSGMode");
bool globalSGMode = false;
bool LAi_GetSGMode()
{
	return globalSGMode;
}

bool LAi_IsBottleWork(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.hp_bottle"))
	{
		if(stf(chr.chr_ai.hp_bottle) > 0.0) return true;
	}
	return false;
}

//����� � ����� ������
bool LAi_CanNearEnemy(aref chr, float radius)
{
	int num = FindNearCharacters(chr, radius, -1.0, -1.0, 0.001, false, false);
	if(num <= 0) return false;
	for(int i = 0; i < num; i++)
	{
		int idx = sti(chrFindNearCharacters[i].index);
		if(LAi_group_IsEnemy(chr, &Characters[idx])) return true;
	}	
	return false;
}

