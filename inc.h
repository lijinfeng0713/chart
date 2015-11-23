#pragma once

DWORD WINAPI listenthreadfunc(LPVOID pParam);
DWORD WINAPI clientthreadfunc(LPVOID pParam);
BOOL SOCKET_Select(SOCKET hSocket, int nTimeOut, BOOL bRead);


class CChatRoomDlg;

class clientitem
{
public:
	CString m_strIp;
	SOCKET m_Socket;
	HANDLE hThread;

	clientitem()
	{
	
		m_Socket = INVALID_SOCKET;
		hThread = NULL;
	}
};

void sendclientmsg(CString msg,clientitem *pnotsend);