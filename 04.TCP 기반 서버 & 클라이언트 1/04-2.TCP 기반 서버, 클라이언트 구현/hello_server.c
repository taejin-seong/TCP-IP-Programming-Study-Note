/* Linux */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    char message[] = "Hello World!";

    if (argc != 2)
    {
        printf("Usage : %s <port> \n", argv[0]);
        exit(1);
    }

/* 서버 프로그램의 구현과정에서 제일 먼저 해야 할일이 소켓의 생성 */
    serv_sock = socket(PF_INET, SOCK_STREAM, 0); // 소켓을 생성, 단 이 때 생성되는 소켓은 아직 서버 소켓이라 부르기 이른 상태.
    if (serv_sock == -1)
    {
        error_handling("socket() error");
    }

/* 35~43행 : 소켓의 주소할당을 위해 구조체 변수를 초기화하고 bind 함수를 호출 */
    memset(&serv_addr, 0 , sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == 1) 
    {
        error_handling("bind() error");
    }

/* 연결요청 대기상태로 들어가기 위해 listen 함수를 호출 */
    if (listen(serv_sock, 5) == 1) // 연결요청 대기 큐의 크기를 5로 설정, 이제야 비로소 28행에서 생성한 소켓을 가리켜 서버 소켓이라 할 수 있음.
    {
        error_handling("listen() error");
    }

/* accept 함수가 호출 되었으니, 대기 큐에서 첫 번째로 대기 중에 있는 연결요청을 참조하여 클라이언트와의 연결을 구성하고, 이 때 생성된 소켓의 파일 디스크립터를 반환 */
    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size); //만약 이 함수가 호출되었을 때 대기 큐가 비어있는 상태라면, 대기 큐가 찰 때까지,(클라이언트 연결요청이 들어 올 때 까지) accept 함수는 반환하지 않음.
    if(clnt_sock == -1)
    {
        error_handling("accpet() error");
    }

/* write 함수호출을 통해 클라이언트에게 데이터를 전송, 그리고 close 함수호출을 통해서 연결을 끊음. */
    write(clnt_sock, message, sizeof(message)); 
    close(clnt_sock);
    close(serv_sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message , stderr);
    fputc('\n', stderr);

    exit(1);
}