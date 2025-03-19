#include <stdio.h>

/*
문자 단위로 파일 복사하는 예제
*/

int main(int argc, char *argv[])
{
	FILE	*src, *dst;
	int		ch;

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

	// 문자 단위의 I/O 함수 (fgetc, fputc)
	while ((ch = fgetc(src)) != EOF)  {	// EOF = End of File
		fputc(ch, dst);
	}

	fclose(src);
	fclose(dst);

	return 0;
}