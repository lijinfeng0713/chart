// chartDlg.h : header file
//
#include "inc.h"
#include "Resource.h"
#include "afxtempl.h"

#if !defined(AFX_CHARTDLG_H__5E955406_E5DF_4047_A9F9_6AEA0DF97344__INCLUDED_)
#define AFX_CHARTDLG_H__5E955406_E5DF_4047_A9F9_6AEA0DF97344__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChartDlg dialog

struct FriendList{
	CString name;
	CString ip;
};

class CChartDlg : public CDialog
{
// Construction
public:
	

	CChartDlg(CWnd* pParent = NULL);	// standard constructor

	
// Dialog Data
	//{{AFX_DATA(CChartDlg)
	enum { IDD = IDD_CHART_DIALOG };
	CButton	m_connect;
	CButton	m_stopClient;
	CButton	m_stopServer;
	CButton	m_startServer;
	CEdit	m_serverPort;
	CEdit	m_showmsg;
	CEdit	m_username;
	CListBox	m_friendList;
	CIPAddressCtrl	m_clientIP;
	CIPAddressCtrl	m_serverIP;
	CButton	m_sendMessage;
	CButton	m_cancelSending;
	CButton	m_exit;
	CButton	m_addFriend;
	CString	m_editMessage;
	CString	m_ipAddress;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChartDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

public:
	SOCKET m_listensock;
	SOCKET m_connectsock;
	HANDLE m_listentread;
	HANDLE m_connecttread;
	CArray<clientitem,clientitem> m_clientarray;
	int is_sever;
	bool shutdown;
	void showmsg(CString msg);       //声明显示消息记录的函数
	void removeclient(clientitem c_item);  //声明从客户数组移除客户的函数
	void stopsever();                //声明停止服务器的函数
	void stopclient();               //声明停止客户端的函数


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CChartDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnExit();
	afx_msg void OnEditMessage();
	afx_msg void OnCancelSending();
	afx_msg void OnAddFriend();
	afx_msg void OnDblclkList1();    //声明响应列表框双击的函数
	afx_msg void OnConnect();
	afx_msg void OnSendMSG();
	afx_msg void OnStartserver();
	afx_msg void OnStopserver();
	afx_msg void OnStopClient();
	afx_msg BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTDLG_H__5E955406_E5DF_4047_A9F9_6AEA0DF97344__INCLUDED_)
