#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF 256

int main(int argc, char *argv[]) {
	FILE *fp;
	char buf[MAX_BUF];
	int line;

	if(argc != 2) {
		printf("Usage: %s filename\n", argv[0]);
		exit(1);
	}

	if(!(fp = fopen(argv[1], "rt"))) {
		perror("fopen");
		exit(1);
	}

	line = 1;
	while(fgets(buf, sizeof(buf), fp)) {
		printf("%4d: %s", line++, buf);
	}

	fclose(fp);

	return 0;
}