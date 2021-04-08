#!/usr/bin/python3
#
# Copyright 2021 Shay Gordon
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License. You may obtain a copy
# of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations
# under the License.
#
# SPDX-License-Identifier: Apache-2.0
#
import sys
import time
import math

from itertools import compress

"""
Computes prime numbers in a given range using an implementation of the
Sieve of Erastosthenes algorithm.
"""
class Sieve:
  # defines the number of primes to display around an ellipsis that is used
  # when large numbers of primes are requested
  MAX_HALF = 10

  """
  Private functions
  """
  @staticmethod
  def _createPrimes(range):
    integers = [True] * (range + 1)
    integers[0] = integers[1] = False # by convention, 0 and 1 are not primes
    return integers

  """
  Public functions
  """
  def __init__(self, range):
    self.range = range
    self.primes = self._createPrimes(self.range)

  def computePrimes(self):
    self.startTime = time.time()

    # step 1. sieve: tag non-prime inputs
    for p in range(0, math.ceil(math.sqrt(self.range))):
      if self.primes[p]:
        for i in range(p * p, self.range + 1, p):
          if self.primes[i]:
            self.primes[i] = False

    # step 2. add primes to output
    self.primes = list(compress(range(self.getCount()), self.primes))

    self.endTime = time.time()
    return self

  def printPrimes(self):
    print(f"Prime numbers in range 0-{self.range:,d} inclusive:")
    half = int(self.getCount() / 2)
    for n, p in enumerate(self.primes):
      if half > Sieve.MAX_HALF:
        if n == Sieve.MAX_HALF:
          print("..", end=" ")
        elif n < Sieve.MAX_HALF or n >= self.getCount() - Sieve.MAX_HALF:
          print(p, end=" ")
      else:
        print(p, end=" ")
    print(f"\nFound {self.getCount():,d} prime(s) in {self.range:,d} integers in "
        + f"{self.getElapsed():,.0f} microseconds\n")

  def getPrimes(self):
    return self.primes.copy()

  def getRange(self):
    return self.range

  def getCount(self):
    return len(self.primes)

  def getElapsed(self):
    return (self.endTime - self.startTime) * 1_000_000.

  def __iter__(self):
    self.index = -1
    return self

  def __next__(self):
    self.index += 1
    if self.index == self.getCount():
      raise StopIteration
    return self.primes[self.index]

if __name__ == '__main__':
    if len(sys.argv) > 1:
      range = sys.argv[1]
    else:
      range = 10
    Sieve(range).computePrimes().printPrimes()
