/* Linux */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE    30
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int sock;
    char message[BUF_SIZE];
    struct sockaddr_in my_adr, your_adr;
    socklen_t adr_sz;
    int str_len, i;

    if (argc != 2)
    {
        printf("Usage : %s <port> \n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock == -1)
    {
        error_handling("socket() error");
    }

    memset(&my_adr, 0, sizeof(my_adr));
    my_adr.sin_family = AF_INET;
    my_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    my_adr.sin_port = htons(atoi(argv[1]));

    if (bind(sock, (struct sockaddr*)&my_adr, sizeof(my_adr)) == -1)
    {
        error_handling("bind() error");
    }

    for (i = 0; i < 3; i++) // for문 안에서는 5초 간격으로 recvfrom 함수를 호출
    {
        sleep(5);   //delay 5 sec.
        adr_sz = sizeof(your_adr);
// 총 3회의 recvfrom 함수호출을 통해 데이터를 수신함. recvfrom 함수호출에는 5초간의 지연시간이 존재하기 때문에 
// recvfrom 함수가 호출되기 이전에 bound_host1.c에서 3회의 sendto 함수호출이 진행되어서, 
// 데이터는 이미 bound_host2.c 에서 bound_host1.c에 전송된 상태로 놓임.
        str_len = recvfrom(sock, message, BUF_SIZE, 0, (struct sockaddr*)&your_adr, &adr_sz);
        printf("Message %d: %s\n", i+1, message); // recvform 함수가 몇 번 호출되었는지 확인
    }
    close(sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}