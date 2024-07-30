#include "pch.h"
#include "CppUnitTest.h"
#include "../SWE_App/Singleton.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalculatorProcessorTests
{
	TEST_CLASS(CalculatorProcessorTests)
	{
	public:

		TEST_METHOD(TestMethod101)
		{
			Singleton* CalculatorInstance = Singleton::getInstance();
			Assert::AreEqual(CalculatorInstance->Calculate("2 + 2"), 4.0);
		}
		TEST_METHOD(TestMethod102)
		{
			Singleton* CalculatorInstance = Singleton::getInstance();
			Assert::AreEqual(CalculatorInstance->Calculate("2 +  Sin 6"), 1.720585);
		}
		TEST_METHOD(TestMethod103)
		{
			Singleton* CalculatorInstance = Singleton::getInstance();
			Assert::AreEqual(CalculatorInstance->Calculate("2 + Cos 6"), 2.960170);
		}
		TEST_METHOD(TestMethod104)
		{
			Singleton* CalculatorInstance = Singleton::getInstance();
			Assert::AreEqual(CalculatorInstance->Calculate("2 + Tan 6"), 1.708994);
		}
		TEST_METHOD(TestMethod105)
		{
			Singleton* CalculatorInstance = Singleton::getInstance();
			Assert::AreEqual(CalculatorInstance->Calculate("2 - -3"), 5.000000);
		}
		TEST_METHOD(TestMethod106)
		{
			Singleton* CalculatorInstance = Singleton::getInstance();
			Assert::AreEqual(CalculatorInstance->Calculate("-2 x -2"), 4.0);
		}
		TEST_METHOD(TestMethod107)
		{
			Singleton* CalculatorInstance = Singleton::getInstance();
			Assert::AreEqual(CalculatorInstance->Calculate("2 / -2"), -1.000000);
		}
		TEST_METHOD(TestMethod108)
		{
			Singleton* CalculatorInstance = Singleton::getInstance();
			Assert::AreEqual(CalculatorInstance->Calculate("54325423 x 1234567890"), 67068422846467472.000000);
		}
		TEST_METHOD(TestMethod109)
		{
			Singleton* CalculatorInstance = Singleton::getInstance();
			Assert::AreEqual(CalculatorInstance->Calculate("55 % 2"), 1.0);
		}
		TEST_METHOD(TestMethod110)
		{
			Singleton* CalculatorInstance = Singleton::getInstance();
			Assert::AreEqual(CalculatorInstance->Calculate("8.95423 x 6 / 3.2 + -6 +  Sin 9.9"), 10.331645);
		}
	};
}
