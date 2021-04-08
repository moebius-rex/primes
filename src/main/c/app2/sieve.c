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
int readRange(int range) {
  if (range == 0) {
    char buf[100];
    printf("Enter highest integer to test for primeness: ");
    fgets(buf, sizeof(buf), stdin);
    range = strtol(buf, (char**) NULL, 10);
  }
  return range;
}

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
  Sieve_t* sieve = malloc(sizeof(Sieve_t));
  sieve->range = range;
  sieve->integers = integers;
  return sieve;
}

void destroyIntegers(Sieve_t* sieve) {
  if (sieve->integers != NULL) {
    free(sieve->integers);
  }
}

void destroyPrimes(Sieve_t* sieve) {
  if (sieve->primes != NULL) {
    free(sieve->primes);
  }
}

/**
 * Public functions
 */
Sieve_t* sieve_create(int range) {
  range = readRange(range);
  bool* integers = createIntegers(range);
  return createSieve(range, integers);
}

void sieve_destroy(Sieve_t* sieve) {
  destroyIntegers(sieve);
  destroyPrimes(sieve);
  free(sieve);
}

void sieve_computePrimes(Sieve_t* sieve) {
  gettimeofday(&sieve->startTime, NULL);

  // step 1. sieve: tag non-prime inputs
  for (int p = 0; p * p <= sieve->range; ++p) {
    if (sieve->integers[p]) {
      for (int i = p * p; i <= sieve->range; i += p) {
        if (sieve->integers[i]) {
          sieve->integers[i] = false;
        }
      }
    }
  }

  // step 2. add up number of primes found
  sieve->count = 0;
  for (int i = 0; i <= sieve->range; ++i) {
    if (sieve->integers[i]) {
      sieve->count++;
    }
  }
 
  // step 3. add primes found
  sieve->primes = createPrimes(sieve->count);
  int count = 0;
  for (int p = 0; p <= sieve->range; ++p) {
    if (sieve->integers[p]) {
      sieve->primes[count++] = p;
    }
  }

  gettimeofday(&sieve->endTime, NULL);
}

void sieve_printPrimes(const Sieve_t* sieve) {
  printf("Prime numbers in range 0-%d inclusive:\n", sieve->range);
  int half = sieve->count / 2;
  for (int n = 0; n < sieve->count; ++n) {
    int p = sieve->primes[n];
    if (half > MAX_HALF) {
      if (n == MAX_HALF) {
        printf(".. ");
      } else if (n < MAX_HALF || n >= sieve->count - MAX_HALF) {
        printf("%d ", p);
      }
    } else {
      printf("%d ", p);
    }
  }
  printf("\nFound %d prime(s) in %d integers in %.0f microseconds\n\n",
      sieve_getCount(sieve), sieve_getRange(sieve), sieve_getElapsed(sieve));
}

int* sieve_getPrimes(const Sieve_t* sieve) {
  int* copy = createPrimes(sieve->count);
  memcpy(copy, sieve->primes, sieve->count * sizeof(((Sieve_t *)0)->primes[0]));
  return copy;
}

int sieve_getRange(const Sieve_t* sieve) {
  return sieve->range;
}

int sieve_getCount(const Sieve_t* sieve) {
  return sieve->count;
}

float sieve_getElapsed(const Sieve_t* sieve) {
  return 1e6 * (sieve->endTime.tv_sec - sieve->startTime.tv_sec) +
      (sieve->endTime.tv_usec - sieve->startTime.tv_usec);
}
