FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

# Instalar toolchain RISC-V y dependencias
RUN apt-get update && apt-get install -y \
    git \
    build-essential \
    gdb-multiarch \
    qemu-system-misc \
    gcc-riscv64-linux-gnu \
    binutils-riscv64-linux-gnu \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /xv6_original

# Clonar tu repositorio
RUN git clone https://github.com/AlejandroVS-code/Xv6_orginal_test.git .

# Compilar
RUN make

# Ejecutar xv6
CMD ["make", "qemu", "CPUS=1"]
