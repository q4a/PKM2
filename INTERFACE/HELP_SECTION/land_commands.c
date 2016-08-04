#event_handler("InitHelpSegment","land_commands_InitHelp");
#event_handler("ResetHelpSegment","land_commands_ResetHelp");

void land_commands_InitHelp()
{
	string sectName = GetEventData();
	if(sectName!="land_commands") return;

	// �������� ����� ����������
		// �������
	SetNewPicture("HELPPICTURE","interfaces\helppictures\land_commands.tga");
		// ������
	int strFileID = LanguageOpenFile("helpsections\land_command_menu.txt");
	SetFormatedText("TEXTWINDOW",LanguageConvertString(strFileID,"land_commands_info"));
	GameInterface.strings.HelpName = LanguageConvertString(strFileID,"land_commands_title");
	LanguageCloseFile(strFileID);
}

void land_commands_ResetHelp()
{
	string sectName = GetEventData();
	if(sectName!="lands_commands") return;

	// ������ � ����� ���
	SetNewPicture("HELPPICTURE","");
	SetFormatedText("TEXTWINDOW","");
}
