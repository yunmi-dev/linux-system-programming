#include <stdio.h>

int main()
{
	char c, s[80];
	int i; long l;
	float f; double d;
	
	scanf("%c %s %d %ld %f %lf", &c, s, &i, &l, &f, &d); 
	printf("Output: %c %s %d %ld %.4f %.2lf\n", c, s, i, l, f, d); 

	c = getchar();
	putchar(c);

	gets(s);
	// 주의: gets() 함수는 보안상 취약점이 있어 현대 C 프로그래밍에서는 권장X
	// 학습 목적으로만 사용하며, 실제 개발에서는 fgets()를 사용하는 것이 좋다. (컴파일 시에도 warning)
	puts(s);

	return 0;
}