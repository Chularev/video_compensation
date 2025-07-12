#include <benchmark/benchmark.h>

static void BM_main(benchmark::State& state) {
    std::string script_command = "../scripts/run_programm.sh";

    for (auto _ : state)
        system(script_command.c_str());
}

BENCHMARK(BM_main);

BENCHMARK_MAIN();
