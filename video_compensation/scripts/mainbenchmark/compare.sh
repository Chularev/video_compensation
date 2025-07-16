#!/bin/bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd "$SCRIPT_DIR" || exit

compare.py benchmarks mainbenchmark.json tmp_mainbenchmark.json 
