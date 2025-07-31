#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

char sign(double x) {
	if (x > 0) return 1;
	if (x < 0) return -1;
	return 0;
}

double f(double a, double b, double c, double x) {
	return a * x * x + b * x + c;
}
double df(double a, double b, double x) {
	return 2 * a * x + b;
}
double extremum(double a, double b) {
		return -b / (2 * a);
}

class equation {
protected:
	double a, b, c;
	std::vector<double> roots;
public:
	virtual void solve(void) = 0;
	void print_roots(void) {
		if (!roots.size()) std::cout << "Roots not found" << std::endl;
		for(auto& v: roots) std::cout << v << std::endl;
	};
};

class linear : public equation {
	friend linear* create_linear(double, double, double);
public:
	virtual void solve(void) { roots.push_back( -c / b ); };
};

class square : public equation {
	friend square* create_square(double, double, double);
private:
	double extremum;
	double f(double x) { return ::f(a, b, c, x); };
	double df(double x) { return ::df(a, b, x); };
	double f_div_df(double x) { return f(x) / df(x); };
	double find_rigth_root(void) {
		double x = extremum + 1;
		do 
			x -= f_div_df(x);
		while (f(x) != 0);
		return x;
	};
public:
	virtual void solve(void) {
		roots.push_back( find_rigth_root() );
		roots.push_back( 2 * extremum - roots[0] );
	};
};

class square_one_root : public equation {
	friend square_one_root* create_square_one_root(double, double, double);
private:
	double extremum;
public:
	virtual void solve(void) { roots.push_back(extremum); };
};

class no_roots :public equation {
	friend no_roots* create_no_roots(double, double, double);
public:
	virtual void solve(void) { ; };
};

linear* create_linear(double a, double b, double c) {
	linear *eq = new linear();
	eq->a = a;
	eq->b = b;
	eq->c = c;
	return eq;
}

square* create_square(double a, double b, double c) {
	square *eq = new square();
	eq->a = a;
	eq->b = b;
	eq->c = c;
	eq->extremum = extremum(a, b);
	return eq;
}

square_one_root* create_square_one_root(double a, double b, double c) {
	square_one_root *eq = new square_one_root();
	eq->a = a;
	eq->b = b;
	eq->c = c;
	eq->extremum = extremum(a, b);
	return eq;
}

no_roots* create_no_roots(double a, double b, double c) {
	return new no_roots();
}

equation* create_equation(double a, double b, double c) {
	if ((a == 0) && (b != 0)) return create_linear(a, b, c);

	double e = extremum(a, b);
	if (f(a, b, c, e) == 0) return create_square_one_root(a, b, c);
	if (sign(f(a, b, c, e)) * sign(df(a, b, e - 1)) > 0) return create_square(a, b, c);

	return create_no_roots(a, b, c);
}

int main() {
	double a = 0, b = 0, c = 0;
	equation *eq = NULL;

	std::cin >> a >> b >> c;

	eq = create_equation(a, b, c);
	eq->solve();
	eq->print_roots();

	delete eq;

	return 0;
}