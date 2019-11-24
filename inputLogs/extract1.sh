#! /bin/bash

cd logs
touch extracted.txt
for file in *; do
    grep "<Tree" $file | tail -1 | sed 's/[[:blank:]]*<Tree size=\"[[:digit:]]*\">//g' | sed 's/<\/Tree>[[:blank:]]*//g' >> extracted.txt
done