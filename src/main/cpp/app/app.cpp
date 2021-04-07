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
#include <cstddef>
#include <iostream>

#include "app.h"

/**
 * Private functions
 */
int readRange(int range) {
  if (range == 0) {
    std::cout << "Enter highest integer to test for primeness: ";
    std::cin >> range;
  }
  return range;
}

bool* createIntegers(int range) {
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
  this->range = readRange(range);
  this->primes = createIntegers(this->range);
}

App::~App() {
  if (this->primes != NULL) {
    delete[] this->primes;
  }
}

void App::computePrimes() {
  gettimeofday(&this->startTime, NULL);
  for (int p = 0; p * p <= this->range; ++p) {
    if (this->primes[p]) {
      for (int i = p * p; i <= this->range; i += p) {
        if (this->primes[i]) {
          this->primes[i] = false;
        }
      }
    }
  }
  gettimeofday(&this->endTime, NULL);
}

void App::printPrimes() {
  std::cout << "Prime numbers in range 0-" << this->range << " inclusive:" << std::endl;
  for (int p = 0; p <= this->range; ++p) {
    if (this->primes[p]) {
      if (this->range <= 1000 || this->range - p <= 1000) {
        std::cout << p << " ";
      }
    }
  }
  std::cout << std::endl
            << "Found " << this->getCount()
            << " prime(s) in " << this->getRange()
            << " integers in " << this->getElapsed() << " microseconds\n"
            << std::endl;
}

int App::getRange() {
  return this->range;
}

int App::getCount() {
  int count = 0;
  for (int p = 0; p <= this->range; ++p) {
    if (this->primes[p]) {
      count++;
    }
  }
  return count;
}

float App::getElapsed() {
  return 1e6 * (this->endTime.tv_sec - this->startTime.tv_sec) +
      (this->endTime.tv_usec - this->startTime.tv_usec);
}
