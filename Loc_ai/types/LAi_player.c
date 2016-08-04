/*
���: �����

	������������ �������:
		player
		dialog
*/



#define LAI_TYPE_PLAYER		"player"


//�������������
void LAi_type_player_Init(aref chr)
{
	DeleteAttribute(chr, "location.follower");
	bool isNew = false;
	if(CheckAttribute(chr, "chr_ai.type") == false)
	{
		isNew = true;
	}else{
		if(chr.chr_ai.type != LAI_TYPE_PLAYER) isNew = true;
	}
	if(isNew == true)
	{
		//����� ���
		DeleteAttribute(chr, "chr_ai.type");
		chr.chr_ai.type = LAI_TYPE_PLAYER;
	}
	//��������� ������ �������
	LAi_tmpl_player_InitTemplate(chr);
	//��������� �������� ���������
	LAi_SetDefaultStayAnimation(chr);
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
	//����� ������� � �������
	chr.chr_ai.type.weapontime = 0;
}

//��������������� ���� ���������
void LAi_type_player_CharacterUpdate(aref chr, float dltTime)
{
	float time;
	if(SendMessage(chr, "ls", MSG_CHARACTER_EX_MSG, "IsActive") != 0)
	{
		chr.chr_ai.type.weapontime = "0";
	}
	if(LAi_group_GetPlayerAlarm())
	{
		chr.chr_ai.type.weapontime = "0";
	}
	if(LAi_IsFightMode(chr))
	{
		time = stf(chr.chr_ai.type.weapontime) + dltTime;
		chr.chr_ai.type.weapontime = time;
		if(time > 300.0)
		{
			chr.chr_ai.type.weapontime = "0";
			SendMessage(chr, "lsl", MSG_CHARACTER_EX_MSG, "ChangeFightMode", false);
		}
	}else{
		chr.chr_ai.type.weapontime = "0";
	}
}

//�������� ��������� � �������
bool LAi_type_player_CharacterLogin(aref chr)
{
	return true;
}

//�������� ��������� �� �������
bool LAi_type_player_CharacterLogoff(aref chr)
{
	return true;
}

//���������� ������ ���������
void LAi_type_player_TemplateComplite(aref chr, string tmpl)
{
	LAi_tmpl_player_InitTemplate(chr);
}

//�������� � ������� ������� ������
void LAi_type_player_NeedDialog(aref chr, aref by)
{
}

//������ �� ������, ���� ���������� true �� � ���� ������ ����� ������ ������
bool LAi_type_player_CanDialog(aref chr, aref by)
{
	//���� ��� �������, �� �������
	if(chr.chr_ai.tmpl == LAI_TMPL_DIALOG) return false;
	//���� ���������, �� �������
	if(SendMessage(chr, "ls", MSG_CHARACTER_EX_MSG, "IsFightMode") != 0) return false;
	//���������� �� ������
	return true;
}

//������ ������
void LAi_type_player_StartDialog(aref chr, aref by)
{
	//���� �� �������, ��������� ������ ��� ������� ����������
	LAi_CharacterSaveAy(chr);
	CharacterTurnByChr(chr, by);
	LAi_tmpl_SetActivatedDialog(chr, by);
}

//��������� ������
void LAi_type_player_EndDialog(aref chr, aref by)
{
	LAi_tmpl_stay_InitTemplate(chr);
	LAi_CharacterRestoreAy(chr);
	LAi_tmpl_player_InitTemplate(chr);
}


//�������� �������� ������� ���������
void LAi_type_player_Attack(aref attack, aref enemy, float attackDmg, float hitDmg)
{

}

//�������� �������� ������������������ ���������
void LAi_type_player_Block(aref attack, aref enemy, float attackDmg, float hitDmg)
{

}

//�������� ���������
void LAi_type_player_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{

}


//�������� ��������
void LAi_type_player_Attacked(aref chr, aref by)
{
	
}
