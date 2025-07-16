#!/bin/bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd "$SCRIPT_DIR" || exit

../../benchmark/mainbenchmark --benchmark_out=tmp_mainbenchmark.json --benchmark_out_format=json
