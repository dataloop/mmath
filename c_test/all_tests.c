#include <stdio.h>

#include "cutest/cutest.h"

// TODO: consider converting to some simpler framework, maybe minunit

CuSuite* get_dec_math_suite();
void run_all_tests();

void run_all_tests() {
  CuString *output = CuStringNew();
  CuSuite* suite = CuSuiteNew();

  CuSuiteAddSuite(suite, get_dec_math_suite());

  CuSuiteRun(suite);
  CuSuiteSummary(suite, output);
  CuSuiteDetails(suite, output);
  printf("%s\n", output->buffer);
}

int main(void) {
  run_all_tests();
}
