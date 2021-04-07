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
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>

#include "app.h"

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
  size_t size = (range + 1) * sizeof(((App_t*) 0)->integers[0]);
  bool* integers = malloc(size);
  memset(integers, true, size);
  integers[0] = integers[1] = false; // by convention, 0 and 1 are not primes
  return integers;
}

int* createPrimes(int count) {
  size_t size = count * sizeof(((App_t*) 0)->primes[0]);
  int* primes = malloc(size);
  memset(primes, true, size);
  return primes;
}

App_t* createApp(int range, bool* integers) {
  App_t* app = malloc(sizeof(App_t));
  app->range = range;
  app->integers = integers;
  return app;
}

void destroyIntegers(App_t* app) {
  if (app->integers != NULL) {
    free(app->integers);
  }
}

void destroyPrimes(App_t* app) {
  if (app->primes != NULL) {
    free(app->primes);
  }
}

/**
 * Public functions
 */
App_t* app_create(int range) {
  range = readRange(range);
  bool* integers = createIntegers(range);
  return createApp(range, integers);
}

void app_destroy(App_t* app) {
  destroyIntegers(app);
  destroyPrimes(app);
  free(app);
}

void app_computePrimes(App_t* app) {
  gettimeofday(&app->startTime, NULL);
  for (int p = 0; p * p <= app->range; ++p) {
    if (app->integers[p]) {
      for (int i = p * p; i <= app->range; i += p) {
        if (app->integers[i]) {
          app->integers[i] = false;
        }
      }
    }
  }
  gettimeofday(&app->endTime, NULL);

  app->count = app_getCount(app);
  app->primes = createPrimes(app->count);
  int count = 0;
  for (int p = 0; p < app->range; ++p) {
    if (app->integers[p]) {
      app->primes[count++] = p;
    }
  }
}

void app_printPrimes(App_t* app) {
  printf("Prime numbers in range 0-%d inclusive:\n", app->range);
  int half = app->count / 2;
  for (int n = 0; n < app->count; ++n) {
    int p = app->primes[n];
    if (half > MAX_HALF) {
      if (n == MAX_HALF) {
        printf(".. ");
      } else if (n < MAX_HALF || n >= half * 2 - MAX_HALF) {
        printf("%d ", p);
      }
    } else {
      printf("%d ", p);
    }
  }
  printf("\nFound %d prime(s) in %d integers in %.0f microseconds\n\n",
      app_getCount(app), app_getRange(app), app_getElapsed(app));
}

int app_getRange(App_t* app) {
  return app->range;
}

int app_getCount(App_t* app) {
  int count = 0;
  for (int p = 0; p <= app->range; ++p) {
    if (app->integers[p]) {
      count++;
    }
  }
  return count;
}

float app_getElapsed(App_t* app) {
  return 1e6 * (app->endTime.tv_sec - app->startTime.tv_sec) +
      (app->endTime.tv_usec - app->startTime.tv_usec);
}
