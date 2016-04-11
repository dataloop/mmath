#include "seatest/seatest.h"
#include <inttypes.h>
#include <mmath.h>

//
// dec_add tests
//
void test_adding_simple_intergers() {
  decimal a = {.coefficient = 1, .exponent = 0};
  decimal b = {.coefficient = 2, .exponent = 0};
  decimal sum = dec_add(a, b);
  assert_ulong_equal(3, sum.coefficient);
  assert_int_equal(0, sum.exponent);
}

void test_adding_floats() {
  decimal a = {.coefficient = 125, .exponent = -2};
  decimal b = {.coefficient = 21, .exponent = 0};
  decimal sum = dec_add(a, b);
  assert_ulong_equal(2225, sum.coefficient);
  assert_int_equal(-2, sum.exponent);
}

void test_adding_with_overflow () {
  decimal a = {.coefficient = 93000000000000, .exponent = -14};
  decimal b = {.coefficient = 93000000000000, .exponent = -14};
  decimal sum = dec_add(a, b);
  assert_ulong_equal(18600000000000, sum.coefficient);
  assert_int_equal(-13, sum.exponent);
}

void test_adding_negative_float() {
  decimal a = {.coefficient = -99452189536800, .exponent = -14};
  decimal b = {.coefficient = -1, .exponent = 0};
  decimal sum = dec_add(a, b);
  assert_long_equal(-19945218953680, sum.coefficient);
  assert_int_equal(-13, sum.exponent);
}

void test_adding_int_to_negative_float () {
  decimal a = {.coefficient = -10000000000000, .exponent = -13};
  decimal b = {.coefficient = 2, .exponent = 0};
  decimal sum = dec_add(a, b);
  assert_ulong_equal(10000000000000, sum.coefficient);
  assert_int_equal(-13, sum.exponent);
}

void test_adding_float_to_zero () {
  decimal a = {.coefficient = 0, .exponent = 0};
  decimal b = {.coefficient = 10000000000000, .exponent = -14};
  decimal sum = dec_add(a, b);
  assert_ulong_equal(10000000000000, sum.coefficient);
  assert_int_equal(-14, sum.exponent);
}

void test_adding_int_to_float () {
  decimal a = {.coefficient = 100000000000000, .exponent = -14};
  decimal b = {.coefficient = 14073, .exponent = 0};
  decimal sum = dec_add(a, b);
  assert_ulong_equal(140740000000000, sum.coefficient);
  assert_int_equal(-10, sum.exponent);
}

//
// dec_div_tests
//
void test_dividing () {
  decimal a = {.coefficient = 18600000000000, .exponent = -13};
  decimal r = dec_div(a, 2);
  assert_ulong_equal(9300000000000, r.coefficient);
  assert_int_equal(-13, r.exponent);
}

void dec_math_tests() {
  test_fixture_start();
  run_test(test_adding_simple_intergers);
  run_test(test_adding_floats);
  run_test(test_adding_with_overflow);
  run_test(test_adding_negative_float);
  run_test(test_adding_int_to_negative_float);
  run_test(test_adding_float_to_zero);
  run_test(test_adding_int_to_float);
  run_test(test_dividing);
  test_fixture_end();
}
