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
#include <iostream>

#include "sieve.h"

using namespace std;

int read_range(int range) {
  if (range == 0) {
    std::cout << "Enter highest integer to test for primeness: ";
    std::cin >> range;
  }
  return range;
}

int main(int argc, const char *argv[]) {
  cout << "Sieve of Erastosthenes: Find all prime numbers in a given range" << endl;

  int range = argc > 1 ? atoi(argv[1]) : 0;
  Sieve sieve(read_range(range));
  sieve.compute_primes();
  sieve.print_primes();

  // for valgrind
  vector<int> copy = sieve.get_primes();
  for(vector<int>::iterator it = copy.begin(); it != copy.end(); ++it) {
    int p = *it;
  }
  copy.clear();

  return 0;
}
