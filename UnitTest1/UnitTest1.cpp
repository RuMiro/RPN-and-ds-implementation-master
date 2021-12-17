
#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include "RPN_calc.h"

#include "InfToRPN_Convert.h"

//#include "InfToRPN_Convert.h"
//
//#include <iostream>
//#include <string>


using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:
        TEST_METHOD(SimpleEcuationsRPN1) {
            Assert::IsTrue("1 2 4 * + " == RPN("1 + 2 * 4", 10));
        }

        TEST_METHOD(SimpleEcuationsRPN2) {
            Assert::IsTrue("57 5 1 - 4 2 ^ / + " == RPN("57 + (5 - 1) / 4^2", 100));
        }
        TEST_METHOD(SimpleEcuationsRPN3) {
            Assert::IsTrue("48 8 9 * + 45 pi * 5 * / 8 + " == RPN("(48 + 8 * 9) / (45 * pi * 5) + 8", 100));
        }

        TEST_METHOD(SimpleEcuationsRPN4) {
            Assert::IsTrue("9 8 * cos " == RPN("cos (9 * 8)", 100));
        }

        TEST_METHOD(SimpleEcuationsRPN5) {
            Assert::IsTrue("8 7 * 9 pi * 2 / + sin 5 / 9 pi * 4 / tan + " == RPN("tan(8 * 7 + 9 * pi / 2) / 5 + sin(9 * pi / 4)", 120));
        }

        TEST_METHOD(SimpleEcuationsRPN6) {
            Assert::IsTrue("5 log " == RPN("log 5", 10));
        }
   
    };
}