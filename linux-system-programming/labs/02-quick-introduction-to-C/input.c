#include <stdio.h>

int main() {
	char c ,s[80];
	int i; long l;
	float f; double d;

	scanf("%c %s %d %ld %f %lf", &c, s, &i, &l, &f, &d);
	printf("Output: %c %s %d %ld %.4f %.2lf\n", c, s, i, l, f, d);

	c = getchar();
	putchar(c);

	fgets(s, sizeof(s), stdin);
	puts(s);

	return 0;
}