#!/usr/bin/env sh

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

GO=go
GCCGO=gccgo
GCCGOFLAGS="-compiler ${GCCGO}"
LOG=.build.log

rule=$1; shift

case ${rule} in
  clean)
    rm -f ${LOG}
    ${GO} ${rule}
    exit $?
    ;;
  test)
	  ${GO} test -v
    exit $?
    ;;
  install)
    ${GO} ${rule}
    exit $?
    ;;
esac

# build app or utility
path=$(which ${GCCGO})
if [ ! -z ${path} ]; then
  echo "`date` | gccgo | ${GO} build ${GCCGOFLAGS} -o ${rule} $@" >> ${LOG}
  ${GO} build ${GCCGOFLAGS} -o ${rule} $@
else
  if [ $# -gt 0 ]; then
    echo "`date` | go    | ${GO} build -o ${rule} $@" >> ${LOG}
    ${GO} build -o ${rule} $@
  else
    # assume target is a utility and check that it builds
    echo "`date` | go    | ${GO} build ${rule}" >> ${LOG}
    ${GO} build ${rule}
  fi
fi
