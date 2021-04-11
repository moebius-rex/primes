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
#ifndef INCLUDED_CPP_SIEVE
#define INCLUDED_CPP_SIEVE

#include <sys/time.h>
#include <vector>

#include "c/app3/sieve.h"

using namespace std;

/**
 * Computes prime numbers in a given range using an implementation of the
 * Sieve of Erastosthenes algorithm.
 * 
 * This class is a pure wrapper around the C language implementaion
 * cd in c/app3.
 */
class Sieve {
  private:
    sieve *impl;

  public:
    Sieve(int range = 0);
    ~Sieve();

    void    compute_primes();
    void    print_primes()    const;

    int*    get_primes()      const;
    int     get_range()       const;
    int     get_count()       const;
    time_t  get_elapsed()     const;
};

#endif // INCLUDED_CPP_SIEVE
