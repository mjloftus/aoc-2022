#include <fstream>
#include <iostream>
#include <queue>
#include <map>
#include <sstream>
#include <string>


using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::queue;
using std::map;
using std::string;

int main(int argc, char** argv) {
	string inputFile = "input.txt";
	if (argc > 1) inputFile = argv[1];
	ifstream file(inputFile);
	string line;
	queue<char> charStream;
	map<char, int> seenCharCount;
	int packetCount = 0;
	int count = 0;

	while (getline(file, line)) {
		istringstream is(line);
		char x;

		while (is >> x) {
			++count;
			if (!packetCount && charStream.size() == 4) {
				if (--seenCharCount[charStream.front()] == 0) seenCharCount.erase(charStream.front());
				charStream.pop();
			}
			else if (charStream.size() == 14) {
				if (--seenCharCount[charStream.front()] == 0) seenCharCount.erase(charStream.front());
				charStream.pop();
			}
			++seenCharCount[x];
			charStream.push(x);
			if (seenCharCount.size() == 4) packetCount = count;
			if (seenCharCount.size() == 14) break;
		}
	}

	cout << "Part 1: " << packetCount << endl;
	cout << "Part 2: " << count << endl;

	return 0;
}