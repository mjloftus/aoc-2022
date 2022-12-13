#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>
#include <queue>

using std::cout;
using std::endl;
using std::hash;
using std::ifstream;
using std::istringstream;
using std::pair;
using std::string;
using std::unordered_set;
using std::vector;
using std::queue;

typedef struct pair_hash {
	size_t operator()(const pair<int, int> &pair) const {
		return hash<int>()(pair.first) ^ hash<int>()(pair.second);
	}
} pair_hash;

int main(int argc, char** argv) {
	string inputFile = "input.txt";
	if (argc > 1) inputFile = argv[1];
	ifstream file(inputFile);
	string line;
	vector<vector<signed char>> elevation;
	unordered_set<pair<int, int>, pair_hash> seenFront, seenEnd;
	queue<pair<int, int>> fromStart;
	queue<pair<int, int>> fromEnd;

	while (getline(file, line)) {
		istringstream is(line);
		signed char height;
		vector<signed char> heights;
		while (is >> height) {
			if (height == 'S' || height == 'a') {
				fromStart.push(pair<int, int>(elevation.size(), heights.size()));
				height = 'a';
			}
			if (height == 'E') {
				fromEnd.push(pair<int, int>(elevation.size(), heights.size()));
				height = 'z';
			}
			heights.push_back(height);
		}
		elevation.push_back(heights);
	}

	int count = 0;

	while (!fromStart.empty() || !fromEnd.empty()) {
		queue<pair<int, int>> newFromStart;
		bool stop = false;
		while (!fromStart.empty()) {
			pair<int, int> cur = fromStart.front();
			if (seenEnd.find(cur) != seenEnd.end()) {
				stop = true;
				break;
			};
			fromStart.pop();
			if (seenFront.find(cur) != seenFront.end()) continue;
			seenFront.insert(cur);
			int row = cur.first;
			int col = cur.second;
			cout << "looking at " << row << " " << col << " from front count " << count << endl;
			signed char curEle = elevation[row][col];
			if (row > 0 && elevation[row-1][col] - curEle <= 1) newFromStart.push(pair<int, int>(row-1, col));
			if (row < elevation.size()-1 && elevation[row+1][col] - curEle <= 1) newFromStart.push(pair<int, int>(row+1, col));
			if (col > 0 && elevation[row][col-1] - curEle <= 1) newFromStart.push(pair<int, int>(row, col-1));
			if (col < elevation[0].size()-1 && elevation[row][col+1] - curEle <= 1) newFromStart.push(pair<int, int>(row, col+1));
		}
		++count;
		if (stop) break;
		fromStart = newFromStart;
		queue<pair<int, int>> newFromEnd;
		while (!fromEnd.empty()) {
			pair<int, int> cur = fromEnd.front();
			if (seenFront.find(cur) != seenFront.end()) {
				stop = true;
				break;
			};
			fromEnd.pop();
			if (seenEnd.find(cur) != seenEnd.end()) continue;
			seenEnd.insert(cur);
			int row = cur.first;
			int col = cur.second;
			cout << "looking at " << row << " " << col << " from back count " << count << endl;
			signed char curEle = elevation[row][col];
			if (row > 0 && curEle - elevation[row-1][col] <= 1) newFromEnd.push(pair<int, int>(row-1, col));
			if (row < elevation.size()-1 && curEle - elevation[row+1][col] <= 1) newFromEnd.push(pair<int, int>(row+1, col));
			if (col > 0 && curEle - elevation[row][col-1] <= 1) newFromEnd.push(pair<int, int>(row, col-1));
			if (col < elevation[0].size()-1 && curEle - elevation[row][col+1] <= 1) newFromEnd.push(pair<int, int>(row, col+1));
		}
		++count;
		if (stop) break;
		fromEnd = newFromEnd;
	}

	//cout << "Part 1: " << count-1 << endl;
	cout << "Part 2: " << count-2 << endl;

	return 0;
}