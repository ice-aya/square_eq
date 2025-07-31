#include <math.h>
#include <stdio.h>
#include <stdlib.h>

const double eps = 1.0 - 0.2 - 0.2 - 0.2 - 0.2 - 0.2;

typedef int (*solver)(double, double, double, double **);

char eq(double a, double b) {
	return ( (a > (b - eps)) && (a < (b + eps)) );
}

char ne(double a, double b) {
	return !eq(a, b);
}

void print_array(double *x, int N) {
	for(int i = 0; i < N; ++i) {
		printf("x[%d] = %lg; ", i + 1, x[i]);
	}
}

void print_roots(double *x, int number_of_roots) {
	if (number_of_roots) print_array(x, number_of_roots);
	else 								 puts("Roots not foud");
}

int linear_eq(double a, double b, double c, double **x) {
	if (ne(b, 0.)) {
		*x = (double *) malloc( sizeof(double) );
		**x = -c / b;
		return 1;
	}
	return 0;
}

int square_eq(double a, double b, double c, double **x) {
	double D = b * b - 4 * a * c;
	
	if (D < 0) return 0;

	double term1 = -b / (2 * a);
	if (D > 0) {
		*x = (double *) malloc( 2 * sizeof(double) );
		double term2 = sqrt(D) / (2 * a);
		for (int i = 0; i < 2; ++i) {
			*(*x + i) = term1 + pow(-1, i) * term2;
		}
		return 2;
	}

	*x = (double *) malloc( sizeof(double) );
	**x = term1;
	return 1;
}

int main() {
	double a = 0, b = 0, c = 0;
	int number_of_roots = -1;
	double *x = NULL;
	solver solve = linear_eq;

	scanf("%lg %lg %lg", &a, &b, &c);

	if (ne(a, 0.)) solve = square_eq;
	number_of_roots = solve(a, b, c, &x);

	print_roots(x, number_of_roots);

	if (x) free(x);
	return 0;
}

//  a  b   c x1  x2
//  2 -1 -15  3  -2.5
//  1 -6   9  3   -
//  3  1   2  -   -
// -1  1   0  0   1
//  3  0 -27  3  -3
//  5  0   0  0   -