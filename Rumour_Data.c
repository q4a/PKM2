//������� ������, � �� ���������. "active" - ���� ������� � ���� ��������� ������ �����, "passive" - ���� �������� �� ����
#define MAX_RUMOURS 7
object	Rumour[MAX_RUMOURS];


void SetRumourDefaults()
{
	Rumour[0].text = "��������� ����� ������ ����������� �� �������. ����� ����� �������� � �����. ������ ���� �������!";
	Rumour[0].state = "active";

	Rumour[1].text = "�������, ��� �� �������� ���� �� ���� �������� �����-�� ������� �������� �����������. ������ �������� ��������, �����, ����� � ������. � �� ����� ������!";
	Rumour[1].state = "active";

	Rumour[2].text = "� ������, ��� ���������� �������� ���-�� �������� �������� ����� � ������ �� ��������� ����� � ������� ������ ������, ��� ��� ���������� �������� ���� �� ����, ����������� ��� ������.";
	Rumour[2].state = "active";

	Rumour[3].text = "�������, ��� ���� ������� 2 �� ��������� ��-�� ������� ���� �������� ������!";
	Rumour[3].state = "active";

	Rumour[4].text = "� ���� ����� �������� ���� ����������� ���������, ���� ����� ��� - ������ ALexusB ;)";
	Rumour[4].state = "active";

	Rumour[5].text = "����� ������ ������! ����� ������ ������� ��� ����� ������� � ����!";
	Rumour[5].state = "active";

	Rumour[6].text = "�� ���? � � ������, ��� ���� �������� �� ��� ���� �� �������!";
	Rumour[6].state = "active";
	
/*
    Rumour[10].text = "";
    Rumour[10].state = "active";
    */
}