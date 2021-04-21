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

#include <stdbool.h>
#include <sys/time.h>

/**
 * Computes prime numbers in a given range using an implementation of the
 * sieve of Eratosthenes algorithm.
 */
typedef struct sieve_t {
  int   range;           // range of integers in which to find primes
  bool* integers;        // integer inputs, true => prime number
  int*  primes;          // outputs, list of primes in inputs
  int   count;           // number of primes found

  struct timeval
          start_time, end_time;
} sieve;

sieve*  sieve_create(int);
void    sieve_destroy(sieve*);

void    sieve_compute_primes(sieve*);
void    sieve_print_primes(const sieve*);

int*    sieve_get_primes(const sieve*);
int     sieve_get_range(const sieve*);
int     sieve_get_count(const sieve*);
float   sieve_get_elapsed(const sieve*);
