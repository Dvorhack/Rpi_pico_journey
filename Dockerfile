FROM ubuntu:22.04

RUN apt-get update
RUN apt-get -y install gcc-arm-none-eabi binutils-arm-none-eabi make gcc pkg-config cargo wget curl git
RUN cargo install cargo-binutils

WORKDIR /home