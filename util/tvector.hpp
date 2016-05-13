#ifndef _FHP_TVECTOR_HPP_INCLUDED_
#define _FHP_TVECTOR_HPP_INCLUDED_

#if defined(_MSC_VER)
  #ifdef _OSTREAM_
    #define _STD_OSTREAM_INCLUDED_ 1
  #endif // _OSTREAM_
  #ifdef _STRING_
    #define _STD_STRING_INCLUDED_ 1
  #endif // _STRING_
#elif defined(__GNUC__) || defined(__clang__)
  #include <iostream>
  #include <string>
  #define _STD_OSTREAM_INCLUDED_ 1
  #define _STD_STRING_INCLUDED_ 1
#endif


#include <initializer_list>
#include <cmath>

#define GENERIC_VECTOR Vector<dim, base_t>
#define iterate for(unsigned int i=0; i<dim; ++i)


template <unsigned int dim, typename base_t> class Vector
{
protected:
	/// components
	base_t comp[dim];

public:
	/// constructor
	Vector();
	Vector(int);
	template <typename auxtype> Vector(std::initializer_list<auxtype>);
	Vector(GENERIC_VECTOR&);
	/// destructor
	virtual ~Vector();

	/// direct assignment operators
	inline GENERIC_VECTOR& operator=(const GENERIC_VECTOR&);
	template <typename auxtype> inline GENERIC_VECTOR& operator=(std::initializer_list<auxtype>);
	template <typename auxtype> inline GENERIC_VECTOR& operator=(const auxtype);

	/// indirect assignment operators
	inline GENERIC_VECTOR& operator+=(const GENERIC_VECTOR&);
	template <typename auxtype> inline GENERIC_VECTOR& operator+=(std::initializer_list<auxtype>);
	inline GENERIC_VECTOR& operator-=(const GENERIC_VECTOR&);
	template <typename auxtype> inline GENERIC_VECTOR& operator-=(std::initializer_list<auxtype>);
	template <typename auxtype> inline GENERIC_VECTOR& operator*=(const auxtype);
	template <typename auxtype> inline GENERIC_VECTOR& operator/=(const auxtype);

	/// comparison operators
	inline int operator==(const GENERIC_VECTOR&) const;
	//template <typename auxtype> inline int operator==(std::initializer_list<auxtype>) const;
	inline int operator!=(const GENERIC_VECTOR&) const;
	//template <typename auxtype> inline int operator!=(std::initializer_list<auxtype>) const;

	/// arithmetic operators
	inline GENERIC_VECTOR operator+(const GENERIC_VECTOR&) const;
	//template <typename auxtype> inline GENERIC_VECTOR operator+(std::initializer_list<auxtype>) const;
	inline GENERIC_VECTOR operator-(const GENERIC_VECTOR&) const;
	//template <typename auxtype> inline GENERIC_VECTOR operator-(std::initializer_list<auxtype>) const;
	template <typename auxtype> inline GENERIC_VECTOR operator*(const auxtype) const;
	template <typename auxtype> inline GENERIC_VECTOR operator/(const auxtype) const;
	//inline base_t operator*(const GENERIC_VECTOR&) const;

	/// other vector operations
	inline base_t abs_sqr() const;
	inline base_t abs() const;
	inline GENERIC_VECTOR get_normalized() const;
	inline GENERIC_VECTOR operator-() const;
	inline GENERIC_VECTOR& normalize();

	/// direct access
	inline base_t get(unsigned int i) const;
	inline GENERIC_VECTOR& set(unsigned int i, const base_t x);
	inline base_t& operator[](unsigned int i);
	inline base_t* get_array_pointer();

#ifdef _STD_STRING_INCLUDED_
	inline std::string to_string(const char* left_bracket = "(", const char* right_bracket = ")", const char* separator = "; ") const;
#endif

	template <typename auxtype> Vector<dim, auxtype> cast() const;

};
/// some more arithmetic operators
template <typename auxtype, unsigned int dim, typename base_t> inline GENERIC_VECTOR operator*(auxtype, GENERIC_VECTOR&);
template <typename base_t> inline Vector<3u, base_t> cross(const Vector<3u, base_t>, const Vector<3u, base_t>&);
template <unsigned int dim, typename base_t> inline base_t dot(const GENERIC_VECTOR, const GENERIC_VECTOR&);
template <unsigned int dim, typename base_t> inline base_t abs(const GENERIC_VECTOR&);

#ifdef _STD_OSTREAM_INCLUDED_
/// output override
template <unsigned int dim, typename base_t> inline std::ostream& operator<<(std::ostream&, GENERIC_VECTOR&);
#endif



/** Default Contructor */
template<unsigned int dim, typename base_t>
inline Vector<dim, base_t>::Vector()
{
	iterate comp[i] = base_t(0.0);
}
/** Contructor */
template<unsigned int dim, typename base_t>
inline Vector<dim, base_t>::Vector(int x)
{
	iterate comp[i] = ((x - i == 1) ? (1.0) : (0.0));
}
/** Contructor */
template<unsigned int dim, typename base_t>
template<typename auxtype>
inline Vector<dim, base_t>::Vector(std::initializer_list<auxtype> list)
{
	unsigned int i = 0;
	for (auxtype x : list) this->comp[i++] = static_cast<base_t>(x);
}
/** Copy Contructor */
template<unsigned int dim, typename base_t>
inline Vector<dim, base_t>::Vector(GENERIC_VECTOR& v)
{
	iterate comp[i] = v.get(i);
}
/** Destructor */
template<unsigned int dim, typename base_t>
inline Vector<dim, base_t>::~Vector()
{

}


/** direct assignment operator */
template<unsigned int dim, typename base_t>
inline GENERIC_VECTOR & Vector<dim, base_t>::operator=(const GENERIC_VECTOR &v)
{
	if (&v != this)
		iterate comp[i] = v.get(i);
	return *this;
}
/** direct assignment operator */
template<unsigned int dim, typename base_t>
template<typename auxtype>
inline GENERIC_VECTOR & Vector<dim, base_t>::operator=(std::initializer_list<auxtype> list)
{
	unsigned int i = 0;
	for(auxtype x : list) this->comp[i++] = static_cast<base_t>(x);
	return *this;
}
/** direct scalar assignment operator - assigns the argument to all components ( mainly intended for 0 )*/
template<unsigned int dim, typename base_t>
template<typename auxtype>
inline GENERIC_VECTOR & Vector<dim, base_t>::operator=(const auxtype arg)
{
	iterate this->comp[i] = static_cast<base_t>(arg);
	return *this;
}


/** indirect assignment/addition operator */
template<unsigned int dim, typename base_t>
inline GENERIC_VECTOR & Vector<dim, base_t>::operator+=(const GENERIC_VECTOR &v)
{
	iterate this->comp[i] += v.comp[i];
	return *this;
}
/** indirect assignment/addition operator */
template<unsigned int dim, typename base_t>
template<typename auxtype>
inline GENERIC_VECTOR & Vector<dim, base_t>::operator+=(std::initializer_list<auxtype> list)
{
	unsigned int i = 0;
	for (auxtype x : list) this->comp[i++] += static_cast<base_t>(x);
	return *this;
}
/** indirect assignment/subtraction operator */
template<unsigned int dim, typename base_t>
inline GENERIC_VECTOR & Vector<dim, base_t>::operator-=(const GENERIC_VECTOR &v)
{
	iterate this->comp[i] -= v.comp[i];
	return *this;
}
/** indirect assignment/subtraction operator */
template<unsigned int dim, typename base_t>
template<typename auxtype>
inline GENERIC_VECTOR & Vector<dim, base_t>::operator-=(std::initializer_list<auxtype> list)
{
	unsigned int i = 0;
	for(auxtype x : list) this->comp[i++] -= static_cast<base_t>(x);
	return *this;
}
/** indirect assignment/multiplication operator */
template<unsigned int dim, typename base_t>
template<typename auxtype>
inline GENERIC_VECTOR & Vector<dim, base_t>::operator*=(const auxtype arg)
{
	base_t x = static_cast<base_t>(arg);
	iterate this->comp[i] *= x;
	return *this;
}
/** indirect assignment/division operator */
template<unsigned int dim, typename base_t>
template<typename auxtype>
inline GENERIC_VECTOR & Vector<dim, base_t>::operator/=(const auxtype arg)
{
	base_t x = static_cast<base_t>(arg);
	iterate this->comp[i] /= x;
	return *this;
}


/** Equality sign */
template<unsigned int dim, typename base_t>
inline int Vector<dim, base_t>::operator==(const GENERIC_VECTOR &other) const
{
	if (this == &other)
		return true;
	else
		for (unsigned int i = 0; i < dim; ++i)
			if (this->get(i) != other.get(i))
				return false;
	return true;
}
/* Equality sign
template<unsigned int dim, typename base_t>
template<typename auxtype>
inline int Vector<dim, base_t>::operator==(std::initializer_list<auxtype> list) const
{
	if (this == &other)
		return true;
	else
	{
		unsigned int i = 0
		for (auxtype x : list)
			if (static_cast<auxtype>(this->get(i++)) != x)
				return false;
		return true;
	}
}*/
/** Inequality sign */
template<unsigned int dim, typename base_t>
inline int Vector<dim, base_t>::operator!=(const GENERIC_VECTOR &other) const
{
	if (this == &other)
		return false;
	else
		for (unsigned int i = 0; i < dim; ++i)
			if (this->get(i) != other.get(i))
				return true;
	return false;
}
/* Inequality sign
template<unsigned int dim, typename base_t>
template<typename auxtype>
inline int Vector<dim, base_t>::operator!=(std::initializer_list<auxtype> list) const
{
	if (this == &other)
		return false;
	else
	{
		unsigned int i = 0
		for (auxtype x : list)
			if (static_cast<auxtype>(this->get(i++)) != x)
				return true;
		return false;
	}
}*/


/** Plus operator */
template<unsigned int dim, typename base_t>
inline GENERIC_VECTOR Vector<dim, base_t>::operator+(const GENERIC_VECTOR &other) const
{
	GENERIC_VECTOR res;
	iterate res.set(i, this->get(i) + other.get(i));
	return res;
}
/** Plus operator *
template<unsigned int dim, typename base_t>
template<typename auxtype>
inline GENERIC_VECTOR Vector<dim, base_t>::operator+(std::initializer_list<auxtype> list) const
{
	GENERIC_VECTOR res;
	unsigned int i = 0;
	for (auxtype x : list)
	{
		res.set(i, this->get(i) + static_cast<base_t>(x));
		++i;
	}
	return res;
}*/
/** Minus operator */
template<unsigned int dim, typename base_t>
inline GENERIC_VECTOR Vector<dim, base_t>::operator-(const GENERIC_VECTOR &other) const
{
	GENERIC_VECTOR res;
	iterate res.set(i, this->get(i) - other.get(i));
	return res;
}
/** Minus operator *
template<unsigned int dim, typename base_t>
template<typename auxtype>
inline GENERIC_VECTOR Vector<dim, base_t>::operator-(std::initializer_list<auxtype> list) const
{
	GENERIC_VECTOR res;
	unsigned int i = 0;
	for (auxtype x : list)
	{
		res.set(i, this->get(i) - static_cast<base_t>(x));
		++i;
	}
	return res;
}*/
/** Scalar multiplication */
template<unsigned int dim, typename base_t>
template<typename auxtype>
inline GENERIC_VECTOR Vector<dim, base_t>::operator*(const auxtype arg) const
{
	GENERIC_VECTOR res;
	iterate res.set(i, this->get(i)*static_cast<base_t>(arg));
	return res;
}
/** Scalar division */
template<unsigned int dim, typename base_t>
template<typename auxtype>
inline GENERIC_VECTOR Vector<dim, base_t>::operator/(const auxtype arg) const
{
	GENERIC_VECTOR res;
	iterate res.set(i, this->get(i)/static_cast<base_t>(arg));
	return res;
}
/** Basic type conversion */
template<unsigned int dim, typename base_t>
template<typename auxtype>
inline Vector<dim, auxtype> Vector<dim, base_t>::cast() const
{
	Vector<dim, auxtype> res(0);
	iterate res.set(i, static_cast<auxtype>(this->get(i)));
	return res;
}
/** Dot product *
template<unsigned int dim, typename base_t>
inline base_t Vector<dim, base_t>::operator*(const GENERIC_VECTOR & other) const
{
	base_t res = 0.0;
	iterate res += this->get(i) + other.get(i);
	return res;
}*/


/** Square of the absolute value */
template<unsigned int dim, typename base_t>
inline base_t Vector<dim, base_t>::abs_sqr() const
{
	base_t res = 0.0;
	iterate res += this->get(i)*this->get(i);
	return res;
}
/** Absolute value */
template<unsigned int dim, typename base_t>
inline base_t Vector<dim, base_t>::abs() const
{
	base_t res = 0.0;
	iterate res += this->get(i)*this->get(i);
	return std::sqrt(res);
}
/** Normalized vector */
template<unsigned int dim, typename base_t>
inline GENERIC_VECTOR Vector<dim, base_t>::get_normalized() const
{
    GENERIC_VECTOR res;
    res = *this / this->abs();
	return res;
}
/** Inverse vector */
template<unsigned int dim, typename base_t>
inline GENERIC_VECTOR Vector<dim, base_t>::operator-() const
{
	GENERIC_VECTOR res;
	res = this->operator*(-1.0);
	return res;
}
/** Normalizes the vector */
template<unsigned int dim, typename base_t>
inline GENERIC_VECTOR & Vector<dim, base_t>::normalize()
{
	base_t a = this->abs();
	iterate this->comp[i] /= a;
	return *this;
}


/** Indirect access */
template<unsigned int dim, typename base_t>
inline base_t Vector<dim, base_t>::get(unsigned int i) const
{
	return this->comp[i];
}
/** Indirect access */
template<unsigned int dim, typename base_t>
inline GENERIC_VECTOR & Vector<dim, base_t>::set(unsigned int i, const base_t x)
{
	this->comp[i] = x;
	return *this;
}
/** Direct access */
template<unsigned int dim, typename base_t>
inline base_t & Vector<dim, base_t>::operator[](unsigned int i)
{
	return (this->comp[i]);
}
/** Access to basic array */
template<unsigned int dim, typename base_t>
inline base_t * Vector<dim, base_t>::get_array_pointer()
{
	return this->comp;
}

#ifdef _STD_STRING_INCLUDED_
#include <sstream>
/** Returns a string representation of the vector */
template<unsigned int dim, typename base_t>
inline std::string Vector<dim, base_t>::to_string(const char * left_bracket, const char * right_bracket, const char * separator) const
{
	std::stringstream sstr;
	iterate sstr << ((i == 0) ? (left_bracket) : (separator)) << this->get(i);
	sstr << right_bracket;
	return sstr.str();
}
#endif


/** Scalar product (manifold?) */
template<typename auxtype, unsigned int dim, typename base_t>
inline GENERIC_VECTOR operator*(auxtype m, GENERIC_VECTOR &v)
{
	GENERIC_VECTOR res = v;
	res *= m;
	return res;
}
/** Cross product */
template<typename base_t>
inline Vector<3u, base_t> cross(const Vector<3u, base_t> a, const Vector<3u, base_t>& b)
{
	Vector<3u, base_t> res;
	res.set(0, a.get(1) * b.get(2) - a.get(2) * b.get(1));
	res.set(1, a.get(2) * b.get(0) - a.get(0) * b.get(2));
	res.set(2, a.get(0) * b.get(1) - a.get(1) * b.get(0));
	return res;
}
/** Dot product */
template<unsigned int dim, typename base_t>
inline base_t dot(const GENERIC_VECTOR a, const GENERIC_VECTOR &b)
{
	base_t res = 0.0;
	iterate res += a.get(i)*b.get(i);
	return res;
}
/** Absolute value */
template<unsigned int dim, typename base_t>
inline base_t abs(const GENERIC_VECTOR &arg)
{
	return arg.abs();
}


#ifdef _STD_OSTREAM_INCLUDED_
/** Ouput override for std::ostream */
template <unsigned int dim, typename base_t>
inline std::ostream& operator<<(std::ostream& str, GENERIC_VECTOR& v)
{
	iterate str << ((i == 0) ? ("(") : ("; ")) << v.get(i);
	return str << ")";
}
#endif

#undef iterate

typedef Vector<2u, float> vector2f;
typedef Vector<2u, double> vector2d;
typedef Vector<3u, float> vector3f;
typedef Vector<3u, double> vector3d;

#endif

