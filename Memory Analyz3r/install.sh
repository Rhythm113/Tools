#!/bin/bash

# Update and upgrade packages
pkg update && pkg upgrade

# Install libelf and ldd
pkg install ldd libelf

# Check if libelf and ldd are installed
if ! pkg show libelf && ! pkg show ldd; then
  echo "libelf and ldd not found"
  exit 1
fi

# Download mema3 and mem from URLs
wget https://example.com/mema3 -O $PREFIX/bin/mema3
wget https://example.com/mem -O $PREFIX/bin/mem

# Verify downloaded files
if [ ! -x $PREFIX/bin/mema3 ] || [ ! -x $PREFIX/bin/mem ]; then
  echo "Error: downloaded files are missing or not executable"
  exit 1
fi

# Echo success message
echo "Installation successful"
