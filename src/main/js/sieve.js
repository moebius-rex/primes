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
"use strict";

const { _, performance } = require("perf_hooks");

// defines the number of primes to display around an ellipsis that is used
// when large numbers of primes are requested
const MAX_HALF = 10;

/**
 * Private methods
 */
function createIntegers(range) {
  const integers = new Array(range + 1).fill(true);
  integers[0] = integers[1] = false; // by convention, 0 and 1 are not primes
  return integers;
}

/**
 * Computes prime numbers in a given range using an implementation of the
 * Sieve of Eratosthenes algorithm.
 */
class Sieve {
  // private data members
  #integers
  #primes
  #start
  #end

  /**
   * Public methods
   */
  constructor(range) {
    this.#integers = createIntegers(range);
    this.#primes = new Array();
  }
  
  computePrimes() {
    this.#start = performance.now();

    // step 1. sieve: tag non-prime inputs
    this.#integers.forEach((val, p) => {
      if (val) {
        for (var i = p * p; i <= this.range; i += p) {
          if (this.#integers[i]) {
            this.#integers[i] = false;
          }
        }
      }
    });

    // step 2. add primes to output
    this.#integers.forEach((val, p) => {
      if (val) {
        this.#primes.push(p);
      }
    });
  
    this.#end = performance.now();
  }

  printPrimes() {
    console.log("Prime numbers in range 0-" + this.range + " inclusive:");
    const half = Math.floor(this.count / 2);
    this.#primes.forEach((p, n) => {
      if (half > MAX_HALF) {
        if (n == MAX_HALF) {
          process.stdout.write(".. ");
        } else if (n < MAX_HALF || n >= this.count - MAX_HALF) {
          process.stdout.write(p + " ");
        }
      } else {
        process.stdout.write(p + " ");
      }
    });
    console.log("\nFound " + this.count + " prime(s) in "
        + this.range + " integers in " + this.elapsed + " microseconds\n");
  }

  get primes() {
    return Array.from(this.#primes);
  }

  get range() {
    return this.#integers.length - 1;
  }

  get count() {
    return this.#primes.length;
  }

  get elapsed() {
    return Math.round(1e3 * (this.#end - this.#start));
  }
}

module.exports = Sieve;
