#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_BUF 1024

int main(int argc, char *argv[]) {
	FILE *fp;

	int ch;

	if(argc != 2) {
		printf("Usage:%s filename\n", argv[0]);
		exit(1);
	}

	if(!(fp = fopen(argv[1], "rt"))) {
		perror("fopen");
		exit(1);
	}

	while((ch = fgetc(fp)) != EOF) {
		putchar(toupper(ch));
	}

	fclose(fp);

	return 0;
}