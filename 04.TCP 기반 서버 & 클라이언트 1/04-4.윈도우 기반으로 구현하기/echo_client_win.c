/* Windows */
/*
 * 리눅스 기반 예제를 윈도우 기반으로 변경하기 위해서는 일단 다음 네 가지만 기억하면 됨.
 *
 * # WSAStartup, WSACleanup 함수호출을 통한 소켓 라이브러리 초기화와 해제
 * # 자료형과 변수의 이름을 윈도우 스타일로 변경하기
 * # 데이터 송수신을 위해서 read, write 함수 대신 recv, send 함수 호출하기
 * # 소켓의 종료를 위해서 close 대신 closesocket 함수 호출하기
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define BUF_SIZE    1024
void ErrorHandling(char *message);

int main(int argc, char *argv[])
{
   WSADATA wsaData;
   SOCKET hSocket;
   char message[BUF_SIZE];
   int strLen;
   SOCKADDR_IN servAdr;

   if (argc != 3)
   {
       printf("Usage : %s <IP> <port>\n", argv[0]);
       exit(1);
   }

   if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
   {
       ErrorHandling("WSAStartup() error!");
   }

   hSocket = socket(PF_INET, SOCK_STREAM, 0);
   if (hSocket == INVALID_SOCKET)
   {
       ErrorHandling("socket() error");
   }

   memset(&servAdr, 0, sizeof(servAdr));
   servAdr.sin_family = AF_INET;
   servAdr.sin_addr.s_addr = inet_addr(argv[1]);
   servAdr.sin_port = htons(atoi(argv[2]));

   if (connect(hSocket, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
   {
       ErrorHandling("connect() error!");
   }

   else
   {
       printf("Connected...........");
   }

   while (1)
   {
       fputs("Input message(Q to quit): ", stdout);
       fgets(message, BUF_SIZE, stdin);

       if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
       {
           break;
       }

       send(hSocket, message, strlen(message), 0);
       strLen = recv(hSocket, message, BUF_SIZE-1, 0);
       message[strLen] = 0;
       printf("Message frome server : %s", message);
   }

   closesocket(hSocket);
   WSACleanup();

   return 0;
}

void ErrorHandling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
