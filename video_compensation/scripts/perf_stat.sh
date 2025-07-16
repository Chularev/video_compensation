#!/bin/bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd "$SCRIPT_DIR" || exit


sudo perf stat -d ../project/VideoCompensation -pathInput ../data/input.yuv -w 1920 -h 1000 -pathOutput ../data/result.yuv
