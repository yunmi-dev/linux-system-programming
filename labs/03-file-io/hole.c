#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

/*
파일 홀 (Sparce file) 생성하는 프로그램
*/

int main()
{
	int 	fd;
	char	ch = '\0';

	if ((fd = creat("file.hole", 0400)) < 0)  {
		perror("creat");
		exit(1);
	}

	if (lseek(fd, 1023, SEEK_SET) < 0)  {	// 파일 포인터 이동
		perror("lseek");
		exit(1);
	}
	write(fd, &ch, 1);

	close(fd);

	return 0;
}