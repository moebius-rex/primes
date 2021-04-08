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
class App2:
  # defines the number of primes to display around an ellipsis that is used
  # when large numbers of primes are requested
  MAX_HALF = 10

  """
  Private functions
  """
  @staticmethod
  def _readRange(range):
    if (range == 0):
      range = int(input("Enter highest integer to test for primeness: "))
    return range

  @staticmethod
  def _createPrimes(range):
    return [True] * (range + 1)

  """
  Public functions
  """
  def __init__(self, range):
    self.range = self._readRange(range)
    self.primes = self._createPrimes(self.range)

  def computePrimes(self):
    self.startTime = time.time()
    for p in range(2, math.ceil(math.sqrt(self.range))):
      if self.primes[p]:
        for i in range(p * p, self.range + 1, p):
          if self.primes[i]:
            self.primes[i] = False
    self.endTime = time.time()
    self.primes = list(compress(range(len(self.primes)), self.primes))[2:]

  def getPrimes(self):
    return self.primes.copy()

  def getRange(self):
    return self.range

  def getElapsed(self):
    return (self.endTime - self.startTime) * 1_000_000.

  def printPrimes(self):
    print(f"Prime numbers in range 0-{self.range:,d} inclusive:")
    half = len(self.primes) / 2
    for n, p in enumerate(self.primes):
      if half > App2.MAX_HALF:
        if n == App2.MAX_HALF:
          print("..", end = " ")
        elif n < App2.MAX_HALF or n > half * 2 - App2.MAX_HALF:
          print(p, end = " ")
      else:
        print(p, end = " ")
    print(f"\nFound {len(self.primes):,d} prime(s) in {self.range:,d} integers in {self.getElapsed():,.0f} microseconds\n")

  def __iter__(self):
    self.index = -1
    return self

  def __next__(self):
    self.index += 1
    if self.index == len(self.primes):
      raise StopIteration
    return self.primes[self.index]

"""
Main entry point
"""
def main():
  print("Sieve of Erastosthenes: Find all prime numbers in a given range")

  range = 0
  if len(sys.argv) > 1:
    try:
      range = int(sys.argv[1])
    except ValueError:
      pass
  app = App2(range)
  app.computePrimes()
  app.printPrimes()

  return 0

if __name__ == "__main__":
   sys.exit(main())
