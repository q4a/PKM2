#include "DIALOGS\Miner_dialog.h"

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
			Dialog.snd = "voice\MIDI\MIDI001";
			
			dialog.text = DLG_TEXT[0];
			link.l1 = DLG_TEXT[1];
			link.l1.go = "exit";

			if (pchar.quest.main_line == "slave_in_oxbay_mine_begin")
			{
				Dialog.snd = "voice\MIDI\MIDI002";
				Dialog.Text = DLG_TEXT[2];
				Link.l1 = DLG_TEXT[3];
				Link.l1.go = "node_2";
			}
			NextDiag.TempNode = "first time";
		break;

		case "node_2":
			Dialog.snd = "voice\MIDI\MIDI003";
			dialog.text = DLG_TEXT[4];
			link.l1 = DLG_TEXT[5];
			link.l1.go = "node_3";
		break;

		case "node_3":
			Dialog.snd = "voice\MIDI\MIDI004";
			dialog.text = DLG_TEXT[6];
			link.l1 = DLG_TEXT[7];
			link.l1.go = "node_4";
		break;

		case "node_4":
			Dialog.snd = "voice\MIDI\MIDI005";
			dialog.text = DLG_TEXT[8];
			link.l1 = DLG_TEXT[9];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT[10];
			link.l2.go = "node_5";
		break;

		case "node_5":
			Dialog.snd = "voice\MIDI\MIDI006";
			dialog.text = DLG_TEXT[11];
			link.l1 = DLG_TEXT[12];
			link.l1.go = "again_kick_exit";
			AddDialogExitQuest("miner_again_kick_exit");
		break;

		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			//pchar.quest.main_line = "blaze_in_mine";
			//EndQuestMovie();
		break;
	}
}
