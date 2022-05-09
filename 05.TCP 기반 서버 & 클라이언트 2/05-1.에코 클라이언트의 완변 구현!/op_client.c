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

#define BUF_SIZE 1024
// 피연산자의 바이트 수와 연산결과의 바이트 수를 상수화
#define RLT_SIZE 4
#define OPSZ     4
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int sock;
    char opmsg[BUF_SIZE]; // 데이터 송수신을 위한 메모리 공간
    int result , opnd_cnt, i;
    struct sockaddr_in serv_adr;

    if (argc != 3)
    {
        printf("Usage : %s <IP> <port> \n", argv[0]);
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

    fputs("Operand count : ", stdout);
// 사용자로부터 피연산자의 개수정보를 입력 받은 후, 이를 opmsg배열에 저장함.
    scanf("%d", &opnd_cnt);
    opmsg[0] = (char)opnd_cnt;

// 사용자로부터 정수를 입력받아서 opmsg배열에 저장.
    for (i = 0; i < opnd_cnt; i++)
    {
        printf("Operand %d: ", i+1);
        scanf("%d", (int*)&opmsg[i*OPSZ+1]);
    }

    fgetc(stdin); // 문자를 입력받기 전 버퍼에 남아있는 \n 문자의 삭제를 위해 fgetc 함수호출
    fputs("Operator: ", stdout); 
    scanf("%c", &opmsg[opnd_cnt+OPSZ+1]); // 연산자 정보를 입력 받아서 opmsg배열에 저장.
    write(sock, opmsg, opnd_cnt*OPSZ+2); // write 함수호출을 통해 opmsg에 저장되어 있는 연산과 관련된 정보를 한번에 전송 (TCP는 데이터의 경계가 존재X)
    read(sock, &result, RLT_SIZE); // 서버가 전송해주는 연산결과의 저장과정, 수신할 데이터의 크기가 4바이트이기 때문에 이렇게 한번에 read 함수호출로 충분히 수신이 가능.

    printf("Operation result: %d \n", result);
    close(sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
} 
