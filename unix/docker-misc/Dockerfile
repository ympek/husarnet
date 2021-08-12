ARG TARGETPLATFORM
FROM debian:stable-slim AS app_builder

# note: will assume context as . (repo root)
WORKDIR /husarnet
COPY . .

RUN ./util/build-prepare.sh
RUN ./util/build-cmake.sh ${TARGETPLATFORM}

# stage 2
FROM debian:stable-slim

RUN apt-get update -y && apt-get install -y iptables procps iproute2
RUN update-alternatives --set ip6tables /usr/sbin/ip6tables-nft

COPY --from=app_builder /husarnet/build/bin/husarnet /usr/bin/husarnet
COPY ./unix/docker-misc/husarnet-docker.sh /usr/bin/husarnet-docker

CMD husarnet-docker
