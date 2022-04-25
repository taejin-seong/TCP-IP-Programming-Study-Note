* API상에서의 IP주소와 PORT번호 표현을 위한 **구조체**가 정의되어있음. 
* 따라서 이 구조체를 중심으로 목적지 주소의 표현방법에 대해 IPv4 중심으로 살펴보도록함.
<br>

## IPv4 기반의 주소표현을 위한 구조체<br>
* 아래의 구조체는 **`bind 함수`** 에 주소정보를 전달하는 용도로 사용됨.
```C 
struct sockaddr_in
{
  sa_family_t       sin_family; //주소체계(Address Family)
  uint16_t          sin_port;   //16비트 TCP/UDP PROT번호
  struct in_addr    sin_addr;   //32비트 IP주소
  char              sin_zero;   //사용되지 않음  
}
```
* 그리고 위의 구조체 정의에 사용된 또 다른 구조체 `in_addr`은 다음과 같이 정의되어 있음.
```C
struct in_addr
{
  in_addr_t        s_addr;     //32비트 IPv4 인터넷 주소
}
```
* 두 구조체 설명에 앞선 생소한 자료형에 대한 소개가 먼저 필요함. <br>

|자료형 이름|자료형에 담길 정보|선언된 헤더파일|
|------|---|:---:|
|int8_t <br> uint8_t <br> int16_t <br> uint16_t <br> in32_t <br> uint32_t |signed 8-bit int <br> unsigned 8-bit int (unsigned char) <br> signed 16-bit int <br> unigned 16-bit int (unsigned short) <br> signed 32-bit int <br> unsigned 32-bit int (unsigned long) |sys/types.h|
|**sa_family_t** <br> **socklen_t**|주소체계(address family) <br> 길이정보(length of struct) | sys/socket.h|
|**in_addr_t** <br> **in_port_t** |IP주소정보, uint32_t로 정의되어 있음 <br> PORT번호정보, uint16_t로 정의되어 있음 |netinet/in.h|

<br>

## 구조체 sockaddr_in의 멤버에 대한 분석 <br>
* 멤버 **`sin_family`**<br>
  + 프로토콜 체계마다 적용하는 주소체계가 다름. ex) IPv4는 4바이트, IPv6는 16바이트 주소체계를 사용
  + 따라서 아래의 표를 참조하여 멤버 **`sin_family`** 에 적용할 주소체계 정보를 저장해야함.

<br>

|주소체계 (Address Family)| 의미|
|-------|-------|
|AF_INET | IPv4 인터넷 프로토콜에 적용하는 주소체계 |
|AF_INET6| IPv6 인터넷 프로토콜에 적용하는 주소체계|
|AF_LOCAL| 로컬 통신을 위한 유닉스 프로토콜의 주소체계|

<br>

* 멤버 **`sin_port`**<br>
  + 16비트 PORT번호를 저장함 단, '네트워크 바이트 순서'로 저장해야함. 


<br>

* 멤버 **`sin_port`**<br>
  + 32비트 IP주소정보를 저장함 단, '네트워크 바이트 순서'로 저장해야함.

<br>

* 멤버 **`sin_zero`**<br>
  + 특별한 의미를 지니지 않는 멤버.
  + 단순히 구조체 `sockaddr_in`의 크기를 구조체 `sockaddr`와 일치시키기 위해 삽입된 멤버
  + 그러나 반드시 0으로 채워야함.

