/*****************************************************************************
ISC License

Copyright (c) 2016, Timothy Lyons

Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
PERFORMANCE OF THIS SOFTWARE.

******************************************************************************/
#ifndef MATH_FIXEDPOINT_HPP
#define MATH_FIXEDPOINT_HPP

#include "math/pow10.hpp"

#include <cstdint>
#include <iosfwd>
#include <ratio>

namespace math {

template <typename RATIO>
struct fixed_point_t {

   using ratio = RATIO;

   constexpr fixed_point_t()
      : m_value() {}

   explicit constexpr fixed_point_t(double value)
      : m_value(static_cast<int64_t>(value * ratio::den) / ratio::num) {}

   constexpr fixed_point_t& operator+=(const fixed_point_t& other) {
      m_value += other.m_value;
      return *this;
   }

   constexpr fixed_point_t& operator-=(const fixed_point_t& other) {
      m_value -= other.m_value;
      return *this;
   }

   constexpr int64_t whole_number() const {
      return (m_value * ratio::num) / ratio::den;
   }

   int64_t& significand() {
      return m_value;
   }

   constexpr int64_t significand() const {
      return m_value;
   }

   struct rational_t {

      constexpr rational_t(int64_t numerator, uint64_t denominator)
         : m_numerator(numerator)
         , m_denominator(denominator) {}

      int64_t m_numerator;
      uint64_t m_denominator;
   };

   constexpr rational_t fraction() const {
      return rational_t((m_value * ratio::num) % ratio::den, ratio::den);
   }

private:
   int64_t m_value;
}; // struct fixed_point_t

template <typename RATIO>
std::ostream& operator<<(std::ostream& out, const fixed_point_t<RATIO>& fp) {
   if /*constexpr*/ (RATIO::den == 1) {
      return out << fp.whole_number();
   } else if /*constexpr*/ ((RATIO::den % 10) == 0) {
      // TODO(tblyons): Set width of fractional component
      return out << fp.whole_number() << '.' << fp.fraction().m_numerator;
   } else {
      return out << fp.whole_number() << ' ' << fp.fraction().m_numerator << '/' << fp.fraction().m_denominator;
   }
}

} // namespace math

#endif // MATH_FIXEDPOINT_HPP