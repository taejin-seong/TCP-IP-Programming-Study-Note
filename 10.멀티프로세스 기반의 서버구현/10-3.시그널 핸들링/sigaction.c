/* Linux */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig)
{
    if (sig == SIGALRM){
        puts("Time out");
    }
    alarm(2);
}

int main(int argc, char *argv[])
{
    int i;
// 18, 19행: 시그널 발생시 호출될 함수의 등록을 위해서는 이렇듯 sigaction 구조체 변수를 선언해서 멤버 sa_handler에 함수 포인터 값을 저장해야함.
    struct sigaction act;
    act.sa_handler = timeout; 
    sigemptyset(&act.sa_mask); // 앞서 sigaction 구조체를 설명하면서 멤버 sa_mask의 모든 비트를 0으로 초기화해야 한다고 하였는데, sigemptyset 함수는 바로 이러한 목적으로 호출되는 함수.
    act.sa_flags = 0; // sa_flags 역시 signal 함수를 대신하기 위해서 필요한 멤버가 아니므로 0으로 초기화 시킴.
// 23, 25행: 시그널 SIGALRM에 대한 핸들러를 지정하고 있음. 그리고 alarm 함수호출을 통해서 2초 뒤에 시그널 SIGALRM의 발생을 예약해 놓음. 
    sigaction(SIGALRM, &act, 0);

    alarm(2);

    for (i = 0; i < 3; i++){
        puts("wait...");
        sleep(100);
    }
    return 0;
}