#include "DIALOGS\Tancrede Rimbaud_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar, PChar, d;
	PChar = GetMainCharacter();
	aref Link, Diag;
	string NPC_meeting;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------������ ������ - ������ �������

		case "Exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "First time":
			Dialog.defAni = "dialog_stay1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "dialog_stay2";
			Dialog.snd = "voice\TARI\TARI001";
			Diag.TempNode = "First time";
			d.Text = DLG_TEXT[0] + address_form.fra + DLG_TEXT[1] + address_form.fra + " " + Characters[GetCharacterIndex(DLG_TEXT[2])].lastname + DLG_TEXT[3];
			Link.l1 = DLG_TEXT[4];
			Link.l1.go = "exit";
			AddDialogExitQuest("Story_BoonStartTalkToTancredeAgain");
		break;
	}
}


