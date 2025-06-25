#include <benchmark/benchmark.h>
#include <string>
#include <iostream>
#include <filesystem>
#include "programmtest.h"

#include "tests.h"
#include "resources.h"

class BProgrammTest : public ProgrammTest
{
  public:
    virtual void TestBody() override
    {

    }
};

static void BM_integration_main(benchmark::State& state) {

}
static void BM_isReachable(benchmark::State& state) {
}
