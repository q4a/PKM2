//Monsters, fantoms & encounters


string LAi_monsters_group = "monsters";

void LAi_CreateMonsters(ref location)
{
	//����������� ������ �������� � �������
	if(LAi_LocationIsMonstersGen(location) == false) return;
	//������� � ������ ������ ��������
	if(!LEnc_MonstersLoginStart(location)) return;
	//������� ������ ��� ������ ��������
	string group = "locators." + LAi_monsters_group;
	if(CheckAttribute(location, group) == 0) return;
	//����������� ��������� ���������� ��������
	int maxMonsters = 20 - LAi_numloginedcharacters;
	if(maxMonsters <= 0) return;
	//���������� ��������, ������� ���������
	aref grp;
	makearef(grp, location.(group));
	int num = GetAttributesNum(grp);
	if(num <= 0) return;
	if(maxMonsters > num) maxMonsters = num;
	int locatorPos = 0;
	int loginedMonsters = 0;
	for(int i = 0; i < maxMonsters; i++)
	{
		//���������� ��������� �� �������� �������
		int locnum = (num - locatorPos)/(maxMonsters - loginedMonsters);
		if(locnum < 1) locnum = 1;
		//�������� ������� �� ���������
		locnum = rand(locnum - 1);
		locatorPos = locatorPos + locnum + 1;
		//������� ��������
		aref loc = GetAttributeN(grp, locatorPos - 1);
		float lx = stf(loc.x);
		float ly = stf(loc.y);
		float lz = stf(loc.z);
		if(CheckLocationPosition(loadedLocation, lx, ly, lz))
		{
			if(LAi_MonsterLogin(location, LAi_monsters_group, GetAttributeName(GetAttributeN(grp, i))))
			{
				loginedMonsters = loginedMonsters + 1;
			}
		}
	}
	//������� �� ��������� ������ ��������
	LEnc_MonstersLoginEnd(location);
}

object LAi_MonsterInfo;
bool LAi_MonsterLogin(ref location, string group, string locator)
{
	//�������� ������
	string defModel = "Skel1";
	string defAni = "man";
	LAi_MonsterInfo.model = defModel;
	LAi_MonsterInfo.ani = defAni;
	aref ainfo;
	makearef(ainfo, LAi_MonsterInfo);
	if(!LEnc_MonstersLoginSelectModel(location, ainfo, group, locator)) return false;
	//�������� ��������
	if(!CheckAttribute(LAi_MonsterInfo, "model")) return false;	
	if(LAi_MonsterInfo.model == "") return false;
	if(!CheckAttribute(LAi_MonsterInfo, "ani")) LAi_MonsterInfo.ani = defModel;
	if(LAi_MonsterInfo.ani == "") LAi_MonsterInfo.ani = defModel;
	//������ ������� � ��������� ���� �� ���������
	ref chr = LAi_CreateFantomCharacterEx(LAi_MonsterInfo.model, LAi_MonsterInfo.ani, group, locator);
	LAi_CharacterReincarnationEx(chr, true, true, LAi_monsters_group);
	LAi_SetWarriorType(chr);
	LAi_warrior_SetStay(chr, true);
	LAi_group_MoveCharacter(chr, LAI_GROUP_MONSTERS);
	//��������� �� ������� ���������
	ref mchr = GetMainCharacter();
	//���������� ������� �����
	int hp = 20 + rand(5)*10;
	if(CheckAttribute(mchr, "rank") != 0)
	{
		int rank = sti(mchr.rank);
		if(rank < 1) rank = 1;
		hp = hp*(1.0 + rank*0.1);
	}
	LAi_SetHP(chr, hp, hp);
	//���������� ���� ����������
	if(CheckAttribute(mchr, "skill.Fencing") != 0)
	{
		int flevel = sti(mchr.skill.Fencing);
		if(flevel < 1) flevel = 1;
		if(flevel > 10) flevel = 10;
		flevel = rand(flevel) + 1;
		if(flevel > 10) flevel = 10;
		chr.skill.Fencing = flevel;
	}
	//������������ ���� ��������
	LEnc_MonstersLoginCorrectParams(location, chr, group, locator);
	return true;
}

//������� ������� ����������� �� ��������������� ������� ��������� � ����� ������� ����
void LAi_GenerateFantomFromMe(aref chr)
{
	//��������� ����������� ��������� ������� � ������ �������
	if(!TestRef(loadedLocation)) return;
	if(!IsEntity(loadedLocation)) return;
	if(LAi_LocationIsFantomsGen(loadedLocation) == false) return;
	//��������� ����������� ������������ ���������
	if(LAi_CharacterIsReincarnation(chr) == false) return;
	//��������� ����� �������� ������������ ��� ������������
	bool isGen = LAi_CharacterReincarnationMode(chr);
	if(CheckAttribute(chr, "model") == false) isGen = true;
	if(CheckAttribute(chr, "model.animation") == false) isGen = true;
	if(chr.model == "") isGen = true;
	if(chr.model.animation == "") isGen = true;
	string model, ani;
	if(isGen)
	{
		int nat = GetLocationNation(loadedLocation)
		if(nat < 0) nat = PIRATE;
		if(nat >= MAX_NATIONS) nat = PIRATE;
		if(CheckAttribute(&Nations[nat], "fantomModel") == false)
		{
			Trace("Nation (Nations[" + nat + "]) by name " + Nations[nat].name + " not include fantoms");
			return;
		}
		aref fantoms;
		makearef(fantoms, Nations[nat].fantomModel);
		int num = GetAttributesNum(fantoms);
		if(num <= 0)
		{
			Trace("Nation (Nations[" + nat + "]) by name " + Nations[nat].name + " not include have fantoms");
			return;
		}
		num = rand(num - 1);
		string m = GetAttributeName(GetAttributeN(fantoms, num));
		model = fantoms.(m);
		ani = "man";
		m = m + ".ani";
		if(CheckAttribute(fantoms, m) != false)
		{
			ani = fantoms.(m);
		}
	}else{
		model = chr.model;
		ani = chr.model.animation;
	}
	//��������� ��������� ���������
	object tmp;
	CopyAttributes(&tmp, chr);
	//������ �������	
	ref fnt = LAi_CreateFantomCharacterEx(model, ani, LAi_CharacterReincarnationGroup(chr), "");
	string curidx = fnt.index;
	//������������� ��������� ����������� ���������
	CopyAttributes(fnt, &tmp);
	LAi_SetCurHPMax(fnt);
	if(CheckAttribute(fnt, "chr_ai.group"))
	{
		LAi_group_MoveCharacter(fnt, fnt.chr_ai.group);
	}else{
		LAi_group_MoveCharacter(fnt, "");
	}
	//��������� �������� � ��������
	fnt.model = model;
	fnt.model.animation = ani;
	//�������������� ���
	if(!CheckAttribute(fnt, "chr_ai.type")) fnt.chr_ai.type = "";	
	string chrtype = fnt.chr_ai.type;
	SetRandomNameToCharacter(fnt);
	fnt.id = tmp.id;
	fnt.index = curidx;
	LAi_tmpl_stay_InitTemplate(fnt);
	fnt.chr_ai.type = "";
	if(chrtype != "")
	{
		chrtype = "LAi_type_" + chrtype + "_Init";
		call chrtype(fnt);
	}
}

bool LAi_CreateEncounters(ref location)
{
	bool retValue = false;
	string encGroup, str;
	aref grp;
	int num = 0;
	for(int i = 0; i < 5; i++)
	{
		//�������� ������ ���������
		encGroup = LAi_FindRandomLocator("encdetector");
		if(encGroup == "") return retValue;
		//��������� �� �������������
		if(CheckAttribute(location, "locators." + encGroup))
		{
			//�������� �� ���������� ����������
			str = "locators." + encGroup;
			makearef(grp, location.(str));
			num = GetAttributesNum(grp);			
			if(num > 0) break;
		}
	}
	if(num <= 0) return retValue;
	//����������� ��������� ���������� ���������� � ����������
	int maxChr = 16 - LAi_numloginedcharacters;
	if(maxChr <= 0) return retValue;
	if(maxChr > num) maxChr = num;
	//���� ������ ������� ������� �����������
	if(!LEnc_LoginStart(location, "encdetector", encGroup, maxChr)) return retValue;
	//�������� ���������� �������� � �������� ��������
	for(i = 0; i < maxChr; i++)
	{
		//������� ������� ��� ������
		string locator = GetAttributeName(GetAttributeN(grp, i));
		//�������� ������
		string defModel = "man1";
		string defAni = "man";
		LAi_MonsterInfo.model = defModel;
		LAi_MonsterInfo.ani = defAni;
		aref ainfo;
		makearef(ainfo, LAi_MonsterInfo);
		LEnc_LoginSelectModel(location, ainfo, encGroup, locator);
		//�������� ��������
		if(!CheckAttribute(LAi_MonsterInfo, "model")) break;
		if(LAi_MonsterInfo.model == "") break;
		if(!CheckAttribute(LAi_MonsterInfo, "ani")) LAi_MonsterInfo.ani = defModel;
		if(LAi_MonsterInfo.ani == "") LAi_MonsterInfo.ani = defModel;
		//������ �������
		ref chr = LAi_CreateFantomCharacterEx(LAi_MonsterInfo.model, LAi_MonsterInfo.ani, encGroup, locator);
		//������������� ���������
		LEnc_LoginCorrectParams(location, chr, encGroup, locator);
		retValue = true;
		//����������� ������
		if(!LEnc_IsContinueLogin(location, chr, encGroup, locator)) break;
	}
	//��������� �������� ���������� � �������
	LEnc_LoginEnd(location, "encdetector", encGroup);
	return retValue;
}



















