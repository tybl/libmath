#include "tbl/math/stats.hpp"

#include "doctest/doctest.h"

TEST_CASE("tbl::math::stats") {
   tbl::math::stats accum;
   for (long i = 0; i < 100; ++i) {
      accum.include(i);
      accum.include(-i);
      CHECK(accum.mean() < 0.000001);
   }
}