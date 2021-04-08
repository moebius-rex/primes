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
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stdio.h>
#include <stdlib.h>

#include "sieve.h"

int main(int argc, char* argv[]) {
  printf("Sieve of Erastosthenes: Find all prime numbers in a given range\n");

  int range = argc > 1 ? atoi(argv[1]) : 0;
  Sieve_t* sieve = sieve_create(range);
  sieve_computePrimes(sieve);
  sieve_printPrimes(sieve);
  sieve_destroy(sieve);

  return 0;
}
