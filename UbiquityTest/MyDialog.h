#pragma once

// MyDialog dialog
#include "resource.h"
#include "PropertyTree.h"

#include "rxmember.h"
#include "rxvaluetype.h"
#include "rxattrib.h"
#include "rxprop.h"

class MyDialog : public CDialog
{
	DECLARE_DYNAMIC(MyDialog)

public:
	MyDialog(AcDbObjectId id, CWnd* pParent = NULL);   // standard constructor
	virtual ~MyDialog();

// Dialog Data
	enum { IDD = IDD_MYDIALOG };
	PropertyTree * m_propertyTree;
	AcDbObjectId m_id;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void showProperties(void);
	void printValues(AcRxObject * entity, HTREEITEM hParent, const AcRxMember * member);
	void valueToString(AcRxValue & value, AcString & strValue);
};
