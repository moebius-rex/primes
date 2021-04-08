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
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

/**
 * Computes prime numbers in a given range using an implementation of the
 * Sieve of Erastosthenes algorithm.
 */
static int read_range() {
  char buf[100];
  printf("Enter highest integer to test for primeness: ");
  fgets(buf, sizeof(buf), stdin);
  return strtol(buf, (char**) NULL, 10);
}

static void compute_primes(bool* integers, int range) {
  for (int p = 2; p * p <= range; ++p) {
    if (integers[p]) {
      for (int i = p * p; i <= range; i += p) {
        if (integers[i]) {
          integers[i] = false;
        }
      }
    }
  }
}

static void print_primes(bool* integers, int range) {
  printf("Prime numbers in range 0-%d inclusive:\n", range);
  for (int p = 2; p <= range; ++p) {
    if (integers[p]) {
      if (range <= 1000 || range - p <= 1000) {
        printf("%d ", p);
      }
    }
  }
}

static int get_count(bool* integers, int range) {
  int count = 0;
  for (int p = 2; p <= range; ++p) {
    if (integers[p]) {
      count++;
    }
  }
  return count;
}

static float get_elapsed(struct timeval* start, struct timeval* end) {
  return 1e6 * (end->tv_sec - start->tv_sec) + (end->tv_usec - start->tv_usec);
}

int main(int argc, char* argv[]) {
  printf("Sieve of Erastosthenes: Find all prime numbers in a given range\n");

  int range = argc > 1 ? atoi(argv[1]) : read_range();
  bool integers[range + 1];
  memset(integers, 1, sizeof(integers));
  struct timeval start_time;
  gettimeofday(&start_time, NULL);
  compute_primes(integers, range);
  struct timeval end_time;
  gettimeofday(&end_time, NULL);
  print_primes(integers, range);
  int count = get_count(integers, range);
  float elapsed = get_elapsed(&start_time, &end_time);
  printf("\nFound %d prime(s) in %d integers in %.0f microseconds\n\n",
      count, range, elapsed);

  return 0;
}
