#!/bin/bash

cmake -DBISON_EXECUTABLE=/opt/homebrew/opt/bison/bin/bison -DCMAKE_BUILD_TYPE=Release -H. -Bbuild -GNinja
cmake --build build

mv $(find build -name '*.c') generated/
