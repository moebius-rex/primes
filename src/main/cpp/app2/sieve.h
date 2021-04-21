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

#pragma once

#include <sys/time.h>
#include <vector>

using namespace std;

/**
 * Computes prime numbers in a given range using an implementation of the
 * Sieve of Eratosthenes algorithm.
 */
class Sieve {
  private:
    int         range;           // range of integers in which to find primes
    bool*       integers;        // integer inputs, true => prime number
    vector<int> primes;          // outputs, list of primes in inputs

    struct timeval
                start_time, end_time;

  public:
    Sieve(int range = 0);
    ~Sieve();

    void        compute_primes();
    void        print_primes()    const;

    vector<int> get_primes()      const;
    int         get_range()       const;
    time_t      get_elapsed()     const;
};
