#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *src, *dst;
	int ch;

	if(argc != 3) {
		fprintf(stderr, "Usage: %s source destination\n", argv[0]);
		exit(1);
	}

	if(!(src = fopen(argv[1], "rt"))) {
		perror("fopen");
		exit(1);
	}

	if(!(dst = fopen(argv[2], "wt"))) {
		perror("fopen");
		exit(1);
	}

	while((ch = fgetc(src)) > 0) {
		fputc(ch, dst);
	}

	fclose(src);
	fclose(dst);

	return 0;
}