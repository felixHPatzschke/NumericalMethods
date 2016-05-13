#ifndef _FHP_TPOLYNOMIAL_HPP_INCLUDED_
#define _FHP_TPOLYNOMIAL_HPP_INCLUDED_

#if defined(_MSC_VER)
#  ifdef _OSTREAM_
#    define _STD_OSTREAM_INCLUDED_ 1
#  endif
#  ifdef _STRING_
#    define _STD_STRING_INCLUDED_ 1
#  endif
#elif defined(__GNUC__) || defined(__clang__)
#  include <iostream>
#  include <string>
#  define _STD_OSTREAM_INCLUDED_ 1
#  define _STD_STRING_INCLUDED_ 1
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
	inline Polynomial()	{ coef = std::vector<_ty>(0); }
	template <typename aux> inline Polynomial(std::initializer_list<aux> list)
	{
		coef = std::vector<_ty>(0);
		for (aux x : list)
			coef.push_back(_ty(x));
	}
	inline Polynomial(const unsigned int i)
	{
		coef = std::vector<_ty>(i+1);
	}
	inline Polynomial(const _ty i) 
	{ 
		coef = std::vector<_ty>(1); 
		coef[0] = i; 
	}
	inline Polynomial(const Polynomial<_ty>& other);
	#ifdef _STD_STRING_INCLUDED_
	inline Polynomial(std::string str);
	#endif
	inline ~Polynomial(){}

	inline Polynomial<_ty>& operator=(const Polynomial<_ty>& other);
	template <typename aux> inline Polynomial<_ty>& operator=(std::initializer_list<aux> list);
	template <typename aux> inline Polynomial<_ty>& operator=(const aux scalar)
	{
		coef.resize(1);
		coef[0] = scalar;
	}
	
	inline Polynomial<_ty> operator-() const
	{
		Polynomial<_ty> res = Polynomial(coef.size()-1);
		for(unsigned int i=0; i<coef.size(); ++i)
		{
			res.coef[i] = _ty(-1)*coef[i];
		}
		return res;
	}
	
	inline Polynomial<_ty>& operator+=(const Polynomial<_ty>& other);
	template <typename aux> inline Polynomial<_ty>& operator+=(std::initializer_list<aux> list);
	template <typename aux> inline Polynomial<_ty>& operator+=(const aux scalar);
	
	inline Polynomial<_ty>& operator-=(const Polynomial<_ty>& other);
	template <typename aux> inline Polynomial<_ty>& operator-=(std::initializer_list<aux> list);
	template <typename aux> inline Polynomial<_ty>& operator-=(const aux scalar);
	
	

	inline _ty operator()(const _ty x)const
	{
		_ty res = 0.0;
		for(unsigned int i=0; i<coef.size(); ++i)
		{
			if(coef[i]!=_ty(0))
			{
				_ty q = coef[i];
				for(unsigned int j=0; j<i; ++j)
					q *= x;
				res += q;
			}
		}
		return res;
	}
	inline Polynomial<_ty> operator[](const unsigned int i) const
	{
		Polynomial<_ty> res = Polynomial<_ty>(i);
		res.coef[i] = this->get_coefficient(i);
		return res;
	}
	inline unsigned int degree() const { return coef.size()-1; }

	inline Polynomial<_ty> derivative(const int n = 1) const;
	inline _ty derivativeAt(const _ty x) const;
	inline Polynomial<_ty> integral(const int n = 1) const;

	inline _ty get_coefficient(const unsigned int i) const
	{
		if(i<coef.size())
			return coef[i];
		else
			return _ty(0);
	}
	inline Polynomial<_ty>& set_coefficient(const unsigned int i, const _ty arg)
	{
		if(i<coef.size())
			coef[i] = arg;
		else
		{
			coef.resize(i+1);
			coef[i] = arg;
		}
	}
	inline std::vector<_ty>& coefficients()	{ return coef; }

	#ifdef _STD_STRING_INCLUDED_
	inline std::string to_string(const char* argn = "x") const;
	#endif

};

#ifdef _STD_OSTREAM_INCLUDED_
inline std::ostream& operator<<(std::ostream ostr, Polynomial<_ty>& pol);
#endif

template <typename _ty>
inline Polynomial<_ty> Polynomial<_ty>::derivative(const int n)
{
	if(n==0) 
		return Polynomial<_ty>(*this)
	else if(n<0)
		return integral(-n);
	else if(n>degree())
		return Polynomial<_ty>(_ty(0));
	else if(n==1)
	{
		Polynomial<_ty> res(0u);
		for(unsigned int i=1; i<coef.size(); ++i)
		{
			res.set_coefficient(i-1, coef[i]*i);
		}
		return res;
	}
	else
		return derivative().derivative(n-1);
	// TODO: get rid of recursion
}



typedef Polynomial<float> polynomialf;
typedef Polynomial<double> polynomiald;
/// typedef Polynomial<std::complex> polynomialc;

#endif
