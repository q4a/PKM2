


bool wdmDisableRelease = true;

//=========================================================================================
//Events
//=========================================================================================

void wdmEvent_EncounterCreate()
{
	float dltTime = GetEventData();
	float playerShipX = GetEventData();
	float playerShipZ = GetEventData();
	float playerShipAY = GetEventData();
	//Save player ship position
	worldMap.playerShipX = playerShipX;
	worldMap.playerShipZ = playerShipZ;
	worldMap.playerShipAY = playerShipAY;
	if(wdmCurrentIsland !=	WDM_NONE_ISLAND)
	{
		wdmLoginToSea.island = worldMap.islands.(wdmCurrentIsland).name;
		float ix = MakeFloat(worldMap.islands.(wdmCurrentIsland).position.rx);
		float iz = MakeFloat(worldMap.islands.(wdmCurrentIsland).position.rz);
		worldMap.playerShipDispX = (playerShipX - ix);
		worldMap.playerShipDispZ = (playerShipZ - iz);
	}else{
		worldMap.playerShipDispX = 0.0;
		worldMap.playerShipDispZ = 0.0;
	}
	//Skip encounters
	if(CheckAttribute(worldMap, "noenc") != 0)
	{
		if(worldMap.noenc == "true") return;
	}
	//Generate encounters
	wdmStormGen(dltTime, playerShipX, playerShipZ, playerShipAY);
	wdmShipEncounter(dltTime, playerShipX, playerShipZ, playerShipAY);
	wdmQuestShipEncounter(dltTime, playerShipX, playerShipZ, playerShipAY);
}

void wdmEvent_InsideIsland()
{
	wdmDisableTornadoGen = true;
	wdmCurrentIsland = GetEventData();
	//Trace("Inside to "+wdmCurrentIsland);
}

void wdmEvent_OutsideIsland()
{
	wdmCurrentIsland = GetEventData();
	//Trace("Outside from "+wdmCurrentIsland);
	wdmCurrentIsland = WDM_NONE_ISLAND;
}

void wdmEvent_PlayerInStorm()
{
	float playerShipX = GetEventData();
	float playerShipZ = GetEventData();
	float playerShipAY = GetEventData();
	int stormIndex = GetEventData();
	wdmDisableTornadoGen = false;
	wdmReloadToSea();
}

void wdmEvent_ShipEncounter()
{
	wdmDisableTornadoGen = true;
	float playerShipX = GetEventData();
	float playerShipZ = GetEventData();
	float playerShipAY = GetEventData();
	int eshipIndex = GetEventData();
	//Trace("Player ship hit in ship encounter with index " + eshipIndex);
	
	if(CheckAttribute(worldMap, "evwin") != 0)
	{
		if(worldMap.evwin == "true")
		{
			wdmMessage("Sails on horizon!# Pirate ships ahead.", "Engage", "Skip");
			return;
		}
	}
	// boal -->
	LaunchBoalMapScreen();
	//wdmReloadToSea();
	// boal <--

}

void wdmEvent_DeleteShipEncounter()
{
	if(wdmDisableRelease == true)
	{
		int type = GetEventData();
		if(type >= 0) ReleaseMapEncounter(type);
	}
}

void wdmEvent_EventWindowChangeSelectoin()
{
	int select = GetEventData();
}

void wdmEvent_EventWindowSelect()
{
	int result = GetEventData();

	//Trace("Event window select is " + result);

	if(result == 0) wdmReloadToSea();
}

void wdmEvent_WaitMenuChangeSelectoin()
{
	int selectItem = GetEventData();
}

void wdmEvent_WaitMenuSelect()
{
	int selectItem = GetEventData();

	//Trace("Wait menu select is " + selectItem);
}

void wdmEvent_UpdateDate()
{
	Environment.date.day = worldMap.date.day;
	Environment.date.month = worldMap.date.month;	
	Environment.date.year = worldMap.date.year;
	Environment.date.hour = worldMap.date.hour;
	Environment.date.min = worldMap.date.min;
	Environment.date.sec = worldMap.date.sec;
	Environment.time = GetEventData();
}



#event_handler("NextDay", "wdmNextDayUpdate");
void wdmNextDayUpdate()
{
	if(sti(worldMap.date.day) == 7)
	{
		wdmLockReload = true;
		PostEvent("Event_CheckMoneyData", 0);
	}
}


#event_handler("Event_CheckMoneyData", "wdmCheckMoneyData");
void wdmCheckMoneyData()
{
	LaunchSalayScreen();
	wdmLockReload = false;
}

#event_handler("WorldMap_IsSkipEnable", "wdmIsSkipEnable");
bool wdmSkipReturnBool = false;
bool wdmIsSkipEnable()
{
	wdmSkipReturnBool = false;
	if(IsCharacterPerkOn(GetMainCharacter(), "SailingProfessional"))
	{
		if(rand(100) <= 50)
		{
			wdmSkipReturnBool = true;
		}
	}
	return wdmSkipReturnBool;
}
