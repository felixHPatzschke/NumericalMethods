#include <cstdlib>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <complex>
#include <vector>

#define ETA (1.0e-10)
#define _ty std::complex<double>
#define x1 (x[i-2])
#define x2 (x[i-1])
#define x3 (x[i])
#define init(a,b,c,d,e,f) x.resize(0);	x.push_back(std::complex<double>(a,b));	x.push_back(std::complex<double>(c,d));	x.push_back(std::complex<double>(e,f))


typedef _ty(*Function)(const _ty&);


_ty _f(const _ty& x)
{
	return (((x - 1.0)*x - 7.0)*x - 65.0);
}

template <typename t> inline int t_sign(t x)
{
	return (x > t(0)) - (x < t(0));
}

int find_root(Function f, std::vector<_ty>& x)
{
	unsigned int i = 2;
	_ty xk;
	_ty y1, y2, y3;
	_ty a, b, c;
	while (abs(f(x[i])) >= ETA)
	{
		y1 = f(x1);
		y2 = f(x2);
		y3 = f(x3);

		a = ((y1 - y3)*(x2 - x3) - (y2 - y3)*(x1 - x3)) / ((x1 - x3)*(x2 - x3)*(x1 - x2));
		b = (y1 - y3) / (x1 - x3) - a*(x1 - x3);
		c = y3;

		xk = x3-(2.0*c / (b + static_cast<_ty>(t_sign(b.real()))*sqrt(b*b - 4.0*a*c)));
		x.push_back(xk);
		++i;
		std::cout << "\r" << (i - 2) << ": " << f(xk) << "\t\t";
	}
	return i-2;
}

int main()
{
	std::cout << std::setprecision(12);
	std::vector<_ty> x = std::vector<_ty>(0);

	int i;

	init(0, 0, 1, 0, 0, -9);
	i = find_root(_f, x);
	std::cout << "\rRoot 1: " << x[x.size() - 1] << " - " << i << " Iterations\t\t\t" << std::endl;
	init(-1, 0, 0, 0, 1, 0);
	i = find_root(_f, x);
	std::cout << "\rRoot 2: " << x[x.size() - 1] << " - " << i << " Iterations\t\t\t" << std::endl;
	init(4, 0, 5, 0, 6, 0);
	i = find_root(_f, x);
	std::cout << "\rRoot 3: " << x[x.size() - 1] << " - " << i << " Iterations\t\t\t" << std::endl;

	std::cout << "\nPress [ENTER] to exit the program.\nIronic,isn't it?" << std::endl;
	std::cin.get();
    return EXIT_SUCCESS;
}
