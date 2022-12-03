#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>

using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::string;
using std::unordered_set;

int main(int argc, char** argv) {
	string inputFile = "input.txt";
	if (argc > 1) inputFile = argv[1];
	ifstream file(inputFile);
	string line;
	int dupPrioritySum = 0;
	int groupCounter = 0;
	int groupPrioritySum = 0;
	unordered_set<char> groupCommonItems;

	while (getline(file, line)) {
		istringstream is(line);
		string sack;
		if (groupCounter % 3 == 0) groupCommonItems.clear();
		unordered_set<char> elfItems;

		if (is >> sack) {
			unordered_set<char> items;
			for (int i = 0; i < sack.size() / 2; ++i) {
				items.insert(sack[i]);
			}
			for (int i = sack.size() / 2; i < sack.size(); ++i) {
				if (items.find(sack[i]) != items.end()) {
					if (sack[i] >= 'a') dupPrioritySum += (sack[i] - 'a' + 1);
					else dupPrioritySum += (sack[i] - 'A' + 27);
					break;
				}
			}
			// part 2
			for (int i = 0; i < sack.size(); ++i) {
				if (groupCounter % 3 == 0) groupCommonItems.insert(sack[i]);
				else if (groupCommonItems.find(sack[i]) != groupCommonItems.end()) {
					if (groupCounter % 3 == 1) elfItems.insert(sack[i]);
					else {
						if (sack[i] >= 'a') groupPrioritySum += (sack[i] - 'a' + 1);
						else groupPrioritySum += (sack[i] - 'A' + 27);
						break;
					}
				}
			}
			if (groupCounter % 3 != 0) groupCommonItems = elfItems;
			++groupCounter;
		}
	}

	cout << "Part 1: " << dupPrioritySum << endl;
	cout << "Part 2: " << groupPrioritySum << endl;

	return 0;
}