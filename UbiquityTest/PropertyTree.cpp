// PropertyTree.cpp : implementation file
//

#include "stdafx.h"
#include "PropertyTree.h"


// PropertyTree

IMPLEMENT_DYNCREATE(PropertyTree, CTreeView)

PropertyTree::PropertyTree()
{
}

PropertyTree::~PropertyTree()
{
}

BEGIN_MESSAGE_MAP(PropertyTree, CTreeView)
END_MESSAGE_MAP()


// PropertyTree diagnostics

#ifdef _DEBUG
void PropertyTree::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void PropertyTree::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// PropertyTree message handlers
