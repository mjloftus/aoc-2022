#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::pair;
using std::string;
using std::vector;

int main(int argc, char** argv) {
	string inputFile = "input.txt";
	if (argc > 1) inputFile = argv[1];
	ifstream file(inputFile);
	string line;
	vector<vector<pair<int, int>>> field(4000000, vector<pair<int, int>>());
	const int excludedRow = 2000000;

	while (getline(file, line)) {
		istringstream is(line);
		string s;
		char c;
		int xS, yS, xB, yB;

		is >> s >> s >> c >> c >> xS >> c >> c >> c >> yS >> c >> s >> s >> s >> s >> c >> c >> xB >> c >> c >> c >> yB;
		int manhattanDistance = abs(yS - yB) + abs(xS - xB);
		for (int excludedRow = 0; excludedRow <= 4000000; ++excludedRow) {
			vector<pair<int, int>>& excludedZones = field[excludedRow];
			int yDist = yS > excludedRow ? yS - excludedRow : excludedRow - yS;
			int xRange = manhattanDistance - yDist;
			if (xRange >= 0) {
				int low = xS - xRange;
				int high = xS + xRange;
				int mergeIndex = -1;
				for (int i = 0; i < excludedZones.size(); ++i) {
					if (low >= excludedZones[i].first && high <= excludedZones[i].second) {
						mergeIndex = i;
						break;
					}
					else if (low <= excludedZones[i].first && high >= excludedZones[i].second) {
						excludedZones[i].first = low;
						excludedZones[i].second = high;
						mergeIndex = i;
						break;
					}
					else if (low >= excludedZones[i].first && low <= excludedZones[i].second) {
						excludedZones[i].second = high;
						mergeIndex = i;
						break;
					}
					else if (high >= excludedZones[i].first && high <= excludedZones[i].second) {
						excludedZones[i].first = low;
						mergeIndex = i;
						break;
					}
				}
				if (mergeIndex == -1) excludedZones.push_back(pair(low, high));
				else {
					int low = excludedZones[mergeIndex].first;
					int high = excludedZones[mergeIndex].second;
					for (int i = 0; i < excludedZones.size(); ++i) {
						if (i == mergeIndex) continue;
						if (low >= excludedZones[i].first && high <= excludedZones[i].second) {
							excludedZones.erase(excludedZones.begin() + mergeIndex);
							break;
						}
						else if (low <= excludedZones[i].first && high >= excludedZones[i].second) {
							excludedZones[i].first = low;
							excludedZones[i].second = high;
							excludedZones.erase(excludedZones.begin() + mergeIndex);
							break;
						}
						else if (low >= excludedZones[i].first && low <= excludedZones[i].second) {
							excludedZones[i].second = high;
							excludedZones.erase(excludedZones.begin() + mergeIndex);
							break;
						}
						else if (high >= excludedZones[i].first && high <= excludedZones[i].second) {
							excludedZones[i].first = low;
							excludedZones.erase(excludedZones.begin() + mergeIndex);
							break;
						}
					}
				}
			}
		}
	}

	int excludedSpaces = 0;
	vector<pair<int, int>> singleRow = field[excludedRow];
	for (int i = 0; i < singleRow.size(); ++i) {
		excludedSpaces += singleRow[i].second - singleRow[i].first;
	}

	uint64_t tuningFreq = 1;
	int y;
	for (int i = 0; i < field.size(); ++i) {
		if (field[i][0].first <= 0 && field[i][0].second >= 4000000) continue;
		else {
			int x = 0;
			y = i;
			for (int j = 0; j < field[i].size(); ++j) {
				cout << field[i][j].first << " " << field[i][j].second << endl;
				if (field[i][j].first > 0 && field[i][j].first <= 4000000) x = field[i][j].first - 1;
				else if (field[i][j].second >= 0 && field[i][j].second < 4000000) x = field[i][j].second + 1;
				cout << x << endl;
			}
			tuningFreq = x * 4;
			break;
		}
	}
	
	cout << "Part 1: " << excludedSpaces << endl;
	cout << "Part 2: " << (tuningFreq / 10) << y << endl;

	return 0;
}