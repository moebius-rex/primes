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
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "csieve.h"

// defines the number of primes to display around an ellipsis that is used
// when large numbers of primes are requested
static const int MAX_HALF = 10;

// define the contents of the opaque csieve_t struct declared in the header
struct csieve_t {
  int    range;               // range of integers in which to find primes
  bool*  integers;            // integer inputs, true => prime number
  int*   primes;              // outputs, list of primes in inputs
  int    count;               // number of primes found

  struct timeval start_time;  // time to complete the algo in microseconds
  struct timeval end_time;
};

/**
 * Private functions.
 */
static bool* create_integers(int range) {
  size_t size = (range + 1) * sizeof(((csieve*) 0)->integers[0]);
  bool* integers = (bool*) malloc(size);
  memset(integers, true, size);
  integers[0] = integers[1] = false; // by convention, 0 and 1 are not primes
  return integers;
}

static int* create_primes(int count) {
  size_t size = count * sizeof(((csieve*) 0)->primes[0]);
  int* primes = (int*) malloc(size);
  return primes;
}

static csieve* create_sieve(int range, bool* integers) {
  csieve* self = (csieve*) malloc(sizeof(*self));
  self->range = range;
  self->integers = integers;
  return self;
}

static void destroy_integers(csieve* self) {
  if (self->integers != NULL) {
    free(self->integers);
  }
}

static void destroy_primes(csieve* self) {
  if (self->primes != NULL) {
    free(self->primes);
  }
}

/**
 * Public functions.
 */
csieve* csieve_create(int range) {
  bool* integers = create_integers(range);
  return create_sieve(range, integers);
}

void csieve_destroy(csieve* self) {
  destroy_integers(self);
  destroy_primes(self);
  free(self);
}

void csieve_compute_primes(csieve* self) {
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

void csieve_print_primes(const csieve* self) {
  printf("Prime numbers in the range 0-%d inclusive:\n", self->range);
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
      csieve_get_count(self), csieve_get_range(self),
      csieve_get_elapsed(self));
}

int* csieve_get_primes(const csieve* self) {
  int* copy = create_primes(self->count);
  memcpy(copy, self->primes, self->count * sizeof(self->primes[0]));
  return copy;
}

int csieve_get_range(const csieve* self) {
  return self->range;
}

int csieve_get_count(const csieve* self) {
  return self->count;
}

float csieve_get_elapsed(const csieve* self) {
  return 1e6 * (self->end_time.tv_sec - self->start_time.tv_sec) +
      (self->end_time.tv_usec - self->start_time.tv_usec);
}
