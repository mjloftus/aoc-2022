#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::string;
using std::unordered_set;
using std::vector;

int main(int argc, char** argv) {
	string inputFile = "input.txt";
	if (argc > 1) inputFile = argv[1];
	ifstream file(inputFile);
	string line;
	vector<vector<int>> trees;

	while (getline(file, line)) {
		istringstream is(line);
		char x;
		vector<int> row;

		while (is >> x) {
			row.push_back(stoi(string(&x)));
		}
		trees.push_back(row);
	}

	unordered_set<int> seenTrees;
	vector<vector<int>> scenicScores;
	// l to r
	for (int r = 0; r < trees.size(); ++r) {
		int max = 0;
		int scenicScore = 0;
		vector<int> scenicRow;
		for (int c = 0; c < trees[r].size(); ++c) {
			if (c == 0 || trees[r][c] > max) {
				seenTrees.insert(r * trees[r].size() + c);
				max = trees[r][c];
			}
			if (c == 0) scenicScore = 0;
			else scenicScore = 1;
			while (c - scenicScore > 0 && trees[r][c-scenicScore] < trees[r][c]) scenicScore += scenicRow[c - scenicScore];
			scenicRow.push_back(scenicScore);
		}
		scenicScores.push_back(scenicRow);
	}
	// r to l
	for (int r = 0; r < trees.size(); ++r) {
		int max = 0;
		int scenicScore = 0;
		vector<int> scenicRow(trees[0].size(), 0);
		for (int c = trees[r].size()-1; c >= 0; --c) {
			if (c == trees[r].size()-1 || trees[r][c] > max) {
				seenTrees.insert(r * trees[r].size() + c);
				max = trees[r][c];
			}
			if (c == trees[r].size()-1) scenicScore = 0;
			else scenicScore = 1;
			while (c + scenicScore < trees[r].size()-1 && trees[r][c+scenicScore] < trees[r][c]) scenicScore += scenicRow[c + scenicScore];
			scenicRow[c] = scenicScore;
			scenicScores[r][c] *= scenicScore;
		}
	}
	// t to b
	for (int c = 0; c < trees[0].size(); ++c) {
		int max = 0;
		int scenicScore = 0;
		vector<int> scenicCol;
		for (int r = 0; r < trees.size(); ++r) {
			if (r == 0 || trees[r][c] > max) {
				seenTrees.insert(r * trees[r].size() + c);
				max = trees[r][c];
			}
			if (r == 0) scenicScore = 0;
			else scenicScore = 1;
			while (r - scenicScore > 0 && trees[r-scenicScore][c] < trees[r][c]) scenicScore += scenicCol[r - scenicScore];
			scenicCol.push_back(scenicScore);
			scenicScores[r][c] *= scenicScore;
		}
	}
	// b to t
	int scenicMax = 0;
	for (int c = 0; c < trees[0].size(); ++c) {
		int max = 0;
		int scenicScore = 0;
		vector<int> scenicCol(trees.size(), 0);
		for (int r = trees.size()-1; r >= 0; --r) {
			if (r == trees.size()-1 || trees[r][c] > max) {
				seenTrees.insert(r * trees[r].size() + c);
				max = trees[r][c];
			}
			if (r == trees.size()-1) scenicScore = 0;
			else scenicScore = 1;
			while (r + scenicScore < trees.size()-1 && trees[r+scenicScore][c] < trees[r][c]) scenicScore += scenicCol[r + scenicScore];
			scenicCol[r] = scenicScore;
			scenicScores[r][c] *= scenicScore;
			if (scenicScores[r][c] > scenicMax) scenicMax = scenicScores[r][c];
		}
	}

	cout << "Part 1: " << seenTrees.size() << endl;
	cout << "Part 2: " << scenicMax << endl;

	return 0;
}