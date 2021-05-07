Larong Ahas 32 Bit
==================

A Bootable Snake Game Created In C Language


Setup Builder
=============
::

    docker pull six519/make_linux:1.0
    alias make_linux="docker run -it -v \"\$(pwd)\":/app --rm six519/make_linux:1.0"

Build & Run Using QEMU
======================
::

    make_linux
    qemu-system-x86_64 -cdrom ahas.iso