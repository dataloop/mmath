#include "cutest/cutest.h"
#include <inttypes.h>
#include <mmath.h>

//
// dec_add tests
//
void test_adding_simple_intergers(CuTest *tc) {
  decimal a = {.coefficient = 1, .exponent = 0};
  decimal b = {.coefficient = 2, .exponent = 0};
  decimal sum = dec_add(a, b);
  CuAssertIntEquals(tc, 3, sum.coefficient);
  CuAssertIntEquals(tc, 0, sum.exponent);
}

void test_adding_floats(CuTest *tc) {
  decimal a = {.coefficient = 125, .exponent = -2};
  decimal b = {.coefficient = 21, .exponent = 0};
  decimal sum = dec_add(a, b);
  CuAssertIntEquals(tc, 2225, sum.coefficient);
  CuAssertIntEquals(tc, -2, sum.exponent);
}

void test_adding_with_overflow (CuTest *tc) {
  decimal a = {.coefficient = 93000000000000, .exponent = -14};
  decimal b = {.coefficient = 93000000000000, .exponent = -14};
  decimal sum = dec_add(a, b);
  CuAssertLongEquals(tc, 18600000000000, sum.coefficient);
  CuAssertLongEquals(tc, -13, sum.exponent);
}

void test_dividing (CuTest *tc) {
  decimal a = {.coefficient = 18600000000000, .exponent = -13};
  decimal r = dec_div(a, 2);
  CuAssertLongEquals(tc, 9300000000000, r.coefficient);
  CuAssertLongEquals(tc, -13, r.exponent);  
}

CuSuite *get_dec_math_suite() {
  CuSuite* suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, test_adding_simple_intergers);
  SUITE_ADD_TEST(suite, test_adding_floats);  
  SUITE_ADD_TEST(suite, test_adding_with_overflow);
  SUITE_ADD_TEST(suite, test_dividing);
  return suite;
}
