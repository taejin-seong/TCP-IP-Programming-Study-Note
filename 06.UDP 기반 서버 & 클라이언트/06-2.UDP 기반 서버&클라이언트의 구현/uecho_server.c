/* Linux */
/* TCP와 달리 UDP는 연결요청과 그에 따른 수락의 과정이 존재하지 않기 때문에 서버 및 클라이언트라는 표현이 적절하지 않은 부분도 있음.
 * 다만 서비스를 제공한다는 측면에서 서버라하는 것이니 오해하면 안됨. 
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
    int serv_sock;
    char message[BUF_SIZE];
    int str_len;
    socklen_t clnt_adr_sz;

    struct sockaddr_in serv_adr, clnt_adr;
    if (argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_DGRAM, 0); // UDP 소켓 생성을 위해 socket 함수의 두 번째 인자로 SOCK_DGRAM을 전달함.
    if (serv_sock == -1)
    {
        error_handling("UDP socket creation error");
    }

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
    {
        error_handling("bind() error");
    }

    while (1)
    {
        clnt_adr_sz = sizeof(clnt_adr);
// 40행에 할당된 주소로 전달되는 모든 데이터를 수신함. 물론 데이터의 전달대상에는 제한이 없음.
        str_len = recvfrom(serv_sock, message, BUF_SIZE, 0, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
// recvfrom 함수호출을 통해서 데이터를 전송한 이의 주소정보도 함께 얻게 되는데, 바로 이 주소정보를 이용해서 수신된 데이터를 역으로 재전송하고 있음.         
        sendto(serv_sock, message, str_len, 0, (struct sockaddr*)&clnt_adr, clnt_adr_sz);
    }
    close(serv_sock); // while문을 빠져나가기 위한 break문이 삽입되지 않았기 때문에 사실상 이 문장은 실행되지 않음.
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}