/* Linux */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE    1024
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int sock;
    char message[BUF_SIZE];
    int str_len, recv_len, recv_cnt;
    struct sockaddr_in serv_adr;

    if (argc != 3)
    {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        error_handling("socket() error");
    }

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
    {
        error_handling("connect() error!");
    }

    else
    {
        puts("Connected...........");
    }

    while (1)
    {
        fputs("Input message(Q to quit): ", stdout);
        fgets(message, BUF_SIZE, stdin);

        if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
        {
            break;
        }

// 57~ 70행까지가 변경 및 추가 된 부분
// 전송한 데이터의 크기만큼 데이터를 수신하기 위해서 read 함수를 반복호출 함. 
// 따라서 정확히 전송한 바이트 크기만큼 데이터를 수신할 수 있게 됨. 
        str_len = write(sock, message, strlen(message));

        recv_len = 0;
        while (recv_len < str_len) // while (recv_len != str_len)과 동일하나 해당 반복문은 무한루프에 빠질 문제가 발생할 수 있음.
        {
            recv_cnt = read(sock, &message[recv_len], BUF_SIZE-1);
            if (recv_cnt == -1)
            {
                error_handling("read() error!");
            }

            recv_len += recv_cnt;
        }
        message[recv_len] = 0;
        printf("Message from server: %s", message);
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