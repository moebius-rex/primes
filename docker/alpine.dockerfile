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
RUN apk add bash
RUN apk add gcc 
RUN apk add g++ 
RUN apk add make
RUN apk add maven
RUN apk add nodejs
RUN apk add python3

# install LTS jdk and remove jdk that came with maven package
RUN apk add openjdk11
RUN apk del openjdk8

# copy project source files to image & remove generated files
WORKDIR /project
COPY . .
RUN ./installer/install.sh
