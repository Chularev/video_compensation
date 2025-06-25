#include "programmtest.h"

#include "programm.h"
#include "resources.h"

#include <iostream>
#include <fstream>
#include <vector>

ProgrammTest::ProgrammTest() {}

void ProgrammTest::initMainTest(const std::string& file)
{
    static std::string text = "";
    if (text == "")
    {
        std::ifstream testData(Resources::executableDir + file);

        EXPECT_FALSE(testData.fail());

        std::stringstream buffer;
        buffer << testData.rdbuf();
        text = buffer.str();
        testData.close();
    }

    static std::istringstream input;
    input.str(text);
    std::cin.rdbuf(input.rdbuf());

    testing::internal::CaptureStdout();

}

void ProgrammTest::bodyMainTest()
{
    Programm programm;
    programm.main();
}
void ProgrammTest::finalizeMainTest(const std::string &file)
{
    std::string result = testing::internal::GetCapturedStdout();

    std::ifstream testResult(Resources::executableDir + file);
    EXPECT_FALSE(testResult.fail());
    std::string templateResult((std::istreambuf_iterator<char>(testResult)), std::istreambuf_iterator<char>());

    EXPECT_EQ(result, templateResult);
    testResult.close();
}

void ProgrammTest::mainTest()
{
    std::vector<std::tuple<std::string, std::string>> fixture = {
        {"/data/test1.data", "/data/test1.result"}
    };
    for (auto& files : fixture)
    {
        initMainTest(std::get<0>(files));
        bodyMainTest();
        finalizeMainTest(std::get<1>(files));
    }

}

TEST_F(ProgrammTest, main)
{
    mainTest();
}
