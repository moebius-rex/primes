#!/usr/bin/python3
#
# Copyright 2021 Shay Gordon
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
import sys
import time
import math

"""
Computes prime numbers in a given range using an implementation of the
Sieve of Eratosthenes algorithm.
"""

def get_range():
  return int(input("Enter highest integer to test for primality: "))

def compute_primes(n):
  prime = [True] * (n + 1)
  prime[0] = prime[1] = False
  m = int(math.sqrt(n)) + 1
  for p in range(m):
    if prime[p]:
      for i in range(p * p, n + 1, p):
        if prime[i]:
          prime[i] = False
  return prime

def print_primes(prime):
  n = len(prime)
  print(f"Prime numbers in the range 0-{n - 1:d} inclusive:")
  for p in range(n):
    if prime[p]:
      if n <= 1000 or n - p <= 1000:
        print(p, end = " ")

def main():
  print("Sieve of Eratosthenes: Find all prime numbers in a given range")
  range = 0
  if len(sys.argv) > 1:
    try:
      range = int(sys.argv[1])
    except ValueError:
      pass
  if range == 0:
    range = get_range()
  start_time = time.time()
  primes = compute_primes(range)
  elapsed = (time.time() - start_time) * 1_000_000.
  print_primes(primes)
  count = sum(primes)
  print(f"\nFound {count:d} prime(s) in {range:d} integers in {elapsed:.0f} microseconds\n")
  return 0

if __name__ == "__main__":
   sys.exit(main())
