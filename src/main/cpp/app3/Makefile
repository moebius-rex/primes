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

CPP = g++
CPPFLAGS = -std=c++17 -Wall -Werror -pedantic
LDFLAGS =

SRCDIR = .
BINDIR = bin
OBJDIR = obj
LIBDIR = ../../c/app3/lib

INCFLAGS = -I../../

SIEVERANGE = 1000

all: targets $(BINDIR)/app test

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CPP) $(CPPFLAGS) $(INCFLAGS) -c $? -o $@

$(BINDIR)/app : $(OBJDIR)/sieve.o $(OBJDIR)/app.o
	@$(CPP) $(LDFLAGS) -L$(LIBDIR) -lsieve $? -o $@

.PHONY: targets clean test
targets:
	-@mkdir -p $(OBJDIR)
	-@mkdir -p $(BINDIR)

clean:
	-@$(RM) -r $(OBJDIR)
	-@$(RM) -r $(BINDIR)

test:
	@$(BINDIR)/app $(SIEVERANGE)
