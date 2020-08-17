#ifdef _MSC_VER
#pragma once
#endif  //_MSC_VER

#ifndef VECOVERRIDES
#define VECOVERRIDES

#include <assert.h>
#include <array>
#include <functional>
#include <vector>
#include "../precisionChecks.hpp"
typedef std::vector<double> vecDBL;
typedef std::array<double, 2> arrXY;
typedef std::array<double, 3> arrABC;
typedef std::array<double, 3> arrXYR;

// If this was templated on the num elements argument, I wonder if the compiler
// would auto unroll any loops
inline bool _ARRAY2_ALMOST_EQUAL(const arrXY &a, const arrXY &b,
                                 double epsScale) {
  return _ALMOST_EQUAL(a[0], b[0], epsScale) &&
         _ALMOST_EQUAL(a[1], b[1], epsScale);
}

inline bool _ARRAY2_ALMOST_ZERO(const arrXY &a, double epsScale) {
  return _ALMOST_ZERO(a[0], epsScale) && _ALMOST_ZERO(a[1], epsScale);
}

inline double _MAXVAL_3xARRXY(const arrXY &a, const arrXY &b, const arrXY &c) {
  return std::fmax(std::fmax(a[0], a[1]),
                   std::fmax(std::fmax(b[0], b[1]), std::fmax(c[0], c[1])));
}

template <typename T>
inline std::vector<T> operator+(const std::vector<T> &a,
                                const std::vector<T> &b) {
  assert(a.size() == b.size());

  std::vector<T> result(a.size());
  // result.reserve(a.size());
  for (std::size_t i = 0; i < a.size(); i++) result[i] = a[i] + b[i];
  // std::transform(a.begin(), a.end(), b.begin(),
  // std::back_inserter(result), std::plus<T>());
  return result;
}
inline arrXY operator+(const arrXY &a, const arrXY &b) {
  arrXY result;
  result[0] = a[0] + b[0];
  result[1] = a[1] + b[1];
  return result;
}
inline arrABC operator+(const arrABC &a, const arrABC &b) {
  arrABC result;
  result[0] = a[0] + b[0];
  result[1] = a[1] + b[1];
  return result;
}
template <typename T>
inline std::vector<T> operator+(const std::vector<T> &a, const T &b) {
  std::vector<T> result(a.size());
  // result.reserve(a.size());
  for (int i = 0; i < a.size(); i++) result[i] = a[i] + b;
  // std::transform(a.begin(), a.end(),
  // std::back_inserter(result), bind2nd(std::plus<T>(), b));
  return result;
}

template <typename T>
inline std::vector<T> operator+(const T &b, const std::vector<T> &a) {
  std::vector<T> result(a.size());
  // result.reserve(a.size());
  for (int i = 0; i < a.size(); i++) result[i] = a[i] + b;
  return result;
}
inline arrXY operator+(const arrXY &a, const double &b) {
  arrXY result;
  result[0] = a[0] + b;
  result[1] = a[1] + b;
  return result;
}
inline arrXY operator+(const double &b, const arrXY &a) {
  arrXY result;
  result[0] = a[0] + b;
  result[1] = a[1] + b;
  return result;
}

// vec - ? overrides
template <typename T>
inline std::vector<T> operator-(const std::vector<T> &a,
                                const std::vector<T> &b) {
  assert(a.size() == b.size());

  std::vector<T> result(a.size());
  // result.reserve(a.size());
  for (std::size_t i = 0; i < a.size(); i++) result[i] = a[i] - b[i];

  return result;
}
inline arrXY operator-(const arrXY &a, const arrXY &b) {
  arrXY result;
  result[0] = a[0] - b[0];
  result[1] = a[1] - b[1];
  return result;
}

template <typename T>
inline std::vector<T> operator-(const std::vector<T> &a, const T &b) {
  std::vector<T> result(a.size());
  // result.reserve(a.size());
  for (int i = 0; i < a.size(); i++) result[i] = a[i] - b;
  return result;
}

template <typename T>
inline std::vector<T> operator-(const T &b, const std::vector<T> &a) {
  std::vector<T> result(a.size());
  // result.reserve(a.size());
  for (int i = 0; i < a.size(); i++) result[i] = b - a[i];
  return result;
}
inline arrXY operator-(const arrXY &a, const double &b) {
  arrXY result;
  result[0] = a[0] - b;
  result[1] = a[1] - b;
  return result;
}
inline arrXY operator-(const double &b, const arrXY &a) {
  arrXY result;
  result[0] = b - a[0];
  result[1] = b - a[1];
  return result;
}

// This is not appropiate vector multiplication
// vec * ? overrides
template <typename T>
inline std::vector<T> operator*(const std::vector<T> &a,
                                const std::vector<T> &b) {
  assert(a.size() == b.size());

  std::vector<T> result(a.size());
  // result.reserve(a.size());
  for (int i = 0; i < a.size(); i++) result[i] = a[i] * b[i];
  return result;
}
inline arrXY operator*(const arrXY &a, const arrXY &b) {
  arrXY result;
  result[0] = a[0] * b[0];
  result[1] = a[1] * b[1];
  return result;
}
template <typename T>
inline std::vector<T> operator*(const std::vector<T> &a, const T &b) {
  std::vector<T> result(a.size());
  // result.reserve(a.size());
  for (int i = 0; i < a.size(); i++) result[i] = a[i] * b;
  return result;
}

template <typename T>
inline std::vector<T> operator*(const T &b, const std::vector<T> &a) {
  std::vector<T> result(a.size());
  // result.reserve(a.size());
  for (std::size_t i = 0; i < a.size(); i++) result[i] = a[i] * b;
  return result;
}
inline arrXY operator*(const arrXY &a, const double &b) {
  arrXY result;
  result[0] = a[0] * b;
  result[1] = a[1] * b;
  return result;
}
inline arrXY operator*(const double &b, const arrXY &a) {
  arrXY result;
  result[0] = a[0] * b;
  result[1] = a[1] * b;
  return result;
}
// vec / ? overrides
template <typename T>
inline std::vector<T> operator/(const std::vector<T> &a,
                                const std::vector<T> &b) {
  assert(a.size() == b.size());

  std::vector<T> result(a.size());
  // result.reserve(a.size());
  for (int i = 0; i < a.size(); i++) result[i] = a[i] / b[i];
  return result;
}
inline arrXY operator/(const arrXY &a, const arrXY &b) {
  arrXY result;
  result[0] = a[0] / b[0];
  result[1] = a[1] / b[1];
  return result;
}
template <typename T>
inline std::vector<T> operator/(const std::vector<T> &a, const T &b) {
  std::vector<T> result(a.size());
  // result.reserve(a.size());
  for (std::size_t i = 0; i < a.size(); i++) result[i] = a[i] / b;
  return result;
}

template <typename T>
inline std::vector<T> operator/(const T &b, const std::vector<T> &a) {
  std::vector<T> result(a.size());
  // result.reserve(a.size());
  for (int i = 0; i < a.size(); i++) result[i] = b / a[i];
  return result;
}
inline arrXY operator/(const arrXY &a, const double &b) {
  arrXY result;
  result[0] = a[0] / b;
  result[1] = a[1] / b;  // result.reserve(a.size());
  return result;
}
inline arrXY operator/(const double &b, const arrXY &a) {
  arrXY result;
  result[0] = a[0] / b;
  result[1] = a[1] / b;  // result.reserve(a.size());
  return result;
}
// vec += overrides
template <typename T>
inline void operator+=(std::vector<T> &a, const std::vector<T> &b) {
  assert(a.size() == b.size());
  // result.reserve(a.size());
  for (int i = 0; i < a.size(); i++) a[i] += b[i];
}
inline void operator+=(arrXY &a, const arrXY &b) {
  a[0] = a[0] + b[0];
  a[1] = a[1] + b[1];
}

template <typename T>
inline void operator+=(std::vector<T> &a, const T &b) {
  for (int i = 0; i < a.size(); i++) a[i] += b;
}
inline void operator+=(arrXY &a, const double &b) {
  a[0] = a[0] + b;
  a[1] = a[1] + b;
}
// vec -= overrides
template <typename T>
inline void operator-=(std::vector<T> &a, const std::vector<T> &b) {
  assert(a.size() == b.size());
  for (int i = 0; i < a.size(); i++) a[i] -= b[i];
}
inline void operator-=(arrXY &a, const arrXY &b) {
  a[0] = a[0] - b[0];
  a[1] = a[1] - b[1];
}
template <typename T>
inline void operator-=(std::vector<T> &a, const T &b) {
  assert(a.size() == b.size());
  for (int i = 0; i < a.size(); i++) a[i] -= b;
}
inline void operator-=(arrXY &a, const double &b) {
  a[0] = a[0] - b;
  a[1] = a[1] - b;
}
/*
//vec *= overrides
template <typename T>
std::vector<T> operator*=(std::vector<T> &a, const std::vector<T> &b)
{
        assert(a.size() == b.size());

        std::transform(a.begin(), a.end(), b.begin(),
                                        a.begin(), std::multiplies<T>());
        return a;
}

template <typename T>
std::vector<T> operator*=(const std::vector<T> &a, const T &b)
{
        std::transform(a.begin(), a.end(),
                                        a.begin(), bind2nd(std::multiplies<T>(),
b));
        return a;
}

//vec /= overrides
template <typename T>
std::vector<T> operator/=(const std::vector<T> &a, const std::vector<T> &b)
{
        assert(a.size() == b.size());

        std::transform(a.begin(), a.end(), b.begin(),
                                        a.begin(), std::divides<T>());
        return a;
}

template <typename T>
std::vector<T> operator/=(const std::vector<T> &a, const T &b)
{
        std::transform(a.begin(), a.end(),
                                        a.begin(), bind2nd(std::divides<T>(),
b));
        return a;
}
*/
#endif
