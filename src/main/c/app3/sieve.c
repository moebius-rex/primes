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
static bool* create_integers(int range) {
  size_t size = (range + 1) * sizeof(((sieve*) 0)->integers[0]);
  bool* integers = malloc(size);
  memset(integers, true, size);
  integers[0] = integers[1] = false; // by convention, 0 and 1 are not primes
  return integers;
}

static int* create_primes(int count) {
  size_t size = count * sizeof(((sieve*) 0)->primes[0]);
  int* primes = malloc(size);
  return primes;
}

static void destroy_integers(sieve* self) {
  if (self->integers != NULL) {
    free(self->integers);
  }
}

static void destroy_primes(sieve* self) {
  if (self->primes != NULL) {
    free(self->primes);
  }
}

/**
 * Static, private implementations of public member functions
 */
static void destroy(sieve* self) {
  destroy_integers(self);
  destroy_primes(self);
  free(self);
}

static void compute_primes(sieve* self) {
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

static void print_primes(const sieve* self) {
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
      self->get_count(self), self->get_range(self), self->get_elapsed(self));
}

static int* get_primes(const sieve* self) {
  int* copy = create_primes(self->count);
  memcpy(copy, self->primes, self->count * sizeof(((sieve *)0)->primes[0]));
  return copy;
}

static int get_range(const sieve* self) {
  return self->range;
}

static int get_count(const sieve* self) {
  return self->count;
}

static float get_elapsed(const sieve* self) {
  return 1e6 * (self->end_time.tv_sec - self->start_time.tv_sec) +
      (self->end_time.tv_usec - self->start_time.tv_usec);
}

/* internal initializer */
static sieve* sieve_init(sieve* self, int range) {
  /* initialize struct data */
  self->range = range;
  self->integers = create_integers(self->range);

  /* bind struct function pointers */
  self->destroy = &destroy;
  self->compute_primes = &compute_primes;
  self->print_primes = &print_primes;
  self->get_primes = &get_primes;
  self->get_range = &get_range;
  self->get_count = &get_count;
  self->get_elapsed = &get_elapsed;

  return self;
}

/**
 * Public non-member functions
 */
sieve* sieve_create(int range) {
  return sieve_init((sieve*) calloc(sizeof(sieve), 1), range);
}
