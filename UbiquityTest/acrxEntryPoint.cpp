// (C) Copyright 2002-2007 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//----- acrxEntryPoint.cpp
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"

#include "rxmember.h"
#include "rxvaluetype.h"
#include "rxattrib.h"
#include "rxprop.h"

#include "MyDialog.h"

#include "MyProperties.h"

#include "AEN1MyCircle.h"

//-----------------------------------------------------------------------------
#define szRDS _RXST("AEN1")

/////////////////////////////////////////////////////////////////////
// ObjectARX EntryPoint /////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class CUbiquityTestApp : public AcRxArxApp {

public:
	CUbiquityTestApp () : AcRxArxApp () {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		// TODO: Load dependencies here

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode = AcRxArxApp::On_kInitAppMsg (pkt) ;

		acutPrintf(_T("%s%s%s%s%s"),
			_T("Ubiquity sample adds two custom properties to line entities and can list the properties of existing entities\n"),
			_T(" Commands:\n"),
			_T(" - SHOWPROPERTIES : Lists all the properties of the selected object in a tree control\n"),
			_T(" - CREATEMYCIRCLE : Creates our custom entity circle which provides additional properties\n"),
			_T(" - TOGGLEEXTRALINEPROPERTIES : Toggles if the extra two properties for line entities are shown or not in the property palette\n")); 

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		// TODO: Add your code here

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;

		return (retCode) ;
	}

	virtual void RegisterServerComponents () {
	}

	/// <summary>
	/// ShowProperties command
	/// Displays a dialog with a tree control that shows all the properties
	/// that are attached to the selected entity
	/// </summary>
	static void AEN1UbiquityTestShowProperties(void)
	{
		ads_name name;
		ads_point pt;

		if (RTNORM != acedEntSel(_T("Select an entity\n"), name, pt))
			return;

		AcDbObjectId id;
		acdbGetObjectId(id, name);

		CAcModuleResourceOverride resOverride;

		MyDialog md(id, acedGetAcadFrame());
		md.DoModal(); 
	}

	static void AEN1UbiquityTestCreateMyCircle(void)
	{
		AcDbDatabase * pDb = acdbHostApplicationServices()->workingDatabase();  

		AcDbBlockTableRecordPointer ptrMS(ACDB_MODEL_SPACE, pDb, AcDb::kForWrite);  

		AcDbObjectPointer<AEN1MyCircle> ptrMC;
		ptrMC.create();

		ptrMC->setRadius(5);

		ptrMS->appendAcDbEntity(ptrMC); 
	}

	static bool isExtraLinePropertiesOn;

	static void AEN1UbiquityTestToggleExtraLineProperties(void)
	{
		if (isExtraLinePropertiesOn)
			MyPropertyFacetProvider::removeProvider(); 
		else
			MyPropertyFacetProvider::addProvider(); 

		isExtraLinePropertiesOn = !isExtraLinePropertiesOn;  
	}
} ;

bool CUbiquityTestApp::isExtraLinePropertiesOn = false;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CUbiquityTestApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CUbiquityTestApp, AEN1UbiquityTest, ShowProperties, ShowProperties, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CUbiquityTestApp, AEN1UbiquityTest, CreateMyCircle, CreateMyCircle, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CUbiquityTestApp, AEN1UbiquityTest, ToggleExtraLineProperties, ToggleExtraLineProperties, ACRX_CMD_MODAL, NULL)
