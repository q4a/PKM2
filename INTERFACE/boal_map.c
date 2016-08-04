string totalInfo;
void InitInterface(string iniName)
{
    GameInterface.title = "titleBoal_map";

    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	CalculateInfoData();

	//int tmpLangFileID = LanguageOpenFile("interface_strings.txt");
	SetFormatedText("INFO_TEXT",totalInfo);//"�������, ���-�� ���� ������.");
	//LanguageCloseFile(tmpLangFileID);
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",5);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0); // ����� �� ����
	SetEventHandler("exitCancel","ProcessCancelExit",0); // ����� �� ���� �� �������� ��� Esc
	SetEventHandler("ievnt_command","ProcCommand",0); // ����� �� ����� ������ ��� (�� ���)
	SetEventHandler("evntDoPostExit","DoPostExit",0); // ����� �� ����������
}

void ProcessBreakExit()
{
	IDoExit( RC_INTERFACE_SALARY_EXIT );
	wdmReloadToSea();
}

void ProcessCancelExit()
{
	IDoExit( RC_INTERFACE_SALARY_EXIT );
	wdmReloadToSea();
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
	case "B_OK":
		if(comName=="activate" || comName=="click")
		{
			// �������
			PostEvent("evntDoPostExit",1,"l",RC_INTERFACE_SALARY_EXIT);
			wdmReloadToSea();
		}
	break;

	case "B_CANCEL":
		if(comName=="activate" || comName=="click")
		{
			//����������
			PostEvent("evntDoPostExit",1,"l",RC_INTERFACE_SALARY_EXIT);
		}
		if(comName=="upstep")
		{
			if(GetSelectable("B_OK"))	{SetCurrentNode("B_OK");}
		}
	break;
	}
}
void wdmRecalcReloadToSea()
{
/* ENCOUNTER_TYPE_MERCHANT0			0
#define ENCOUNTER_TYPE_MERCHANT1			1
#define ENCOUNTER_TYPE_MERCHANT2			2
#define ENCOUNTER_TYPE_PATROL				3
#define ENCOUNTER_TYPE_FLEET				4
#define ENCOUNTER_TYPE_CORSAR				5
#define ENCOUNTER_TYPE_PIRATE				6
#define ENCOUNTER_TYPE_PUNITIVE_SQUADRON	7

#define ENGLAND			0
#define FRANCE			1
#define SPAIN			2
#define PIRATE			3
#define HOLLAND			4
#define PORTUGAL		5
*/
	worldMap.encounter.type = "";
	totalInfo = "";
	//Encounters
	int numEncounters = wdmGetNumberShipEncounters();
	int isShipEncounterType = 0;
	ref rEncounter;
	for(int i = 0; i < numEncounters; i++)
	{
		if(wdmSetCurrentShipData(i))
		{
		    if(MakeInt(worldMap.encounter.select) == 0) continue;			
			isShipEncounterType++;
			if (isShipEncounterType>1)
			{
			    totalInfo = totalInfo + "vs. ";
			}
			rEncounter = &MapEncounters[sti(worldMap.encounter.type)];
			
			switch(sti(rEncounter.RealEncounterType))
	        {
		        case 0:		
			        totalInfo = totalInfo + "��������";
		        break;
		        case 1:		
			        totalInfo = totalInfo + "�������� � ��������������";
		        break;
		        case 2:		
			        totalInfo = totalInfo + "������� ������ ������� �����";
		        break;
		        case 3:		
			        totalInfo = totalInfo + "������� �������";
		        break;
		        case 4:		
			        totalInfo = totalInfo + "������� ������";
		        break;
		        case 5:		
			        totalInfo = totalInfo + "���� ��� ��������� ������� ��������";
		        break;
		        case 6:		
			        totalInfo = totalInfo + "�������";
		        break;
		        case 7:		
			        totalInfo = totalInfo + "����������� ����������";
		        break;
	        }
	        totalInfo = totalInfo + ", ���� ";
	        switch(sti(rEncounter.Nation))
	        {
		        case 0:		
			        totalInfo = totalInfo + "���������� ";
		        break;
		        case 1:		
			        totalInfo = totalInfo + "���������� ";
		        break;
		        case 2:		
			        totalInfo = totalInfo + "��������� ";
		        break;
		        case 3:		
			        totalInfo = totalInfo + "��������� ";
		        break;
		        case 4:		
			        totalInfo = totalInfo + "���������� ";
		        break;
		        case 5:		
			        totalInfo = totalInfo + "������������� ";
		        break;
		    }
		}
	}
	if (isShipEncounterType>1)
	{
	   totalInfo = "�������, �������� �� �����. ������, ��� ��� " + totalInfo;
	}
	else
	{
	   totalInfo = "�������, ���-�� ������. ������, ��� ��� " + totalInfo;
	}
}




void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void CalculateInfoData()
{
	
	CreateString(true,"payment","�������?",FONT_NORMAL,COLOR_NORMAL,320,258,SCRIPT_ALIGN_CENTER,1.0);
    wdmRecalcReloadToSea();
    ref mainCh = GetMainCharacter();
    
	if( (rand(100) / GetSummonSkillFromName(mainCh, SKILL_SNEAK)) > GetSummonSkillFromName(mainCh, SKILL_SAILING) )// ������� ���� ����� ��������� ��� ������� ������ ���
	{
		SetSelectable("B_CANCEL",false);
		SetCurrentNode("B_OK");
	}
}
