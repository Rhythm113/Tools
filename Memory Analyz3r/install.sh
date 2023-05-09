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
wget https://raw.githubusercontent.com/Rhythm113/Tools/master/Memory%20Analyz3r/v0.2/mema3 -O $PREFIX/bin/mema3
wget https://raw.githubusercontent.com/Rhythm113/Tools/master/Memory%20Analyz3r/v0.2/mem -O $PREFIX/bin/mem

# Verify downloaded files
if [ ! -x $PREFIX/bin/mema3 ] || [ ! -x $PREFIX/bin/mem ]; then
  echo "Error: downloaded files are missing or not executable"
  exit 1
fi

# Echo success message
echo "Installation successful"
