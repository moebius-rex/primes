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
package sieve

import (
	"fmt"
	"time"
)

// defines the number of primes to display around an ellipsis that is used
// when large numbers of primes are requested
const MAX_HALF int = 10

type ISieve interface {
	NewSieve(r int)         // new prime computer with range r
	ComputePrimes()         // comoute all primes in range
	PrintPrimes()           // print summary of primes found in range
	Integers() []bool       // [0 < n < range] == true => prime number
	Primes() []int          // [0 < m < count] => a prime number
	PrimeMap() map[int]bool // map[m] == true => a prime number
	Range() int             // range of integers tested for primeness
	Count() int             // count of primes in range tested
	Elapsed() time.Duration // time taken to comoute primes in range
}

type Sieve struct {
	inrange  int           // range of integers in which to find primes
	integers []bool        // integer inputs, true => prime number
	primes   []int         // outputs, list of primes in inputs
	count    int           // number of primes found
	elapsed  time.Duration // time taken to complete algo, in microseconds
}

func NewSieve(r int) (s *Sieve, err error) {
	if r < 0 {
		return nil, fmt.Errorf("range is negative: %d", r)
	}
	s = new(Sieve)
	s.inrange = r
	s.integers = make([]bool, s.inrange+1)
	for i := 2; i <= s.inrange; i++ {
		s.integers[i] = true
	}
	return s, nil
}

func (s *Sieve) ComputePrimes() {
	startTime := time.Now()

	// step 1. sieve: tag non-prime inputs
	for i := 0; i*i <= s.inrange; i++ {
		if s.integers[i] {
			for j := i * i; j <= s.inrange; j += i {
				if s.integers[j] {
					s.integers[j] = false
				}
			}
		}
	}

	// step 2. add up number of primes found
	s.count = 0
	for i := 0; i <= s.inrange; i++ {
		if s.integers[i] {
			s.count++
		}
	}

	// step 3. add primes found to primes array
	s.primes = make([]int, s.count)
	count := 0
	for i := 0; i <= s.inrange; i++ {
		if s.integers[i] {
			s.primes[count] = i
			count++
		}
	}
	s.elapsed = time.Since(startTime)
}

func (s *Sieve) PrintPrimes() {
	fmt.Printf("Prime numbers in range 0-%d inclusive:\n", s.inrange)
	half := int(s.count / 2)
	for i := 0; i < s.count; i++ {
		j := s.primes[i]
		if half > MAX_HALF {
			if i == MAX_HALF {
				fmt.Print(".. ")
			} else if i < MAX_HALF || i >= s.count-MAX_HALF {
				fmt.Printf("%d ", j)
			}
		} else {
			fmt.Printf("%d ", j)
		}
	}
	fmt.Printf("\nFound %d prime(s) in %d integers in %v microseconds\n\n",
		s.count, s.inrange, s.elapsed.Nanoseconds()/1000)
}

func (s *Sieve) Integers() []bool {
	return s.integers
}

func (s *Sieve) Primes() []int {
	return s.primes
}

func (s *Sieve) PrimeMap() (pm map[int]bool) {
	pm = make(map[int]bool, s.count)
	for _, v := range s.primes {
		pm[v] = true
	}
	return pm
}

func (s *Sieve) Range() int {
	return s.inrange
}

func (s *Sieve) Count() int {
	return s.count
}

func (s *Sieve) Elapsed() time.Duration {
	return s.elapsed
}
