#!/usr/bin/env bash

disk=$(lsblk -r -o NAME |grep sd.1)
if [ -z $disk ]; then
    echo "The pico isn't connected or in flash mode"
    exit -1
fi

if [ ! -f "$1" ]; then
    echo "The file '$1' isn't a regular file"
    exit -1
fi 

if [ $(whoami) == "root" ]; then
    SUDO=""
else
    SUDO="sudo"
fi

mkdir -p /tmp/rasp
$SUDO mount /dev/$disk /tmp/rasp || exit -1

$SUDO cp "$1" /tmp/rasp
