// MyDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MyDialog.h"
#include "afxdialogex.h"

#include "resource.h"

// MyDialog dialog

IMPLEMENT_DYNAMIC(MyDialog, CDialog)

MyDialog::MyDialog(AcDbObjectId id, CWnd* pParent /*=NULL*/)
	: CDialog(MyDialog::IDD, pParent)
{
	m_id = id;
	m_propertyTree = (PropertyTree*)PropertyTree::CreateObject();
}

MyDialog::~MyDialog()
{
}

void MyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MyDialog, CDialog)
END_MESSAGE_MAP()


// MyDialog message handlers

void MyDialog::valueToString(AcRxValue & value, AcString & strValue)
{
	if (value.type()  == AcRxValueType::Desc<double>::value())
	{
		strValue.format(_T("%f"), *rxvalue_cast<double>(&value));
	}
	else if (value.type() == AcRxValueType::Desc<double>::value())
	{
	}
}

void getAttInfo(const AcRxAttribute * att, const AcRxObject * member, AcString & attInfo)
{
	if (att->isA() == AcRxCOMAttribute::desc())
	{
		AcRxCOMAttribute * a = AcRxCOMAttribute::cast(att);
		attInfo.format(_T("%s - %s"), att->isA()->name(), a->name()); 
	}
	else if (att->isA() == AcRxUiPlacementAttribute::desc())
	{
		AcRxUiPlacementAttribute * a = AcRxUiPlacementAttribute::cast(att);
		attInfo.format(
			_T("%s - %s - %f"), 
			att->isA()->name(), 
			a->getCategory(member),
			a->getWeight(member)); 
	}
	else
	{
		attInfo.format(_T("%s"), att->isA()->name()); 
	}
}

void MyDialog::printValues(AcRxObject * entity, HTREEITEM hParent, const AcRxMember * member)
{
	Acad::ErrorStatus err = Acad::eOk;

	CTreeCtrl & ctrl = m_propertyTree->GetTreeCtrl();

	AcString strValue;
	AcRxProperty * prop = AcRxProperty::cast(member);
	if (prop != NULL)
	{
		AcRxValue value;

		if ((err = prop->getValue(entity, value)) == Acad::eOk) 
		{
			ACHAR * szValue = NULL;

			int buffSize = value.toString(NULL, 0);
			if (buffSize > 0)
			{
				buffSize++;
				szValue = new ACHAR[buffSize];
				value.toString(szValue, buffSize);
			}

			strValue.format(
				_T("%s = %s"), 
				value.type().name(), 
				(szValue == NULL) ? _T("none") : szValue);  

			if (szValue)
				delete szValue;
		}
		else
		{
			strValue.format(_T("Error Code = %d"), err);
		}
	}

	AcString str;
	str.format(_T("%s - %s [%s]"), member->isA()->name(), member->name(), strValue.kACharPtr());
	AfxOutputDebugString(str.kACharPtr());  
	HTREEITEM hItem = ctrl.InsertItem(str.kACharPtr(), hParent);  

	const AcRxAttributeCollection & atts = member->attributes();
		
	for (int i = 0; i < atts.count(); i++)
	{
		const AcRxAttribute * att = atts.getAt(i); 

		AcString attInfo;
		getAttInfo(att, member, attInfo);
		AfxOutputDebugString(str.kACharPtr());  
		ctrl.InsertItem(attInfo.kACharPtr(), hItem);
	}

	if (member->children() != NULL)
	{
		for (int i = 0; i < member->children()->length(); i++)
		{
			const AcRxMember * subMember = member->children()->at(i);
			printValues(entity, hItem, subMember);  
		}
	}

	ctrl.Expand(hItem, TVE_EXPAND);  
}

void MyDialog::showProperties(void)
{
	AcDbObjectPointer<AcDbEntity> entity(m_id, AcDb::kForRead);

	AcRxMemberIterator * iter =
		AcRxMemberQueryEngine::theEngine()->newMemberIterator(entity);   
	for (; !iter->done(); iter->next())
	{
		printValues(entity, TVI_ROOT, iter->current());
	}
}

BOOL MyDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_propertyTree->SubclassDlgItem(IDC_PROPERTYTREE, this); 

	showProperties();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
