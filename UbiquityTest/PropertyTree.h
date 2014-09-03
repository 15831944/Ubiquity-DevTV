#pragma once


// PropertyTree view

class PropertyTree : public CTreeView
{
	DECLARE_DYNCREATE(PropertyTree)

protected:
	PropertyTree();           // protected constructor used by dynamic creation
	virtual ~PropertyTree();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


