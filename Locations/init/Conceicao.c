

int LocationInitConceicao(int n)
{
	// -------------------------------------------------

	Locations[n].filespath.models = "locations\town_Conceicao\port";

	Locations[n].id = "Conceicao_port";
	locations[n].id.label = "Conceicao Port";
	locations[n].worldmap = "Conceicao";
	Locations[n].image = "loading\Conceicao_Port.tga";

	//Town sack
	Locations[n].townsack = "Conceicao";

	//Sound
	locations[n].act.fantoms = 1;
	locations[n].type = "port";
	locations[n].fastreload = "Conceicao";

	//Models
	//Always
	Locations[n].models.always.locators = "Conport_l";
	Locations[n].models.always.seabed = "Conport_sb";
	Locations[n].models.always.seabed.foam = "1";
	Locations[n].models.always.town = "Conport";
	Locations[n].models.always.town.foam = "1";
	Locations[n].models.always.l1 = "Conport_b04";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.grassPatch = "Conport_g";
	//Day
	Locations[n].models.day.rinok = "Conport_e01";
	Locations[n].models.day.fonar = "Conport_fd";
	Locations[n].models.day.charactersPatch = "Conport_pd";
	//Night
	Locations[n].models.night.fonar = "Conport_fn";
	Locations[n].models.night.charactersPatch = "Conport_pn";
	//Environment
	Locations[n].environment.weather = "true";
	Locations[n].environment.sea = "true";
	//Reload map
	LAi_LocationFantomsGen(&locations[n], true);
	Locations[n].reload.l1.name = "reload1";
	Locations[n].reload.l1.go = "Conceicao_town";
	Locations[n].reload.l1.emerge = "reload2";
	Locations[n].reload.l1.autoreload = "0";
	Locations[n].reload.l1.label = "Conceicao.";

	Locations[n].reload.l4.name = "reload2_back";
	Locations[n].reload.l4.go = "Conceicao";
	Locations[n].reload.l4.emerge = "reload_1";
	Locations[n].reload.l4.autoreload = "0";
	Locations[n].reload.l4.label = "Sea.";
	Locations[n].locators_radius.reload.reload2_back = 2;

	Locations[n].reload.l3.name = "reload2";
	Locations[n].reload.l3.go = "Conceicao";
	Locations[n].reload.l3.emerge = "reload_1";
	Locations[n].reload.l3.autoreload = "0";
	Locations[n].reload.l3.label = "Sea.";
	Locations[n].locators_radius.reload.reload2 = 3;

	n = n + 1;

	// -------------------------------------------------

	Locations[n].filespath.models = "locations\town_Conceicao\town";

	Locations[n].id = "Conceicao_town";
	locations[n].id.label = "Conceicao town";
	locations[n].worldmap = "Conceicao";
	Locations[n].image = "loading\Conceicao_Town.tga";

	//Town sack
	Locations[n].townsack = "Conceicao";

	//Sound
	locations[n].type = "town";
	locations[n].fastreload = "Conceicao";
	//Models
	//Always
	Locations[n].models.always.locators = "ConTown_l";
  	Locations[n].models.always.grassPatch = "ConTown_g";
	Locations[n].models.always.town = "ConTown";
	Locations[n].models.always.l1 = "Contown_b02";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "Contown_b03";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "Contown_b04";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";
	//Day
	Locations[n].models.day.fonar = "ConTown_fd";
	Locations[n].models.day.charactersPatch = "ConTown_pd";
	Locations[n].models.day.jumpPatch = "ConTown_j";
	//Night
	Locations[n].models.night.fonar = "ConTown_fn";
	Locations[n].models.night.charactersPatch = "ConTown_pn";
	Locations[n].models.night.jumpPatch = "ConTown_j";
	//Environment
	Locations[n].environment.weather = "true";
	Locations[n].environment.sea = "false";
	//Reload map
	LAi_LocationFantomsGen(&locations[n], true);
	Locations[n].reload.l1.name = "reload1";
	Locations[n].reload.l1.go = "Conceicao_town_exit";
	Locations[n].reload.l1.emerge = "Reload2";
	Locations[n].reload.l1.autoreload = "0";
	Locations[n].reload.l1.label = "Jungle.";

	Locations[n].reload.l2.name = "reload2";
	Locations[n].reload.l2.go = "Conceicao_Port";
	Locations[n].reload.l2.emerge = "reload1";
	Locations[n].reload.l2.autoreload = "0";
	Locations[n].reload.l2.label = "Port.";

	Locations[n].reload.l3.name = "reload4";
	Locations[n].reload.l3.go = "Conceicao_Tavern";
	Locations[n].reload.l3.emerge = "reload1";
	Locations[n].reload.l3.autoreload = "0";
	Locations[n].reload.l3.label = "Tavern.";

	Locations[n].reload.l4.name = "reload18";
	Locations[n].reload.l4.go = "Conceicao_Store";
	Locations[n].reload.l4.emerge = "reload1";
	Locations[n].reload.l4.autoreload = "0";
	Locations[n].reload.l4.label = "Store.";
	Locations[n].reload.l4.close_for_night = 1;

	Locations[n].reload.l5.name = "reload13";
	Locations[n].reload.l5.go = "Conceicao_Shipyard";
	Locations[n].reload.l5.emerge = "reload1";
	Locations[n].reload.l5.autoreload = "0";
	Locations[n].reload.l5.label = "Shipyard.";
	Locations[n].reload.l5.close_for_night = 1;

	Locations[n].reload.l6.name = "reload14";
	Locations[n].reload.l6.go = "Conceicao_townhall";
	Locations[n].reload.l6.emerge = "reload1";
	Locations[n].reload.l6.autoreload = "0";
	Locations[n].reload.l6.label = "Residence.";
	Locations[n].reload.l6.close_for_night = 1;

	Locations[n].reload.l7.name = "reload7";
	Locations[n].reload.l7.go = "Conceicao_church";
	Locations[n].reload.l7.emerge = "reload1";
	Locations[n].reload.l7.autoreload = "0";
	Locations[n].reload.l7.label = "Church.";
	Locations[n].reload.l7.close_for_night = 1;

	Locations[n].reload.l12.name = "reload12";
	Locations[n].reload.l12.go = "Conceicao_UsurerHouse";
	Locations[n].reload.l12.emerge = "reload1";
	Locations[n].reload.l12.autoreload = "0";
	Locations[n].reload.l12.label = "Loanshark's Office.";
	Locations[n].reload.l12.close_for_night = 1;

	Locations[n].reload.l13.name = "reload16";
	Locations[n].reload.l13.go = "Conceicao_HouseInsideR16";
	Locations[n].reload.l13.emerge = "reload1";
	Locations[n].reload.l13.autoreload = "0";
	Locations[n].reload.l13.label = "House.";
	Locations[n].reload.l13.close_for_night = 1;

	Locations[n].reload.l14.name = "reload11";
	Locations[n].reload.l14.go = "Conceicao_HouseInsideR11";
	Locations[n].reload.l14.emerge = "reload1";
	Locations[n].reload.l14.autoreload = "0";
	Locations[n].reload.l14.label = "House.";

	//Hitman

	Locations[n].reload.l15.name = "reload15";
	Locations[n].reload.l15.go = "Hit_house2";
	Locations[n].reload.l15.emerge = "reload1";
	Locations[n].reload.l15.autoreload = "0";
	Locations[n].reload.l15.label = "House of Amerigo Vieira";

	//Hitman

	n = n + 1;


	// -------------------------------------------------

	Locations[n].filespath.models = "locations\inside\Residence5";

	Locations[n].id = "Conceicao_townhall";
	locations[n].id.label = "Conceicao townhall";
	Locations[n].image = "loading\Conceicao_Townhall.tga";

	//Town sack
	Locations[n].townsack = "Conceicao";

	//Sound
	locations[n].type = "residence";
	locations[n].fastreload = "Conceicao";

	//Models
	//Always
	Locations[n].models.always.locators = "Res05_l";
	Locations[n].models.always.l1 = "Res05";
	Locations[n].models.always.window = "Res05_w";
	Locations[n].models.always.window.tech = "LocationWindows";
	Locations[n].models.always.window.level = 50;

	//Day
	Locations[n].models.day.charactersPatch = "Res05_p";
	//Night
	Locations[n].models.night.charactersPatch = "Res05_p";
	//Environment
	Locations[n].environment.weather = "false";
	Locations[n].environment.sea = "false";
	Locations[n].models.back = "back\cores5_";

	//Reload map
	Locations[n].reload.l1.name = "Reload1";
	Locations[n].reload.l1.go = "Conceicao_town";
	Locations[n].reload.l1.emerge = "reload14";
	Locations[n].reload.l1.autoreload = "0";
	Locations[n].reload.l1.label = "Conceicao.";

	LAi_LocationFightDisable(&Locations[n], true);

	n = n + 1;


	// -------------------------------------------------

	Locations[n].filespath.models = "locations\town_Conceicao\exit";

	Locations[n].id = "Conceicao_town_exit";
	locations[n].id.label = "Exit from Conceicao";
	Locations[n].image = "loading\Conceicao_Town_Exit.tga";

	//Town sack
	Locations[n].townsack = "Conceicao";

	//Sound
	locations[n].type = "jungle";
	LAi_LocationMonstersGen(&locations[n], true);
	LAi_LocationSetMonstersTime(&locations[n], 22, 6);
//	locations[n].fastreload = "Conceicao";
	//Models
	//Always
	Locations[n].models.always.locators = "ConExit_l";
	Locations[n].models.always.exit = "ConExit";
	Locations[n].models.always.grassPatch = "ConExit_g";
	Locations[n].models.always.l1 = "plan_1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan_2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan_3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";

	//Day
	Locations[n].models.day.fonar = "ConExit_fd";
	Locations[n].models.day.charactersPatch = "ConExit_p";
	//Night
	Locations[n].models.night.fonar = "ConExit_fn";
	Locations[n].models.night.charactersPatch = "ConExit_p";
	//Environment
	Locations[n].environment.weather = "true";
	Locations[n].environment.sea = "false";

	//Reload map
	Locations[n].reload.l1.name = "Reload1";
	Locations[n].reload.l1.go = "Conceicao_Jungle_01";
	Locations[n].reload.l1.emerge = "reload3";
	Locations[n].reload.l1.autoreload = "1";
	Locations[n].reload.l1.label = "Jungle.";
	Locations[n].locators_radius.reload.reload1 = 2;

	Locations[n].reload.l3.name = "Reload1_back";
	Locations[n].reload.l3.go = "Conceicao_Jungle_01";
	Locations[n].reload.l3.emerge = "reload3";
	Locations[n].reload.l3.autoreload = "1";
	Locations[n].reload.l3.label = "Jungle.";
	Locations[n].locators_radius.reload.Reload1_back = 2;

	Locations[n].reload.l2.name = "Reload2";
	Locations[n].reload.l2.go = "Conceicao_town";
	Locations[n].reload.l2.emerge = "reload1";
	Locations[n].reload.l2.autoreload = "0";
	Locations[n].reload.l2.label = "Conceicao.";
	Locations[n].locators_radius.reload.reload2 = 1.5;
	n = n + 1;

	// -------------------------------------------------

	Locations[n].filespath.models = "locations\Inside\MediumStore";
	Locations[n].image = "loading\store_02.tga";

	Locations[n].id = "Conceicao_Store";
	locations[n].id.label = "Conceicao store";

	//Town sack
	Locations[n].townsack = "Conceicao";

	//Sound
	locations[n].type = "shop";
	locations[n].fastreload = "Conceicao";
	//Models
	//Always
	Locations[n].models.always.locators = "MS_l";
	Locations[n].models.always.store = "MS";
	Locations[n].models.always.window = "MS_w";
	Locations[n].models.always.window.tech = "LocationWindows";
	Locations[n].models.always.window.level = 50;

	//Day
	Locations[n].models.day.charactersPatch = "MS_p";

	//Night
	Locations[n].models.night.charactersPatch = "MS_p";
	//Environment

	Locations[n].environment.weather = "false";
	Locations[n].environment.sea = "false";
	Locations[n].models.back = "back\coms_";

	//Reload map
	Locations[n].reload.l1.name = "reload1";
	Locations[n].reload.l1.go = "Conceicao_town";
	Locations[n].reload.l1.emerge = "Reload18";
	Locations[n].reload.l1.autoreload = "0";
	Locations[n].reload.l1.label = "Conceicao.";
	Locations[n].locators_radius.camdetector.camera1 = 5;
	LAi_LocationFightDisable(&Locations[n], true);

	n = n + 1;

// -------------------------------------------------

	Locations[n].filespath.models = "locations\Inside\Shipyard3";

	Locations[n].id = "Conceicao_Shipyard";
	locations[n].id.label = "Conceicao shipyard";
	Locations[n].image = "loading\Shipyard_02.tga";

	//Town sack
	Locations[n].townsack = "Conceicao";

	//Sound
	locations[n].type = "shop";
	locations[n].fastreload = "Conceicao";
	//Models
	//Always
	Locations[n].models.always.locators = "sh03_l";
	Locations[n].models.always.l1 = "Sh03";
	Locations[n].models.always.window = "sh03_w";
	Locations[n].models.always.window.tech = "LocationWindows";
	Locations[n].models.always.window.level = 50;

	//Day
	Locations[n].models.day.charactersPatch = "Sh03_p";

	//Night
	Locations[n].models.night.charactersPatch = "Sh03_p";

	//Environment
	Locations[n].environment.weather = "false";
	Locations[n].environment.sea = "false";
	Locations[n].models.back = "back\cosh3_";
	//Reload map
	Locations[n].reload.l1.name = "reload1";
	Locations[n].reload.l1.go = "Conceicao_town";
	Locations[n].reload.l1.emerge = "Reload13";
	Locations[n].reload.l1.autoreload = "0";
	Locations[n].reload.l1.label = "Conceicao.";
	LAi_LocationFightDisable(&Locations[n], true);

	n = n + 1;



	// -------------------------------------------------

	Locations[n].filespath.models = "locations\Inside\SmallTavern";

	Locations[n].id = "Conceicao_Tavern";
	locations[n].id.label = "Conceicao Tavern";
	Locations[n].image = "loading\Tavern_03.tga";

	//Town sack
	Locations[n].townsack = "Conceicao";

	//Sound
	locations[n].type = "tavern";
	locations[n].fastreload = "Conceicao";
	//Models
	//Always
	Locations[n].models.always.locators = "ST_l";
	Locations[n].models.always.tavern = "ST";
	Locations[n].models.always.window = "St_w";
	Locations[n].models.always.window.tech = "LocationWindows";
	Locations[n].models.always.window.level = 50;
	//Day
	Locations[n].models.day.charactersPatch = "ST_p";

	//Night
	Locations[n].models.night.charactersPatch = "ST_p";

	//Environment
	Locations[n].environment.weather = "false";
	Locations[n].environment.sea = "false";
	Locations[n].models.back = "back\cost_";
	//Reload map
	Locations[n].reload.l1.name = "reload1";
	Locations[n].reload.l1.go = "Conceicao_Town";
	Locations[n].reload.l1.emerge = "reload4";
	Locations[n].reload.l1.autoreload = "0";
	Locations[n].reload.l1.label = "Conceicao.";

	Locations[n].reload.l2.name = "reload2";
	Locations[n].reload.l2.go = "Conceicao_tavern_upstairs";
	Locations[n].reload.l2.emerge = "reload1";
	Locations[n].reload.l2.autoreload = "0";
	Locations[n].reload.l2.label = "Room.";
	Locations[n].reload.l2.disable = 1;
	LAi_LocationFightDisable(&Locations[n], true);

	n = n + 1;

	// -------------------------------------------------
	Locations[n].filespath.models = "locations\Inside\Doubleflour_house";

	Locations[n].id = "Conceicao_tavern_upstairs";
	locations[n].id.label = "Room in Conceicao tavern";
	Locations[n].image = "loading\Tavern_Upstairs_01.tga";

	//Town sack
	Locations[n].townsack = "Conceicao";

	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Conceicao";
	//Models
	//Always
	Locations[n].models.always.locators = "LH_F2_l";
	Locations[n].models.always.house = "LH_F2";
	Locations[n].models.always.window = "LH_F2_w";
	Locations[n].models.always.window.tech = "LocationWindows";
	Locations[n].models.always.window.level = 50;
	//Day
	Locations[n].models.day.charactersPatch = "LH_F2_p";

	//Night
	Locations[n].models.night.charactersPatch = "LH_F2_p";

	//Environment
	Locations[n].environment.weather = "false";
	Locations[n].environment.sea = "false";
	Locations[n].models.back = "back\colf2_";
	//Reload map
	Locations[n].reload.l1.name = "reload1";
	Locations[n].reload.l1.go = "Conceicao_tavern";
	Locations[n].reload.l1.emerge = "reload2";
	Locations[n].reload.l1.autoreload = "0";
	Locations[n].reload.l1.label = "Tavern.";

	n = n + 1;

	// -------------------------------------------------

	Locations[n].filespath.models = "locations\Inside\SmallHome";

	Locations[n].id = "Conceicao_UsurerHouse";
	locations[n].id.label = "Loanshark's Office.";
	Locations[n].image = "loading\house_03.tga";

	//Town sack
	Locations[n].townsack = "Conceicao";

	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Conceicao";
	//Models
	//Always
	Locations[n].models.always.locators = "SH_l";
	Locations[n].models.always.house = "SH";
	//Locations[n].models.always.env = "smallhome_FF_02_env";
	Locations[n].models.always.window = "Sh_w";
	Locations[n].models.always.window.tech = "LocationWindows";
	Locations[n].models.always.window.level = 50;
	//Day
	Locations[n].models.day.charactersPatch = "Sh_p";

	//Night
	Locations[n].models.night.charactersPatch = "Sh_p";

	//Environment
	Locations[n].environment.weather = "false";
	Locations[n].environment.sea = "false";
	Locations[n].models.back = "back\cosh_";
	//Reload map
	Locations[n].reload.l1.name = "reload1";
	Locations[n].reload.l1.go = "Conceicao_town";
	Locations[n].reload.l1.emerge = "reload12";
	Locations[n].reload.l1.autoreload = "0";
	Locations[n].reload.l1.label = "Conceicao.";
	LAi_LocationFightDisable(&Locations[n], true);

	n = n + 1;

	// -------------------------------------------------

	Locations[n].filespath.models = "locations\Outside\Jungle_6";

	Locations[n].id = "Conceicao_Jungle_01";
	locations[n].id.label = "Conceicao jungle";
	Locations[n].image = "loading\Conceicao_Jungle_01.tga";
	//Sound
	locations[n].type = "jungle";
	LAi_LocationMonstersGen(&locations[n], true);
	LAi_LocationSetMonstersTime(&locations[n], 22, 6);

	//Models
	//Always
	Locations[n].models.always.locators = "Jungle06_l";
	Locations[n].models.always.jungle = "Jungle06";
	Locations[n].models.always.grassPatch = "JUNGLE06_g";
	Locations[n].models.always.l1 = "plan_1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan_2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan_3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";

	//Day
	Locations[n].models.day.charactersPatch = "Jungle06_p";
	//Night
	Locations[n].models.night.charactersPatch = "Jungle06_p";
	//Environment
	Locations[n].environment.weather = "true";
	Locations[n].environment.sea = "false";
	//Reload map
	Locations[n].reload.l1.name = "reload1";
	Locations[n].reload.l1.go = "Smugglers_lair_exit";
	Locations[n].reload.l1.emerge = "reload1";
	Locations[n].reload.l1.autoreload = "1";
	Locations[n].locators_radius.reload.reload1 = 2.5;
	Locations[n].reload.l1.label = "Jungle.";

	Locations[n].reload.l2.name = "reload2";
	Locations[n].reload.l2.go = "Conceicao_Shore_01";
	Locations[n].reload.l2.emerge = "reload2";
	Locations[n].reload.l2.autoreload = "1";
	Locations[n].locators_radius.reload.reload2 = 2.5;
	Locations[n].reload.l2.label = "Sunny Haven.";

	Locations[n].reload.l3.name = "reload3";
	Locations[n].reload.l3.go = "Conceicao_town_exit";
	Locations[n].reload.l3.emerge = "reload1";
	Locations[n].reload.l3.autoreload = "1";
	Locations[n].locators_radius.reload.reload3 = 2.5;
	Locations[n].reload.l3.label = "Jungle.";

	Locations[n].reload.l4.name = "reload2_back";
	Locations[n].reload.l4.go = "Conceicao_Shore_01";
	Locations[n].reload.l4.emerge = "reload2";
	Locations[n].reload.l4.autoreload = "1";
	Locations[n].locators_radius.reload.reload2_back = 2.5;
	Locations[n].reload.l4.label = "Sunny Haven.";

	Locations[n].reload.l5.name = "reload3_back";
	Locations[n].reload.l5.go = "Conceicao_town_exit";
	Locations[n].reload.l5.emerge = "reload1";
	Locations[n].reload.l5.autoreload = "1";
	Locations[n].locators_radius.reload.reload3_back = 3;
	Locations[n].reload.l5.label = "Jungle.";

	Locations[n].reload.l6.name = "reload1_back";
	Locations[n].reload.l6.go = "Smugglers_lair_exit";
	Locations[n].reload.l6.emerge = "reload1";
	Locations[n].reload.l6.autoreload = "1";
	Locations[n].locators_radius.reload.reload1_back = 2.5;
	Locations[n].reload.l6.label = "Jungle.";

	n = n + 1;


	// -------------------------------------------------


	Locations[n].filespath.models = "locations\Outside\Shore_8";

	Locations[n].id = "Conceicao_shore_01";
	locations[n].id.label = "Conceicao shore";
	locations[n].worldmap = "CShore 1";
	Locations[n].image = "loading\Conceicao_Shore_01.tga";
	Locations[n].name = "Sunny Haven";
	//Sound
	locations[n].type = "seashore";

	//Models
	//Always
	Locations[n].models.always.jungle = "Shore08";
	Locations[n].models.always.jungle.foam = "1";
	Locations[n].models.always.locators = "Shore08_l";
	Locations[n].models.always.grassPatch = "Shore08_g";
	Locations[n].models.always.seabed = "Shore08_sb";
	Locations[n].models.always.seabed.foam = "1";
	Locations[n].models.always.l1 = "plan_1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan_2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan_3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";

	//Day
	Locations[n].models.day.charactersPatch = "Shore08_p";
	//Night
	Locations[n].models.night.charactersPatch = "Shore08_p";
	//Environment
	Locations[n].environment.weather = "true";
	Locations[n].environment.sea = "true";
	//Reload map
	Locations[n].reload.l1.name = "reload2";
	Locations[n].reload.l1.go = "Conceicao_Jungle_01";
	Locations[n].reload.l1.emerge = "reload2";
	Locations[n].reload.l1.autoreload = "1";
	Locations[n].reload.l1.label = "Jungle.";
	Locations[n].locators_radius.reload.reload2 = 3;

	Locations[n].reload.l3.name = "reload2_back";
	Locations[n].reload.l3.go = "Conceicao_Jungle_01";
	Locations[n].reload.l3.emerge = "reload2";
	Locations[n].reload.l3.autoreload = "1";
	Locations[n].reload.l3.label = "Jungle.";
	Locations[n].locators_radius.reload.reload2_back = 3;

	Locations[n].reload.l2.name = "boat";
	Locations[n].reload.l2.go = "Conceicao";
	Locations[n].reload.l2.emerge = "reload_2";
	Locations[n].reload.l2.autoreload = "0";
	Locations[n].locators_radius.reload.boat = 9.0;
	Locations[n].reload.l2.label = "Sea.";

	n = n + 1;


	// -------------------------------------------------

	Locations[n].filespath.models = "locations\Outside\Shore_4";

	Locations[n].id = "Conceicao_shore_02";
	locations[n].id.label = "Conceicao shore";
	locations[n].worldmap = "CShore 2";
	Locations[n].image = "loading\Conceicao_Shore_02.tga";
	Locations[n].name = "Leviathan Rock";
	//Sound
	locations[n].type = "seashore";

	//Models
	//Always
	Locations[n].models.always.locators = "Shore04_l";
	Locations[n].models.always.shore = "Shore04";
	Locations[n].models.always.shore.foam = "1";
	Locations[n].models.always.seabed = "Shore04_sb";
	Locations[n].models.always.seabed.foam = "1";
	Locations[n].models.always.grassPatch = "Shore04_g";
	Locations[n].models.always.l1 = "plan_1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan_2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan_3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";

	//Day
	Locations[n].models.day.charactersPatch = "Shore04_p";
	//Night
	Locations[n].models.night.charactersPatch = "Shore04_p";
	//Environment
	Locations[n].environment.weather = "true";
	Locations[n].environment.sea = "true";
	//Reload map
	Locations[n].reload.l4.name = "rock1";
	Locations[n].reload.l4.go = "Conceicao_Grot";
	Locations[n].reload.l4.emerge = "reload1";
	Locations[n].reload.l4.autoreload = "1";	
	Locations[n].reload.l4.label = "Hidden Cave.";

	Locations[n].reload.l5.name = "rock1_back";
	Locations[n].reload.l5.go = "Conceicao_Grot";
	Locations[n].reload.l5.emerge = "reload1";
	Locations[n].reload.l5.autoreload = "1";
	Locations[n].locators_radius.reload.rock1_back = 1.5;
	Locations[n].reload.l5.label = "Hidden Cave.";


	Locations[n].reload.l1.name = "locator3";
	Locations[n].reload.l1.go = "Smugglers_Lair_exit";
	Locations[n].reload.l1.emerge = "reload2";
	Locations[n].reload.l1.autoreload = "1";
	Locations[n].locators_radius.reload.locator3 = 3;
	Locations[n].reload.l1.label = "Jungle.";

	Locations[n].reload.l3.name = "locator3_back";
	Locations[n].reload.l3.go = "Smugglers_Lair_exit";
	Locations[n].reload.l3.emerge = "reload2";
	Locations[n].reload.l3.autoreload = "1";
	Locations[n].locators_radius.reload.locator3_back = 1;
	Locations[n].reload.l3.label = "Jungle.";

	Locations[n].reload.l2.name = "boat";
	Locations[n].reload.l2.go = "Conceicao";
	Locations[n].reload.l2.emerge = "reload_3";
	Locations[n].reload.l2.autoreload = "0";
	Locations[n].locators_radius.reload.boat = 9.0;
	Locations[n].reload.l2.label = "Sea.";

	n = n + 1;


// -------------------------------------------------


	Locations[n].filespath.models = "locations\Smuggler Lair\Exit";

	Locations[n].id = "Smugglers_lair_exit";
	locations[n].id.label = "Exit from Smugglers Lair";
	Locations[n].image = "loading\Smugglers_Lair_Town_Exit.tga";
	//Sound
	locations[n].type = "jungle";
	LAi_LocationMonstersGen(&locations[n], true);
	LAi_LocationSetMonstersTime(&locations[n], 22, 6);

	//Models
	//Always
	Locations[n].models.always.locators = "SmLexit_l";
	Locations[n].models.always.exit = "SmLexit";
	Locations[n].models.always.grassPatch = "SmLexit_g";
	Locations[n].models.always.l1 = "plan_1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan_2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan_3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";

	//Day
	Locations[n].models.day.charactersPatch = "SmLexit_p";
	Locations[n].models.day.fonar = "SmLexit_fd";
	//Night
	Locations[n].models.night.charactersPatch = "SmLexit_p";
	Locations[n].models.night.fonar = "SmLexit_fn";
	//Environment
	Locations[n].environment.weather = "true";
	Locations[n].environment.sea = "false";
	//Reload map
	Locations[n].reload.l1.name = "reload1";
	Locations[n].reload.l1.go = "Conceicao_jungle_01";
	Locations[n].reload.l1.emerge = "reload1";
	Locations[n].reload.l1.autoreload = "1";
	Locations[n].locators_radius.reload.reload1 = 2;
	Locations[n].reload.l1.label = "Jungle.";

	Locations[n].reload.l2.name = "reload2";
	Locations[n].reload.l2.go = "Conceicao_shore_02";
	Locations[n].reload.l2.emerge = "locator3";
	Locations[n].reload.l2.autoreload = "1";
	Locations[n].locators_radius.reload.reload2 = 2;
	Locations[n].reload.l2.label = "Leviathan Rock.";

	Locations[n].reload.l4.name = "reload1_back";
	Locations[n].reload.l4.go = "Conceicao_jungle_01";
	Locations[n].reload.l4.emerge = "reload1";
	Locations[n].reload.l4.autoreload = "1";
	Locations[n].locators_radius.reload.reload1_back = 2;
	Locations[n].reload.l4.label = "Jungle.";

	Locations[n].reload.l5.name = "reload2_back";
	Locations[n].reload.l5.go = "Conceicao_shore_02";
	Locations[n].reload.l5.emerge = "locator3";
	Locations[n].reload.l5.autoreload = "1";
	Locations[n].locators_radius.reload.reload2_back = 2;
	Locations[n].reload.l5.label = "Leviathan Rock.";

	Locations[n].reload.l3.name = "reload3";
	Locations[n].reload.l3.go = "Smugglers_lair";
	Locations[n].reload.l3.emerge = "reload1";
	Locations[n].reload.l3.autoreload = "0";
	Locations[n].reload.l3.label = "Smugglers Lair.";

	n = n + 1;

	// -------------------------------------------------

	Locations[n].filespath.models = "locations\Smuggler Lair\town";

	Locations[n].id = "Smugglers_Lair";
	locations[n].id.label = "Smugglers Lair";
	Locations[n].image = "loading\Smugglers_Lair_Town.tga";
	//Sound
	locations[n].type = "town";

	//Models
	//Always
	Locations[n].models.always.locators = "SmL_l";
	Locations[n].models.always.town = "SmL";
	Locations[n].models.always.grassPatch = "SmL_g";
	Locations[n].models.always.l1 = "plan_1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan_2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan_3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";
	Locations[n].models.always.l4 = "plan_4";
	Locations[n].models.always.l4.level = 6;
	Locations[n].models.always.l4.tech = "LocationModelBlend";

	//Day
	Locations[n].models.day.charactersPatch = "SmL_p";
	Locations[n].models.day.fonar = "SmL_fd";
	Locations[n].models.day.jumppatch = "SmL_j";
	//Night
	Locations[n].models.night.charactersPatch = "SmL_p";
	Locations[n].models.night.fonar = "SmL_fn";
	Locations[n].models.night.jumppatch = "SmL_j";
	//Environment
	Locations[n].environment.weather = "true";
	Locations[n].environment.sea = "false";
	//Reload map
	Locations[n].reload.l1.name = "reload1";
	Locations[n].reload.l1.go = "Smugglers_Lair_exit";
	Locations[n].reload.l1.emerge = "reload3";
	Locations[n].reload.l1.autoreload = "0";
	Locations[n].reload.l1.label = "Jungle.";

	Locations[n].reload.l2.name = "reload3";
	Locations[n].reload.l2.go = "Smugglers_Store";
	Locations[n].reload.l2.emerge = "locator2";
	Locations[n].reload.l2.autoreload = "0";
	Locations[n].reload.l2.label = "Store.";
	Locations[n].reload.l2.close_for_night = 1;

	Locations[n].reload.l3.name = "reload6";
	Locations[n].reload.l3.go = "Smugglers_Tavern";
	Locations[n].reload.l3.emerge = "reload1";
	Locations[n].reload.l3.autoreload = "0";
	Locations[n].reload.l3.label = "Tavern.";

	Locations[n].reload.l4.name = "reload7";
	Locations[n].reload.l4.go = "Smugglers_Residence";
	Locations[n].reload.l4.emerge = "reload1";
	Locations[n].reload.l4.autoreload = "0";
	Locations[n].reload.l4.label = "Chief's House.";
	Locations[n].reload.l4.close_for_night = 1;

	Locations[n].reload.l5.name = "reload10";
	Locations[n].reload.l5.go = "Rheims_house_in_smugglers";
	Locations[n].reload.l5.emerge = "reload1";
	Locations[n].reload.l5.disable = "1";
	Locations[n].reload.l5.autoreload = "0";
	Locations[n].reload.l5.label = "Rheims' House.";

	Locations[n].reload.l6.name = "window";
	Locations[n].reload.l6.go = "Rheims_house_in_smugglers";
	Locations[n].reload.l6.emerge = "reload1";
	Locations[n].reload.l6.disable = "1";
	Locations[n].reload.l6.autoreload = "0";
	Locations[n].reload.l6.label = "Rheims' House Window.";

	n = n + 1;

	// -------------------------------------------------

	Locations[n].filespath.models = "locations\Inside\StoreSmall";
	Locations[n].image = "loading\Store_04.tga";

	Locations[n].id = "Smugglers_Store";

	//Sound
	locations[n].type = "shop";
	locations[n].fastreload = "Conceicao";

	//Models
	//Always
	Locations[n].models.always.locators = "SS_l";
	Locations[n].models.always.store = "SS";
	Locations[n].models.always.window = "SS_w";
	Locations[n].models.always.window.tech = "LocationWindows";
	Locations[n].models.always.window.level = 50;

	//Day
	Locations[n].models.day.charactersPatch = "SS_p";
	Locations[n].models.day.fonar = "SS_fn";

	//Night
	Locations[n].models.night.charactersPatch = "SS_p";
	Locations[n].models.night.fonar = "SS_fn";

	//Environment
	Locations[n].environment.weather = "false";
	Locations[n].environment.sea = "false";
	Locations[n].models.back = "back\smuss_";
	//Reload map
	Locations[n].reload.l1.name = "locator2";
	Locations[n].reload.l1.go = "Smugglers_Lair";
	Locations[n].reload.l1.emerge = "Reload3";
	Locations[n].reload.l1.autoreload = "0";
	Locations[n].reload.l1.label = "Smugglers Lair.";
	LAi_LocationFightDisable(&Locations[n], true);

	n = n + 1;


	// -------------------------------------------------

	Locations[n].filespath.models = "locations\Inside\MediumTavern";

	Locations[n].id = "Smugglers_Tavern";
	locations[n].id.label = "Smugglers Tavern";
	Locations[n].image = "loading\Tavern_02.tga";
	//Sound
	locations[n].type = "tavern";

	//Models
	//Always
	Locations[n].models.always.locators = "MT_l";
	Locations[n].models.always.l1 = "MT";
	Locations[n].models.always.window = "MT_w";
	Locations[n].models.always.window.tech = "LocationWindows";
	Locations[n].models.always.window.level = 50;

	//Day
	Locations[n].models.day.charactersPatch = "MT_p";

	//Night
	Locations[n].models.night.charactersPatch = "MT_p";

	//Environment
	Locations[n].environment.weather = "false";
	Locations[n].environment.sea = "false";
	Locations[n].models.back = "back\smumt_";
	//Reload map
	Locations[n].reload.l1.name = "reload1";
	Locations[n].reload.l1.go = "Smugglers_Lair";
	Locations[n].reload.l1.emerge = "reload6";
	Locations[n].reload.l1.autoreload = "0";
	Locations[n].reload.l1.label = "Smugglers Lair.";

	//fake reload_to_room
	Locations[n].reload.l2.name = "to_room";
	Locations[n].reload.l2.go = "Smugglers_tavern_upstairs";
	Locations[n].reload.l2.emerge = "reload1";
	Locations[n].reload.l2.autoreload = "0";
	Locations[n].reload.l2.label = "Room.";

	//fake reload_back_to_tavern
	Locations[n].reload.l3.name = "back_to_tavern";
	Locations[n].reload.l3.go = "Smugglers_tavern";
	Locations[n].reload.l3.emerge = "reload1";
	Locations[n].reload.l3.autoreload = "0";
	Locations[n].reload.l3.label = "Tavern.";
	LAi_LocationFightDisable(&Locations[n], true);


	n = n + 1;


	// -------------------------------------------------

	Locations[n].filespath.models = "locations\Inside\MediumHouse2";

	Locations[n].id = "Smugglers_residence";
	locations[n].id.label = "House of Leader of smugglers";
	Locations[n].image = "loading\room.tga";
	//Sound
	locations[n].type = "house";

	//Models
	//Always
	Locations[n].models.always.locators = "MH02_l";
	Locations[n].models.always.house = "MH02";
	//Locations[n].models.always.env = "smalltavern_env";
	Locations[n].models.always.window = "MH02_w";
	Locations[n].models.always.window.tech = "LocationWindows";
	Locations[n].models.always.window.level = 50;
	//Day
	Locations[n].models.day.charactersPatch = "MH02_p";

	//Night
	Locations[n].models.night.charactersPatch = "MH02_p";

	//Environment
	Locations[n].environment.weather = "false";
	Locations[n].environment.sea = "false";
	Locations[n].models.back = "back\smumh2_";
	//Reload map
	Locations[n].reload.l1.name = "reload1";
	Locations[n].reload.l1.go = "Smugglers_Lair";
	Locations[n].reload.l1.emerge = "reload7";
	Locations[n].reload.l1.autoreload = "0";
	Locations[n].reload.l1.label = "Smugglers Lair.";
	LAi_LocationFightDisable(&Locations[n], true);

	n = n + 1;

	// -------------------------------------------------
	Locations[n].filespath.models = "locations\Inside\MediumHouse";

	Locations[n].id = "Rheims_house_in_smugglers";
	locations[n].id.label = "Rheims house in smugglers lair";
	Locations[n].image = "loading\room.tga";
	//Sound
	locations[n].type = "house";

	//Models
	//Always
	Locations[n].models.always.locators = "MH_l";
	Locations[n].models.always.house = "MH";
	Locations[n].models.always.window = "MH_w";
	Locations[n].models.always.window.tech = "LocationWindows";
	Locations[n].models.always.window.level = 50;
	//Day
	Locations[n].models.day.charactersPatch = "MH_p";

	//Night
	Locations[n].models.night.charactersPatch = "MH_p";

	//Environment
	Locations[n].environment.weather = "false";
	Locations[n].environment.sea = "false";
	Locations[n].models.back = "back\smumh_";
	//Reload map
	Locations[n].reload.l1.name = "reload1";
	Locations[n].reload.l1.go = "Smugglers_Lair";
	Locations[n].reload.l1.emerge = "reload10";
	Locations[n].reload.l1.autoreload = "0";
	Locations[n].reload.l1.label = "Smugglers Lair.";


	n = n + 1;

	// -------------------------------------------------
	Locations[n].filespath.models = "locations\Inside\SmallHome";

	Locations[n].id = "Smugglers_tavern_upstairs";
	locations[n].id.label = "Room in Smugglers Lair tavern";
	Locations[n].image = "loading\Tavern_Upstairs_01.tga";
	//Sound
	locations[n].type = "house";

	//Models
	//Always
	Locations[n].models.always.locators = "SH_l";
	Locations[n].models.always.house = "SH";
	//Locations[n].models.always.env = "smallhome_FF_02_env";
	Locations[n].models.always.window = "Sh_w";
	Locations[n].models.always.window.tech = "LocationWindows";
	Locations[n].models.always.window.level = 50;
	//Day
	Locations[n].models.day.charactersPatch = "Sh_p";

	//Night
	Locations[n].models.night.charactersPatch = "Sh_p";

	//Environment
	Locations[n].environment.weather = "false";
	Locations[n].environment.sea = "false";
	Locations[n].models.back = "back\smush_";
	//Reload map
	Locations[n].reload.l1.name = "reload1";
	Locations[n].reload.l1.go = "Smugglers_tavern";
	Locations[n].reload.l1.emerge = "reload2";
	Locations[n].reload.l1.autoreload = "0";
	Locations[n].reload.l1.label = "Tavern.";

	n = n + 1;

	// Conceicao_church -------------------------------------------------
	Locations[n].id = "Conceicao_church";
	locations[n].id.label = "Conceicao's church";
	Locations[n].image = "loading\Small_Churche.tga";
	Locations[n].filespath.models = "locations\inside\Church_2\";

	//Town sack
	Locations[n].townsack = "Conceicao";

	//Sound
	locations[n].type = "church";
	locations[n].fastreload = "Conceicao";
	//Models
	//Always
	Locations[n].models.always.city = "Church2";
	Locations[n].models.always.locators = "Church2_l";
	Locations[n].models.always.window = "church2_w";
	Locations[n].models.always.window.tech = "LocationWindows";
	Locations[n].models.always.window.level = 50;
	//Day
//	Locations[n].models.day.lamp = "FalaiseDeFleur05_day";
	Locations[n].models.day.charactersPatch = "Church2_p";

	//Night
//	Locations[n].models.night.lamp = "FalaiseDeFleur05_night";
	Locations[n].models.night.charactersPatch = "Church2_p";

	//Environment
	Locations[n].environment.weather = "false";
	Locations[n].environment.sea = "false";
	//Reload map
	Locations[n].reload.l1.name = "reload1";
	Locations[n].reload.l1.go = "Conceicao_town";
	Locations[n].reload.l1.emerge = "reload7";
	Locations[n].reload.l1.autoreload = "0";
	Locations[n].reload.l1.label = "Conceicao";
	LAi_LocationFightDisable(&Locations[n], true);

	n = n + 1;

	// -------------------------------------------------

	Locations[n].filespath.models = "locations\Inside\mh4";

	Locations[n].id = "Conceicao_HouseInsideR16";
	locations[n].id.label = "House.";
	Locations[n].image = "loading\house_05.tga";

	//Town sack
	Locations[n].townsack = "Conceicao";

	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Conceicao";
	//Models
	//Always
	Locations[n].models.always.locators = "mh4_l";
	Locations[n].models.always.house = "mh4";
	//Locations[n].models.always.env = "smallhome_FF_02_env";
	Locations[n].models.always.window = "mh4_w";
	Locations[n].models.always.window.tech = "LocationWindows";
	Locations[n].models.always.window.level = 50;
	//Day
	Locations[n].models.day.charactersPatch = "mh4_p";

	//Night
	Locations[n].models.night.charactersPatch = "mh4_p";

	//Environment
	Locations[n].environment.weather = "false";
	Locations[n].environment.sea = "false";
	Locations[n].models.back = "back\comh4_";
	//Reload map
	Locations[n].reload.l1.name = "reload1";
	Locations[n].reload.l1.go = "Conceicao_town";
	Locations[n].reload.l1.emerge = "reload16";
	Locations[n].reload.l1.autoreload = "0";
	Locations[n].reload.l1.label = "Conceicao.";

	n = n + 1;

		// -------------------------------------------------

	Locations[n].filespath.models = "locations\Inside\mh8";

	Locations[n].id = "Conceicao_HouseInsideR11";
	locations[n].id.label = "House.";
	Locations[n].image = "loading\house_06.tga";

	//Town sack
	Locations[n].townsack = "Conceicao";

	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Conceicao";
	//Models
	//Always
	Locations[n].models.always.locators = "mh8_l";
	Locations[n].models.always.house = "mh8";
	//Locations[n].models.always.env = "smallhome_FF_02_env";
	Locations[n].models.always.window = "mh8_w";
	Locations[n].models.always.window.tech = "LocationWindows";
	Locations[n].models.always.window.level = 50;
	//Day
	Locations[n].models.day.charactersPatch = "mh8_p";

	//Night
	Locations[n].models.night.charactersPatch = "mh8_p";

	//Environment
	Locations[n].environment.weather = "false";
	Locations[n].environment.sea = "false";
	Locations[n].models.back = "back\comh8_";
	//Reload map
	Locations[n].reload.l1.name = "reload1";
	Locations[n].reload.l1.go = "Conceicao_town";
	Locations[n].reload.l1.emerge = "reload11";
	Locations[n].reload.l1.autoreload = "0";
	Locations[n].reload.l1.label = "Conceicao.";

	Locations[n].locators_radius.camdetector.camera1 = 3.0;
	Locations[n].locators_radius.camdetector.camera2 = 1.8;

	n = n + 1;

//-------------------------------------------------------------------------------------------


	Locations[n].filespath.models = "locations\Inside\Grot";

	Locations[n].id = "Conceicao_Grot";
	locations[n].id.label = "Hidden Cave";
	Locations[n].image = "loading\Conceicao_Cave.tga";
	//Sound
	locations[n].type = "cave";
	//Models
	Locations[n].models.back = "back\grotenv_";
	//Always
	Locations[n].models.always.cave = "Grot";
	Locations[n].models.always.locators = "Grot_l";
	//Day
	Locations[n].models.day.charactersPatch = "Grot_p";
	//Night
	Locations[n].models.night.charactersPatch = "Grot_p";
	//Environment
	Locations[n].environment.weather = "false";
	Locations[n].environment.sea = "false";
	//Reload map
	Locations[n].reload.l1.name = "reload1";
	Locations[n].reload.l1.go = "Conceicao_Shore_02";
	Locations[n].reload.l1.emerge = "rock1";
	Locations[n].reload.l1.autoreload = "1";
	Locations[n].reload.l1.label = "Leviathan Rock.";

	Locations[n].reload.l2.name = "reload1_back";
	Locations[n].reload.l2.go = "Conceicao_Shore_02";
	Locations[n].reload.l2.emerge = "rock1";
	Locations[n].reload.l2.autoreload = "1";
	Locations[n].reload.l2.label = "Leviathan Rock.";
	Locations[n].locators_radius.reload.reload1_back = 2;

	LAi_LocationMonstersGen(&locations[n], true);
	LAi_LocationSetMonstersTime(&locations[n], 0, 24);

	Locations[n].items.randitem1 = "blade8";

	n = n + 1;


	return n;
}
