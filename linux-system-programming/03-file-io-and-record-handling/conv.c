#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"

int main(int argc, char *argv[]) {
	FILE *src, *dst;
	Record rec;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s source dest\n", argv[0]);
		exit(1);
	}

	if(!(src = fopen(argv[1], "rt"))) {
		perror("fopen, src");
		exit(1);
	}

	if(!(dst = fopen(argv[2], "wb"))) {
		perror("fopen, dst");
		exit(1);
	}
	
	while(fgets(rec.stud, SMAX, src)) {
		*strchr(rec.stud, '\n') = '\0';
	
	
		fgets(rec.num, NMAX, src);
		*strchr(rec.num, '\n') = '\0';
		fgets(rec.dept, DMAX, src);
		*strchr(rec.dept, '\n') = '\0';
		
		fwrite(rec.stud, sizeof(rec.stud), 1, dst);
		fwrite(rec.num, sizeof(rec.num), 1, dst);
		fwrite(rec.dept, sizeof(rec.dept), 1, dst);
	}
	
	fclose(src);
	fclose(dst);
	
	return 0;
}