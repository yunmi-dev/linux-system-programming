#include <stdio.h>
#include <string.h>

/*
의도적으로 NULL 포인터에 문자열을 copy하여 Segmentation Fault를 발생시킨다.
NULL 포인터 역참조(dereferencing)의 예시!
*/ 
 
int main()
{
	int		i;
	double	j;
	char	*bug = NULL; // NULL로 초기화된 문자열 포인터 선언

	for (i = 0 ; i < 5 ; i++) {
		j = i/2 + i;
		printf("j is %lf \n", j );
	}

	strcpy(bug, "hi"); /// bug는 NULL 포인터로, 그 어떤 유효한 메모리 영역도 가리키지 않는데 여기에 "hi" 문자열을 복사하려고 시도함. => 유효하지 않은 메모리 접근 (Segmentation Fault 발생)
	printf("bug is %s \n", bug);

	return 0;
}