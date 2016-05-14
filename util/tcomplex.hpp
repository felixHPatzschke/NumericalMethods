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
#define CXARITHMETIC complex_representation::arithmetic;
#define CXPOLAR complex_representation::polar;
#define CXREAL 0u
#define CXIMAG 1u

template <typename _ty> class Complex
{
protected:
	/// components
	_ty re, im;

public:
	/// constructor
	inline Complex()
	{
		re = _ty(0);
		im = _ty(0);
	}
	inline Complex(const _ty x, const _ty y = _ty(0), const CXREP representation = CXARITHMETIC)
	{
		if(representation==CXARITHMETIC)
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
	template <typename aux> inline Complex(std::initializer_list<aux> list)
	inline Complex(const Complex<_ty>& other)
	{
		re = other.re;
		im = other.im;
	}
	#ifdef _STD_COMPLEX_INCLUDED_
	inline Complex(const std::complex&);
	#endif
	/// destructor
	inline ~Complex() {  }

	#ifdef _STD_COMPLEX_INCLUDED_
	inline operator std::complex() const { return std::complex(re, im); }
	#endif
	template <typename aux> inline Complex<aux> cast() const { return Complex<aux>(static_cast<aux>(re), static_cast<aux>(im), CXARITHMETIC); }
	
	/// direct assignment operators
	inline Complex<_ty>& operator=(const Complex<_ty>& other)
	{
		this->re = other.re;
		this->im = other.im;
	}
	template <typename aux> inline GENERIC_VECTOR& operator=(std::initializer_list<aux>);
	inline Complex<_ty>& operator=(const _ty x)
	{
		this->re = x;
		this->im = _ty(0);
	}

	/// indirect assignment operators
	inline Complex<_ty>& operator+=(const Complex<_ty>& other)
	{
		re += other.re;
		im += other.im;
	}
	template <typename aux> inline Complex<_ty>& operator+=(std::initializer_list<aux> list)
	{
		unsigned int i=0;
		for(aux x : list)
			this->operator[](i++)+=static_cast<_ty>(x);
	}
	template <typename aux> inline Complex<_ty>& operator+=(const aux x)
	{
		re += static_cast<_ty>(x);
	}
	#ifdef _STD_COMPLEX_INCLUDED_
	inline Complex<_ty>& operator+=(const std::complex&);
	#endif
	inline Complex<_ty>& operator+=(const Complex<_ty>& other)
	{
		re -= other.re;
		im -= other.im;
	}
	template <typename aux> inline Complex<_ty>& operator+=(std::initializer_list<aux> list)
	{
		unsigned int i=0;
		for(aux x : list)
			this->operator[](i++)-=static_cast<_ty>(x);
	}
	template <typename aux> inline Complex<_ty>& operator+=(const aux x)
	{
		re -= static_cast<_ty>(x);
	}
	#ifdef _STD_COMPLEX_INCLUDED_
	inline Complex<_ty>& operator-=(const std::complex&);
	#endif
	inline Complex<_ty>& operator*=(const Complex<_ty>&);
	template <typename aux> inline Complex<_ty>& operator*=(std::initializer_list<aux>);
	template <typename aux> inline Complex<_ty>& operator*=(const aux);
	#ifdef _STD_COMPLEX_INCLUDED_
	inline Complex<_ty>& operator*=(const std::complex&);
	#endif
	inline Complex<_ty>& operator/=(const Complex<_ty>&);
	template <typename aux> inline Complex<_ty>& operator/=(std::initializer_list<aux>);
	template <typename aux> inline Complex<_ty>& operator/=(const aux);
	#ifdef _STD_COMPLEX_INCLUDED_
	inline Complex<_ty>& operator/=(const std::complex&);
	#endif
	
	/// comparison operators
	inline int operator==(const Complex<_ty>& other) const
	{
		return ((re==other.re)&&(im==other.im));
	}
	inline int operator!=(const Complex<_ty>& other) const;
	{
		return ((re!=other.re)||(im!=other.im));
	}
	template <typename aux> inline int operator==(const aux arg) const
	{
		return ((re==arg)&&(im==_ty(0)));
	}
	template <typename aux> inline int operator!=(const aux arg) const;
	{
		return ((re!=arg)||(im!=_ty(0)));
	}
	#ifdef _STD_COMPLEX_INCLUDED_
	inline int operator==(const std::complex& stdc) const;
	inline int operator!=(const std::complex& stdc) const;
	#endif

	/// arithmetic operators
	inline Complex<_ty> operator-() const { return Complex<_ty>(-re, -im) };
	#ifdef _FHP_OVERLOAD_LOGICAL_NOT_OPERATOR_BY_COMPLEX_CONJUGATE_
	inline Complex<_ty> operator!() const { return Complex<_ty>(re, -im) };
	#endif

	inline Complex<_ty> operator+(const Complex<_ty>&) const;
	template <typename aux> inline Complex<_ty> operator+(std::initializer_list<aux>) const;
	template <typename aux> inline Complex<_ty> operator+(const aux) const;
	#ifdef _STD_COMPLEX_INCLUDED_
	inline Complex<_ty> operator+(const std::complex&) const;
	#endif
	inline Complex<_ty> operator-(const Complex<_ty>&) const;
	template <typename aux> inline Complex<_ty> operator-(std::initializer_list<aux>) const;
	template <typename aux> inline Complex<_ty> operator-(const aux) const;
	#ifdef _STD_COMPLEX_INCLUDED_
	inline Complex<_ty> operator-(const std::complex&) const;
	#endif
	inline Complex<_ty> operator*(const Complex<_ty>&) const;
	template <typename aux> inline Complex<_ty> operator*(std::initializer_list<aux>) const;
	template <typename aux> inline Complex<_ty> operator*(const aux) const;
	#ifdef _STD_COMPLEX_INCLUDED_
	inline Complex<_ty> operator*(const std::complex&) const;
	#endif
	inline Complex<_ty> operator/(const Complex<_ty>&) const;
	template <typename aux> inline Complex<_ty> operator/(std::initializer_list<aux>) const;
	template <typename aux> inline Complex<_ty> operator/(const aux) const;
	#ifdef _STD_COMPLEX_INCLUDED_
	inline Complex<_ty> operator/(const std::complex&) const;
	#endif

	/// other operations
	inline Complex<_ty> sqr() const { return Complex<_t>(re*re-im*im, _ty(2)*re*im); }
	inline Complex<_ty> sqrt() const;

	/// direct access
	inline _ty real() const { return re; }
	inline _ty imag() const { return im; }
	inline _ty& operator[](unsigned int i)
	{
		if(i==CXREAL) return re;
		else if(i==CXIMAG) return im;
		else return _ty(0);
	}
	inline _ty* get(const CXREP representation = CXARITHMETIC)
	{
		_ty* res = static_cast<_ty*>malloc(2*sizeof(_ty));
		if(representation == CXARITHMETIC)
		{
			res[0] = re;
			res[1] = im;
		}
		else
		{
			res[0] = sqrt(re*re + im*im);
			res[1] = arg();
		}
		return res;
	}
	inline Complex<_ty>& set_real(const _ty x) { re = x; }
	inline Complex<_ty>& set_imag(const _ty y) { im = y; }
	inline Complex<_ty>& set(const _ty x, const _ty y, const CXREP representation = CXARITHMETIC)
	{
		if(representation==CXARITHMETIC)
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
	
	inline _ty abs() const { return sqrt(re*re + im*im); }
	inline _ty arg() const; 
	inline _ty norm() const { return (re*re + im*im); }
	inline Complex<_ty> conj() const { return Complex<_ty>(re, -im); }
	
	

#ifdef _STD_STRING_INCLUDED_
	inline std::string to_string() const
	{
		std::stringstream sstr();
		sstr << re << "+" << im << "i";
		return sstr.str();
	}
#endif


};
/// some more arithmetic operators
template <typename _ty> inline Complex<_ty> operator*(_ty a, Complex<_ty>& z)
{
	return Complex<_ty>(a*z.real(), a*z.imag(), CXARITHMETIC);
}
template <typename _ty> inline _ty abs(const Complex<_ty>& z)
{
	return sqrt(z.real()*z.real() + z.imag()*z.imag());
}

#ifdef _STD_OSTREAM_INCLUDED_
/// output override
template <typename _ty> inline std::ostream& operator<<(std::ostream& ostr, Complex<_ty>& z)
{
	return (ostr << z.real() << "+" << z.imag() << "i");
}
#endif





typedef Complex<float> complexf;
typedef Complex<double> complexd;

#endif

