#!/bin/bash

control=begin

make
make clean

./decrypt

./stock_diff

firefox enonce_pascal/blaise.html &

echo ""
echo "    Pour sortir, taper stop"
echo "    Choisir un défi à résoudre (entrer une lettre entre a et d)"
read request
control=$request

while [ $control != stop ]
do
    ./defi $control
    echo ""
    echo "    Choisir un défi à résoudre (entrer une lettre entre a et d)"
    read request
    control=$request
done


