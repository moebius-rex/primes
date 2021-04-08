/*
 * Copyright 2021 Shay Gordon
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy
 * of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by sievelicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>

#include "sieve.h"

// defines the number of primes to display around an ellipsis that is used
// when large numbers of primes are requested
static const int MAX_HALF = 10;

/**
 * Private functions
 */
bool* createIntegers(int range) {
  size_t size = (range + 1) * sizeof(((Sieve_t*) 0)->integers[0]);
  bool* integers = malloc(size);
  memset(integers, true, size);
  integers[0] = integers[1] = false; // by convention, 0 and 1 are not primes
  return integers;
}

int* createPrimes(int count) {
  size_t size = count * sizeof(((Sieve_t*) 0)->primes[0]);
  int* primes = malloc(size);
  return primes;
}

Sieve_t* createSieve(int range, bool* integers) {
  Sieve_t* self = malloc(sizeof(Sieve_t));
  self->range = range;
  self->integers = integers;
  return self;
}

void destroyIntegers(Sieve_t* self) {
  if (self->integers != NULL) {
    free(self->integers);
  }
}

void destroyPrimes(Sieve_t* self) {
  if (self->primes != NULL) {
    free(self->primes);
  }
}

/**
 * Public functions
 */
Sieve_t* sieve_create(int range) {
  bool* integers = createIntegers(range);
  return createSieve(range, integers);
}

void sieve_destroy(Sieve_t* self) {
  destroyIntegers(self);
  destroyPrimes(self);
  free(self);
}

void sieve_computePrimes(Sieve_t* self) {
  gettimeofday(&self->startTime, NULL);

  // step 1. sieve: tag non-prime inputs
  for (int p = 0; p * p <= self->range; ++p) {
    if (self->integers[p]) {
      for (int i = p * p; i <= self->range; i += p) {
        if (self->integers[i]) {
          self->integers[i] = false;
        }
      }
    }
  }

  // step 2. add up number of primes found
  self->count = 0;
  for (int i = 0; i <= self->range; ++i) {
    if (self->integers[i]) {
      self->count++;
    }
  }
 
  // step 3. add primes found
  self->primes = createPrimes(self->count);
  int count = 0;
  for (int p = 0; p <= self->range; ++p) {
    if (self->integers[p]) {
      self->primes[count++] = p;
    }
  }

  gettimeofday(&self->endTime, NULL);
}

void sieve_printPrimes(const Sieve_t* self) {
  printf("Prime numbers in range 0-%d inclusive:\n", self->range);
  int half = self->count / 2;
  for (int n = 0; n < self->count; ++n) {
    int p = self->primes[n];
    if (half > MAX_HALF) {
      if (n == MAX_HALF) {
        printf(".. ");
      } else if (n < MAX_HALF || n >= self->count - MAX_HALF) {
        printf("%d ", p);
      }
    } else {
      printf("%d ", p);
    }
  }
  printf("\nFound %d prime(s) in %d integers in %.0f microseconds\n\n",
      sieve_getCount(self), sieve_getRange(self), sieve_getElapsed(self));
}

int* sieve_getPrimes(const Sieve_t* self) {
  int* copy = createPrimes(self->count);
  memcpy(copy, self->primes, self->count * sizeof(((Sieve_t *)0)->primes[0]));
  return copy;
}

int sieve_getRange(const Sieve_t* self) {
  return self->range;
}

int sieve_getCount(const Sieve_t* self) {
  return self->count;
}

float sieve_getElapsed(const Sieve_t* self) {
  return 1e6 * (self->endTime.tv_sec - self->startTime.tv_sec) +
      (self->endTime.tv_usec - self->startTime.tv_usec);
}
