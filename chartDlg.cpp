/**
  *Author�������
  *Date:2015-06-23
  *Description������MFC�ļ�ʱ���������ʵ��
  *Version��1.0
*/

// chartDlg.cpp : implementation file

#include "stdafx.h"
#include "chart.h"
#include "chartDlg.h"
#include "afx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
FriendList *list[20]={0};
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChartDlg dialog

CChartDlg::CChartDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChartDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChartDlg)
	m_editMessage = _T("");
	m_ipAddress = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_listensock=INVALID_SOCKET;//��ʼ��Ϊ-1
    m_connectsock=INVALID_SOCKET;
	m_listentread=NULL;
	m_connecttread=NULL;
	is_sever=-1;
	shutdown=false;
}


void CChartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChartDlg)
	DDX_Control(pDX, IDC_BUTTON5, m_connect);
	DDX_Control(pDX, IDC_BUTTON8, m_stopClient);
	DDX_Control(pDX, IDC_BUTTON6, m_stopServer);
	DDX_Control(pDX, IDC_BUTTON7, m_startServer);
	DDX_Control(pDX, IDC_EDIT5, m_serverPort);
	DDX_Control(pDX, IDC_SHOWINFO, m_showmsg);
	DDX_Control(pDX, IDC_EDIT1, m_username);
	DDX_Control(pDX, IDC_LIST1, m_friendList);
	DDX_Control(pDX, IDC_IPADDRESS1, m_clientIP);
	DDX_Control(pDX, IDC_IPADDRESS2, m_serverIP);
	DDX_Control(pDX, IDC_BUTTON1, m_sendMessage);
	DDX_Control(pDX, IDC_BUTTON2, m_cancelSending);
	DDX_Control(pDX, IDC_BUTTON4, m_exit);
	DDX_Control(pDX, IDC_BUTTON3, m_addFriend);
	DDX_Text(pDX, IDC_INPUTMSG, m_editMessage);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CChartDlg, CDialog)
	//{{AFX_MSG_MAP(CChartDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON4, OnExit)
	ON_EN_CHANGE(IDC_INPUTMSG, OnEditMessage)
	ON_BN_CLICKED(IDC_BUTTON2, OnCancelSending)
	ON_BN_CLICKED(IDC_BUTTON3, OnAddFriend)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON5, OnConnect)
	ON_BN_CLICKED(IDC_BUTTON1, OnSendMSG)
	ON_BN_CLICKED(IDC_BUTTON7, OnStartserver)
	ON_BN_CLICKED(IDC_BUTTON6, OnStopserver)
	ON_BN_CLICKED(IDC_BUTTON8, OnStopClient)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChartDlg message handlers

BOOL CChartDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}


	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CChartDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CChartDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CChartDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CChartDlg::OnExit() 
{
	// TODO: Add your control notification handler code here
	if( MessageBox( "�Ƿ�ȷ���˳���", "�����ʾ", MB_YESNO | MB_ICONQUESTION ) == IDYES  )
	{
      this->PostMessage(WM_QUIT);   //��������
	} 
	
	
}



void CChartDlg::OnEditMessage() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	
}

void CChartDlg::OnCancelSending() 
{
	// TODO: Add your control notification handler code here
	SetDlgItemText(IDC_INPUTMSG,""); 
	
}

//��Ӧ����Ӻ��ѡ���ť�����ṹ��ָ������ӳ�Ա
void CChartDlg::OnAddFriend() 
{
	// TODO: Add your control notification handler code here
	CString fname,fip;
	GetDlgItemText(IDC_EDIT1,fname);
	GetDlgItemText(IDC_IPADDRESS1,fip);
	
	for(int i=0; i<20; i++)
	{
		if(!list[i])
		{
			list[i]= new FriendList();
			list[i]->name=fname;
			list[i]->ip=fip;
			break;
		}
	}
	m_friendList.AddString(fname);    //���б������ʾ����ӵĺ���
   
}

//������Ӧ�б��˫���ĺ���
void CChartDlg::OnDblclkList1() 
{
	// TODO: Add your control notification handler code here
		int index=m_friendList.GetCurSel();
		CString lname;
		CString lip;
	    m_friendList.GetText(index,lname);

		//�ڽṹ��ָ���в��Һ���ip
		for(int i=0; i<20; i++)
		{
			if(strcmp(list[i]->name,lname)==0){
				lip=list[i]->ip;
				break;
			}
		}
		SetDlgItemText(IDC_IPADDRESS2,lip); //�����ѵ�ip��ʾ�ں���ip���Է��㷢��Ự

}


//��Ӧ����ʼ����ť����¼���ʵ�����ӵ�������
void CChartDlg::OnConnect() 
{
	// TODO: Add your control notification handler code here
	m_connecttread=CreateThread(NULL,0,clientthreadfunc,this,0,NULL);
	CWnd *pWndstart = GetDlgItem(IDC_BUTTON7);
	CWnd *pWndstop = GetDlgItem(IDC_BUTTON6);
	pWndstop->EnableWindow(FALSE);
	pWndstart->EnableWindow(FALSE);
	
}

//������ʾ��Ϣ��¼�ĺ���
void CChartDlg::showmsg(CString msg)
{
	CString currTime; //��ȡϵͳʱ�� ���� ����
	currTime=CTime::GetCurrentTime().Format("%X");

	m_showmsg.SetSel(-1,-1);
	m_showmsg.ReplaceSel(currTime+_T("\r\n")+msg+_T("\r\n")+_T("\r\n"));
}

//��Ӧ������Ͱ�ť�¼�
void CChartDlg::OnSendMSG() 
{
	// TODO: Add your control notification handler code here
	if(is_sever==-1)
		AfxMessageBox(_T("����δ����Ự�����ȷ���Ự"));
	else
	{
	CString msg;
	GetDlgItemText(IDC_INPUTMSG,msg);
	
	if(is_sever==1)
	{
		//msg=_T("��>")+msg;
		if(msg.IsEmpty())
		{
			MessageBox( "���ܷ��Ϳ���Ϣ��", "�����ʾ");
		    //AfxMessageBox(_T("���ܷ��Ϳ���Ϣ��"));
		}else{
			showmsg(_T("��>")+msg);
			sendclientmsg(msg,NULL);
		}
		
	}
	else  if(is_sever==0)
	{
		char sbuf[1024]={0};
		if(msg.IsEmpty())
		{
			MessageBox( "���ܷ��Ϳ���Ϣ��", "�����ʾ");//�������Ϳ���Ϣ
		}else{
			strcpy(sbuf,msg);
			int isend=send(m_connectsock,sbuf,_tcslen(sbuf)*sizeof(char),0);
			msg=msg;
			showmsg(_T("��>")+msg);
		}

	}
	SetDlgItemText(IDC_INPUTMSG,_T(""));
	}
}

//�ӿͻ��������Ƴ����߿ͻ�
void CChartDlg::removeclient(clientitem c_item)
{
	for(int i=0;i<m_clientarray.GetSize();i++)
	{
		clientitem titem=m_clientarray.GetAt(i);
		if(titem.hThread==c_item.hThread&&
		   titem.m_Socket==c_item.m_Socket&&
		   titem.m_strIp==c_item.m_strIp)
		   m_clientarray.ElementAt(i);

	}
}

//��Ӧ�����������ť�¼�
void CChartDlg::OnStartserver() 
{
	// TODO: Add your control notification handler code here
	m_listentread=CreateThread(NULL,0,listenthreadfunc,this,0,NULL);

	//����������ʱ�����á���ʼ��������������ť
	CWnd *pWndstart = GetDlgItem(IDC_BUTTON5);
	CWnd *pWndstop = GetDlgItem(IDC_BUTTON8);
	pWndstop->EnableWindow(FALSE);
	pWndstart->EnableWindow(FALSE);
}

void CChartDlg::OnStopserver() 
{
	// TODO: Add your control notification handler code here

	int ok=MessageBox(_T("������Ϣ�����ߣ�������˳����к��Ѷ������ߣ�ȷ���˳���"),0,MB_OKCANCEL);
	if(ok==IDOK)
	{
		stopsever(); //���ùرշ������ĺ���
		showmsg(_T("ϵͳ��Ϣ�����߳ɹ�"));
	}

	//����ֹ����ʱ�����á���ʼ��������������ť
    CWnd *pWndstart = GetDlgItem(IDC_BUTTON5);
	CWnd *pWndstop = GetDlgItem(IDC_BUTTON8);
	pWndstop->EnableWindow(TRUE);
	pWndstart->EnableWindow(TRUE);
}

void CChartDlg::OnStopClient() 
{
	// TODO: Add your control notification handler code here
	int ok=MessageBox(_T("�������ֹͣ��"),0,MB_OKCANCEL);
	if(ok==IDOK)
	{
	stopclient();
	showmsg(_T("ϵͳ��Ϣ�����߳ɹ�"));
	}
	CWnd *pWndstart = GetDlgItem(IDC_BUTTON7);
	CWnd *pWndstop = GetDlgItem(IDC_BUTTON6);
	pWndstop->EnableWindow(true);
	pWndstart->EnableWindow(true);
	
}

void CChartDlg::stopsever()
{
	int count=m_clientarray.GetSize();
	HANDLE *phandles=new HANDLE[count+1];
	phandles[0]=m_listentread;
	for(int i=0;i<count;i++)
	{
		phandles[i+1]=m_clientarray.GetAt(i).hThread;
	}
	shutdown=true;
	DWORD dw=WaitForMultipleObjects(count+1,phandles,true,1000);
	if(dw!=WAIT_OBJECT_0)
	{
		for(int i=0;i<m_clientarray.GetSize();i++)
		{
		TerminateThread(m_clientarray.GetAt(i).hThread,-1);
		closesocket(m_clientarray.GetAt(i).m_Socket);
		}
		TerminateThread(m_listentread,-1);
		closesocket(m_listensock);

	}
	delete [] phandles;
	m_listentread=NULL;
	m_listensock=INVALID_SOCKET;
	is_sever=-1;
	shutdown=false;
}

void CChartDlg::stopclient()//������Դ����
{
	shutdown=true;
	DWORD dw=WaitForSingleObject(m_connecttread,1000);
	if(dw!=WAIT_OBJECT_0)
	{
		closesocket(m_connectsock);
		TerminateThread(m_connecttread,-1);
		
	}
	m_connecttread=NULL;
	m_connectsock=INVALID_SOCKET;
	is_sever=-1;
	shutdown=false;

}



BOOL CChartDlg::PreTranslateMessage(MSG* pMsg) 
{ 
        //   �޸Ļس����Ĳ�����Ӧ 
        if(pMsg-> message==WM_KEYDOWN && pMsg-> wParam==VK_RETURN) 
        { 
                if(GetDlgItem(IDC_INPUTMSG)==GetFocus()) 
                { 
                     CChartDlg::OnSendMSG();
					 return true; 
                } else{
					return false;
				}
        } 
        return   CDialog::PreTranslateMessage(pMsg); 
} 
