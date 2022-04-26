/* Linux */
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    struct sockaddr_in addr1, addr2;
    char *str_ptr;
    char  str_arr[20];

    addr1.sin_addr.s_addr = htonl(0x1020304);
    addr2.sin_addr.s_addr = htonl(0x1010101);

// 구조체 변수 addr1에 저장된 IP정보를 전달하면서 inet_ntoa 함수를 호출함.
// 따라서 IP주소 정보를 담은 문자열의 주소 값이 반환됨.
    str_ptr = inet_ntoa(addr1.sin_addr); 
    strcpy(str_arr, str_ptr); // 17행의 함수호출로 반환된 주소 값을 참조해서 문자열을 복사함.
    printf("Dotted-Decimal notation1:  %s \n", str_ptr);

// inet_ntoa 함수가 다시 한번 호출되었음. 이로써 17행에서 반환된 주소 값에는 다른 문자열 정보가 채워짐.
// 이를 24행의 출력결과를 통해 확인할 수 있음.
    inet_ntoa(addr2.sin_addr);
    printf("Dotted-Decimal notation2:  %s \n", str_ptr);
    printf("Dotted-Decimal notation3:  %s \n", str_arr); // 18행에서 문자열을 복사해뒀기 때문에, 17행의 함수호출을 통해 얻은 문자열을 재출력할 수 있음.

    return 0;
}