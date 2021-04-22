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

const readline = require("readline");
const { _, performance } = require("perf_hooks");

/**
 * Computes prime numbers in a given range using an implementation of the
 * Sieve of Eratosthenes algorithm.
 */

function main(range) {
  let integers = new Array(range + 1);
  integers.fill(true);
  integers[0] = integers[1] = false;
  let start = performance.now();
  computePrimes(integers);
  let end = performance.now();
  printPrimes(integers);
  let count = getCount(integers);
  let elapsed = getElapsed(start, end);
  console.log("\nFound " + count + " prime(s) in " + range + " integers in "
      + elapsed + " microseconds\n");
}

function computePrimes(integers) {
  integers.forEach((val, n) => {
    if (val) {
      for (var i = n * n; i <= integers.length; i += n) {
        if (integers[i]) {
          integers[i] = false;
        }
      }
    }
  });
}

function printPrimes(integers) {
  console.log("Prime numbers in range 0-" + (integers.length - 1)
      + " inclusive:");
  integers.forEach((val, p) => {
    if (val) {
      if (integers.length <= 1000 || integers.length - p <= 1000) {
        process.stdout.write(p + " ");
      }
    }
  });
}

function getCount(integers) {
  let count = 0;
  integers.forEach(p => {
    if (p) {
      count++;
    }
  });
  return count;
}

function getElapsed(start, end) {
  return Math.round(1e3 * (end - start));
}

/**
 * Read a line from standard input synchronously.
 */
function readlineSync() {
  return new Promise((resolve, reject) => {
    process.stdin.resume();
    process.stdin.on('data', function (data) {
      process.stdin.pause();
      resolve(data);
    });
  });
}

console.log("Sieve of Eratosthenes: Find all prime numbers in a given range");

if (process.argv.length > 2) {
  main(parseInt(process.argv[2]));
} else {
  let rl = readline.createInterface(process.stdin, process.stdout);
  rl.question("Enter highest integer to test for primeness: ", range => {
    main(parseInt(range));
    rl.close();
  });
}
