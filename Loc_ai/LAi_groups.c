

//������, ����������� ��������� ����� ������ � ������
object LAi_grp_relations;
float LAi_grp_playeralarm = 0;
bool LAi_grp_alarmactive = false;

//------------------------------------------------------------------------------------------
//�������������
//------------------------------------------------------------------------------------------

//�������������
bool LAi_group_Init()
{
	//���� �� ��������
	LAi_grp_playeralarm = 0;
	LAi_grp_alarmactive = false;
	//������ ������ ����� � ��������� ���������
	if(CreateEntity(&LAi_grp_relations, "CharactersGroups") == 0) return false;
	//������������� ����������� ������ ����������
	LAi_group_Register(LAI_DEFAULT_GROUP);
	//������ ������
	LAi_group_Register(LAI_GROUP_PLAYER);
	LAi_group_SetLookRadius(LAI_GROUP_PLAYER, LAI_GROUP_PLA_LOOK);
	LAi_group_SetHearRadius(LAI_GROUP_PLAYER, LAI_GROUP_PLA_HEAR);
	LAi_group_SetSayRadius(LAI_GROUP_PLAYER, LAI_GROUP_PLA_SAY);
	LAi_group_SetPriority(LAI_GROUP_PLAYER, LAI_GROUP_PPLAYER);
	//������ ���������
	LAi_group_Register(LAI_GROUP_GUARDS);
	LAi_group_SetLookRadius(LAI_GROUP_GUARDS, LAI_GROUP_GRD_LOOK);
	LAi_group_SetHearRadius(LAI_GROUP_GUARDS, LAI_GROUP_GRD_HEAR);
	LAi_group_SetSayRadius(LAI_GROUP_GUARDS, LAI_GROUP_GRD_SAY);
	LAi_group_SetPriority(LAI_GROUP_PLAYER, LAI_GROUP_PGUARDS);
	//������ ������
	LAi_group_Register(LAI_GROUP_ACTOR);
	LAi_group_SetLookRadius(LAI_GROUP_GUARDS, LAI_GROUP_ACT_LOOK);
	LAi_group_SetHearRadius(LAI_GROUP_GUARDS, LAI_GROUP_ACT_HEAR);
	LAi_group_SetSayRadius(LAI_GROUP_GUARDS, LAI_GROUP_ACT_SAY);
	LAi_group_SetPriority(LAI_GROUP_PLAYER, LAI_GROUP_PDEFAULT);
	//������ �����������
	LAi_group_Register(LAI_GROUP_HUBER);
	LAi_group_SetLookRadius(LAI_GROUP_GUARDS, LAI_GROUP_HUB_LOOK);
	LAi_group_SetHearRadius(LAI_GROUP_GUARDS, LAI_GROUP_HUB_HEAR);
	LAi_group_SetSayRadius(LAI_GROUP_GUARDS, LAI_GROUP_HUB_SAY);
	LAi_group_SetPriority(LAI_GROUP_PLAYER, LAI_GROUP_PCITIZENS);
	//������ ��������
	LAi_group_Register(LAI_GROUP_MONSTERS);
	LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_SetLookRadius(LAI_GROUP_MONSTERS, LAI_GROUP_MNS_LOOK);
	LAi_group_SetHearRadius(LAI_GROUP_MONSTERS, LAI_GROUP_MNS_HEAR);
	LAi_group_SetSayRadius(LAI_GROUP_MONSTERS, LAI_GROUP_MNS_SAY);
	LAi_group_SetPriority(LAI_GROUP_PLAYER, 0);
	//���������	
	//giards
	LAi_group_SetRelation(LAI_GROUP_GUARDS, LAI_DEFAULT_GROUP, LAI_GROUP_FRIEND);
	LAi_group_SetAlarmReaction(LAI_GROUP_GUARDS, LAI_DEFAULT_GROUP, LAI_GROUP_FRIEND, LAI_GROUP_FRIEND);
	LAi_group_SetRelation(LAI_GROUP_GUARDS, LAI_GROUP_HUBER, LAI_GROUP_FRIEND);
	LAi_group_SetAlarmReaction(LAI_GROUP_GUARDS, LAI_GROUP_HUBER, LAI_GROUP_FRIEND, LAI_GROUP_FRIEND);
	//huber
	LAi_group_SetRelation(LAI_GROUP_HUBER, LAI_DEFAULT_GROUP, LAI_GROUP_FRIEND);
	LAi_group_SetAlarmReaction(LAI_GROUP_HUBER, LAI_DEFAULT_GROUP, LAI_GROUP_FRIEND, LAI_GROUP_FRIEND);
	//actor
	LAi_group_SetRelation(LAI_GROUP_ACTOR, LAI_DEFAULT_GROUP, LAI_GROUP_NEITRAL);
	LAi_group_SetRelation(LAI_GROUP_ACTOR, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	LAi_group_SetRelation(LAI_GROUP_ACTOR, LAI_GROUP_HUBER, LAI_GROUP_NEITRAL);
	LAi_group_SetAlarmReaction(LAI_GROUP_ACTOR, LAI_DEFAULT_GROUP, LAI_GROUP_NEITRAL, LAI_GROUP_NEITRAL);
	LAi_group_SetAlarmReaction(LAI_GROUP_ACTOR, LAI_GROUP_GUARDS, LAI_GROUP_NEITRAL, LAI_GROUP_NEITRAL);
	LAi_group_SetAlarmReaction(LAI_GROUP_ACTOR, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL, LAI_GROUP_NEITRAL);
	LAi_group_SetAlarmReaction(LAI_GROUP_ACTOR, LAI_GROUP_HUBER, LAI_GROUP_NEITRAL, LAI_GROUP_NEITRAL);
	//player
	LAi_group_SetRelation(LAI_GROUP_PLAYER, LAI_DEFAULT_GROUP, LAI_GROUP_NEITRAL);
	LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, LAI_DEFAULT_GROUP, LAI_GROUP_ENEMY, LAI_GROUP_NEITRAL);
	LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, LAI_GROUP_GUARDS, LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
	LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, LAI_GROUP_HUBER, LAI_GROUP_ENEMY, LAI_GROUP_NEITRAL);
	//���������� ���������
	SendMessage(&LAi_grp_relations, "s", "LoadDataRelations");
	//���� ��������� �����
	if(LAi_restoreStates)
	{
		SendMessage(&LAi_grp_relations, "s", "RestoreStates");
	}
	return true;
}

//������������ ��������
void LAi_group_Release()
{
	DeleteAttribute(&LAi_grp_relations, "quests");
	LAi_group_ClearAllTargets();
	SendMessage(&LAi_grp_relations, "s", "SaveData");
	//������� ������ �����
	DeleteClass(&LAi_grp_relations);
}

void LAi_group_SaveInfo()
{
	SendMessage(&LAi_grp_relations, "s", "SaveData");
}

//------------------------------------------------------------------------------------------
//����������� ����� ������, ��������� ����� ����������
//------------------------------------------------------------------------------------------

//����������� ����� ������
void LAi_group_Register(string groupName)
{
	SendMessage(&LAi_grp_relations, "ss", "RegistryGroup", groupName);
	LAi_group_SetLookRadius(groupName, LAI_GROUP_DEF_LOOK);
	LAi_group_SetHearRadius(groupName, LAI_GROUP_DEF_HEAR);
	LAi_group_SetSayRadius(groupName, LAI_GROUP_DEF_SAY);
}

//���������� ��� ������ ������ ���������
void LAi_group_SetLookRadius(string groupName, float radius)
{
	SendMessage(&LAi_grp_relations, "ssf", "SetGroupLook", groupName, radius);
}

//���������� ��� ������ ������ ����������
void LAi_group_SetHearRadius(string groupName, float radius)
{
	SendMessage(&LAi_grp_relations, "ssf", "SetGroupHear", groupName, radius);
}

//���������� ��� ������ ������ ���������
void LAi_group_SetSayRadius(string groupName, float radius)
{
	SendMessage(&LAi_grp_relations, "ssf", "SetGroupSay", groupName, radius);
}

//���������� ��� ������ ���������
void LAi_group_SetPriority(string groupName, int priority)
{
	SendMessage(&LAi_grp_relations, "ssl", "SetGroupPriority", groupName, priority);
}

//���������� ������� ������� 0..1
void LAi_group_SetAlarm(string group1, string group2, float level)
{
	SendMessage(&LAi_grp_relations, "sssf", "SetAlarm", group1, group2, level);
}

//���������� �������� �������� ������� ��/���
void LAi_group_SetAlarmDown(string group1, string group2, float down)
{
	SendMessage(&LAi_grp_relations, "sssf", "SetAlarmDown", group1, group2, down);
}


//------------------------------------------------------------------------------------------
//����������� ��������� � ������
//------------------------------------------------------------------------------------------

//����������� ��������� � ����� ������
void LAi_group_MoveCharacter(aref chr, string groupName)
{
	chr.chr_ai.group = groupName;
	SendMessage(&LAi_grp_relations, "sis", "MoveChr", chr, groupName);	
}

//------------------------------------------------------------------------------------------
//��������� �����
//------------------------------------------------------------------------------------------

//���������� ��������� ����� ��������
void LAi_group_SetRelation(string group1, string group2, string curRelation)
{
	SendMessage(&LAi_grp_relations, "ssss", "SetRelation", group1, group2, curRelation);
}

//���������� ��������� ����� �������� ��� ��������� ������� � �����
void LAi_group_SetAlarmReaction(string group1, string group2, string actRelation, string relRelation)
{
	SendMessage(&LAi_grp_relations, "sssss", "SetAlarmReaction", group1, group2, actRelation, relRelation);
}

//��������� ���� �� ����� 2 ������
void LAi_group_FightGroups(string group1, string group2, bool asignWarriarType)
{
	LAi_group_FightGroupsEx(group1, group2, asignWarriarType, -1, -1, true, false);
}

//��������� ���� �� ����� 2 ������, � ��������� ���������� ����������
void LAi_group_FightGroupsEx(string group1, string group2, bool asignWarriarType, int commander1, int commander2, bool isStay, bool isDialog)
{
	//������ ��� ���������� ���� �������� ����������
	SendMessage(&LAi_grp_relations, "s", "ResetWaveTime");
	//��������� ������ ���� ����������
	if(asignWarriarType)
	{
		ref mchr = GetMainCharacter();
		for(int i = 0; i < LAi_numloginedcharacters; i++)
		{
			int idx = LAi_loginedcharacters[i];
			if(idx >= 0)
			{
				//��������� �������� ��������� ��� �������
				if(idx == GetMainCharacterIndex()) continue;
				for(int j = 1; j < 4; j++)
				{
					if(GetOfficersIndex(mchr, j) == idx) break;
				}
				if(j < 4) continue;
				//��������� ��������� ��������� � ������
				ref chr = &Characters[idx];
				if(CheckAttribute(chr, "chr_ai.group"))
				{
					bool selected = false;
					bool isOne;
					if(chr.chr_ai.group == group1)
					{
						selected = true;
						isOne = true;
					}else{
						if(chr.chr_ai.group == group2)
						{
							selected = true;
							isOne = false;
						}
					}
					if(selected)
					{
						LAi_SetWarriorTypeNoGroup(chr);
						LAi_warrior_SetStay(chr, isStay);
						LAi_warrior_DialogEnable(chr, isDialog);
						if(isOne)
						{
							if(commander1 >= 0)
							{
								LAi_warrior_SetCommander(chr, &Characters[commander1]);
							}
							LAi_group_MoveCharacter(chr, group1);
						}else{
							if(commander2 >= 0)
							{
								LAi_warrior_SetCommander(chr, &Characters[commander2]);
							}
							LAi_group_MoveCharacter(chr, group2);
						}
					}
				}
			}
		}
	}
	//�������� ������
	LAi_group_SetRelation(group1, group2, LAI_GROUP_ENEMY);
	LAi_group_SetHearRadius(group1, 40000000.0);
	LAi_group_SetSayRadius(group1, 40000000.0);
	LAi_group_SetHearRadius(group2, 40000000.0);	
	LAi_group_SetSayRadius(group2, 40000000.0);
}

//------------------------------------------------------------------------------------------
//����
//------------------------------------------------------------------------------------------

//������� ���� ��� ������� ���������
int LAi_group_GetTarget(aref chr)
{
	int index = -1;
	if(SendMessage(&LAi_grp_relations, "sie", "GetTrg", chr, &index) == 0)
	{
		index = -1;
	}
	return index;
}

//��������� ����
bool LAi_group_ValidateTarget(aref chr, aref trg)
{	
	return (SendMessage(&LAi_grp_relations, "sii", "VldTrg", chr, trg) != 0);
}

//���� �� ������ ��������
bool LAi_group_IsEnemy(aref chr, aref trg)
{
	return (SendMessage(&LAi_grp_relations, "sii", "IsEnemy", chr, trg) != 0);
}

//------------------------------------------------------------------------------------------
//������� �� �����
//------------------------------------------------------------------------------------------

//������� ����� �� ����� attack->hit
bool LAi_group_Attack(aref attack, aref hit)
{
	if(attack.chr_ai.group == hit.chr_ai.group)
	{
		//����� ����������
		return false;
	}
	//�������� ���� �� �����
	SendMessage(&LAi_grp_relations, "sss", "Attack", attack.chr_ai.group, hit.chr_ai.group);
	//��������� �����
	SendMessage(&LAi_grp_relations, "siif", "AddTarget", hit, attack, 10.0 + rand(10));
	return true;
}

//�������� ������ ������ ���������
void LAi_group_UpdateTargets(aref chr)
{
	SendMessage(&LAi_grp_relations, "si", "UpdChrTrg", chr);
}

//------------------------------------------------------------------------------------------
//���������
//------------------------------------------------------------------------------------------

//������� ��� ���� �� �������
void LAi_group_ClearAllTargets()
{
	SendMessage(&LAi_grp_relations, "s", "ClearAllTargets");
}

//�������� �������� ������� ��� ������
float LAi_group_GetPlayerAlarm()
{
	return LAi_grp_playeralarm;
}

//������� �� ������� ��� ������
bool LAi_group_IsActivePlayerAlarm()
{
	return LAi_grp_alarmactive;
}

//���������� ����� �� �������� ������
void LAi_group_SetCheck(string groupName, string quest)
{
	//����� ��������� ����
	aref quests;
	makearef(quests, LAi_grp_relations.quests);
	int num = GetAttributesNum(quests);
	string atr = "q";
	for(int i = 0; i < num + 10; i++)
	{
		atr = "q" + i;
		if(!CheckAttribute(quests, atr)) break;
	}
	//��������
	quests.(atr).group = groupName;
	quests.(atr).quest = quest;
}

//���������� ������� �� �������� ������
void LAi_group_SetCheckEvent(string groupName)
{
	//����� ��������� ����
	aref quests;
	makearef(quests, LAi_grp_relations.quests);
	int num = GetAttributesNum(quests);
	string atr = "q";
	for(int i = 0; i < num + 10; i++)
	{
		atr = "q" + i;
		if(!CheckAttribute(quests, atr)) break;
	}
	//��������
	quests.(atr).group = groupName;
}


//������ ����� �� �������� ������
void LAi_group_RemoveCheck(string groupName)
{
	//����� ��������� ����
	aref quests;
	makearef(quests, LAi_grp_relations.quests);
	int num = GetAttributesNum(quests);
	for(int i = 0; i < num; i++)
	{
		aref atr = GetAttributeN(&quests, i);
		if(atr.group == groupName)
		{
			//������
			DeleteAttribute(&quests, GetAttributeName(GetAttributeN(&quests, i)));
			i = -1;
			num = GetAttributesNum(&quests);
		}		
	}
}

//��������� ����� �� �������� ������
void LAi_group_CheckGroupQuest(aref chr)
{
	//������� ����� � ��������
	aref quests;
	makearef(quests, LAi_grp_relations.quests);
	int num = GetAttributesNum(&quests);
	if(num <= 0) return;
	//�������� ��������� ���������� � ������ ������
	if(!CheckAttribute(chr, "chr_ai.group"))
	{
		Trace("CheckGroupQuest: Character <" + chr.id + "> can't have field chr_ai.group");
		return;
	}
	string group = chr.chr_ai.group;
	int chridx = sti(chr.index);
	for(int i = 0; i < LAi_numloginedcharacters; i++)
	{
		int idx = LAi_loginedcharacters[i];
		if(idx >= 0)
		{
			if(idx != chridx)
			{
				ref ch = &Characters[idx];
				if(!CheckAttribute(ch, "chr_ai.group")) ch.chr_ai.group = LAI_DEFAULT_GROUP;
				if(group == ch.chr_ai.group)
				{
					//���� ��� ����� � ���� ������
					return;
				}
			}
		}
	}
	//��������� �� �������...
	for(i = 0; i < num; i++)
	{
		aref atr = GetAttributeN(&quests, i);
		if(atr.group == group)
		{
			//����� �����, �������� ��� �� ����������
			if(CheckAttribute(atr, "quest"))
			{
				LAi_QuestDelay(atr.quest, 0.000001);
			}else{
				PostEvent("LAi_event_GroupKill", 1, "s", group);
			}
			string atname = GetAttributeName(GetAttributeN(&quests, i));
			//������ ������
			DeleteAttribute(&quests, atname);
			i = -1;
			num = GetAttributesNum(&quests);
		}
	}
}


//------------------------------------------------------------------------------------------
//�������� ������� �� �������
//------------------------------------------------------------------------------------------

//���������� ������, ���������� �� ������ �����
#event_handler("CharacterGroup_UpdateAlarm", "LAi_group_UpdateAlarm");
void LAi_group_UpdateAlarm()
{
	LAi_grp_playeralarm = GetEventData();
	LAi_grp_alarmactive = GetEventData();
	Sound_OnAlarm(LAi_grp_alarmactive);
}


