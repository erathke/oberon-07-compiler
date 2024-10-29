#!/bin/bash

LD="ld"
LDFLAGS="-T min.ld --build-id=none"

$LD $LDFLAGS RTL_sys.xo $1.xo -o $1
