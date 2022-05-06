/* Windows */
/*
 * 리눅스 기반 예제를 윈도우 기반으로 변경하기 위해서는 일단 다음 네 가지만 기억하면 됨.
 *
 * # WSAStartup, WSACleanup 함수호출을 통한 소켓 라이브러리 초기화와 해제
 * # 자료형과 변수의 이름을 윈도우 스타일로 변경하기
 * # 데이터 송수신을 위해서 read, write 함수 대신 recv, send 함수 호출하기
 * # 소켓의 종료를 위해서 close 대신 closesocket 함수 호출하기
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define BUF_SIZE    1024
void ErrorHandling(char *message);