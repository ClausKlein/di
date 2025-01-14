//
// Copyright (c) 2012-2020 Kris Jusiak (kris at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_DI_TEST_HPP
#define BOOST_DI_TEST_HPP

#include <cstdio>
#include <cstdlib>

#include "boost/di/aux_/compiler.hpp"

#if defined(__MSVC__)
#pragma warning(disable : 4503)
#pragma warning(disable : 4822)
#pragma warning(disable : 4505)
#define __has_include(...) 0
#endif

#define expect(...) (void)((__VA_ARGS__) || (expect_fail__(#__VA_ARGS__, __FILE__, __LINE__), 0))
#define static_expect(...) static_assert((__VA_ARGS__), "fail")

void expect_fail__(const char *msg, const char *file, int line) {
  std::printf("%s:%d:%s\n", file, line, msg);
  std::exit(-1);
}

struct test {
  template <class Test>
  test(const Test &test) {
    test();
  }
};

int main() {}

#endif
