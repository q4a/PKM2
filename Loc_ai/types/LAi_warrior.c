/*
���: ����, ���� ������, ����� ��������, ������������ � ������ ��� �����

	������������ �������:
		fight
		follow
		walk
		stay
		dialog
*/



#define LAI_TYPE_WARRIOR	"warrior"



//���������� ����� ���������
void LAi_warrior_SetCommander(aref chr, aref commander)
{
	chr.chr_ai.type.index = commander.index;
}

//��������� ��� ��������� ������� ��� �����
void LAi_warrior_DialogEnable(aref chr, bool isEnable)
{
	chr.chr_ai.type.dialog = isEnable;
}

//������� ����� ������ ��� ���������� �����
void LAi_warrior_SetStay(aref chr, bool isStay)
{
	chr.chr_ai.type.stay = isStay;
}

//�������������
void LAi_type_warrior_Init(aref chr)
{
	DeleteAttribute(chr, "location.follower");
	bool isNew = false;
	if(CheckAttribute(chr, "chr_ai.type") == false)
	{
		isNew = true;
	}else{
		if(chr.chr_ai.type != LAI_TYPE_WARRIOR) isNew = true;
	}
	if(isNew == true)
	{
		//����� ���
		DeleteAttribute(chr, "chr_ai.type");
		chr.chr_ai.type = LAI_TYPE_WARRIOR;
		chr.chr_ai.type.stay = "0";
		chr.chr_ai.type.index = "";
		chr.chr_ai.type.dialog = "0";
		LAi_tmpl_stay_InitTemplate(chr);
	}else{
		if(!CheckAttribute(chr, "chr_ai.type.stay")) chr.chr_ai.type.stay = "0";
		if(!CheckAttribute(chr, "chr_ai.type.index")) chr.chr_ai.type.index = "";
		if(!CheckAttribute(chr, "chr_ai.type.dialog")) chr.chr_ai.type.dialog = "0";
	}
	//��������� �������� ���������
	LAi_SetDefaultStayAnimation(chr);
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
}

//��������������� ���� ���������
void LAi_type_warrior_CharacterUpdate(aref chr, float dltTime)
{
	int trg = -1;
	//������ �� ����� � �����������
	aref type;
	makearef(type, chr.chr_ai.type);
	//����������� ���������
	if(chr.chr_ai.tmpl == LAI_TMPL_FIGHT)
	{
		//�����
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
			if(trg < 0)
			{
				//��������� � ����� ��������
				LAi_tmpl_stay_InitTemplate(chr);
				LAi_type_warrior_SetWateState(chr);
			}else{
				//������������ �� ����� ����
				LAi_tmpl_SetFight(chr, &Characters[trg]);
				if(rand(100) < 20)
				{
					LAi_type_warrior_PlaySound(chr);
				}
			}
		}
	}else{
		//���� ����� ����
		trg = LAi_group_GetTarget(chr);
		if(trg >= 0)
		{
			//�������� �� ����� ����
			LAi_tmpl_SetFight(chr, &Characters[trg]);
			if(rand(100) < 70)
			{
				LAi_type_warrior_PlaySound(chr);
			}
		}else{
			if(chr.chr_ai.tmpl == LAI_TMPL_STAY)
			{
				//����� � ��� ����
				LAi_type_warrior_SetWateState(chr);
			}

		}
	}	
}

//�������� ��������� � �������
bool LAi_type_warrior_CharacterLogin(aref chr)
{
	return true;
}

//�������� ��������� �� �������
bool LAi_type_warrior_CharacterLogoff(aref chr)
{
	return true;
}

//���������� ������ ���������
void LAi_type_warrior_TemplateComplite(aref chr, string tmpl)
{
}

//�������� � ������� ������� ������
void LAi_type_warrior_NeedDialog(aref chr, aref by)
{
}

//������ �� ������, ���� ���������� true �� � ���� ������ ����� ������ ������
bool LAi_type_warrior_CanDialog(aref chr, aref by)
{	
	if(sti(chr.chr_ai.type.dialog) == 0) return false;
	//���� ������ �����, �� ����������
	if(chr.chr_ai.tmpl == LAI_TMPL_STAY) return true;
	if(chr.chr_ai.tmpl == LAI_TMPL_FOLLOW) return true;
	if(chr.chr_ai.tmpl == LAI_TMPL_WALK) return true;
	return false;
}

//������ ������
void LAi_type_warrior_StartDialog(aref chr, aref by)
{
	//���� �� �������, ��������� ������ ��� ������� ����������
	LAi_CharacterSaveAy(chr);
	CharacterTurnByChr(chr, by);
	LAi_tmpl_SetActivatedDialog(chr, by);
}

//��������� ������
void LAi_type_warrior_EndDialog(aref chr, aref by)
{
	LAi_tmpl_stay_InitTemplate(chr);
	LAi_CharacterRestoreAy(chr);
}

//�������� �������� ������� ���������
void LAi_type_warrior_Attack(aref attack, aref enemy, float attackDmg, float hitDmg)
{
	
}

//�������� �������� ������������������ ���������
void LAi_type_warrior_Block(aref attack, aref enemy, float attackDmg, float hitDmg)
{
	
}

//�������� ���������
void LAi_type_warrior_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{
	
}


//�������� ��������
void LAi_type_warrior_Attacked(aref chr, aref by)
{
	//����� ����������
	if(!LAi_group_IsEnemy(chr, by)) return;
	LAi_group_UpdateTargets(chr);
	bool isChangeTarget = false;
	if(chr.chr_ai.tmpl == LAI_TMPL_FIGHT)
	{
		if(LAi_tmpl_fight_NoActive(chr))
		{
			isChangeTarget = true;
		}
	}else{
		isChangeTarget = true;
	}
	if(isChangeTarget)
	{
		//������ ����
		LAi_tmpl_SetFight(chr, by);
		if(rand(100) < 80)
		{
			LAi_type_warrior_PlaySound(chr);
		}
	}
}

//��������� � ����� ��������
void LAi_type_warrior_SetWateState(aref chr)
{
	if(sti(chr.chr_ai.type.stay) == 0)
	{
		if(chr.chr_ai.type.index != "")
		{
			int cmd = sti(chr.chr_ai.type.index);
			if(cmd >= 0)
			{
				//������������ � ���������
				LAi_tmpl_SetFollow(chr, &Characters[cmd], -1.0);
			}else{
				//������ � ������� ����
				LAi_tmpl_walk_InitTemplate(chr);
			}
		}else{
			//������ � ������� ����
			LAi_tmpl_walk_InitTemplate(chr);
		}
	}else{
		//������� ���� ���� �� �����
		if(chr.chr_ai.tmpl != LAI_TMPL_STAY)
		{
			LAi_tmpl_stay_InitTemplate(chr);
		}
	}
}

void LAi_type_warrior_PlaySound(aref chr)
{
	if(LAi_IsDead(chr)) return;
	string sname = "";
	if(CheckAttribute(chr, "sex"))
	{
		switch(chr.sex)
		{
		case "man":
			sname = "warrior";
			break;
		case "woman":
			break;
		case "skeleton":
			sname = "skeleton";
			break;
		}
	}
	if(sname == "") return;
	LAi_CharacterPlaySound(chr, sname);
}