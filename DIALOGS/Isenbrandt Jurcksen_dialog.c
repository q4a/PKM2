#include "DIALOGS\Isenbrandt Jurcksen_dialog.h"

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
			Dialog.snd = "dialogs\0\009";

			NextDiag.TempNode = "first time";
			
			dialog.text = DLG_TEXT[0];
			link.l1 = DLG_TEXT[1];
			link.l1.go = "exit";

			if ( CheckQuestAttribute("story_FindRheims_IsenbrandtTask","pirate_arrest") )
			{
				AddDialogExitQuest("Herald_from_Redmond_comming_to_Isenbrandt");
				dialog.text = DLG_TEXT[2] + Characters[getCharacterIndex(DLG_TEXT[3])].lastname + DLG_TEXT[4];
				link.l1 = DLG_TEXT[5];
				link.l1.go = "AskingAboutRheims";
				PChar.quest.story_FindRheims_IsenbrandtTask = "neutral";
			}
			if ( CheckQuestAttribute("story_FindRheims_IsenbrandtTask","enemy") )
			{
				dialog.text = DLG_TEXT[6];
				link.l1 = DLG_TEXT[7];
				link.l1.go = "exit";
				AddDialogExitQuest("Herald_already_prevent_Isenbrandt");
			}


			if (pchar.quest.main_line == "letter_to_Isenbrandt")
			{
				if (makeint(pchar.reputation) > 60 || makeint(pchar.reputation) < 30)
				{
					dialog.text = pcharrepphrase(DLG_TEXT[8] + pchar.name + DLG_TEXT[9], DLG_TEXT[10] + pchar.name + DLG_TEXT[11]);
					link.l1 = pcharrepphrase(DLG_TEXT[12], DLG_TEXT[13]);
					link.l1.go = "node_2";
				}
				else
				{			
					dialog.text = DLG_TEXT[14];
					link.l1 = DLG_TEXT[15] + pchar.name + " " + pchar.lastname + DLG_TEXT[16];
					link.l1.go = "node_2";
				}
			}
		break;

		case "node_2":
			dialog.text = DLG_TEXT[17];
			link.l1 = DLG_TEXT[18];
			link.l1.go = "node_3";
		break;

		case "node_3":
			dialog.text = DLG_TEXT[19];
			link.l1 = DLG_TEXT[20] + characters[GetCharacterIndex(DLG_TEXT[21])].lastname + DLG_TEXT[22];
			link.l1.go = "node_4";
		break;

		case "node_4":
			dialog.text = characters[GetCharacterIndex(DLG_TEXT[23])].lastname + DLG_TEXT[24];
			link.l1 = DLG_TEXT[25];
			link.l1.go = "exit";
			characters[GetCharacterIndex("Robert Christopher Silehard")].dialog.CurrentNode = "letter_to_Isenbrandt_complete_node";
			pchar.quest.main_line = "letter_to_Isenbrandt_complete";
			AddQuestRecord("blaze_to_Isenbrandt", "2");
		break;

		case "AskingAboutRheims":
			dialog.text = DLG_TEXT[26];
			link.l1 = DLG_TEXT[27];
			link.l1.go = "AskingAboutRheims_1";		
		break;

		case "AskingAboutRheims_1":
			dialog.text = DLG_TEXT[28];
			link.l1 = DLG_TEXT[29];
			link.l1.go = "AskingAboutRheims_2";		
		break;

		case "AskingAboutRheims_2":
			dialog.text = DLG_TEXT[30];
			link.l1 = DLG_TEXT[31];
			link.l1.go = "AskingAboutRheims_3";		
		break;

		case "AskingAboutRheims_3":
			dialog.text = DLG_TEXT[32];
			link.l1 = DLG_TEXT[33];
			link.l1.go = "exit";		
		break;

		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
	}
}
