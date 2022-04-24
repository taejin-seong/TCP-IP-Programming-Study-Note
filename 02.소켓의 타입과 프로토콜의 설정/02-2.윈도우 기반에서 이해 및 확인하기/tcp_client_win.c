/* Windows */
/*
@brief:
소켓의 생성에 사용되는 socket함수
성공 시 소켓 핸들, 실패 시 INVALID_SOCKET 반환

SOCKET         : 정수로 표현되는 소켓의 핸들 값을 저장하기 위해 정의된 자료형의 이름
               : 즉, 함수가 반환하는 값은 SOCKET형 변수를 하나 선언해서 저장해야 한다.
INVALID_SOCKET : 오류발생을 알리는 하나의 상수 (-1)

#include <winscok2.h>
SOCKET socket(int af, int type, int protocol);


@param:
int af / int type / int protocol : 함수의 이름과 전달되는 상수의 이름까지 리눅스와 동일함.
*/

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
//#include <WinSock2.h>
void ErrorHandling(char* message);

int main(int argc, char* argv[])
{
    WSADATA wsaData;
    SOCKET hSocket; // socket 함수의 반환 값 저장을 위해서 SOCKET형 변수 하나를 선언
    SOCKADDR_IN servAddr;

    char message[30];
    int strLen = 0;
    int idx = 0, readLen = 0;

    if (argc != 3)
    {
        printf("Usage : %s <IP> <port> \n", argv[0]);
        exit(1);
    }

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        ErrorHandling("WSAStartup() error!");
    }

    hSocket = socket(PF_INET, SOCK_STREAM, 0); // socket 함수호출을 통해 TCP 소켓을 생성
    if (hSocket == INVALID_SOCKET)
    {
        ErrorHandling("hSocket() error");
    }

    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(argv[1]);
    servAddr.sin_port = htons(atoi(argv[2]));

    if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
    {
        ErrorHandling("connect() error!");
    }
    
    while(readLen = recv(hSocket, &message[idx++], 1, 0)) //while 문 안에 recv 함수호출을 통해 수신된 데이터를 1byte 씩 읽음
    {
        if (readLen == -1)
        {
            ErrorHandling("read() error!");
        }

        strLen += readLen; // 1byte 씩 데이터를 읽고 있기 대문에 변수 strLen에 실제로 더해지는 값은 1이며, 이는 recv 함수의 호출횟수와 같음
    }

    printf("Message from server : %s \n", message);
    printf("Function read call : %d \n", strLen);

    closesocket(hSocket);
    WSACleanup();

    return 0;
}

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
