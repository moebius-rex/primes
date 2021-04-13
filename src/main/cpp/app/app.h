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
#ifndef INCLUDED_CPP_APP
#define INCLUDED_CPP_APP

#include <sys/time.h>

/**
 * Computes prime numbers in a given range using an implementation of the
 * Sieve of Eratosthenes algorithm.
 */
class App {
  private:
    int   range;
    bool* primes;

    struct timeval start_time, end_time;

  public:
    App(int range = 0);
    ~App();

    void  compute_primes();
    void  print_primes();

    int   get_range();
    int   get_count();
    float get_elapsed();
};

#endif // INCLUDED_CPP_APP
