#include "DIALOGS\Ines Diaz_dialog.h"

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref PChar;
	PChar = GetMainCharacter();
	int iTest, iTime, iAddTime, NPC_meeting;

	
	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- ������ ������ - ������ �������
		case "First time":
			Dialog.defAni = "dialog_stay1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "dialog_stay2";
			Dialog.cam = "1";
			
			dialog.snd = "Voice\INDI\INDI001";
			Dialog.Text = DLG_TEXT[0] + npchar.name + DLG_TEXT[1];
			link.l1 = pcharrepphrase(DLG_TEXT[2] + npchar.name + DLG_TEXT[3], DLG_TEXT[4]);
			link.l1.go = "node_2";
			NextDiag.TempNode = "Second time";
		break;

		case "node_2":
			dialog.snd = pcharrepphrase("Voice\INDI\INDI002", "Voice\INDI\INDI003");
			dialog.text = pcharrepphrase(DLG_TEXT[5], DLG_TEXT[6]);
			link.l1 = pcharrepphrase(DLG_TEXT[7] + pchar.name + " " + pchar.lastname + DLG_TEXT[8], DLG_TEXT[9] + npchar.name + DLG_TEXT[10]);
			link.l1.go = "Second time";
		break;

		case "Second time":
			Dialog.defAni = "dialog_stay1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "dialog_stay2";
			Dialog.cam = "1";
			
			dialog.snd = "Voice\INDI\INDI004";
			dialog.text = DLG_TEXT[11];
			if(npchar.quest.about == "0")
			{
				link.l1 = DLG_TEXT[12];
				link.l1.go = "about";
			}
			link.l2 = DLG_TEXT[13];
			link.l2.go = "quests";
			link.l3 = DLG_TEXT[14];
			link.l3.go = "crew";
			link.l4 = pcharrepphrase(DLG_TEXT[15], DLG_TEXT[16]);
			link.l4.go = "room";
			link.l5 = DLG_TEXT[17];
			link.l5.go = "exit";

			NextDiag.TempNode = "Second time";
		break;

		// Nikita
		case "RheimsFind_1":
			dialog.snd = "Voice\INDI\INDI005";
			dialog.text = DLG_TEXT[18];
			link.l1 = DLG_TEXT[19];
			link.l1.go = "RheimsFind_2";			
		break;

		case "RheimsFind_2":
			dialog.snd = "Voice\INDI\INDI006";
			dialog.text = DLG_TEXT[20];
			link.l1 = DLG_TEXT[21];
			link.l1.go = "RheimsFind_3";			
		break;

		case "RheimsFind_3":
			dialog.snd = "Voice\INDI\INDI007";
			dialog.text = DLG_TEXT[22] + characters[GetCharacterIndex(DLG_TEXT[23])].name + " " + characters[GetCharacterIndex(DLG_TEXT[24])].lastname + DLG_TEXT[25];
			link.l1 = DLG_TEXT[26];
			link.l1.go = "exit";
			PChar.quest.RheimsBook = "1";//for Mosh d23
			AddQuestRecord("Story_Find_Rheims", "111");
		break;

		case "room":
			//Locations[FindLocation("Smugglers_Lair")].reload.l6.disable = 1;
			dialog.snd = "Voice\INDI\INDI008";
			dialog.text = DLG_TEXT[27];
			if (makeint(environment.time) >= 22.0 || makeint(environment.time) < 10.0)
			{

				link.l1 = DLG_TEXT[28];
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = DLG_TEXT[29];
				link.l1.go = "room_night";
			}
		break;

		case "room_day":
			dialog.snd = "Voice\INDI\INDI009";
			Dialog.text = DLG_TEXT[30];
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = DLG_TEXT[31];
				link.l1.go = "room_day_wait";
			}
			link.l2 = pcharrepphrase(DLG_TEXT[32], DLG_TEXT[33]);
			link.l2.go = "hall_day_wait";
			link.l3 = DLG_TEXT[34];
			link.l3.go = "second time";
		break;

		case "room_night":
			dialog.snd = "Voice\INDI\INDI010";
			Dialog.text = DLG_TEXT[35];
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = DLG_TEXT[36];
				link.l1.go = "room_night_wait";
			}
			link.l2 = pcharrepphrase(DLG_TEXT[37], DLG_TEXT[38]);
			link.l2.go = "hall_night_wait";
			link.l3 = DLG_TEXT[39];
			link.l3.go = "second time";
		break;

		case "room_night_wait":
			DialogExit();
			NextDiag.CurrentNode =  NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate2("wait_night");
		break;

		case "hall_night_wait":
			DialogExit();
			NextDiag.CurrentNode =  NextDiag.TempNode;
			TavernWaitDate("wait_night");
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode =  NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate2("wait_day");
		break;

		case "hall_day_wait":
			DialogExit();
			NextDiag.CurrentNode =  NextDiag.TempNode;
			TavernWaitDate("wait_day");
		break;

		case "about":
			dialog.snd = "Voice\INDI\INDI011";
			dialog.text = DLG_TEXT[40];
			link.l1 = pcharrepphrase(DLG_TEXT[41], DLG_TEXT[42]);
			link.l1.go = "about_2";
		break;

		case "about_2":
			dialog.snd = "Voice\INDI\INDI012";
			dialog.text = DLG_TEXT[43];
			link.l1 = DLG_TEXT[44];
			link.l1.go = "about_3";
		break;

		case "about_3":
			dialog.snd = "Voice\INDI\INDI013";
			dialog.text = DLG_TEXT[45];
			link.l1 = DLG_TEXT[46];
			link.l1.go = "about_4";
			link.l2 = DLG_TEXT[47];
			link.l2.go = "Second time";
		break;

		case "about_4":
			dialog.snd = "Voice\INDI\INDI014";
			dialog.text = DLG_TEXT[48];
			link.l1 = DLG_TEXT[49];
			link.l1.go = "about_5";
			link.l2 = DLG_TEXT[50];
			link.l2.go = "Second time";
		break;

		case "about_5":
			dialog.snd = "Voice\INDI\INDI015";
			dialog.text = DLG_TEXT[51];
			link.l1 = DLG_TEXT[52];
			link.l1.go = "about_6";
			link.l2 = DLG_TEXT[53];
			link.l2.go = "Second time";
		break;

		case "about_6":
			dialog.snd = "Voice\INDI\INDI016";
			dialog.text = DLG_TEXT[54];
			link.l1 = DLG_TEXT[55];
			link.l1.go = "about_7";
			link.l2 = DLG_TEXT[56];
			link.l2.go = "Second time";
		break;

		case "about_7":
			dialog.snd = "Voice\INDI\INDI017";
			dialog.text = DLG_TEXT[57];
			link.l1 = DLG_TEXT[58];
			link.l1.go = "about_8";
			link.l2 = DLG_TEXT[59];
			link.l2.go = "Second time";
		break;

		case "about_8":
			dialog.snd = "Voice\INDI\INDI018";
			dialog.text = DLG_TEXT[60];
			link.l1 = DLG_TEXT[61];
			link.l1.go = "about_9";
			link.l2 = DLG_TEXT[62];
			link.l2.go = "Second time";
		break;

		case "about_9":
			dialog.snd = "Voice\INDI\INDI019";
			dialog.text = DLG_TEXT[63];
			link.l1 = DLG_TEXT[64];
			link.l1.go = "about_10";
			link.l2 = DLG_TEXT[65];
			link.l2.go = "Second time";
		break;

		case "about_10":
			dialog.snd = "Voice\INDI\INDI020";
			dialog.text = DLG_TEXT[66];
			link.l1 = DLG_TEXT[67];
			link.l1.go = "about_11";
			link.l2 = DLG_TEXT[68];
			link.l2.go = "Second time";
		break;

		case "about_11":
			dialog.snd = "Voice\INDI\INDI021";
			dialog.text = DLG_TEXT[69];
			link.l1 = pcharrepphrase(DLG_TEXT[70], DLG_TEXT[71]);
			link.l1.go = "about_12";
			link.l2 = DLG_TEXT[72];
			link.l2.go = "Second time";
		break;

		case "about_12":
			dialog.snd = pcharrepphrase("Voice\INDI\INDI022", "Voice\INDI\INDI023");
			dialog.text = pcharrepphrase(DLG_TEXT[73], DLG_TEXT[74]);
			link.l1 = pcharrepphrase(DLG_TEXT[75], DLG_TEXT[76] + pchar.name + DLG_TEXT[77]);
			link.l1.go = "about_13";
			link.l2 = DLG_TEXT[78];
			link.l2.go = "Second time";
		break;

		case "about_13":
			dialog.snd = "Voice\INDI\INDI024";
			dialog.text = DLG_TEXT[79] + characters[GetcharacterIndex(DLG_TEXT[80])].name  + " " + characters[GetcharacterIndex(DLG_TEXT[81])].lastname + DLG_TEXT[82];
			link.l1 = DLG_TEXT[83] + characters[GetcharacterIndex(DLG_TEXT[84])].name + DLG_TEXT[85];
			link.l1.go = "about_14";
			link.l2 = DLG_TEXT[86];
			link.l2.go = "Second time";
		break;

		case "about_14":
			dialog.snd = "Voice\INDI\INDI025";
			dialog.text = DLG_TEXT[87];
			link.l1 = DLG_TEXT[88];
			link.l1.go = "about_15";
			link.l2 = DLG_TEXT[89];
			link.l2.go = "Second time";
		break;

		case "about_15":
			dialog.snd = "Voice\INDI\INDI026";
			dialog.text = DLG_TEXT[90];
			link.l1 = DLG_TEXT[91];
			link.l1.go = "about_16";
			link.l2 = DLG_TEXT[92];
			link.l2.go = "Second time";
		break;

		case "about_16":
			dialog.snd = "Voice\INDI\INDI027";
			dialog.text = DLG_TEXT[93];
			link.l1 = DLG_TEXT[94];
			link.l1.go = "about_17";
			link.l2 = DLG_TEXT[95];
			link.l2.go = "Second time";
		break;

		case "about_17":
			dialog.snd = "Voice\INDI\INDI028";
			dialog.text = DLG_TEXT[96];
			link.l1 = pcharrepphrase(DLG_TEXT[97], DLG_TEXT[98]);
			link.l1.go = "Second time";
			npchar.quest.about = "1";
		break;

		case "quests":
			iTest = 0;
			dialog.snd = "Voice\INDI\INDI029";
			dialog.text = DLG_TEXT[99];
			//�������� ������
			if (pchar.quest.main_line == "blaze_talk_with_silehard_complete" && iTest < QUEST_COUNTER)
			{
				link.l1 = DLG_TEXT[100] + characters[GetCharacterIndex(DLG_TEXT[101])].name + " " + characters[GetCharacterIndex(DLG_TEXT[102])].lastname + DLG_TEXT[103];
				link.l1.go = "blaze_search_rheims";
				iTest = iTest + 1;
			}
			if (CheckQuestAttribute("ANIMISTS", "to_qc"))
			{
				link.l1 = DLG_TEXT[104];
				link.l1.go = "ANIMISTS";
				iTest = iTest + 1;
			}
			link.l99 = DLG_TEXT[105];
			link.l99.go = "second time";
		break;

		case "ANIMISTS":
			dialog.snd = "Voice\INDI\INDI030";
			dialog.text = DLG_TEXT[106];
			link.l1 = pcharrepphrase(DLG_TEXT[107], DLG_TEXT[108]);
			link.l1.go = "ANIMISTS_1";
		break;

		case "ANIMISTS_1":
			dialog.snd = "Voice\INDI\INDI031";
			dialog.text = DLG_TEXT[109];
			link.l1 = DLG_TEXT[110];
			link.l1.go = "ANIMISTS_2";
		break;

		case "ANIMISTS_2":
			dialog.snd = "Voice\INDI\INDI032";
			dialog.text = DLG_TEXT[111];
			link.l1 = DLG_TEXT[112];
			link.l1.go = "exit";
			AddQuestRecord("ANIMISTS", "7");
			pchar.quest.ANIMISTS = "frigate_lost";
			ChangeCharacterAddressGroup(&characters[GetCharacterIndex("father Gareth")], "Redmond_church", "goto", "goto12");
		break;

		case "blaze_search_rheims":
			dialog.snd = "Voice\INDI\INDI033";
			dialog.text = DLG_TEXT[113];
			if (npchar.quest.rheims == "speak_with_humans")
			{
				link.l1 = DLG_TEXT[114];
				link.l1.go = "blaze_search_rheims_1";
			}
			else
			{
				link.l1 = DLG_TEXT[115];
				link.l1.go = "blaze_search_rheims_7";
			}
		break;

		case "blaze_search_rheims_1":
			dialog.snd = "Voice\INDI\INDI034";
			dialog.text = DLG_TEXT[116];
			link.l1 = DLG_TEXT[117];
			link.l1.go = "blaze_search_rheims_2";
		break;

		case "blaze_search_rheims_2":
			if (makeint(pchar.reputation) > 40 && GetCharacterSkill(pchar, SKILL_LEADERSHIP) > 4)
			{
				dialog.snd = "Voice\INDI\INDI035";
				dialog.text = DLG_TEXT[118];
				link.l1 = DLG_TEXT[119];
				link.l1.go = "blaze_search_rheims_3";
				link.l2 = DLG_TEXT[120];
				link.l2.go = "blaze_search_rheims_8";
			}
			else
			{
				dialog.snd = "Voice\INDI\INDI036";
				dialog.text = DLG_TEXT[121];
				link.l1 = pcharrepphrase(DLG_TEXT[122], DLG_TEXT[123]);
				link.l1.go = "ines_denied_exit";
			}
		break;

		case "blaze_search_rheims_3":
			dialog.snd = "Voice\INDI\INDI037";
			dialog.text = DLG_TEXT[124];
			link.l1 = DLG_TEXT[125];
			link.l1.go = "blaze_search_rheims_4";
		break;

		case "blaze_search_rheims_4":
			dialog.snd = "Voice\INDI\INDI038";
			dialog.text = DLG_TEXT[126] + characters[GetCharacterIndex(DLG_TEXT[127])].name + DLG_TEXT[128];
			link.l1 = DLG_TEXT[129];
			link.l1.go = "blaze_search_rheims_5";
		break;

		case "blaze_search_rheims_5":
			dialog.snd = "Voice\INDI\INDI039";
			dialog.text = DLG_TEXT[130];
			link.l1 = DLG_TEXT[131];
			link.l1.go = "blaze_search_rheims_6";
		break;

		case "blaze_search_rheims_6":
			dialog.snd = "Voice\INDI\INDI040";
			dialog.text = DLG_TEXT[132];
			link.l1 = DLG_TEXT[133];
			link.l1.go = "exit";
			pchar.quest.main_line = "blaze_talk_with_innes_diaz_complete";
			AddQuestRecord("Blaze_search_Rheims", "2");
		break;

		case "blaze_search_rheims_7":
			dialog.snd = "Voice\INDI\INDI041";
			dialog.text = DLG_TEXT[134];
			link.l1 = DLG_TEXT[135];
			link.l1.go = "ines_denied_exit";
		break;

		case "blaze_search_rheims_8":
			dialog.snd = "Voice\INDI\INDI042";
			dialog.text = DLG_TEXT[136];
			link.l1 = DLG_TEXT[137];
			link.l1.go = "blaze_search_rheims_9";
		break;

		case "blaze_search_rheims_9":
			if (GetCharacterSkill(pchar, SKILL_LEADERSHIP) > 5)
			{
				dialog.snd = "Voice\INDI\INDI043";
				dialog.text = DLG_TEXT[138];
				link.l1 = DLG_TEXT[139];
				link.l1.go = "blaze_search_rheims_6";
			}
			else
			{
				dialog.snd = "Voice\INDI\INDI044";
				dialog.text = DLG_TEXT[140];
				link.l1 = DLG_TEXT[141];
				link.l1.go = "blaze_search_rheims_10";
			}
		break;

		case "blaze_search_rheims_10":
			dialog.snd = "Voice\INDI\INDI045";
			dialog.text = DLG_TEXT[142];
			link.l1 = DLG_TEXT[143];
			link.l1.go = "ines_denied_exit";
		break;

		case "ines_denied_exit":
			AddQuestRecord("Blaze_search_Rheims", "3");
			DialogExit();
			NextDiag.CurrentNode =  NextDiag.TempNode;
			pchar.quest.main_line = "ines_info_denied";
			Locations[FindLocation("QC_town")].reload.l3.disable = 1;
			//�������� ����� �� ������, ������� ���� ���� � ������.
			pchar.quest.ines_denied_exit_from_tavern.win_condition.l1 = "location";
			pchar.quest.ines_denied_exit_from_tavern.win_condition.l1.location = "QC_town";
			pchar.quest.ines_denied_exit_from_tavern.win_condition = "ines_denied_exit_from_tavern_complete";
		break;

		case "crew":
			if (makeint(environment.time) <= 22.0 && makeint(environment.time) >= 10.0)
			{
				DialogExit();
				NextDiag.CurrentNode =  NextDiag.TempNode;
				launchhirecrew();
			}
			else
			{
				dialog.snd = "Voice\INDI\INDI046";
				dialog.text = DLG_TEXT[144];
				link.l1 = DLG_TEXT[145];
				link.l1.go = "room";
				link.l2 = DLG_TEXT[146];
				link.l2.go = "second time";
			}
		break;

		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "room":
			dialog.snd = "Voice\INDI\INDI047";
			dialog.text = DLG_TEXT[147];
			if (makeint(environment.time) >= 22.0 || makeint(environment.time) < 6.0)
			{

				link.l1 = DLG_TEXT[148];
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = DLG_TEXT[149];
				link.l1.go = "room_night";
			}
		break;

		case "room_day":
			dialog.snd = "Voice\INDI\INDI048";
			Dialog.text = DLG_TEXT[150];
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = DLG_TEXT[151];
				link.l1.go = "room_day_wait";
			}
			link.l2 = pcharrepphrase(DLG_TEXT[152], DLG_TEXT[153]);
			link.l2.go = "hall_day_wait";
			link.l3 = DLG_TEXT[154];
			link.l3.go = "second time";
		break;

		case "room_night":
			dialog.snd = "Voice\INDI\INDI049";
			Dialog.text = DLG_TEXT[155];
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = DLG_TEXT[156];
				link.l1.go = "room_night_wait";
			}
			link.l2 = pcharrepphrase(DLG_TEXT[157], DLG_TEXT[158]);
			link.l2.go = "hall_night_wait";
			link.l3 = DLG_TEXT[159];
			link.l3.go = "second time";
		break;

		case "room_night_wait":
			DialogExit();
			NextDiag.CurrentNode =  NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_conceicao_tavern");
			TavernWaitDate("wait_night");
		break;

		case "hall_night_wait":
			DialogExit();
			NextDiag.CurrentNode =  NextDiag.TempNode;
			TavernWaitDate("wait_night");
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode =  NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_conceicao_tavern");
			TavernWaitDate("wait_day");
		break;

		case "hall_day_wait":
			DialogExit();
			NextDiag.CurrentNode =  NextDiag.TempNode;
			TavernWaitDate("wait_day");
		break;

		case "tavern_keeper":
			NextDiag.TempNode = "second time";
			
			Dialog.defAni = "dialog_stay1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "dialog_stay2";
			Dialog.cam = "1";
			Dialog.snd = "dialogs\0\009";

			dialog.snd = "Voice\INDI\INDI050";
			dialog.text = DLG_TEXT[160];
			link.l1 = DLG_TEXT[161];
			link.l1.go = "exit_sit";
		break;

		case "exit_sit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
	}
}
