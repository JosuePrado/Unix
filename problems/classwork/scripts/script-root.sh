#!/bin/bash

if [ "$(id -u)" -eq 1 ]; then 
    echo "Run as root"
else 
    echo "you neet to run this script as root"
fi 
