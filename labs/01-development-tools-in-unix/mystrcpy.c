#include <string.h>

/*
C 표준 라이브러리의 strcpy 함수 직접 구현
*/

void mystrcpy(char *dst, char *src)
{
	while (*src)  {
		*dst++ = *src++;
	}
	*dst = *src; // 널 문자(\0) 복사: 문자열은 널 문자로 끝나야 함
	/// 마지막에 널 문자로 끝나도록 하지 않으면, 다른 함수들(printf 등)이 문자열의 끝을 찾지 못하고 메모리를 계속 일어나가다가 예상치 못한 동작을 일으킬 수 있음
}