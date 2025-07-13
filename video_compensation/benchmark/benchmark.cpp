#include <benchmark/benchmark.h>
#include <string>
#include "filereader.h"

static void BM_old(benchmark::State& state) {
  FileReader reader("../data/input.yuv");

  for ([[maybe_unused]] auto _ : state)
    reader.readeNext();

}

BENCHMARK(BM_old);


static void BM_new(benchmark::State& state) {
}

BENCHMARK(BM_new); // clazy:skip

BENCHMARK_MAIN();
