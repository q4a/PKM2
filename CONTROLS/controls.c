
#event_handler("frame","procUpdateControlKeyGroup");

// control flags
#define USE_AXIS_AS_BUTTON				1
#define USE_AXIS_AS_INVERSEBUTTON		2
#define INVERSE_CONTROL					4

string curKeyGroupName = "";
object objControlsState;
extern void ExternControlsInit(bool bFirst);

void ControlsInit(string sPlatformName,bool bFirst)
{
	DeleteAttribute(&objControlsState,"");

	string initFileName = "";
	
	if(sPlatformName=="xbox")	initFileName = "controls\init_xbox.c";
	if(sPlatformName=="pc")		initFileName = "controls\init_pc.c";

	if(initFileName=="")
	{
		trace("Can`t init controls because not right platform");
		return;
	}

	if(LoadSegment(initFileName))
	{
		ExternControlsInit(bFirst);
		UnloadSegment(initFileName);
	}
	else
	{
		trace("Can`t init controls because not loaded segment "+initFileName);
		return;
	}
}

void RestoreKeysFromOptions(aref arControlsRoot)
{
	if( GetTargetPlatform()=="xbox" )
	{
		ControlsInit("xbox",false);
		return;
	}
	aref arRootKey,arKey;
	int nGroupQ,nKeyQ, i,j, state,ctrlCode,keyCode;
	string ctrlName,grName;

	nGroupQ = GetAttributesNum(arControlsRoot);

	for(i=0; i<nGroupQ; i++)
	{
		arRootKey = GetAttributeN(arControlsRoot,i);
		grName = GetAttributeName(arRootKey);
		nKeyQ = GetAttributesNum(arRootKey);
		for(j=0; j<nKeyQ; j++)
		{
			arKey = GetAttributeN(arRootKey,j);
			state = 0;
			if(CheckAttribute(arKey,"state"))
			{
				state = sti(arKey.state);
			}

			ctrlName = GetAttributeName(arKey);
			keyCode = CI_GetKeyCode(GetAttributeValue(arKey));
			CI_CreateAndSetControls( grName, ctrlName, keyCode, state, true );
		}
	}

	RunControlsContainers();
}

void CI_CreateContainer( string groupName, string containerName, float containerVal )
{
	objControlsContainer.(containerName) = containerVal;
	CI_CreateAndSetControls(groupName, containerName, -1, 0, false);
	DoControlInvisible(groupName, containerName);
}

void AddToContainer(string groupName, string containerName, string controlName, int KeyCode, int controlState, bool inverse )
{
	float fVal = objControlsContainer.(containerName);
	string keyName = CI_GetKeyName(KeyCode);
	if( CheckAttribute(&objControlsState,"key_codes."+keyName+".stick") &&
		sti(objControlsState.key_codes.(keyName).stick)==true )
	{
		fVal /= 15.0;
	}
	if(inverse) fVal = -fVal;
	objControlsContainer.(containerName).(controlName) = fVal;
	CI_CreateAndSetControls(groupName, controlName, KeyCode, controlState, false);
	DoControlInvisible(groupName, controlName);
}

void DoControlInvisible(string groupName, string controlName)
{
	if( CheckAttribute(&objControlsState,"keygroups."+groupName+"."+controlName) )
	{
		objControlsState.keygroups.(groupName).(controlName).invisible = true;
	}
}

string CI_CreateAndSetControls( string groupName, string controlName, int keyCode, int controlState, bool bRemappingEnable )
{
	if(controlName=="") return "";
	string retString = "";

	if( !CheckAttribute(&objControlsState,"map.controls."+controlName) )
	{	objControlsState.map.controls.(controlName) = CreateControl(controlName);
	}
	int cntrlCode = sti(objControlsState.map.controls.(controlName));

	if(keyCode>=0)
	{	string keyName = "key_" + keyCode;
		objControlsState.map.keys.(keyName) = controlName;
	}
	MapControl(cntrlCode,keyCode);

	if(keyCode<0 && controlState==0)
	{	controlState = USE_AXIS_AS_BUTTON;
	}

	if(controlState!=-1)
	{	SetControlFlags(cntrlCode,controlState);
	}
	else
	{	controlState=0;
	}

	if(groupName!="")
	{
		if( CheckAttribute(&objControlsState,"keygroups."+groupName+"."+controlName) )
		{	retString = objControlsState.keygroups.(groupName).(controlName);
		}
		else
		{	objControlsState.keygroups.(groupName).(controlName) = "";
		}
		SetControlsByKey(controlName,CI_GetKeyName(keyCode),controlState);
		objControlsState.keygroups.(groupName).(controlName).remapping = bRemappingEnable;
	}

	return retString;
}

void SetControlsByKey(string controlName, string keyName, int state)
{
	int i,nGQ;
	aref arKGRoot, arKG;

	makearef(arKGRoot,objControlsState.keygroups);
	nGQ = GetAttributesNum(arKGRoot);

	for(i=0; i<nGQ; i++)
	{
		arKG = GetAttributeN(arKGRoot,i);
		if( CheckAttribute(arKG,controlName) )
		{	arKG.(controlName) = keyName;
			arKG.(controlName).state = state;
		}
	}
}

void MapControlToGroup(string controlName,string groupName)
{
	// ������ ������������� ��������
	int i,nRootSize;
	aref arRoot,arGroup;

	makearef(arRoot,objControlsState.keygroups);
	nRootSize = GetAttributesNum(arRoot);

	for(i=0; i<nRootSize; i++)
	{
		arGroup = GetAttributeN(arRoot,i);
		if( CheckAttribute(arGroup,controlName) )
		{
			objControlsState.keygroups.(groupName).(controlName) = arGroup.(controlName);
			objControlsState.keygroups.(groupName).(controlName).state = arGroup.(controlName).state;
			if( CheckAttribute(arGroup,controlName+".invisible") ) {
				objControlsState.keygroups.(groupName).(controlName).invisible = arGroup.(controlName).invisible;
			}
			if( CheckAttribute(arGroup,controlName+".remapping") ) {
				objControlsState.keygroups.(groupName).(controlName).remapping = arGroup.(controlName).remapping;
			}
			return;
		}
	}
}

int CI_GetKeyCode(string keyName)
{
	if( CheckAttribute(&objControlsState,"key_codes."+keyName) )
	{	return sti(objControlsState.key_codes.(keyName));
	}

	trace("Can`t key named as: " + keyName);
	return -1;
}

string CI_GetKeyName(int code)
{
	aref arKeys,arCur;
	makearef(arKeys,objControlsState.key_codes);
	int nq = GetAttributesNum(arKeys);

	for(int i=0; i<nq; i++)
	{
		arCur = GetAttributeN(arKeys,i);
		if( sti(GetAttributeValue(arCur)) == code )
		{	return GetAttributeName(arCur);
		}
	}

	return "";
}

int ControlNameToCode(string cname)
{
	if( CheckAttribute(&objControlsState,"map.controls."+cname) )
	{	return sti(objControlsState.map.controls.(cname));
	}
	return -1;
}

void procUpdateControlKeyGroup()
{
	string newCurGroup = GetCurControlGroup();
	if(curKeyGroupName==newCurGroup) return;

	FreezeGroupControls(curKeyGroupName,true);
	FreezeGroupControls(newCurGroup,false);
	curKeyGroupName = newCurGroup;
}

string GetCurControlGroup()
{
	if( IsEntity(&aviVideoObj) ) return "VideoPlayer";
	if( bRunHelpChooser ) return "HelpChooser";

	if( sti(InterfaceStates.Launched) == true ) return "MainInterface";

	if( DialogRun ) return "DialogControls";

	if(IsEntity(&worldMap)) return "WorldMapControls";

	if(bSeaActive && !bAbordageStarted)
	{
		if( CheckAttribute(&BattleInterface,"ComState") && sti(BattleInterface.ComState) != 0 )
			return "BattleInterfaceControls";

		if( SeaCameras.Camera == "SeaDeckCamera" )	{ return "Sailing1Pers"; }
		else { return "Sailing3Pers"; }
	}

	if( CheckAttribute(&objLandInterface,"ComState") && sti(objLandInterface.ComState) != 0 )
		return "BattleInterfaceControls";

	ref mchref = GetMainCharacter();
	if( SendMessage(mchref,"ls",MSG_CHARACTER_EX_MSG,"IsFightMode") != 0 )
		return "FightModeControls";

	return "PrimaryLand";
}

void FreezeGroupControls(string grName, bool bFreeze)
{
	if(grName=="")
	{
		AllControlsFreeze(bFreeze);
		return;
	}
	if( !CheckAttribute(&objControlsState,"keygroups."+grName) ) return;

	int i,nq;
	aref arKeyRoot, arKey;

	makearef(arKeyRoot,objControlsState.keygroups.(grName));
	nq = GetAttributesNum(arKeyRoot);
	for(i=0; i<nq; i++)
	{
		arKey = GetAttributeN(arKeyRoot,i);
		LockControl(GetAttributeName(arKey),bFreeze);
	}
}

void AllControlsFreeze(bool bFreeze)
{
	int i,ngq, j,ncq;
	aref arRoot,arGroup;

	makearef(arRoot,objControlsState.keygroups);
	ngq = GetAttributesNum(arRoot);

	for(i=0; i<ngq; i++)
	{
		arGroup = GetAttributeN(arRoot,i);
		ncq = GetAttributesNum(arGroup);
		for(j=0; j<ncq; j++)
		{
			LockControl(GetAttributeName(GetAttributeN(arGroup,j)),bFreeze);
		}
	}
}

object objControlsContainer;
void RunControlsContainers()
{
	CreateEntity(&objControlsContainer,"controls_container");
	LayerAddObject("iExecute",&objControlsContainer,1);
}
