/* Linux */
// sigaction 함수를 기반으로 좀비 프로세스의 생성을 막는 예제
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void read_childproc(int sig)
{
    int status;
    pid_t id = waitpid(-1, &status, WNOHANG);
    if (WIFEXITED(status))
    {
        printf("Removed proc id: %d \n", id);
        printf("Child send: %d \n", WEXITSTATUS(status));
    }
}

int main(int argc, char *argv[])
{
    pid_t pid;
 // 25~29행: 시그널 SIGCHLD에 대한 시그널 핸들러의 등록과정을 보임. 이로써 자식 프로세스가 종료되면
 //          9행에 정의된 함수가 호출됨. 그리고 이 함수 내에서의 waitpid 함수호출로 인해 자식 프로세스는 좀비가 되지않고 소멸함.
    struct sigaction act;
    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, 0);

    pid = fork(); // 부모 프로세스를 통해서 총 두 개의 자식 프로세스를 생성하고 있음. (39행 포함해서 2개)
    if (pid == 0){
        puts("Hi I'm child process");
        sleep(10);
        return 12;
    }
    else{
        printf("Child proc id: %d \n", pid);
        pid = fork(); // 부모 프로세스를 통해서 총 두개의 자식 프로세스를 생성하고 있음 (31행 포함해서 2개)
        if (pid == 0){
            puts("Hi! I'm child process");
            sleep(10);
            exit(24);
        }
        else{
            int i;
            printf("Child proc id: %d \n", pid);
            // 시그널 SIGCHLD의 발생을 대기하기 위해서 부모 프로세스를 5초간 5회 멈춰 놓았음. 물론 시그널이 발생하면
            // 부모 프로세스는 깨어나기 때문에 실제 멈춰잇는 시간은 25초가 되지않음.
            for (i = 0; i < 5; i++){
                puts("wait...");
                sleep(5);
            }
        }
    }
    return 0;
}