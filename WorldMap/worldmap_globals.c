


#define WDM_NONE_ISLAND		"open_sea"
#define WDM_MAP_TO_SEA_SCALE	19.607843
#define WDM_MAP_TO_SEA_ENCOUNTERS_SCALE		10.0


#define WDM_ETYPE_MERCHANT	0
#define WDM_ETYPE_FOLLOW	1
#define WDM_ETYPE_WARRING	2


object worldMap;

string wdmCurrentIsland = WDM_NONE_ISLAND;



//=========================================================================================
//Util functions
//=========================================================================================

//Storm functions

int wdmGetNumberStorms()
{
	return MakeInt(worldMap.storm.num);
}

void wdmCreateStorm()
{
	SendMessage(&worldMap, "l", MSG_WORLDMAP_CREATESTORM);
}

//Ship encounter functions

int wdmGetNumberShipEncounters()
{
	return MakeInt(worldMap.encounter.num);
}

bool wdmSetCurrentShipData(int shipIndex)
{
	worldMap.encounter.cur = shipIndex;
	int i = MakeInt(worldMap.encounter.cur);
	if(i < 0 || i != shipIndex) return 0;
	return 1;
}

bool wdmCreateMerchantShip(int type, string islandName, float dltSpeedInPMPercents)
{
	float kSpeed = dltSpeedInPMPercents/100.0;
	if(kSpeed >= 0.0)
	{
		kSpeed = kSpeed + 1.0;
	}else{
		kSpeed = 1.0/(1.0 - kSpeed);
	}
	string nationShipName = wdmEncounterModelName(type);
	return SendMessage(&worldMap, "llssf", MSG_WORLDMAP_CREATEENC_MER, type, nationShipName, islandName, kSpeed);
}

//if islandName == "" then island finding automatically
bool wdmCreateMerchantShipTime(int type, string islandName, float dltSpeedInPMPercents, float liveTime)
{
	float kSpeed = dltSpeedInPMPercents/100.0;
	if(kSpeed >= 0.0)
	{
		kSpeed = kSpeed + 1.0;
	}else{
		kSpeed = 1.0/(1.0 - kSpeed);
	}
	if(liveTime < 1.0) liveTime = 1.0;
	string nationShipName = wdmEncounterModelName(type);
	return SendMessage(&worldMap, "llssff", MSG_WORLDMAP_CREATEENC_MER_TIME, type, nationShipName, islandName, kSpeed, liveTime);
}

bool wdmCreateFollowShip(int type, float dltSpeedInPMPercents)
{
	float kSpeed = dltSpeedInPMPercents/100.0;
	if(kSpeed >= 0.0)
	{
		kSpeed = kSpeed + 1.0;
	}else{
		kSpeed = 1.0/(1.0 - kSpeed);
	}
	string nationShipName = wdmEncounterModelName(type);
	return SendMessage(&worldMap, "llsf", MSG_WORLDMAP_CREATEENC_FLW, type, nationShipName, kSpeed);
}

bool wdmCreateFollowShipTime(int type, float dltSpeedInPMPercents, float liveTime)
{
	float kSpeed = dltSpeedInPMPercents/100.0;
	if(kSpeed >= 0.0)
	{
		kSpeed = kSpeed + 1.0;
	}else{
		kSpeed = 1.0/(1.0 - kSpeed);
	}
	if(liveTime < 1.0) liveTime = 1.0;
	string nationShipName = wdmEncounterModelName(type);
	return SendMessage(&worldMap, "llsff", MSG_WORLDMAP_CREATEENC_FLW_TIME, type, nationShipName, kSpeed, liveTime);
}

bool wdmCreateWarringShips(int type1, int type2)
{
	string nationShipName1 = wdmEncounterModelName(type1);
	string nationShipName2 = wdmEncounterModelName(type2);
	return SendMessage(&worldMap, "llsls", MSG_WORLDMAP_CREATEENC_WAR, type1, nationShipName1, type2, nationShipName2);
}

bool wdmCreateWarringShipsTime(int type1, int type2, float liveTime)
{
	if(liveTime < 1.0) liveTime = 1.0;
	string nationShipName1 = wdmEncounterModelName(type1);
	string nationShipName2 = wdmEncounterModelName(type2);
	return SendMessage(&worldMap, "llslsf", MSG_WORLDMAP_CREATEENC_WAR_TIME, type1, nationShipName1, type2, nationShipName2, liveTime);
}


void wdmReleaseEncounters()
{
	SendMessage(&worldMap, "l", MSG_WORLDMAP_CREATEENC_RELEASE);
}

//Interface

void wdmMessage(string text, string yes, string no)
{
	worldMap.eventWindow.text = text;
	worldMap.eventWindow.yes = yes;
	worldMap.eventWindow.no = no;
	worldMap.eventWindow.update = "";
}

void wdmWaitMenu()
{
	worldMap.waitMenu.update = "";
}

string wdmEncounterModelName(int encIndex)
{
	ref n = GetMapEncounterNationRef(encIndex);
	if(CheckAttribute(n, "worldMapShip") != 0)
	{
		return n.worldMapShip;
	}
	return "ship";	
}
