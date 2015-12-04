#include <stdio.h>

#include "seatest/seatest.h"

// TODO: consider converting to some simpler framework, maybe minunit

void dec_math_tests();
void all_tests();

void all_tests() {
  dec_math_tests();
}

int main(int argc, char** argv) {
  run_tests(all_tests);
}
