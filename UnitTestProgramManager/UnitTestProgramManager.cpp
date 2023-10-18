#include "pch.h"
#include "CppUnitTest.h"
#include "../PlanerTV/ProgramManager.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestProgramManager
{
	TEST_CLASS(UnitTestProgramManager)
	{
	public:
		
		TEST_METHOD(ProgramManagerConstruct) {
			ProgramManager manager("../PlanerTV/Example.csv");
		}
	};
}
