#include <stdio.h>

/*
다양한 데이터 형식을 출력해보는 예제
*/

int main()
{
	char c = 'a', s[] = "hello";	// 문자, 문자열
	int i = 100; long l = 99999;	// 정수형 변수
	float f = 3.14; double d = 99.999;	// 부동 소수점 변수
	int *p = &i;					// 포인터 변수 (i의 주소를 저장함)
	
	printf("Output: %c %s %d %#X %ld %.4f %.2lf %p\n", c, s, i, i, l, f, d, p); 
	// 다양한 서식 지정자를 사용해서 printf로 출력

    // %c: 문자, %s: 문자열, %d: 10진 정수, %#X: 0x 접두사가 있는 16진수
    // %ld: long 정수, %.4f: 소수점 4자리 float, %.2lf: 소수점 2자리 double
    // %p: 포인터 주소

	// character 출력 함수
	putchar(c);

	// 문자열 출력 함수 (가종 개행도 포함함)
	puts(s);

	return 0;
}