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
package com.shaygordon.primes;

import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * Computes prime numbers in a given range using an implementation of the
 * Sieve of Erastosthenes algorithm.
 */
public class Sieve {
  // defines the number of prines to display around an ellipsis that is used
  // when large numbers of primes are equested
  private static int MAX_HALF = 10;
  private static DecimalFormat FMT = new DecimalFormat("#,###");

  private int range;
  private boolean[] integers;
  private List<Integer> primes;
  private long startTime, endTime;

  /***
   * Private functions
   */
  private static String format(Number value) { return FMT.format(value); }

  private static boolean[] createIntegers(int range) {
    boolean[] integers = new boolean[range + 1];
    Arrays.fill(integers, true);
    integers[0] = integers[1] = false; // by convention, 0 and 1 are not primes
    return integers;
  }

  /**
   * Public functions
   */
  public Sieve(int range) {
    this.range = range;
    this.integers = createIntegers(this.range);
    this.primes = new ArrayList<Integer>();
  }

  public void computePrimes() {
    this.startTime = System.nanoTime();

    // step 1. sieve: tag non-prime inputs
    for (int p = 0; p * p < this.range; p++) {
      if (this.integers[p]) {
        for (int i = p * p; i <= this.range; i += p) {
          if (this.integers[i]) {
            this.integers[i] = false;
          }
        }
      }
    }
    
    // step 2. add primes to output
    for (int index = 0; index < this.range; index++) {
      if (this.integers[index]) {
        this.primes.add(index);
      }
    }

    this.endTime = System.nanoTime();
  }

  public void printPrimes() {
    System.out.println(String.format("Prime numbers up to %s:", format(range)));
    StringBuilder sb = new StringBuilder();
    int half = this.primes.size() / 2;
    for (int n = 0; n < this.primes.size(); n++) {
      int p = this.primes.get(n);
      if (half > MAX_HALF) {
        if (n == MAX_HALF) {
          sb.append(".. ");
        } else if (n < MAX_HALF || n >= this.primes.size() - MAX_HALF) {
          sb.append(p).append(' ');
        }
      } else {
        sb.append(p).append(' ');
      }
    }
    System.out.println(sb);
    System.out.println(String.format("Found %s prime(s) in %s integers in %s microseconds\n",
        format(this.primes.size()), format(this.range), format(this.getElapsed())));
  }

  public List<Integer> getPrimes() {
    return List.copyOf(this.primes);
  }

  public int getRange() {
    return this.range;
  }  

  public double getElapsed() {
    return (this.endTime - this.startTime) / 1000.0;
  }
}
