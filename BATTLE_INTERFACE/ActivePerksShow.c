
object objActivePerkShower;

#event_handler(EVENT_LOCATION_LOAD,"procLoadIntoNew");

void InitActivePerkShower()
{
	objActivePerkShower.ShowParam.PosRect.left		= sti(showWindow.right) - RecalculateHIcon(16+132);
	objActivePerkShower.ShowParam.PosRect.top		= sti(showWindow.top) + RecalculateVIcon(200);
	objActivePerkShower.ShowParam.PosRect.right		= sti(showWindow.right) - RecalculateHIcon(16);
	objActivePerkShower.ShowParam.PosRect.bottom	= sti(showWindow.bottom) - RecalculateVIcon(28);
	objActivePerkShower.ShowParam.IconSize.horz		= RecalculateHIcon(64);
	objActivePerkShower.ShowParam.IconSize.vert		= RecalculateVIcon(64);
	objActivePerkShower.ShowParam.IconSpace.horz	= RecalculateHIcon(4);
	objActivePerkShower.ShowParam.IconSpace.vert	= RecalculateVIcon(4);
}

void procLoadIntoNew()
{
	UnloadActivePerkShower();
	SetEventHandler("frame","LoadActivePerkShower",1);
}

void LoadActivePerkShower()
{
	DelEventHandler("frame","LoadActivePerkShower");

	ref mchref = GetMainCharacter();
	DeleteAttribute(&objActivePerkShower,"PerkList.list");
	DeleteAttribute(&objActivePerkShower,"Textures");

	// ���������� � ���������
	if(bSeaActive && !bAbordageStarted)
	{	// ������� �����
		objActivePerkShower.Textures.t0.file = "battle_interface\sea_abilitys.tga";
		objActivePerkShower.Textures.t0.horz = 8;
		objActivePerkShower.Textures.t0.vert = 2;
		objActivePerkShower.Textures.t1.file = "battle_interface\Sinking.tga";
		objActivePerkShower.Textures.t1.horz = 1;
		objActivePerkShower.Textures.t1.vert = 1;
		objActivePerkShower.Textures.t2.file = "battle_interface\TimeSpeed.tga";
		objActivePerkShower.Textures.t2.horz = 1;
		objActivePerkShower.Textures.t2.vert = 1;
	}
	else
	{	// ������ �����
		objActivePerkShower.Textures.t0.file = "battle_interface\LandCommands.tga";
		objActivePerkShower.Textures.t0.horz = 4;
		objActivePerkShower.Textures.t0.vert = 4;
	}

	aref arPerksRoot,arPerk;
	makearef(arPerksRoot,mchref.perks.list);
	int perksQ = GetAttributesNum(arPerksRoot);

	string stmp;
	int idx = 0;
	for(int j=0; j<perksQ; j++)
	{
		arPerk = GetAttributeN(arPerksRoot,j);
		if( CheckAttribute(arPerk,"delay") )
		{
			if( CheckAttribute(arPerk,"active") )
			{
				AddPerkToActiveList(GetAttributeName(arPerk));
			}
		}
	}

	CreateEntity(&objActivePerkShower,"ActivePerkShower");
	if(bSeaActive && !bAbordageStarted)
	{	// ������� �����
		LayerAddObject(SEA_EXECUTE,&objActivePerkShower,-1);
		LayerAddObject(SEA_REALIZE,&objActivePerkShower,-1);
	}
	else
	{
		LayerAddObject("execute",&objActivePerkShower,-1);
		LayerAddObject("realize",&objActivePerkShower,-1);
	}
}

void UnloadActivePerkShower()
{
	DeleteClass(&objActivePerkShower);
	DeleteAttribute(&objActivePerkShower,"PerkList");
}

bool IsPerkIntoList(string perkID)
{
	return CheckAttribute(&objActivePerkShower,"PerkList.list."+perkID);
}

void AddPerkToActiveList(string perkID)
{
	if( !IsEntity(&objActivePerkShower) ) return;
	aref arRoot,arCur;
	makearef(arRoot,objActivePerkShower.PerkList.list);
	if( CheckAttribute(arRoot,perkID) ) return;

	makearef(arCur,arRoot.(perkID));
	arCur.texture = GetTextureIndex(GetPerkTextureName(perkID));
	arCur.pic_idx = GetPerkPictureIndex(perkID);
	SendMessage(&objActivePerkShower,"lsa",MSG_ACTIVE_PERK_LIST_REFRESH,"add",arCur);
}

int GetPerkPictureIndex(string perkName)
{
	switch(perkName)
	{
	case "Rush":	return 12;	break;

	case "ImmediateReload":	return 10; break;
	case "InstantBoarding":	return 11; break;
	case "Turn180":			return 2; break;
	case "SandbankManeuver":return 3; break;
	case "LightRepair":		return 9; break;
	case "InstantRepair":	return 1; break;
	case "Troopers":		return 8; break;
	case "Brander":			return 0; break;

	case "TimeSpeed":		return 0; break;
	case "Sink":			return 0; break;
	}
	trace("WARNING!!! Perk name - "+perkName+" hav`t picture");
	return 0;
}

string GetPerkTextureName(string perkName)
{
/*	aref arPerkList,arPerk;
	makearef(arPerkList,ChrPerksList.list);
	int i,q;

	q = GetAttributesNum(arPerkList);
	for(i=0; i<q; i++)
	{
		arPerk = GetAttributeN(arPerkList,i);
		if( CheckAttribute()
	}
	return "";
*/
	switch(perkName)
	{
	case "Rush":			return "battle_interface\LandCommands.tga";	break;

	case "ImmediateReload":	return "battle_interface\sea_abilitys.tga"; break;
	case "InstantBoarding":	return "battle_interface\sea_abilitys.tga"; break;
	case "Turn180":			return "battle_interface\sea_abilitys.tga"; break;
	case "SandbankManeuver":return "battle_interface\sea_abilitys.tga"; break;
	case "LightRepair":		return "battle_interface\sea_abilitys.tga"; break;
	case "InstantRepair":	return "battle_interface\sea_abilitys.tga"; break;
	case "Troopers":		return "battle_interface\sea_abilitys.tga"; break;
	case "Brander":			return "battle_interface\sea_abilitys.tga"; break;

	case "TimeSpeed":		return "battle_interface\TimeSpeed.tga"; break;
	case "Sink":			return "battle_interface\Sinking.tga"; break;
	}
	trace("WARNING!!! Perk name - "+perkName+" hav`t texture");
	return "";
}

int GetTextureIndex(string texName)
{
	aref arTexList,arCurTex;
	makearef(arTexList,objActivePerkShower.Textures);
	int i,q;

	q = GetAttributesNum(arTexList);
	for(i=0; i<q; i++)
	{
		arCurTex = GetAttributeN(arTexList,i);
		if(arCurTex.file == texName) return i;
	}
	trace("WARNING!!! Texture name - "+texName+" hav`t describe");
	return -1;
}

void DelPerkFromActiveList(string perkID)
{
	aref arRoot,arCur;
	makearef(arRoot,objActivePerkShower.PerkList.list);
	if( !CheckAttribute(arRoot,perkID) ) return;

	makearef(arCur,arRoot.(perkID));
	SendMessage(&objActivePerkShower,"lsa",MSG_ACTIVE_PERK_LIST_REFRESH,"del",arCur);
	DeleteAttribute(arRoot,perkID);
}
