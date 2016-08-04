#include "DIALOGS\Gervasio Serrao_dialog.h"

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
			Dialog.ani = "dialog_stay1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.cam = "1";
			
			dialog.snd = "Voice\GESE\GESE001";
			dialog.text = DLG_TEXT[0];
			if (pchar.quest.main_line == "after_defeat_Serrao")
			{
				dialog.snd = "Voice\GESE\GESE002";
				Dialog.Text = DLG_TEXT[1];
				Link.l1 = DLG_TEXT[2];
				Link.l1.go = "fight_again";
				link.l2 = DLG_TEXT[3];
				link.l2.go = "about_hire";
				pchar.quest.main_line = "defeat_serrao";
			}
			if (npchar.quest.hire == "wait")
			{
				dialog.snd = "Voice\GESE\GESE003";
				dialog.text = DLG_TEXT[4];
				link.l1 = DLG_TEXT[5];
				link.l1.go = "about_hire_4";
			}
			link.l99 = DLG_TEXT[6];
			link.l99.go = "exit";
			NextDiag.TempNode = "first time";
		break;

		case "about_hire":
			dialog.snd = "Voice\GESE\GESE004";
			Dialog.Text = DLG_TEXT[7];
			Link.l1 = DLG_TEXT[8];
			Link.l1.go = "fight_again";
			link.l2 = DLG_TEXT[9];
			link.l2.go = "about_hire_2";
		break;

		case "about_hire_2":
			dialog.snd = "Voice\GESE\GESE005";
			dialog.text = DLG_TEXT[10];
			link.l1 = DLG_TEXT[11];
			link.l1.go = "hire_denied";
			link.l2 = DLG_TEXT[12];
			link.l2.go = "about_hire_3";
		break;

		case "about_hire_3":
			dialog.snd = "Voice\GESE\GESE006";
			dialog.text = DLG_TEXT[13] + npchar.name + " " + npchar.lastname + DLG_TEXT[14];
			link.l1 = DLG_TEXT[15] + pchar.name + " " + pchar.lastname + DLG_TEXT[16];
			link.l1.go = "about_hire_4";
		break;

		case "about_hire_4":
			dialog.snd = "Voice\GESE\GESE007";
			dialog.text = DLG_TEXT[17];
			if (makeint(pchar.money) >=2000)
			{
				link.l1 = DLG_TEXT[18];
				link.l1.go = "hired_2";
			}
			link.l2 = DLG_TEXT[19];
			link.l2.go = "about_hire_5";
			link.l3 = DLG_TEXT[20];
			link.l3.go = "hire_denied";
		break;

		case "about_hire_5":
			if (getCharacterSkill(pchar, SKILL_LEADERSHIP) >= 5)
			{
				dialog.snd = "Voice\GESE\GESE008";
				dialog.text = DLG_TEXT[21];
				link.l1 = DLG_TEXT[22];
				link.l1.go = "hired";
			}
			else
			{
				dialog.snd = "Voice\GESE\GESE009";
				dialog.text = DLG_TEXT[23];
				link.l1 = DLG_TEXT[24];
				link.l1.go = "exit";
				AddDialogExitQuest("serrao_wait_for_hire");
				npchar.quest.hire = "wait";
			}
		break;

		case "hired":
			AddPassenger(pchar, npchar, -1);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			npchar.location = "none";
			npchar.quest.hire = "hired";
		break;
		
		case "hired_2":
			AddMoneyToCharacter(pchar, -2000);
			AddPassenger(pchar, npchar, -1);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			npchar.location = "none";
			npchar.quest.hire = "hired";
		break;

		case "hire_denied":
			dialog.snd = "Voice\GESE\GESE010";
			dialog.text = DLG_TEXT[25];
			npchar.quest.hire = "wait";
			link.l1 = DLG_TEXT[26];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT[27];
			link.l2.go = "fight_again";
		break;

		case "fight_again":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Gervasio_Serrao_fight_again");
		break;

		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
	}
}
