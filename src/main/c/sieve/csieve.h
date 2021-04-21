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

// allow C++ source to include C functions
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <sys/time.h>

/**
 * Computes prime numbers in a given range using an implementation of the
 * Sieve of Eratosthenes algorithm.
 */
typedef struct csieve_t {
  int     range;           // range of integers in which to find primes
  bool*   integers;        // integer inputs, true => prime number
  int*    primes;          // outputs, list of primes in inputs
  int     count;           // number of primes found

  struct timeval
          start_time, end_time;

  void    (*destroy)(struct csieve_t*);

  void    (*compute_primes)(struct csieve_t*);
  void    (*print_primes)(const struct csieve_t*);

  int*    (*get_primes)(const struct csieve_t*);
  int     (*get_range)(const struct csieve_t*);
  int     (*get_count)(const struct csieve_t*);
  float   (*get_elapsed)(const struct csieve_t*);

} csieve;

/**
 * Non-member functions.
 * 
 * These provide limited support for implementing language bindings.
 */
csieve* csieve_create(int);
void csieve_destroy(csieve*);

void csieve_compute_primes(csieve*);
void csieve_print_primes(const csieve*);

float csieve_get_elapsed(const csieve*);

// allow C++ source to include C functions
#ifdef __cplusplus
}
#endif