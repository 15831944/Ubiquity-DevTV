#pragma once

#include "rxmember.h"
#include "rxvaluetype.h"
#include "rxattrib.h"
#include "rxprop.h"
#include "rxcategory.h"

/////////////////////////////////////////////////////////////////////
// MyPorpertyFacet //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

class MyPropertyFacetBase : public AcRxObject 
{
public:
	// This declares desc(), isA(), rxInit()
	ACRX_DECLARE_MEMBERS(MyPropertyFacetBase);

    static void makeMembers(
            AcRxMemberCollectionBuilder& collectionBuilder,
            void* customData);

    MyPropertyFacetBase()
	{
	}

    virtual ~MyPropertyFacetBase()
	{
	}
};

/////////////////////////////////////////////////////////////////////
// MyPorpertyFacet //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

class MyPropertyFacet : public MyPropertyFacetBase 
{
public:
	// This declares desc(), isA(), rxInit()
	ACRX_DECLARE_MEMBERS(MyPropertyFacet);

    static void makeMembers(
            AcRxMemberCollectionBuilder& collectionBuilder,
            void* customData);

    MyPropertyFacet()
	{
	}

    virtual ~MyPropertyFacet()
	{
	}
};

/////////////////////////////////////////////////////////////////////
// MyDoubleProperty /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

class MyDoubleProperty : public AcRxProperty 
{
public:
	static AcRxObject * makeMyDoubleProperty();

	static const ACHAR * kMyAppName; 
	static const ACHAR * kCategoryName;
	static AcRxCategory * category;

	MyDoubleProperty();
	~MyDoubleProperty()
	{
	}

    virtual Acad::ErrorStatus subGetValue(const AcRxObject* pO, AcRxValue& value) const;

	virtual Acad::ErrorStatus subSetValue(AcRxObject* pO, const AcRxValue& value) const;
};

/////////////////////////////////////////////////////////////////////
// MyColorProperty //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

class MyColorProperty : public AcRxProperty 
{
public:
	static AcRxObject * makeMyColorProperty();

	static const ACHAR * kMyAppName; 
	static const ACHAR * kCategoryName;
	static AcRxCategory * category;

	MyColorProperty();

	~MyColorProperty()
	{
	}

    virtual Acad::ErrorStatus subGetValue(const AcRxObject* pO, AcRxValue& value) const;

	virtual Acad::ErrorStatus subSetValue(AcRxObject* pO, const AcRxValue& value) const;
};

/////////////////////////////////////////////////////////////////////
// MyPropertyFacetProvider //////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

class MyPropertyFacetProvider : public AcRxFacetProvider
{
	static MyPropertyFacetProvider instance;

public:
	static void addProvider();

	static void removeProvider();

	virtual void getFacets(const AcRxObject* pO, const AcRxMemberQueryContext* pContext, AcArray<const AcRxClass*>& facets);
};

