/* Linux */
/* 
 *  < 계산기 서버, 클라이언트의 예 >
 *
 * # 클라이언트는 서버에 접속하자마자 피연사자의 개수정보를 1바이트 정수형태로 전달한다.
 * # 클라이언트가 서버에 전달하는 정수 하나는 4바이트로 표현한다.
 * # 정수를 전달한 다음에는 연산의 종류를 전달한다. 연산정보는 1바이트로 전달한다.
 * # 문자 +,-,* 중 하나를 선택해서 전달한다.
 * # 연산결과를 얻은 클라이언트는 서버와 연결을 종료한다.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE    1024
#define OPSZ        4
void error_handling(char *message);
int calculate(int opnum, int opnds[], char oprator);

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;
    char opinfo[BUF_SIZE];
    int result, opnd_cnt, i;
    int recv_cnt, recv_len;
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

    if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))== -1)
    {
        error_handling("bind() error");
    }

    if (listen(serv_sock, 5) == -1)
    {
        error_handling("listen() error");
    }
    clnt_adr_sz = sizeof(clnt_adr);

// 총 5개의 클라이언트 연결요청을 수용하기 위해 for문 구성
    for (i = 0; i < 5; i++)
    {
        opnd_cnt = 0;
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
        read(clnt_sock, &opnd_cnt, 1); // 제일 먼저 피연산자의 개수정보를 수신.

        recv_len = 0;
// 피연산자의 개수정보를 바탕으로 피연사 정보를 수신        
        while ((opnd_cnt*OPSZ+1) > recv_len)
        {
            recv_cnt = read(clnt_sock, &opinfo[recv_len], BUF_SIZE-1);
            recv_len += recv_cnt;
        }
        result = calculate(opnd_cnt, (int*)opinfo, opinfo[recv_len-1]); // calculate 함수를 호출하면서, 피연산자의 정보와 연산자 정보를 인자로 전달.
        write(clnt_sock, (char*)&result, sizeof(result)); // calculate 함수가 반환한 연산결과를 클라이언트에게 전송.
        close(clnt_sock);
    }
    close(serv_sock);
    return 0;
}

int calculate(int opnum, int opnds[], char oprator)
{
    int result = opnds[0],i;
    switch (oprator)
    {
    case '+':
        for (i = 1; i < opnum; i++) 
        {
             result += opnds[i];
        } 
        break;

    case '-':
        for (i = 1; i < opnum; i++)
        {
            result -= opnds[i];
        } 
        break;

    case '*':
        for (i = 1; i < opnum; i++)
        {
            result *= opnds[i];    
        } 
        break;
    }
    return result;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
} 
