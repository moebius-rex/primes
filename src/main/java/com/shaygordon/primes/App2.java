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
import java.util.InputMismatchException;
import java.util.Scanner;

public class App2 {
  private static int readRange(int range) {
    if (range == 0) {
      System.out.print("Enter highest integer to test for primality: ");
      try (Scanner scanner = new Scanner(new InputStreamReader(System.in))) {
        range = scanner.nextInt();
      } catch (InputMismatchException ime) {
      }
    }
    return range;
  }

  public static void main(String[] args) {
    System.out.println("Sieve of Eratosthenes: Find all prime numbers in a given range");

    int range = 0;
    if (args.length > 0) {
      try {
        range = Integer.parseInt(args[0]);
      } catch (NumberFormatException nfe) {
      }
    }
    Sieve sieve = new Sieve(readRange(range));
    sieve.computePrimes();
    sieve.printPrimes();
  }
}
