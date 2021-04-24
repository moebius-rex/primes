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

#include "csieve.h"

// allow C++ source to include C functions
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Computes prime numbers in a given range using an implementation of the
 * Sieve of Eratosthenes algorithm.
 * 
 * Extended version of csieve that adds function pointers. However,
 * data encapsulation is now broken because the csieve pointer is exposed
 * and can therefore be manipulated.
 */
typedef struct csievex_t {
  void    (*destroy)(struct csievex_t*);

  void    (*compute_primes)(struct csievex_t*);
  void    (*print_primes)(const struct csievex_t*);

  int*    (*get_primes)(const struct csievex_t*);
  int     (*get_range)(const struct csievex_t*);
  int     (*get_count)(const struct csievex_t*);
  float   (*get_elapsed)(const struct csievex_t*);

  csieve* sieve;
} csievex;

// constructor
csievex* csievex_create(int);

// allow C++ source to include C functions
#ifdef __cplusplus
}
#endif
