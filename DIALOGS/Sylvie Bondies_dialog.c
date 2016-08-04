#include "DIALOGS\Sylvie Bondies_dialog.h"
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
	int iTest;

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
			Dialog.snd = "voice\SYBO001\SYBO001";

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// �������� ��������, ���� ������� ���� ��� ��������� �������, �� ����� �� ��� �������� ��� ��������, �� ��� ������ ������.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			Dialog.Text = DLG_TEXT[0] + Address_Form.Spa + DLG_TEXT[1];
			link.l1 = pcharrepphrase(DLG_TEXT[2], DLG_TEXT[3]);
			link.l1.go = "exit";
			if (characters[GetCharacterIndex("Sabine Matton")].quest.hire == "blaze_on_ship")
			{
				Dialog.snd = "voice\SYBO001\SYBO002";
				dialog.text = DLG_TEXT[4] + pchar.name + DLG_TEXT[5] + Characters[GetCharacterIndex(DLG_TEXT[6])].name + DLG_TEXT[7];
				link.l1 = pcharrepphrase(DLG_TEXT[8] + npchar.name + " " + npchar.lastname + DLG_TEXT[9] + Characters[GetCharacterIndex(DLG_TEXT[10])].name + DLG_TEXT[11], DLG_TEXT[12]);
				link.l1.go = "goddaughter";
				link.l2 = pcharrepphrase(DLG_TEXT[13] + Characters[GetCharacterIndex(DLG_TEXT[14])].name + DLG_TEXT[15], DLG_TEXT[16] + Characters[GetCharacterIndex(DLG_TEXT[17])].name + DLG_TEXT[18]);
				link.l2.go = "goddaughter_denied";
			}
			if (characters[GetCharacterIndex("Sabine Matton")].quest.hire == "captured_by_blaze")
			{
				Dialog.snd = "voice\SYBO001\SYBO003";
				dialog.text = DLG_TEXT[19];
				link.l1 = pcharrepphrase(DLG_TEXT[20], DLG_TEXT[21]);
				link.l1.go = "ransom";
			}
			NextDiag.TempNode = "First time";
		break;

		case "ransom":
			Dialog.snd = "voice\SYBO001\SYBO004";
			dialog.text = DLG_TEXT[22];
			link.l1 = pcharrepphrase(DLG_TEXT[23], DLG_TEXT[24]);
			link.l1.go = "ransom_1";
			link.l2 = pcharrepphrase(DLG_TEXT[25], DLG_TEXT[26] + Characters[GetCharacterIndex(DLG_TEXT[27])].name + DLG_TEXT[28]);
			link.l2.go = "ransom_free";
			link.l3 = pcharrepphrase(DLG_TEXT[29], DLG_TEXT[30]);
			link.l3.go = "exit";
		break;

		case "ransom_1":
			Dialog.snd = "voice\SYBO001\SYBO005";
			dialog.text = DLG_TEXT[31];
			link.l1 = pcharrepphrase(DLG_TEXT[32], DLG_TEXT[33]);
			link.l1.go = "ransom_2";
		break;

		case "ransom_2":
			Dialog.snd = "voice\SYBO001\SYBO006";
			dialog.text = DLG_TEXT[34];
			link.l1 = pcharrepphrase(DLG_TEXT[35], DLG_TEXT[36]);
			link.l1.go = "ransom_3";
			link.l2 = pcharrepphrase(DLG_TEXT[37] + Characters[GetCharacterIndex(DLG_TEXT[38])].name + DLG_TEXT[39], DLG_TEXT[40]);
			link.l2.go = "ransom_lie";
		break;

		case "ransom_3":
			Dialog.snd = "voice\SYBO001\SYBO007";
			dialog.text = DLG_TEXT[41];
			link.l1 = pcharrepphrase(DLG_TEXT[42], DLG_TEXT[43]);
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -1);
			characters[GetCharacterIndex("Sabine Matton")].quest.hire = "almost_done_ransom";
			AddMoneyToCharacter(pchar, 5000);
			characters[GetCharacterIndex("Sabine Matton")].location = "house_of_Stlvie_Bondies";
		break;

		case "ransom_lie":
			Dialog.snd = "voice\SYBO001\SYBO008";
			dialog.text = DLG_TEXT[44] + Address_Form.Spa + DLG_TEXT[45];
			link.l1 = pcharrepphrase(DLG_TEXT[46], DLG_TEXT[47]);
			link.l1.go = "ransom_lie_1";
		break;

		case "ransom_lie_1":
			Dialog.snd = "voice\SYBO001\SYBO009";
			dialog.text = DLG_TEXT[48];
			link.l1 = pcharrepphrase(DLG_TEXT[49], DLG_TEXT[50]);
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -1);
			characters[GetCharacterIndex("Sabine Matton")].quest.hire = "captured_by_blaze_again";
			AddMoneyToCharacter(pchar, 5000);
		break;

		case "ransom_free":
			Dialog.snd = "voice\SYBO001\SYBO010";
			dialog.text = DLG_TEXT[51] + Address_form.Spa + DLG_TEXT[52];
			link.l1 = pcharrepphrase(DLG_TEXT[53], DLG_TEXT[54]);
			link.l1.go = "ransom_free_wrong";
			link.l2 = pcharrepphrase(DLG_TEXT[55], DLG_TEXT[56]);
			link.l2.go = "ransom_free_right";
		break;

		case "ransom_free_wrong":
			Dialog.snd = "voice\SYBO001\SYBO011";
			dialog.text = DLG_TEXT[57];
			link.l1 = pcharrepphrase(DLG_TEXT[58], DLG_TEXT[59]);
			link.l1.go = "exit";
			characters[GetCharacterIndex("Sabine Matton")].quest.hire = "almost_done_ransom_free";
			ChangeCharacterReputation(pchar, -1);
		break;

		case "ransom_free_right":
			Dialog.snd = "voice\SYBO001\SYBO012";
			dialog.text = DLG_TEXT[60];
			link.l1 = pcharrepphrase(DLG_TEXT[61], DLG_TEXT[62]);
			link.l1.go = "exit";
			characters[GetCharacterIndex("Sabine Matton")].quest.hire = "almost_done";
			ChangeCharacterReputation(pchar, 1);
			AddPartyExp(pchar, 500);
		break;

		case "goddaughter_denied":
			Dialog.snd = "voice\SYBO001\SYBO013";
			dialog.text = DLG_TEXT[63];
			link.l1 = pcharrepphrase(DLG_TEXT[64], DLG_TEXT[65]);
			link.l1.go = pcharrepphrase("goddaughter_denied_1", "goddaughter_denied_2");
		break;

		case "goddaughter_denied_1":
			Dialog.snd = "voice\SYBO001\SYBO014";
			dialog.text = DLG_TEXT[66] + Address_Form.Spa + DLG_TEXT[67] + Characters[GetCharacterIndex(DLG_TEXT[68])].name + DLG_TEXT[69];
			link.l1 = DLG_TEXT[70];
			link.l1.go = "goddaughter_denied_confirm";
			link.l2 = DLG_TEXT[71];
			link.l2.go = "goddaughter";
		break;

		case "goddaughter_denied_confirm":
			Dialog.snd = "voice\SYBO001\SYBO015";
			dialog.text = DLG_TEXT[72] + Address_Form.Spa + DLG_TEXT[73];
			link.l1 = DLG_TEXT[74];
			link.l1.go = "exit";
			characters[GetCharacterIndex("Sabine Matton")].quest.hire = "captured_by_blaze";
			///////////////////////////////////////////
			// ������ ������ � ����������� �������
			///////////////////////////////////////////
			ChangeCharacterAddress(characterFromID("Sabine Matton"), "none", "none")
		break;

		case "goddaughter_denied_2":
			Dialog.snd = "voice\SYBO001\SYBO016";
			dialog.text = DLG_TEXT[75] + Address_form.Spa + DLG_TEXT[76];
			link.l1 = DLG_TEXT[77];
			link.l1.go = "goddaughter_denied_confirm_1";
		break;

		case "goddaughter_denied_confirm_1":
			Dialog.snd = "voice\SYBO001\SYBO017";
			dialog.text = DLG_TEXT[78];
			link.l1 = DLG_TEXT[79];
			link.l1.go = "exit";
			characters[GetCharacterIndex("Sabine Matton")].quest.hire = "captured_by_blaze";
			ChangeCharacterReputation(pchar, -3);
			///////////////////////////////////////////
			// ������ ������ � ����������� �������
			///////////////////////////////////////////
			ChangeCharacterAddress(characterFromID("Sabine Matton"), "none", "none")
		break;

		case "goddaughter":
			Dialog.snd = "voice\SYBO001\SYBO018";
			dialog.text = DLG_TEXT[80];
			link.l1 = pcharrepphrase(DLG_TEXT[81] + characters[GetCharacterIndex(DLG_TEXT[82])].name + DLG_TEXT[83], DLG_TEXT[84]);
			link.l1.go = pcharrepphrase("goddaughter_1", "goddaughter_2");
			RemovePassenger(pchar, Characters[GetCharacterIndex("Sabine Matton")]);
			ChangeCharacterAddress(characterFromID("Sabine Matton"), "house_of_sylvie_bondies", "locator4")
		break;

		case "goddaughter_1":
			Dialog.snd = "voice\SYBO001\SYBO019";
			dialog.text = DLG_TEXT[85] + characters[GetCharacterIndex(DLG_TEXT[86])].name + DLG_TEXT[87];
			link.l1 = pcharrepphrase(DLG_TEXT[88], DLG_TEXT[89]);
			link.l1.go = "exit";
			////////////////////////////////////////
			// ������ ������, �������� ����� ������
			////////////////////////////////////////
			ChangeCharacterReputation(pchar, 1);
			characters[GetCharacterIndex("Sabine Matton")].quest.hire = "almost_done";
			AddPartyExp(pchar, 700);
		break;

		case "goddaughter_2":
			Dialog.snd = "voice\SYBO001\SYBO020";
			dialog.text = DLG_TEXT[90];
			link.l1 = DLG_TEXT[91];
			link.l1.go = "goddaughter_1";
			AddMoneyToCharacter(pchar, 800);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
