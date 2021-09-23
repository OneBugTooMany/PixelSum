#include <iostream>
#include "Tests.h"
#include "TestsNaive.h"


int main()
{
    std::cout << "############################################" << std::endl;
    std::cout << "----------------  PIXEL SUM ----------------" << std::endl;
    std::cout << "---------------  START TESTS ---------------" << std::endl;
	std::cout << "---------------  For O(1) ---------------" << std::endl;
    std::cout << "############################################" << std::endl;

    Tests tests = Tests();
    tests.run();

    std::cout << "-------------------  END -------------------" << std::endl;
    std::cout << "############################################" << std::endl;

	std::cout << "############################################" << std::endl;
	std::cout << "----------------  PIXEL SUM ----------------" << std::endl;
	std::cout << "---------------  START TESTS ---------------" << std::endl;
	std::cout << "---------------  For 0(n) ------------------" << std::endl;
	std::cout << "############################################" << std::endl;

	TestsNaive testsNaive = TestsNaive();
	testsNaive.runNaive();

	std::cout << "-------------------  END -------------------" << std::endl;
	std::cout << "############################################" << std::endl;
}

