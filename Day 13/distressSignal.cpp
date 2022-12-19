#include <algorithm>
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

bool packetSort(vector<pair<int, int>> leftP, vector<pair<int, int>> rightP) {
	vector<pair<int, int>> left = leftP;
	vector<pair<int, int>> right = rightP;
	int i = 0;
	bool inOrder = false;
	bool done = false;
	while (i <= left.size()) {
		if (i == left.size()) {
			inOrder = true;
			break;
		}
		if (i >= right.size()) break;
		if (i < left.size() && i < right.size() && left[i].second == right[i].second) {
			while (i < left.size() && i < right.size() && left[i].second == right[i].second) {
				if (left[i].first < 0 && right[i].first < 0 && left[i].first != right[i].first) {
					if (right[i].first < left[i].first) inOrder = true;
					done = true;
					break;
				}
				if (left[i].first < right[i].first) {
					inOrder = true;
					done = true;
					break;
				}
				else if (left[i].first > right[i].first) {
					inOrder = false;
					done = true;
					break;
				}
				else ++i;
			}
			if (done) break;
		}
		else if (i < left.size() && i < right.size()) {
			if (left[i].second > right[i].second) {
				for (int j = 0; j < left[i].second - right[i].second; ++j) right.insert(right.begin()+i+1, pair(-(right[i].second+j+1), right[i].second+j+1));
				right[i].second = left[i].second;
			}
			else {
				for (int j = 0; j < right[i].second - left[i].second; ++j) left.insert(left.begin()+i+1, pair(-(left[i].second+j+1), left[i].second+j+1));
				left[i].second = right[i].second;
			}
		}
	}
	return inOrder;
}

int main(int argc, char** argv) {
	string inputFile = "input.txt";
	if (argc > 1) inputFile = argv[1];
	ifstream file(inputFile);
	string line;
	int indexSum = 0;
	int index = 0;
	vector<pair<int, int>> left;
	vector<pair<int, int>> right;
	vector<vector<pair<int, int>>> packets;
	int depth = 0;

	while (getline(file, line)) {
		if (line.size() == 0) continue;
		istringstream is(line);
		vector<pair<int, int>> cur;
		char x;
		int n;
		while (is.peek() != EOF) {
			if (is.peek() == '[') {
				++depth;
				is >> x;
			}
			else if (is.peek() == ']') {
				cur.push_back(pair(-depth, depth));
				--depth;
				is >> x;
			}
			else if (is.peek() == ',') is >> x;
			else {
				is >> n;
				cur.push_back(pair(n, depth));
			}
		}
		packets.push_back(cur);
		if (packets.size() % 2 == 0) {
			++index;
			vector<pair<int, int>> left = packets[packets.size()-2];
			vector<pair<int, int>> right = packets[packets.size()-1];
			if (packetSort(left, right)) indexSum += index;
		}
	}
	packets.push_back({pair(2, 2), pair(-1, 2), pair(-1, -1)});
	packets.push_back({pair(6, 2), pair(-1, 2), pair(-1, -1)});
	sort(packets.begin(), packets.end(), &packetSort);
	int ind1 = 0, ind2 = 0;
	for (int i = 0; i < packets.size(); ++i) {
		int dividerFound = 0;
		for (int j = 0; j < packets[i].size(); ++j) {
			if (packets[i][j].first > -1 && (packets[i][j].first != 2 && packets[i][j].first != 6)) {
				dividerFound = 0;
				break;
			}
			if (packets[i][j].first > -1) dividerFound += packets[i][j].first;
		}
		if (dividerFound == 2) ind1 = i + 1;
		else if (dividerFound == 6) ind2 = i + 1;
	}

	cout << "Part 1: " << indexSum << endl;
	cout << "Part 2: " << ind1 * ind2 << endl;

	return 0;
}