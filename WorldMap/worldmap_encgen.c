

//--------------------------------------------------------------------------------------
//��������� �����������
//--------------------------------------------------------------------------------------

//������� ������� � �������
#define WDM_STORM_RATE			0.002
//������� ��������� � �������
#define WDM_MERCHANTS_RATE		0.2
//������� ������� �������� � �������
#define WDM_WARRING_RATE		0.03
//������� ���������� �������� � �������
#define WDM_FOLLOW_RATE			0.06

//--------------------------------------------------------------------------------------







float wdmTimeOfLastStorm = 0.0;
float wdmTimeOfLastMerchant = 0.0;
float wdmTimeOfLastWarring = 0.0;
float wdmTimeOfLastFollow = 0.0;



void wdmReset()
{
	wdmTimeOfLastStorm = 0.0;
	wdmTimeOfLastMerchant = 0.0;
	wdmTimeOfLastWarring = 0.0;
	wdmTimeOfLastFollow = 0.0;
}

//Storm
void wdmStormGen(float dltTime, float playerShipX, float playerShipZ, float playerShipAY)
{
	ref mc = GetMainCharacter();
	bool encoff = false;
	if(CheckAttribute(mc,"worldmapencountersoff") == 1)
	{
		if(sti(mc.worldmapencountersoff)) return;
	}
	int numStorms = wdmGetNumberStorms();
	if(numStorms < 1)
	{
		wdmTimeOfLastStorm = wdmTimeOfLastStorm + dltTime*WDM_STORM_RATE*1000.0;
		if(rand(1001) < wdmTimeOfLastStorm)
		{
			wdmCreateStorm();
			wdmTimeOfLastStorm = 0.0;
		}
	}else{
		wdmTimeOfLastStorm = 0.0;
	}
}

//Random ships
void wdmShipEncounter(float dltTime, float playerShipX, float playerShipZ, float playerShipAY)
{
	int numShips = wdmGetNumberShipEncounters();
	if(numShips < 5)
	{
		rand(1001);
		//����������� ���������
		wdmTimeOfLastMerchant = wdmTimeOfLastMerchant + dltTime*WDM_MERCHANTS_RATE*1000.0;
		wdmTimeOfLastWarring = wdmTimeOfLastWarring + dltTime*WDM_WARRING_RATE*1000.0;
		wdmTimeOfLastFollow = wdmTimeOfLastFollow + dltTime*WDM_FOLLOW_RATE*1000.0;
		//����������� �� ���������� ���������
		float nump = 1.0 - numShips*0.15;
		//�������������� �����������
		int i1 = -1;
		int i2 = -1;
		//��������
		ref mc = GetMainCharacter();
		bool encoff = false;
		if(CheckAttribute(mc,"worldmapencountersoff") == 1)
		{
			encoff = sti(mc.worldmapencountersoff);
		}
		if(rand(1001) + 1 < wdmTimeOfLastMerchant)
		{
			wdmTimeOfLastMerchant = 0.0;
			if(GenerateMapEncounter(WDM_ETYPE_MERCHANT, wdmGetCurrentIsland(), &i1, &i2) == false) return;
			wdmCreateMerchantShip(i1, "", rand(50) - 20);
		}else{
			if(encoff == false)
			{
				if(rand(1001) + 1 < wdmTimeOfLastWarring)
				{
					wdmTimeOfLastWarring = 0.0;
					if(GenerateMapEncounter(WDM_ETYPE_WARRING, wdmGetCurrentIsland(), &i1, &i2) == false) return;
					wdmCreateWarringShips(i1, i2);
				}else{
					if(rand(1001) + 1 < wdmTimeOfLastFollow)
					{
						wdmTimeOfLastFollow = 0.0;
						if(GenerateMapEncounter(WDM_ETYPE_FOLLOW, wdmGetCurrentIsland(), &i1, &i2) == false) return;
						wdmCreateFollowShip(i1, rand(50) - 20);
					}
				}
			}
		}
	}else{
		wdmTimeOfLastMerchant = 0.0;
		wdmTimeOfLastWarring = 0.0;
		wdmTimeOfLastFollow = 0.0;
	}
}


string wdmGetCurrentIsland()
{
	if(wdmCurrentIsland != WDM_NONE_ISLAND)
	{
		return wdmCurrentIsland;
	}
	return "";
}


//Quest ships
void wdmQuestShipEncounter(float dltTime, float playerShipX, float playerShipZ, float playerShipAY)
{


}

//true if storm whith tornado
bool wdmDisableTornadoGen = true;
bool wdmTornadoGenerator()
{
	if(wdmDisableTornadoGen) return false;
	if(wdmCurrentIsland !=	WDM_NONE_ISLAND) return false;
	int r = rand(1000);
	if(r == 0) return false;
	return r < 450;
}


