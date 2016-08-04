/*
���: ����������, �������� �� �������, ������� �� ������

	������������ �������:
		stay
		dialog
*/



#define LAI_TYPE_HUBER		"huber"


//�������������
void LAi_type_huber_Init(aref chr)
{
	DeleteAttribute(chr, "location.follower");
	DeleteAttribute(chr, "chr_ai.type");
	chr.chr_ai.type = LAI_TYPE_HUBER;
	LAi_tmpl_stay_InitTemplate(chr);
	//��������� �������� ���������
	LAi_SetHuberSitAnimation(chr);
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
}

//��������������� ���� ���������
void LAi_type_huber_CharacterUpdate(aref chr, float dltTime)
{
	if(chr.chr_ai.tmpl != LAI_TMPL_DIALOG)
	{
		if(rand(1000) == 313)
		{
			LAi_CharacterPlaySound(chr, "governor");
		}
	}
}

//�������� ��������� � �������
bool LAi_type_huber_CharacterLogin(aref chr)
{
	return true;
}

//�������� ��������� �� �������
bool LAi_type_huber_CharacterLogoff(aref chr)
{
	return true;
}

//���������� ������ ���������
void LAi_type_huber_TemplateComplite(aref chr, string tmpl)
{
	LAi_tmpl_player_InitTemplate(chr);
}

//�������� � ������� ������� ������
void LAi_type_huber_NeedDialog(aref chr, aref by)
{
}

//������ �� ������, ���� ���������� true �� � ���� ������ ����� ������ ������
bool LAi_type_huber_CanDialog(aref chr, aref by)
{
	//���� ��� �������, �� �������
	if(chr.chr_ai.tmpl == LAI_TMPL_DIALOG) return false;
	//���������� �� ������
	return true;
}

//������ ������
void LAi_type_huber_StartDialog(aref chr, aref by)
{
	//���� �� �������, ��������� ������ ��� ������� ����������
	LAi_tmpl_stay_InitTemplate(chr);
	LAi_tmpl_SetActivatedDialog(chr, by);
	LAi_tmpl_dialog_NoAni(chr);
}

//��������� ������
void LAi_type_huber_EndDialog(aref chr, aref by)
{
	LAi_tmpl_stay_InitTemplate(chr);
	LAi_SetHuberSitAnimation(chr);
}

//�������� �������� ������� ���������
void LAi_type_huber_Attack(aref attack, aref enemy, float attackDmg, float hitDmg)
{
}

//�������� �������� ������������������ ���������
void LAi_type_huber_Block(aref attack, aref enemy, float attackDmg, float hitDmg)
{
}

//�������� ���������
void LAi_type_huber_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{
}


//�������� ��������
void LAi_type_huber_Attacked(aref chr, aref by)
{
	
}

