/*
���: �������

	������������ �������:
		stay
		talk
		fight		
		goto
*/



#define LAI_TYPE_GUARDIAN	"guardian"


//�������������
void LAi_type_guardian_Init(aref chr)
{
	DeleteAttribute(chr, "location.follower");
	bool isNew = false;
	if(CheckAttribute(chr, "chr_ai.type") == false)
	{
		isNew = true;
	}else{
		if(chr.chr_ai.type != LAI_TYPE_GUARDIAN) isNew = true;
	}
	if(isNew == true)
	{
		//����� ���
		DeleteAttribute(chr, "chr_ai.type");
		chr.chr_ai.type = LAI_TYPE_GUARDIAN;
		chr.chr_ai.type.enemy = "";
		chr.chr_ai.type.etime = "0";
		chr.chr_ai.type.wait = "";
		//��������� ������ �������
		LAi_tmpl_stay_InitTemplate(chr);
	}else{
		//�������������� ���������
		if(chr.chr_ai.type.wait == "attack")
		{
			LAi_type_guardian_CmdAttack(chr);
		}else{
			if(chr.chr_ai.type.wait == "return")
			{
				LAi_type_guardian_Return(chr);
			}
		}
	}
	//��������� �������� ���������
	LAi_SetDefaultStayAnimation(chr);
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
	//�������� ����� ��� ����� ������
	chr.chr_ai.type.group = chr.location.group;
	chr.chr_ai.type.locator = chr.location.locator;
}

//��������������� ���� ���������
void LAi_type_guardian_CharacterUpdate(aref chr, float dltTime)
{
	aref type;
	int trg, t;
	float time, dist;
	makearef(type, chr.chr_ai.type);
	//����� ��������
	if(type.wait != "") return;
	//���������� ������
	string tmpl = chr.chr_ai.tmpl;
	if(tmpl == LAI_TMPL_DIALOG) return;
	if(tmpl == LAI_TMPL_FIGHT)
	{
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
		//������� �������� ����������� ����
		time = stf(type.etime) - dltTime;
		if(time <= 0.0)
		{
			type.etime = 0.0;
			t = LAi_group_GetTarget(chr);
			if(t != trg) 
				isValidate = false;
		}else{
			type.etime = time;
		}
		//���� ������� ���� �� �������������, ������� �����
		if(!isValidate)
		{
			//���� ����� ����
			trg = LAi_group_GetTarget(chr);
			if(trg < 0)
			{
				//��������� � ����� ��������
				LAi_tmpl_fight_SetWaitState(chr);
				LAi_type_guardian_Return(chr);
			}else{
				//������������ �� ����� ����
				LAi_type_guardian_CmdAttack_Now(chr, trg);
				if(rand(100) < 20)
				{
					LAi_CharacterPlaySound(chr, "warrior");
				}
			}
		}
	}else{
		if(tmpl == LAI_TMPL_STAY)
		{
			if(rand(1000) == 125)
			{
				LAi_CharacterPlaySound(chr, "guardian");
			}
			//�������� ������� ������
			trg = LAi_group_GetTarget(chr);
			if(trg >= 0)
			{
				chr.chr_ai.type.enemy = trg;
				LAi_type_guardian_CmdAttack(chr);
			}else{
				//��������� ��������� �� ����� ������
				dist = -1.0;
				if(GetCharacterDistByLoc(chr, chr.chr_ai.type.group, chr.chr_ai.type.locator, &dist))
				{
					if(dist > 1.0)
					{
						LAi_tmpl_runto_InitTemplate(chr);
						LAi_tmpl_runto_SetLocator(chr, chr.chr_ai.type.group, chr.chr_ai.type.locator, -1.0);
					}else{
						CharacterTurnByLoc(chr, chr.chr_ai.type.group, chr.chr_ai.type.locator);
					}
				}else{
					CharacterTurnByLoc(chr, chr.chr_ai.type.group, chr.chr_ai.type.locator);
				}
			}
		}else{
			//�������� ������� ������
			trg = LAi_group_GetTarget(chr);
			if(trg >= 0)
			{
				chr.chr_ai.type.enemy = trg;
				LAi_type_guardian_CmdAttack(chr);
			}else{
				if(tmpl != LAI_TMPL_RUNTO)
				{
					LAi_tmpl_stay_InitTemplate(chr);
				}else{
					if(LAi_tmpl_runto_IsStay(chr))
					{
						LAi_tmpl_stay_InitTemplate(chr);
					}
				}
			}
		}
	}
}

//�������� ��������� � �������
bool LAi_type_guardian_CharacterLogin(aref chr)
{
	return true;
}

//�������� ��������� �� �������
bool LAi_type_guardian_CharacterLogoff(aref chr)
{
	return true;
}

//���������� ������ ���������
void LAi_type_guardian_TemplateComplite(aref chr, string tmpl)
{
	LAi_tmpl_stay_InitTemplate(chr);
	CharacterTurnByLoc(chr, chr.chr_ai.type.group, chr.chr_ai.type.locator);
}


//�������� � ������� ������� ������
void LAi_type_guardian_NeedDialog(aref chr, aref by)
{
}

//������ �� ������, ���� ���������� true �� � ���� ������ ����� ������ ������
bool LAi_type_guardian_CanDialog(aref chr, aref by)
{
	//���� ������ �����, �� ���������� �� ������
	if(chr.chr_ai.tmpl == LAI_TMPL_STAY)
	{
		if(LAi_CanNearEnemy(chr, 5.0)) return false;
		return true;
	}
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
void LAi_type_guardian_StartDialog(aref chr, aref by)
{
	//���� �� �������, ��������� ������ ��� ������� ����������
	LAi_CharacterSaveAy(chr);
	CharacterTurnByChr(chr, by);
	LAi_tmpl_SetActivatedDialog(chr, by);
}

//��������� ������
void LAi_type_guardian_EndDialog(aref chr, aref by)
{
	LAi_tmpl_stay_InitTemplate(chr);
	LAi_CharacterRestoreAy(chr);
}

//�������� �������� ������� ���������
void LAi_type_guardian_Attack(aref attack, aref enemy, float attackDmg, float hitDmg)
{
	
}

//�������� �������� ������������������ ���������
void LAi_type_guardian_Block(aref attack, aref enemy, float attackDmg, float hitDmg)
{

}

//�������� ���������
void LAi_type_guardian_Fire(aref chr, aref enemy, float kDist, bool isFindedEnemy)
{

}

//�������� ��������
void LAi_type_guardian_Attacked(aref chr, aref by)
{
	if(chr.chr_ai.tmpl == LAI_TMPL_DIALOG)
	{
		LAi_tmpl_dialog_StopNPC(chr);
	}
}


//------------------------------------------------------------------------------------------
//���������� �������
//------------------------------------------------------------------------------------------

void LAi_type_guardian_CmdAttack(aref chr)
{
	chr.chr_ai.type.wait = "attack";
	PostEvent("Event_type_guardian_Attacked", rand(5)*100, "i", chr);
}

#event_handler("Event_type_guardian_Attacked", "LAi_type_guardian_CmdAttack_Event");
void LAi_type_guardian_CmdAttack_Event()
{
	aref chr = GetEventData();
	if(!TestRef(chr)) return;
	chr.chr_ai.type.wait = "";
	if(chr.chr_ai.type.enemy == "") return;
	int trg = sti(chr.chr_ai.type.enemy);
	LAi_type_guardian_CmdAttack_Now(chr, trg);
}

bool LAi_type_guardian_CmdAttack_Now(aref chr, int trg)
{
	if(trg < 0)
	{
		LAi_tmpl_stay_InitTemplate(chr);
		return false;
	}
	chr.chr_ai.type.etime = 8 + rand(12);
	if(!LAi_tmpl_SetFight(chr, &Characters[trg]))
	{
		//�������� ������������ ������
		LAi_tmpl_stay_InitTemplate(chr);
		return false;
	}
	return true;
}

void LAi_type_guardian_Return(aref chr)
{
	chr.chr_ai.type.wait = "return";
	chr.chr_ai.type.enemy = "";
	PostEvent("Event_type_guardian_Return", rand(10)*100, "i", chr);
}

#event_handler("Event_type_guardian_Return", "LAi_type_guardian_Return_Event");
void LAi_type_guardian_Return_Event()
{
	aref chr = GetEventData();
	if(!TestRef(chr)) return;
	chr.chr_ai.type.wait = "";	
	chr.chr_ai.type.enemy = "";
	LAi_tmpl_runto_InitTemplate(chr);
	LAi_tmpl_runto_SetLocator(chr, chr.chr_ai.type.group, chr.chr_ai.type.locator, -1.0);
}




