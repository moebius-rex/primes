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
#include "sieve.h"

sieve::sieve(int range) {
  this->impl = csievex_create(range);
}

sieve::~sieve() {
  this->impl->destroy(this->impl);
}

void sieve::compute_primes() {
  this->impl->compute_primes(this->impl);
}

void sieve::print_primes() const {
  this->impl->print_primes(this->impl);
}

int* sieve::get_primes() const {
  return this->impl->get_primes(this->impl);
}

int sieve::get_range() const {
  return this->impl->get_range(this->impl);
}

int sieve::get_count() const {
  return this->impl->get_count(this->impl);
}

time_t sieve::get_elapsed() const {
  return this->impl->get_elapsed(this->impl);
}
