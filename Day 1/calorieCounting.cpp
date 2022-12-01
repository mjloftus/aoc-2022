#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::priority_queue;
using std::string;

int main(int argc, char** argv) {
	string inputFile = "input.txt";
	if (argc > 1) inputFile = argv[1];
	ifstream file(inputFile);
	string line;
	priority_queue<int> calories;
	int total = 0;

	while (getline(file, line)) {
		istringstream is(line);
		int x;
		if (is >> x) {
			total += x;
		}
		else {
			calories.push(total);
			total = 0;
		}
	}
	if (total > 0) calories.push(total);
	cout << "Part 1: " << calories.top() << endl;
	total = 0;
	for (int i = 0; i < 3; ++i) {
		total += calories.top();
		calories.pop();
	}
	cout << "Part 2: " << total;
	return 0;
}