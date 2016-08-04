#event_handler("InitHelpSegment","fast_commands_InitHelp");
#event_handler("ResetHelpSegment","fast_commands_ResetHelp");

void fast_commands_InitHelp()
{
	string sectName = GetEventData();
	if(sectName!="fast_commands") return;

	// �������� ����� ����������
		// �������
	SetNewPicture("HELPPICTURE","interfaces\helppictures\fast_commands.tga");
		// ������
	int strFileID = LanguageOpenFile("helpsections\fast_commands.txt");
	SetFormatedText("TEXTWINDOW",LanguageConvertString(strFileID,"fast_commands_info"));
	GameInterface.strings.HelpName = LanguageConvertString(strFileID,"fast_commands_title");
	LanguageCloseFile(strFileID);
}

void fast_commands_ResetHelp()
{
	string sectName = GetEventData();
	if(sectName!="fast_commands") return;

	// ������ � ����� ���
	SetNewPicture("HELPPICTURE","");
	SetFormatedText("TEXTWINDOW","");
}
