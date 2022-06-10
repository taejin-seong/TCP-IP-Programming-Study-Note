/* Linux */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int status;
// 11행에서 생성된 자식 프로세스는 15행에서 보이듯이 main 함수 내에서의 return문 실행을 통해서 종료하게 됨.
    pid_t pid = fork();

    if (pid == 0)
    {
        return 3;
    }
    else
    {
        printf("Child PID: %d \n", pid);
// 21행에서 생성된 자식 프로세스는 24행에서 보이듯이 exit 함수호출을 통해서 종료하게 됨.
        pid = fork();
        if (pid = 0)
        {
            exit(7);
        }
        else
        {
            printf("Child PID: %d \n", pid);
// wait 함수를 호출하고 잇음. 이로 인해서 종료된 프로세스 관련 정보는 status에 담기게 되고, 해당 정보의 프로세스는 완전히 소멸됨.
            wait(&status);
// 33행의 매크로 함수 WIFEXITED를 통해서 자식 프로세스의 정상종료 여부를 확인하고 있음.
// 그리고 정상종료인 경우에 한해서 WEXITSTATUS 함수를 호출하여 자식 프로세스가 전달한 값을 출력하고 있음.
            if (WIFEXITED(status))
            {
                printf("Child send one: %d \n", WEXITSTATUS(status));
            }

// 39행~43행 : 앞서 생성한 자식 프로세스가 두 개이므로 또 한번의 wait 함수호출과 매크로 함수의 호출을 진행하고 있음.
            wait(&status);
            if (WIFEXITED(status))
            {
                printf("Child send two: %d \n", WEXITSTATUS(status));
            }
// 부모 프로세스의 종료를 멈추기 위해서 삽입한 코드. 이 순간에 자식 프로세스의 상태를 확인하면 됨.
            sleep(30); // Sleep 30 sec.
        }
    }

    return 0;
}