#!/bin/bash

sudo perf stat -d /home/alex/workspace/projects/video_compensation/video_compensation/build/benchmark/benchmark --benchmark_filter=$1
