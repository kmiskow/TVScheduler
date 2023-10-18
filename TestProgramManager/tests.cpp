#include <iostream>
#include "../PlanerTV/ProgramManager.h"
using namespace std;

// Main() function: where the execution of program begins
int main()
{
	
	ProgramManager manager("../PlanerTV/Example.csv");
	for (auto i : manager.priority)
		std::cout << i << ' ';

    return 0;
}