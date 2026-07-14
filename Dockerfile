FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    git build-essential gdb-multiarch \
    qemu-system-riscv gcc-riscv64-linux-gnu \
    binutils-riscv64-linux-gnu \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /xv6

COPY xv6-original/ .

RUN make

CMD ["make", "qemu"]
