/*
���: �������, ������ �����, �������� �� �������, ������� �� ������

	������������ �������:
		stay
		dialog
		goto
*/



#define LAI_TYPE_PATROL		"patrol"


//�������������
void LAi_type_patrol_Init(aref chr)
{
	DeleteAttribute(chr, "location.follower");
	bool isNew = false;
	if(CheckAttribute(chr, "chr_ai.type") == false)
	{
		isNew = true;
	}else{
		if(chr.chr_ai.type != LAI_TYPE_PATROL) isNew = true;
	}
	if(isNew)
	{
		DeleteAttribute(chr, "chr_ai.type");
		chr.chr_ai.type = LAI_TYPE_PATROL;
		chr.chr_ai.type.locator = "";
		chr.chr_ai.type.state = "stay";
		chr.chr_ai.type.time = rand(5);
		chr.chr_ai.type.player = "0";
		LAi_tmpl_stay_InitTemplate(chr);
	}else{
		if(!CheckAttribute(chr, "chr_ai.type.locator")) chr.chr_ai.type.locator = "";
		if(!CheckAttribute(chr, "chr_ai.type.state")) chr.chr_ai.type.state = "stay";
		if(!CheckAttribute(chr, "chr_ai.type.time")) chr.chr_ai.type.time = rand(5);
		if(!CheckAttribute(chr, "chr_ai.type.player")) chr.chr_ai.type.player = "0";
	}
	//��������� �������� ���������
	LAi_SetDefaultStayAnimation(chr);
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
}

//��������������� ���� ���������
void LAi_type_patrol_CharacterUpdate(aref chr, float dltTime)
{
	int trg = -1;
	//���� �������, �� ������ ���� �� ������
	if(chr.chr_ai.tmpl == LAI_TMPL_DIALOG) return;
	if(chr.chr_ai.tmpl != LAI_TMPL_FIGHT)
	{
		//���� ����
		trg = LAi_group_GetTarget(chr);
		if(trg < 0)
		{
			//��������������
			float time = stf(chr.chr_ai.type.player) - dltTime;
			chr.chr_ai.type.player = time;
			if(time <= 0.0)
			{
				//����������� ���������� ����������
				int num = FindNearCharacters(chr, 3.0, -1.0, -1.0, 0.001, true, true);
				if(num > 0)
				{
					for(int i = 0; i < num; i++)
					{
						if(GetMainCharacterIndex() == sti(chrFindNearCharacters[i].index)) break;
					}
					if(i < num)
					{
						//����� �������� ���������
						if(stf(chr.chr_ai.type.player) <= 0.0)
						{
							chr.chr_ai.type.player = 3 + rand(10);
							LAi_type_patrol_TestControl(chr);
							return;
						}
					}else{
						trg = sti(chrFindNearCharacters[0].index);
					}
				}
			}			
			//����������� ��������� ������
			if(chr.chr_ai.tmpl == LAI_TMPL_GOTO)
			{
				if(LAi_tmpl_goto_IsWait(chr))
				{
					if(rand(100) < 20) LAi_type_patrol_Goto(chr);
				}
				return;
			}
			//������ ������
			if(rand(1000) == 125)
			{
				LAi_CharacterPlaySound(chr, "patrol");
			}
			//�����
			time = stf(chr.chr_ai.type.time) - dltTime;
			chr.chr_ai.type.time = time;
			if(time > 0.0)
			{
				if(trg >= 0) CharacterTurnByChr(chr, &Characters[trg]);
				return;
			}else{
				LAi_type_patrol_Goto(chr);
				return;
			}

		}else{
			//�������� �����
			chr.chr_ai.type.state = "fight";
			if(!LAi_tmpl_SetFight(chr, &Characters[trg]))
			{
				//�������� ������������ ������
				LAi_type_patrol_Stay(chr);
			}
		}
	}else{
		//�������� �� ������������ ����
		bool isValidate = false;
		trg = LAi_tmpl_fight_GetTarget(chr);
		if(trg >= 0)
		{
			if(LAi_group_ValidateTarget(chr, &Characters[trg]))
			{
				if(!LAi_tmpl_fight_LostTarget(chr))
				{
					isValidate = true;
				}
			}
		}
		if(!isValidate)
		{
			//���� ����� ����
			trg = LAi_group_GetTarget(chr);
			if(trg >= 0)
			{
				chr.chr_ai.type.state = "fight";
				if(!LAi_tmpl_SetFight(chr, &Characters[trg]))
				{
					//�������� ������������ ������
					LAi_type_patrol_Stay(chr);
				}
			}else{
				LAi_type_patrol_Stay(chr);
			}
		}
	}
}

//�������� ��������� � �������
bool LAi_type_patrol_CharacterLogin(aref chr)
{
	return true;
}

//�������� ��������� �� �������
bool LAi_type_patrol_CharacterLogoff(aref chr)
{
	return true;
}

//���������� ������ ���������
void LAi_type_patrol_TemplateComplite(aref chr, string tmpl)
{
	if(tmpl == "goto")
	{
		LAi_type_patrol_Stay(chr);
		CharacterTurnByLoc(chr, "goto", chr.chr_ai.type.locator);
		chr.chr_ai.type.locator = "";
	}
}

//�������� � ������� ������� ������
void LAi_type_patrol_NeedDialog(aref chr, aref by)
{
}

//������ �� ������, ���� ���������� true �� � ���� ������ ����� ������ ������
bool LAi_type_patrol_CanDialog(aref chr, aref by)
{
	if(chr.chr_ai.type.state == "dialog")
	{
		if(sti(by.index) == GetMainCharacterIndex())
		{
			chr.chr_ai.type.state = "stay";
			return true;
		}
		return false;
	}
	if(LAi_CanNearEnemy(chr, 5.0)) return false;
	if(chr.chr_ai.tmpl == LAI_TMPL_STAY) return true;
	if(chr.chr_ai.tmpl == LAI_TMPL_GOTO) return true;
	if(sti(by.index) == GetMainCharacterIndex())
	{
		if(chr.chr_ai.tmpl == LAI_TMPL_DIALOG)
		{
			if(LAi_tmpl_dialog_StopNPC(chr)) return true;
		}
	}
	return false;
}

//������ ������
void LAi_type_patrol_StartDialog(aref chr, aref by)
{
	//���� �� �������, ��������� ������ ��� ������� ����������
	LAi_CharacterSaveAy(chr);
	CharacterTurnByChr(chr, by);
	LAi_tmpl_SetActivatedDialog(chr, by);
}

//��������� ������
void LAi_type_patrol_EndDialog(aref chr, aref by)
{
	LAi_tmpl_stay_InitTemplate(chr);
	LAi_CharacterRestoreAy(chr);
	bool isSet = false;
	if(chr.chr_ai.type.state == "goto")
	{
		if(chr.chr_ai.type.locator != "")
		{
			LAi_tmpl_goto_InitTemplate(chr);
			LAi_tmpl_goto_SetLocator(chr, "goto", chr.chr_ai.type.locator, -1.0);
			isSet = true;
		}
	}
	if(!isSet)
	{
		LAi_type_patrol_Stay(chr);
	}
}

//�������� �������� ������� ���������
void LAi_type_patrol_Attack(aref attack, aref enemy, float attackDmg, float hitDmg)
{
}

//�������� �������� ������������������ ���������
void LAi_type_patrol_Block(aref attack, aref enemy, float attackDmg, float hitDmg)
{
}

//�������� ���������
void LAi_type_patrol_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{
}


//�������� ��������
void LAi_type_patrol_Attacked(aref chr, aref by)
{
	if(chr.chr_ai.tmpl == LAI_TMPL_DIALOG)
	{
		LAi_tmpl_dialog_StopNPC(chr);
	}	
}

//��������� ��������� � �������� ������������
void LAi_type_patrol_Stay(aref chr)
{
	chr.chr_ai.type.time = 2 + rand(20);
	chr.chr_ai.type.state = "stay";
	LAi_tmpl_stay_InitTemplate(chr);
}

//��������� ��������� � ����� �����
void LAi_type_patrol_Goto(aref chr)
{
	//��� � ����� �����
	string newloc = LAi_FindRandomLocator("goto");
	if(newloc != "")
	{
		LAi_tmpl_goto_InitTemplate(chr);
		LAi_tmpl_goto_SetLocator(chr, "goto", newloc, -1.0);
		chr.chr_ai.type.state = "goto";
		chr.chr_ai.type.locator = newloc;
	}
}

//��������� ��������� � �������� ������������
void LAi_type_patrol_TestControl(aref chr)
{
	//�������� �� ������ �������
	ref mchr = GetMainCharacter();
	float luck = 0.0;
	if(CheckAttribute(mchr, "skill.Sneak"))
	{
		luck = sti(mchr.skill.Sneak)*0.1;
		if(luck < 0.0) luck = 0.0;
		if(luck > 1.0) luck = 1.0;
	}
	luck = 80.0 + luck*20.0;
	if(rand(100) <= luck) return;
	//�������� ������ ������
	if(LAi_Character_CanDialog(chr, mchr))
	{
		chr.chr_ai.type.state = "dialog";
		LAi_tmpl_SetDialog(chr, mchr, -1.0);
		//��������� ��� ����� �������
		chr.chr_ai.type.player = "1000000";
	}
}
