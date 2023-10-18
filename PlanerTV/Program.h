#pragma once
#include <string>

using namespace std;

constexpr int SECONDS_IN_DAY = 86400;

class Program
{
private:
	string name;
	string type;
	int time;
	int min_age;
	bool can_partition;
	bool used = false;
protected:
	bool scheduled;
public:
	Program(string my_name, int my_time, string my_type, bool my_can_partition = true, int my_min_age=0) :
		name(my_name), time(my_time), type(my_type), can_partition(my_can_partition), min_age(my_min_age), scheduled(false) {};
	Program() : name("NULL"), time(0), type("NULL"), can_partition(false), min_age(0), scheduled(false) {};
	static Program NotFound;
	enum day { monday = 0, tuesday = 1, wednesday = 2, thursday = 3, friday = 4, saturday = 5, sunday = 6 };
	virtual ~Program() = default;
	//getters
	bool getUsed();
	void setUsed();
	const string getName() const;
	const int getTime() const;
	const int getMinAge() const;
	const bool canPartition() const;
	const string getType() const;
	bool isScheduled() const;
	// Operator <<
	// operator >
};
bool operator>(const Program& left, const Program& right);
ostream& operator<<(ostream& os, const Program& prog);
