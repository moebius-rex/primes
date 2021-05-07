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

FROM ubuntu:focal

# update package list & upgrade
RUN apt update  -y
RUN apt upgrade -y

# disable all interactive package installation dialogs while building the image
ARG DEBIAN_FRONTEND=noninteractive

# install utilities
RUN apt install -y file less tree vim

# install project build & run toolchains
RUN apt install -y gcc
RUN apt install -y gccgo-go
RUN apt install -y golang-go
RUN apt install -y g++
RUN apt install -y make
RUN apt install -y maven
RUN apt install -y nodejs
RUN apt install -y python3

# upgrade nodejs to 14.16.1
RUN \
  apt install -y curl && \
  cd ~ && \
  curl -sL https://deb.nodesource.com/setup_14.x -o nodesource_setup.sh && \
  bash nodesource_setup.sh && \
  apt install -y nodejs

# copy project source files to image & remove generated files
WORKDIR /prime
COPY . .

# add prime directory to PATH for any shell
ENV PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/prime
RUN printf "export PATH=\$PATH:/prime\n" > /etc/profile.d/prime.sh

# some distros don't include /usr/local/include
RUN if [ ! -e /usr/local/include ]; then mkdir /usr/local/include; fi

# complete project setup
RUN setup/setup.sh
