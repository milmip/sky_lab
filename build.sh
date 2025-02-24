#!/bin/bash

read -p "Tap : 1. build | 2. clean | 3. rebuild >> " -n 1 -r my
clear

if [ "$my" == "1" ]; then
    make all
    if [ $? -ne 0 ]; then
        exit 1
    fi
elif [ "$my" == "2" ]; then
    make clean
    exit $?
elif [ "$my" == "3" ]; then
    make rebuild
    if [ $? -ne 0 ]; then
        exit 1
    fi
else
    echo "Réponse pas clair"
fi

read -p "Wanna run (y/n)? " -n 1 -r my
clear

if [ "$my" == "y" ]; then
    ./run.sh
    exit $?
fi
exit 0