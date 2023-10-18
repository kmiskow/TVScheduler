#include <iostream>
#include "../PlanerTV/ProgramManager.h"
using namespace std;

// Main() function: where the execution of program begins
int main()
{
    // prints hello world
    //cout << "Hello World";
    ProgramManager manager("../../PlanerTV/Example.csv");
    //if (manager.Others_empty())
    //    cout << "Others Empty";
    //else
    //    cout << "Others Not Empty"<< endl;
    struct VisitBaseSchedule {
        void operator()(Game& a) { if (a.getUsed() == false) cout << a.getName() << " Duration: " << a.getTime() << " Day: "<< a.getDay() << " Start time: " << a.getStartTime() << endl; }
        void operator()(ScheduledProgram& a) { if (a.getUsed() == false) cout << a.getName() << " Duration: " << a.getTime() << " Day: " << a.getDay()<< " Start time: " << a.getStartTime() << endl;}
        void operator()(BreakfastShow& a) { if (a.getUsed() == false) cout << a.getName() << " Duration: " << a.getTime() << " Day: " << a.getDay() <<" Start time: " << a.getStartTime() << endl;}
    };

    manager.show();
    //cout << endl;
    //cout << "Programs in priority:"<< endl;
    //for(auto& prog : manager.priority) {
    //    std::visit(VisitBaseSchedule(), prog);
    //}
    
    //std::cout << std::endl;
    //cout << Program::day::tuesday << endl;
    //Program* x = manager.getPriority(150000, 1, Program::day::monday);
    //cout << x->getName();

    //for (int i = 0; i < 2; i++) {
    //    x = manager.getAdd(150000);
    //    cout << x->getName() << endl;
    //}

    //cout << endl;
    //cout << "Programs in priority after get:" << endl;
    //for (auto& prog : manager.priority) {
    //    std::visit(VisitBaseSchedule(), prog);
    //}
    string z;
    cin >> z;

}