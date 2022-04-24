/* Linux */
/*
@brief:
소켓의 생성에 사용되는 socket 함수
성공 시 파일디스크립터, 실패 시 -1 반환

#include <sys/socket.h>
socket(int domain, int type, int protocol);


@param:
int domain   : 소켓이 사용할 프로토콜 체계 (Protocol Family) 정보 전달.
                   : PF_INET   : IPv4 인터넷 프로토콜 체계
                   : PF_INET6  : IPv6 인터넷 프로토콜 체계
                   : PF_LOCAL  : 로컬 통신을 위한 UNIX 프로토콜 쳬계
                   : PF_PACKET : Low Level 소켓을 위한 프로토콜 체계
                   : PF_IPX    : IPX 노벨 프로토콜 체계

int type     : 소켓의 데이터 전송방식에 대한 정보 전달.
                   : SOCK_STREAM : 연결지향형 소켓 (신뢰성 있는 순차적인 바이트 기반의 연결지향 데이터 전송 방식의 1:1 소켓) *TCP
                   : SOCK_DGRAM  : 비연결지향형 소켓 (신뢰성과 순차적 데이터 전송을 보장하지 않는 고속의 데이터 전송을 목적으로 하는 소켓) *UDP

int protocol : 두 컴퓨터간 통신에 사용되는 프로토콜 정보 전달.
                   : 대부분의 경우 0
                   : 하나의 프로토콜 체계 안에 데이터의 전송방식이 동일한 프로토콜이 둘 이상 존재하는 경우에는 세번째 인자가 필요
                   
                   - IPv4 인터넷 프로토콜 체계에서 동작하는 연결지향형 데이터 전송 소켓 
                   - PF_INET와 SOCK_STREAM의 두 가지 조건을 만족시키는 프로토콜은 IPPROTO_TCP 
                   int tcp_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); *'TCP 소켓'이라 한다.
                   
                   - IPv4 인터넷 프로토콜 체계에서 동작하는 비 연결지향형 데이터 전송 소켓 
                   - PF_INET와 SOCK_DGRAM의 두 가지 조건을 만족시키는 프로토콜은 IPPROTO_UDP 
                   int udp_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP); * 'UDP 소켓'이라 한다.
 */                                     
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
void error_handling(char* message);

int main(int argc, char* argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int str_len = 0;
    int idx = 0, read_len = 0;
    
    if (argc != 3)
    {
        printf("Usage : %s <IP> <port> \n", argv[0]);
        exit(1);
    }
    
    sock = socket(PF_INET, SOCK_STREAM, 0); // TCP 소켓을 생성, PF_INET/SOCK_STREAM 가 전달되면 세 번째 인자인 IPPROTO_TCP는 생략 가능.
    if (sock == -1)
    {
        error_handling("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == 1)
    {
        error_handling("connect() error!");
    }

// while문 안에서 read 함수를 반복 호출, 이 함수가 호출될 때마다 1 byte 씩 데이터를 읽어 들임
// read 함수가 0을 반환하면 false이므로 while문을 빠져나감.
    while(read_len = read(sock, &message[idx++], 1)) 
    {
        if (read_len == -1)
        {
            error_handling("read() error!");
        }

        str_len += read_len;
    }

    printf("Message from server : %s \n", message);
    printf("Function read all count : %d \n", str_len);
    close(sock);

    return 0;
}
 
void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);

    exit(1);
}