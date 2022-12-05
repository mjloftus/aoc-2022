#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::queue;
using std::stack;
using std::string;
using std::vector;

int main(int argc, char** argv) {
	string inputFile = "input.txt";
	if (argc > 1) inputFile = argv[1];
	ifstream file(inputFile);
	string line;
	vector<stack<char>> toReverse;
	vector<stack<char>> stacks;

	while (getline(file, line)) {
		istringstream is(line);
		is >> std::noskipws;
		char c;
		int charCount = 0;
		int x, a, b;

		while (is.peek() != EOF) {
			// setup
			while (is.peek() == ' ') {
				is >> c;
				++charCount;
			}
			if (is.peek() == '[') {
				is >> c >> c;
				charCount += 2;
				int queueNum = charCount / 4;
				while (queueNum + 1 > toReverse.size()) toReverse.push_back(stack<char>());
				toReverse[queueNum].push(c);
				is >> c >> c;
				charCount += 2;
			}
			else if (is.peek() == '1') {
				is >> c;
				for (int i = 0; i < toReverse.size(); ++i) {
					stacks.push_back(stack<char>());
					while (!toReverse[i].empty()) {
						stacks[i].push(toReverse[i].top());
						toReverse[i].pop();
					}
				}
				break;
			}

			// moves
			else if (is.peek() == 'm') {
				for (int i = 0; i < 5; ++i) is >> c;
				is >> x;
				for (int i = 0; i < 6; ++i) is >> c;
				is >> a;
				for (int i = 0; i < 4; ++i) is >> c;
				is >> b;
				--a;
				--b;
				/* PART 1
				for (int i = 0; i < x; ++i) {
					stacks[b].push(stacks[a].top());
					stacks[a].pop();
				}
				*/
				stack<char> toMove;
				for (int i = 0; i < x; ++i) {
					toMove.push(stacks[a].top());
					stacks[a].pop();
				}
				while (!toMove.empty()) {
					stacks[b].push(toMove.top());
					toMove.pop();
				}
			}
			else break;
		}
	}

	string topCrates;
	for (int i = 0; i < stacks.size(); ++i) topCrates += stacks[i].top();

	// cout << "Part 1: " << topCrates << endl;
	cout << "Part 2: " << topCrates << endl;

	return 0;
}