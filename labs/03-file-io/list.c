#include <stdio.h>

#define	MAX_BUF	256

/*
행 번호와 함께 파일 내용 출력하는 예제
*/

int main(int argc, char *argv[])
{
	FILE	*fp;
	char	buf[MAX_BUF];
	int		line;

	if (argc != 2)  {
		printf("Usage: %s filename\n", argv[0]);
		exit(1);
	}

	if ((fp = fopen(argv[1], "rt")) == NULL)  {
		perror("fopen");
		exit(1);
	}

	line = 1;
	while (fgets(buf, MAX_BUF, fp))  {
		printf("%4d: %s", line++, buf);
	}

	fclose(fp);

	return 0;
}