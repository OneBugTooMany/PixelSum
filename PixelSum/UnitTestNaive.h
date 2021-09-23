#pragma once
#include <string>
#include <vector>

struct TestDataNaive
{
    // name
    std::string name;
    // data
    int xWidth;
    int yHeight;
    std::vector<unsigned char> buffer;
    int x0;
    int y0;
    int x1;
    int y1;
    // answers
    unsigned int pixelSum;
    double pixelAvg;

};
class UnitTestNaive
{
public:
    UnitTestNaive(const TestDataNaive& testDataNaive);
    virtual ~UnitTestNaive();
   
    TestDataNaive testDataNaive;
    bool passed;
    // FOR O(n)
    void runNaive();
    bool checkNaive(unsigned int& pixSum, double& pixAvg) const;

    
};

