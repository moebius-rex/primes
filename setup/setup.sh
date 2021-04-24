#!/usr/bin/env bash

# Copyright 2021 Shay Gordon
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#		 http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# get the normalized path of this script's parent directory, i.e., the
# project home directory
projpath=$(pwd)/$(dirname $0)     # current directory
projpath=$(cd ${projpath} && pwd) # normalized current directory
projpath=$(dirname ${projpath})   # parent & project home directory

# clean generated files and make and install project libraries and other files
make clean install > /dev/null 2>&1

# Three ways shared libraries may be located by loader in order of permanence:
# 1. libraries are described in /etc/ld.so.conf (not on all systems)
# 2. libraries are searched for in /usr/local/lib (on every system)
# 3. libraries are searched for in LD_LIBRARY_PATH env variable (never needed)

# add sieve shared library to loader config if required
if [ ! -z $(command -v ldconfig) ]; then
	confdir=/etc/ld.so.conf.d
	if [ -d ${confdir} ]; then
		cp ${projpath}/setup/libcsieve.so.conf ${confdir}
	else
		# some systems, like alpine, don't use a config directory, so just try to
    # make sure the loader knows to look in /usr/local/lib
		ldconfig -n /usr/local/lib
	fi
	ldconfig
fi

# run sieve shared library test apps
cd ${projpath}/src/main/c/sieve;  make test  > /dev/null 2>&1
cd ${projpath}/src/main/c/sievex; make test  > /dev/null 2>&1
cd ${projpath};                   make clean > /dev/null 2>&1