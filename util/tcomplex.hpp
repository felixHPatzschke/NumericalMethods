#ifndef _FHP_TCOMPLEX_HPP_INCLUDED_
#define _FHP_TCOMPLEX_HPP_INCLUDED_

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
#include <cmath>

enum class complex_representation : unsigned int { arithmetic = 1u, polar = 2u };
#define CXREP complex_representation
#define CXARITHMETIC complex_representation::arithmetic
#define CXPOLAR complex_representation::polar
enum complex_attribute { none = 0, real = 1, imaginary = 2, absolute_value = 4, argument = 8 };
#define CXATTRIB complex_attribute
#define CXNONE complex_attribute::none
#define CXREAL complex_attribute::real
#define CXIMAG complex_attribute::imaginary
#define CXABS complex_attribute::absolute_value
#define CXARG complex_attribute::argument


template <typename _ty> class Complex
{
protected:
	/// components
	_ty re, im;

public:
	typedef _ty value_type;
	/// constructor
	/** default constructor */
	inline Complex()
	{
		re = _ty(0);
		im = _ty(0);
	}
	/** constructor from base types */
	inline Complex(const _ty x, const _ty y = _ty(0), const CXREP representation = CXARITHMETIC)
	{
		if (representation == CXARITHMETIC)
		{
			re = x;
			im = y;
		}
		else
		{
			re = x * cos(y);
			im = x * sin(y);
		}
	}
	/** constructor from initializer_list */
	template <typename aux> inline Complex(std::initializer_list<aux> list)
	{
		re = static_cast<_ty>(*(list.begin()));
		im = static_cast<_ty>(*(list.begin() + 1));
	}
	/** copy constructor */
	inline Complex(const Complex<_ty>& other)
	{
		re = other.re;
		im = other.im;
	}
#ifdef _STD_COMPLEX_INCLUDED_
	/** constructor from std::complex */
	inline Complex(const std::complex<_ty>& stdc)
	{
		re = stdc.real();
		im = stdc.imag();
	}
#endif
	/** destructor */
	inline ~Complex() {  }

#ifdef _STD_COMPLEX_INCLUDED_
	/** casts a Complex to a std::complex */
	inline operator std::complex<_ty>() const
	{
		return std::complex<_ty>(re, im);
	}
#endif
	/** casts between base data types */
	template <typename aux> inline Complex<aux> cast() const
	{
		return Complex<aux>(static_cast<aux>(re), static_cast<aux>(im), CXARITHMETIC);
	}

	/// direct assignment operators
	/** Assignment operator */
	inline Complex<_ty>& operator=(const Complex<_ty>& other)
	{
		this->re = other.re;
		this->im = other.im;
		return *this;
	}
	/** Assignment operator (initializer_list) */
	template <typename aux> inline Complex<_ty>& operator=(std::initializer_list<aux> list)
	{
		re = static_cast<_ty>(*(list.begin()));
		im = static_cast<_ty>(*(list.begin() + 1));
		return *this;
	}
	/** Assignment operator (real number) */
	inline Complex<_ty>& operator=(const _ty x)
	{
		this->re = x;
		this->im = _ty(0);
		return *this;
	}
#ifdef _STD_COMPLEX_INCLUDED_
	/** Assignment operator (std::complex) */
	inline Complex<_ty>& operator=(const std::complex<_ty>& stdc)
	{
		re = stdc.real();
		im = stdc.imag();
		return *this;
	}
#endif

	/// indirect assignment operators
	inline Complex<_ty>& operator+=(const Complex<_ty>& other)
	{
		re += other.re;
		im += other.im;
		return *this;
	}
	template <typename aux> inline Complex<_ty>& operator+=(std::initializer_list<aux> list)
	{
		re += static_cast<_ty>(*(list.begin()));
		im += static_cast<_ty>(*(list.begin() + 1));
		return *this;
	}
	template <typename aux> inline Complex<_ty>& operator+=(const aux x)
	{
		re += static_cast<_ty>(x);
		return *this;
	}
#ifdef _STD_COMPLEX_INCLUDED_
	inline Complex<_ty>& operator+=(const std::complex<_ty>& stdc)
	{
		re += stdc.real();
		im += stdc.imag();
		return *this;
	}
#endif
	inline Complex<_ty>& operator-=(const Complex<_ty>& other)
	{
		re -= other.re;
		im -= other.im;
		return *this;
	}
	template <typename aux> inline Complex<_ty>& operator-=(std::initializer_list<aux> list)
	{
		re -= static_cast<_ty>(*(list.begin()));
		im -= static_cast<_ty>(*(list.begin() + 1));
		return *this;
	}
	template <typename aux> inline Complex<_ty>& operator-=(const aux x)
	{
		re -= static_cast<_ty>(x);
		return *this;
	}
#ifdef _STD_COMPLEX_INCLUDED_
	inline Complex<_ty>& operator-=(const std::complex<_ty>& stdc)
	{
		re -= stdc.real();
		im -= stdc.imag();
		return *this;
	}
#endif
	inline Complex<_ty>& operator*=(const Complex<_ty>& other)
	{
		_ty _re = (this->re*other.re) - (this->im*other.im);
		_ty _im = (this->re*other.im) + (this->im*other.re);
		this->re = _re;
		this->im = _im;
		return *this;
	}
	template <typename aux> inline Complex<_ty>& operator*=(std::initializer_list<aux> list)
	{
		_ty _re = (this->re * static_cast<_ty>(*(list.begin()))) - (this->im * static_cast<_ty>(*(list.begin()+1)));
		_ty _im = (this->re * static_cast<_ty>(*(list.begin()+1))) + (this->im * static_cast<_ty>(*(list.begin())));
		this->re = _re;
		this->im = _im;
		return *this;
	}
	template <typename aux> inline Complex<_ty>& operator*=(const aux x)
	{
		re *= static_cast<_ty>(x);
		im *= static_cast<_ty>(x);
		return *this;
	}
#ifdef _STD_COMPLEX_INCLUDED_
	inline Complex<_ty>& operator*=(const std::complex<_ty>& stdc)
	{
		_ty _re = (this->re*stdc.real()) - (this->im*stdc.imag());
		_ty _im = (this->re*stdc.imag()) + (this->im*stdc.real());
		this->re = _re;
		this->im = _im;
		return *this;
	}
#endif
	inline Complex<_ty>& operator/=(const Complex<_ty>& other)
	{
		_ty a = this->re, b = this->im;
		this->re = (a*(other.re) + b*(other.im)) / ((other.re)*(other.re) + (other.im)*(other.im));
		this->im = (b*(other.re) - a*(other.im)) / ((other.re)*(other.re) + (other.im)*(other.im));
		return *this;
	}
	template <typename aux> inline Complex<_ty>& operator/=(std::initializer_list<aux> list)
	{
		_ty a = this->re, b = this->im, c = static_cast<_ty>(*(list.begin())), d = static_cast<_ty>(*(list.begin() + 1));
		this->re = (a*c + b*d) / (c*c + d*d);
		this->im = (b*c - a*d) / (c*c + d*d);
		return *this;
	}
	template <typename aux> inline Complex<_ty>& operator/=(const aux x)
	{
		re /= static_cast<_ty>(x);
		im /= static_cast<_ty>(x);
		return *this;
	}
#ifdef _STD_COMPLEX_INCLUDED_
	inline Complex<_ty>& operator/=(const std::complex<_ty>& stdc)
	{
		_ty a = this->re, b = this->im;
		this->re = (a*(stdc.real()) + b*(stdc.imag())) / ((stdc.real())*(stdc.real()) + (stdc.imag())*(stdc.imag()));
		this->im = (b*(stdc.real()) - a*(stdc.imag())) / ((stdc.real())*(stdc.real()) + (stdc.imag())*(stdc.imag()));
		return *this;
	}
#endif

	/** Comparison */
	inline int operator==(const Complex<_ty>& other) const
	{
		return ((re == other.re) && (im == other.im));
	}
	/** Comparison */
	inline int operator!=(const Complex<_ty>& other) const
	{
		return ((re != other.re) || (im != other.im));
	}
	/** Comparison of real part */
	template <typename aux> inline int operator==(const aux arg) const
	{
		return ((re == static_cast<_ty>(arg)) && (im == _ty(0)));
	}
	/** Comparison of real part */
	template <typename aux> inline int operator!=(const aux arg) const
	{
		return ((re != static_cast<_ty>(arg)) || (im != _ty(0)));
	}
#ifdef _STD_COMPLEX_INCLUDED_
	/** Comparison with std::complex */
	inline int operator==(const std::complex<_ty>& stdc) const
	{
		return ((re == stdc.real()) && (im == stdc.imag()));
	}
	/** Comparison with std::complex */
	inline int operator!=(const std::complex<_ty>& stdc) const
	{
		return ((re != stdc.real()) || (im != stdc.imag()));
	}
#endif

	/** Negative */
	inline Complex<_ty> operator-() const
	{
		return Complex<_ty>(-re, -im);
	}
#ifdef _FHP_OVERLOAD_LOGICAL_NOT_OPERATOR_BY_COMPLEX_CONJUGATE_
	/** Complex conjugate */
	inline Complex<_ty> operator!() const
	{
		return Complex<_ty>(re, -im);
	}
#endif

	inline Complex<_ty> operator+(const Complex<_ty>& other) const
	{
		return Complex<_ty>(this->re + other.re, this->im + other.im, CXARITHMETIC);
	}
	template <typename aux> inline Complex<_ty> operator+(const aux x) const
	{
		return Complex<_ty>(this->re + static_cast<_ty>(x), this->im, CXARITHMETIC);
	}
#ifdef _STD_COMPLEX_INCLUDED_
	inline Complex<_ty> operator+(const std::complex<_ty>& stdc) const
	{
		return Complex<_ty>(re + stdc.real(), im + stdc.imag(), CXARITHMETIC);
	}
#endif
	inline Complex<_ty> operator-(const Complex<_ty>& other) const
	{
		return Complex<_ty>(this->re - other.re, this->im - other.im, CXARITHMETIC);
	}
	template <typename aux> inline Complex<_ty> operator-(const aux x) const
	{
		return Complex<_ty>(this->re - static_cast<_ty>(x), this->im, CXARITHMETIC);
	}
#ifdef _STD_COMPLEX_INCLUDED_
	inline Complex<_ty> operator-(const std::complex<_ty>& stdc) const
	{
		return Complex<_ty>(re - stdc.real(), im - stdc.imag(), CXARITHMETIC);
	}
#endif
	inline Complex<_ty> operator*(const Complex<_ty>& other) const
	{
		return Complex<_ty>(re * other.re - im * other.im, re * other.im + im * other.re, CXARITHMETIC);
	}
	template <typename aux> inline Complex<_ty> operator*(const aux x) const
	{
		return Complex<_ty>(static_cast<_ty>(x)*re, static_cast<_ty>(x)*im, CXARITHMETIC);
	}
#ifdef _STD_COMPLEX_INCLUDED_
	inline Complex<_ty> operator*(const std::complex<_ty>& stdc) const
	{
		return Complex<_ty>(re*stdc.real() - im*stdc.imag(), im*stdc.real() + re*stdc.imag(), CXARITHMETIC);
	}
#endif
	inline Complex<_ty> operator/(const Complex<_ty>& other) const
	{
		return Complex<_ty>(
			(re*(other.re) + im*(other.im)) / ((other.re)*(other.re) + (other.im)*(other.im)),
			(im*(other.re) - re*(other.im)) / ((other.re)*(other.re) + (other.im)*(other.im)),
			CXARITHMETIC);
	}
	template <typename aux> inline Complex<_ty> operator/(const aux x) const
	{
		return Complex<_ty>(re / static_cast<_ty>(x), im / static_cast<_ty>(x));
	}
#ifdef _STD_COMPLEX_INCLUDED_
	inline Complex<_ty> operator/(const std::complex<_ty>& stdc) const
	{
		return Complex<_ty>(
			(re*(stdc.real()) + im*(stdc.imag())) / ((stdc.real())*(stdc.real()) + (stdc.imag())*(stdc.imag())),
			(im*(stdc.real()) - re*(stdc.imag())) / ((stdc.real())*(stdc.real()) + (stdc.imag())*(stdc.imag())),
			CXARITHMETIC);
	}
#endif

	/// other operations
	/** Square of the complex number */
	inline Complex<_ty> sqr() const
	{
		return Complex<_ty>(re*re - im*im, _ty(2)*re*im);
	}
	/** The complex number, raised to the power of the argument */
	inline Complex<_ty> pow(const _ty x) const
	{
		return Complex<_ty>(::pow(abs(), x), arg()*x, CXPOLAR);
	}
	/** Square root of the complx number */
	inline Complex<_ty> sqrt() const
	{
		return Complex<_ty>(::sqrt(abs()), arg() / 2, CXPOLAR);
	}
	/** x-th root of the complx number */
	inline Complex<_ty> root(const _ty x) const
	{
		return Complex<_ty>(::pow(abs(), 1 / x), arg() / x, CXPOLAR);
	}

	/// direct access
	/** returns the real part */
	inline _ty real() const
	{
		return re;
	}
	/** returns the imaginary part */
	inline _ty imag() const
	{
		return im;
	}
	/** converts the complex number to an array */
	inline _ty* get(const CXREP representation = CXARITHMETIC)
	{
		_ty res[2];
		if (representation == CXARITHMETIC)
		{
			res[0] = re;
			res[1] = im;
		}
		else
		{
			res[0] = ::sqrt(re*re + im*im);
			res[1] = ::atan2(im, re);
		}
		return res;
	}
	/** manipulates the real part */
	inline Complex<_ty>& set_real(const _ty x)
	{
		re = x;
		return *this;
	}
	/** manipulates the imaginary part */
	inline Complex<_ty>& set_imag(const _ty y)
	{
		im = y;
		return *this;
	}
	/** manipulates the components directly */
	inline Complex<_ty>& set(const _ty x, const _ty y, const CXREP representation = CXARITHMETIC)
	{
		if (representation == CXARITHMETIC)
		{
			re = x;
			im = y;
		}
		else
		{
			re = x * cos(y);
			im = x * sin(y);
		}
		return *this;
	}

	/** absolute value */
	inline _ty abs() const
	{
		return ::sqrt(re*re + im*im);
	}
	/** complex argument */
	inline _ty arg() const
	{
		return ::atan2(im, re);
	}
	/** square of the absolute value */
	inline _ty norm() const
	{
		return (re*re + im*im);
	}
	/** complex conjugate */
	inline Complex<_ty> conj() const
	{
		return Complex<_ty>(re, -im);
	}

	/** returns true if the imaginary part is zero */
	inline int is_real() const
	{
		return (im == _ty(0));
	}
	/** returns true if the real part is zero */
	inline int is_imag() const
	{
		return (re == _ty(0));
	}

#ifdef _STD_STRING_INCLUDED_
	/** returns a string representation of the complex number */
	inline std::string to_string(CXREP rep = CXARITHMETIC) const
	{
		std::stringstream sstr;
		if (rep == CXARITHMETIC)
		{
			sstr << re;
			((im >= _ty(0)) ? (sstr << "+" << im) : (sstr << "-" << -im));
			sstr << "i";
		}
		else
		{
			sstr << abs() << "*e^(" << arg() << ")";
		}
		return sstr.str();
	}
#endif


};
/// arithmetic operators, with the primitive data type as first operand
template <typename _ty> inline Complex<_ty> operator+(const _ty a, const Complex<_ty>& z)
{
	return Complex<_ty>(a + z.real(), z.imag(), CXARITHMETIC);
}
template <typename _ty> inline Complex<_ty> operator-(const _ty a, const Complex<_ty>& z)
{
	return Complex<_ty>(a - z.real(), -z.imag(), CXARITHMETIC);
}
template <typename _ty> inline Complex<_ty> operator*(const _ty a, const Complex<_ty>& z)
{
	return Complex<_ty>(a*z.real(), a*z.imag(), CXARITHMETIC);
}
template <typename _ty> inline Complex<_ty> operator/(const _ty a, const Complex<_ty>& z)
{
	Complex<_ty> res(a, _ty(0));
	res /= z;
	return res;
}

template <typename _ty> inline _ty abs(const Complex<_ty>& z)
{
	return ::sqrt(z.real()*z.real() + z.imag()*z.imag());
}
template <typename _ty> inline _ty arg(const Complex<_ty>& z)
{
	return ::atan2(z.imag(), z.real());
}
template <typename _ty> inline _ty norm(const Complex<_ty>& z)
{
	return z.real()*z.real() + z.imag()*z.imag();
}
template <typename _ty> inline _ty _real(const Complex<_ty>& z)
{
	return z.real();
}
template <typename _ty> inline _ty _imag(const Complex<_ty>& z)
{
	return z.imag();
}
template <typename _ty> inline Complex<_ty> pow(const Complex<_ty>& z, const _ty x)
{
	return Complex<_ty>(::pow(abs(z), x), arg(z)*x, CXPOLAR);
}
template <typename _ty> inline Complex<_ty> sqr(const Complex<_ty>& z)
{
	return Complex<_ty>(z.real()*z.real() - z.imag()*z.imag(), 2 * z.real()*z.imag(), CXARITHMETIC);
}
template <typename _ty> inline Complex<_ty> root(const Complex<_ty>& z, const _ty x)
{
	return Complex<_ty>(::pow(abs(z), 1.0/x), arg(z)/x, CXPOLAR);
}
template <typename _ty> inline Complex<_ty> sqrt(const Complex<_ty>& z)
{
	return Complex<_ty>(::sqrt(abs(z)), arg(z) / 2, CXPOLAR);
}
template <typename _ty> inline int is_real(const Complex<_ty>& z)
{
	return (z.imag() == _ty(0));
}
template <typename _ty> inline int is_imag(const Complex<_ty>& z)
{
	return (z.real() == _ty(0));
}
template <typename _ty> inline Complex<_ty> exp(const Complex<_ty>& z)
{
	return Complex<_ty>(exp(z.real()), z.imag(), CXPOLAR);
}
template <typename _ty> inline Complex<_ty> conj(const Complex<_ty>& z)
{
	return Complex<_ty>(z.real(), -(z.imag()), CXARITHMETIC);
}

#ifdef _STD_OSTREAM_INCLUDED_
/// output override
template <typename _ty> inline std::ostream& operator<<(std::ostream& ostr, const Complex<_ty>& z)
{
	ostr << z.real();
	((z.imag() >= _ty(0)) ? (ostr << "+" << z.imag()) : (ostr << "-" << -(z.imag())));
	return (ostr << "i");
}
#endif

typedef Complex<float> complexf;
typedef Complex<double> complexd;

#endif

