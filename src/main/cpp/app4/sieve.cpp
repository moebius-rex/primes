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

struct sieve::impl {
  csievex* ps;
  impl(csievex* ps = csievex_create(0)) : ps(ps) {}
};

sieve::sieve(int range) {
  pimpl = std::make_unique<sieve::impl>(csievex_create(range));
}

sieve::~sieve() {
  pimpl->ps->destroy(pimpl->ps);
  pimpl.release();
}

void sieve::compute_primes() {
  pimpl->ps->compute_primes(pimpl->ps);
}

void sieve::print_primes() const {
  pimpl->ps->print_primes(pimpl->ps);
}

int* sieve::get_primes() const {
  return pimpl->ps->get_primes(pimpl->ps);
}

int sieve::get_range() const {
  return pimpl->ps->get_range(pimpl->ps);
}

int sieve::get_count() const {
  return pimpl->ps->get_count(pimpl->ps);
}

time_t sieve::get_elapsed() const {
  return pimpl->ps->get_elapsed(pimpl->ps);
}
