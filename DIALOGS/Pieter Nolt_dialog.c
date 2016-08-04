#include "DIALOGS\Pieter Nolt_dialog.h"

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
			Dialog.snd = "voice\PINO\PINO001";
			
			dialog.text = DLG_TEXT[0];
			link.l1 = DLG_TEXT[1];
			link.l1.go = "exit";

			if (pchar.quest.main_line == "blaze_to_incas_collection_begin_4" && makeint(pchar.reputation) >= 25)
			{
				Dialog.snd = "voice\PINO\PINO002";
				Dialog.Text = DLG_TEXT[2];
				Link.l1 = DLG_TEXT[3] + characters[GetCharacterIndex(DLG_TEXT[4])].name + " " + characters[GetCharacterIndex(DLG_TEXT[5])].lastname + DLG_TEXT[6];
				Link.l1.go = "denied";
			}
			if (pchar.quest.main_line == "blaze_to_incas_collection_begin_4" && makeint(pchar.reputation) < 25)
			{
				Dialog.snd = "voice\PINO\PINO003";
				dialog.text = DLG_TEXT[7] + pchar.name + " " + pchar.lastname + DLG_TEXT[8];
				link.l1 = DLG_TEXT[9];
				link.l1.go = "access";
			}
			if (pchar.quest.main_line == "to_douwesen_pirates" || pchar.quest.main_line == "after_speak_with_peasant")
			{

				link.l1 = DLG_TEXT[10];
				link.l1.go = "to_douwesen_pirates_2";
			}
			NextDiag.TempNode = "first time";
		break;

		case "to_douwesen_pirates_2":
			Dialog.snd = "voice\PINO\PINO004";
			dialog.text = DLG_TEXT[11] + characters[GetCharacterIndex(DLG_TEXT[12])].lastname + DLG_TEXT[13];
			link.l1 = DLG_TEXT[14] + characters[GetCharacterIndex(DLG_TEXT[15])].lastname + DLG_TEXT[16];
			link.l1.go = "to_douwesen_pirates_3";
		break;

		case "to_douwesen_pirates_3":
			Dialog.snd = "voice\PINO\PINO005";
			dialog.text = DLG_TEXT[17];
			link.l1 = DLG_TEXT[18];
			link.l1.go = "exit";
			pchar.quest.main_line = "after_talk_with_douwesen_pirate";
			AddQuestRecord("Where_are_i", "3");
		break;


		case "access":
			Dialog.snd = "voice\PINO\PINO006";
			AddQuestRecord("blaze_to_incas_collection", "6");
			dialog.text = DLG_TEXT[19];
			link.l1 = DLG_TEXT[20];
			link.l1.go = "exit";
			pchar.quest.main_line = "blaze_to_incas_collection_begin_5";
		break;

		case "denied":
			Dialog.snd = "voice\PINO\PINO007";
			Dialog.Text = DLG_TEXT[21];
			Link.l1 = DLG_TEXT[22];
			Link.l1.go = "denied_2";
		break;

		case "denied_2":
			Dialog.snd = "voice\PINO\PINO008";
			dialog.text = DLG_TEXT[23];
			link.l1 = DLG_TEXT[24];
			link.l1.go = "exit";
			AddDialogExitQuest("Pieter_nolt_fight");
		break;

		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
	}
}
