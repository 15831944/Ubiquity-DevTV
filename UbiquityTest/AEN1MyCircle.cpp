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
//----- AEN1MyCircle.cpp : Implementation of AEN1MyCircle
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "AEN1MyCircle.h"

//-----------------------------------------------------------------------------
Adesk::UInt32 AEN1MyCircle::kCurrentVersionNumber =1 ;

//-----------------------------------------------------------------------------
ACRX_DXF_DEFINE_MEMBERS_WITH_PROPERTIES (
	AEN1MyCircle, AcDbCircle,
	AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
	AcDbProxyEntity::kNoOperation, AEN1MYCIRCLE,
AEN1UBIQUITYTESTAPP
|Product Desc:     A description for your object
|Company:          Your company name
|WEB Address:      Your company WEB site address,
	AEN1MyCircle::makeMembers
)

//-----------------------------------------------------------------------------
AEN1MyCircle::AEN1MyCircle () : AcDbCircle () {
}

AEN1MyCircle::~AEN1MyCircle () {
}

//-----------------------------------------------------------------------------
//----- AcDbObject protocols
//- Dwg Filing protocol
Acad::ErrorStatus AEN1MyCircle::dwgOutFields (AcDbDwgFiler *pFiler) const {
	assertReadEnabled () ;
	//----- Save parent class information first.
	Acad::ErrorStatus es =AcDbCircle::dwgOutFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be saved first
	if ( (es =pFiler->writeUInt32 (AEN1MyCircle::kCurrentVersionNumber)) != Acad::eOk )
		return (es) ;
	//----- Output params
	//.....

	return (pFiler->filerStatus ()) ;
}

Acad::ErrorStatus AEN1MyCircle::dwgInFields (AcDbDwgFiler *pFiler) {
	assertWriteEnabled () ;
	//----- Read parent class information first.
	Acad::ErrorStatus es =AcDbCircle::dwgInFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be read first
	Adesk::UInt32 version =0 ;
	if ( (es =pFiler->readUInt32 (&version)) != Acad::eOk )
		return (es) ;
	if ( version > AEN1MyCircle::kCurrentVersionNumber )
		return (Acad::eMakeMeProxy) ;
	//- Uncomment the 2 following lines if your current object implementation cannot
	//- support previous version of that object.
	//if ( version < AEN1MyCircle::kCurrentVersionNumber )
	//	return (Acad::eMakeMeProxy) ;
	//----- Read params
	//.....

	return (pFiler->filerStatus ()) ;
}

//-----------------------------------------------------------------------------
//----- AcDbEntity protocols
Adesk::Boolean AEN1MyCircle::subWorldDraw (AcGiWorldDraw *mode) {
	assertReadEnabled () ;
	return (AcDbCircle::subWorldDraw (mode)) ;
}

Adesk::UInt32 AEN1MyCircle::subSetAttributes (AcGiDrawableTraits *traits) {
	assertReadEnabled () ;
	return (AcDbCircle::subSetAttributes (traits)) ;
}

/// <summary>
/// Called to provide the available properties
/// </summary>
void AEN1MyCircle::makeMembers(
        AcRxMemberCollectionBuilder& collectionBuilder,
        void* customData)
{
	collectionBuilder.add((AcRxMember*)MyDoubleProperty::makeMyDoubleProperty());
	collectionBuilder.add((AcRxMember*)MyColorProperty::makeMyColorProperty());
}
