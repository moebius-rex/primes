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
#include <memory>
#include "csievex.h"
#include "sieve.h"

#define pp pimpl->pcsieve

struct sieve::impl {
  csievex* pcsieve;
  impl(csievex* pcsieve = csievex_create(0)) : pcsieve(pcsieve) {}
};

sieve::sieve(int range) {
  pimpl = std::make_unique<sieve::impl>(csievex_create(range));
}

sieve::~sieve() {
  pp->destroy(pp);
  pimpl.release();
}

void sieve::compute_primes() {
  pp->compute_primes(pp);
}

void sieve::print_primes() const {
  pp->print_primes(pp);
}

int* sieve::get_primes() const {
  return pp->get_primes(pp);
}

int sieve::get_range() const {
  return pp->get_range(pp);
}

int sieve::get_count() const {
  return pp->get_count(pp);
}

time_t sieve::get_elapsed() const {
  return pp->get_elapsed(pp);
}
