#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::string;

int main(int argc, char** argv) {
	string inputFile = "input.txt";
	if (argc > 1) inputFile = argv[1];
	ifstream file(inputFile);
	string line;
	int subsumedPairs = 0;
	int overlappingPairs = 0;

	while (getline(file, line)) {
		istringstream is(line);
		int a, b, x, y;
		char c;

		if (is >> a >> c >> b >> c >> x >> c >> y) {
			if ((a >= x && a <= y) || (y >= a && y <= b) || (b >= x && b <= y) || (x >= a && x <= b)) {
				++overlappingPairs;
				if ((a >= x && b <= y) || (x >= a && y <= b)) ++subsumedPairs;
			}
		}
	}

	cout << "Part 1: " << subsumedPairs << endl;
	cout << "Part 2: " << overlappingPairs << endl;

	return 0;
}