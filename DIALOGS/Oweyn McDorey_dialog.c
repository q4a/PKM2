#include "DIALOGS\Oweyn McDorey_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar, PChar, d;
	PChar = GetMainCharacter();
	aref Link, Diag;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);

	string iDay, iMonth;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;
	
	switch(Dialog.CurrentNode)
	{

		// -----------------------------------������ ������ - ������ �������
		case "First time":
			Dialog.defAni = "Gov_Dialog_1";
			Dialog.ani = "Gov_Dialog_2";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.cam = "1";
			
			if(NPChar.quest.meeting == "0")
			{
				Dialog.snd = "voice\OWMC\OWMC001";
				d.Text = TimeGreeting() + DLG_TEXT[0] + NPChar.name + " " + NPChar.lastname + DLG_TEXT[1];
				Link.l1 = DLG_TEXT[2] + Pchar.name + " " + Pchar.lastname + DLG_TEXT[3] + PChar.Ship.name + DLG_TEXT[4];
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1"; 
			}
			else
			{
				Dialog.snd = "voice\OWMC\OWMC002";
				d.Text = TimeGreeting() + DLG_TEXT[5] + PChar.name + DLG_TEXT[6] + address_form.eng + DLG_TEXT[7];
				Link.l1 = DLG_TEXT[8];
				if(CheckAttribute(Pchar, "Quest.Story_OxbayCaptured"))
				{
					Link.l1.go = "No ships";
				}
				else
				{
					Link.l1.go = "Shipyard";
				}
				Link.l2 = DLG_TEXT[9];
				Link.l2.go = "quest lines";
				Link.l3 = DLG_TEXT[10];
				Link.l3.go = "exit";
			}
		break;

		case "Meeting":
				Dialog.snd = "voice\OWMC\OWMC003";
				d.Text = DLG_TEXT[11];
				Link.l1 = DLG_TEXT[12] + NPChar.name +DLG_TEXT[13];
				if(CheckAttribute(Pchar, "Quest.Story_OxbayCaptured"))
				{
					Link.l1.go = "No ships";
				}
				else
				{
					Link.l1.go = "Shipyard";
				}			
				Link.l2 = DLG_TEXT[14];
				Link.l2.go = "quest lines";
				Link.l3 = DLG_TEXT[15];
				Link.l3.go = "exit";
		break;

		case "quest lines":
				Dialog.snd = "voice\OWMC\OWMC004";
				d.Text = DLG_TEXT[16] + PChar.name + DLG_TEXT[17];
				Link.l1 = DLG_TEXT[18];
				Link.l1.go = "no quest";
				
				if(CheckQuestAttribute("Story_CursedCoins", "TalkToMcDorey"))
				{
				
					Link.l2 = DLG_TEXT[19];
					Link.l2.go = "Story_chest";
				}
							

		break;

		case "No quest":
				Dialog.snd = "voice\OWMC\OWMC005";
				d.Text = DLG_TEXT[20] + PChar.name + DLG_TEXT[21];
				Link.l1 = DLG_TEXT[22];
				if(CheckAttribute(Pchar, "Quest.Story_OxbayCaptured"))
				{
					Link.l1.go = "No ships";
				}
				else
				{
					Link.l1.go = "Shipyard";
				}			
				Link.l2 = DLG_TEXT[23];
				Link.l2.go = "exit";
		break;

		case "shipyard":
				Dialog.snd = "voice\OWMC\OWMC006";
				d.Text = DLG_TEXT[24];
				Link.l1 = DLG_TEXT[25];
				Link.l1.go = "SHIPYARD_interface";
				Link.l2 = DLG_TEXT[26];
				Link.l2.go = "Cannons_interface";
				Link.l3 = DLG_TEXT[27];
				Link.l3.go = "no quest";
		break;

		case "No ships":
				Dialog.snd = "voice\OWMC\OWMC007";
				d.Text = DLG_TEXT[28] + Address_form.eng + DLG_TEXT[29];
				Link.l1 = DLG_TEXT[30];
				Link.l1.go = "no Quest";
		break;

		case "Blaze and Counterspy":
				Dialog.snd = "voice\OWMC\OWMC008";
				CharacterTurnByChr(&Characters[getCharacterIndex("Counterspy")], &Characters[getCharacterIndex("Oweyn MCDorey")]);
				d.Text = DLG_TEXT[31];
				Link.l1 = DLG_TEXT[32];
				Link.l1.go = "Blaze and Counterspy_1";
		break;

		case "Blaze and Counterspy_1":
				Dialog.snd = "voice\OWMC\OWMC009";
				d.Text = DLG_TEXT[33];
				Link.l1 = DLG_TEXT[34];
				Link.l1.go = "Blaze and Counterspy_2";
		break;

		case "Blaze and Counterspy_2":
			Dialog.snd = "voice\OWMC\OWMC010";
			d.Text = DLG_TEXT[35];
			Link.l1 = DLG_TEXT[36];
			Link.l1.go = "exit";
			AddDialogExitQuest("Blaze_and_Counterspy_exit_from_shipyard");
		break;

		case "Soldiers left":
			Dialog.snd = "voice\OWMC\OWMC011";
			d.Text = DLG_TEXT[37];
			Link.l1 = DLG_TEXT[38] + Characters[GetCharacterIndex(DLG_TEXT[39])].name + DLG_TEXT[40];
			Link.l1.go = "Soldiers left_1";
		break;

		case "Soldiers left_1":
			Dialog.snd = "voice\OWMC\OWMC012";
			d.Text = DLG_TEXT[41];
			Link.l1 = DLG_TEXT[42];
			Link.l1.go = "Soldiers left_2";
		break;

		case "Soldiers left_2":
			Dialog.snd = "voice\OWMC\OWMC013";
			d.Text = DLG_TEXT[43];
			Link.l1 = DLG_TEXT[44];
			Link.l1.go = "Soldiers left_3";
		break;

		case "Soldiers left_3":
			AddDialogExitQuest("Story_CursedCoinsStarted");
			Dialog.snd = "voice\OWMC\OWMC014";

			d.Text = DLG_TEXT[45] + address_form.eng + DLG_TEXT[46];
			Link.l1 = DLG_TEXT[47];
			Link.l1.go = "Soldiers left_4";
		break;

		case "Soldiers left_4":
			Dialog.snd = "voice\OWMC\OWMC015";
			d.Text = DLG_TEXT[48] + Characters[GetCharacterIndex(DLG_TEXT[49])].name + DLG_TEXT[50] + Characters[GetCharacterIndex(DLG_TEXT[51])].lastname + DLG_TEXT[52] + Pchar.name + DLG_TEXT[53];
			Link.l1 = DLG_TEXT[54];
			Link.l1.go = "exit";
			AddDialogexitQuest("Story_AfterHiddenInShipyardWatch");
			SetQuestHeader("chest");
			AddQuestRecord("chest", "1");
		break;

		case "Story_Chest":
			Dialog.snd = "voice\OWMC\OWMC017";
			d.Text = DLG_TEXT[55];
			Link.l1 = DLG_TEXT[56];
			Link.l1.go = "Story_Chest_1";			
		break;

		case "Story_Chest_1":
			Dialog.snd = "voice\OWMC\OWMC018";
			d.Text = DLG_TEXT[57];
			Link.l1 = DLG_TEXT[58];
			Link.l1.go = "Story_Chest_2";			
		break;

		case "Story_Chest_2":
			Dialog.snd = "voice\OWMC\OWMC019";
			d.Text = DLG_TEXT[59];
			Link.l1 = DLG_TEXT[60];
			Link.l1.go = "Story_Chest_3";			
		break;

		case "Story_Chest_3":
			Dialog.snd = "voice\OWMC\OWMC020";
			d.Text = DLG_TEXT[61];
			Link.l1 = DLG_TEXT[62];
			Link.l1.go = "Story_Chest_4";			
		break;

		case "Story_Chest_4":
			Dialog.snd = "voice\OWMC\OWMC021";
			d.Text = DLG_TEXT[63];
			Link.l1 = DLG_TEXT[64];
			Link.l1.go = "Story_Chest_5";			
		break;

		case "Story_Chest_5":
			Dialog.snd = "voice\OWMC\OWMC022";
			d.Text = DLG_TEXT[65] + Characters[GetCharacterIndex(DLG_TEXT[66])].name + DLG_TEXT[67];
			Link.l1 = DLG_TEXT[68];
			Link.l1.go = "Story_Chest_6";			
		break;

		case "Story_Chest_6":
			Dialog.snd = "voice\OWMC\OWMC023";
			d.Text = DLG_TEXT[69];
			Link.l1 = DLG_TEXT[70];
			Link.l1.go = "Story_Chest_7";			
		break;

		case "Story_Chest_7":
			DeleteAttribute(Pchar, "quest.Story_CursedCoins");

			Pchar.quest.Seen_Black_Pearl.win_condition.l1 = "location";
			Pchar.quest.Seen_Black_Pearl.win_condition.l1.location = "FalaiseDeFleur";
			Pchar.quest.Seen_Black_Pearl.win_condition = "Seen_Black_Pearl";

			Dialog.snd = "voice\OWMC\OWMC024";
		
			d.Text = DLG_TEXT[71];
			Link.l1 = DLG_TEXT[72];
			Link.l1.go = "exit";			
			AddQuestRecord("chest", "5");
			ChangeCharacterAddressGroup(CharacterFromID("Henry Peat"), "HouseInsideR20", "sit", "sit1");
		break;


		case "SHIPYARD_interface":
			Diag.CurrentNode = Diag.TempNode;

			if (npchar.quest.Meeting != lastspeak_date)
			{
				int iTest_ship;

				DeleteAttribute(npchar, "shipyard");
			
				npchar.shipyard.ship1 = SHIP_TARTANE;

				iTest_ship = rand(2);
				if (iTest_ship == 1)
				{
					npchar.shipyard.ship2 = SHIP_BARQUE_ENGLAND;
				}
				if (iTest_ship == 2) 
				{
					npchar.shipyard.ship2 = SHIP_BARQUE2_ENGLAND;
				}

				iTest_ship = rand(2);
				if (iTest_ship == 1) npchar.shipyard.ship3 = SHIP_YACHT_ENGLAND;
				if (iTest_ship == 2) npchar.shipyard.ship3 = SHIP_YACHT2_ENGLAND;
				
				iTest_ship = rand(2);
				if (iTest_ship == 1) npchar.shipyard.ship4 = SHIP_LUGGER_ENGLAND;
				if (iTest_ship == 2) npchar.shipyard.ship4 = SHIP_LUGGER2_ENGLAND;

				iTest_ship = rand(3);
				if (iTest_ship == 1) npchar.shipyard.ship5 = SHIP_SLOOP_ENGLAND;
				if (iTest_ship == 2) npchar.shipyard.ship5 = SHIP_SLOOP2_ENGLAND;
				
				iTest_ship = rand(3);
				if (iTest_ship == 1) npchar.shipyard.ship6 = SHIP_GALEOTH_ENGLAND;
				if (iTest_ship == 2) npchar.shipyard.ship6 = SHIP_GALEOTH2_ENGLAND;
		
				iTest_ship = rand(3);
				if (iTest_ship == 1) npchar.shipyard.ship7 = SHIP_XEBEC_ENGLAND;
				if (iTest_ship == 2)npchar.shipyard.ship7 = SHIP_XEBEC2_ENGLAND;
				
				iTest_ship = rand(4);
				if (iTest_ship == 1) npchar.shipyard.ship8 = SHIP_SCHOONER_ENGLAND;
				if (iTest_ship == 2) npchar.shipyard.ship8 = SHIP_SCHOONER2_ENGLAND;
				
				iTest_ship = rand(4);
				if (iTest_ship == 1) npchar.shipyard.ship9 = SHIP_CARAVEL_ENGLAND;
				if (iTest_ship == 2) npchar.shipyard.ship9 = SHIP_CARAVEL2_ENGLAND;
				
				iTest_ship = rand(4);
				if (iTest_ship == 1) npchar.shipyard.ship10 = SHIP_FLEUT_ENGLAND;
				if (iTest_ship == 2) npchar.shipyard.ship10 = SHIP_FLEUT2_ENGLAND;
				
				iTest_ship = rand(5);
				if (iTest_ship == 1) npchar.shipyard.ship11 = SHIP_PINNACE_ENGLAND;
				if (iTest_ship == 2) npchar.shipyard.ship11 = SHIP_PINNACE2_ENGLAND;
				
				iTest_ship = rand(5);
				if (iTest_ship == 1) npchar.shipyard.ship12 = SHIP_BRIG_ENGLAND;
				if (iTest_ship == 2) npchar.shipyard.ship12 = SHIP_BRIG2_ENGLAND;
				
				iTest_ship = rand(5);
				if (iTest_ship == 1) npchar.shipyard.ship13 = SHIP_GALEON_ENGLAND;
				if (iTest_ship == 2) npchar.shipyard.ship13 = SHIP_GALEON2_ENGLAND;

				npchar.quest.Meeting = lastspeak_date;
			}
		
			DialogExit();
			LaunchShipyard(Npchar);
		break;

		case "CANNONS_interface":
			Diag.CurrentNode = Diag.TempNode;			
			DialogExit();
			LaunchCannons();
		break;

		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
	}
}