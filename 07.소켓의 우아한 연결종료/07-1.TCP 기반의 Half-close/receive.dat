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
    int serv_sd, clnt_sd;
    FILE * fp;
    char buf[BUF_SIZE];
    int read_cnt;

    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_sz;

    if (argc != 2)
    {
        printf("Usage : %s <port> \n", argv[0]);
        exit(1);
    }

    fp = fopen("file_server.c", "rb");  // 서버의 소스파일인 file_server.c를 클라이언트에게 전송하기 위해 파일을 열고있음.
    serv_sd = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sd == -1)
    {
        error_handling("socket() error");
    }

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sd, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
    {
        error_handling("bind() error");
    }

    if (listen(serv_sd, 5) == -1)
    {
        error_handling("listen() error");
    }

    clnt_adr_sz = sizeof(clnt_adr);
    clnt_sd = accept(serv_sd, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);

// 54~63행 : accept 함수호출을 통해 연결된 클라이언트에게 파일 데이터를 전송하기 위해 반복문이 구성되어 있음.
    while (1)
    {
        read_cnt = fread((void*)buf, 1, BUF_SIZE, fp);
        if (read_cnt < BUF_SIZE)
        {
            write(clnt_sd, buf, read_cnt);
            break;
        }
        write(clnt_sd, buf, BUF_SIZE);
    }

    shutdown(clnt_sd, SHUT_WR); // 파일 전송후에 출력 스트림에 대한 Half-close를 진행, 이로써 클라이언트에게는 EOF가 전송되고, 이를 통해 클라이언트는 파일전송이 완료되었음을 인식할 수 있음.
    read(clnt_sd, buf, BUF_SIZE); // 출력 스트림만 닫았기 때문에 입력 스트림을 통한 데이터의 수신은 여전히 가능.
    printf("Message from client : %s \n", buf);

    fclose(fp);
    close(clnt_sd);
    close(serv_sd);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}