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

SUBDIRS := $(filter-out Makefile, $(wildcard *))

all: $(SUBDIRS)
	@# compile anything that needs to be compiled and then run

$(SUBDIRS):
	@# run make with no arguments for each subdirectory
	$(MAKE) --no-print-directory --directory $@

clean test install:
	@for subdir in $(SUBDIRS); do $(MAKE) --no-print-directory --directory $$subdir $@; done

.PHONY: $(SUBDIRS) clean test install
