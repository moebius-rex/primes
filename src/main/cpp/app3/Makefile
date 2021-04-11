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
CPP = g++
CPPFLAGS = -g -std=c++17 -Wall -Werror -pedantic
LDFLAGS =

SRCDIR = .
BINDIR = bin
OBJDIR = obj
LIBDIR = ../../c/app3/obj

INC = -I../../
# LIB = -L$(LIBDIR) -lsieve.so 
LIB = $(LIBDIR)/sieve.o

SIEVERANGE = 1000

all: targets $(BINDIR)/app test

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CPP) $(CPPFLAGS) $(INC) -c $? -o $@

$(BINDIR)/app : $(OBJDIR)/sieve.o $(OBJDIR)/app.o
	@$(CPP) $(LDFLAGS) $(LIB) $? -o $@

.PHONY: targets clean test
targets:
	-@mkdir -p $(OBJDIR)
	-@mkdir -p $(BINDIR)

clean:
	-@$(RM) -r $(OBJDIR)
	-@$(RM) -r $(BINDIR)

test:
	@$(BINDIR)/app $(SIEVERANGE)
