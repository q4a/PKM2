#include "DIALOGS\anacleto_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar, PChar, d;
	PChar = GetMainCharacter();
	aref Link, Diag;
	string NPC_Meeting;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			Dialog.defAni = "dialog_stay1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "dialog_stay2";
			Dialog.cam = "1";
			
			dialog.snd = "Voice\ANAC\ANAC001";
			dialog.text = DLG_TEXT[0];
			link.l1 = DLG_TEXT[1];
			link.l1.go = "node_2";
		break;
		
		case "node_2":
			dialog.snd = "Voice\ANAC\ANAC002";
			dialog.text = DLG_TEXT[2];
			link.l1 = DLG_TEXT[3];
			link.l1.go = "exit";
		break;
		
		case "ask_about_artois":
			dialog.snd = "Voice\ANAC\ANAC003";
			dialog.text = DLG_TEXT[4];
			link.l1 = DLG_TEXT[5];
			link.l1.go = "exit";
			AddDialogExitQuest("Blaze_cop_dialog");
		break;
		
		case "artois_lay":
			dialog.snd = "Voice\ANAC\ANAC004";
			dialog.text = DLG_TEXT[6];
			link.l1 = DLG_TEXT[7];
			link.l1.go = "artois_lay_2";
		break;
		
		case "artois_lay_2":
			dialog.snd = "Voice\ANAC\ANAC005";
			dialog.text = DLG_TEXT[8];
			link.l1 = DLG_TEXT[9];
			link.l1.go = "exit";
			AddDialogExitQuest("fight_for_artois_with_child_of_giens");
		break;
		
		case "doctor":
			dialog.snd = "Voice\ANAC\ANAC006";
			dialog.text = DLG_TEXT[10];
			link.l1 = DLG_TEXT[11];
			link.l1.go = "doctor_2";
		break;
		
		case "doctor_2":
			dialog.snd = "Voice\ANAC\ANAC007";
			dialog.text = DLG_TEXT[12];
			if (makeint(pchar.money)>=2000)
			{
				link.l1 = DLG_TEXT[13];
				link.l1.go = "doctor_3";
			}
			link.l2 = DLG_TEXT[14];
			link.l2.go = "exit_doctor_bad";
		break;
		
		case "doctor_3":
			dialog.snd = "Voice\ANAC\ANAC008";
			dialog.text = DLG_TEXT[15];
			link.l1 = DLG_TEXT[16];
			link.l1.go = "exit_doctor_good";
			link.l2 = DLG_TEXT[17];
			link.l2.go = "exit_doctor_bad";
		break;
		
		case "exit_doctor_good":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_doctor_good");
		break;
		
		case "remove":
			if (npchar.alignment == "good")
			{
				dialog.snd = "Voice\ANAC\ANAC009";
				dialog.text = DLG_TEXT[18];
				link.l1 = DLG_TEXT[19];
			}
			else
			{
				dialog.snd = "Voice\ANAC\ANAC010";
				dialog.text = DLG_TEXT[20];
				link.l1 = DLG_TEXT[21];
			}
			link.l1.go = "exit";
			pchar.removed_officer = GetCharacterIndex(npchar.id);
			AddDialogExitQuest("removed_officer_runaway");
			npchar.location = npchar.homelocation;
			npchar.location.group = npchar.homelocation.group;
			npchar.location.locator = npchar.homelocation.locator;
		break;
		
		case "hired_again":
			dialog.snd = "Voice\ANAC\ANAC011";
			dialog.text = DLG_TEXT[22];
			link.l1 = DLG_TEXT[23];
			link.l1.go = "hired_again_2";
		break;
		
		case "hired_again_2":
			dialog.snd = "Voice\ANAC\ANAC012";
			dialog.text = DLG_TEXT[24];
			link.l1 = DLG_TEXT[25];
			link.l1.go = "exit";
			AddPassenger(Pchar, npchar, 0);
			npchar.loyality = 1;
			npchar.dialog.filename = npchar.selfdialog.filename;
			npchar.dialog.currentnode = npchar.selfdialog.currentnode;
		break;
		
		case "exit_doctor_bad":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_doctor_bad");
		break;

		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "prepare_convoy_quest":
			dialog.text = DLG_TEXT[26];
			link.l1 = DLG_TEXT[27];
			link.l1.go = "prepare_convoy_quest_2";
		break;
		
		case "prepare_convoy_quest_2":
			dialog.text = DLG_TEXT[28];
			link.l1 = DLG_TEXT[29];
			link.l1.go = "prepare_convoy_quest_3";
		break;
		
		case "prepare_convoy_quest_3":
			/*Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("prepare_gen_convoy_quest");
		break;
		
		case "prepare_convoy_quest_4":*/
			GenerateConvoyQuest();
			dialog.text = DLG_TEXT[30] + pchar.quest.destination + DLG_TEXT[31] + pchar.quest.convoymoney + DLG_TEXT[32];
			link.l1 = DLG_TEXT[33];
			link.l1.go = "convoy_agreeded";
			link.l2 = DLG_TEXT[34];
			link.l2.go = "convoy_refused";
		break;
		
		case "convoy_refused":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("convoy_refused");
		break;
		
		case "convoy_agreeded":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("convoy_agreeded");
		break;
		
		case "complete_convoy_quest":
			dialog.text = DLG_TEXT[35];
			Link.l1 = DLG_TEXT[36];
			link.l1.go = "exit";
			AddDialogExitQuest("convoy_refused");
		break;
	}
} 