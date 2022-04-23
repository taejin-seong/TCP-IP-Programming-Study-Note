## 윈도우 소켓을 위한 헤더와 라이브러리 설정 <br>
* 윈도우 소켓 (윈속 : winsock)을 기반으로 프로그램을 개발하기 위해서는 기본적으로 다음 두 가지를 진행해야한다.
  + 헤더파일 winsock2.h를 포함한다.
  + **ws2_32.lib 라이브러리를 링크시켜야 한다.**
 
<br>


* 책 내용의 p35~p36은 Visual Studio 개발환경을 바탕으로 ws2_32.lib 라이브러리의 프로젝트 단위 링크 방법을 설명하나, 본 학습 노트에서는 **Windows 10**에서의 TCP/IP 프로그래밍 개발환경을  **Dev C++ 5.11 버전으로 선택하여 사용하므로** 이에 책과 다른 변경점을 정리하였다.<br>
  + 1). **링커 추가** 
    - Dev C++ 개발환경에서 ws2_32.lib 라이브러리를 링크시키는 방법
    - `도구 → 컴파일러 설정 → 다음의 링커 추가 명령 사용 → -lws_32 작성 ` <br>
    
     <p align="center">
     <img src="https://user-images.githubusercontent.com/70312248/164916405-d8164100-1828-40c7-aa3a-6c3f0ef3ea26.png" width="450" height="500"/> </p><br>
     
  + 2). **실행 시키기**
    - Dev C++ 개발환경에서  TCP/IP 프로그래밍 파일을 실행시키는 방법
    - `프로그래밍된 파일을 컴파일 → 컴파일 후 생성된 .exe 파일을 윈도우 cmd에서 실행`<br>
    
     <p align="center">
     <img src="https://user-images.githubusercontent.com/70312248/164916880-fa5b2a4d-fbb5-46c8-8382-7c1f434e017c.png" width="1300" height="500"/> </p><br>
