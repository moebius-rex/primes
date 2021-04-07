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
#ifndef INCLUDED_CPP_APP
#define INCLUDED_CPP_APP

#include <sys/time.h>

/**
 * Computes prime numbers in a given range using an implementation of the
 * Sieve of Erastosthenes algorithm.
 */
class App {
  private:
    int   range;
    bool* primes;

    struct timeval startTime, endTime;

  public:
    App(int range = 0);
    ~App();

    void  computePrimes();
    void  printPrimes();
  
    int   getRange();
    int   getCount();
    float getElapsed();
};

#endif // INCLUDED_CPP_APP