/**
  *Author：李进锋
  *Date:2015-06-23
  *Description：基于MFC的即时聊天软件的实现
  *Version：1.0
*/

// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "chart.h"
#include "LoginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog
User *user[20];

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginDlg)
	//}}AFX_DATA_INIT
}

BOOL CLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	return true;

}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDlg)
	DDX_Control(pDX, IDC_BUTTON2, m_login);
	DDX_Control(pDX, IDC_BUTTON1, m_register);
	DDX_Control(pDX, IDC_EDIT1, m_username1);
	DDX_Control(pDX, IDC_EDIT2, m_password);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CLoginDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnRegister)
	ON_BN_CLICKED(IDC_BUTTON2, OnLogin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg message handlers

void CLoginDlg::OnRegister() 
{
	// TODO: Add your control notification handler code here
	CString username,password;
	GetDlgItemText(IDC_EDIT1,username);
	GetDlgItemText(IDC_EDIT2,password);
	
	for(int i=0; i<20; i++)
	{
		if(!user[i])
		{
			if(!username.IsEmpty()&&!password.IsEmpty())
			{
				user[i]= new User();
			    user[i]->username=username;
			    user[i]->password=password;
                MessageBox("恭喜你，注册成功！","锋哥提示");	
			}else{
				MessageBox("用户名和密码不能为空！","锋哥提示");
			}
			
			break;
		}
	}
	
}

void CLoginDlg::OnLogin() 
{
	// TODO: Add your control notification handler code here
	CString username;
	CString pwd;
	//取出IDC_EDIT1的值，放到username字符串中，且仅截取前20个字符
	GetDlgItemText(IDC_EDIT1,username);
	//取出IDC_EDIT2的值，放到pwd字符串中，且仅截取前20个字符
	GetDlgItemText(IDC_EDIT2,pwd);
	//对比字符串请用strcmp(a,b)是否等于0的函数，直接==是不行的，不要犯C语言中常犯的错误
	for(int i=0; i<20; i++)
	{
		if( strcmp(user[i]->username,username)==0 && strcmp(user[i]->password,pwd)==0 )
		{
			//如果输入的用户名与密码同时等于admin与123456，那么关闭这个对话框，并返回一个IDOK值，也就是1
			OnOK();
			break;
		}else{
			//如果输入用户名与密码不是这两个值，那么则弹MB_OK类型的窗。这里不关闭这个窗口。
			MessageBox("用户名或者密码错误！","锋哥提示",MB_OK);
			break;
		}
	}

	
}

// 屏蔽回车操作 
BOOL CLoginDlg::PreTranslateMessage(MSG* pMsg) 
{ 
        
        if(pMsg-> message==WM_KEYDOWN && pMsg-> wParam==VK_RETURN) 
        { 
                if(GetDlgItem(IDC_BUTTON1)==GetFocus()||GetDlgItem(IDC_BUTTON2)==GetFocus()) 
                { 
                     return CDialog::PreTranslateMessage(pMsg);
					 return true; 
                } else{
					return false;
				}
        } 
        return   CDialog::PreTranslateMessage(pMsg); 
} 
