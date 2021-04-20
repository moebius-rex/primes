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

CC = gcc
CCFLAGS = -std=c11 -Wall -Werror -pedantic -fPIC
SOFLAGS = -shared
LDFLAGS =

SRCDIR = .
BINDIR = bin
LIBDIR = lib
OBJDIR = obj

SIEVERANGE = 1000

all: targets $(LIBDIR)/libcsieve.a $(LIBDIR)/libcsieve.so $(BINDIR)/appa $(BINDIR)/appso test

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CCFLAGS) -c $? -o $@

$(LIBDIR)/lib%.a : $(OBJDIR)/%.o
	$(AR) q $@ $?

$(LIBDIR)/lib%.so : $(OBJDIR)/%.o
	$(CC) $(SOFLAGS) $? -o $@

$(BINDIR)/appa : $(OBJDIR)/app.o $(LIBDIR)/libcsieve.a
	@$(CC) $(LDFLAGS) $? -o $@

$(BINDIR)/appso : $(OBJDIR)/app.o $(LIBDIR)/libcsieve.so
	@$(CC) $(LDFLAGS) -L$(LIBDIR) -lcsieve $? -o $@

.PHONY: targets clean test
targets:
	-@mkdir -p $(OBJDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(BINDIR)

clean:
	-@$(RM) -r $(OBJDIR)
	-@$(RM) -r $(LIBDIR)
	-@$(RM) -r $(BINDIR)

test: $(BINDIR)/appa $(BINDIR)/appso
	@$(BINDIR)/appa $(SIEVERANGE)
	@$(BINDIR)/appso $(SIEVERANGE)
