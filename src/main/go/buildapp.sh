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

log() {
  printf "$(date) | app  | %-5s | ${1}\n" ${PKG} >> ${LOG}
}

GO=go
GCCGO=gccgo
GCCGOFLAGS="-compiler ${GCCGO} "
PKG=$(basename $(pwd))
RM="rm -f"
LOG=.golog

cmd=$1
shift
case ${cmd} in
  test)    args="-v ." ;;
  install) args=.      ;;
  clean)   args=.      ;;
  version)
    log "$(${GO} ${cmd})"
    exit 0
    ;;
  scrub)
    ${RM} ${LOG}
    log "++ log scrubbed"
    exit 0
    ;;
  build)
    path=$(which ${GCCGO})
    if [ ! -z ${path} ]; then
      args=${GCCGOFLAGS}
    fi
    app=$1
    shift
    args="${args}-o ${app} $@"
    ;;
  *)
    echo unknown command: ${cmd}
    exit 1
    ;;
esac
gocmd="${GO} ${cmd} ${args}"
log "${gocmd}"
eval "${gocmd}"
exit $?
