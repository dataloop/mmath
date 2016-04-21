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

void dec_conv_tests() {
  test_fixture_start();
  run_test(test_deserialize_int);
  run_test(test_serialize_int);
  test_fixture_end();
}
