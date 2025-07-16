#include <filesystem>
#include <iostream>

#include <benchmark/benchmark.h>

static void BM_main(benchmark::State& state) {
    try {
        char result[PATH_MAX];
        ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
        std::string executable_path(result, (count > 0) ? count : 0);
        std::string executable_directory =  std::filesystem::path(executable_path).parent_path();
        std::filesystem::current_path(executable_directory);
        std::cout << "Changed working directory to: " << std::filesystem::current_path() << std::endl;
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error changing directory: " << e.what() << std::endl;
    }

    std::string script_command = "../scripts/run_programm.sh";

    for ([[maybe_unused]] auto _ : state)
        system(script_command.c_str());
}

BENCHMARK(BM_main); // clazy:skip

BENCHMARK_MAIN();
