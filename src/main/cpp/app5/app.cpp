/*
 * Copyright 2021 Shay Gordon
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <iomanip>
#include <iostream>
#include <vector>

#include "sieve.h"

using namespace std;
using namespace shay::gordon;

static int read_range(int range) {
  if (range == 0) {
    cout << "Enter highest integer to test for primality: "; cin >> range;
  }
  return range;
}

int main(int argc, const char *argv[]) {
  cout << "Sieve of Eratosthenes: Find all prime numbers in a given range"
       << endl;

  int range = argc > 1 ? stol(argv[1]) : 0;
  sieve sieve(read_range(range));
  sieve.compute();
  sieve.print();

  // for valgrind
  for (int i : sieve.primes()) {
    cout << setw(3) << i << ' ';
  }
  cout << endl;

  return 0;
}
