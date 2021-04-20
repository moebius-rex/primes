#!/usr/bin/env bash

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

# get the normalized path of this script's parent directory, i.e., the
# project home directory
projpath=$(pwd)/$(dirname $0)     # current directory
projpath=$(cd ${projpath} && pwd) # normalized current directory
projpath=$(dirname ${projpath})   # parent directory

# clean all generated project files
cd ${projpath}
make clean

# make sieve libraries
cd ${projpath}/src/main/c/sieve
libpath=$(pwd)/lib
make targets lib/libcsieve.so

# Three ways shared libraries may be located by loader in order of permanence:
# 1. libraries are described in /etc/ld.so.conf (not on all systems)
# 2. libraries are searched for in /usr/local/lib
# 3. libraries are searched for in LD_LIBRARY_PATH environment variable

# if no /usr/local/lib, use LD_LIBRARY_PATH to identify shared objects
if [ ! -d /usr/local/lib ]; then
  rc=".$(basename ${SHELL})rc"
  echo "-----------------------------------------------------------------------------"
  echo "                              I M P O R T A N T                              "
  echo "-----------------------------------------------------------------------------"
  echo "Add the following line to the end of the ${rc} file in your home directory:"
  echo 
  echo "export LD_LIBRARY_PATH=${libpath}"
  echo
  echo "Then, source the modified file to apply the change:"
  echo "  % source \$HOME/${rc}"
  echo
  echo "To verify the change:"
  echo "  % env|grep LD_LIBRARY_PATH"
  echo "  LD_LIBRARY_PATH=${libpath}"
  echo
  echo "Alternatively, log out and back in for the change to take effect"
  echo "-----------------------------------------------------------------------------"
fi

# create softlink to sieve shared library in /usr/local/lib
target=/usr/local/lib/libcsieve.so
if [ -L ${target} ]; then
  unlink ${target}
fi
ln -s ${libpath}/libcsieve.so ${target}

# configure sieve shared library in loader if rquired
confdir=/etc/ld.so.conf.d
if [ -d ${confdir} ]; then
  cp ${projpath}/installer/libcsieve.so.conf ${confdir}/libcsieve.conf
  ldconfig
  # ldconfig -n ${projpath}/src/main/c/sieve
fi
