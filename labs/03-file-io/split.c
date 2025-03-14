#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_BUF 1024

long filesize(FILE *fp) {
	long cur, size;

	cur = ftell(fp);
	fseek(fp, 0L, SEEK_END);
	size = ftell(fp);
	fseek(fp, cur, SEEK_SET);
	return size;
}

int main(int argc, char *argv[]) {
	FILE *src, *dst1, *dst2;
	char buf[MAX_BUF];
	int cnt, size;

	if(argc != 4) {
		fprintf(stderr, "Usage: %s source dest1 dest2\n", argv[0]);
		exit(1);
	}

	if(!(src = fopen(argv[1], "rb"))) {
		perror("fopen, src");
		exit(1);
	}

	if(!(dst1 = fopen(argv[2], "wb"))) {
		perror("fopen, dst1");
		exit(1);
	}

	if(!(dst2 = fopen(argv[3], "wb"))) {
		perror("fopen, dst2");
		exit(1);
	}

	size = filesize(src) / 2;

	while(size > 0) {
		cnt = (size > MAX_BUF) ? MAX_BUF : size;
		fread(buf, sizeof(char), cnt, src);
		fwrite(buf, sizeof(char), cnt, dst1);
		size -= cnt;
	}

	while((cnt = fread(buf, sizeof(char), MAX_BUF, src)) > 0) {
		fwrite(buf, sizeof(char), cnt, dst2);
	}

	fclose(src);
	fclose(dst1);
	fclose(dst2);

	return 0;
}