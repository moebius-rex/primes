/*
 * Copyright 2021 Shay Gordon
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy
 * of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */
#include <stdio.h>
#include <stdlib.h>

#include "sieve.h"

int read_range(int range) {
  if (range == 0) {
    char buf[100];
    printf("Enter highest integer to test for primeness: ");
    fgets(buf, sizeof(buf), stdin);
    range = strtol(buf, (char**) NULL, 10);
  }
  return range;
}

int main(int argc, char* argv[]) {
  printf("Sieve of Erastosthenes: Find all prime numbers in a given range\n");

  int range = argc > 1 ? atoi(argv[1]) : 0;
  sieve* sieve = sieve_create(read_range(range));
  sieve_compute_primes(sieve);
  sieve_print_primes(sieve);

  // for valgrind
  int *copy = sieve_get_primes(sieve);
  for (int i = 0; i < sieve_get_count(sieve); ++i) {
    int prime = copy[i];
    (void) prime;
  }
  free(copy);

  sieve_destroy(sieve);

  return 0;
}
