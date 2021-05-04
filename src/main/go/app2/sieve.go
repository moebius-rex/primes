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

// #cgo CFLAGS: -I/usr/local/include -Wall
// #cgo LDFLAGS: -L/usr/local/lib -lcsieve
// #include "stdlib.h"
// #include "csieve.h"
import "C"

type Sieve = C.csieve

func sieve_create(r int) *Sieve {
	return (*Sieve)(C.csieve_create(C.int(r)))
}

func sieve_destroy(sieve *Sieve) {
	C.csieve_destroy(sieve)
}

func sieve_compute_primes(sieve *Sieve) {
	C.csieve_compute_primes(sieve)
}

func sieve_print_primes(sieve *Sieve) {
	C.csieve_print_primes(sieve)
}

func sieve_get_range(sieve *Sieve) int {
	return int(C.csieve_get_range(sieve))
}

func sieve_get_count(sieve *Sieve) int {
	return int(C.csieve_get_count(sieve))
}

func sieve_get_elapsed(sieve *Sieve) float32 {
	return float32(C.csieve_get_elapsed(sieve))
}
