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
#ifndef INCLUDED_C_SIEVE
#define INCLUDED_C_SIEVE

#include <stdbool.h>
#include <sys/time.h>

/**
 * Computes prime numbers in a given range using an implementation of the
 * Sieve of Erastosthenes algorithm.
 */
typedef struct sieve_t {
  int     range;           // range of integers in which to find primes
  bool*   integers;        // integer inputs, true => prime number
  int*    primes;          // outputs, list of primes in inputs
  int     count;           // number of primes found

  struct timeval
          start_time, end_time;
} Sieve_t;

Sieve_t*  sieve_create(int);
void      sieve_destroy(Sieve_t*);

void      sieve_compute_primes(Sieve_t*);
void      sieve_print_primes(const Sieve_t*);

int*      sieve_get_primes(const Sieve_t*);
int       sieve_get_range(const Sieve_t*);
int       sieve_get_count(const Sieve_t*);
float     sieve_get_elapsed(const Sieve_t*);

#endif // INCLUDED_C_SIEVE
