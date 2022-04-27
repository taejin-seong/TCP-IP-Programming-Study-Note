### WSAStringToAddress & WSAAddressToString <br>

* 윈속2에 추가된 변환함수 **`WSAStringToAddress`** 와 **`WSAAddressToString`** 
* 이 두개의 함수는 **`inet_ntoa`**, 그리고 **`inet_addr`** 함수와 기능은 같으나 다양한 프로토콜에 적용이 가능하다는 장점이 있음. 
  + 즉 IPv4뿐 아니라 IPv6에서도 사용이 가능.

* **`inet_ntoa`**, **`inet_addr`** 함수를 사용하는 경우 리눅스 기반에서 윈도우 기반으로, 그리고 그 반대로도 프로그램의 변경이 용이하지만,  다음 두 함수를 사용하면 **윈도우에 종속적인 코드가 만들어지기 때문에** 다른 운영체제로의 이식성이 떨어짐.

<hr>

<br>


* **`WSAStringToAddress`** 는 주소정보를 나타내는 문자열을 가지고 주소정보 구조체 변수를 적절히 채워 넣을 때 호출하는 함수
```C
#include <winsock2.h>

/* @return : 성공 시 0, 실패 시 SOCKET_ERROR 반환
 * @param  :    AddressString : IP와 PORT번호를 담고 있는 문자열의 주소 값 전달.
 *              AddressFamily : 첫 번째 인자로 전달된 주소정보가 속하는 주소체계 정보전달.
 *             lpProtocolInfo : 프로토콜 프로바이더(Provider)설정, 일반적으로 NULL 전달.
 *                  lpAddress : 주소정보를 담을 구조체 변수의 주소 값 전달.
 *            lpAddressLength : 네 번째 인자로 전달된 주소 값의 변수 크기를 담고 있는 변수의 주소 값 전달.
 */
INT WSAStringToAddress(LPTSTR AddressString, INT AddressFamily,  LPWSAPROTOCOL_INFO  lpProtocolInfo,
                       LPSOCKADDR  lpAddress,  LPINT lpAddressLength );
```

<br>

<hr>

<br>

* **`WSAAddressToString`** 함수는 **`WSAStringToAddress`** 함수와 반대의 기능을 제공함. 즉, 구조체 변수에 저장된 데이터를 참조하여 주소정보를 담고 있는 문자열을 만들어 반환.
```C
#include <winsock2.h>

/* @return : 성공 시 0, 실패 시 SOCKET_ERROR 반환
 * @param  :              lpsaAddress : 문자열로 변환할 주소정보를 지니는 구조체 변수의 주소,
 *                    dwAddressLength : 첫 번째 인자로 전달된 구조체 변수의 크기 전달.
 *                     lpProtocolInfo : 프로토콜 프로바이더(Provider)설정, 일반적으로 NULL 전달.
 *                  lpszAddressString : 문자열로 변환된 결과를 저장할 배열의 주소 값 전달.
 *            lpdwAddressStringLength : 네 번째 인자로 전달된 주소 값의 변수 크기를 담고 있는 변수의 주소 값 전달.
 */
INT WSAAddressToString(LPSOCKADDR lpsaAddress, DWORD  dwAddressLength, LPWSAPROTOCOL_INFO lpProtocolInfo,
                       LPTSTR lpszAddressString, LPDWORD  lpdwAddressStringLength);
```

