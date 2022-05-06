/* Linux */
/* 
 * Iterative 형태로 동작하는 에코 서버 그리고 이와 함께 동작하는 에코 클라이언트 프로그램 기본동작 방식 설명
 * 
 * # 서버는 한 순간에 하나의 클라이언트와 연결되어 에코 서비스를 제공함.
 * # 클라이언트는 프로그램 사용자로부터 문자열 데이터를 입력 받아서 서버에 전송.
 * # 서버는 전송 받은 문자열 데이터를 클라이언트에게 재전송. 즉 에코 시킴.
 * # 서버와 클라이언트간의 문자열 에코는 클라이언트가 Q를 입력할 때까지 계속함.
 */
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
    int str_len;
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

// connect 함수호출로 인한 연결요청 정보가 서버의 대기 큐에 등록되면, connect 함수는 정상적으로 호출을 완료
// 따라서 53행에 의해서 연결되었다는 문자열 정보가 출력되더라도 서버에서 accpet 함수를 호출하지 않는 상황이라면 실제 서비스가 이뤄지지 않음을 주의
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

        write(sock, message, strlen(message));
        str_len = read(sock, message, BUF_SIZE);
        message[str_len] = 0;
        printf("Message from server: %s", message);
    }
    close(sock); // 이렇게 close 함수가 호출되면 상대 소켓으로 EOF가 전송됨. 즉, EOF는 연결의 끝을 의미

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}