#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF 1024

int main(int argc, char *argv[]) {
	FILE *src, *dst;
	char buf[MAX_BUF];
	int cnt;

	if(argc != 3) {
		fprintf(stderr, "Usage: %s source destination\n", argv[0]);
		exit(1);
	}

	if(!(src = fopen(argv[1], "rb"))) {
		perror("fopen");
		exit(1);
	}

	if(!(dst = fopen(argv[2], "wb"))) {
		perror("fopen");
		exit(1);
	}

	while(cnt = fread(buf, sizeof(char), MAX_BUF, src)) {
		fwrite(buf, sizeof(char), cnt, dst);
	}

	fclose(src);
	fclose(dst);

	return 0;
}