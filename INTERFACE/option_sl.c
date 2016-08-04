
void OSL_WriteGameOption()
{
	object gopt;
	PrepareDefaultOption(&gopt);
	GetRealOptions(&gopt);
	SaveSavedOptions(&gopt);
}

void OSL_ReadGameOption()
{
	object gopt;
	PrepareDefaultOption(&gopt);
	ReadSavedOptions(&gopt);
	SetCurentOptions(&gopt);
}

void PrepareDefaultOption(ref optref)
{
	optref.volume.music = 0.5;
	optref.volume.sound = 0.5;
	optref.volume.dialog = 0.5;
	optref.cameramode.follow_on = true;
	optref.arcademode.arcade_on = true;
}

void GetRealOptions(ref optref)
{
	float ftmp1,ftmp2,ftmp3;

	ftmp1 = stf(optref.volume.sound);
	ftmp2 = stf(optref.volume.music);
	ftmp3 = stf(optref.volume.dialog);
	SendMessage(&sound,"leee", MSG_SOUND_GET_MASTER_VOLUME, &ftmp1, &ftmp2,	&ftmp3 );
	optref.volume.sound = ftmp1;
	optref.volume.music = ftmp2;
	optref.volume.dialog = ftmp3;

	optref.arcademode.arcade_on = bArcadeMode;

	optref.cameramode.follow_on = !locCameraEnableSpecialMode;

	if( CheckAttribute(&InterfaceStates,"InvertCameras") ) {
		optref.cameramode.InvertCameras = sti(InterfaceStates.InvertCameras);
	} else {
		optref.cameramode.InvertCameras = false;
	}

	GetControlsOptions(optref);
	/*aref arIn,arOut;
	makearef(arOut,objControlsState.keygroups);
	makearef(arIn,optref.controls);
	CopyAttributes(arIn,arOut);*/
}

void SetCurentOptions(ref optref)
{
	SendMessage(&sound,"lfff", MSG_SOUND_SET_MASTER_VOLUME,
		stf(optref.volume.sound),	stf(optref.volume.music),	stf(optref.volume.dialog)
	);

	bArcadeMode = sti(optref.arcademode.arcade_on);
	locCameraEnableSpecialMode = !sti(optref.cameramode.follow_on);
	if( CheckAttribute(optref,"cameramode.InvertCameras") ) {
		InterfaceStates.InvertCameras = optref.cameramode.InvertCameras;
	} else {
		InterfaceStates.InvertCameras = false;
	}

	aref arControls;
	makearef(arControls,optref.controls);
	RestoreKeysFromOptions(arControls);
}

void ReadSavedOptions(ref gopt)
{
	SendMessage(&GameInterface, "lsa", MSG_INTERFACE_LOADOPTIONS, "options", gopt);
}

void SaveSavedOptions(ref gopt)
{
	SendMessage(&GameInterface, "lsa", MSG_INTERFACE_SAVEOPTIONS, "options", gopt);
}

void GetControlsOptions(ref optref)
{
	int ng,qg, nc,qc;
	aref arIn, arOut, arGrp, arCntrl;
	string grName, cntrlName;

	makearef(arOut,objControlsState.keygroups);
	optref.controls = true;
	makearef(arIn,optref.controls);

	qg = GetAttributesNum(arOut);
	for(ng=0; ng<qg; ng++)
	{
		arGrp = GetAttributeN(arOut,ng);
		grName = GetAttributeName(arGrp);
		if( CheckAttribute(&objControlsState,"grouplist."+grName) && sti(objControlsState.grouplist.(grName))==true )
		{
			qc = GetAttributesNum(arGrp);
			for(nc=0; nc<qc; nc++)
			{
				arCntrl = GetAttributeN(arGrp,nc);
				if( CheckAttribute(arCntrl,"remapping") && sti(arCntrl.remapping)==true )
				{
					cntrlName = GetAttributeName(arCntrl);
					arIn.(grName).(cntrlName) = GetAttributeValue(arCntrl);
					arIn.(grName).(cntrlName).state = arCntrl.state;
				}
			}
		}
	}
}
