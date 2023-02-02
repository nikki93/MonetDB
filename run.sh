#!/bin/bash

cmake -DBISON_EXECUTABLE=/opt/homebrew/opt/bison/bin/bison -DCMAKE_BUILD_TYPE=Release -H. -Bbuild -GNinja
cmake --build build

cp $(find build -name '*.h') generated/
cp $(find build -name '*.c') generated/

cp monetdb_config.h generated/
