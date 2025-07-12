#include <benchmark/benchmark.h>

static void BM_main(benchmark::State& state) {
    int a,b;
    for (auto _ : state)
        a + b;
}

BENCHMARK(BM_main);

BENCHMARK_MAIN();
