#pragma once
#include <vector>
#include "UnitTestNaive.h"


class TestsNaive
{
public:
    TestsNaive();
    virtual ~TestsNaive();

    void runNaive();

    std::vector<UnitTestNaive> testsNaive;
};
