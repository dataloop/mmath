#include "seatest/seatest.h"
#include <inttypes.h>
#include <mmath.h>

void test_deserialize_int() {
  int64_t v = htonll(0x0100000000000006LL);
  decimal d = dec_deserialize(v);
  assert_int_equal(0, d.exponent);
  assert_long_equal(6, d.coefficient);
}

void test_serialize_int() {
  decimal d = {.exponent = 0, .coefficient = 6};
  int64_t v = ntohll(dec_serialize(d));
  assert_long_hex_equal(0x0100000000000006LL, v);
}

void test_from_big_float() {
  double v = 9223372037000250000.0;
  decimal d = dec_from_double(v);
  assert_int_equal(5, d.exponent);
  assert_long_equal(92233720370002, d.coefficient);
}

void test_deserialize_big_float() {
  int64_t v = htonll(0x020553e2d6239352LL);
  decimal d = dec_deserialize(v);
  assert_int_equal(5, d.exponent);
  assert_long_equal(92233720370002, d.coefficient);
}

void test_serialize_big_float() {
  decimal d = {.exponent = 5, .coefficient = 92233720370002};
  int64_t v = ntohll(dec_serialize(d));
  assert_long_hex_equal(0x020553e2d6239352, v);
}

void dec_conv_tests() {
  test_fixture_start();
  run_test(test_deserialize_int);
  run_test(test_serialize_int);
  run_test(test_from_big_float);
  run_test(test_deserialize_big_float);
  run_test(test_serialize_big_float);
  test_fixture_end();
}
