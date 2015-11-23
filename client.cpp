/**
  *Author：李进锋
  *Date:2015-06-23
  *Description：基于MFC的即时聊天软件的实现
  *Version：1.0
*/

#include "stdafx.h"
#include "chart.h"
#include "chartDlg.h"
#include "inc.h"
#define max_size  1024


DWORD WINAPI clientthreadfunc(LPVOID pParam)
{
	CString msg;
    CChartDlg *	pChatRoom= (CChartDlg *)pParam;
	ASSERT(pChatRoom!=NULL);
	pChatRoom->m_connectsock = socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
	if ( pChatRoom->m_connectsock == INVALID_SOCKET )
	{
		AfxMessageBox(_T("新建Socket失败！"));
		return FALSE;
	}
	
	CString ip;
	pChatRoom->GetDlgItemText(IDC_IPADDRESS2,ip);
	int iPort = pChatRoom->GetDlgItemInt(IDC_EDIT5);
	if ( iPort <= 0 || iPort > 65535 )
	{
		AfxMessageBox(_T("请输入合适的端口：1 - 65535"));
		goto __Error_End;
	}



	sockaddr_in sever;
	sever.sin_family = AF_INET;
	sever.sin_addr.s_addr =inet_addr(ip);
	sever.sin_port = htons(iPort);

	if ( connect(pChatRoom->m_connectsock, (sockaddr*)&sever, sizeof(sockaddr_in)) == SOCKET_ERROR ) 
	{
		AfxMessageBox(_T("连接失败！"));
		goto __Error_End;
	}
	else{  
		pChatRoom->showmsg(_T("系统消息：好友连接成功，开始发起会话")); 
    }  

		
	    

	pChatRoom->is_sever=0;

	//接收服务器发送过来的消息
	while(!(pChatRoom->shutdown))
	{
		if ( SOCKET_Select(pChatRoom->m_connectsock, 100, TRUE) ) 
		{
		    char buf[max_size]={0};
			int irec=recv(pChatRoom->m_connectsock,(char*)buf,max_size,0);
			if(irec>0)
			{
				msg=buf;
				pChatRoom->showmsg(msg);
			}
			else
			{
				pChatRoom->showmsg(_T("好友已下线，请重新连接"));
				break;
			}
		
			Sleep(500);
		}
	}

	
	
__Error_End:
	closesocket(pChatRoom->m_connectsock);
   return true;
}


