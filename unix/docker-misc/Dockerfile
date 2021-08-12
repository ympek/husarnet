FROM ubuntu:focal AS app_builder
ARG TARGETPLATFORM
# note: will assume context as . (repo root)
WORKDIR /husarnet
COPY . .
RUN echo $TARGETPLATFORM
RUN apt-get update -y && apt-get install -y git
RUN git submodule update --init --recursive

RUN apt install -y ninja-build cmake build-essential g++-mingw-w64 ruby ruby-dev rubygems rpm

RUN ln -sf /usr/include/asm-generic /usr/include/asm

# unno if needed
RUN gem install --no-document fpm

RUN ./util/build-cmake.sh $TARGETPLATFORM

# stage 2
FROM debian:stable-slim

RUN apt-get update -y && apt-get install -y iptables procps iproute2
RUN update-alternatives --set ip6tables /usr/sbin/ip6tables-nft

COPY --from=app_builder /husarnet/build/bin/husarnet /usr/bin/husarnet
COPY ./unix/docker-misc/husarnet-docker.sh /usr/bin/husarnet-docker

CMD husarnet-docker
