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
package main

import (
	"fmt"
	"os"
	"strconv"

	"github.com/moebius-rex/primes/src/main/go/sieve"
)

/*
 * Computes prime numbers in a given range using an implementation of the
 * Sieve of Eratosthenes algorithm.
 */

func readRange() (r int64, err error) {
	if len(os.Args) > 1 {
		if r, err = strconv.ParseInt(os.Args[1], 10, 0); err != nil {
			return 0, fmt.Errorf("not an integer: %v", os.Args[1])
		}
		return r, nil
	}

	fmt.Print("Enter highest integer to test for primeness: ")
	if _, err := fmt.Scanf("%d", &r); err != nil {
		return 0, fmt.Errorf("not an integer")
	}
	return r, nil
}

func main() {
	fmt.Println("Sieve of Eratosthenes: Find all prime numbers in a given range")
	r, err := readRange()
	if err != nil {
		fmt.Printf("Error: %v\n", err)
		os.Exit(1)
	}
	ps, err := sieve.NewSieve(int(r))
	if err != nil {
		fmt.Printf("Error: %v\n", err)
		os.Exit(1)
	}
	ps.ComputePrimes().PrintPrimes()
}
