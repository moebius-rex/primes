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

// allow C++ source to include C functions
#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Computes prime numbers in a given range using an implementation of the
 * Sieve of Eratosthenes algorithm.
 */
struct csieve_t;
typedef struct csieve_t csieve;

csieve *csieve_create(int);
void csieve_destroy(csieve *);

void csieve_compute_primes(csieve *);
void csieve_print_primes(const csieve *);

int *csieve_get_primes(const csieve *);
int csieve_get_range(const csieve *);
int csieve_get_count(const csieve *);
float csieve_get_elapsed(const csieve *);

// allow C++ source to include C functions
#ifdef __cplusplus
}
#endif
