/* Linux */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int sock;
    int snd_buf = 1024 * 3, rcv_buf = 1024 * 3; 
    int state;
    socklen_t len;

    sock = socket(PF_INET, SOCK_STREAM, 0);
    state = setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void*)&rcv_buf, sizeof(rcv_buf));  // 입력버퍼와 출력버퍼의 크기를 각각 3KByte로 변경하고 있음.
    if (state)
    {
        error_handling("setsockopt() error");
    }

    state = setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void*)&snd_buf, sizeof(snd_buf)); // 입력버퍼와 출력버퍼의 크기를 각각 3KByte로 변경하고 있음.
    if (state)
    {
        error_handling("setsockopt() error");
    }

    len = sizeof(snd_buf);
    state = getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void*)&snd_buf, &len); // 입출력 버퍼의 변경요청에 따른 결과를 확인하기 위해서 입출력 버퍼의 크기를 참조하고 있음.
    if (state)
    {
        error_handling("getsockopt() error");
    }  

    len = sizeof(rcv_buf);  
    state = getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void*)&rcv_buf, &len); // 입출력 버퍼의 변경요청에 따른 결과를 확인하기 위해서 입출력 버퍼의 크기를 참조하고 있음.
    if (state)
    {
        error_handling("getsockopt() error");
    }  
        
    printf("Input buffer size: %d \n", rcv_buf);
    printf("Output buffer size: %d \n", snd_buf);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}