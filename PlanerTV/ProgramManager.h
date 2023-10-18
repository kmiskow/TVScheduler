#pragma once
#include <vector>
#include <variant>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "BaseScheduled.h"
#include "BaseUnscheduled.h"
#include <iomanip>
#include <typeinfo>

typedef variant<ScheduledProgram, Game, BreakfastShow> BaseScheduled;
class ProgramManager
{
private:
    /*vector<BaseScheduled> priority;*/
    vector<variant<Program, Film, Game>> others;
    vector<Reklama> adds;
    
    vector<Interlude> interludes;
    void createProg(vector<string> v);//  Internal function to create correct class based on vector of strings, which we posses from csv file
    void sortPrograms(); // Internal function to sort programs in vectors 
    vector<string> makeVector(const std::string& str); // make vector out of string
public:
    ProgramManager(string fname); // Constructor
    void read_csv(string fname); // Function to read csv file, filename - path to file
    vector<BaseScheduled> priority;
    // checkers
    bool Others_empty();
    bool Priority_empty();
    bool Adds_empty();
    // getters
    Program* getPriority(int range,int startTime, Program::day d); // Get next priority program, priority - with set time

    Program* getOther(int range); // Get next program like game, program, film
    Program* getAdd(int range); // Get next add

    Program* getInterlude(int range);
    void show();
};

