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
 */
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sieve.h"

// defines the number of primes to display around an ellipsis that is used
// when large numbers of primes are requested
static const int MAX_HALF = 10;

/**
 * Private functions
 */
bool* create_integers(int range) {
  size_t size = (range + 1) * sizeof(((sieve*) 0)->integers[0]);
  bool* integers = malloc(size);
  memset(integers, true, size);
  integers[0] = integers[1] = false; // by convention, 0 and 1 are not primes
  return integers;
}

int* create_primes(int count) {
  size_t size = count * sizeof(((sieve*) 0)->primes[0]);
  int* primes = malloc(size);
  return primes;
}

sieve* create_sieve(int range, bool* integers) {
  sieve* self = malloc(sizeof(sieve));
  self->range = range;
  self->integers = integers;
  return self;
}

void destroy_integers(sieve* self) {
  if (self->integers != NULL) {
    free(self->integers);
  }
}

void destroy_primes(sieve* self) {
  if (self->primes != NULL) {
    free(self->primes);
  }
}

/**
 * Public functions
 */
sieve* sieve_create(int range) {
  bool* integers = create_integers(range);
  return create_sieve(range, integers);
}

void sieve_destroy(sieve* self) {
  destroy_integers(self);
  destroy_primes(self);
  free(self);
}

void sieve_compute_primes(sieve* self) {
  gettimeofday(&self->start_time, NULL);

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
  self->primes = create_primes(self->count);
  int count = 0;
  for (int p = 0; p <= self->range; ++p) {
    if (self->integers[p]) {
      self->primes[count++] = p;
    }
  }

  gettimeofday(&self->end_time, NULL);
}

void sieve_print_primes(const sieve* self) {
  setlocale(LC_NUMERIC, "");
  printf("Prime numbers in range 0-%'d inclusive:\n", self->range);
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
  printf("\nFound %'d prime(s) in %'d integers in %'.0f microseconds\n\n",
      sieve_get_count(self), sieve_get_range(self), sieve_get_elapsed(self));
}

int* sieve_get_primes(const sieve* self) {
  int* copy = create_primes(self->count);
  memcpy(copy, self->primes, self->count * sizeof(((sieve *)0)->primes[0]));
  return copy;
}

int sieve_get_range(const sieve* self) {
  return self->range;
}

int sieve_get_count(const sieve* self) {
  return self->count;
}

float sieve_get_elapsed(const sieve* self) {
  return 1e6 * (self->end_time.tv_sec - self->start_time.tv_sec) +
      (self->end_time.tv_usec - self->start_time.tv_usec);
}
