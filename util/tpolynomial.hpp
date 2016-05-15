#ifndef _FHP_TPOLYNOMIAL_HPP_INCLUDED_
#define _FHP_TPOLYNOMIAL_HPP_INCLUDED_

#if defined(_MSC_VER)
#  ifdef _OSTREAM_
#    define _STD_OSTREAM_INCLUDED_ 1
#  endif
#  ifdef _STRING_
#    define _STD_STRING_INCLUDED_ 1
#  endif
#  ifdef _COMPLEX_
#    define _STD_COMPLEX_INCLUDED_ 1
#  endif
#elif defined(__GNUC__) || defined(__clang__)
#  include <iostream>
#  include <string>
#  include <complex>
#  define _STD_OSTREAM_INCLUDED_ 1
#  define _STD_STRING_INCLUDED_ 1
#  define _STD_COMPLEX_INCLUDED_ 1
#endif
#ifdef _STD_STRING_INCLUDED_
#  include <sstream>
#endif

#include <initializer_list>
#include <vector>


template <typename _ty> class Polynomial
{
protected:
	std::vector<_ty> coef;

public:
	/** creates a new empty polynomial */
	inline Polynomial() { coef = std::vector<_ty>(0); }
	/** creates a new polynomial with given coefficients */
	template <typename aux> inline Polynomial(std::initializer_list<aux> list)
	{
		coef = std::vector<_ty>(0);
		for (aux x : list)
			coef.push_back(_ty(x));
	}
	/** creates a new polynomial of i-th degree, and inserts a leading coefficient */
	inline Polynomial(const unsigned int i, const _ty leading)
	{
		coef = std::vector<_ty>(i + 1);
		coef[i] = leading;
	}
	/** creates a new 0th degree polynomial, and inserts a coefficient as the constant value */
	inline Polynomial(const _ty i)
	{
		coef = std::vector<_ty>(1);
		coef[0] = i;
	}
	/** copy constructor */
	inline Polynomial(const Polynomial<_ty>& other)
	{
		coef = std::vector<_ty>(other.coef.size());
		for (unsigned int i = 0; i < coef.size(); ++i)
			coef[i] = other.coef[i];
	}
	/** destructor */
	inline ~Polynomial() {}

	inline Polynomial<_ty>& operator=(const Polynomial<_ty>& other)
	{
		coef.resize(other.coef.size())
			for (unsigned int i = 0; i < coef.size(); ++i)
				coef[i] = other.coef[i];
		return *this;
	}
	template <typename aux> inline Polynomial<_ty>& operator=(std::initializer_list<aux> list)
	{
		coef.resize(0);
		for (aux x : list)
			coef.push_back(_ty(x));
		return *this;
	}
	template <typename aux> inline Polynomial<_ty>& operator=(const aux scalar)
	{
		coef.resize(1);
		coef[0] = scalar;
	}

	inline Polynomial<_ty> operator-() const
	{
		Polynomial<_ty> res = Polynomial(coef.size() - 1);
		for (unsigned int i = 0; i < coef.size(); ++i)
			res.coef[i] = _ty(-1)*coef[i];
		return res;
	}

	inline Polynomial<_ty>& operator+=(const Polynomial<_ty>& other);
	inline Polynomial<_ty>& operator+=(const _ty scalar);

	inline Polynomial<_ty>& operator-=(const Polynomial<_ty>& other);
	inline Polynomial<_ty>& operator-=(const _ty scalar);

	inline Polynomial<_ty>& operator*=(const _ty scalar);
	inline Polynomial<_ty>& operator/=(const _ty scalar);

	inline Polynomial<_ty>& operator*=(const Polynomial<_ty>& other);

	inline Polynomial<_ty> operator+(const Polynomial<_ty>& other) const;
	inline Polynomial<_ty> operator+(const _ty scalar) const;

	inline Polynomial<_ty> operator-(const Polynomial<_ty>& other) const;
	inline Polynomial<_ty> operator-(const _ty scalar) const;

	inline Polynomial<_ty> operator*(const _ty scalar) const;
	inline Polynomial<_ty> operator/(const _ty scalar) const;

	inline Polynomial<_ty> operator*(const Polynomial<_ty>& other) const;


	inline _ty operator()(const _ty x) const
	{
		_ty res = 0.0;
		_ty x_pow = _ty(1);
		for (unsigned int i = 0; i < coef.size(); ++i)
		{
			if (coef[i] != _ty(0))
			{
				_ty q = coef[i] * x_pow;
				res += q;
			}
			x_pow *= x;
		}
		return res;
	}
	inline Polynomial<_ty> operator[](const unsigned int i) const
	{
		Polynomial<_ty> res = Polynomial<_ty>(i);
		res.coef[i] = this->get_coefficient(i);
		return res;
	}
	inline int degree() const { return coef.size() - 1; }

	inline Polynomial<_ty> derivative(const int n = 1) const;
	inline _ty derivativeAt(const _ty x) const;
	inline Polynomial<_ty> integral(const int n = 1) const;
	inline _ty integrate(const _ty a, const _ty b) const;

	inline _ty get_coefficient(const unsigned int i) const
	{
		if (i < coef.size())
			return coef[i];
		else
			return _ty(0);
	}
	inline Polynomial<_ty>& set_coefficient(const unsigned int i, const _ty arg)
	{
		if (i < coef.size())
			coef[i] = arg;
		else
		{
			coef.resize(i + 1);
			coef[i] = arg;
		}
	}
	inline std::vector<_ty>& coefficients() { return coef; }

#ifdef _STD_STRING_INCLUDED_
	inline std::string to_string(const char* argn = "x") const
	{
		if (coef.size() == 0)
			return std::string("0");
		std::stringstream sstr;
		unsigned int x = 0;
		for (int i = (coef.size() - 1); i >= 0; --i)
		{
			if (coef[i] != _ty(0))
			{
				if (x == 0 && coef[i] < _ty(0))
					sstr << "-";
				if (x != 0)
					sstr << ((coef[i] > _ty(0)) ? (" + ") : (" - "));
				sstr << ((coef[i] > _ty(0)) ? (coef[i]) : (-(coef[i])));
				if (i != 0)
					sstr << argn;
				if (i >= 2)
					sstr << "^" << i;
				++x;
			}
		}
		return sstr.str();
	}
#endif

};

#ifdef _STD_OSTREAM_INCLUDED_
template <typename _ty>
inline std::ostream& operator<<(std::ostream& ostr, const Polynomial<_ty>& pol)
{
	if (pol.degree() == -1)
		return ostr << "0";
	unsigned int x = 0;
	for (int i = pol.degree(); i >= 0; --i)
	{
		if (pol.get_coefficient(i) != _ty(0))
		{
			if (x == 0 && pol.get_coefficient(i) < _ty(0))
				ostr << "-";
			if (x != 0)
				ostr << ((pol.get_coefficient(i) > _ty(0)) ? (" + ") : (" - "));
			ostr << ((pol.get_coefficient(i) > _ty(0)) ? (pol.get_coefficient(i)) : (-(pol.get_coefficient(i))));
			if (i != 0)
				ostr << "x";
			if (i >= 2)
				ostr << "^" << i;
			++x;
		}
	}
	return ostr;
}
#endif

template <typename _ty>
inline Polynomial<_ty> Polynomial<_ty>::derivative(const int n) const
{
	if (n == 0)
		return Polynomial<_ty>(*this)
	else if (n < 0)
		return integral(-n);
	else if (n > degree())
		return Polynomial<_ty>(_ty(0));
	else if (n == 1)
	{
		Polynomial<_ty> res(0u);
		for (unsigned int i = 1; i < coef.size(); ++i)
		{
			res.set_coefficient(i - 1, coef[i] * i);
		}
		return res;
	}
	else
		return derivative().derivative(n - 1);
	// TODO: get rid of recursion
}



typedef Polynomial<float> polynomialf;
typedef Polynomial<double> polynomiald;
#ifdef _STD_COMPLEX_INCLUDED_
typedef Polynomial<std::complex> polynomialc;
#endif

#endif
