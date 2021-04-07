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
"use strict";

const Sieve = require("./sieve.js");

/**
 * Computes prime numbers in a given range using an implementation of the
 * Sieve of Erastosthenes algorithm.
 */

function main(range) {
  let sieve = new Sieve(parseInt(range));
  sieve.computePrimes();
  sieve.printPrimes();
}

console.log("Sieve of Erastosthenes: Find all prime numbers in a given range");
if (process.argv.length > 2) {
  main(process.argv[2]);
} else {
  process.stdout.write("Enter highest integer to test for primeness: ");
  process.stdin.on('data', data => {
    process.stdin.pause();
    main(data);
  });
}
