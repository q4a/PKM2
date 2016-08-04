#include "DIALOGS\Anacleto Rui Sa Pinto_dialog.h"

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
			
			dialog.text = DLG_TEXT[0];
			link.l1 = DLG_TEXT[1];
			link.l1.go = "exit";
			
			if (pchar.quest.main_line == "after_talk_with_douwesen_pirate" || pchar.quest.main_line == "to_douwesen_pirates" || pchar.quest.main_line == "after_speak_with_peasant")
			{
				dialog.snd = "Voice\ANRU\ANRU001";
				Dialog.Text = DLG_TEXT[2];
				Link.l1 = DLG_TEXT[3];
				Link.l1.go = "talk_in_tavern";
			}
			if (pchar.quest.main_line == "defeat_serrao")
			{
				dialog.snd = "Voice\ANRU\ANRU002";
				dialog.text = DLG_TEXT[4];
				link.l1 = DLG_TEXT[5];
				link.l1.go = "captain_4";
			}
			if (pchar.quest.main_line == "bad_swimming_in_oxbay")
			{
				dialog.snd = "Voice\ANRU\ANRU003";
				dialog.text = DLG_TEXT[6];
				link.l1 = DLG_TEXT[7];
				link.l1.go = "bad_swimming_in_oxbay";
			}
			NextDiag.TempNode = "first time";
		break;

		case "bad_swimming_in_oxbay":
			dialog.snd = "Voice\ANRU\ANRU004";
			dialog.text = DLG_TEXT[8];
			link.l1 = DLG_TEXT[9];
			link.l1.go = "bad_swimming_in_oxbay_2";
		break;

		case "bad_swimming_in_oxbay_2":
			dialog.snd = "Voice\ANRU\ANRU005";
			dialog.text = DLG_TEXT[10];
			link.l1 = DLG_TEXT[11];
			link.l1.go = "bad_swimming_in_oxbay_3";
		break;

		case "bad_swimming_in_oxbay_3":
			dialog.snd = "Voice\ANRU\ANRU006";
			dialog.text = DLG_TEXT[12];
			link.l1 = DLG_TEXT[13];
			link.l1.go = "bad_swimming_in_oxbay_4";
		break;

		case "bad_swimming_in_oxbay_4":
			if (GetCharacterSkill(pchar, SKILL_LEADERSHIP) > 5)
			{
				dialog.snd = "Voice\ANRU\ANRU007";
				dialog.text = DLG_TEXT[14];
				link.l1 = DLG_TEXT[15];
				link.l1.go = "bad_swimming_in_oxbay_good";
			}
			else
			{
				dialog.snd = "Voice\ANRU\ANRU008";
				dialog.text = DLG_TEXT[16];
				link.l1 = DLG_TEXT[17];
				link.l1.go = "bad_swimming_in_oxbay_bad";
			}
		break;

		case "bad_swimming_in_oxbay_good":
			dialog.snd = "Voice\ANRU\ANRU009";
			dialog.text = DLG_TEXT[18];
			link.l1 = DLG_TEXT[19];
			link.l1.go = "exit";
			AddDialogExitQuest("anacleto_rui_sa_pinto_bad_swimming_in_oxbay_good_2");
		break;

		case "bad_swimming_in_oxbay_bad":
			AddQuestrecord("Where_are_i", "10");
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("swimming_to_lighthouse");
		break;

		case "talk_in_tavern":
			dialog.snd = "Voice\ANRU\ANRU010";
			dialog.text = DLG_TEXT[20];
			link.l1 = DLG_TEXT[21];
			link.l1.go = "captain";
			link.l2 = DLG_TEXT[22];
			link.l2.go = "naezd";
			link.l3 = DLG_TEXT[23];
			link.l3.go = "friends";
		break;

		case "friends":
			dialog.snd = "Voice\ANRU\ANRU011";
			dialog.text = DLG_TEXT[24];
			link.l1 = DLG_TEXT[25];
			link.l1.go = "friends_exit";
		break;

		case "friends_exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.quest.main_line = "bad_swimming_in_oxbay";
			AddDialogExitQuest("bad_swimming_in_oxbay");
			AddQuestrecord("Where_are_i", "8");
		break;

		case "captain":
			dialog.snd = "Voice\ANRU\ANRU012";
			dialog.text = DLG_TEXT[26];
			link.l1 = DLG_TEXT[27];
			link.l1.go = "naezd";
			link.l2 = DLG_TEXT[28];
			link.l2.go = "captain_2";
		break;

		case "captain_2":
			dialog.snd = "Voice\ANRU\ANRU013";
			dialog.text = DLG_TEXT[29];
			link.l1 = DLG_TEXT[30];
			link.l1.go = "captain_3";
		break;

		case "captain_3":
			dialog.snd = "Voice\ANRU\ANRU014";
			dialog.text = DLG_TEXT[31] + characters[GetCharacterIndex(DLG_TEXT[32])].lastname + DLG_TEXT[33];
			link.l1 = DLG_TEXT[34];
			link.l1.go = "exit_captain";
			AddQuestrecord("Where_are_i", "4");
		break;

		case "captain_4":
			dialog.snd = "Voice\ANRU\ANRU015";
			dialog.text = DLG_TEXT[35];
			link.l1 = DLG_TEXT[36];
			link.l1.go = "captain5";
			link.l2 = DLG_TEXT[37];
			link.l2.go = "naezd";
			AddQuestrecord("Where_are_i", "5");
		break;

		case "captain5":
			dialog.snd = "Voice\ANRU\ANRU016";
			dialog.text = DLG_TEXT[38];
			link.l1 = DLG_TEXT[39];
			link.l1.go = "luck_exit";
			link.l2 = DLG_TEXT[40];
			link.l2.go = "naezd";
		break;

		case "naezd":
			dialog.snd = "Voice\ANRU\ANRU017";
			dialog.text = DLG_TEXT[41];
			link.l1 = DLG_TEXT[42];
			link.l1.go = "exit";
			AddQuestrecord("Where_are_i", "6");
			AddDialogExitQuest("anacleto_rui_sa_pinto_fight_exit");
		break;

		case "luck_exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("anacleto_rui_sa_pinto_luck_exit");
		break;

		case "exit_captain":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("anacleto_rui_sa_pinto_exit_captain");
		break;

		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
	}
}
