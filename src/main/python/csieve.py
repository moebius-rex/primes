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

from ctypes import *

##
# Partial implementation of Python language bindings around the sieve algo
# implementation in src/main/c/sieve/. Partial, because rather than trying to
# figure out how to map the contents of the csieve struct, including "member"
# function pointers, we just added non-member versions of a subset of the
# functions that are much easier to map using Python's ctypes module.
##

# define class that maps non-member csieve struct functions between C and
# python. could be used to map member functions but this is trickier
class _CSieve(Structure):
  pass

# import sieve shared object and define non-member function signatures
csieve = CDLL("libcsieve.so")
csieve.csieve_create.argtypes = [
	c_int	 # the range of integers
]
csieve.csieve_create.restype = POINTER(_CSieve)

csieve.csieve_destroy.argtypes = [
	POINTER(_CSieve)  # self
]
csieve.csieve_destroy.restype = None

csieve.csieve_compute_primes.argtypes = [
	POINTER(_CSieve)  # self
]
csieve.csieve_compute_primes.restype = None

csieve.csieve_print_primes.argtypes = [
	POINTER(_CSieve)  # self
]
csieve.csieve_print_primes.restype = None

csieve.csieve_get_primes.argtypes = [
	POINTER(_CSieve)  # self
]
csieve.csieve_get_primes.restype = POINTER(c_int)

csieve.csieve_get_range.argtypes = [
	POINTER(_CSieve)  # self
]
csieve.csieve_get_range.restype = c_int

csieve.csieve_get_count.argtypes = [
	POINTER(_CSieve)  # self
]
csieve.csieve_get_count.restype = c_int

csieve.csieve_get_elapsed.argtypes = [
	POINTER(_CSieve)  # self
]
csieve.csieve_get_elapsed.restype = c_float

"""
Computes prime numbers in a given range using an implementation of the
Sieve of Eratosthenes algorithm.
"""
class CSieve:
	def __init__(self, range):
		self.impl = csieve.csieve_create(range).contents

	def destroy(self):
		csieve.csieve_destroy(self.impl)

	def compute_primes(self):
		csieve.csieve_compute_primes(self.impl)

	def print_primes(self):
		csieve.csieve_print_primes(self.impl)

	def get_primes(self):
		return csieve.csieve_get_primes(self.impl)

	def get_range(self):
		return csieve.csieve_get_range(self.impl)

	def get_count(self):
		return csieve.csieve_get_count(self.impl)

	def get_elapsed(self):
		return csieve.csieve_get_elapsed(self.impl)
