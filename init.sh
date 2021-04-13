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

# get the normalized path of this script, i.e., the project home directory
projpath=$(pwd)/$(dirname $0)
projpath=$(cd ${projpath} && pwd)

# clean all generated project files
cd ${projpath}
make clean

# make sieved libraries
cd ${projpath}/src/main/c/app3
libpath=$(pwd)/lib
make targets lib/libcsieve.so

# install libsieve.so softlink in /usr/local/lib
if [ -d /usr/local/bin ]; then
  target=/usr/local/lib/libcsieve.so
  if [ -L ${target} ]; then
    unlink ${target}
  fi
  ln -s ${libpath}/libcsieve.so ${target}
else
  # don't know how to permanently install so use LD_LIBRARY_PATH instead
  rc=".$(basename ${SHELL})rc"
  echo "-----------------------------------------------------------------------------"
  echo "                              I M P O R T A N T                              "
  echo "-----------------------------------------------------------------------------"
  echo "Add the following line to the end of the ${rc} file in your home directory:"
  echo 
  echo "export LD_LIBRARY_PATH=${libpath}"
  echo
  echo "Then source the modified file to apply the change:"
  echo "% source ${rc}"
  echo "% env|grep LD_LIBRARY_PATH"
  echo "LD_LIBRARY_PATH=${libpath}"
  echo
  echo "Alternatively, log out and back in for the change to take effect"
  echo "-----------------------------------------------------------------------------"
fi
