#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	double a = 0, b = 0, c = 0;
	int number_of_roots = -1;
	double *x = NULL;

	scanf("%lg %lg %lg", &a, &b, &c);

	if (a == 0) {
		if (b != 0) {
			number_of_roots = 1;
			x = malloc( number_of_roots * sizeof(double) );
		} else {
			number_of_roots = 0;
		}
	}

	double D = b * b - 4 * a * c;

	if (D > 0) {
		number_of_roots = 2;
		x = malloc( number_of_roots * sizeof(double) );
		x[0] = (-b - sqrt(D)) / (2 * a);
		x[1] = (-b + sqrt(D)) / (2 * a);
	} else if ( D < 0 ) {
		number_of_roots = 0;
	} else {
		number_of_roots = 1;
		x = malloc( number_of_roots * sizeof(double) );
		x[0] = -b / (2 * a);
	}

	for(int i = 0; i < number_of_roots; ++i) {
		printf("x[%d] = %lg; ", i + 1, x[i]);
	}

	if (!number_of_roots) puts("Roots not foud");
	if (x) free(x);
	return 0;
}