// PlanerApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <memory>
#include "../PlanerTV/ProgramManager.h"
#include "../PlanerTV/WeekPlan.h"
using namespace std;

int main()
{
	ProgramManager manager1("C:\\Users\\konra\\source\\repos\\proi-23l-planertv-jkowalski-kmiskow-kjurczynski\\x64\\Debug\\Example.csv");
	WeekPlan plan1;
	plan1.setRule(WeekPlan::rule::num_priority, 5);
	plan1.setRule(WeekPlan::rule::num_ads_after, 5);
	plan1.ConstructPlan(&manager1);
	plan1.print();

	bool database_loaded = false;
	bool plan_loaded = false;
	ProgramManager* manager =  nullptr;
    cout << "Welcome to TV Schedule Planner" << endl;
	string line;
	cout << ">>";
	while (getline(cin, line))
	{
		istringstream usr_input(line);
		vector<string> arg_vec;
		string arg;
		while (getline(usr_input, arg, ' '))
		{
			arg_vec.push_back(arg);
		}
		string cmd_family = arg_vec.at(0);
		if (cmd_family == "quit")
		{
			cout << "Bye";
			return 0;
		}
		else if (cmd_family == "database")
		{
			if(arg_vec.size() < 2) 
			{ 
				cout << "Invalid input" << endl;
				cout << ">>";
				continue;
			}
			string cmd_1 = arg_vec.at(1);
			if (cmd_1 == "load")
			{	
				if (arg_vec.size() < 3)
				{
					cout << "Invalid input" << endl;
					cout << ">>";
					continue;
				}
				if (!database_loaded)
				{
					manager = new ProgramManager(arg_vec.at(2));
					cout << "Database loaded" << endl;
					database_loaded = true;
				}
				else
				{
					cout << "Database already loaded. Do you want to load a new one? [y/n]" << endl;
					cout << ">>";
					string in;
					while (getline(cin, in))
					{
						if (in == "y")
						{
							manager = new ProgramManager(arg_vec.at(2));
							cout << "Database loaded" << endl;
							database_loaded = true;
							break;
						}
						else if (in == "n")
						{
							cout << "Database not loaded" << endl;
							break;
						}
						else
						{
							cout << "Input invalid. Do you want to load a new one? [y/n]" << endl;
							cout << ">>";
						}
					}
				}
			}
			else if (cmd_1 == "print" && database_loaded)
				manager->show();
			else
			{
				cout << "Invalid input 2" << endl;
			}
		}
		else if (cmd_family == "plan")
		{
			if (arg_vec.size() < 2)
			{
				cout << "Invalid input" << endl;
				cout << ">>";
				continue;
			}
			string cmd_1 = arg_vec.at(1);
			if (cmd_1 == "load")
			{
				if (!plan_loaded)
				{
					cout << "Plan loaded" << endl;
					plan_loaded = true;
				}
				else
				{
					cout << "Plan already loaded. Do you want to discard changes and load a new one? [y/n]" << endl;
					cout << ">>";
					string in;
					while (getline(cin, in))
					{
						if (in == "y")
						{
							cout << "Plan loaded" << endl;
							plan_loaded = true;
							break;
						}
						else if (in == "n")
						{
							cout << "Plan not loaded" << endl;
							break;
						}
						else
						{
							cout << "Input invalid. Do you want to discard changes and load a new one? [y/n]" << endl;
							cout << ">>";
						}
					}
				}
			}
			else if (cmd_1 == "new")
			{
				if (!plan_loaded)
				{
					cout << "Created empty plan" << endl;
					plan_loaded = true;
				}
				else
				{
					cout << "Plan already loaded. Do you want to discard changes and load a new one? [y/n]" << endl;
					cout << ">>";
					string in;
					while (getline(cin, in))
					{
						if (in == "y")
						{
							cout << "Plan loaded" << endl;
							plan_loaded = true;
							break;
						}
						else if (in == "n")
						{
							cout << "Plan not loaded" << endl;
							break;
						}
						else
						{
							cout << "Input invalid. Do you want to discard changes and load a new one? [y/n]" << endl;
							cout << ">>";
						}
					}				
				}
			}
			else if (cmd_1 == "print")
			{
				cout << "Printed plan" << endl;
			}
			else if (cmd_1 == "save")
			{
				cout << "Saved plan" << endl;
			}
			else
			{
				cout << "Invalid input" << endl;
			}
		}
		else
		{
			cout << "Invalid input" << endl;
		}
		cout << ">>";
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
