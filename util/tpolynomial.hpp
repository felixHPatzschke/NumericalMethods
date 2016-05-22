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
#  include <iostream>
#  define _STD_OSTREAM_INCLUDED_ 1
#  include <sstream>
#endif

#include <initializer_list>
#include <vector>
#include "sfinae.hpp"

#if _STD_OSTREAM_INCLUDED_
template <typename _ty>
inline std::ostream& ostream_lshift(std::ostream& ostr, const _ty t, const unsigned int x, const std::true_type&)
{
	if (x == 0 && t < _ty(0))
		ostr << "-";
	if (x != 0)
		ostr << ((t < _ty(0)) ? (" - ") : (" + "));
	return (ostr << ((t < _ty(0)) ? (-t) : (t)));
}

template <typename _ty>
inline std::ostream& ostream_lshift(std::ostream& ostr, const _ty t, const unsigned int x, const std::false_type&)
{
	if (x != 0)
		ostr << " + ";
	return (ostr << t);
}
#endif



template <typename _ty> class Polynomial
{
protected:
	std::vector<_ty> coef;

public:
	/** creates a new empty polynomial */
	inline Polynomial() { coef = std::vector<_ty>(1,0); }
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
	template <typename aux> inline Polynomial(const aux i)
	{
		coef = std::vector<_ty>(1);
		coef[0] = _ty(i);
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

	template <typename aux> inline Polynomial<aux> cast() const
	{
		Polynomial<aux> res = Polynomial<aux>();
		for (unsigned int i = 0; i < coef.size(); ++i)
			res.set_coefficient(i, _ty(this->get_coefficient(i)));
		return res;
	}

	inline Polynomial<_ty>& operator=(const Polynomial<_ty>& other)
	{
		coef.resize(other.coef.size());
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
		coef[0] = _ty(scalar);
		return *this;
	}

	inline Polynomial<_ty> operator-() const
	{
		Polynomial<_ty> res = Polynomial<_ty>();
		for (unsigned int i = 0; i < coef.size(); ++i)
			res[i] = _ty(-1)*coef[i];
		return res;
	}

	inline Polynomial<_ty>& operator+=(const Polynomial<_ty>& other)
	{
		for (unsigned int i = 0; i <= other.coef.size(); ++i)
			this->operator[](i) += other.get_coefficient(i);
		return *this;
	}
	template <typename aux> inline Polynomial<_ty>& operator+=(const aux scalar)
	{
		this->coef[0] += _ty(scalar);
		return *this;
	}

	inline Polynomial<_ty>& operator-=(const Polynomial<_ty>& other)
	{
		for (unsigned int i = 0; i < other.coef.size(); ++i)
			this->operator[](i) -= other.get_coefficient(i);
		return *this;
	}
	template <typename aux> inline Polynomial<_ty>& operator-=(const aux scalar)
	{
		this->coef[0] -= _ty(scalar);
		return *this;
	}

	template <typename aux> inline Polynomial<_ty>& operator*=(const aux scalar)
	{
		for (_ty& x : this->coef)
			x *= _ty(scalar);
		return *this;
	}
	template <typename aux> inline Polynomial<_ty>& operator/=(const aux scalar)
	{
		for (_ty& x : this->coef)
			x /= _ty(scalar);
		return *this;
	}

	inline Polynomial<_ty>& operator*=(const Polynomial<_ty>& other)
	{
		Polynomial<_ty> res = 0;
		Polynomial<_ty> h;
		for (unsigned int i = 0; i < other.coef.size(); ++i)
		{
			h = 0;
			for (unsigned int j = 0; j < this->coef.size(); ++j)
				h[j + i] = this->get_coefficient(j);
			res += (h *= other.get_coefficient(i));
		}
		this->operator=(res);
		return *this;
	}

	inline Polynomial<_ty> operator+(const Polynomial<_ty>& other) const
	{
		Polynomial<_ty> res = *this;
		for (unsigned int i = 0; i < other.coef.size(); ++i)
			this->operator[](i) += other.get_coefficient(i);
		return res;
	}
	template <typename aux> inline Polynomial<_ty> operator+(const aux scalar) const
	{
		Polynomial<_ty> res = *this;
		res[0] += _ty(scalar);
		return res;
	}

	inline Polynomial<_ty> operator-(const Polynomial<_ty>& other) const
	{
		Polynomial<_ty> res = *this;
		for (unsigned int i = 0; i < other.coef.size(); ++i)
			this->operator[](i) += other.get_coefficient(i);
		return res;
	}
	template <typename aux> inline Polynomial<_ty> operator-(const aux scalar) const
	{
		Polynomial<_ty> res = *this;
		res[0] -= _ty(scalar);
		return res;
	}

	template <typename aux> inline Polynomial<_ty> operator*(const aux scalar) const
	{
		Polynomial<_ty> res = *this;
		for (_ty& x : res.coef)
			x *= _ty(scalar);
		return res;
	}
	template <typename aux> inline Polynomial<_ty> operator/(const aux scalar) const
	{
		Polynomial<_ty> res = *this;
		for (_ty& x : res.coef)
			x *= _ty(scalar);
		return res;
	}

	inline Polynomial<_ty> operator*(const Polynomial<_ty>& other) const
	{
		Polynomial<_ty> res = 0;
		Polynomial<_ty> h;
		for (unsigned int i = 0; i < other.coef.size(); ++i)
		{
			h = 0;
			for (unsigned int j = 0; j < this->coef.size(); ++j)
				h[j + i] = this->get_coefficient(j);
			res += (h *= other.get_coefficient(i));
		}
		return res;
	}


	template <typename aux> inline _ty operator()(const aux x) const
	{
		_ty res = _ty(0);
		for(unsigned int i = coef.size()-1; i > 0; --i)
		{
			
			res += coef[i];
			res *= _ty(x);
		}
		res += coef[0];
		return res;
	}
	inline _ty& operator[](const unsigned int i)
	{
		if (i >= coef.size())
			coef.resize(i+1);
		return coef[i];
	}
	inline int degree() const { return coef.size() - 1; }

	inline Polynomial<_ty> derivative(const int n = 1) const
	{
		if (n == 0)
			return Polynomial<_ty>(*this);
		else if (n < 0)
			return integral(-n);
		else if (n > degree())
			return Polynomial<_ty>(_ty(0));
		else if (n == 1)
		{
			Polynomial<_ty> res(0u);
			for (unsigned int i = 1; i < coef.size(); ++i)
			{
				res.set_coefficient(i - 1, coef[i] * _ty(i));
			}
			return res;
		}
		else
			return derivative().derivative(n - 1);
		// TODO: get rid of recursion
	}
	template <typename aux>	inline _ty derivativeAt(const aux x) const
	{
		// TODO: find a more efficient way
		return this->derivative().operator()(x);
	}
	inline Polynomial<_ty> integral(const int n = 1) const
	{
		if (n == 0)
			return Polynomial<_ty>(*this);
		else if (n < 0)
			return derivative(-n);
		else if (n == 1)
		{
			Polynomial<_ty> res(0);
			for (unsigned int i = 0; i < coef.size(); ++i)
				res.set_coefficient(i + 1, coef[i] / _ty(i + 1));
			return res;
		}
		else
			return integral().integral(n - 1);
		// TODO: get rid of recursion
	}
	template <typename aux> inline _ty integrate(const aux a, const aux b) const
	{
		Polynomial<_ty> F = integral();
		return (F(b) - F(a));
	}

	inline _ty get_coefficient(const unsigned int i) const
	{
		if (i < coef.size())
			return coef[i];
		else
			return _ty(0);
	}
	inline Polynomial<_ty> get_monomial(const unsigned int i) const
	{
		Polynomial<_ty> res = 0;
		if (i < coef.size())
			res[i] = coef[i];
		return res;
	}
	template <typename aux> inline Polynomial<_ty>& set_coefficient(const unsigned int i, const aux arg)
	{
		if (i < coef.size())
			coef[i] = _ty(arg);
		else
		{
			coef.resize(i + 1);
			coef[i] = _ty(arg);
		}
		return *this;
	}
	inline std::vector<_ty>& coefficients() { return coef; }

#ifdef _STD_STRING_INCLUDED_
	inline std::string to_string(const char* argn = "x") const
	{
		if (coef.size() == 0)
			return std::string("0");
		std::ostringstream sstr;
		if (coef.size() == 1)
		{
			sstr << coef[0];
			return sstr.str();
		}
		unsigned int x = 0;
		for (int i = (coef.size() - 1); i >= 0; --i)
		{
			if (coef[i] != _ty(0))
			{
				ostream_lshift(sstr, coef[i], x, is_ineq_supported(_ty));
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

	inline Polynomial<_ty>& shrink()
	{
		while (coef[coef.size() - 1] == _ty(0))
			coef.pop_back();
		return *this;
	}

};

#ifdef _STD_OSTREAM_INCLUDED_
template <typename _ty>
inline std::ostream& operator<<(std::ostream& ostr, const Polynomial<_ty>& pol)
{
	if (pol.degree() == -1)
		return ostr << "0";
	if (pol.degree() == 0)
		return ostr << pol.get_coefficient(0);
	unsigned int x = 0;
	for (int i = pol.degree(); i >= 0; --i)
	{
		if (pol.get_coefficient(i) != _ty(0))
		{
			ostream_lshift(ostr, pol.get_coefficient(i), x, is_ineq_supported(_ty));
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


void make_sine(Polynomial<double>* pol, unsigned int order)
{
	pol->operator=(0);
	double f = 1;
	for (unsigned int i = 0; i <= order; ++i)
	{
		if (i > 0)
			f /= i;
		pol->operator[](i) = (i % 2 == 0) ? (0.0) : ((((((i - 1) / 2) % 2) == 0) ? (1) : (-1))*f);
	}
}

void make_cosine(Polynomial<double>* pol, unsigned int order)
{
	pol->operator=(0);
	double f = 1;
	for (unsigned int i = 0; i <= order; ++i)
	{
		if (i > 0)
			f /= i;
		pol->operator[](i) = (i % 2 != 0) ? (0.0) : (((((i / 2) % 2) == 0) ? (1) : (-1))*f);
	}
}

void make_exp(Polynomial<double>* pol, unsigned int order)
{
	pol->operator=(0);
	double f = 1;
	for (unsigned int i = 0; i <= order; ++i)
	{
		if (i > 0)
			f /= i;
		pol->operator[](i) = f;
	}
}


typedef Polynomial<float> polynomialf;
typedef Polynomial<double> polynomiald;
#ifdef _STD_COMPLEX_INCLUDED_
typedef Polynomial<std::complex<double>> polynomialcd;
typedef Polynomial<std::complex<float>> polynomialcf;

template <typename _cbty> inline int has_real_coefficients(const Polynomial<std::complex<_cbty>>& pol)
{
	for (unsigned int i = 0; i <= pol.degree(); ++i)
		if (static_cast<std::complex<_cbty>>(pol.get_coefficient(i)).imag() != _cbty(0))
			return false;
	return true;
}
template <typename _cbty> inline int has_imaginary_coefficients(const Polynomial<std::complex<_cbty>>& pol)
{
	for (unsigned int i = 0; i <= pol.degree(); ++i)
		if (static_cast<std::complex<_cbty>>(pol.get_coefficient(i)).real() != _cbty(0))
			return false;
	return true;
}
#endif
#ifdef _FHP_TCOMPLEX_HPP_INCLUDED_
typedef Polynomial<complexd> polynomialcxd;
typedef Polynomial<complexf> polynomialcxf;

template <typename _cbty> inline int has_real_coefficients(const Polynomial<Complex<_cbty>>& pol)
{
	for (unsigned int i = 0; i <= pol.degree(); ++i)
		if (!(static_cast<Complex<_cbty>>(pol.get_coefficient(i)).is_real()))
			return false;
	return true;
}
template <typename _cbty> inline int has_imaginary_coefficients(const Polynomial<Complex<_cbty>>& pol)
{
	for (unsigned int i = 0; i <= pol.degree(); ++i)
		if (!(static_cast<Complex<_cbty>>(pol.get_coefficient(i)).is_imag()))
			return false;
	return true;
}

#endif

#endif
