#include <stdio.h>

#define	MAX_BUF	1024

/*
고수준 파일 복사 (fopen, fread, fwrite, fclose 고수준 파일 I/O 함수)
*/

int main(int argc, char *argv[])
{
	FILE	*src, *dst;
	char	buf[MAX_BUF];
	int		count;

	if (argc != 3)  {
		fprintf(stderr, "Usage: %s source destination\n", argv[0]);
		exit(1);
	}

	// 바이너리 모드로 파일 열기 ("rb", "wb")
	if ((src = fopen(argv[1], "rb")) == NULL)  {
		perror("fopen");
		exit(1);
	}

	if ((dst = fopen(argv[2], "wb")) == NULL)  {
		perror("fopen");
		exit(1);
	}

	while ((count = fread(buf, 1, MAX_BUF, src)) > 0)  {
		fwrite(buf, 1, count, dst);
	}

	// 파일 닫기
	fclose(src);
	fclose(dst);

	return 0;
}