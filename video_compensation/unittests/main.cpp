#include <gtest/gtest.h>
#include <string>
#include <iostream>
#include <filesystem>

#include "resources.h"

int main(int argc, char **argv) {
    std::filesystem::path execPath = argv[0];
    std::filesystem::path execDir = execPath.parent_path();
    Resources::executableDir = execDir.string();
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
