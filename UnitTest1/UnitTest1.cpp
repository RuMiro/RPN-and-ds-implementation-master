#include "pch.h"
#include "CppUnitTest.h"
#include "RPN_calc.h"
#include "InfToRPN_Convert.h"

#include <iostream>
#include <string>

using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:
        TEST_METHOD(SimpleEcuationsRPN) {
            Assert::IsTrue("1 2 4 * + " == RPN("1 + 2 * 4", 10));
            Assert::IsTrue("57 5 1 - 4 2 ^ / + " == RPN("57 + (5 - 1) / 4^2", 100));
            Assert::IsTrue("48 8 9 * + 45 pi * k * / 8 + " == RPN("(48 + 8 * 9) / (45 * pi * k) + 8", 100));
        }

        TEST_METHOD(FunctionsRPN) {
            Assert::IsTrue("9 8 * cos " == RPN("cos (9 * 8)", 10));
            Assert::IsTrue("8 7 * 9 pi * 2 / + sin 5 / 9 pi * 4 / ctg + " == RPN("sin(8 * 7 + 9 * pi / 2) / 5 + ctg(9 * pi / 4)", 120));
            Assert::IsTrue("5 lg" == RPN("lg 5", 10));
        }
   
    };
}