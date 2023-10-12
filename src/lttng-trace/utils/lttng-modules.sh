#!/bin/sh

# CERTS_DIR=certs
# KERNEL_CERTS_DIR=/lib/modules/$(uname -r)/build/certs

# # Install linux headers
# apt-get update
# apt-get install -y linux-headers-$(uname -r)

# # Generate key to sign kernel moduless
# cp $CERTS_DIR/* $KERNEL_CERTS_DIR && cd $KERNEL_CERTS_DIR
# openssl req -new -nodes -utf8 -sha512 -days 36500 -batch -x509 -config x509.genkey -outform DER -out signing_key.x509 -keyout signing_key.pem

# Install lttng modules
cd /tmp
git clone https://github.com/lttng/lttng-modules.git
cd lttng-modules
git checkout stable-2.13
make
make modules_install
depmod -a
