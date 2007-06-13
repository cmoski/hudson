/*
* Price.hpp
*/

#ifndef _PRICE_HPP_
#define _PRICE_HPP_

#ifdef WIN32
#pragma warning (disable:4290)
#endif

// C++
#include <stdexcept>

// STL
#include <string>


class PriceException: public std::exception
{
public:
  PriceException(const std::string& msg):
    _Str("PriceException: ")
  {
    _Str += msg;
  }

  virtual ~PriceException(void) throw() { }
  virtual const char *what() const throw() { return _Str.c_str(); }

protected:
  std::string _Str;
};


class Price
{
  public:
    Price(double value) throw(PriceException);
    Price(const Price& src);

    Price& operator=(const Price& src);

    double value(void) const { return _value; }

  protected:
    double _value;
};


inline double operator-(const Price& first, const Price& second) { return first.value() - second.value(); }
inline double operator+(const Price& first, const Price& second) { return first.value() + second.value(); }
inline double operator*(const Price& first, const Price& second) { return first.value() * second.value(); }
inline double operator/(const Price& first, const Price& second) { return first.value() / second.value(); }

inline double operator-(const Price& first, int second) { return first.value() - second; }
inline double operator+(const Price& first, int second) { return first.value() + second; }
inline double operator*(const Price& first, int second) { return first.value() * second; }
inline double operator/(const Price& first, int second) { return first.value() / second; }

#endif // _PRICE_HPP_
