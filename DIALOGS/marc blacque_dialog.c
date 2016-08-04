#include "DIALOGS\marc blacque_dialog.h"
// object	Dialog;	declared in dialog.c
// ref		NPChar; declared in dialog.c
//#include "Dialogs\blaze_dialog_defines.c"

void ProcessDialogEvent()
{
	ref NPChar;
	
	DeleteAttribute(&Dialog,"Links");
	aref Link, NextDiag;
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
			Dialog.snd = "voice\MABL\MABL001";

			Dialog.Text = DLG_TEXT[0] + Address_Form.Eng + DLG_TEXT[1];
			Link.l1 = DLG_TEXT[2] + PChar.name + " " + PChar.lastname + DLG_TEXT[3];
			link.l1.go = "node_1";
			NextDiag.TempNode = "Second time";
		break;

		case "node_1":
			Dialog.snd = "voice\MABL\MABL002";
			Dialog.text = DLG_TEXT[4] + Address_Form.Eng + DLG_TEXT[5] + Characters[GetCharacterIndex(DLG_TEXT[6])].name + " " + Characters[GetCharacterIndex(DLG_TEXT[7])].lastname + DLG_TEXT[8];
			if (Characters[GetCharacterIndex("Milon Blacque")].quest.first_talk == "done")
			{
				Link.l1 = Characters[GetCharacterIndex(DLG_TEXT[9])].lastname + DLG_TEXT[10];
				Link.l1.go = "family_1";
			}
			else
			{
				link.l1 = DLG_TEXT[11];
				Link.l1.go = "exit";
			}
		break;

		case "family_1":
			Dialog.snd = "voice\MABL\MABL003";
			Dialog.text = DLG_TEXT[12];
			Link.l1 = DLG_TEXT[13];
			Link.l1.go = "family_2";
		break;

		case "family_2":
			Dialog.snd = "voice\MABL\MABL004";
			Dialog.text = DLG_TEXT[14] + Address_Form.Eng + DLG_TEXT[15];
			if (Characters[GetCharacterIndex("Rachel Blacque")].quest.badguy == "dead")
			{
				Link.l1 = DLG_TEXT[16];
				Link.l1.go = "dead_sister_1";
			}
			else
			{
				Link.l1 = DLG_TEXT[17];
				Link.l1.go = "family_3";
			}
		break;


		case "dead_sister_1":
			Dialog.snd = "voice\MABL\MABL005";
			Dialog.text = Characters[GetCharacterIndex(DLG_TEXT[18])].name + DLG_TEXT[19];
			link.l1 = DLG_TEXT[20];
			link.l1.go = "family_3";
			Characters[GetCharacterIndex("Rachel Blacque")].quest.badguy = "done";
		break;

		case "family_3":
			Dialog.snd = "voice\MABL\MABL006";
			Dialog.text = DLG_TEXT[21];
			link.l1 = DLG_TEXT[22];
			link.l1.go = "family_4";
		break;

		case "family_4":
			Dialog.snd = "voice\MABL\MABL007";
			Dialog.text = DLG_TEXT[23] + Address_Form.Eng + DLG_TEXT[24];
			link.l1 = DLG_TEXT[25];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT[26];
			link.l2.go = "story";
		break;

		case "story":
			Dialog.snd = "voice\MABL\MABL008";
			Dialog.text = DLG_TEXT[27];
			Link.l1 = DLG_TEXT[28];
			link.l1.go = "letter";
			Link.l2 = DLG_TEXT[29];
			Link.l2.go = "resque";
			Link.l3 = DLG_TEXT[30];
			link.l3.go = "exit";
		break;

		case "letter":
			Dialog.snd = "voice\MABL\MABL009";
			Dialog.text = DLG_TEXT[31];
			link.l1 = DLG_TEXT[32];
			link.l1.go = "letter_1";
			link.l2 = DLG_TEXT[33];
			link.l2.go = "letter_2";
		break;

		case "letter_1":
			Dialog.snd = "voice\MABL\MABL010";
			Characters[GetCharacterIndex("Milon Blacque")].quest.son = "letter";
			Dialog.text = DLG_TEXT[34];
			link.l1 = DLG_TEXT[35];
			link.l1.go = "exit";
		break;

		case "letter_2":
			Dialog.snd = "voice\MABL\MABL011";
			Dialog.text = DLG_TEXT[36];
			link.l1 = DLG_TEXT[37];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT[38];
			link.l2.go = "letter_1";
		break;

		case "resque":
			Dialog.snd = "voice\MABL\MABL012";
			Dialog.text = DLG_TEXT[39] + Address_Form.Eng + DLG_TEXT[40];
			Link.l1 = DLG_TEXT[41];
			Link.l1.go = "exit";
			if (makeint(PChar.money) > 2500)
			{
				Link.l2 = DLG_TEXT[42];
				link.l2.go = "resque_1";
			}
		break;

		case "resque_1":
			Dialog.snd = "voice\MABL\MABL013";
			Dialog.text = DLG_TEXT[43];
			Link.l1 = DLG_TEXT[44];
			link.l1.go = "resque_2";
		break;

		case "resque_2":
			Dialog.snd = "voice\MABL\MABL014";
			Dialog.Text = DLG_TEXT[45];
			Link.l1 = DLG_TEXT[46];
			Link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 500);
			Characters[GetCharacterIndex("Milon Blacque")].quest.son = "2";
		break;

		case "Second time":
			if (Characters[GetCharacterIndex("Milon Blacque")].quest.son == "2")
			{
				Dialog.snd = "voice\MABL\MABL015";
				Dialog.text = TimeGreeting() + DLG_TEXT[47] PChar.name + " " + PChar.lastname + DLG_TEXT[48];
				Link.l1 = DLG_TEXT[49];
				link.l1.go = "exit";
			}
			else 
			{
				if (Characters[GetCharacterIndex("Milon Blacque")].quest.son == "money")
				{
					Dialog.snd = "voice\MABL\MABL016";
					Dialog.text = TimeGreeting() + DLG_TEXT[50] PChar.name + " " + PChar.lastname + DLG_TEXT[51];
					Link.l1 = DLG_TEXT[52];
					link.l1.go = "lie";
				}
				if (Characters[GetCharacterIndex("Milon Blacque")].quest.son == "money_done")
				{
					Dialog.snd = "voice\MABL\MABL017";
					Dialog.text = TimeGreeting() + DLG_TEXT[53] + PChar.name + " " + PChar.lastname + DLG_TEXT[54];
					Link.l2 = DLG_TEXT[55] + PChar.ship.name + DLG_TEXT[56];
					Link.l2.go = "exit2";
				}
				else
				{
					if (Characters[GetCharacterIndex("Milon Blacque")].quest.son == "letter_return")
					{
						Dialog.snd = "voice\MABL\MABL018";
						Dialog.text = TimeGreeting() + " " + Address_Form.Eng + DLG_TEXT[57];
						Link.l1 = DLG_TEXT[58];
						link.l1.go = "letter_return";
					}
					else
					{
						Dialog.snd = "voice\MABL\MABL019";
						Dialog.text = TimeGreeting() + " " + Address_Form.Eng + DLG_TEXT[59];
						link.l1 = DLG_TEXT[60];
						link.l1.go = "exit";
						if (Characters[GetCharacterIndex("Milon Blacque")].quest.son  == "0")
						{
							Link.l2 = DLG_TEXT[61];
							Link.l2.go = "letter";
							Link.l3 = DLG_TEXT[62];
							Link.l3.go = "resque";
						}
					}
				}
				if (Characters[GetCharacterIndex("Milon Blacque")].quest.son == "done")
				{
					Dialog.snd1 = "voice\MABL\MABL020";
					Dialog.snd2 = "voice\MABL\MABL021";
					Dialog.snd3 = "voice\MABL\MABL022";
					Dialog.text = randphrase(DLG_TEXT[63] + Address_Form.Eng + DLG_TEXT[64], DLG_TEXT[65] + Address_Form.Eng + DLG_TEXT[66], DLG_TEXT[67] + Address_Form.Fra + DLG_TEXT[68], &Dialog, Dialog.snd1, Dialog.snd2, Dialog.snd3);
					link.l1 = DLG_TEXT[69];
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "Second time";
		break;

		case "lie":
			Dialog.snd = "voice\MABL\MABL023";
			Dialog.text = DLG_TEXT[70];
			link.l1 = DLG_TEXT[71];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT[72];
			link.l2.go = "lie_2";
		break;

		case "letter_return":
			Dialog.snd = "voice\MABL\MABL024";
			Dialog.text = DLG_TEXT[73];
			ChangeCharacterReputation(pchar, 1);
			AddPartyExp(pchar, 1000)
			link.l1 = DLG_TEXT[74];
			link.l1.go = "exit";
			Link.l2 = DLG_TEXT[75];
			Link.l2.go = "resque";
		break;

		case "lie_2":
			Dialog.snd = "voice\MABL\MABL025";
			Dialog.text = DLG_TEXT[76];
			link.l1 = DLG_TEXT[77];
			link.l1.go = "exit";
			Characters[GetCharacterIndex("Milon Blacque")].quest.son = "done";
			ChangeCharacterReputation(pchar, -1);
		break;
					
		case "Exit2":
			Characters[GetCharacterIndex("Milon Blacque")].quest.son = "rescue";
			AddPassenger(pchar, npchar, 0);
			npchar.location = "none";
			DialogExit();
			NextDiag.CurrentNode =  NextDiag.TempNode;
		break;

		case "Exit":
			DialogExit();
			NextDiag.CurrentNode =  NextDiag.TempNode;
		break;
	}
}
