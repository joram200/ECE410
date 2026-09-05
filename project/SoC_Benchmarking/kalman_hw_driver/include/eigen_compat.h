// Compatibility shim for Eigen 5.0.0 on RISC-V bare-metal targets
// (rv32imac/ilp32, GCC 8.3.0 + newlib).
//
// This file is force-included via -include in build_flags, so it is seen by
// both C and C++ translation units.  All C++-specific content is guarded by
// #ifdef __cplusplus.
//
// Root cause:
//   _GLIBCXX_USE_C99_MATH_TR1 is disabled in c++config.h for this target
//   because newlib's 128-bit long double (rv32imac) lacks the l-suffix math
//   functions (fabsl, cbrtl, …).  Without TR1, <cmath> omits float overloads
//   of functions like fma, cbrt, exp2, etc.  Eigen 5 calls these via
//   std:: and hits "not declared" / static_assert failures.
//
//   Additionally, Eigen's MathFunctions.h calls ::fabsl directly (not through
//   std::), but newlib only declares fabsl when _LDBL_EQ_DBL is defined.

#pragma once

#include <math.h>   // always safe: C math functions (declares fmaf, cbrtf, …)

#ifdef __cplusplus
#include <cmath>    // C++ math wrappers

// ---------------------------------------------------------------------------
// Global namespace: long double math symbols newlib omits for 128-bit targets.
// Eigen's absdiff<long double> calls ::fabsl directly.
// ---------------------------------------------------------------------------
#ifndef _LDBL_EQ_DBL
inline long double fabsl(long double x) noexcept { return __builtin_fabsl(x); }
#endif

// ---------------------------------------------------------------------------
// std namespace: float overloads that <cmath> only provides inside the
// _GLIBCXX_USE_C99_MATH_TR1 block (disabled for this target).
// Eigen uses these via EIGEN_USING_STD(func) → using std::func.
// ---------------------------------------------------------------------------
#ifndef _GLIBCXX_USE_C99_MATH_TR1
namespace std {

  // has_fma<float> SFINAE check: needs fma(float,float,float) → float
  inline float fma(float x, float y, float z) noexcept   { return ::fmaf(x, y, z); }

  inline float cbrt(float x) noexcept                     { return ::cbrtf(x); }
  inline float exp2(float x) noexcept                     { return ::exp2f(x); }
  inline float expm1(float x) noexcept                    { return ::expm1f(x); }
  inline float log1p(float x) noexcept                    { return ::log1pf(x); }
  inline float log2(float x) noexcept                     { return ::log2f(x); }
  inline float logb(float x) noexcept                     { return ::logbf(x); }
  inline int   ilogb(float x) noexcept                    { return ::ilogbf(x); }

  inline float acosh(float x) noexcept                    { return ::acoshf(x); }
  inline float asinh(float x) noexcept                    { return ::asinhf(x); }
  inline float atanh(float x) noexcept                    { return ::atanhf(x); }

  inline float erf(float x) noexcept                      { return ::erff(x); }
  inline float erfc(float x) noexcept                     { return ::erfcf(x); }

  inline float tgamma(float x) noexcept                   { return ::tgammaf(x); }
  inline float lgamma(float x) noexcept                   { return ::lgammaf(x); }

  inline float hypot(float x, float y) noexcept           { return ::hypotf(x, y); }
  inline float fdim(float x, float y) noexcept            { return ::fdimf(x, y); }
  inline float fmax(float x, float y) noexcept            { return ::fmaxf(x, y); }
  inline float fmin(float x, float y) noexcept            { return ::fminf(x, y); }
  inline float remainder(float x, float y) noexcept       { return ::remainderf(x, y); }
  inline float remquo(float x, float y, int* q) noexcept  { return ::remquof(x, y, q); }
  inline float nextafter(float x, float y) noexcept       { return ::nextafterf(x, y); }
  inline float copysign(float x, float y) noexcept        { return ::copysignf(x, y); }

  inline float round(float x) noexcept                    { return ::roundf(x); }
  inline float trunc(float x) noexcept                    { return ::truncf(x); }
  inline float rint(float x) noexcept                     { return ::rintf(x); }
  inline float nearbyint(float x) noexcept                { return ::nearbyintf(x); }

  inline long int  lrint(float x) noexcept                { return ::lrintf(x); }
  inline long long llrint(float x) noexcept               { return ::llrintf(x); }
  inline long int  lround(float x) noexcept               { return ::lroundf(x); }
  inline long long llround(float x) noexcept              { return ::llroundf(x); }

  inline float scalbln(float x, long int n) noexcept      { return ::scalblnf(x, n); }
  inline float scalbn(float x, int n) noexcept            { return ::scalbnf(x, n); }

}  // namespace std
#endif  // !_GLIBCXX_USE_C99_MATH_TR1

#endif  // __cplusplus
