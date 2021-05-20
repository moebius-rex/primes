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

FROM alpine

# update package list & upgrade
RUN apk update
RUN apk upgrade

# install utilities
RUN apk add file less tree vim

# install project build & run toolchains
RUN apk add go
RUN apk add make

# copy required project source files to image
WORKDIR /prime
COPY . .
RUN cd src/main; rm -rf cpp; rm -rf java; rm -rf js; rm -rf python

# add prime directory to PATH for any shell
ENV PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/prime
RUN printf "export PATH=\$PATH:/prime\n" > /etc/profile.d/prime.sh

# some distros don't include /usr/local/include
RUN if [ ! -e /usr/local/include ]; then mkdir /usr/local/include; fi

# install go man page generator
# RUN go get -v golang.org/x/tools/cmd/godoc

# complete project setup
RUN setup/setup.sh
