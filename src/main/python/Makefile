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

SUBPROJS = $(patsubst %.py, %, $(wildcard app*))

SIEVERANGE = 1000

all: test
	@# nothing to build, just run the tests

$(SUBPROJS):
	@# run one app script by entering e.g. 'make app2' on the command line
	python3 $@.py $(SIEVERANGE)

clean:
	@$(RM) -r __pycache__

test:
	@for subproj in $(SUBPROJS); do echo python/$$subproj; ./$$subproj.py $(SIEVERANGE); done

install:
	@# suppress nothing to be done messages

.PHONY: $(SUBPROJS) clean test install
