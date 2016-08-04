#include "DIALOGS\Jaoquin de masse_dialog.h"
	
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
			
			dialog.text = DLG_TEXT[0];
			link.l1 = DLG_TEXT[1];
			link.l1.go = "exit";

			if (CheckQuestAttribute("ANIMISTS", "first_time_Masse"))
			{
				dialog.text = DLG_TEXT[2];
				link.l1 = DLG_TEXT[3];
				link.l1.go = "first_time_Masse";
			}
// boal -->
			//if (CheckQuestAttribute("ANIMISTS", "to_prison_for_teacher"))
			//{
			//	dialog.text = DLG_TEXT[4];
			//	link.l1 = DLG_TEXT[5];
			//	link.l1.go = "exit";
			//	pchar.quest.ANIMISTS = "raskainye";
			//	AddDialogExitQuest("to_greenford_prison");
			//}
// boal <--
		break;

		case "first_time_Masse":
			dialog.text = DLG_TEXT[6] + address_form.eng + DLG_TEXT[7];
			link.l1 = DLG_TEXT[8];
			link.l1.go = "first_time_Masse_2":
		break;

		case "first_time_Masse_2":
			dialog.text = DLG_TEXT[9];
			link.l1 = DLG_TEXT[10];
			link.l1.go = "first_time_Masse_3";
		break;

		case "first_time_Masse_3":
			dialog.text = DLG_TEXT[11] + GetCharacterFullName(npchar.id) + DLG_TEXT[12];
			link.l1 = DLG_TEXT[13];
			link.l1.go = "first_time_Masse_4";
		break;

		case "first_time_Masse_4":
			dialog.text = DLG_TEXT[14];
			link.l1 = DLG_TEXT[15];
			link.l1.go = "first_time_Masse_5":
		break;

		case "first_time_Masse_5":
			dialog.text = DLG_TEXT[16];
			link.l1 = DLG_TEXT[17];
			link.l1.go = "exit";
			AddDialogExitQuest("masse_becomes_officer");
			pchar.quest.ANIMISTS = "to_muelle_for_rumors";
		break;
			
		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
	}
}
