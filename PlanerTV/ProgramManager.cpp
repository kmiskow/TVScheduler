#include "ProgramManager.h"
void ProgramManager::createProg(vector<string> v)
{

	if (v.size() == 0) {
		return;
	}
	bool partition;
	// check field for if can partition
	if (v[4] == "True")
		partition = true;
	else
		partition = false;

	if (v.front() == "Reklama") {
		cout << "Add added" << endl;
		adds.emplace_back(Reklama(v[1], stoi(v[2]), v[3], partition, stoi(v[5])));

		return;
	}
	// Game is scheduled
	else if (v.front() == "Game") {
		if (v.size() < 9)
			throw std::invalid_argument("Game must be scheduled, insufficent number of arguments");
		else {
			cout << "Game added" << endl;
			priority.emplace_back(Game(v[1], stoi(v[2]), v[3], Program::day(stoi(v[7])), stoi(v[6]), v[8], v[9], partition, stoi(v[5])));

			return;
		}
	}
	else if (v.front() == "BreakfastShow") {
		if (v.size() < 9)
			throw std::invalid_argument("Game must be scheduled, insufficent number of arguments");
		else {
			cout << "Breakfast added" << endl;
			priority.emplace_back(BreakfastShow(v[1], stoi(v[2]), v[3], Program::day(stoi(v[7])), stoi(v[6]), makeVector(v[8]), makeVector(v[9]), partition, stoi(v[5])));

			return;
		}
	}
	else if (v.front() == "Film") {
		cout << "Film added" << endl;
		others.emplace_back(Film(v[1], stoi(v[2]), v[3], partition, stoi(v[5])));
		return;
	}
	else if (v.front() == "Interlude") {
		cout << "Interlude added" << endl;
		interludes.emplace_back(Interlude(v[1], stoi(v[2]), v[3]));
		return;
	}
	else {
		cout << "other added" << endl;
		others.emplace_back(Program(v[1], stoi(v[2]), v[3], partition, stoi(v[5])));
		return;
	}

}

void ProgramManager::sortPrograms()
{
	ranges::sort(others, std::less(), [](auto const& x) {
		return std::visit([](auto const& e) { return e.getTime(); }, x);
		});
	ranges::sort(priority, std::less(), [](auto const& x) {
		return std::visit([](auto const& e) { return e.getStartTime(); }, x);
		});
	sort(adds.begin(), adds.end(), [](const auto& lhs, const auto& rhs)
		{
			return lhs > rhs;
		});
	sort(interludes.begin(), interludes.end(), [](const auto& lhs, const auto& rhs)
		{
			return lhs > rhs;
		});
}

vector<string> ProgramManager::makeVector(const std::string& str)
{
	std::vector<std::string> tokens;
	std::stringstream ss(str);
	std::string token;

	while (std::getline(ss, token, '-')) {
		tokens.push_back(token);
	}
	return tokens;
}

ProgramManager::ProgramManager(string fname)
{
	read_csv(fname);
	sortPrograms();
}

void ProgramManager::read_csv(string fname)
{
	vector<string> row;
	string line, word;

	fstream file(fname, ios::in);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			row.clear();

			stringstream str(line);

			while (getline(str, word, ','))
				row.push_back(word);
			createProg(row);
		}
	}
	else
		cout << "Could not open the file\n";

}

Program* ProgramManager::getPriority(int range, int startTime, Program::day d)
{

	for (int i = 0; i < priority.size(); i++) {
		cout << i << endl;
		if (holds_alternative<BreakfastShow>(priority.at(i))) {
			BreakfastShow& myObj = std::get<BreakfastShow>(priority.at(i));
			if (myObj.getTime() <= range && myObj.getStartTime() >= startTime && myObj.getDay() == d && myObj.getUsed() == false) {
				myObj.setUsed();
				Program* x = &myObj;
				return  x;
			}
		}
		else if (holds_alternative<Game>(priority.at(i))) {
			Game& myObj = std::get<Game>(priority.at(i));
			if (myObj.getTime() <= range && myObj.getStartTime() >= startTime && myObj.getDay() == d && myObj.getUsed() == false) {
				myObj.setUsed();
				Program* x = &myObj;
				return  x;
			}
		}
	}
	return nullptr;
}

Program* ProgramManager::getOther(int range)
{
	if (range == 0) return nullptr;
	vector<int> adds_range;
	for (int i = 0; i < others.size(); i++) {
		if (holds_alternative<Program>(others.at(i))) {
			Program& myObj = std::get<Program>(others.at(i));
			if (myObj.getTime() <= range && myObj.getUsed() == false) {
				adds_range.push_back(i);
			}
		}
		else if (holds_alternative<Film>(others.at(i))) {
			Film& myObj = std::get<Film>(others.at(i));
			if (myObj.getTime() <= range && myObj.getUsed() == false) {
				adds_range.push_back(i);
			}
		}
	}
	// Choose random
	if (adds_range.size() == 0) { return nullptr; }
	int random = rand() % adds_range.size();
	int sel_elem = adds_range[random];

	if (holds_alternative<Program>(others.at(sel_elem))) {
		Program& myObj = std::get<Program>(others.at(sel_elem));
		if (myObj.getTime() <= range && myObj.getUsed() == false) {
			myObj.setUsed();
			Program* x = &myObj;
			return  x;
		}
	}
	else if (holds_alternative<Film>(others.at(sel_elem))) {
		Film& myObj = std::get<Film>(others.at(sel_elem));
		if (myObj.getTime() <= range && myObj.getUsed() == false) {
			myObj.setUsed();
			Program* x = &myObj;
			return  x;
		}
	}
	else
		return nullptr;
}

Program* ProgramManager::getAdd(int range)
{
	if (range == 0) return nullptr;
	vector<int> adds_range;
	for (int i = 0; i < adds.size(); i++) {
		Reklama& myObj = adds.at(i);
		if (myObj.getTime() <= range) {
			adds_range.push_back(i);
		}
	}
	if (!adds_range.empty()) {
		int random = rand() % adds_range.size();
		int sel_elem = adds_range[random];
		Reklama& myObj = adds.at(sel_elem);
		Program* x = &myObj;
		return  x;
	}

	return nullptr;
}

Program* ProgramManager::getInterlude(int range)
{
	if (range == 0) return nullptr;
	for (int i = 0; i < interludes.size(); i++) {
		Interlude& myObj = interludes.at(i);
		if (myObj.getTime() <= range) {
			Program* x = &myObj;
			return  x;
		}
	}
	return nullptr;
}

void ProgramManager::show()
{
	cout << "\t\t\t\tDATABASE" << endl;

	struct VisitPackage {
		void operator()(Game& a) {
			cout << setw(20) << a.getName() << '|' << setw(20) << a.getName() << '|' << setw(10)
				<< a.getTime() << '|' << setw(20) << a.getType() << '|' << setw(10) << a.getStartTime() << endl;
		}
		void operator()(Program& a) {
			cout << setw(20) << a.getName() << '|' << setw(20) << a.getName() << '|' << setw(10)
				<< a.getTime() << '|' << setw(20) << a.getType() << '|' << setw(10) << endl;
		}
		void operator()(BreakfastShow& a) {
			cout << setw(20) << a.getName() << '|' << setw(20) << a.getName() << '|' << setw(10)
				<< a.getTime() << '|' << setw(20) << a.getType() << '|' << setw(10) << a.getStartTime() << endl;
		}
		void operator()(Interlude& a) {
			cout << setw(20) << a.getName() << '|' << setw(20) << a.getName() << '|' << setw(10)
				<< a.getTime() << '|' << setw(20) << a.getType() << '|' << setw(10) << endl;
		}
		void operator()(Film& a) {
			cout << setw(20) << a.getName() << '|' << setw(20) << a.getName() << '|' << setw(10)
				<< a.getTime() << '|' << setw(20) << a.getType() << '|' << setw(10) << endl;
		}
	};
	cout << "PRIORITY:" << endl;
	cout << setw(20) << "Type" << '|' << setw(20) << "Name" << '|' << setw(10)
		<< "Length" << '|' << setw(20) << "Addl. Info" << '|' << setw(10) << "Start Time" << endl;
	for (int i = 0; i < priority.size(); i++)
	{

		visit(VisitPackage(), priority[i]);
	}
	cout << "ADDS:" << endl;
	cout << setw(20) << "Type" << '|' << setw(20) << "Name" << '|' << setw(10)
		<< "Length" << '|' << setw(20) << "Addl. Info" << '|' << setw(10) << endl;
	for (int i = 0; i < adds.size(); i++)
	{
		cout << setw(20) << adds[i].getName() << '|' << setw(20) << adds[i].getName() << '|' << setw(10)
			<< adds[i].getTime() << '|' << setw(20) << adds[i].getType() << '|' << endl;
	}
	cout << "Other:" << endl;
	cout << setw(20) << "Type" << '|' << setw(20) << "Name" << '|' << setw(10)
		<< "Length" << '|' << setw(20) << "Addl. Info" << '|' << endl;
	for (int i = 0; i < others.size(); i++)
	{
		visit(VisitPackage(), others[i]);
	}
}

bool ProgramManager::Priority_empty()
{
	return priority.empty();
}
bool ProgramManager::Others_empty()
{
	return others.empty();
}
bool ProgramManager::Adds_empty()
{
	return adds.empty();
}