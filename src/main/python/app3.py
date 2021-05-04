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

from csieve import CSieve

def read_range(range):
	if (range == 0):
		range = int(input("Enter highest integer to test for primeness: "))
	return range

def main():
	print("Sieve of Eratosthenes: Find all prime numbers in a given range")

	range = 0
	if len(sys.argv) > 1:
		try:
			range = int(sys.argv[1])
		except ValueError:
			pass

	csieve = CSieve(read_range(range))
	csieve.compute_primes()
	csieve.print_primes()
	csieve.destroy()

	return 0

if __name__ == "__main__":
	sys.exit(main())
