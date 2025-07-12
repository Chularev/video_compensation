#include <benchmark/benchmark.h>
#include <string>
#include <iostream>
#include <filesystem>

#include "tests.h"
#include "filereader.h"

static void BM_old(benchmark::State& state) {
<<<<<<< HEAD
  FileReader reader("../data/input.yuv");
=======
  FileReader reader("/home/alex/workspace/projects/video_compensation/video_compensation/run/Good_dog.mp4");
>>>>>>> 1dc40f8c89b88279b3820c0a0d223a268ffd213a

  for (auto _ : state)
    reader.readeNext();

}

BENCHMARK(BM_old);


static void BM_new(benchmark::State& state) {
<<<<<<< HEAD
=======
//  FileReader reader("/home/alex/workspace/projects/video_compensation/video_compensation/run/Good_dog.mp4");
>>>>>>> 1dc40f8c89b88279b3820c0a0d223a268ffd213a
  int a,b;
  for (auto _ : state)
    a + b;
}

BENCHMARK(BM_new);

BENCHMARK_MAIN();
