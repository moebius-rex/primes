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

# Build and/or run all language sub-projects
SUBDIRS = src/main

all: maven $(SUBDIRS)

.PHONY: maven $(SUBDIRS) clean test

maven:
	@mvn -q compile

$(SUBDIRS):
	$(MAKE) --no-print-directory -C $@

clean test:
	@mvn -q $@
	@for subdir in $(SUBDIRS); do $(MAKE) --no-print-directory -C $$subdir $@; done
