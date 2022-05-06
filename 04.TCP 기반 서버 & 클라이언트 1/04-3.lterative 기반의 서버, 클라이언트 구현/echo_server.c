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
    int serv_sock, clnt_sock;
    char message[BUF_SIZE];
    int str_len, i;

    struct sockaddr_in serv_adr, clnt_adr; 
    socklen_t clnt_adr_sz;

    if (argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
    {
        error_handling("socket() error");
    }

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
    {
        error_handling("bind() error");
    }

    if (listen(serv_sock, 5) == -1)
    {
        error_handling("listen() error");
    }

    clnt_adr_sz = sizeof(clnt_adr);

//59~79행 : 총 5개의 클라이언트에게 서비스를 제공하기 위한 반복문. 결과적으로 accept 함수가 총 5회 호출 되어 총 5개의 클라이언트에게 순서대로 에코 서비스를 제공
    for (i = 0; i < 5; i++)
    {
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
        if (clnt_sock == -1)
        {
            error_handling("accept() error");
        }

        else
        {
            printf("Connected client %d \n", i+1);
        }

//73~76행 : 실제 에코서비스가 이뤄지는 부분, 읽어 들인 문자열을 그대로 전송함
        while((str_len = read(clnt_sock, message, BUF_SIZE)) != 0)
        {
            write(clnt_sock, message, str_len);
        }
// 소켓을 대상으로 close 함수가 호출되면, 연결되어있던 상대방 소켓에게 EOF가 전달됨. 즉, 클라이언트 소켓이 close 함수를 호출하면 73행의 조건은 거짓(false)이 되어 80행을 실행함.
         close(clnt_sock); 
    }
// 총 5개의 클라이언트에게 서비스를 제공하고 나면, 마지막으로 서버 소켓을 종료하면서 프로그램을 종료함.
    close(serv_sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}