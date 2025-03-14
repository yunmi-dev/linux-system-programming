#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void conv(char *fname) {
	FILE *src, *dst;
	char fdest[40];
	int ch, first;

	if(!(src = fopen(fname, "rt"))) {
		perror("fopen, src");
		return;
	}

	strcpy(fdest, fname);
	strcat(fdest, ".t");
	if(!(dst = fopen(fdest, "wt"))) {
		perror("fopen, dst");
		return;
	}

	first = true;
	while((ch = fgetc(src)) != EOF) {
		if(first && ch == '\t') {
			fputc(' ', dst);
			fputc(' ', dst);
			fputc(' ', dst);
			fputc(' ', dst);
		}
		else {
			fputc(ch, dst);
			if(first) {
				first = false;
			}
			if(ch == '\n') {
				first = true;
			}
		}
	}

	fclose(src);
	fclose(dst);
}

int main(int argc, char *argv[]) {
	while(--argc) {
		conv(argv[argc]);
	}

	return 0;
}