#!/bin/bash

if ! make DEBUG=1 2>&1; then
	echo "make failed"
	exit 1
fi

./bin "$@" 2>&1
