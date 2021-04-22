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

// defines the number of primes to display around an ellipsis that is used
// when large numbers of primes are requested
static const int MAX_HALF = 10;

/**
 * Private functions
 */
bool* create_integers(int range) {
  bool* integers = new bool[range + 1];
  std::fill_n(integers, range + 1, true);
  integers[0] = integers[1] = false; // by convention, 0 and 1 are not primes
  return integers;
}

/**
 * Public functions
 */
Sieve::Sieve(int range) {
  this->range = range;
  this->integers = create_integers(this->range);
}

Sieve::~Sieve() {
  if (this->integers != NULL) {
    delete[] this->integers;
  }
  this->primes.clear();
}

void Sieve::compute_primes() {
  gettimeofday(&this->start_time, NULL);

  // step 1. sieve: tag non-prime inputs
  for (int p = 0; p * p <= this->range; p++) {
    if (this->integers[p]) {
      for (int i = p * p; i <= this->range; i += p) {
        if (this->integers[i]) {
          this->integers[i] = false;
        }
      }
    }
  }

  // step 2. add up number of primes found
  int count = 0;
  for (int i = 0; i <= this->range; ++i) {
    if (this->integers[i]) {
      count++;
    }
  }
 
  // step 3. add primes to output
  this->primes.reserve(count);
  for (int p = 0; p <= this->range; ++p) {
    if (this->integers[p]) {
      primes.push_back(p);
    }
  }
  gettimeofday(&this->end_time, NULL);
}

void Sieve::print_primes() const {
  std::cout.imbue(std::locale(""));
  std::cout << "Prime numbers in range 0-" << this->range << " inclusive:" << std::endl;
  int half = this->primes.size() / 2;
  for (size_t n = 0; n < this->primes.size(); n++) {
    int p = this->primes.at(n);
    if (half > MAX_HALF) {
      if (n == MAX_HALF) {
        std::cout << ".. ";
      } else if (n < MAX_HALF || n >= this->primes.size() - MAX_HALF) {
        std::cout << p << ' ';
      }
    } else {
      std::cout << p << ' ';
    }
  }
  std::cout << std::endl
            << "Found " << this->primes.size() << " prime(s) in "
            << this->get_range() << " integers in "
            << this->get_elapsed() << " microseconds\n"
            << std::endl;
}

vector<int> Sieve::get_primes() const {
  // todo: verify that vector is *copied* to caller, return a copy
  // if it returns a reference
  return this->primes;
}

int Sieve::get_range() const {
  return this->range;
}

time_t Sieve::get_elapsed() const {
  return 1e6 * (this->end_time.tv_sec - this->start_time.tv_sec) +
      (this->end_time.tv_usec - this->start_time.tv_usec);
}
