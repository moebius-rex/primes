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

FROM fedora

# update package list & upgrade
RUN dnf update  -y
RUN dnf upgrade -y

# install utilities
RUN dnf install -y file less tree vim

# install project build & run toolchains
RUN dnf install -y gcc
RUN dnf install -y gcc-c++
RUN dnf install -y gccgo
RUN dnf install -y go
RUN dnf install -y make
RUN dnf install -y maven
RUN dnf install -y nodejs
RUN dnf install -y python3

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
