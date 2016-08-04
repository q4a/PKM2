object	SeaCameras;
aref	Crosshair;
object	SeaShipCamera,SeaFreeCamera,SeaDeckCamera;
ref		SeaShipCharacterForCamera;
bool	bCanSwitchCameras = true;

void DeleteSeaCamerasEnvironment()
{
	DeleteClass(&SeaCameras);
	DeleteClass(&SeaFreeCamera);
	DeleteClass(&SeaShipCamera);
	DeleteClass(&SeaDeckCamera);
	DelEventHandler("SeaCameras_Switch", "SeaCameras_Switch");
	DelEventHandler(TELESCOPE_ACTIVE, "SeaCameras_TelescopeActive");
}

void CreateSeaCamerasEnvironment()
{
	bCanSwitchCameras = true;

	CreateEntity(&SeaCameras, "SEA_CAMERAS");
	CreateEntity(&SeaFreeCamera, "FREE_CAMERA");
	CreateEntity(&SeaShipCamera, "SHIP_CAMERA");
	CreateEntity(&SeaDeckCamera, "DECK_CAMERA");

	LayerAddObject("system_messages", &SeaCameras, 1);
	LayerAddObject(SEA_EXECUTE, &SeaShipCamera, 1);
	LayerAddObject(SEA_EXECUTE, &SeaFreeCamera, 1);
	LayerAddObject(SEA_EXECUTE, &SeaDeckCamera, 1);

	SeaFreeCamera.Perspective = 1.285;

	// Ship camera paramerets
	SeaShipCamera.Perspective = 1.285;
	SeaShipCamera.SensivityDistance = 30.0;
	SeaShipCamera.SensivityHeightAngle = 0.02;
	SeaShipCamera.SensivityHeightAngleOnShip = 0.005;
	SeaShipCamera.SensivityAzimuthAngle = 0.04;
	SeaShipCamera.MaxAngleX = 0.2;
	SeaShipCamera.MinAngleX = -1.4;
	SeaShipCamera.Distance = 69.0;
	SeaShipCamera.MinDistance = 25.0;
	SeaShipCamera.MaxDistance = 70.0;
	SeaShipCamera.MinHeightOnSea = 1.0;
	SeaShipCamera.MaxHeightOnShip = 16.0;
	SeaShipCamera.InvertMouseX = 1.0;
	SeaShipCamera.InvertMouseY = -1.0;

	// Deck camera paramerets
	SeaDeckCamera.Perspective = 1.285;
	SeaDeckCamera.SensivityDistance = 0.01;
	SeaDeckCamera.SensivityHeightAngle = 0.0015;
	SeaDeckCamera.SensivityAzimuthAngle = 0.0015;
	SeaDeckCamera.StepUp = 0.5;
	SeaDeckCamera.StepMin = 0.01;
	SeaDeckCamera.h_max = 2.0;
	SeaDeckCamera.h_min = 0.5;
	SeaDeckCamera.h_step = 0.1;
	SeaDeckCamera.h_def = 1.6;
	SeaDeckCamera.MaxAngleX = 1.5;
	SeaDeckCamera.MinAngleX = -1.5;
	SeaDeckCamera.RockingX = 0.8;
	SeaDeckCamera.RockingZ = 0.8;

	SeaCameras.Camera = "SeaShipCamera";
	makearef(Crosshair,SeaCameras.Crosshair);

	Crosshair.OutsideCamera = true;
	Crosshair.Texture = "crosshair\crosshair.tga";
	Crosshair.Size = 0.05;
	Crosshair.Technique = "Crosshair";
	Crosshair.SubTexX = 1;
	Crosshair.SubTexY = 1;
	Crosshair.Colors.Default = argb(0, 255, 255, 255);
	Crosshair.Colors.Enemy = argb(0, 255, 0, 0);
	Crosshair.Colors.Friend = argb(0, 0, 255, 0);
	Crosshair.Colors.Neutral = argb(0, 128, 128, 128);

	SendMessage(&AISea, "la", AI_MESSAGE_SET_CAMERAS_ATTRIBUTE, &SeaCameras);

	SetEventHandler("SeaCameras_Switch", "SeaCameras_Switch", 1);
	SetEventHandler(TELESCOPE_ACTIVE, "SeaCameras_TelescopeActive", 0);
}

void SeaCameras_TelescopeActive()
{
	int iTelescopeActive = GetEventData();
	if (iTelescopeActive)
	{
		bCanSwitchCameras = false;
		Crosshair.OutsideCamera = true;
	}
	else
	{
		bCanSwitchCameras = true;
		Crosshair.OutsideCamera = SeaCameras_isCameraOutside();
	}
}

void SeaCameras_Switch()
{
	if (!bCanSwitchCameras) return;

	int bSwitch = false;
	//Trace("Sea Camera Switch");
	switch (SeaCameras.Camera)
	{
		case "SeaFreeCamera":
			SeaCameras.Camera = "SeaShipCamera";
			Crosshair.OutsideCamera = true;
			PeopleOnShip.IsOnDeck = 0;
			bSwitch = true;
		break;
		case "SeaShipCamera":
			if (!LAi_IsDead(&Characters[GetMainCharacterIndex()]))
			{
				SeaCameras.Camera = "SeaDeckCamera";
				Crosshair.OutsideCamera = false;
				PeopleOnShip.IsOnDeck = 1;
				bSwitch = true;
			}
		break;
		case "SeaDeckCamera":
			switch (GetTargetPlatform())
			{
				case "xbox": SeaCameras.Camera = "SeaShipCamera"; break;	// 
				case "pc": SeaCameras.Camera = "SeaShipCamera"; break;		// Debug : SeaFreeCamera, release : SeaShipCamera
				//case "pc": SeaCameras.Camera = "SeaFreeCamera"; break;		// Debug : SeaFreeCamera, release : SeaShipCamera
			}
			//SeaCameras.Camera = "SeaFreeCamera"; // SeaShipCamera
			Crosshair.OutsideCamera = true;
			PeopleOnShip.IsOnDeck = 0;
			bSwitch = true;
		break;
	}
	if (bSwitch) SeaCameras_UpdateCamera();
}

void SeaCameras_UpdateCamera()
{
	switch (SeaCameras.Camera)
	{
		case "SeaShipCamera":
			SendMessage(&SeaCameras, "ia", SeaShipCamera, &SeaShipCharacterForCamera);
		break;
		case "SeaFreeCamera":
			SendMessage(&SeaCameras, "ia", SeaFreeCamera, &SeaShipCharacterForCamera);
		break;
		case "SeaDeckCamera":
			SendMessage(&SeaCameras, "ia", SeaDeckCamera, &SeaShipCharacterForCamera);
		break;
	}
}

void SeaCameras_SetDieCamera()
{
	bool bOldCanSwitchCameras;
	if (SeaCameras.Camera == "SeaDeckCamera")
	{
		SeaCameras.Camera = "SeaShipCamera";
		Crosshair.OutsideCamera = true;
		PeopleOnShip.IsOnDeck = 0;
		DeleteClass(&Telescope);
		SeaCameras_UpdateCamera();
	}
}

bool SeaCameras_isCameraOutside()
{
	if (SeaCameras.Camera == "SeaShipCamera") return true;
	if (SeaCameras.Camera == "SeaFreeCamera") return true;
	if (SeaCameras.Camera == "SeaDeckCamera") return false;
	return false;
}

void SeaCameras_SetShipForSeaCamera(object Character)
{
	makeref(SeaShipCharacterForCamera, Character);
	SeaCameras_UpdateCamera();
}