#!/bin/sh -e
find -name '*.cpp' -print0 | xargs -0 g++ -O0 -ggdb3 -o tdp $(pkgconf --cflags --libs sfml-all)
