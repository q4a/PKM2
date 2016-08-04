//===========================================================================================
//			RULE:
//	pStore.StoreSize	- ������ �������� ("large" ��� "small") - ������ �� ���-�� ������,
//						�� ��������� ������� ������ "large".
//	pStore.Island		- id ������� � �������� ����������� �������.
//	pStore.Goods.���_������.NotUsed		- ��������������� � TRUE ��� ��� �������, ��������
//										������ ��������� � ������ ��������.
//										(�� ��������� false).
//===========================================================================================
void StoreInit()
{
	ref pStore;

	// Falaise de fleur
	Stores[FALAISE_DE_FLEUR_STORE].Island	= "FalaiseDeFleur";
	Stores[FALAISE_DE_FLEUR_STORE].group	= "Falaise_de_fleur";

	// Redmond
	Stores[REDMOND_STORE].Island	= "Redmond";
	Stores[REDMOND_STORE].group	= "Redmond";

	// Isla Muelle
	Stores[ISLA_MUELLE_STORE].Island	= "IslaMuelle";
	Stores[ISLA_MUELLE_STORE].group	= "Muelle";

	// Oxbay
	Stores[OXBAY_STORE].Island	= "Oxbay";
	Stores[OXBAY_STORE].Group	= "Oxbay";

	// ������������� ����� � Oxbay
	Stores[GREENFORD_STORE].Island	= "Oxbay";
	Stores[GREENFORD_STORE].Group	= "Greenford";	

	// Conceicao
	Stores[CONCEICAO_STORE].Island	= "Conceicao";
	Stores[CONCEICAO_STORE].Group	= "Conceicao";

	// ��������������
	Stores[SMUGGLERS_STORE].Island	= "Conceicao";
	Stores[SMUGGLERS_STORE].group	= "Conceicao";

	// Douwesen
	Stores[DOUWESEN_STORE].Island	= "Douwesen";
	Stores[DOUWESEN_STORE].group	= "Douwesen";

	// Quebradas
	Stores[PIRATES_STORE].Island	= "QuebradasCostillas";
	Stores[PIRATES_STORE].group	= "QC";
}
