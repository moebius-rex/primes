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
package main

import (
	"fmt"
	"os"
	"strconv"
	"time"
)

/*
 * Computes prime numbers in a given range using an implementation of the
 * Sieve of Eratosthenes algorithm.
 */

func get_range() (r int64, err error) {
	if len(os.Args) > 1 {
		r, err = strconv.ParseInt(os.Args[1], 10, 0)
		if err != nil {
			return 0, fmt.Errorf("not an integer: %v", os.Args[1])
		}
		if r < 0 {
			return 0, fmt.Errorf("invalid range: %d", r)
		}
		return r, nil
	}

	fmt.Print("Enter highest integer to test for primeness: ")
	if _, err := fmt.Scanf("%d", &r); err != nil {
		return 0, fmt.Errorf("not an integer")
	}
	if r < 0 {
		return 0, fmt.Errorf("negative range: %d", r)
	}
	return r, nil
}

func compute_primes(r int) []bool {
	var primes = make([]bool, r+1)
	for i := 2; i <= r; i++ {
		primes[i] = true
	}
	for i := 0; i*i <= r; i++ {
		if primes[i] {
			for j := i * i; j <= r; j += i {
				if primes[j] {
					primes[j] = false
				}
			}
		}
	}
	return primes
}

func print_primes(primes []bool) {
	n := len(primes)
	fmt.Printf("Prime numbers in range 0-%d inclusive:\n", n-1)
	for p := 2; p < n; p++ {
		if primes[p] {
			if n <= 1000 || n-p <= 1000 {
				fmt.Printf("%d ", p)
			}
		}
	}
	fmt.Println()
}

func get_count(primes []bool) int {
	count := 0
	for _, p := range primes {
		if p {
			count++
		}
	}
	return count
}

func main() {
	fmt.Println("Sieve of Eratosthenes: Find all prime numbers in a given range")
	r, e := get_range()
	if e != nil {
		fmt.Printf("Error: %v\n", e)
		os.Exit(1)
	}
	start_time := time.Now()
	primes := compute_primes(int(r))
	print_primes(primes)
	count := get_count(primes)
	end_time := time.Now()
	elapsed := end_time.Sub(start_time) / 1000
	fmt.Printf("Found %d prime(s) in %d integers in %d microseconds\n\n",
		count, r, elapsed)
}
