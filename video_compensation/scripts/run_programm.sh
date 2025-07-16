#!/bin/bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd "$SCRIPT_DIR" || exit


../project/VideoCompensation -pathInput ../data/input.yuv -w 1920 -h 1000 -pathOutput ../data/result.yuv
