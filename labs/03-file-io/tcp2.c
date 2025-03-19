#include <stdio.h>

#define	MAX_BUF	256

/*
라인 단위로 파일 복사하는 예제
*/

int main(int argc, char *argv[])
{
	FILE	*src, *dst;
	char	buf[MAX_BUF];

	if (argc != 3)  {
		fprintf(stderr, "Usage: %s source destination\n", argv[0]);
		exit(1);
	}

	if ((src = fopen(argv[1], "rt")) == NULL)  {
		perror("fopen");
		exit(1);
	}

	if ((dst = fopen(argv[2], "wt")) == NULL)  {
		perror("fopen");
		exit(1);
	}

	// 라인 단위 I/O 함수 (fgets, fputs)
	while (fgets(buf, MAX_BUF, src) != NULL)  {	// 버퍼 크기 제한, 오버플로우 방지
		fputs(buf, dst);
	}

	fclose(src);
	fclose(dst);

	return 0;
}