#include "DIALOGS\Usurer_dialog.h"
void ProcessDialogEvent()
{
	int LoanSum, LoanInterest, LoanPeriod, LoanResult, iPastMonths, DepositSum, DepositInterest, DepositResult;
	ref NPChar, PChar, d;
	PChar = GetMainCharacter();
	aref Link, Diag;	
	string NPC_Area;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);

	NPC_Area = Npchar.quest.area;
	
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------������ ������ - ������ �������

	
		case "LoanGranted_exit":
			Diag.CurrentNode = Diag.TempNode;

			AddMoneyToCharacter(Pchar, makeint(Pchar.Quest.Loans.(NPC_Area).Sum));
			Pchar.Quest.Loans.(NPC_Area) = true;
			Pchar.Quest.Loans.(NPC_Area).StartDay = getDataDay();
			Pchar.Quest.Loans.(NPC_Area).StartMonth = getDataMonth();
			Pchar.Quest.Loans.(NPC_Area).StartYear = getDataYear();
			Pchar.Quest.Loans.(NPC_Area).StartTime = getTime();

			Pchar.quest.(NPC_Area).win_condition.l1 = "Timer";
			Pchar.quest.(NPC_Area).win_condition.l1.date.day = getDataDay(); 
			Pchar.quest.(NPC_Area).win_condition.l1.date.month = getDataMonth() + makeint(Pchar.Quest.Loans.(NPC_Area).Period);
			Pchar.quest.(NPC_Area).win_condition.l1.date.year = getDataYear();  
			Pchar.quest.(NPC_Area).win_condition = "Loans_" + (NPC_Area);	
			
			DialogExit();

		break;

		case "Deposit_exit":
			Diag.CurrentNode = Diag.TempNode;			
			
		//	DepositSum = -DepositSum;
			AddMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Deposits.(NPC_Area).Sum)));
			Pchar.Quest.Deposits.(NPC_Area) = true;
			Pchar.Quest.Deposits.(NPC_Area).StartDay = getDataDay();
			Pchar.Quest.Deposits.(NPC_Area).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(NPC_Area).StartYear = getDataYear();
			Pchar.Quest.Deposits.(NPC_Area).StartTime = getTime();
			DialogExit();
		break;

		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
			DeleteAttribute(Pchar, "quest.Deposits." + (NPC_Area));
		break;

		case "exit_NoChange":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

	
		case "First time":
			Dialog.defAni = "dialog_stay1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "dialog_stay2";
			Dialog.cam = "1";
			
			if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = 1; 
				Dialog.snd1 = "voice\USDI\USDI001";
				Dialog.snd2 = "voice\USDI\USDI002";
				Dialog.snd3 = "voice\USDI\USDI003";
				d.Text = RandPhrase(TimeGreeting() + DLG_TEXT[0], DLG_TEXT[1] + address_form.eng + DLG_TEXT[2], DLG_TEXT[3] + address_form.eng + DLG_TEXT[4], &Dialog, Dialog.snd1, Dialog.snd2, Dialog.snd3);
				Link.l1 = LinkRandPhrase(DLG_TEXT[5] + Pchar.name + " " + Pchar.lastname + DLG_TEXT[6], DLG_TEXT[7] + Pchar.name + " " + Pchar.lastname + DLG_TEXT[8], DLG_TEXT[9] + PChar.name + DLG_TEXT[10]);
				Link.l1.go = "meeting";
			}
			else
			{
					Dialog.snd1 = "voice\USDI\USDI004";
					Dialog.snd2 = "voice\USDI\USDI005";
					Dialog.snd3 = "voice\USDI\USDI006";
					d.Text = RandPhrase(DLG_TEXT[11] + PChar.name + DLG_TEXT[12], TimeGreeting() + DLG_TEXT[13], DLG_TEXT[14] + address_form.eng + DLG_TEXT[15], &Dialog, Dialog.snd1, Dialog.snd2, Dialog.snd3);
					Link.l1 = LinkRandPhrase(DLG_TEXT[16], DLG_TEXT[17], DLG_TEXT[18]);
					Link.l1.go = "loan";	
					if(makeint(Pchar.money) >= 100)
					{
						Link.l2 = LinkRandPhrase(DLG_TEXT[19], DLG_TEXT[20], DLG_TEXT[21]);
						Link.l2.go = "deposit";				
					}
					Link.l3 = DLG_TEXT[22] + NPchar.name + DLG_TEXT[23];
					Link.l3.go = "exit";

				if(CheckAttribute(Pchar, "Quest.Loans." + (NPC_Area)) && makeint(Pchar.Quest.Loans.(NPC_Area)) == true)
				{
					iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
					Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makeint(Pchar.Quest.Loans.(NPC_Area).Interest))*iPastMonths;

					Dialog.snd1 = "voice\USDI\USDI007";
					Dialog.snd2 = "voice\USDI\USDI008";
					Dialog.snd3 = "voice\USDI\USDI009";

					d.Text = RandPhrase(TimeGreeting() + DLG_TEXT[24] + PChar.name + DLG_TEXT[25] + Pchar.Quest.Loans.(NPC_Area).Result + DLG_TEXT[26], DLG_TEXT[27] + Pchar.Quest.Loans.(NPC_Area).Result + DLG_TEXT[28], DLG_TEXT[29] + address_form.eng + DLG_TEXT[30] + Pchar.Quest.Loans.(NPC_Area).Result + DLG_TEXT[31], &Dialog, Dialog.snd1, Dialog.snd2, Dialog.snd3);
					if(makeint(PChar.money) >= makeint(Pchar.Quest.Loans.(NPC_Area).Result))
					{
						Link.l1 = LinkRandPhrase(DLG_TEXT[32], DLG_TEXT[33], DLG_TEXT[34]);
						Link.l1.go = "loan_return";				
					}					
					Link.l2 = LinkRandPhrase(DLG_TEXT[35], DLG_TEXT[36] + NPChar.name + DLG_TEXT[37], DLG_TEXT[38]);
					Link.l2.go = "Loan_Remind";
					Link.l3 = DLG_TEXT[39];
					Link.l3.go = "exit_NoChange";

				}									
				if(CheckAttribute(Pchar, "Quest.Deposits." + (NPC_Area)) && makeint(Pchar.Quest.Deposits.(NPC_Area)) == true)
				{
					iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(NPC_Area).StartYear),makeint(Pchar.Quest.Deposits.(NPC_Area).StartMonth),makeint(Pchar.Quest.Deposits.(NPC_Area).StartDay), makefloat(Pchar.Quest.Deposits.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
					Pchar.Quest.Deposits.(NPC_Area).Result = makeint(Pchar.Quest.Deposits.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Deposits.(NPC_Area).Sum)/100)*makeint(Pchar.Quest.Deposits.(NPC_Area).Interest))*iPastMonths;
					Dialog.snd1 = "voice\USDI\USDI010";
					Dialog.snd2 = "voice\USDI\USDI011";
					Dialog.snd3 = "voice\USDI\USDI012";
					d.Text = RandPhrase(DLG_TEXT[40] + PChar.name + DLG_TEXT[41], TimeGreeting() + DLG_TEXT[42], DLG_TEXT[43] + address_form.eng + DLG_TEXT[44], &Dialog, Dialog.snd1, Dialog.snd2, Dialog.snd3);
					Link.l1 = LinkRandPhrase(DLG_TEXT[45], DLG_TEXT[46], DLG_TEXT[47]);
					Link.l1.go = "Deposit_return";									
					Link.l2 = DLG_TEXT[48] + NPchar.name + DLG_TEXT[49];
					Link.l2.go = "exit_NoChange";
					Link.l3 = DLG_TEXT[50];
					Link.l3.go = "exit_NoChange";
				}
			}
		break;

		case "Meeting":
			Dialog.snd1 = "voice\USDI\USDI013";
			Dialog.snd2 = "voice\USDI\USDI014";
			Dialog.snd3 = "voice\USDI\USDI015";
			d.Text = RandPhrase(DLG_TEXT[51] + NPChar.name + " " + NPChar.lastname + DLG_TEXT[52], DLG_TEXT[53] + NPChar.name + " " + NPChar.lastname + DLG_TEXT[54], DLG_TEXT[55] + NPChar.name + " " + NPChar.lastname + DLG_TEXT[56], &Dialog, Dialog.snd1, Dialog.snd2, Dialog.snd3);
			Link.l1 = LinkRandPhrase(DLG_TEXT[57], DLG_TEXT[58], DLG_TEXT[59]);
			Link.l1.go = "loan";
			if(makeint(Pchar.money) >= 100)
			{
				Link.l2 = LinkRandPhrase(DLG_TEXT[60], DLG_TEXT[61], DLG_TEXT[62]);
				Link.l2.go = "deposit";				
			}
			Link.l3 = DLG_TEXT[63] + NPchar.name + DLG_TEXT[64];
			Link.l3.go = "exit";
		break;

		case "loan":
			Dialog.snd = "voice\USDI\USDI016";
			d.Text = DLG_TEXT[65];
			Link.l1 = DLG_TEXT[66];
			Link.l1.go = "Small";
			Link.l2 = DLG_TEXT[67];
			Link.l2.go = "Medium";
			Link.l3 = DLG_TEXT[68];
			Link.l3.go = "Large";
		break;

		case "small":
			Pchar.Quest.Loans.(NPC_Area).Sum = 500*makeint(Pchar.rank);
			Dialog.snd = "voice\USDI\USDI017";
			d.Text = DLG_TEXT[69] + Pchar.Quest.loans.(NPC_Area).sum + DLG_TEXT[70];
			Link.l1 = DLG_TEXT[71];
			Link.l1.go = "Interest";
			Link.l2 = DLG_TEXT[72];
			Link.l2.go = "Loan";
			Link.l3 = DLG_TEXT[73];
			Link.l3.go = "Exit";
		break;

		case "Medium":
			Pchar.Quest.Loans.(NPC_Area).Sum = 1500*makeint(Pchar.rank);
			Dialog.snd = "voice\USDI\USDI018";
			d.Text = DLG_TEXT[74] + Pchar.Quest.Loans.(NPC_Area).sum + DLG_TEXT[75];
			Link.l1 = DLG_TEXT[76];
			Link.l1.go = "Interest";
			Link.l2 = DLG_TEXT[77];
			Link.l2.go = "Loan";
			Link.l3 = DLG_TEXT[78];
			Link.l3.go = "Exit";
		break;

		case "Large":
			Pchar.Quest.Loans.(NPC_Area).Sum = 3000*makeint(Pchar.rank);
			Dialog.snd = "voice\USDI\USDI019";
			d.Text = DLG_TEXT[79] + Pchar.Quest.Loans.(NPC_Area).sum + DLG_TEXT[80];
			Link.l1 = DLG_TEXT[81];
			Link.l1.go = "Interest";
			Link.l2 = DLG_TEXT[82];
			Link.l2.go = "Loan";
			Link.l3 = DLG_TEXT[83];
			Link.l3.go = "Exit";
		break;

		case "Interest":
			Pchar.Quest.Loans.(NPC_Area).Interest = 11 - makeint(Pchar.skill.commerce);	
			Dialog.snd = "voice\USDI\USDI020";
			d.Text = Pchar.Quest.Loans.(NPC_Area).Interest + DLG_TEXT[84]; 
			Link.l1 = DLG_TEXT[85];
			Link.l1.go = "Period";
			Link.l3 = DLG_TEXT[86];
			Link.l3.go = "Exit";
		break;

		case "Period":
			Pchar.Quest.Loans.(NPC_Area).Period = makeint(makeint(Pchar.reputation)/20) + 1;			
			Dialog.snd = "voice\USDI\USDI021";
			d.Text =  DLG_TEXT[87] + Pchar.name + DLG_TEXT[88] + Pchar.Quest.Loans.(NPC_Area).Period + DLG_TEXT[89]; 
			Link.l1 = DLG_TEXT[90];
			Link.l1.go = "LoanGranted";
			Link.l3 = DLG_TEXT[91];
			Link.l3.go = "Exit";
		break;


		case "LoanGranted":
			Dialog.snd = "voice\USDI\USDI022";
			d.Text = DLG_TEXT[92];
			Link.l1 = DLG_TEXT[93];
			Link.l1.go = "LoanGranted_exit";
		break;

		case "Loan_Remind":
			Dialog.snd = "voice\USDI\USDI023";
			d.Text = DLG_TEXT[94];
			Link.l1 = DLG_TEXT[95];
			Link.l1.go = "exit_NoChange";
		break;

		case "loan_return":
			addMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Loans.(NPC_Area).Result)));
			DeleteAttribute(PChar, "quest.loans." + (NPC_Area)); 
			Dialog.snd1 = "voice\USDI\USDI024";
			Dialog.snd2 = "voice\USDI\USDI025";
			Dialog.snd3 = "voice\USDI\USDI026";
			d.Text = RandPhrase(DLG_TEXT[96], DLG_TEXT[97],  DLG_TEXT[98] + address_form.fra + DLG_TEXT[99], &Dialog, Dialog.snd1, Dialog.snd2, Dialog.snd3);
			Link.l1 = LinkRandPhrase(DLG_TEXT[100], DLG_TEXT[101], DLG_TEXT[102]);
			Link.l1.go = "loan";
			if(makeint(PChar.money) >= 100)
			{
				Link.l2 = LinkRandPhrase(DLG_TEXT[103], DLG_TEXT[104], DLG_TEXT[105]);
				Link.l2.go = "deposit";				
			}
			Link.l3 = DLG_TEXT[106] + NPchar.name + DLG_TEXT[107];
			Link.l3.go = "exit";
		break;

		case "deposit":
			Dialog.snd1 = "voice\USDI\USDI027";
			Dialog.snd2 = "voice\USDI\USDI028";
			Dialog.snd3 = "voice\USDI\USDI029";
			d.Text = RandPhrase(DLG_TEXT[108], DLG_TEXT[109], DLG_TEXT[110], &Dialog, Dialog.snd1, Dialog.snd2, Dialog.snd3);
			Link.l1 = DLG_TEXT[111] + makeint(makeint(PChar.money)/40)*10 + DLG_TEXT[112];
			Link.l1.go = "quarter";
			Link.l2 = DLG_TEXT[113] + makeint(makeint(PChar.money)/20)*10 + DLG_TEXT[114];
			Link.l2.go = "half";
			Link.l3 = DLG_TEXT[115] + makeint(makeint(PChar.money)/10)*10 + DLG_TEXT[116];
			Link.l3.go = "All";
		break;

		case "quarter":
			Pchar.Quest.Deposits.(NPC_Area).Interest = makeint(Pchar.skill.commerce) + 1;			
			Pchar.Quest.Deposits.(NPC_Area).Sum = makeint(makeint(PChar.money)/40)*10;
			Dialog.snd = "voice\USDI\USDI030";
			d.Text = DLG_TEXT[117] + Pchar.Quest.Deposits.(NPC_Area).Interest + DLG_TEXT[118];
			Link.l1 = DLG_TEXT[119];
			Link.l1.go = "Deposit_placed";
			Link.l2 = DLG_TEXT[120];
			Link.l2.go = "Deposit";
			Link.l3 = DLG_TEXT[121];
			Link.l3.go = "Exit";
		break;

		case "half":
			Pchar.Quest.Deposits.(NPC_Area).Interest = makeint(Pchar.skill.commerce) + 1;			
			Pchar.Quest.Deposits.(NPC_Area).Sum = makeint(makeint(PChar.money)/20)*10;
			Dialog.snd = "voice\USDI\USDI031";
			d.Text = DLG_TEXT[122] + Pchar.Quest.Deposits.(NPC_Area).Interest + DLG_TEXT[123];
			Link.l1 = DLG_TEXT[124];
			Link.l1.go = "Deposit_placed";
			Link.l2 = DLG_TEXT[125];
			Link.l2.go = "Deposit";
			Link.l3 = DLG_TEXT[126];
			Link.l3.go = "Exit";		
		break;

		case "All":
			Pchar.Quest.Deposits.(NPC_Area).Interest = makeint(Pchar.skill.commerce) + 1;			
			Pchar.Quest.Deposits.(NPC_Area).Sum = makeint(makeint(PChar.money)/10)*10;
			Dialog.snd = "voice\USDI\USDI032";
			d.Text = DLG_TEXT[127] + Pchar.Quest.Deposits.(NPC_Area).Interest + DLG_TEXT[128];
			Link.l1 = DLG_TEXT[129];
			Link.l1.go = "Deposit_placed";
			Link.l2 = DLG_TEXT[130];
			Link.l2.go = "Deposit";
			Link.l3 = DLG_TEXT[131];
			Link.l3.go = "Exit";		
		break;

		case "Deposit_placed":
			Dialog.snd = "voice\USDI\USDI033";
			d.Text = DLG_TEXT[132];
			Link.l1 = DLG_TEXT[133];			
			Link.l1.go = "Deposit_Exit";		
		break;

		case "Deposit_return":
			Dialog.snd = "voice\USDI\USDI034";
			d.Text = DLG_TEXT[134] + Pchar.Quest.Deposits.(NPC_Area).Result + DLG_TEXT[135];
			Link.l1 = DLG_TEXT[136];			
			Link.l1.go = "Deposit_return_1";		
			Link.l2 = DLG_TEXT[137];			
			Link.l2.go = "Exit_noChange";		
		break;

		case "Deposit_return_1":
			addMoneyToCharacter(Pchar, makeint(Pchar.Quest.Deposits.(NPC_Area).Result));
			DeleteAttribute(PChar,"quest.deposits." + (NPC_Area));
			Dialog.snd = "voice\USDI\USDI035";
			d.Text = DLG_TEXT[138];			
			Link.l1 = DLG_TEXT[139];			
			Link.l1.go = "Exit";		
		break;

		case "DeadMotherfucker":
			Dialog.Tempnode = "DeadMotherFucker_1";
			Dialog.snd = "voice\USDI\USDI035";
			d.Text = DLG_TEXT[140];			
			Link.l1 = DLG_TEXT[141];			
			Link.l1.go = "Exit";		
		break;

		case "DeadMotherFucker_1":			
			Dialog.snd = "voice\USDI\USDI035";
			d.Text = DLG_TEXT[142];			
			Link.l1 = DLG_TEXT[143];			
			Link.l1.go = "Exit";		
		break;


		}
}

