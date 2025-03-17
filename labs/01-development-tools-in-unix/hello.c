#include <stdio.h>

/*
Makefile를 보면 

	libmine.a : mystrcpy.o
		ar ruv libmine.a mystrcpy.o

mystrcpy.o 파일로부터 libmine.a 정적 라이브러리를 생성하고,

	LDFLAGS = -L. -lmine
	$(TARGET) : $(OBJS) libmine.a
		$(CC) -o $@ $(OBJS) $(LDFLAGS)

메인 프로그램을 빌드할 때 이 라이브러리를 링크함.
(-lmine은 libmine.a 라이브러리를 링크하라는 의미, -L.은 현재 디렉토리에서 라이브러리를 찾으라는 의미)


mystrcpy 함수를 정의한 mystrcpy.c 파일을 컴파일 => mystrcpy.o 생성
mystrcpy.o => libmine.a 생성
libmine.a와 hello.o를 링크 => 최종 실행파일인 hello 생성
이 메커니즘으로 파일에 정의해놓은 함수를 메인 프로그램에서 사용할 수 있었다.
*/

int main()
{
	char	str[80];

	mystrcpy(str, "Hello, World!");
	puts(str);

	return 0;
}