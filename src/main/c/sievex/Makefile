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

CINCDIR = -I/usr/local/include
CLIBDIR = /usr/local/lib

SIEVERANGE = 1000

all: targets $(LIBDIR)/libcsievex.a $(LIBDIR)/libcsievex.so $(BINDIR)/appa $(BINDIR)/appso test

.PRECIOUS: $(OBJDIR)/%.o  # only way to suppress the 'rm obj/...' message

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CCFLAGS) $(CINCDIR) -c $? -o $@

$(LIBDIR)/lib%.a : $(OBJDIR)/%.o
	@$(AR) -cq $@ $?

$(LIBDIR)/lib%.so : $(OBJDIR)/%.o $(CLIBDIR)/libcsieve.so
	@$(CC) $(SOFLAGS) -L$(CLIBDIR) -lcsieve $? -o $@

$(BINDIR)/appa : $(OBJDIR)/app.o $(LIBDIR)/libcsievex.a $(CLIBDIR)/libcsieve.a
	@$(CC) $(LDFLAGS) $? -o $@

$(BINDIR)/appso : $(OBJDIR)/app.o $(LIBDIR)/libcsievex.so $(CLIBDIR)/libcsieve.so
	@$(CC) $(LDFLAGS) -L$(CLIBDIR) -lcsieve -L$(LIBDIR) -lcsievex $? -o $@

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

install: targets $(LIBDIR)/libcsievex.a $(LIBDIR)/libcsievex.so $(SRCDIR)/csievex.h
	@ln -sf $${PWD}/lib/libcsievex.a   /usr/local/lib 
	@ln -sf $${PWD}/lib/libcsievex.so  /usr/local/lib
	@ln -sf $${PWD}/csievex.h          /usr/local/include

.PHONY: targets clean test install
