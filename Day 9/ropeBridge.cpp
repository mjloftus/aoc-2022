#include <cstdlib>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::set;
using std::string;
using std::to_string;
using std::vector;

typedef struct {
	int x = 0;
	int y = 0;
} Pos;

void updateTail(Pos* head, Pos* tail) {
	if (abs(head->x - tail->x) <= 1 && abs(head->y - tail->y) <= 1) return;
	if (abs(head->x - tail->x) > 1 && abs(head->y - tail->y) <= 1) {
		tail->y = head->y;
		tail->x += (head->x - tail->x) / 2;
	}
	else if (abs(head->y - tail->y) > 1 && abs(head->x - tail->x) <= 1) {
		tail->x = head->x;
		tail->y += (head->y - tail->y) / 2;
	}
	else {
		tail->x += (head->x - tail->x) / 2;
		tail->y += (head->y - tail->y) / 2;
	}
}

int main(int argc, char** argv) {
	string inputFile = "input.txt";
	if (argc > 1) inputFile = argv[1];
	ifstream file(inputFile);
	string line;
	vector<Pos*> knots(10);
	for (int i = 0; i < 10; ++i) knots[i] = new Pos();
	set<string> secondKnotPositions;
	set<string> finalKnotPositions;

	while (getline(file, line)) {
		istringstream is(line);
		char d;
		int l;

		while (is >> d >> l) {
			for (int i = 0; i < l; ++i) {
				if (d == 'U') ++knots[0]->y;
				else if (d == 'D') --knots[0]->y;
				else if (d == 'R') ++knots[0]->x;
				else if (d == 'L') --knots[0]->x;
				for (int i = 1; i < knots.size(); ++i) updateTail(knots[i-1], knots[i]);
				secondKnotPositions.insert(to_string(knots[1]->x) + "-" + to_string(knots[1]->y));
				finalKnotPositions.insert(to_string(knots[9]->x) + "-" + to_string(knots[9]->y));
			}
		}
	}

	cout << "Part 1: " << secondKnotPositions.size() << endl;
	cout << "Part 2: " << finalKnotPositions.size() << endl;

	return 0;
}