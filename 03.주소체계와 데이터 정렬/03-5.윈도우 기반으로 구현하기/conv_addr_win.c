/* Windows */
/* 
undef는 기존에 정의된 매크로를 해제하는 경우에 사용함.
프로젝트 환경에 따라서 VC++ 자체적으로 이 두매크로를 정의하는 경우가 있는데,
그렇게 되면 23행 26행에서 호출하는 두 함수의 매개변수형이 유니코드 기반으로 바뀌어서 잘못된 실행결과를 보임.
*/
#undef UNICODE  
#undef _UNICODE
#include <stdio.h>
#include <winsock2.h>

int main(int argc, char *argv[])
{
    //WSAStringToAddress 함수에 전달되는 문자열의 형태.
    char *strAddr = "203.211.218.102:9190";

    char strAddrBuf[50];
    SOCKADDR_IN servAddr;
    int size = 0;

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    size = sizeof(servAddr);
    //함수호출을 통해 14행의 문자열을 기반으로 18행에 선언된 구조체 변수에 주소 정보를 채움.
    WSAStringToAddress(strAddr, AF_INET, NULL, (SOCKADDR*)&servAddr, &size);

     size = sizeof(strAddrBuf);
    //26행에서의 변환과정을 역으로 실행함. 즉, WSAAddressToString 함수호출을 통해서 구조체 변수에 저장된 주소정보를 문자열의 형태로 변환함.
    WSAAddressToString((SOCKADDR*)&servAddr, sizeof(servAddr), NULL, strAddrBuf,
                        &size);

    printf("Second conv result : %s \n", strAddrBuf);
    WSACleanup();
    return 0;
}
