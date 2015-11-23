/**
  *Author：李进锋
  *Date:2015-06-23
  *Description：基于MFC的即时聊天软件的实现
  *Version：1.0
*/

#include "stdafx.h"
#include "chartDlg.h"
#include "inc.h"
#define max_size  1024


DWORD WINAPI testfunc(LPVOID lpParam);
CChartDlg *pChatRoom;

BOOL SOCKET_Select(SOCKET hSocket, int nTimeOut, BOOL bRead)
{
	fd_set fdset;
	timeval tv;
	FD_ZERO(&fdset);
	FD_SET(hSocket, &fdset);
	nTimeOut = nTimeOut > 1000 ? 1000 : nTimeOut;
	tv.tv_sec  = 0;
	tv.tv_usec = nTimeOut;

	int iRet = 0;
	if ( bRead )
	{
		iRet = select(0, &fdset, NULL , NULL, &tv);
	}
	else
	{
		iRet = select(0, NULL , &fdset, NULL, &tv);
	}

	if(iRet <= 0) 
	{
		return FALSE;
	} 
	else if (FD_ISSET(hSocket, &fdset))
	{
		return TRUE;
	}
	return FALSE;
}





DWORD WINAPI listenthreadfunc(LPVOID pParam)
{
	pChatRoom= (CChartDlg *)pParam;
	ASSERT(pChatRoom!=NULL);
	pChatRoom->m_listensock = socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
	if ( pChatRoom->m_listensock == INVALID_SOCKET )
	{
		AfxMessageBox(_T("新建Socket失败！"));
		return FALSE;
	}

	int iPort = 6666;
	/**
	if ( iPort <= 0 || iPort > 65535 )
	{
		AfxMessageBox(_T("请输入合适的端口：1 - 65535"));
		goto __Error_End;
	}**/

	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = INADDR_ANY;
	service.sin_port = htons(iPort);

	if ( bind(pChatRoom->m_listensock, (sockaddr*)&service, sizeof(sockaddr_in)) == SOCKET_ERROR ) 
	{
		AfxMessageBox(_T("绑定端口失败！"));
		goto __Error_End;
	}else{
		pChatRoom->showmsg(_T("系统消息：服务已启动，开始发起会话！"));
	
	}

	if( listen(pChatRoom->m_listensock, 5) == SOCKET_ERROR )
	{
		AfxMessageBox(_T("监听失败！"));
		goto __Error_End;
	}
	pChatRoom->is_sever=1;

	while(!(pChatRoom->shutdown))
	{
		if ( SOCKET_Select(pChatRoom->m_listensock, 100, TRUE) ) 
		{
			sockaddr_in clientAddr;
			int iLen = sizeof(sockaddr_in);
			SOCKET accSock = accept(pChatRoom->m_listensock, (struct sockaddr *)&clientAddr , &iLen);
			if (accSock == INVALID_SOCKET)
			{
				continue;
			}
			clientitem item;
			item.m_Socket=accSock;
			item.m_strIp=inet_ntoa(clientAddr.sin_addr);
			
			int idx=pChatRoom->m_clientarray.Add(item);
			item.hThread=CreateThread(NULL,0,testfunc,&(pChatRoom->m_clientarray.GetAt(idx)),CREATE_SUSPENDED,NULL);
			(&(pChatRoom->m_clientarray.GetAt(idx)))->hThread=item.hThread;
			pChatRoom->showmsg(_T("系统消息：好友"+item.m_strIp+"已上线，开始发起聊天"));
			ResumeThread(item.hThread);
		
			Sleep(100);
		}
	}

__Error_End:
	closesocket(pChatRoom->m_listensock);
	return true;
}


DWORD WINAPI testfunc(LPVOID lpParam)
{
	CString msg;
	clientitem m_client=*(clientitem*)lpParam;
	
	  while(!(pChatRoom->shutdown))
	{
		if(SOCKET_Select(m_client.m_Socket, 100, TRUE))
		{
			char buf[max_size]={0};
			int irec=recv(m_client.m_Socket,(char*)buf,max_size,0);
			if(irec>0)
			{
				msg=buf;
				msg=_T("好友")+m_client.m_strIp+_T(">")+msg;
				pChatRoom->showmsg(msg+_T("\r\n"));
			    sendclientmsg(msg,&m_client);
			}
			else
			{
				msg=_T("好友")+m_client.m_strIp+_T("已离线");
				pChatRoom->showmsg(msg+_T("\r\n"));
				pChatRoom->removeclient(m_client);
				break;
			}
		}
		Sleep(500);
	}

	return true;
}

void sendclientmsg(CString msg,clientitem *pnotsend)
{
	char sbuf[max_size]={0};
	strcpy(sbuf,msg);
	
	for(int i=0;i<pChatRoom->m_clientarray.GetSize();i++)
	{
		if(!pnotsend||pnotsend->m_Socket!=pChatRoom->m_clientarray.GetAt(i).m_Socket||
			pChatRoom->m_clientarray.GetAt(i).hThread!=pnotsend->hThread||
			pChatRoom->m_clientarray.GetAt(i).m_strIp!=pnotsend->m_strIp)
			int isend=send(pChatRoom->m_clientarray.GetAt(i).m_Socket,sbuf,_tcslen(sbuf)*sizeof(char),0);
	}
	
}
