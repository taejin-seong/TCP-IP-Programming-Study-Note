/* Linux */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>

int main(void)
{
    int fd1, fd2, fd3;
    
    /* 하나의 파일과 두 개의 소켓을 생성 */
    fd1 = socket(PF_INET, SOCK_STREAM, 0);
    fd2 = open("test.dat", O_CREAT|O_WRONLY|O_TRUNC);
    fd3 = socket(PF_INET, SOCK_DGRAM, 0);

    /* 앞서 생성한 파일 디스크립터의 정수 값을 출력 */
    // 표준 입출력에서 0~2까지 파일 디스크립터가 넘버링 되어있으므로 파일 디스크립터는 3부터 시작함.
    printf("file descriptor 1 : %d\n", fd1);  
    printf("file descriptor 2 : %d\n", fd2);
    printf("file descriptor 3 : %d\n", fd3);         

    close(fd1);
    close(fd2);
    close(fd3);

    return 0;    
}