#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF 1024

int main(int argc, char *argv[]) {
	FILE *src1, *src2, *dst;
	char buf[MAX_BUF];
	int cnt;

	if(argc != 4) {
		fprintf(stderr, "Usage: %s source1 source2 dest\n", argv[0]);
		exit(1);
	}

	if(!(src1 = fopen(argv[1], "rb"))) {
		perror("fopen, src1");
		exit(1);
	}

	if(!(src2 = fopen(argv[2], "rb"))) {
		perror("fopen, src2");
		exit(1);
	}

	if(!(dst = fopen(argv[3], "wb"))) {
		perror("fopen, dst");
		exit(1);
	}

	while(cnt = fread(buf, sizeof(char), MAX_BUF, src1)) {
		fwrite(buf, sizeof(char), cnt, dst);
	}

	while(cnt = fread(buf, sizeof(char), MAX_BUF, src2)) {
		fwrite(buf, sizeof(char), cnt, dst);
	}

	fclose(src1);
	fclose(src2);
	fclose(dst);

	return 0;
}