#include "DIALOGS\Habitue_dialog.h"
void ProcessDialogEvent()
{
    ref NPChar, PChar, d; 
	PChar = GetMainCharacter();
	aref Link, Diag;
	string NPC_Meeting, TempInfoCharacterID_1, TempInfoCharacterID_2;
	int DonationSize;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);

	int iEnemyDice, iPCDice;
	string iDay, iMonth;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	if (npchar.quest.Meeting != lastspeak_date)
	{
		npchar.quest.last_theme = makeint(rand(1));
		npchar.quest.Meeting = lastspeak_date;
		npchar.money = rand(10)*100;
		//Log_SetStringToLog("Money of character " + npchar.id + " is " + npchar.money + "!!!");
	}
	
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------������ ������ - ������ �������
		
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "First time":
			Dialog.defAni = "Sit_Lower_head";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "Sit_Lower_head";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "Sit_Lower_head";
			Dialog.cam = "1";
			

			switch (npchar.quest.last_theme)
			{
				case "0": //������.
					dialog.snd = "Voice\HADI\HADI001";
					dialog.text = DLG_TEXT[0];
					link.l1 = DLG_TEXT[1];
					link.l1.go = "exit";
					if (makeint(pchar.money) >= 1)
					{
						link.l2 = DLG_TEXT[2];
						link.l2.go = "talk_with_alchogol";
					}
				break;

				case "1":
					if (!checkAttribute(pchar, "quest.gambling_with_girl"))
					{
						pchar.quest.gambling_with_girl = "";
					}
					if (CheckQuestAttribute("gambling_with_girl", "") && makeint(pchar.quest.gambling) >= 40 && makeint(pchar.money) >=100)
					{
						dialog.snd = "Voice\HADI\HADI002";
						dialog.text = DLG_TEXT[3];
						link.l1 = DLG_TEXT[4];
						link.l1.go = "gambling_with_girl_1";
					}
					else
					{
						dialog.snd = "Voice\HADI\HADI003";
						dialog.text = DLG_TEXT[5];
						link.l1 = DLG_TEXT[6];
						link.l1.go = "exit";
						if (makeint(pchar.quest.gambling) >= 100  && makeint(npchar.money) >=100)
						{
							dialog.snd = "Voice\HADI\HADI004";
							Dialog.text = DLG_TEXT[7];
							link.l1 = DLG_TEXT[8];
							link.l1.go = "exit";
						}
						if (makeint(pchar.quest.gambling) >= 50 && makeint(pchar.quest.gambling) < 100  && makeint(npchar.money) >=100)
						{
							dialog.snd = "Voice\HADI\HADI005";
							Dialog.text = DLG_TEXT[9];
							link.l1 = DLG_TEXT[10];
							link.l1.go = "gambling";
							link.l2 = DLG_TEXT[11];
							link.l2.go = "exit";
						}
						if (makeint(pchar.quest.gambling) < 50 && makeint(npchar.money) >=100)
						{
							dialog.snd = pcharrepphrase("Voice\HADI\HADI006", "Voice\HADI\HADI007");
							dialog.text = pcharrepphrase(DLG_TEXT[12], DLG_TEXT[13] + pchar.name + DLG_TEXT[14]);
							if (makeint(pchar.money) >= 100)
							{
								link.l1 = DLG_TEXT[15];
								link.l1.go = "gambling";
							}
							link.l2 = DLG_TEXT[16];
							link.l2.go = "exit";
						}
					}
				break;
			}
			
			Diag.TempNode = "First time";
	    break;

		case "gambling_with_girl_1":
			pchar.quest.gambling_with_girl = npchar.id;
			dialog.snd = "Voice\HADI\HADI008";
			dialog.text = DLG_TEXT[17];
			link.l1 = DLG_TEXT[18];
			link.l1.go = "gambling_with_girl_2";
		break;

		case "gambling_with_girl_2":
			dialog.snd = "Voice\HADI\HADI009";
			dialog.text = DLG_TEXT[19];
			link.l1 = DLG_TEXT[20];
			link.l1.go = "gambling_with_girl_3";
		break;

		case "gambling_with_girl_3":
			dialog.snd = "Voice\HADI\HADI010";
			dialog.text = DLG_TEXT[21];
			link.l1 = DLG_TEXT[22];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT[23];
			link.l2.go = "gambling_with_girl_4";
		break;

		case "gambling_with_girl_4":
			dialog.snd = "Voice\HADI\HADI011";
			dialog.text = DLG_TEXT[24];
			link.l1 = DLG_TEXT[25];
			link.l1.go = "exit";
			pchar.quest.friend_in_tavern = npchar.id;
			npchar.quest.locator = npchar.location.locator;
			AddDialogExitQuest("to_the_room_for_see_girl");
			npchar.dialog.tempnode = "speak_in_room_while_see_girl";
		break;

		case "speak_in_room_while_see_girl":
			Diag.tempNode = "first time";

			Dialog.defAni = "Sit_Lower_head";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "Sit_Lower_head";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "Sit_Lower_head";
			Dialog.cam = "1";
			
			dialog.snd = "Voice\HADI\HADI012";
			dialog.text = DLG_TEXT[26];
			link.l1 = DLG_TEXT[27];
			link.l1.go = "speak_in_room_while_see_girl_2";
			SetQuestHeader("gambled_girl");
			AddQuestRecord("gambled_girl", "1");
		break;

		case "speak_in_room_while_see_girl_2":
			dialog.snd = "Voice\HADI\HADI013";
			dialog.text = DLG_TEXT[28];
			link.l1 = DLG_TEXT[29];
			link.l1.go = "speak_in_room_while_see_girl_3";
			link.l2 = DLG_TEXT[30];
			link.l2.go = "speak_in_room_while_see_girl_6";
		break;

		case "speak_in_room_while_see_girl_3":
			dialog.snd = "Voice\HADI\HADI014";
			dialog.text = DLG_TEXT[31];
			link.l1 = DLG_TEXT[32];
			link.l1.go = "speak_in_room_while_see_girl_4";
		break;

		case "speak_in_room_while_see_girl_4":
			dialog.snd = "Voice\HADI\HADI015";
			dialog.text = DLG_TEXT[33] + (rand(6)+3) + DLG_TEXT[34];
			link.l1 = DLG_TEXT[35] + (rand(10) + 10) + DLG_TEXT[36];
			link.l1.go = "speak_in_room_while_see_girl_5";
		break;

		case "speak_in_room_while_see_girl_5":
			dialog.snd = "Voice\HADI\HADI016";
			dialog.text = DLG_TEXT[37];
			link.l1 = DLG_TEXT[38];
			link.l1.go = "exit";
			pchar.quest.gambling_with_girl = "gambled";
			AddDialogExitQuest("habitue_exit_from_room");
			AddQuestRecord("gambled_girl", "2");
		break;
		
		case "speak_in_room_while_see_girl_6":
			dialog.snd = "Voice\HADI\HADI017";
			dialog.text = DLG_TEXT[39];
			link.l1 = DLG_TEXT[40];
			link.l1.go = "speak_in_room_while_see_girl_7";
		break;

		case "speak_in_room_while_see_girl_7":
			dialog.snd = "Voice\HADI\HADI018";
			dialog.text = DLG_TEXT[41];
			link.l1 = DLG_TEXT[42];
			link.l1.go = "exit";
			AddDialogExitQuest("fight_in_upstairs_for_girl");
			AddQuestRecord("gambled_girl", "3");
		break;
		
		case "gambling":
			Diag.tempnode = "gambling_node";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.quest.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "gambling_node":
			//Log_SetStringToLog("���������� ��������� " + gambling + "!");

			Diag.tempNode = "first time";

			Dialog.defAni = "Sit_Lower_head";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "Sit_Lower_head";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "Sit_Lower_head";
			Dialog.cam = "1";
			
			dialog.snd = "Voice\HADI\HADI019";
			Dialog.text = DLG_TEXT[43];
			link.l1 = DLG_TEXT[44];
			link.l1.go = "gambling_opponent_strike";
			link.l2 = DLG_TEXT[45];
			link.l2.go = "exit_sit";
		break;

		case "gambling_opponent_strike":
			if (makeint(npchar.money <= 0))
			{
				dialog.snd = "Voice\HADI\HADI020";
				dialog.text = DLG_TEXT[46];
				link.l1 = DLG_TEXT[47];
				link.l1.go = "exit_sit";
			}
			else
			{
				iEnemyDice = makeint(rand(6) + rand(6) + rand(6) + rand(6)) - makeint(pchar.skill.sneak) + 1;
				if (iEnemyDice <4) {iEnemyDice = 4}
				if (iEnemyDice >24) {iEnemyDice = 24}
				if (iEnemyDice <=10)
				{
					dialog.snd = "Voice\HADI\HADI021";
					Dialog.text = iEnemyDice + DLG_TEXT[48];
				}
				if (iEnemyDice > 10 && iEnemyDice <=15)
				{
					dialog.snd = "Voice\HADI\HADI022";
					dialog.text = iEnemyDice + DLG_TEXT[49];
				}
				if (iEnemyDice > 15 && iEnemyDice <=20)
				{
					dialog.snd = "Voice\HADI\HADI023";
					dialog.text = iEnemyDice + DLG_TEXT[50];
				}
				if (iEnemyDice > 20)
				{
					dialog.snd = "Voice\HADI\HADI024";
					dialog.text = iEnemyDice + DLG_TEXT[51];
				}
				link.l1 = DLG_TEXT[52];
				link.l1.go = "gambling_pc_strike";
				pchar.iEnemyDice = iEnemyDice;
			}
		break;

		case "gambling_pc_strike":
			//Log_SetStringToLog("Money of character " + npchar.id + " is " + npchar.money + "!");
			iPCDice = makeint(rand(6) + rand(6) + rand(6) + rand(6));
			if (iPCDice <= (23 -  makeint(pchar.skill.sneak)))
			{
				 iPCDice = iPCDice + makeint(pchar.skill.sneak) - 1;
			}
			if (iPCDice <4) {iPCDice = 4}
			if (iPCDice >24) {iPCDice = 24}
			if (iPCDice < makeint(pchar.iEnemyDice))
			{
				AddMoneyToCharacter(pchar, -100);
				npchar.money = makeint(npchar.money) + 100;
				dialog.snd = "Voice\HADI\HADI025";
				Dialog.text = iPCDice + DLG_TEXT[53] + DLG_TEXT[54];
				if (makeint(pchar.money) >=100)
				{
					link.l1 = DLG_TEXT[55];
					link.l1.go = "gambling_opponent_strike";
				}
				link.l2 = DLG_TEXT[56];
				link.l2.go = "exit_sit";
				pchar.quest.gambling = makeint(pchar.quest.gambling) - 1;
			}
			if (iPCDice > makeint(pchar.iEnemyDice))
			{
				dialog.snd = "Voice\HADI\HADI026";
				Dialog.text = iPCDice + DLG_TEXT[57] + DLG_TEXT[58];
				link.l1 = DLG_TEXT[59];
				link.l1.go = "gambling_opponent_strike";
				link.l2 = DLG_TEXT[60];
				link.l2.go = "exit_sit";
				AddMoneyToCharacter(pchar, 100);
				npchar.money = makeint(npchar.money) - 100;
				pchar.quest.gambling = makeint(pchar.quest.gambling) + 1;
				/*//����� �� ������ � ������� �������
				if (makeint(pchar.quest.gambling) == 60)
				{

					pchar.quest.exit_from_tavern.win_condition.l1 = "ExitFromLocation";
					pchar.quest.exit_from_tavern.win_condition.l1.location = pchar.location;
					pchar.quest.exit_from_tavern.win_condition = "exit_from_tavern";
				}
				//����� �� ������ ���������, ��� ���
				if (makeint(pchar.quest.gambling) == 100)
				{
					pchar.quest.exit_from_tavern.win_condition.l1 = "ExitFromLocation";
					pchar.quest.exit_from_tavern.win_condition.l1.location = pchar.location;
					pchar.quest.exit_from_tavern.win_condition = "exit_from_tavern";
				}*/
			}
			if (iPCDice == makeint(pchar.iEnemyDice))
			{
				dialog.snd = "Voice\HADI\HADI027";
				Dialog.text = DLG_TEXT[61];
				link.l1 = DLG_TEXT[62];
				link.l1.go = "gambling_opponent_strike";
				link.l2 = DLG_TEXT[63];
				link.l2.go = "exit_sit";
			}
			DeleteAttribute(pchar, "iEnemyDice");
		break;


		case "talk_with_alchogol":
			Diag.TempNode = "begin_sit";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.quest.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "begin_sit":
			Diag.TempNode = "first time";
			dialog.snd = "Voice\HADI\HADI028";
			dialog.text = DLG_TEXT[64];
			link.l1 = DLG_TEXT[65];
			link.l1.go = "sit_2";
		break;

		case "sit_2":
			AddMoneyToCharacter(pchar, -1);
			dialog.snd1 = "Voice\HADI\HADI029";
			dialog.snd2 = "Voice\HADI\HADI030";
			dialog.snd3 = "Voice\HADI\HADI031";
			dialog.text = randphrase(DLG_TEXT[66], DLG_TEXT[67], DLG_TEXT[68], &dialog, dialog.snd1, dialog.snd2, dialog.snd3);
			link.l1 = DLG_TEXT[69];
			link.l1.go = "exit_sit";
			if (makeint(pchar.money) >=1)
			{
				link.l2 = DLG_TEXT[70];
				link.l2.go = "sit_3";
			}
		break;

		case "sit_3":
			int iSituation = makeint(rand(4));
			switch (iSituation)
			{
				case 0:
					dialog.snd = "Voice\HADI\HADI032";
					dialog.text = DLG_TEXT[71];
					link.l1 = DLG_TEXT[72];
					link.l1.go = "sit_2";
				break;

				case 1:
					dialog.snd = "Voice\HADI\HADI033";
					dialog.text = DLG_TEXT[73];
					link.l1 = DLG_TEXT[74];
					link.l1.go = "sit_case_2_friend";
					link.l2 = DLG_TEXT[75];
					link.l2.go = "sit_case_2_enemy";
				break;

				case 2:
					dialog.snd = "Voice\HADI\HADI034";
					dialog.text = DLG_TEXT[76];
					link.l1 = DLG_TEXT[77];
					link.l1.go = "exit_sit";
					link.l2 = DLG_TEXT[78];
					link.l2.go = "sit_case_3";
				break;

				case 3:
					dialog.snd = "Voice\HADI\HADI035";
					dialog.text = DLG_TEXT[79];
					link.l1 = DLG_TEXT[80];
					link.l1.go = "sit_case_4_exit";
				break;

				case 4:
					dialog.snd = "Voice\HADI\HADI036";
					dialog.text = DLG_TEXT[81];
					link.l1 = DLG_TEXT[82];
					link.l1.go = "sit_case_5_exit";
				break;
			}
		break;

		case "sit_case_5_exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("fighting");
		break;

		case "sit_case_4_exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.quest.friend_in_tavern = npchar.id;
			AddDialogExitQuest("without_memory");
		break;

		case "sit_case_3":
			dialog.snd = "Voice\HADI\HADI037";
			dialog.text = DLG_TEXT[83];
			link.l1 = DLG_TEXT[84];
			link.l1.go = "exit_sit";
			link.l2 = DLG_TEXT[85];
			link.l2.go = "sit_case_3_exit";
		break;

		case "sit_case_3_exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("drink_talk_with_soldier");
		break;

		case "sit_case_2_friend":
			dialog.snd = "Voice\HADI\HADI038";
			dialog.text = DLG_TEXT[86];
			link.l1 = DLG_TEXT[87];
			link.l1.go = "exit_sit";
			link.l2 = DLG_TEXT[88];
			link.l2.go = "sit_case_2_friend_2";
		break;

		case "sit_case_2_friend_2":
			dialog.snd = "Voice\HADI\HADI039";
			dialog.text = DLG_TEXT[89];
			link.l1 = DLG_TEXT[90];
			link.l1.go = "tavern_keeper";
		break;

		case "sit_case_2_enemy":
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = DLG_TEXT[91];
			link.l1 = DLG_TEXT[92];
			link.l1.go = "tavern_keeper";
		break;

		case "exit_sit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;

		case "danielle_fight":
			dialog.snd = "Voice\HADI\HADI041";
			dialog.text = DLG_TEXT[93];
			link.l1 = DLG_TEXT[94];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT[95];
			link.l2.go = "danielle_fight_2";
		break;

		case "danielle_fight_2":
			dialog.snd = "Voice\HADI\HADI042";
			dialog.text = DLG_TEXT[96];
			link.l1 = DLG_TEXT[97];
			link.l1.go = "tavern_keeper";
			pchar.quest.fight_in_tavern = "fight";
		break;

		case "tavern_keeper":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("tavern_keeper");
		break;

	}

}