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

SUBDIRS := $(wildcard app*)

all: sieve sievex $(SUBDIRS)
	@# compile anything that needs to be compiled and then run

sieve:
	@# run make with no arguments for sieve subdirectory
	$(MAKE) --no-print-directory --directory $@

sievex:
	@# run make with no arguments for sievex subdirectory
	$(MAKE) --no-print-directory --directory $@

$(SUBDIRS):
	@# run make with no arguments for each subdirectory
	$(MAKE) --no-print-directory --directory $@

clean test:
	@$(MAKE) --no-print-directory --directory sieve $@
	@$(MAKE) --no-print-directory --directory sievex $@
	@for subdir in $(SUBDIRS); do $(MAKE) --no-print-directory --directory $$subdir $@; done

install:
	@$(MAKE) --no-print-directory --directory sieve $@
	@$(MAKE) --no-print-directory --directory sievex $@

.PHONY: sieve sievex $(SUBDIRS) clean test install
