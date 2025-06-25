#include <benchmark/benchmark.h>
#include <string>
#include <iostream>
#include <filesystem>

#include "tests.h"
#include "filereader.h"

static void BM_old(benchmark::State& state) {
  FileReader reader("/home/alex/workspace/projects/video_compensation/video_compensation/run/Good_dog.mp4");

  for (auto _ : state)
    reader.readeNext();

}

BENCHMARK(BM_old);


static void BM_new(benchmark::State& state) {
  FileReader reader("/home/alex/workspace/projects/video_compensation/video_compensation/run/Good_dog.mp4");
  
  for (auto _ : state)
    reader.readeNext();
}

BENCHMARK(BM_new);

BENCHMARK_MAIN();
