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
#include <cstddef>
#include <iostream>

#include "app.h"

/**
 * Private functions
 */
bool* create_integers(int range) {
  bool* integers = new bool[range + 1];
  for (int p = 0; p <= range; ++p) {
    integers[p] = true;
  }
  integers[0] = integers[1] = false; // by convention, 0 and 1 are not primes
  return integers;
}

/**
 * Public functions
 */
App::App(int range) {
  this->range = range;
  this->primes = create_integers(this->range);
}

App::~App() {
  if (this->primes != NULL) {
    delete[] this->primes;
  }
}

void App::compute_primes() {
  gettimeofday(&this->start_time, NULL);
  for (int p = 0; p * p <= this->range; ++p) {
    if (this->primes[p]) {
      for (int i = p * p; i <= this->range; i += p) {
        if (this->primes[i]) {
          this->primes[i] = false;
        }
      }
    }
  }
  gettimeofday(&this->end_time, NULL);
}

void App::print_primes() {
  std::cout << "Prime numbers in range 0-" << this->range << " inclusive:" << std::endl;
  for (int p = 0; p <= this->range; ++p) {
    if (this->primes[p]) {
      if (this->range <= 1000 || this->range - p <= 1000) {
        std::cout << p << " ";
      }
    }
  }
  std::cout << std::endl
            << "Found " << this->get_count()
            << " prime(s) in " << this->get_range()
            << " integers in " << this->get_elapsed() << " microseconds\n"
            << std::endl;
}

int App::get_range() {
  return this->range;
}

int App::get_count() {
  int count = 0;
  for (int p = 0; p <= this->range; ++p) {
    if (this->primes[p]) {
      count++;
    }
  }
  return count;
}

float App::get_elapsed() {
  return 1e6 * (this->end_time.tv_sec - this->start_time.tv_sec) +
      (this->end_time.tv_usec - this->start_time.tv_usec);
}
