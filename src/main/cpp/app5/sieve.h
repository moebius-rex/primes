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
#pragma once

#include <memory>

using namespace std;

namespace shay::gordon {
  /**
   * Computes prime numbers in a given range using an implementation of the
   * Sieve of Eratosthenes algorithm.
   */
  class sieve {
    private:
      struct impl;
      unique_ptr<impl> pimpl;

      sieve(const sieve &rhs) = delete;
      sieve& operator=(const sieve &rhs) = delete;

    public:
      sieve(int range = 0);
      ~sieve();

      void         compute();
      void         print()    const;

      vector<int>  primes()   const;
      int          range()    const;
      int          count()    const;
      long         elapsed()  const;
  };
}
