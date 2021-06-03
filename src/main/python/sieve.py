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
import time
import math

from itertools import compress

"""
Computes prime numbers in a given range using an implementation of the
Sieve of Eratosthenes algorithm.
"""
class Sieve:
  # defines the number of primes to display around an ellipsis that is used
  # when large numbers of primes are requested
  MAX_HALF = 10

  """
  Private functions
  """
  @staticmethod
  def _create_primes(range):
    integers = [True] * (range + 1)
    integers[0] = integers[1] = False # by convention, 0 and 1 are not primes
    return integers

  """
  Public functions
  """
  def __init__(self, range):
    self.range = range
    self.primes = self._create_primes(self.range)

  def compute_primes(self):
    self.start_time = time.time()

    # step 1. sieve: tag non-prime inputs
    m = int(math.sqrt(self.range)) + 1
    for p in range(m):
      if self.primes[p]:
        for i in range(p * p, self.range + 1, p):
          if self.primes[i]:
            self.primes[i] = False

    # step 2. add primes to output
    self.primes = list(compress(range(self.get_count()), self.primes))

    self.end_time = time.time()
    return self

  def print_primes(self):
    print(f"Prime numbers in the range 0-{self.range:d} inclusive:")
    half = int(self.get_count() / 2)
    for n, p in enumerate(self.primes):
      if half > Sieve.MAX_HALF:
        if n == Sieve.MAX_HALF:
          print("..", end=" ")
        elif n < Sieve.MAX_HALF or n >= self.get_count() - Sieve.MAX_HALF:
          print(p, end=" ")
      else:
        print(p, end=" ")
    print(f"\nFound {self.get_count():d} prime(s) in {self.range:d} integers in "
        + f"{self.get_elapsed():.0f} microseconds\n")

  def get_primes(self):
    return self.primes.copy()

  def get_range(self):
    return self.range

  def get_count(self):
    return len(self.primes)

  def get_elapsed(self):
    return (self.end_time - self.start_time) * 1_000_000.

  def __iter__(self):
    self.index = -1
    return self

  def __next__(self):
    self.index += 1
    if self.index == self.get_count():
      raise StopIteration
    return self.primes[self.index]
