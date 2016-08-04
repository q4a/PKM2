#include "DIALOGS\arnaud matton_dialog.h"
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

	string iDay, iMonth;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

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
			
			dialog.snd = "Voice\ARMA\ARMA001";
			dialog.text = DLG_TEXT[0];
			link.l1 = pcharrepphrase(DLG_TEXT[1], DLG_TEXT[2]);
			link.l1.go = "exit";
			
			if ((characters[GetCharacterIndex("Sabine Matton")].quest.hire != "ransom") && (characters[GetCharacterIndex("Sabine Matton")].quest.hire != "enemy_forever") && (pchar.location == "Falaise_de_Fleur_store"))
			{
				dialog.snd1 = "Voice\ARMA\ARMA002";
				dialog.snd2 = "Voice\ARMA\ARMA003";
				dialog.snd3 = "Voice\ARMA\ARMA004";
				Dialog.Text = randphrase(DLG_TEXT[3] + Address_form.Fra + DLG_TEXT[4], DLG_TEXT[5] + Address_Form.Fra + DLG_TEXT[6], DLG_TEXT[7], &dialog, dialog.snd1, dialog.snd2, dialog.snd3);
				Link.l1 = DLG_TEXT[8];
				Link.l1.go = "market"; 
				link.l2 = DLG_TEXT[9];
				link.l2.go = "exit";
				if (characters[GetCharacterIndex("Sabine Matton")].quest.hire != "was_captured_done")
				{
					link.l3 = DLG_TEXT[10];
					link.l3.go = "quests";
				}
			}
			if ((characters[GetCharacterIndex("Sabine Matton")].quest.hire == "ransom_1")&&(pchar.location == "Falaise_De_Fleur_shore")) // �������� �� �����
			{
				dialog.snd = "Voice\ARMA\ARMA005";
				dialog.text = DLG_TEXT[11] + Characters[GetCharacterIndex(DLG_TEXT[12])].name + DLG_TEXT[13];
				link.l1 = pcharrepphrase(DLG_TEXT[14], DLG_TEXT[15]);
				link.l1.go = "ransom_money";
				link.l2 = pcharrepphrase(DLG_TEXT[16], DLG_TEXT[17]);
				link.l2.go = "ransom_bad";
			}
			if (characters[GetCharacterIndex("Sabine Matton")].quest.hire == "enemy_forever_1")
			{
				dialog.snd = "Voice\ARMA\ARMA006";
				dialog.text = DLG_TEXT[18];
				link.l1 = pcharrepphrase(DLG_TEXT[19], DLG_TEXT[20]);
				link.l1.go = "exit";
			}
			if (characters[GetCharacterIndex("Sabine Matton")].quest.hire == "danielle_on_ship_1")
			{
				dialog.snd = "Voice\ARMA\ARMA007";
				dialog.text = DLG_TEXT[21];
				link.l3 = pcharrepphrase(DLG_TEXT[22], DLG_TEXT[23]);
				link.l3.go = "exit";
				link.l4 = pcharrepphrase(DLG_TEXT[24], DLG_TEXT[25]);
				link.l4.go = "danielle_daughter_1";
			}
			NextDiag.TempNode = "First time";
		break;

		case "quests":
			iTest = 0;
			dialog.snd = "Voice\ARMA\ARMA008";
			Dialog.text = DLG_TEXT[26];
			//////////////////////////////
			// ������ �������
			//////////////////////////////
			if (npchar.quest_begin == "100")
			{
				Link.l1 = DLG_TEXT[27];
				if (characters[GetCharacterIndex("Sabine Matton")].quest.hire == "blaze_begin_1" && makeint(pchar.reputation) > 40)
				{
					link.l1.go = "daughter";
				}
				if (characters[GetCharacterIndex("Baldewyn Coffier")].quest.hire == "10000")
				{
					link.l1.go = "baldewyn";
				}
				if (npchar.quest.to_redmond_1 == "0" && !(GetNationRelation2MainCharacter(FRANCE) == RELATION_ENEMY))
				{
					link.l1.go = "node_1";
				}
				
			}
			if (CheckAttribute(pchar, "quest.iQuantityGoods"))
			{
				int iQuantityShipGoods = pchar.quest.iQuantityGoods;
				int iQuestTradeGoods = pchar.quest.iTradeGoods;
			}
			if (CheckQuestAttribute("generate_trade_quest_progress", "begin") || CheckQuestAttribute("generate_trade_quest_progress",  "failed"))
			{
				if (CheckQuestAttribute("iTradeNation", npchar.nation) &&  GetSquadronGoods(pchar, iQuestTradeGoods) >= iQuantityShipGoods)
				{
					dialog.snd = "Voice\ARMA\ARMA009";
					dialog.text = DLG_TEXT[28];
					link.l1 = DLG_TEXT[29];
					link.l1.go = "generate_quest_2";
				}
			}
			else
			{
				if (!CheckQuestAttribute("generate_trade_quest_progress", "begin"))
				{
					link.l2 = DLG_TEXT[30];
					link.l2.go = "generate_quest";
				}
			}
			
			//////////////////////////////
			// ����� �������
			//////////////////////////////
			//////////////////////////////
			// ����� �������� �����
			//////////////////////////////
			if (characters[GetCharacterIndex("Baldewyn Coffier")].quest.hire ==  "not_money" && iTest < QUEST_COUNTER)
			{
				link.l2 = pcharrepphrase(DLG_TEXT[31], DLG_TEXT[32]);
				link.l2.go = "baldewyn_done";
				iTest = iTest + 1;
			}
			if (characters[GetCharacterIndex("Baldewyn Coffier")].quest.hire ==  "not_money_2" && iTest < QUEST_COUNTER)
			{
				link.l2 = pcharrepphrase(DLG_TEXT[33], DLG_TEXT[34] + characters[GetCharacterIndex(DLG_TEXT[35])].name + DLG_TEXT[36]);
				link.l2.go = "baldewyn_done";
				iTest = iTest + 1;
			}
			if (characters[GetCharacterIndex("Baldewyn Coffier")].quest.hire ==  "not_money_3" && iTest < QUEST_COUNTER)
			{
				link.l2 = pcharrepphrase(DLG_TEXT[37], DLG_TEXT[38]);
				link.l2.go = "money_1";
				iTest = iTest + 1;
			}
			if (characters[GetCharacterIndex("Baldewyn Coffier")].quest.hire ==  "money_1" && iTest < QUEST_COUNTER)
			{
				link.l2 = pcharrepphrase(DLG_TEXT[39], DLG_TEXT[40]);
				link.l2.go = "baldewyn_work_done";
				iTest = iTest + 1;
			}
			if (characters[GetCharacterIndex("Baldewyn Coffier")].quest.hire ==  "money_4" && iTest < QUEST_COUNTER)
			{
				link.l2 = pcharrepphrase(DLG_TEXT[41] + Characters[GetCharacterIndex(DLG_TEXT[42])].name + " " + Characters[GetCharacterIndex(DLG_TEXT[43])].lastname + DLG_TEXT[44], DLG_TEXT[45] + characters[GetCharacterIndex(DLG_TEXT[46])].name + DLG_TEXT[47]);
				link.l2.go = "baldewyn_work_done_one";
				iTest = iTest + 1;
			}
			if (characters[GetCharacterIndex("Baldewyn Coffier")].quest.hire ==  "money_2" && iTest < QUEST_COUNTER)
			{
				link.l2 = pcharrepphrase(DLG_TEXT[48], DLG_TEXT[49] + characters[GetCharacterIndex(DLG_TEXT[50])] + DLG_TEXT[51]);
				link.l2.go = "baldewyn_guard";
				iTest = iTest + 1;
			}
			//////////////////////////////
			// ����� ������ �������� �����
			//////////////////////////////
			if (npchar.quest.to_redmond_1 ==  "cargo_done_1" && iTest < QUEST_COUNTER)
			{
				link.l3 = pcharrepphrase(DLG_TEXT[52], DLG_TEXT[53] + npchar.name + DLG_TEXT[54]);
				link.l3.go = "redmond_done";
				iTest = iTest + 1;
			}
			if (npchar.quest.to_redmond_1 ==  "cargo_not_done_1" && iTest < QUEST_COUNTER)
			{
				Link.l3 = pcharrepphrase(DLG_TEXT[55], DLG_TEXT[56]);
				link.l3.go = "redmond_quest";
				iTest = iTest + 1;
			}
			if (Characters[GetCharacterIndex("Thomas O'Reily")].quest.first_job == "100" && GetSquadronGoods(PChar,GOOD_SILK)>= 200 && iTest < QUEST_COUNTER)
			{	
				Link.l4 = pcharrepphrase(DLG_TEXT[57] + Characters[GetCharacterIndex(DLG_TEXT[58])].name + Characters[GetCharacterIndex(DLG_TEXT[59])].lastname + DLG_TEXT[60], characters[GetCharacterIndex(DLG_TEXT[61])].name + DLG_TEXT[62]);
				Link.l4.go = "First_job_done";
				iTest = iTest + 1;
			}
			//////////////////////////////
			// ����� ��� ����� ���� �������
			//////////////////////////////
			if (characters[GetCharacterIndex("Sabine Matton")].quest.hire ==  "almost_done_1" && iTest < QUEST_COUNTER)
			{
				link.l5 = DLG_TEXT[63];
				link.l5.go = "daughter_done";
				iTest = iTest + 1;
			}
			if (characters[GetCharacterIndex("Sabine Matton")].quest.hire == "almost_done_ransom_1" && iTest < QUEST_COUNTER)
			{
				link.l5 = DLG_TEXT[64];
				link.l5.go = "daughter_done_1";
				iTest = iTest + 1;
			}
			if (characters[GetCharacterIndex("Sabine Matton")].quest.hire == "almost_done_ransom_free_1" && iTest < QUEST_COUNTER)
			{
				link.l5 = pcharrepphrase(DLG_TEXT[65], DLG_TEXT[66]);
				link.l5.go = "daughter_done_1";
				iTest = iTest + 1;
			}
			if (characters[GetCharacterIndex("Sabine Matton")].quest.hire == "captured_by_blaze_1" || characters[GetCharacterIndex("Sabine Matton")].quest.hire == "captured_by_blaze_again" && iTest < QUEST_COUNTER)
			{
				Link.l5 = pcharrepphrase(DLG_TEXT[67], DLG_TEXT[68]);
				Link.l5.go = "ransom";
			}
			//////////////////////////////
			// ����� ������ ��� ����� ���� �������
			//////////////////////////////
			Link.l99 = DLG_TEXT[69];
			Link.l99.go = "exit";
		break;

		case "danielle_daughter_1":
			dialog.snd = "Voice\ARMA\ARMA010";
			dialog.text = DLG_TEXT[70];
			link.l1 = pcharrepphrase(DLG_TEXT[71], DLG_TEXT[72]);
			link.l1.go = "danielle_daughter_2";
			link.l2 = pcharrepphrase(DLG_TEXT[73], DLG_TEXT[74]);
			link.l2.go = "ransom_1";
		break;

		case "danielle_daughter_2":
			dialog.snd = "Voice\ARMA\ARMA011";
			dialog.text = DLG_TEXT[75];
			link.l1 = pcharrepphrase(DLG_TEXT[76], DLG_TEXT[77]);
			link.l1.go = "danielle_daughter_3";
		break;

		case "danielle_daughter_3":
			dialog.snd = "Voice\ARMA\ARMA012";
			dialog.text = DLG_TEXT[78];
			link.l1 = pcharrepphrase(DLG_TEXT[79], DLG_TEXT[80]);
			link.l1.go = "exit";
			characters[GetCharacterIndex("Sabine Matton")].quest.hire = "done";
			RemovePassenger(pchar, &characters[GetCharacterIndex("Sabine Matton")]);
			pchar.experience = makeint(pchar.experience) + 100;
		break;

		case "ransom_bad":
			dialog.snd = "Voice\ARMA\ARMA013";
			dialog.text = DLG_TEXT[81];
			link.l1 = pcharrepphrase(DLG_TEXT[82], DLG_TEXT[83]);
			link.l1.go = "exit";
			characters[GetCharacterIndex("Sabine Matton")].quest.hire = "enemy_forever";
			ChangeCharacterReputation(pchar, -2);
			///////////////////////////////////////////////////////////////////////////
			// ���� ������, � �� ���� ���������� ��������� 1 ������ � 2 ������� ������, ���� ������� ���������� ����������.
			///////////////////////////////////////////////////////////////////////////
		break;

		case "ransom_money":
			dialog.snd = "Voice\ARMA\ARMA014";
			dialog.text = DLG_TEXT[84];
			link.l1 = pcharrepphrase(DLG_TEXT[85], DLG_TEXT[86]);
			link.l1.go = "ransom_money_1";
			link.l2 = pcharrepphrase(DLG_TEXT[87], DLG_TEXT[88]);
			link.l2.go = "ransom_bad";
		break;

		case "ransom_money_1":
			dialog.snd = "Voice\ARMA\ARMA015";
			dialog.text = DLG_TEXT[89];
			link.l1 = pcharrepphrase(DLG_TEXT[90], DLG_TEXT[91]);
			link.l1.go = "exit";
			characters[GetCharacterIndex("Sabine Matton")].quest.hire = "was_captured_done";
			ChangeCharacterReputation(pchar, -1);
			AddMoneyToCharacter(pchar, 5000);
			RemovePassenger(pchar, Characters[GetCharacterIndex("Sabine Matton")]);
			//fading();
			ChangeCharacterAddress(&characters[GetCharacterIndex("Sabine Matton")], "shore1","citizen06"); //��������� �������.
			npchar.location	= "Falaise_de_Fleur_store";
			npchar.location.locator = "locator4";
			characters[GetCharacterIndex("Sabine Matton")].location = "none";
		break;

		case "ransom":
			dialog.snd = "Voice\ARMA\ARMA016";
			dialog.text = DLG_TEXT[92];
			link.l1 = pcharrepphrase(DLG_TEXT[93], DLG_TEXT[94]);
			link.l1.go = "ransom_1";
		break;

		case "ransom_1":
			dialog.snd = "Voice\ARMA\ARMA017";
			dialog.text = DLG_TEXT[95];
			link.l1 = pcharrepphrase(DLG_TEXT[96], DLG_TEXT[97]);
			link.l1.go = "ransom_stupid";
			link.l2 = pcharrepphrase(DLG_TEXT[98], DLG_TEXT[99]);
			link.l2.go = "ransom_2";
		break;

		case "ransom_2":
			dialog.snd = "Voice\ARMA\ARMA018";
			dialog.text = DLG_TEXT[100];
			link.l1 = pcharrepphrase(DLG_TEXT[101], DLG_TEXT[102]);
			link.l1.go = "exit";
			characters[GetCharacterIndex("Sabine Matton")].quest.hire = "ransom";
			npchar.location = "shore1";
			npchar.location.locator = "citizen05";
		break;

		case "ransom_stupid":
			dialog.snd = "Voice\ARMA\ARMA019";
			dialog.text = DLG_TEXT[103];
			link.l1 = DLG_TEXT[104];
			link.l1.go = "exit";
			///////////////////////////////////////////////////////////////////////
			// ��������� �������, ������������ ���������. ������� ���������. �����. 
			///////////////////////////////////////////////////////////////////////
			characters[GetCharacterIndex("Sabine Matton")].quest.hire = "enemy_forever";
			ChangeCharacterReputation(pchar, -1);
		break;

		case "daughter_done":
			dialog.snd = "Voice\ARMA\ARMA020";
			dialog.text = DLG_TEXT[105];
			link.l1 = pcharrepphrase(DLG_TEXT[106], DLG_TEXT[107]);
			link.l1.go = "trade_guild";
			link.l2 = pcharrepphrase(DLG_TEXT[108], DLG_TEXT[109]);
			link.l2.go = "exit";
			npchar.quest_begin = "0";
			characters[GetCharacterIndex("Sabine Matton")].quest.hire = "done";
			characters[GetCharacterIndex("Sabine Matton")].quest.love = "1";
		break;

		case "daughter_done_1":
			dialog.snd = "Voice\ARMA\ARMA021";
			dialog.text = DLG_TEXT[110];
			link.l1 = pcharrepphrase(DLG_TEXT[111], DLG_TEXT[112]);
			link.l1.go = "exit";
			characters[GetCharacterIndex("Sabine Matton")].quest.hire = "was_captured_done";
			npchar.quest_begin = "0";
			npchar.skill.commerce = makeint(npchar.skill.commerce) + 2;
		break;

		////////////////////////////////////////////////
		// TRADE GUILD QUEST
		////////////////////////////////////////////////
		case "trade_guild":
			link.l1 = DLG_TEXT[113];
			link.l1.go = "exit";
		break;
		////////////////////////////////////////////////
		// END OF TRADE GUILD QUEST
		////////////////////////////////////////////////

		case "daughter":
			dialog.snd = "Voice\ARMA\ARMA022";
			dialog.text = DLG_TEXT[114];
			link.l1 = DLG_TEXT[115];
			link.l1.go = "daughter_1";
		break;

		case "daughter_1":
			dialog.snd = "Voice\ARMA\ARMA023";
			dialog.text = DLG_TEXT[116];
			link.l1 = DLG_TEXT[117];
			link.l1.go = "daughter_2";
		break;

		case "daughter_2":
			dialog.snd = "Voice\ARMA\ARMA024";
			dialog.text = DLG_TEXT[118];
			link.l1 = DLG_TEXT[119];
			link.l1.go = "daughter_3";
		break;

		case "daughter_3":
			dialog.snd = "Voice\ARMA\ARMA025";
			dialog.text = DLG_TEXT[120];
			link.l1 = DLG_TEXT[121];
			link.l1.go = "daughter_4";
		break;

		case "daughter_4":
			dialog.snd = "Voice\ARMA\ARMA026";
			dialog.text = DLG_TEXT[122];
			link.l1 = DLG_TEXT[123];
			link.l1.go = "daughter_5";
		break;

		case "daughter_5":
			dialog.snd = "Voice\ARMA\ARMA027";
			dialog.text = DLG_TEXT[124];
			link.l1 = DLG_TEXT[125];
			link.l1.go = "daughter_6";
		break;

		case "daughter_6":
			dialog.snd = "Voice\ARMA\ARMA028";
			dialog.text = DLG_TEXT[126] + Characters[GetCharacterIndex(DLG_TEXT[127])].name + " " + Characters[GetCharacterIndex(DLG_TEXT[128])].lastname + DLG_TEXT[129];
			link.l1 = DLG_TEXT[130];
			link.l1.go = "daughter_9";
			link.l2 = DLG_TEXT[131];
			link.l2.go = "daughter_7";
			link.l3 = DLG_TEXT[132];
			link.l3.go = "daughter_denied";
		break;

		case "daughter_7":
			dialog.snd = "Voice\ARMA\ARMA029";
			dialog.text = DLG_TEXT[133];
			link.l1 = DLG_TEXT[134];
			link.l1.go = "daughter_8";
			link.l2 = DLG_TEXT[135];
			link.l2.go = "daughter_denied";
		break;

		case "daughter_8":
			dialog.snd = "Voice\ARMA\ARMA030";
			dialog.text = DLG_TEXT[136];
			link.l1 = DLG_TEXT[137];
			link.l1.go = "daughter_9";
			AddMoneyToCharacter(pchar, 1500);
		break;

		case "daughter_9":
			dialog.snd = "Voice\ARMA\ARMA031";
			dialog.text = DLG_TEXT[138] + characters[GetCharacterIndex(DLG_TEXT[139])].name + " " + characters[GetCharacterIndex(DLG_TEXT[140])].lastname + DLG_TEXT[141];
			link.l1 = DLG_TEXT[142];
			link.l1.go = "daughter_10";
		break;

		case "daughter_10":
			dialog.snd = "Voice\ARMA\ARMA032";
			dialog.text = DLG_TEXT[143];
			link.l1 = DLG_TEXT[144] + pchar.ship.name + DLG_TEXT[145];
			link.l1.go = "exit";
			//////////////////////////////////
			//ADD_LETTER
			//////////////////////////////////
			characters[GetCharacterIndex("Sabine Matton")].quest.hire = "blaze_on_ship";
			npchar.quest_begin = "1";
			AddPassenger(pchar, &characters[GetCharacterIndex("Sabine Matton")], 0);
			ChangeCharacterAddress(&characters[GetCharacterIndex("Sabine Matton")], "none", "none");
		break;

		case "daughter_denied":
			dialog.snd = "Voice\ARMA\ARMA033";
			dialog.text = DLG_TEXT[146];
			link.l1 = DLG_TEXT[147];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT[148];
			link.l2.go = "First time";
			characters[GetCharacterIndex("Sabine Matton")].quest = "done";
		break;

		case "baldewyn_work_done":
			AddMoneyToCharacter(pchar, -2500));
			dialog.snd = "Voice\ARMA\ARMA034";
			dialog.text = DLG_TEXT[149];
			link.l1 = pcharrepphrase(DLG_TEXT[150], DLG_TEXT[151]);
			link.l1.go = "arnaud_bad_guy";
			link.l2 = pcharrepphrase(DLG_TEXT[152], DLG_TEXT[153]);
			link.l2.go = "exit";
			link.l3 = pcharrepphrase(DLG_TEXT[154], DLG_TEXT[155]);
			link.l3.go = "First time";
			AddMoneyToCharacter(pchar, makeint(npchar.money.quest));
			characters[GetCharacterIndex("Baldewyn Coffier")].quest.hire = "almost_done_1";
			npchar.quest_begin = "0";
			npchar.quest.money = "0";
			Characters[GetCharacterIndex("Sabine Matton")].location = "Falaise_De_Fleur_store";
		break;

		case "baldewyn_work_done_one":
			dialog.snd = "Voice\ARMA\ARMA035";
			dialog.text = DLG_TEXT[156];
			link.l2 = pcharrepphrase(DLG_TEXT[157], DLG_TEXT[158]);
			link.l2.go = "exit";
			link.l3 = pcharrepphrase(DLG_TEXT[159], DLG_TEXT[160]);
			link.l3.go = "First time";
			characters[GetCharacterIndex("Baldewyn Coffier")].quest.hire = "almost_done_1";
			AddMoneyToCharacter(pchar, -2000);
			Characters[GetCharacterIndex("Sabine Matton")].location = "Falaise_De_Fleur_store";
		break;

		case "money_1":
			dialog.snd = "Voice\ARMA\ARMA036";
			dialog.text = DLG_TEXT[161];
			link.l1 = DLG_TEXT[162];
			link.l1.go = "money_2";
			link.l2 = DLG_TEXT[163];
			link.l2.go = "arnaud_bad_guy";
		break;

		case "arnaud_bad_guy":
			dialog.snd = "Voice\ARMA\ARMA037";
			dialog.text = DLG_TEXT[164];
			link.l1 = DLG_TEXT[165];
			link.l1.go = "arnaud_bad_guy_1";
			link.l2 = DLG_TEXT[166];
			link.l2.go = "exit";
		break;

		case "arnaud_bad_guy_1":
			dialog.snd = "Voice\ARMA\ARMA038";
			dialog.text = DLG_TEXT[167];
			link.l1 = DLG_TEXT[168];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT[169];
			link.l2.go = "First Time";
		break;

		case "money_2":
			dialog.snd = "Voice\ARMA\ARMA039";
			dialog.text = DLG_TEXT[170];
			link.l1 = DLG_TEXT[171];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT[172];
			link.l2.go = "First time";
			AddMoneyToCharacter(pchar, makeint(npchar.money.quest));
			characters[GetCharacterIndex("Baldewyn Coffier")].quest.hire = "money_3";
			npchar.quest_begin = "0";
			npchar.quest.money = "0";
			Characters[GetCharacterIndex("Sabine Matton")].location = "Falaise_De_Fleur_store";
		break;

		case "baldewyn_guard":
			dialog.snd = "Voice\ARMA\ARMA040";
			dialog.text = DLG_TEXT[173] + Address_Form.fra + DLG_TEXT[174];
			link.l1 = DLG_TEXT[175];
			link.l1.go = "exit";
			characters[GetCharacterIndex("Baldewyn Coffier")].quest.hire = "done";
			npchar.quest_begin = "0";
			npchar.quest.money = "0";
			Rumour[4].state = "active";
			characters[GetCharacterIndex("Sabine Matton")].location = "none";
		break;

		case "first_job_done":
			Characters[GetCharacterIndex("Thomas O'Reily")].quest.first_job = "complete";
			dialog.snd = "Voice\ARMA\ARMA041";
			dialog.Text = DLG_TEXT[176];
			Link.l1 = DLG_TEXT[177];
			Link.l1.go = "First_job_done_1";
		break;

		case "First_job_done_1":
			dialog.snd = "Voice\ARMA\ARMA042";
			dialog.Text = DLG_TEXT[178] + address_form.fra + DLG_TEXT[179];
			Link.l1 = DLG_TEXT[180];
			Link.l1.go = "First_job_done_2";
		break;

		case "First_job_done_2":
			RemoveCharacterGoods(PChar,GOOD_SILK, 100);
			RemoveCharacterGoods(PChar,GOOD_RUM, 100);
			RemoveCharacterGoods(PChar,GOOD_PAPRIKA, 100);
			dialog.snd = "Voice\ARMA\ARMA043";
			dialog.Text = DLG_TEXT[181] + address_form.fra + " " + PChar.name + DLG_TEXT[182];
			Link.l1 = DLG_TEXT[183];
			Link.l1.go = "exit";
		break;

		case "redmond_quest":
			dialog.snd = "Voice\ARMA\ARMA044";
			Dialog.text = DLG_TEXT[184];
			link.l1 = DLG_TEXT[185];
			link.l1.go = "redmond_not_done";
			link.l2 = DLG_TEXT[186];
			link.l2.go = "redmond_not_done_1";
		break;

		case "generate_quest":
			if (npchar.quest.trade_date != lastspeak_date)
			{
				npchar.quest.trade_date = lastspeak_date;
				//�������� ������������ ��� ������ ��������
				if (GetNationRelation2MainCharacter(FRANCE) == RELATION_ENEMY)
				{
					dialog.snd = "Voice\ARMA\ARMA045";
					dialog.text = DLG_TEXT[187];
					link.l1 = DLG_TEXT[188];
					link.l1.go = "exit";
				}
				else
				{
					int iTradeNation = GenerateNationTrade(FRANCE);
					if (iTradeNation < 0)
					{
						dialog.snd = "Voice\ARMA\ARMA046";
						dialog.text = DLG_TEXT[189];
						link.l1 = DLG_TEXT[190];
						link.l1.go = "exit";
					}
					else
					{
						//��������� ������/�������
						int iTradeGoods = rand(22) + 4;
						//��������� ��������� ����� (��� ���� ������ ��������� �� ������� ���� 100 ������ ���������� �����
						if (GetSquadronFreeSpace(pchar, iTradeGoods) < 100)
						{
							dialog.snd = "Voice\ARMA\ARMA047";
							dialog.text = DLG_TEXT[191];
							link.l1 = DLG_TEXT[192];
							link.l1.go = "exit";
						}
						else
						{
							int iQuantityGoods = GetSquadronFreeSpace(pchar, iTradeGoods) - 20;
							int iMoney = ((iQuantityGoods *10+99)/100)*100;
							int iDaysExpired = 30;

							pchar.quest.iTradeGoods = iTradeGoods;
							pchar.quest.iQuantityGoods = iQuantityGoods;
							pchar.quest.iMoney = iMoney;
							pchar.quest.iTradeNation = iTradeNation;
							
							string sNation;

							switch (iTradeNation)
							{
								case FRANCE: sNation = FRA_COLONY; break;
								case SPAIN: sNation = SPA_COLONY; break;
								case HOLLAND: sNation = HOL_COLONY; break;
								case PORTUGAL: sNation = POR_COLONY; break;
								case ENGLAND: 
									int iColony = rand(2);
									if (iColony == 2 && CheckAttribute(Pchar, "Quest.Story_OxbayCaptured"))
									{
										iColony = rand(1);
									}
									switch (iColony)
									{
										case 0: sNation = RED_COLONY; pchar.quest.iTradeColony = "Redmond_store"; break;
										case 1: sNation = GREEN_COLONY; pchar.quest.iTradeColony = "Greenford_store"; break;
										case 2: sNation = OX_COLONY; pchar.quest.iTradeColony = "Oxbay_store"; break;
									}
								break;
							}
							dialog.snd = "Voice\ARMA\ARMA048";
							dialog.text = DLG_TEXT[193] + sNation + DLG_TEXT[194] + pchar.quest.iMoney + DLG_TEXT[195];
							link.l1 = DLG_TEXT[196];
							link.l1.go = "exit_trade";
							link.l2  = DLG_TEXT[197];
							link.l2.go = "exit";
						}
					}
				}
			}
			else
			{
				dialog.snd = "Voice\ARMA\ARMA049";
				dialog.text = DLG_TEXT[198];
				link.l1 = DLG_TEXT[199];
				link.l1.go = "exit";
			}
		break;
		
		case "exit_trade":
			AddDialogExitQuest("trade_quest_open");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "generate_quest_2":
			if (CheckQuestAttribute("generate_trade_quest_progress", "failed"))
			{
				dialog.snd = "Voice\ARMA\ARMA050";
				dialog.text = DLG_TEXT[200];
				link.l1 = DLG_TEXT[201];
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, -1);
			}
			else
			{
				dialog.snd = "Voice\ARMA\ARMA051";
				dialog.text = DLG_TEXT[202];
				link.l1 = DLG_TEXT[203];
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, 1);
				AddPartyExp(pchar, (makeint(pchar.quest.iMoney)/2));
				AddMoneyToCharacter(pchar, makeint(pchar.quest.iMoney));
				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
				RemoveCharacterGoods(pchar, makeint(pchar.quest.iTradeGoods), makeint(pchar.quest.iQuantityGoods));
			}
			AddDialogExitQuest("close_trade_quest");
		break;

		case "no_quests":
			if (npchar.quest_begin == "0")
			{
				dialog.snd = "Voice\ARMA\ARMA052";
				dialog.text = DLG_TEXT[204];
				link.l1 = DLG_TEXT[205];
				link.l1.go = "exit";
			}
			else
			{
				dialog.snd = "Voice\ARMA\ARMA053";
				dialog.text = DLG_TEXT[206];
				link.l1 = DLG_TEXT[207];
				link.l1.go = "exit";
			}
		break;

		case "redmond_not_done":
			dialog.snd = "Voice\ARMA\ARMA054";
			dialog.text = DLG_TEXT[208] + Characters[GetCharacterIndex(DLG_TEXT[209])].name + DLG_TEXT[210];
			link.l1 = DLG_TEXT[211];
			link.l1.go = "redmond_not_done_2";
			ChangeCharacterReputation(pchar, -1);
		break;

		case "redmond_not_done_1":
			dialog.snd = "Voice\ARMA\ARMA055";
			dialog.text = DLG_TEXT[212] + characters[GetCharacterIndex(DLG_TEXT[213])].name + DLG_TEXT[214];
			link.l1 = DLG_TEXT[215];
			link.l1.go = "redmond_not_done_2";
		break;

		case "redmond_not_done_2":
			dialog.snd = "Voice\ARMA\ARMA056";
			dialog.text = DLG_TEXT[216];
			link.l1 = DLG_TEXT[217];
			link.l1.go = "redmond_not_done_3";
			if (makeint(pchar.money) >= 1500)
			{
				link.l2 = DLG_TEXT[218];
				link.l2.go = "redmond_not_done_4";
			}
		break;

		case "redmond_not_done_3":
			dialog.snd = "Voice\ARMA\ARMA057";
			dialog.text = DLG_TEXT[219];
			link.l1 = DLG_TEXT[220];
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -10);
		break;

		case "redmond_not_done_4":
			dialog.snd = "Voice\ARMA\ARMA058";
			dialog.text = DLG_TEXT[221];
			link.l1 = DLG_TEXT[222] + Address_Form.Fra + DLG_TEXT[223];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1500);
		break;

		case "node_1":
			if (GetSquadronFreeSpace(pchar, GOOD_CHOCOLATE) >= 100)
			{
				dialog.snd = "Voice\ARMA\ARMA059";
				dialog.text = DLG_TEXT[224];
				link.l1 = DLG_TEXT[225];
				link.l1.go = "war";
				link.l2 = DLG_TEXT[226] + Address_Form.Fra + DLG_TEXT[227];
				link.l2.go = "access";
			}
			else
			{
				dialog.snd = "Voice\ARMA\ARMA060";
				dialog.text = DLG_TEXT[228];
				link.l1 = DLG_TEXT[229];
				link.l1.go = "exit";
				npchar.money.quest = "0";
			}
		break;

		case "war":
			dialog.snd = "Voice\ARMA\ARMA061";
			dialog.text = DLG_TEXT[230];
			link.l1 = DLG_TEXT[231];
			link.l1.go = "access";
			link.l2 = DLG_TEXT[232];
			link.l2.go = "war_1";
		break;

		case "war_1":
			if (makeint(pchar.skill.commerce) > 5)
			{
				dialog.snd = "Voice\ARMA\ARMA062";
				dialog.text = DLG_TEXT[233];
				link.l1 = DLG_TEXT[234];
				link.l1.go = "access_1";
			}
			else
			{
				dialog.snd = "Voice\ARMA\ARMA063";
				dialog.text = DLG_TEXT[235];
				link.l1 = DLG_TEXT[236];
				link.l1.go = "access";
				link.l2 = DLG_TEXT[237];
				link.l2.go = "exit";
			}
		break;

		case "access":
			dialog.snd = "Voice\ARMA\ARMA064";
			dialog.text = DLG_TEXT[238] + npchar.name + " " + npchar.lastname + DLG_TEXT[239];
			link.l1 = DLG_TEXT[240] + pchar.name + " " + pchar.lastname + DLG_TEXT[241];
			link.l1.go = "to_redmond_1";
			npchar.money.quest = "600";
		break;

		case "access_1":
			dialog.snd = "Voice\ARMA\ARMA065";
			dialog.text = DLG_TEXT[242] + npchar.name + " " + npchar.lastname + DLG_TEXT[243];
			link.l1 = DLG_TEXT[244] + pchar.name + " " + pchar.lastname + DLG_TEXT[245];
			link.l1.go = "to_redmond_1";
			npchar.money.quest = "800";
		break;

		case "to_redmond_1":
			dialog.snd = "Voice\ARMA\ARMA066";
			dialog.text = DLG_TEXT[246];
			link.l1 = DLG_TEXT[247];
			link.l1.go = "exit";
			npchar.quest.to_redmond_1 = "1";
			npchar.quest_begin = "1";
			AddCharacterGoods(pchar, GOOD_CHOCOLATE, 100);
		break;

		case "market":
			dialog.snd = "Voice\ARMA\ARMA067";
			dialog.Text = DLG_TEXT[248];
			Link.l1 = DLG_TEXT[249];
			Link.l1.go = "trade_1";
			Link.l2 = DLG_TEXT[250];
			Link.l2.go = "items";
			Link.l3 = DLG_TEXT[251];
			Link.l3.go = "exit";
		break;

		case "trade_1":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			LaunchStore(FALAISE_DE_FLEUR_STORE);
		break;

		case "items":
			if (npchar.quest.item_date != lastspeak_date)
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}
			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar);
		break;

		case "redmond_done":
			dialog.snd = "Voice\ARMA\ARMA068";
			Dialog.text = DLG_TEXT[252];
			link.l1 = DLG_TEXT[253];
			link.l1.go = "redmond_done_1";
		break;

		case "redmond_done_1":
			dialog.snd = "Voice\ARMA\ARMA069";
			Dialog.text = DLG_TEXT[254];
			link.l1 = DLG_TEXT[255];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, makeint(npchar.money.quest));
			AddPartyExp(pchar, 700);
			npchar.money.quest = "0";
			npchar.quest_begin = "0";
		break;

		case "baldewyn":
			dialog.snd = "Voice\ARMA\ARMA070";
			dialog.text = DLG_TEXT[256];
			link.l1 = DLG_TEXT[257];
			link.l1.go = "baldewyn_1";
		break;

		case "baldewyn_1":
			dialog.snd = "Voice\ARMA\ARMA071";
			dialog.text = DLG_TEXT[258] + Address_Form.Fra + DLG_TEXT[259];
			link.l1 = DLG_TEXT[260];
			link.l1.go = "baldewyn_2";
		break;

		case "baldewyn_2":
			dialog.snd = "Voice\ARMA\ARMA072";
			dialog.text = DLG_TEXT[261] + Characters[GetCharacterIndex(DLG_TEXT[262])].name + " " + Characters[GetCharacterIndex(DLG_TEXT[263])].lastname + DLG_TEXT[264];
			link.l1 = DLG_TEXT[265];
			link.l1.go = "baldewyn_3";
		break;

		case "baldewyn_3":
			dialog.snd = "Voice\ARMA\ARMA073";
			dialog.text = DLG_TEXT[266] + Address_Form.Fra + DLG_TEXT[267];
			link.l1 = DLG_TEXT[268];
			link.l1.go = "baldewyn_6";
			npchar.quest.money = "500";
			link.l2 = DLG_TEXT[269] + npchar.name + DLG_TEXT[270];
			link.l2.go = "baldewyn_4";
		break;

		case "baldewyn_4":
			if (makeint(pchar.skill.commerce) > 3)
			{
				dialog.snd = "Voice\ARMA\ARMA074";
				dialog.text = DLG_TEXT[271];
				link.l1 = DLG_TEXT[272];
				link.l1.go = "baldewyn_6";
				npchar.quest.money = "750";
			}
			else
			{
				if (pchar.reputation > 50)
				{
					dialog.snd = "Voice\ARMA\ARMA075";
					dialog.text = DLG_TEXT[273];
				}
				else
				{
					dialog.snd = "Voice\ARMA\ARMA076";
					dialog.text = DLG_TEXT[274];
				}
				link.l1 = DLG_TEXT[275];
				link.l1.go = "baldewyn_6";
				npchar.quest.money = "500";
			}
			link.l2 = DLG_TEXT[276];
			link.l2.go = "baldewyn_5";
		break;

		case "baldewyn_5":
			dialog.snd = "Voice\ARMA\ARMA077";
			dialog.text = DLG_TEXT[277];
			link.l1 = DLG_TEXT[278];
			link.l1.go = "exit";
			characters[GetCharacterIndex("Baldewyn Coffier")].quest.hire = "arno_denied";
			link.l2 = DLG_TEXT[279];
			link.l2.go = "baldewyn_6";
		break;

		case "baldewyn_6":
			dialog.snd = "Voice\ARMA\ARMA078";
			dialog.text = DLG_TEXT[280];
			link.l1 = DLG_TEXT[281];
			link.l1.go = "exit";
			characters[GetCharacterIndex("Baldewyn Coffier")].quest.hire = "arno";
			npchar.quest_begin = "1";
		break;

		case "baldewyn_done":
			dialog.snd = "Voice\ARMA\ARMA079";
			dialog.text = DLG_TEXT[282];
			link.l1 = DLG_TEXT[283];
			link.l1.go = "baldewyn_done_1";
			link.l2 = DLG_TEXT[284];
			link.l2.go = "baldewyn_done_2";
		break;

		case "baldewyn_done_1":
			dialog.snd = "Voice\ARMA\ARMA080";
			dialog.text = DLG_TEXT[285];
			link.l1 = DLG_TEXT[286];
			link.l1.go = "baldewyn_done_2";
			link.l2 = DLG_TEXT[287];
			link.l2.go = "exit";
		break;

		case "baldewyn_done_2":
			dialog.snd = "Voice\ARMA\ARMA081";
			dialog.text = DLG_TEXT[288];
			link.l1 = DLG_TEXT[289];
			link.l1.go = "baldewyn_bye";
			link.l2 = DLG_TEXT[290];
			link.l2.go = "baldewyn_done_3";
		break;

		case "baldewyn_done_3":
			dialog.snd = "Voice\ARMA\ARMA082";
			dialog.text = DLG_TEXT[291];
			link.l1 = DLG_TEXT[292];
			link.l1.go = "baldewyn_bye_2";
			link.l2 = DLG_TEXT[293];
			link.l2.go = "baldewyn_bye_3";
		break;

		case "baldewyn_bye":
			dialog.snd = "Voice\ARMA\ARMA083";
			dialog.text = DLG_TEXT[294];
			link.l1 = DLG_TEXT[295] + Address_Form.Fra + DLG_TEXT[296];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT[297];
			link.l2.go = "First Time";
			characters[GetCharacterIndex("Baldewyn Coffier")].quest.hire = "done";
			npchar.quest_begin = "0";
			npchar.quest.money = "0";
			Rumour[4].state = "active";
			characters[GetCharacterIndex("Baldewyn Coffier")].location = "none";
			Characters[GetCharacterIndex("Sabine Matton")].location = "Falaise_De_Fleur_store";
		break;

		case "baldewyn_bye_2":
			dialog.snd = "Voice\ARMA\ARMA084";
			dialog.text = DLG_TEXT[298];
			link.l1 = DLG_TEXT[299];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT[300];
			link.l2.go = "First Time";
			characters[GetCharacterIndex("Baldewyn Coffier")].quest.hire = "done";
			npchar.quest_begin = "0";
			AddMoneyToCharacter(pchar, makeint(npchar.money.quest));
			ChangeCharacterReputation(pchar, -1);
			AddPartyExp(pchar, 700);
			npchar.quest.money = "0";
			Rumour[4].state = "active";
			characters[GetCharacterIndex("Baldewyn Coffier")].location = "none";
			Characters[GetCharacterIndex("Sabine Matton")].location = "Falaise_De_Fleur_store";
		break;

		case "baldewyn_bye_3":
			if (makeint(pchar.skill.commerce) > 5)
			{
				dialog.snd = "Voice\ARMA\ARMA085";
				dialog.text = DLG_TEXT[301] + makeint(npchar.quest.money) * 2 + DLG_TEXT[302];
				link.l1 = DLG_TEXT[303];
				link.l1.go = "exit";
				link.l2 = DLG_TEXT[304];
				link.l2.go = "First Time";
				characters[GetCharacterIndex("Baldewyn Coffier")].quest.hire = "done";
				npchar.quest_begin = "0";
				AddMoneyToCharacter(pchar, makeint(npchar.money.quest)*2);
				ChangeCharacterReputation(pchar, -1);
				AddPartyExp(pchar, 700);
				npchar.quest.money = "0";
				Rumour[4].state = "active";
				characters[GetCharacterIndex("Baldewyn Coffier")].location = "none";
				Characters[GetCharacterIndex("Sabine Matton")].location = "Falaise_De_Fleur_store";
			}
			else
			{
				dialog.snd = "Voice\ARMA\ARMA086";
				dialog.text = DLG_TEXT[305];
				link.l1 = DLG_TEXT[306] + Address_Form.Fra + DLG_TEXT[307];
				link.l1.go = "exit";
				link.l2 = DLG_TEXT[308];
				link.l2.go = "baldewyn_bye_2";
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
