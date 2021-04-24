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
#include <stdlib.h>
#include <string.h>

#include "csievex.h"

/**
 * Static, private implementations of public member functions
 */
static void destroy(csievex* self) {
  csieve_destroy(self->sieve);
  free(self);
}

static void compute_primes(csievex* self) {
  csieve_compute_primes(self->sieve);
}

static void print_primes(const csievex* self) {
  csieve_print_primes(self->sieve);
}

static int* get_primes(const csievex* self) {
  return csieve_get_primes(self->sieve);
}

static int get_range(const csievex* self) {
  return csieve_get_range(self->sieve);
}

static int get_count(const csievex *self) {
  return csieve_get_count(self->sieve);
}

static float get_elapsed(const csievex* self) {
  return csieve_get_elapsed(self->sieve);
}

/* internal initializer */
static csievex* init(csievex* self, int range) {
  /* create a csieve object to hold all state */
  self->sieve = csieve_create(range);

  /* bind struct function pointers */
  self->destroy = destroy;
  self->compute_primes = compute_primes;
  self->print_primes = print_primes;
  self->get_primes = get_primes;
  self->get_range = get_range;
  self->get_count = get_count;
  self->get_elapsed = get_elapsed;

  return self;
}

/**
 * Non-member functions for creating language bindings
 */
csievex* csievex_create(int range) {
  return init((csievex*) calloc(1, sizeof(csievex)), range);
}
