#!/bin/bash

# Update and upgrade packages
#pkg update && pkg upgrade

if ! command -v wget &> /dev/null
then
    echo "wget is not installed on your system. Installing..."
    pkg install wget
else
    echo "wget is already installed on your system continue..."
fi


# Check if libelf and ldd are installed
if ! pkg show libelf && ! pkg show ldd; then
  echo "libelf and ldd not found installing.."
  pkg install ldd libelf
  exit 1
fi

# Download mema3 and mem from URLs
wget https://raw.githubusercontent.com/Rhythm113/Tools/main/Memory%20Analyz3r/v0.2/mema3 -O $PREFIX/bin/mema3
wget https://raw.githubusercontent.com/Rhythm113/Tools/main/Memory%20Analyz3r/v0.2/mem -O $PREFIX/bin/mem
chmod +x $PREFIX/bin/mema3
chmod +x $PREFIX/bin/mem

# Verify downloaded files
if [ ! -x $PREFIX/bin/mema3 ] || [ ! -x $PREFIX/bin/mem ]; then
  echo "Error: downloaded files are missing or not executable"
  exit 1
fi

# Echo success message
echo "Installation successful run mem to see to see help"
