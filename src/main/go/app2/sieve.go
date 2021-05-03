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
