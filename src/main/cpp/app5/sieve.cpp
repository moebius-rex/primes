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
#include <chrono>
#include <iostream>
#include <numeric>
#include <vector>

#include "sieve.h"

using namespace chrono;
using namespace std;

using namespace shay::gordon;

/**
 * Private constants
 */
namespace {
  // defines the number of primes to display around an ellipsis that is used
  // when large numbers of primes are requested
  constexpr int MAX_HALF = 10;
}

/**
 * Private declarations
 */
struct sieve::impl {
  private:
    int          m_range;    // range of integers in which to find primes
    vector<bool> m_integers; // integer inputs, true => prime number
    vector<int>  m_primes;   // outputs, list of primes in input range

    steady_clock::time_point m_start; // time taken to execute the algo
    steady_clock::time_point m_end;

  public:
    impl(int range = 0);

    void         compute();
    void         print()    const;

    vector<int>  primes()   const;
    int          range()    const;
    int          count()    const;
    time_t       elapsed()  const;
};

/**
 * Private implementation
 */
sieve::impl::impl(int range): m_range(range), m_integers(range + 1, true) {
  if (range < 0) {
    throw invalid_argument("negative range: " + to_string(range));
  }
  m_integers[0] = m_integers[1] = false; // by convention, 0 and 1 are not primes
}

void sieve::impl::compute() {
  m_start = steady_clock::now();

  // step 1. sieve: tag non-prime inputs
  for (int p = 0; p * p <= m_range; ++p) {
    if (m_integers[p]) {
      for (int i = p * p; i <= m_range; i += p) {
        if (m_integers[i]) {
          m_integers[i] = false;
        }
      }
    }
  }

  // step 2. add up number of primes found
  int count = accumulate(m_integers.begin(), m_integers.end(), 0);
 
  // step 3. add primes to output
  m_primes.reserve(count);
  for (int p = 0; p <= m_range; ++p) {
    if (m_integers[p]) {
      m_primes.push_back(p);
    }
  }

  m_end = steady_clock::now();
}

void sieve::impl::print() const {
  cout << "Prime numbers in the range 0-" << m_range << " inclusive:" << endl;
  int half = m_primes.size() / 2;
  for (size_t n = 0; n < m_primes.size(); ++n) {
    int p = m_primes[n];
    if (half > MAX_HALF) {
      if (n == MAX_HALF) {
        cout << ".. ";
      } else if (n < MAX_HALF || n >= m_primes.size() - MAX_HALF) {
        cout << p << ' ';
      }
    } else {
      cout << p << ' ';
    }
  }
  cout << endl
       << "Found " << m_primes.size() << " prime(s) in "
       << range() << " integers in "
       << elapsed() << " microseconds\n"
       << endl;
}

vector<int> sieve::impl::primes() const {
  return m_primes;
}

int sieve::impl::range() const {
  return m_range;
}

int sieve::impl::count() const {
  return m_primes.size();
}

long sieve::impl::elapsed() const {
  return duration_cast<microseconds>(m_end - m_start).count();
}

/**
 * Public implementation
 */
sieve::sieve(int range) {
  pimpl = make_unique<sieve::impl>(range);
}

sieve::~sieve() {
}

void sieve::compute() {
  pimpl->compute();
}

void sieve::print() const {
  pimpl->print();
}

vector<int> sieve::primes() const {
  return pimpl->primes();
}

int sieve::range() const {
  return pimpl->range();
}

int sieve::count() const {
  return pimpl->count();
}

time_t sieve::elapsed() const {
  return pimpl->elapsed();
}
