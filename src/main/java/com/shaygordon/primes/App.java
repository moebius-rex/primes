/*
 * Copyright 2021 Shay Gordon
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.shaygordon.primes;

import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.InputMismatchException;
import java.util.Scanner;

/**
 * Computes prime numbers in a given range using an implementation of the
 * Sieve of Eratosthenes algorithm.
 */
public class App {
  private static int getRange() {
    int range = 0;
    System.out.print("Enter highest integer to test for primality: ");
    try (Scanner scanner = new Scanner(new InputStreamReader(System.in))) {
      range = scanner.nextInt();
    } catch (InputMismatchException ime) {
      System.out.println("Value entered was not an integer");
    }
    return range;
  }

  private static boolean[] findPrimes(int range) {
    boolean[] prime = new boolean[range + 1];
    Arrays.fill(prime, true);
    prime[0] = prime[1] = false;
    for (int p = 0; p * p <= range; p++) {
      if (prime[p]) {
        for (int i = p * p; i <= range; i += p) {
          if (prime[i]) {
            prime[i] = false;
          }
        }
      }
    }
    return prime;
  }

  private static int getCount(boolean[] prime) {
    int range = prime.length - 1;
    int count = 0;
    for (int p = 0; p <= range; p++) {
      if (prime[p]) {
        count++;
      }
    }
    return count;
  }

  private static void printPrimes(boolean[] prime) {
    int range = prime.length - 1;
    System.out.println(String.format("Prime numbers in the range 0-%d:", range));
    for (int p = 0; p <= range; p++) {
      if (prime[p]) {
        if (range <= 1000 || range - p <= 1000) {
          System.out.print(p + " ");
        }
      }
    }
  }

  public static void main(String[] args) {
    System.out.println("Sieve of Eratosthenes: Find all prime numbers in a given range");
    int range = 0;
    if (args.length > 0) {
      try {
        range = Integer.parseInt(args[0]);
      } catch (NumberFormatException nfe) {
      }
    } else {
      range = getRange();
    }
    long start = System.nanoTime();
    boolean[] prime = findPrimes(range);
    double duration = (System.nanoTime() - start) / 1_000.;
    printPrimes(prime);
    int count = getCount(prime);
    System.out.println(
        String.format("\nFound %d prime(s) in %d integers in %.0f microseconds\n",
            count, range, duration));
  }
}
