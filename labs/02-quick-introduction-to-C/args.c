#include <stdio.h>

/*
명령줄 인자(Command Line Arguments) 처리하는 예제
*/

int main(int argc, char *argv[])
{
	int		i;

	// argc: 명령줄 인자의 개수 (프로그램의 이름도 포함함)
	// argv: 명령줄 인자들의 문자열 배열
	for (i = 0 ; i < argc ; i++)
		printf("argv[%d]=%s\n", i, argv[i]);

	// argv[0]은 항상 프로그램의 이름(또는 실행경로)이다.
	// argv[1]부터는 실제로 사용자가 입력한 인자들
	
	return 0;
}