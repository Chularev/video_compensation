#include <benchmark/benchmark.h>
#include <string>
#include <iostream>
#include <filesystem>

#include "tests.h"
#include "filereader.h"

static void BM_old(benchmark::State& state) {
  FileReader reader("../data/input.yuv");

  for (auto _ : state)
    reader.readeNext();

}

BENCHMARK(BM_old);


static void BM_new(benchmark::State& state) {
  int a,b;
  for (auto _ : state)
    a + b;
}

BENCHMARK(BM_new);

BENCHMARK_MAIN();
