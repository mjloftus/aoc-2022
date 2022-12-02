#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::string;

int scoreGame(char col1, char col2) {
	int score = 0;
	switch(col2) {
		case 'X':
			score += 1;
			switch(col1) {
				case 'A':
					score += 3;
					break;
				case 'B':
					score += 0;
					break;
				case 'C':
					score += 6;
					break;
			}
			break;
		case 'Y':
			score += 2;
			switch(col1) {
				case 'A':
					score += 6;
					break;
				case 'B':
					score += 3;
					break;
				case 'C':
					score += 0;
					break;
			}
			break;
		case 'Z':
			score += 3;
			switch(col1) {
				case 'A':
					score += 0;
					break;
				case 'B':
					score += 6;
					break;
				case 'C':
					score += 3;
					break;
			}
			break;
	}
	return score;
}

int main(int argc, char** argv) {string inputFile = "input.txt";
	if (argc > 1) inputFile = argv[1];
	ifstream file(inputFile);
	string line;
	int score1 = 0;
	int score2 = 0;

	while (getline(file, line)) {
		istringstream is(line);
		char x, y;
		if (is >> x >> y) {
			score1 += scoreGame(x, y);
			if (y == 'X') {
				if (x == 'A') score2 += scoreGame(x, 'Z');
				if (x == 'B') score2 += scoreGame(x, 'X');
				if (x == 'C') score2 += scoreGame(x, 'Y');
			}
			if (y == 'Y') {
				if (x == 'A') score2 += scoreGame(x, 'X');
				if (x == 'B') score2 += scoreGame(x, 'Y');
				if (x == 'C') score2 += scoreGame(x, 'Z');
			}
			if (y == 'Z') {
				if (x == 'A') score2 += scoreGame(x, 'Y');
				if (x == 'B') score2 += scoreGame(x, 'Z');
				if (x == 'C') score2 += scoreGame(x, 'X');
			}
		}
	}

	cout << "Part 1: " << score1 << endl;
	cout << "Part 2: " << score2 << endl;

	return 0;
}