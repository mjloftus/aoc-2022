#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;

inline void incCycle(int& cycle, int registerX, int& totalSignalStrength, vector<vector<char>>& screen, int count = 1) {
	for (int i = 0; i < count; ++i) {
		int pixelCount = cycle;
		++cycle;
		if (cycle % 40 == 20) totalSignalStrength += cycle * registerX;
		if (pixelCount % 40 >= registerX - 1 && pixelCount % 40 <= registerX + 1) screen[pixelCount / 40][pixelCount % 40] = '#';
	}
}

int main(int argc, char** argv) {
	string inputFile = "input.txt";
	if (argc > 1) inputFile = argv[1];
	ifstream file(inputFile);
	string line;
	int cycle = 0;
	int registerX = 1;
	int totalSignalStrength = 0;
	vector<vector<char>> screen(6, vector<char>(40, '.'));

	while (getline(file, line)) {
		istringstream is(line);
		string op;

		while (is >> op) {
			if (op == "noop") incCycle(cycle, registerX, totalSignalStrength, screen);
			else if (op == "addx") {
				int arg1;
				is >> arg1;
				incCycle(cycle, registerX, totalSignalStrength, screen, 2);
				registerX += arg1;
			}
		}
	}

	cout << "Part 1: " << totalSignalStrength << endl;
	cout << "Part 2: " << endl;
	for (int i = 0; i < screen.size(); ++i) {
		for (int j = 0; j < screen[i].size(); ++j) {
			cout << screen[i][j];
		}
		cout << endl;
	}

	return 0;
}