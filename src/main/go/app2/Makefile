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

GO = go
GOFLAGS =
#CGO_LDFLAGS = -L/usr/local/lib -lcsieve

SRCDIR = .
BINDIR = bin

SIEVERANGE = 1000

all: targets $(BINDIR)/app test

$(BINDIR)/app : $(SRCDIR)/app.go $(SRCDIR)/sieve.go
	@$(GO) build $(GOFLAGS) -o $@ $?

targets:
	-@mkdir -p $(BINDIR)

clean:
	-@$(RM) -r $(BINDIR)

test:
	@$(BINDIR)/app $(SIEVERANGE)

tidy:
	@$(GO) mod tidy

.PHONY: targets clean test tidy
