/**
  *Author�������
  *Date:2015-06-23
  *Description������MFC�ļ�ʱ���������ʵ��
  *Version��1.0
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
                MessageBox("��ϲ�㣬ע��ɹ���","�����ʾ");	
			}else{
				MessageBox("�û��������벻��Ϊ�գ�","�����ʾ");
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
	//ȡ��IDC_EDIT1��ֵ���ŵ�username�ַ����У��ҽ���ȡǰ20���ַ�
	GetDlgItemText(IDC_EDIT1,username);
	//ȡ��IDC_EDIT2��ֵ���ŵ�pwd�ַ����У��ҽ���ȡǰ20���ַ�
	GetDlgItemText(IDC_EDIT2,pwd);
	//�Ա��ַ�������strcmp(a,b)�Ƿ����0�ĺ�����ֱ��==�ǲ��еģ���Ҫ��C�����г����Ĵ���
	for(int i=0; i<20; i++)
	{
		if( strcmp(user[i]->username,username)==0 && strcmp(user[i]->password,pwd)==0 )
		{
			//���������û���������ͬʱ����admin��123456����ô�ر�����Ի��򣬲�����һ��IDOKֵ��Ҳ����1
			OnOK();
			break;
		}else{
			//��������û��������벻��������ֵ����ô��MB_OK���͵Ĵ������ﲻ�ر�������ڡ�
			MessageBox("�û��������������","�����ʾ",MB_OK);
			break;
		}
	}

	
}

// ���λس����� 
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
