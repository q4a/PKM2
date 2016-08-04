#include "events.h"
#include "globals.c"
#include "animals.c"
#include "sea_ai\sea.c"
#include "ships\ships.c"
#include "Encounters\Encounters.c"
#include "worldmap\worldmap.c"
#include "locations\locations.c"
#include "Loc_ai\LAi_init.c"
#include "store\goods.h"
#include "cannons\cannons.c"
#include "nations\nations.c"
#include "particles.c"
#include "initinterface.c"
#include "characters\characters.c"
#include "interface\interface.h"
#include "store\storeutilite.c"
#include "dialog.c"
#include "quests\quests.c"
#include "islands\islands.c"
#include "reload.c"
#include "situations.c"
#include "battle_interface\loginterface.c"
#include "calendar.c"
#include "teleport.c"
#include "utils.c"
#include "ITEMS\items.h"
#include "ITEMS\itemLogic.c"
#include "ITEMS\items_utilite.c"
#include "weather\WhrWeather.c"
#include "controls\controls.c"
#include "landencounters\landencounters.c"

extern void wdmInitWorldMap();
extern void InitGoods();
extern void InitStores();
extern void InitItems();
extern void InitCharactersTables();
extern void InitCharactersNames();
extern void CreateCharacters();


native float Bring2RangeNoCheck(float fMin1, float fMax1, float fMin2, float fMax2, float fValue);
native float Bring2Range(float fMin1, float fMax1, float fMin2, float fMax2, float fValue);
native float Degree2Radian(float fDegree);
native float Clampf(float fValue);
native int RDTSC_B();
native int RDTSC_E(int iRDTSC);
#libriary "script_libriary_test"


#event_handler(NEW_GAME_EVENT,"NewGame");
#event_handler(GAME_OVER_EVENT,"GameOverE");
#event_handler("Control Activation","ProcessControls");
#event_handler("MainMenuKey","ProcessMainMenuKey");
#event_handler("InterfaceKey","ProcessInterfaceKey");
#event_handler("CameraPosAng","ProcessCameraPosAng");
#event_handler("Cheat","ProcessCheat");
#event_handler("SeaDogs_ClearSaveData", "ClearLocationsSaveData");

void ProcessCheat()
{
	string sCheatName;
	ref mc;
	sCheatName = GetEventData();
	mc = GetMainCharacter();

	switch(sCheatName)
	{
		case "Immortal":
			if(LAi_IsImmortal(GetMainCharacter()))
			{				
				LAi_SetImmortal(GetMainCharacter(), false);
				Log_SetStringToLog("God mode OFF");
			}else{
				
				LAi_SetImmortal(GetMainCharacter(), true);
				Log_SetStringToLog("God mode ON");
			}
		break;
		case "ShotGun":
			if(globalSGMode != false)
			{
				globalSGMode = false;
				Log_SetStringToLog("Shotgun mode OFF");
			}else{
				globalSGMode = true;
				Log_SetStringToLog("Shotgun mode ON");
			}
		break;

		case "Gold":
			mc.money = sti(mc.money) + 100000;
			Log_SetStringToLog(" + 100000 G");
		break;
		case "Skill":
			mc.skill.freeskill = 1;
	
			mc.skill.freeskill = sti(mc.skill.freeskill) + 50;
			Log_SetStringToLog(" + 50 SP");
		break;
		case "Reputation":
			mc.reputation = REPUTATION_NEUTRAL;
			Log_SetStringToLog("Reputation Set to NEUTRAL");
		break;
		case "Morale":

		break;
		case "Encounters":
			if(CheckAttribute(mc,"worldmapencountersoff") == 0)
			{
				mc.worldmapencountersoff = "1";
				Log_SetStringToLog("Worldmap encounters OFF");
			}
			else
			{
				if(mc.worldmapencountersoff == "1") 
				{
					mc.worldmapencountersoff = "0";
					Log_SetStringToLog("Worldmap encounters ON");
				}
				else 
				{
					mc.worldmapencountersoff = "1";
					Log_SetStringToLog("Worldmap encounters OFF");
				}
			}
		break;
		case "MainCharacter":
			mc.model	= "Danielle";
			mc.sex = "woman";
			mc.FaceId = 30;
			mc.model.animation = "woman";
			mc.model.height = 1.75;
		break;
		case "soundoff":
			SendMessage(&Sound,"ll",MSG_SOUND_SET_ENABLED,0);
			Log_SetStringToLog("Sound OFF");
		break;
	}
}

object Camera;

void ProcessCameraPosAng()
{
	Camera.Pos.x = GetEventData();
	Camera.Pos.y = GetEventData();
	Camera.Pos.z = GetEventData();

	Camera.Ang.x = GetEventData();
	Camera.Ang.y = GetEventData();
	Camera.Ang.z = GetEventData();
}

void proc_break_video()
{
	trace("proc_break_video()");
	InterfaceStates.videoIdx = -1;
	Event("ievntEndVideo");
}

void Main()
{
//	LocationTestProcess();
//	return;

	LayerCreate("realize", 1);
	LayerCreate("sea_realize", 1);
	LayerCreate("iRealize", 1);
	LayerCreate("fader_realize", 1);
	LayerCreate("inf_realize", 1);

	ReloadProgressStart();
	ControlsInit(GetTargetPlatform(),true);
	nTeleportLocation = 1;
	sTeleportLocName = "Falaise_de_fleur_port_01";
	sTeleportLocName = "Oxbay_port";

	NationsInit();
	EncountersInit();
	CannonsInit();
	ShipsInit();
	IslandsInit();
	WeatherInit();
	InitPerks();

	if(LoadSegment("store\initGoods.c"))
	{
		InitGoods();
		UnloadSegment("store\initGoods.c");
	}

	if(LoadSegment("Interface\BaseInterface.c"))
	{
		InitBaseInterfaces_main();
		InitBaseInterfaces();
		UnloadSegment("Interface\BaseInterface.c");
	}

	if(LoadSegment("Characters\Characters_names.c"))
	{
		InitCharactersNames();
		UnloadSegment("Characters\Characters_names.c");
	}


	SetEventHandler("Control Activation","proc_break_video",0);
	InterfaceStates.Launched = false;
	SetEventHandler(EVENT_END_VIDEO,"Main_LogoVideo",0);
	InterfaceStates.videoIdx = 0;
	Event(EVENT_END_VIDEO);
	ReloadProgressEnd();
}

void Main_LogoVideo()
{
	
	int i = sti(InterfaceStates.videoIdx);
	trace("Main_LogoVideo() " + i);
	switch(i)
	{
	case 0:
		{
			InterfaceStates.videoIdx = 1;
			StartPostVideo("WaltDisneyLogo",1);
			return;
		}
	break;

	case 1:
		{
			InterfaceStates.videoIdx = 2;
			StartPostVideo("BethesdaLogo",1);
			return;
		}
	break;

	case 2:
		{
			InterfaceStates.videoIdx = 3;
			StartPostVideo("AkellaLogo",1);
			return;
		}
	break;

	/*case 3:
		{
			InterfaceStates.videoIdx = 4;
			StartPostVideo("intro",1);
			return;
		}
	break;*/

	}

	DelEventHandler(EVENT_END_VIDEO,"Main_LogoVideo");
	DeleteClass(&aviVideoObj);
	Event("DoInfoShower","sl","game prepare",true);
	SetEventHandler("frame","Main_Start",1);
}
//*/

void Main_Start()
//void Main()
{
	ReloadProgressStart();


	DelEventHandler("Control Activation","proc_break_video");
	DelEventHandler("frame","Main_Start");

	if( GetTargetPlatform()=="pc" )	ControlsInit(GetTargetPlatform(),false);
/*
	ControlsInit(GetTargetPlatform(),false);

	nTeleportLocation = 1;
	sTeleportLocName = "Falaise_de_fleur_port_01";
	sTeleportLocName = "Oxbay_port";

	NationsInit();
	EncountersInit();
	CannonsInit();
	ShipsInit();
	IslandsInit();
	WeatherInit();
	InitPerks();

	if(LoadSegment("store\initGoods.c"))
	{
		InitGoods();
		UnloadSegment("store\initGoods.c");
	}

	if(LoadSegment("Interface\BaseInterface.c"))
	{
		InitBaseInterfaces_main();
		InitBaseInterfaces();
		UnloadSegment("Interface\BaseInterface.c");
	}

	if(LoadSegment("Characters\Characters_names.c"))
	{
		InitCharactersNames();
		UnloadSegment("Characters\Characters_names.c");
	}

*/	
    
	ReloadProgressUpdate();
	InitGame();
	ReloadProgressUpdate();

	Environment.date.hour = worldMap.date.hour;
	Environment.date.min = worldMap.date.min;
	Environment.date.sec = worldMap.date.sec;
	Environment.time = stf(worldMap.date.hour) + stf(worldMap.date.min)/60.0 + stf(worldMap.date.sec)/3600.0;
	Environment.date.year = worldMap.date.year;
	Environment.date.month = worldMap.date.month;
	Environment.date.day = worldMap.date.day;


	InterfaceStates.Buttons.Load.enable = true;
	
	Event("DoInfoShower","sl","game prepare",false);

	LaunchMainMenu();
	//LaunchLoadGame();

	CharacterIsDead(GetMainCharacter());
	
	//SetMainCharacterIndex(1);
	//LoadMainCharacterInFirstLocation("Oxbay_town", "", "");
	
	ReloadProgressEnd();

}

void SaveGame()
{
	DelEventHandler("evntSave","SaveGame");
	string saveName = GetEventData();
	string saveData = GetEventData();
	SaveEngineState(saveName);
	ISetSaveData(saveName,saveData);
	PostEvent("DoInfoShower",1,"sl","save game",false);
}

void LoadGame()
{
	string saveName = GetEventData();

	DeleteEntities();
	ClearEvents();
	ClearPostEvents();

	CreateEntity(&LanguageObject,"obj_strservice");
	CreateEntity(&reload_fader, "fader");
	if(LanguageGetLanguage()=="English")
	{	SendMessage(&reload_fader, "ls",FADER_PICTURE,"loading\load.tga");
	} else
	{	SendMessage(&reload_fader, "ls",FADER_PICTURE,"loading\load_rus.tga");
	}
	SendMessage(&reload_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
	ReloadProgressStart();
	Characters[0].savegamename = saveName;
	SetEventHandler("frame","LoadGame_continue",1);
}

void LoadGame_continue()
{
	DelEventHandler("frame","LoadGame_continue");
	LoadEngineState(Characters[0].savegamename);
}

void InterfaceDoExit()
{
	DelEventHandler("frame","InterfaceDoExit");
	InterfaceStates.Launched=false;
	if(sti(InterfaceStates.doUnFreeze)==true)
	{
		SendMessage(&GameInterface,"l",MSG_INTERFACE_RELEASE);
		if(!IsEntity(&aviVideoObj))
		{
			if( bSeaActive && !bAbordageStarted )
			{
				LayerFreeze("sea_realize",false);
				LayerFreeze("sea_execute",false);
			}
			else
			{
				LayerFreeze("realize",false);
				LayerFreeze("execute",false);
			}
		}
		DeleteAttribute(&GameInterface,"");
	}
	switch(interfaceResultCommand)
	{
		case RC_INTERFACE_FORTCAPTURE_EXIT:
			ReloadAfterFortCapture();
			break;

		case RC_INTERFACE_DO_NOTHING:
			break;
		case RC_INTERFACE_MAIN_MENU_EXIT:
			break;
		case RC_INTERFACE_DO_NEW_GAME:
			InterfaceStates.doUnFreeze = false;
			DeleteEntities();
			//DeleteSeaEnvironment();
			musicName = "";
			oldMusicName = "";
			ResetSoundScheme();
			StopSound(0,0);
			ReleaseSound(0);
			ClearEvents();
			ClearPostEvents();

			if(LoadSegment("Interface\BaseInterface.c"))
			{
				InitBaseInterfaces_main();
				InitBaseInterfaces();
				UnloadSegment("Interface\BaseInterface.c");
			}

			
			LaunchSelectCharacter();
			
			//SetEventHandler("frame","NewGame",1);
			break;
		case RC_INTERFACE_DO_LOAD_GAME:
			//LoadGame();
			LaunchLoadGame();
			break;
		case RC_INTERFACE_DO_SAVE_GAME:
			LaunchSaveGame();
			break;

		case RC_INTERFACE_DO_OPTIONS:
			LaunchOptionScreen();
			break;
		case RC_INTERFACE_DO_CONTROLS:
			LaunchControlsScreen();
			break;
		case RC_INTERFACE_DO_CREDITS:
			break;
		case RC_INTERFACE_DO_RESUME_GAME:
			break;
		case RC_INTERFACE_RANSACK_MAIN_EXIT:
			Return2SeaAfterAbordage();
			//wdmCreateMap(0.0,0.0,0.0);
			break;
		case RC_INTERFACE_CHARACTER_SELECT_EXIT:
			DeleteEntities();
			ClearEvents();
			SetEventHandler("frame","NewGame",1);
			InterfaceStates.doUnFreeze = false;
			break;
	}
}

void EngineLayersOffOn(bool on)
{
	//LayerSetRealize("realize",on);
	//LayerSetExecute("execute",on);
	on = !on;
	LayerFreeze("realize",on);
	LayerFreeze("execute",on);
	LayerFreeze("sea_realize",on);
	LayerFreeze("sea_execute",on);
	//LayerFreeze("sun_trace",on);
	//LayerFreeze("sea_reflection",on);
	//LayerFreeze("shadow",on);
	//LayerFreeze("ship_cannon_trace",on);
	//LayerFreeze("hull_trace",on);
	//LayerFreeze("mast_ship_trace",on);
	//LayerFreeze("sails_trace",on);
}

string seadogs_saveFrom = "";

void OnSave()
{
	seadogs_saveFrom = "";
	if(IsEntity(&worldMap) != 0)
	{
		seadogs_saveFrom = "world map";
	}else{
		int ldLoc = FindLoadedLocation();
		if(ldLoc >= 0)
		{
			seadogs_saveFrom = "location";
			SendMessage(&Locations[ldLoc], "l", MSG_LOCATION_SETCHRPOSITIONS);
			LAi_SaveInfo();
			PostEvent("SeaDogs_ClearSaveData", 400, "a", &Locations[ldLoc]);
		}else{
			Trace("OnSave() -> unknow character location");
		}
	}

}

void ClearLocationsSaveData()
{
	aref loc = GetEventData();
	SendMessage(loc, "l", MSG_LOCATION_CLRCHRPOSITIONS);
}

int actLoadFlag = 0;
void OnLoad()
{
	actLoadFlag = 1;
	

	//NationsInit();
	ResetSound();

	//CreateClass("dummy");

	if(LoadSegment("Interface\BaseInterface.c"))
	{
		//InitBaseInterfaces_main();
		InitBaseInterfaces();
		UnloadSegment("Interface\BaseInterface.c");
	}
	
	ReloadProgressUpdate();
	
	DialogsInit();
	//IslandsInit();
	//LocationInit();

	ReloadProgressUpdate();

	InitCharacterEvents();
	ReloadProgressUpdate();
	QuestsInit();
	ReloadProgressUpdate();
	InitTeleport();
	ReloadProgressUpdate();
	InitParticles();
	ReloadProgressUpdate();
	//ImportFuncTest();


	InterfaceStates.Buttons.Resume.enable = true;
	InterfaceStates.Buttons.Save.enable = true;
	InterfaceStates.Buttons.Load.enable = true;

	if(seadogs_saveFrom == "location")
	{
		ref mainchar;
		mainchar = GetMainCharacter();
		LoadMainCharacterInFirstLocation(mainchar.location,"", mainchar.location.from_sea);
		//LoadMainCharacterInFirstLocation(sTeleportLocName, "", "Falaise_de_fleur_location_01");
		int ldLoc = FindLoadedLocation();
		if(ldLoc >= 0)
		{
			SendMessage(&Locations[ldLoc], "l", MSG_LOCATION_TLPCHRPOSITIONS);
		}
	}else{
		if(seadogs_saveFrom == "world map")
		{
			wdmLoadSavedMap();
		}else{
			Trace("Unknow seadogs_saveFrom == " + seadogs_saveFrom);
		}
	}

	//ReloadEndFade();
	EngineLayersOffOn(true);
	//NewGame();
	DialogRun = false;
	InterfaceStates.Launched = false;
	
	ReloadProgressUpdate();

	PerkLoad();

	ReloadProgressUpdate();
	LoadGameOptions();

	ReloadProgressEnd();

	actLoadFlag = 0;
}

void NewGame()
{
	DeleteEntities();
	DelEventHandler("frame","NewGame");

	CreateEntity(&LanguageObject,"obj_strservice");
	CreateEntity(&reload_fader, "fader");
	if(LanguageGetLanguage()=="English")
	{	SendMessage(&reload_fader, "ls",FADER_PICTURE,"loading\new_game.tga");
	} else
	{	SendMessage(&reload_fader, "ls",FADER_PICTURE,"loading\new_game_rus.tga");
	}
	SendMessage(&reload_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);

	SetEventHandler("frame","NewGame_continue",1);
}

void NewGame_continue()
{

	ReloadProgressStart();

	DelEventHandler("frame","NewGame_continue");

	if(LoadSegment("Interface\BaseInterface.c"))
	{
		InitBaseInterfaces();
		UnloadSegment("Interface\BaseInterface.c");
	}

	InitGame();
	
	Environment.date.hour = worldMap.date.hour;
	Environment.date.min = worldMap.date.min;
	Environment.date.sec = worldMap.date.sec;
	Environment.time = stf(worldMap.date.hour) + stf(worldMap.date.min)/60.0 + stf(worldMap.date.sec)/3600.0;
	Environment.date.year = worldMap.date.year;
	Environment.date.month = worldMap.date.month;
	Environment.date.day = worldMap.date.day;

	InterfaceStates.Buttons.Resume.enable = true;
	InterfaceStates.Buttons.Save.enable = true;
	InterfaceStates.Buttons.Load.enable = true;
	//PlayMusic("MW battle2.mp3");
	sTeleportLocName = "Tutorial_deck";
	
	ReloadProgressUpdate();

	LoadMainCharacterInFirstLocation(sTeleportLocName, "reload1", "Oxbay_port");

	ReloadProgressEnd();
}

/*
void NewGame()
{
	DeleteEntities();
	Environment.date.hour = 14.0;
	Environment.date.min = 0.0;
	Environment.date.sec = 0.0;
	Environment.time = 14.0;
	Environment.date.year = 1630;
	Environment.date.month = 8;
	Environment.date.day = 15;

	DelEventHandler("frame","NewGame");
	if(LoadSegment("Interface\BaseInterface.c"))
	{
		InitBaseInterfaces();
		UnloadSegment("Interface\BaseInterface.c");
	}
	InitGame();
	
	InterfaceStates.Buttons.Resume.enable = true;
	InterfaceStates.Buttons.Save.enable = true;
	InterfaceStates.Buttons.Load.enable = true;
	//PlayMusic("MW battle2.mp3");
	sTeleportLocName = "Oxbay_port";
	LoadMainCharacterInFirstLocation(sTeleportLocName, "reload2", sTeleportLocName);

}
*/
void InitGame()
{
	LayerCreate("realize", 1);
	LayerCreate("sea_realize", 1);
	LayerCreate("iRealize", 1);
	LayerCreate("fader_realize", 1);
	LayerCreate("inf_realize", 1);
	
	if(LoadSegment("store\initStore.c"))
	{
		InitStores();
		UnloadSegment("store\initStore.c");
	}
	InitSound();

	ReloadProgressUpdate();

	DeleteSeaEnvironment();
	//CharactersInit();
	if(LoadSegment("worldmap\worldmap_init.c"))
	{
		wdmInitWorldMap();
		UnloadSegment("worldmap\worldmap_init.c");
	}
    
	IslandsInit();
	ReloadProgressUpdate();
	//return;
	LocationInit();
	ReloadProgressUpdate();
	DialogsInit();
	ReloadProgressUpdate();
	InitTeleport();
	ReloadProgressUpdate();
	InitParticles();
	ReloadProgressUpdate();

    if(LoadSegment("items\initItems.c"))
	{
		InitItems();
		UnloadSegment("items\initItems.c");
	}

	ReloadProgressUpdate();
	CharactersInit();
	ReloadProgressUpdate();
	QuestsInit();
	ReloadProgressUpdate();
	SeaAIGroupsInit();
	ReloadProgressUpdate();
	InitQuestMapEncounters();
	ReloadProgressUpdate();
	InitLandRandomEncounters();
	ReloadProgressUpdate();

	SetNextWeather("Blue Sky");
	//SetNextWeather("Violet Sky");
	

	ResetQuestMovie();

	ReloadProgressUpdate();
	
	LoadGameOptions();

	ReloadProgressUpdate();
	InfoShowSetting();
}

int counter = 0;
void ProcessControls()
{
	string ControlName;
	ControlName = GetEventData();
	//trace("ProcessControls() : " + ControlName);
	//if (ControlName == "WhrPrevWeather")	{ Whr_LoadNextWeather(-1); }
	//if (ControlName == "WhrNextWeather")	{ Whr_LoadNextWeather(1); }
	//if (ControlName == "WhrUpdateWeather")	{ Whr_UpdateWeather(); }

	if (ControlName == "Help") RunHelpChooser();

	if(bSeaActive && !bAbordageStarted)
	{
		switch(ControlName)
		{
			case "MainMenu": ProcessMainMenuKey();	break;
// boal -->
            case "MainMenuDouble": ProcessMainMenuKey(); break;
// boal <--
			case "Interface": ProcessInterfaceKey();break;

			case "Sea_CameraSwitch": SeaCameras_Switch(); break;
			case "Ship_Fire": Ship_DoFire(); break;

			//case "Tele": Sea_ReloadStart(); break;
		}
	}
	else
	{
		switch(ControlName)
		{
			case "MainMenu": ProcessMainMenuKey();	break;
// boal -->
            case "MainMenuDouble": ProcessMainMenuKey(); break;
// boal <--
			case "Interface": ProcessInterfaceKey();break;
			case "Tele": 
				StartQuickTeleport();
				break;
			case "TeleBack": Teleport(-1); break;
			case "Action":
				//DumpAttributes(loadedLocation/*loadedLocation.reload.reload1.x*/);
				//trace("Y: " + loadedLocation.reload.reload1.y);
				//trace("Z: " + loadedLocation.reload.reload1.z);
			break;
		}
	}


	/*switch(ControlName)
	{
		counter++;
		if(counter > 3) counter = 0;
		case "CameraSwitch": 
			switch(counter)
			{
			case 0: SetDayTime(DAY_TIME_NIGHT); break;
			case 1: SetDayTime(DAY_TIME_MORNING); break;
			case 2: SetDayTime(DAY_TIME_DAY); break;
			case 3: SetDayTime(DAY_TIME_EVENING); break;
			}
		break;
	}*/
// boal -->
    if(ControlName=="TimeScale")
� 	{
� � �		if(IsPerkIntoList("TimeSpeed"))
� � �		{
� � � � 			SetTimeScale(1.0);
� � � � 			DelPerkFromActiveList("TimeSpeed");
� � � � 			TimeScaleCounter = 0; //Tyrus added counter reset
� � �		}
� � �		else
� � �		{
� � � � 			SetTimeScale(GetSeaTimeScale());
� � � � 			Log_SetStringToLog("Time x" + GetSeaTimeScale()); //Tyrus Added message for consistency
� � � � 			AddPerkToActiveList("TimeSpeed");
� � �		}
� 	}
	//Tyrus
� 	if (ControlName=="TimeScaleFaster" || ControlName == "TimeScaleSlower")
� 	{
� � �		if (ControlName == "TimeScaleFaster")
� � �		{TimeScaleCounter++;}
� � �		else
� � �		{TimeScaleCounter--;}

� � �		float newTimeScale = GetSeaTimeScale() + (TimeScaleCounter)*0.25;
� � �		if (newTimeScale < 0) //don't wanna crash the game
� � �		{
� � � � 			TimeScaleCounter++; //so another "slower" key press will not dig us a deeper hole
� � � � 			newTimeScale = 0;
� � �		}
� � �		Log_SetStringToLog("x" + newTimeScale);
� � �		if (TimeScaleCounter == 0) //back to normal
� � �		{
� � � � 			if(IsPerkIntoList("TimeSpeed"))
� � � � 			{
� � � � � �				SetTimeScale(1.0);
� � � � � �				DelPerkFromActiveList("TimeSpeed");
� � � � 			}
� � �		}
� � �		else
� � �		{
� � � � 			SetTimeScale(newTimeScale);
� � � � 			//if perk not in list
� � � � 			if(!IsPerkIntoList("TimeSpeed"))
� � � � 			{AddPerkToActiveList("TimeSpeed");}
� � �		}
� � �
� 	}
    switch(ControlName)
	{
		case "BOAL_Control":
			//Log_SetStringToLog("TestF11");
           /* if(IsPerkIntoList("TimeSpeed"))
� � �		{
� � � � 			SetTimeScale(1.0);
� � � � 			DelPerkFromActiveList("TimeSpeed");
� � � � 			Log_SetStringToLog("Time x1");
� � �		}
� � �		else
� � �		{
� � � � 			SetTimeScale(GetSeaTimeScale());
� � � � 			Log_SetStringToLog("Time x" + GetSeaTimeScale()); 
� � � � 			AddPerkToActiveList("TimeSpeed");
� � �		} */
		break;
        case "BOAL_Control2":
            ref mainCh = GetMainCharacter();
            /*if (mainCh.nation == ENGLAND)
            {
                mainCh.nation = PIRATE;
            }
            else
            {
                mainCh.nation = ENGLAND;
            }*/
            //Log_SetStringToLog("Set Nation to " + mainCh.nation);
            //DeleteAttribute(mainCh, "quest.generate_kill_quest");
            //int num = FindNearCharacters(mainCh, 1, 1, 90, 0.50, true, false);
            // = GetCharacter(num);
            //����� ���������� �������� ��������� � �������� �������
            int res = LAi_FindNearestVisCharacter(mainCh, 20);
            if (res != -1)
            {
                ref findCh = GetCharacter(res);
                res = findCh.chr_ai.hp;
                Log_SetStringToLog("" + findCh.name + " " + findCh.lastname +
                                   " L " + findCh.skill.Leadership +
                                   " F " + findCh.skill.Fencing +
                                   " S " + findCh.skill.Sailing +
                                   " A " + findCh.skill.Accuracy +
                                   " C " + findCh.skill.Cannons +
                                   " G " + findCh.skill.Grappling +
                                   " R " + findCh.skill.Repair +
                                   " D " + findCh.skill.Defence +
                                   " C " + findCh.skill.Commerce +
                                   " L " + findCh.skill.Sneak +
                                   " Rank " + findCh.rank +
                                   " HP "+res );
            }
            // ������� �������� ���� ������!!!!
//            InitGame_boal();
            //Log_SetStringToLog(Characters[0].savegamename);

            // test map enc - mainCh.rank = 11;
// fix mine_kill
/*object refNewAttr;
        string idQuest = "Where_are_i";
		refNewAttr.(idQuest).Complete = false;
        aref refOldAttr; makearef(refOldAttr,mainCh.QuestInfo);
		string qName;
		aref curQ, newQ,oldQ;
		for(int i=0; i<GetAttributesNum(refOldAttr); i++)
		{
			curQ = GetAttributeN(refOldAttr,i);
			qName = GetAttributeName(curQ);
			refNewAttr.(qName) = "";
			makearef(newQ,refNewAttr.(qName));
			makearef(oldQ,refOldAttr.(qName));
			CopyAttributes(newQ,oldQ);
		}
		CopyAttributes(refOldAttr,&refNewAttr);
*/
        break;
		case "BOAL_UsePotion":
            ref mch = GetMainCharacter();
            aref arItm;
            int itmIdx;
            itmIdx = FindPotionFromChr(mch, &arItm, 0);
	        while(itmIdx>=0)
	        {
		      if( EnablePotionUsing(mch,arItm) )
		      {
			     DoCharacterUsedItem(mch,arItm.id);
			     Log_SetStringToLog("Use potion");
			     break;
		      }
		      itmIdx = FindPotionFromChr(mch, &arItm, itmIdx+1);
	        }
		break;
	}
// boal <--
	
}

void Teleport(int step)
{
	nTeleportLocation = nTeleportLocation + step;
	if(nTeleportLocation >=	nLocationsNum) nTeleportLocation = 1;
	if(nTeleportLocation <=	0) nTeleportLocation = nLocationsNum - 1;
	
	sTeleportLocName = Locations[nTeleportLocation].id;
	Trace("Teleport to '" + sTeleportLocName + "'");

	ReleaseSound(0);
	ClearEvents();
	ClearPostEvents();
	DeleteEntities();
	SetEventHandler("frame","NewGame",1);
}

void ProcessMainMenuKey()
{
	LaunchMainMenu();
}

void ProcessInterfaceKey()
{
	if(bSeaActive && !bAbordageStarted)
	{
		if( CheckAttribute(&BattleInterface,"ComState") && sti(BattleInterface.ComState) != 0 )
			{return;}
	}
	else
	{
		if( SendMessage(GetMainCharacter(),"ls",MSG_CHARACTER_EX_MSG,"IsFightMode") != 0 )
			{return;}
		if( CheckAttribute(&objLandInterface,"ComState") && sti(objLandInterface.ComState) != 0 )
			{return;}
	}
	if( IsEntity(&worldMap) ) return;
	LaunchSelectMenu();
	//LaunchCharacter(GetMainCharacter());
}

void GameOverE()
{
	GameOver("sea");
	DeleteSeaEnvironment();
	/*EngineLayersOffOn(false);
	SetEventHandler(EVENT_END_VIDEO,"LaunchMainMenu",0);
	StartVideo("blaze_grasses_dead");
	InterfaceStates.Buttons.Resume.enable = false;
	InterfaceStates.Buttons.Save.enable = false;
	SetEventHandler(EVENT_END_VIDEO,"LaunchMainMenu",0);*/
	//LaunchMainMenu();
}

void GameOver(string sName)
{
	ref mc;
	int nSelect;
	string sFileName;
	//ResetSoundScheme();
	//PauseAllSounds();
	ResetSound();
	EngineLayersOffOn(false);
	
	mc = GetMainCharacter();
	
	ClearEvents();
	ClearPostEvents();
	DeleteEntities();

	if(sti(InterfaceStates.Launched)) {
		UnloadSegment(Interfaces[CurrentInterface].SectionName);
	}

	if(LoadSegment("Interface\BaseInterface.c"))
	{
		InitBaseInterfaces();
		UnloadSegment("Interface\BaseInterface.c");
	}
	InitSound();
	
	SetEventHandler(EVENT_END_VIDEO,"LaunchMainMenu_afterVideo",0);


	switch(sName)
	{
		case "sea":
			nSelect = rand(1);
			sFileName = "skeleton_on_beach";
			switch(nSelect)
			{
				case 0: sFileName = "skeleton_on_beach"; break;
				case 1: sFileName = "undersea"; break;
			}
			StartPostVideo(sFileName,1);
		break;

		case "boarding":
			StartPostVideo("skeleton_on_beach",1);
		break;

		case "land":
			StartPostVideo("blaze_land_dead",1);
		break;

		case "mutiny":
			StartPostVideo("blaze_mutiny_dead",1);
		break;
	}
	InterfaceStates.Buttons.Resume.enable = false;
	InterfaceStates.Buttons.Save.enable = false;
}
// boal ������� �������� ���� ������-->
void InitGame_boal()
{
    if(LoadSegment("Interface\BaseInterface.c"))
	{
		object  Interfaces_n1[35], Interfaces_new[35];
		Interfaces_n1 = &Interfaces;
		Interfaces_new = &Interfaces_n1;
		Interfaces = &Interfaces_new;
        InitBaseInterfaces();
		UnloadSegment("Interface\BaseInterface.c");
	}
	
/*	if(LoadSegment("store\initStore.c"))
	{
		InitStores();
		UnloadSegment("store\initStore.c");
	}
//	InitSound();
	if(LoadSegment("worldmap\worldmap_init.c"))
	{
		wdmInitWorldMap();
		UnloadSegment("worldmap\worldmap_init.c");
	}

	IslandsInit();
	LocationInit();
	DialogsInit();
	InitTeleport();
	InitParticles();
*/
    if(LoadSegment("items\initItems.c"))
	{
		object RandItems_n1[52], RandItems_new[52];
		RandItems_n1 = &RandItems;
		RandItems_new = &RandItems_n1;
		RandItems = &RandItems_new;
        InitItems();
		UnloadSegment("items\initItems.c");
	}

/*	CharactersInit();
	QuestsInit();
	SeaAIGroupsInit();
	InitQuestMapEncounters();
	InitLandRandomEncounters();
	*/
	Log_SetStringToLog("��� ��!");
}
