/* Linux */
#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, int argv[])
{
    unsigned short host_port = 0x1234;  // 2바이트에 데이터를 변수에 저장
    unsigned short net_port;
    unsigned long host_addr = 0x12345678; // 4바이트에 데이터를 변수에 저장
    unsigned long net_addr;

/* 변수 host_port와 host_addr에 저장된 데이터를 네트워크 바이트 순서로 변환하고 있음.
 * 만약 리틀 엔디안 기준으로 정렬하는 CPU에서 실행된다면, 바이트 순서가 바뀐 값이 반환되어 변수에 저장됨. 
 * 빅 엔디안 기준으로 정렬하는 CPU상에서 실행을 했다면 변환 이후에도 값은 달라지지 않음.
 */
    net_port = htons(host_port);
    net_addr = htonl(host_addr);

    printf("Host ordered port: %#x \n", host_port);
    printf("Network ordered port: %#x \n", net_port);
    printf("Host ordered address: %#lx \n", host_addr);
    printf("Network ordered address: %#lx \n", net_addr);

    return 0;
}