#include "DIALOGS\Mario Figuiera_dialog.h"

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
	int iTest;

	
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------������ ������ - ������ �������
		case "First time":
			Dialog.defAni = "dialog_stay1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "dialog_stay2";
			Dialog.cam = "1";
			Dialog.snd = "voice\MAFI\MAFI001";
			
			dialog.text = DLG_TEXT[0] + npchar.name + " " + npchar.lastname + DLG_TEXT[1];
			link.l1 = pcharrepphrase(DLG_TEXT[2] + pchar.name + " " + pchar.lastname + DLG_TEXT[3], DLG_TEXT[4] + pchar.name + " " + pchar.lastname + DLG_TEXT[5]);
			link.l1.go = "second time";
		
			NextDiag.TempNode = "second time";
		break;

		case "second time":
			Dialog.defAni = "dialog_stay1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "dialog_stay2";
			Dialog.cam = "1";
			Dialog.snd = "voice\MAFI\MAFI002";

			dialog.text = DLG_TEXT[6];
			link.l1 = DLG_TEXT[7];
			link.l1.go = "quests";
			link.l2 = pcharrepphrase(DLG_TEXT[8], DLG_TEXT[9]);
			link.l2.go = "crew";
			link.l2 = pcharrepphrase(DLG_TEXT[10], DLG_TEXT[11]);
			link.l2.go = "room";
			link.l4 = DLG_TEXT[12];
			link.l4.go = "exit";
		break;

		case "room":
			Dialog.snd = "voice\MAFI\MAFI003";
			dialog.text = DLG_TEXT[13];
			if (makeint(environment.time) >= 22.0 || makeint(environment.time) < 6.0)
			{

				link.l1 = DLG_TEXT[14];
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = DLG_TEXT[15];
				link.l1.go = "room_night";
			}
		break;

		case "room_day":
			Dialog.snd = "voice\MAFI\MAFI004";
			Dialog.text = DLG_TEXT[16];
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = DLG_TEXT[17];
				link.l1.go = "room_day_wait";
			}
			link.l2 = pcharrepphrase(DLG_TEXT[18], DLG_TEXT[19]);
			link.l2.go = "hall_day_wait";
			link.l3 = DLG_TEXT[20];
			link.l3.go = "second time";
		break;

		case "room_night":
			Dialog.snd = "voice\MAFI\MAFI005";
			Dialog.text = DLG_TEXT[21];
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = DLG_TEXT[22];
				link.l1.go = "room_night_wait";
			}
			link.l2 = pcharrepphrase(DLG_TEXT[23], DLG_TEXT[24]);
			link.l2.go = "hall_night_wait";
			link.l3 = DLG_TEXT[25];
			link.l3.go = "second time";
		break;

		case "room_night_wait":
			DialogExit();
			NextDiag.CurrentNode =  NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_pirate_tavern");
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
			AddDialogExitQuest("sleep_in_pirate_tavern");
			TavernWaitDate2("wait_day");
		break;

		case "hall_day_wait":
			DialogExit();
			NextDiag.CurrentNode =  NextDiag.TempNode;
			TavernWaitDate("wait_day");
		break;

		case "quests":
			itest = 0;
			Dialog.snd = "voice\MAFI\MAFI006";
			dialog.text = DLG_TEXT[26];
			link.l99 = DLG_TEXT[27];
			link.l99.go = "second time";
		break;

		case "crew":
			if (makeint(environment.time) <= 22.0 && makeint(environment.time) >= 6.0)
			{
				DialogExit();
				NextDiag.CurrentNode =  NextDiag.TempNode;
				launchhirecrew();
			}
			else
			{
				Dialog.snd = "voice\MAFI\MAFI007";
				dialog.text = DLG_TEXT[28];
				link.l1 = DLG_TEXT[29];
				link.l1.go = "room";
				link.l2 = DLG_TEXT[30];
				link.l2.go = "second time";
			}
		break;

		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
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
			Dialog.snd = "voice\MAFI\MAFI008";
			dialog.text = DLG_TEXT[31];
			link.l1 = DLG_TEXT[32];
			link.l1.go = "exit_sit";
		break;

		case "exit_sit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
	}
}
