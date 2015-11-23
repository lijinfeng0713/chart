// chart.h : main header file for the CHART application
//

#if !defined(AFX_CHART_H__0B1DB9AE_1925_45DA_BA4E_190B5750461F__INCLUDED_)
#define AFX_CHART_H__0B1DB9AE_1925_45DA_BA4E_190B5750461F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CChartApp:
// See chart.cpp for the implementation of this class
//

class CChartApp : public CWinApp
{
public:
	CChartApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChartApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CChartApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHART_H__0B1DB9AE_1925_45DA_BA4E_190B5750461F__INCLUDED_)
