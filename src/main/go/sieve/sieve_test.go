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
package sieve

import (
	"testing"
)

func TestSieveRange(t *testing.T) {
	want := 42
	ps, err := NewSieve(want)
	if err != nil {
		t.Errorf("NewSieve(want=%d) errt=%v", want, err)
	} else {
		got := ps.Range()
		if got != want {
			t.Errorf("NewSieve(want: %d) got %d", want, got)
		}
	}
}

func TestSieveNegRange(t *testing.T) {
	want := -13
	_, err := NewSieve(want)
	if err == nil {
		t.Errorf("NewSieve(want=%d) generated no error, err=%v\n", want, err)
	}
}

func TestSievePrimeMap(t *testing.T) {
	want := 109
	r := 120
	ps, err := NewSieve(r)
	if err != nil {
		t.Errorf("NewSieve(range=%d) err=%v\n", r, err)
		return
	}
	ps.ComputePrimes()
	pm := ps.PrimeMap()
	found := pm[want]
	if !found {
		t.Errorf("Sieve.PrimeMap[%d]: wanted true, got false", want)
	}
}
