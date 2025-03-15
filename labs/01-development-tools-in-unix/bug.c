#include <stdio.h>
#include <string.h>

/*
bug.c 프로그램에선 의도적으로 NULL 포인터에 문자열을 copy하여 Segmentation Fault를 발생시킨다.
*/
 
int main()
{
	int		i;
	double	j;
	char	*bug = NULL;

	for (i = 0 ; i < 5 ; i++) {
		j = i/2 + i;
		printf("j is %lf \n", j );
	}

	strcpy(bug, "hi");
	printf("bug is %s \n", bug);

	return 0;
}