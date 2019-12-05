#! /bin/bash

#first argument: directory of the logs
cd $1
if test -f extracted.txt; then
    rm extracted.txt
fi
touch extracted.txt
for file in *; do
    grep "<Tree" $file | tail -1 | sed 's/[[:blank:]]*<Tree size=\"[[:digit:]]*\">//g' | sed 's/<\/Tree>[[:blank:]]*//g' >> extracted.txt
done