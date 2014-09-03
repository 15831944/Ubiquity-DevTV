#include "StdAfx.h"

#include "MyProperties.h"

#include "AEN1MyCircle.h"

/////////////////////////////////////////////////////////////////////
// Utility Fuctions /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

/// <summary>
/// Registers our application name if it is not registered already
/// </summary>
static Acad::ErrorStatus createRegApp(AcDbDatabase * pDb, const ACHAR * pAppName)
{
	Acad::ErrorStatus es;

	if (pDb == NULL)
		return Acad::eInvalidInput; 

	AcDbRegAppTablePointer appTable(pDb->regAppTableId(), AcDb::kForWrite);

	if((es = appTable.openStatus()) != Acad::eOk)
		return es;
    
	if(appTable->has(pAppName))
		return Acad::eOk;
    
	AcDbRegAppTableRecordPointer appTableRecord;
	appTableRecord.create(); 
	appTableRecord->setName(pAppName);
    
	if((es = appTable->add(appTableRecord)) != Acad::eOk)
		return es;

	return Acad::eOk;
}

/////////////////////////////////////////////////////////////////////
// MyPorpertyFacet //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

/// <summary>
/// This is called when the class descriptor of MyPropertyFacet is 
/// created (newAcRxClass). 
/// This is where we can add the properties that the class provides
/// </summary>
void MyPropertyFacet::makeMembers(
        AcRxMemberCollectionBuilder& collectionBuilder,
        void* customData)
{
	collectionBuilder.add((AcRxMember*)MyColorProperty::makeMyColorProperty());
}

// This implements MyPropertyFacet::desc() and MyPropertyFacet::isA()
ACRX_DEFINE_MEMBERS(MyPropertyFacet);

/// <summary>
/// This is called to register our class
/// </summary>
void MyPropertyFacet::rxInit() 
{ 
    MyPropertyFacet::gpDesc = newAcRxClass(
		ACRX_T("MyPropertyFacet"), 
		ACRX_T("MyPropertyFacetBase"), 
		AcDb::kDHL_MC0_0,
        AcDb::kMRelease0,
        0,
        NULL, 
        NULL,
        NULL,
        NULL,
		&MyPropertyFacet::makeMembers); 
}

// This will make sure that MyPropertyFacet::rxInit() is called 
// when this arx gets loaded into AutoCAD
ACDB_REGISTER_OBJECT_ENTRY_AUTO(MyPropertyFacet)

/////////////////////////////////////////////////////////////////////
// MyPorpertyFacetBase //////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

/// <summary>
/// This is called when the class descriptor of MyPropertyFacet is 
/// created (newAcRxClass). 
/// This is where we can add the properties that the class provides
/// </summary>
void MyPropertyFacetBase::makeMembers(
        AcRxMemberCollectionBuilder& collectionBuilder,
        void* customData)
{
	collectionBuilder.add((AcRxMember*)MyDoubleProperty::makeMyDoubleProperty());
}

// This implements MyPropertyFacet::desc() and MyPropertyFacet::isA()
ACRX_DEFINE_MEMBERS(MyPropertyFacetBase);

/// <summary>
/// This is called to register our class
/// </summary>
void MyPropertyFacetBase::rxInit() 
{ 
    MyPropertyFacetBase::gpDesc = newAcRxClass(
		ACRX_T("MyPropertyFacetBase"), 
		ACRX_T("AcRxObject"), 
		AcDb::kDHL_MC0_0,
        AcDb::kMRelease0,
        0,
        NULL, 
        NULL,
        NULL,
        NULL,
		&MyPropertyFacetBase::makeMembers); 
}

// This will make sure that MyPropertyFacet::rxInit() is called 
// when this arx gets loaded into AutoCAD
ACDB_REGISTER_OBJECT_ENTRY_AUTO(MyPropertyFacetBase)

/////////////////////////////////////////////////////////////////////
// MyDoubleProperty /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

const ACHAR * MyDoubleProperty::kMyAppName = _T("Aen1MyApp"); 
const ACHAR * MyDoubleProperty::kCategoryName = _T("My Category"); 

AcRxCategory * MyDoubleProperty::category = NULL;

MyDoubleProperty::MyDoubleProperty() : 
	AcRxProperty(_T("My Double Property"), 
	AcRxValueType::Desc<double>::value())
{
	if (category == NULL)
	{
		AcRxCategory * parent =  AcRxCategory::rootCategory();
		category = parent->findDescendant(kCategoryName); 
		if (category == NULL)
			category = new AcRxCategory(kCategoryName, parent); 
	}

	// OPM = Object Property Manager / Property Palette

	// Add the Placement attribute to set under which category in the OPM
	// the property will be shown 
	attributes().add(new AcRxUiPlacementAttribute(kCategoryName, 0));
	// Add this attribute so that AutoCAD will automatically create the COM
	// wrapper for this property, i.e. it will be visible in OPM
	attributes().add(new AcRxGenerateDynamicPropertiesAttribute());
}

/// <summary>
/// This is called by the system to get the property value for a specific object
/// </summary>
Acad::ErrorStatus MyDoubleProperty::subGetValue(const AcRxObject* pO, AcRxValue& value) const
{
	const ACHAR * name = pO->isA()->name(); 

	AcDbEntity * ent = AcDbEntity::cast(pO);
	if (ent == NULL)
		return Acad::eNotThatKindOfClass; // or eNotApplicable

	// If the value is not set then return an "unset" value, so
	// that it can be used for Quick Properties and can be used for Quick Selection
	double val = -1;

	// We store the property value in the XData of the given entity
	// so let's try to retrieve it form there
	resbuf * xdata = ent->xData(kMyAppName);
	if (xdata != NULL)
	{
		resbuf * item = xdata->rbnext;
		if (item->restype == AcDb::kDxfXdReal)
		{
			val = item->resval.rreal; 
		}

		acutRelRb(xdata);
	}

	// Set the value based on the double value we retrieved 
	value = AcRxValue(static_cast<double>(val));  

	return Acad::eOk; 
}

/// <summary>
/// This is called by the system to retrieve the property value for a specific object
/// </summary>
Acad::ErrorStatus MyDoubleProperty::subSetValue(AcRxObject* pO, const AcRxValue& value) const
{
	// In this sample we only want to provide the property for line entities
	AcDbEntity * ent = AcDbEntity::cast(pO);
	if (ent == NULL)
		return Acad::eNotThatKindOfClass;

	const double * val = rxvalue_cast<double>(&value);
	if (val == NULL)
		return Acad::eInvalidInput; 

	createRegApp(ent->database(), MyDoubleProperty::kMyAppName);

	// Store the property data in the XData of the given entity
	resbuf * xdata = acutBuildList(AcDb::kDxfRegAppName, kMyAppName, AcDb::kDxfXdReal, *val, RTNONE);  

	ent->setXData(xdata);

	acutRelRb(xdata);

	return Acad::eOk; 
}

/// <summary>
/// This is called to create an instance of our class
/// </summary>
AcRxObject * MyDoubleProperty::makeMyDoubleProperty() 
{ 
	return new MyDoubleProperty(); 
}

/////////////////////////////////////////////////////////////////////
// MyColorProperty //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

const ACHAR * MyColorProperty::kMyAppName = _T("Aen1MyColorApp"); 
const ACHAR * MyColorProperty::kCategoryName = _T("My Category"); 

AcRxCategory * MyColorProperty::category = NULL;

MyColorProperty::MyColorProperty() : 
	AcRxProperty(_T("My Color Property"), 
	AcRxValueType::Desc<AcCmColor>::value())
{
	if (category == NULL)
	{
		AcRxCategory * parent =  AcRxCategory::rootCategory();
		category = parent->findDescendant(kCategoryName); 
		if (category == NULL)
			category = new AcRxCategory(kCategoryName, parent); 
	}

	// OPM = Object Property Manager / Property Palette

	// Add the Placement attribute to set under which category in the OPM
	// the property will be shown 
	attributes().add(new AcRxUiPlacementAttribute(kCategoryName, 1));
	// Add this attribute so that AutoCAD will automatically create the COM
	// wrapper for this property, i.e. it will be visible in OPM
	attributes().add(new AcRxGenerateDynamicPropertiesAttribute());
}

/// <summary>
/// This is called by the system to get the property value for a specific object
/// </summary>
Acad::ErrorStatus MyColorProperty::subGetValue(const AcRxObject* pO, AcRxValue& value) const
{
	AcDbEntity * ent = AcDbEntity::cast(pO);
	if (ent == NULL)
		return Acad::eNotThatKindOfClass;

	// If the value is not set then return an "unset" value, so
	// that it can be used for Quick Properties and can be used for Quick Selection
	AcCmColor val;

	// We store the property value in the XData of the given entity
	// so let's try to retrieve it form there
	resbuf * xdata = ent->xData(kMyAppName);
	if (xdata != NULL)
	{
		resbuf * item = xdata->rbnext;
		if (item->restype == AcDb::kDxfXdInteger32)
		{
			val.setColor(item->resval.rlong);
		}

		acutRelRb(xdata);
	}

	// Set the value based on the double value we retrieved 
	value = AcRxValue(static_cast<AcCmColor>(val));  

	return Acad::eOk; 
}

/// <summary>
/// This is called by the system to retrieve the property value for a specific object
/// </summary>
Acad::ErrorStatus MyColorProperty::subSetValue(AcRxObject* pO, const AcRxValue& value) const
{
	// In this sample we only want to provide the property for line entities
	AcDbEntity * ent = AcDbEntity::cast(pO);
	if (ent == NULL)
		return Acad::eNotThatKindOfClass;

	const AcCmColor * val = rxvalue_cast<AcCmColor>(&value);
	if (val == NULL)
		return Acad::eInvalidInput; 

	createRegApp(ent->database(), MyColorProperty::kMyAppName);

	// Store the property data in the XData of the given entity
	resbuf * xdata = acutBuildList(AcDb::kDxfRegAppName, kMyAppName, AcDb::kDxfXdInteger32, val->color(), RTNONE);  

	ent->setXData(xdata);

	acutRelRb(xdata);

	return Acad::eOk; 
}

/// <summary>
/// This is called to create an instance of our class
/// </summary>
AcRxObject * MyColorProperty::makeMyColorProperty() 
{ 
	return new MyColorProperty(); 
}

/////////////////////////////////////////////////////////////////////
// MyPropertyFacetProvider //////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

MyPropertyFacetProvider MyPropertyFacetProvider::instance;

/// <summary>
/// We call this when the arx is loaded into AutoCAD, so that our facet 
/// provider will be registered
/// </summary>
void MyPropertyFacetProvider::addProvider()
{
	AcRxMemberQueryEngine::theEngine()->addFacetProvider(&instance);
}

/// <summary>
/// We call this when the arx gets unloaded from AutoCAD, so that our facet 
/// provider will be unregistered
/// </summary>
void MyPropertyFacetProvider::removeProvider()
{
	AcRxMemberQueryEngine::theEngine()->removeFacetProvider(&instance); 
}

/// <summary>
/// This function will return our facet class descriptor
/// Facet Class - any c1lass that provides properties 
/// </summary>
void MyPropertyFacetProvider::getFacets(
	const AcRxObject* pO, 
	const AcRxMemberQueryContext* pContext, AcArray<const AcRxClass*>& facets)
{
	AcDbLine * line = AcDbLine::cast(pO);
	if (line != NULL)
		facets.append(MyPropertyFacet::desc());    
}


