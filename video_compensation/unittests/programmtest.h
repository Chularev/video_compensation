#ifndef PROGRAMMTEST_H
#define PROGRAMMTEST_H

#include "gtest/gtest.h"


class ProgrammTest : public ::testing::Test
{
public:
    ProgrammTest();
    void mainTest();
    void initMainTest(const std::string &file);
    void bodyMainTest();
    void finalizeMainTest(const std::string &file);
};

#endif // PROGRAMMTEST_H
