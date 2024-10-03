#!/bin/bash

for ((i = 1; i <= $1; i++))
do
    IDADE=$(((RANDOM % 100)+1))
    echo "./pessoa -i Pessoa${i} $IDADE"

    ./pessoa -i Pessoa${i} $IDADE

done
