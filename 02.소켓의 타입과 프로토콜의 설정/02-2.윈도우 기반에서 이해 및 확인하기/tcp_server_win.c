/* Windows */
//#pragma comment(lib, "ws2_32")
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
void ErrorHandling(char* message);

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAddr, clntAddr;
	
	int szClntAddr;
	char message[] = "Hello World!";
	if(argc != 2)
	{
		printf("Usage : %s <port> \n", argv[0]);
		exit(1);
	}
	
	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) // ���� ���̺귯�� �ʱ�ȭ
	{
		ErrorHandling("WSAStartup() error!");
	}
	
	hServSock = socket(PF_INET, SOCK_STREAM, 0); // ������ ���� 
	if(hServSock == INVALID_SOCKET)
	{
		ErrorHandling("socket() error");
	}
	
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(argv[1]));
	
	if(bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) // ������ ���Ͽ� IP�ּҿ� PORT��ȣ�� �Ҵ� 
	{
		ErrorHandling("bind() error");
	}
	
	if(listen(hServSock, 5) == SOCKET_ERROR) // listen �Լ�ȣ���� ���� ������ ������ ���� �������� �ϼ���Ŵ
	{
		ErrorHandling("listen() error");
	}
	
	szClntAddr = sizeof(clntAddr);
	hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr); // Ŭ���̾�Ʈ�� �����û�� �����ϱ� ���� accept �Լ�ȣ��
	if(hClntSock == INVALID_SOCKET)
	{
		ErrorHandling("accept() error");
	}
	
	send(hClntSock, message, sizeof(message), 0); // send �Լ�ȣ���� ���� ����� Ŭ���̾�Ʈ�� �����͸� ����
	
	closesocket(hClntSock);
	closesocket(hServSock);
	WSACleanup(); // ���α׷��� �����ϱ� ���� �ʱ�ȭ�� ���� ���̺귯���� ���� 
	
	return 0;
}

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

