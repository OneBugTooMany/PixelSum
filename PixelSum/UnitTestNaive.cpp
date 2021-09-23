#include "UnitTestNaive.h"
#include "PixelSumNaive.h"
#include "Helpers.h"
#include <iostream>
#include <chrono>
#include <iomanip>

UnitTestNaive::UnitTestNaive(const TestDataNaive& data) :testDataNaive(data) {}

UnitTestNaive::~UnitTestNaive() {}

void UnitTestNaive::runNaive()
{
    unsigned char* buffer = new unsigned char[testDataNaive.buffer.size()];
    std::copy(testDataNaive.buffer.begin(), testDataNaive.buffer.end(), buffer);

    // Create PixelSum object and check preprocessing time
    auto start = std::chrono::high_resolution_clock::now();
    PixelSumNaive pixelSumNaive(buffer, testDataNaive.xWidth, testDataNaive.yHeight);
    auto end = std::chrono::high_resolution_clock::now();
    double preprocessingTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    preprocessingTime *= 1e-6;
    delete[] buffer;

    // Calculate stuff
    auto pixSum = pixelSumNaive.getPixelSum(testDataNaive.x0, testDataNaive.y0, testDataNaive.x1, testDataNaive.y1);
    auto pixAvg = pixelSumNaive.getPixelAverage(testDataNaive.x0, testDataNaive.y0, testDataNaive.x1, testDataNaive.y1);


    // Check if passed
    std::cout << std::endl << "--------------------- start test ---------------------" << std::endl;
    std::cout << "Test: " << testDataNaive.name << std::endl;
    std::cout << "-----------------------" << std::endl;
    std::cout << "... ";
    passed = checkNaive(pixSum, pixAvg);
    std::string result = (passed) ? "O.K." : "Failed";
    std::cout << result << std::endl;

    // Comment/uncomment this block if you need less/more verbosity
    // --------------
    std::cout << "Preprocessing Time: " << std::setprecision(6) << preprocessingTime << "s" << std::endl;
    std::cout << "Sum: " << pixSum << " (must be " << testDataNaive.pixelSum << ")" << std::endl;
    std::cout << "Avg: " << pixAvg << " (must be " << testDataNaive.pixelAvg << ")" << std::endl;

    // --------------

    std::cout << "----------- end -----------" << std::endl;
}

bool UnitTestNaive::checkNaive(unsigned int& pixSum, double& pixAvg) const
{
    return (pixSum == testDataNaive.pixelSum) &&
        compare(pixAvg, testDataNaive.pixelAvg);
}
