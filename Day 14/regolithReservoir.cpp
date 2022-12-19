#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;

int main(int argc, char** argv) {
	string inputFile = "input.txt";
	if (argc > 1) inputFile = argv[1];
	ifstream file(inputFile);
	string line;
	int minX = -1, maxX = -1, minY = -1, maxY = -1;
	vector<vector<char>> slice(200, vector<char>(1000, '.'));

	while (getline(file, line)) {
		int x1, x2, y1, y2;
		char c;
		istringstream is(line);
		is >> x1 >> c >> y1;
		if (minX == -1 || x1 < minX) minX = x1;
		if (maxX == -1 || x1 > maxX) maxX = x1;
		if (minY == -1 || y1 < minY) minY = y1;
		if (maxY == -1 || y1 > maxY) maxY = y1;
		while (is >> c >> c) {
			is >> x2 >> c >> y2;
			if (x1 == x2) {
				int yLow = y1 < y2 ? y1 : y2;
				int yHigh = y1 < y2 ? y2 : y1;
				for (int y = yLow; y <= yHigh; ++y) {
					slice[y][x1] = '#';
				}
			}
			else {
				int xLow = x1 < x2 ? x1 : x2;
				int xHigh = x1 < x2 ? x2 : x1;
				for (int x = xLow; x <= xHigh; ++x) {
					slice[y1][x] = '#';
				}
			}
			x1 = x2;
			y1 = y2;
			if (minX == -1 || x1 < minX) minX = x1;
			if (maxX == -1 || x1 > maxX) maxX = x1;
			if (minY == -1 || y1 < minY) minY = y1;
			if (maxY == -1 || y1 > maxY) maxY = y1;
		}
	}

	int unitsOfSand = 0;
	int unitsOfSandEndless = -1;
	while (true) {
		int curX = 500;
		int curY = 0;
		while (true) {
			if (unitsOfSandEndless == -1 && (curY > maxY || curX < minX || curX > maxX)) unitsOfSandEndless = unitsOfSand;
			if (curY == maxY + 1) {
				slice[curY][curX] = 'O';
				++unitsOfSand;
				break;
			}
			if (slice[curY+1][curX] == '.') ++curY;
			else if (slice[curY+1][curX-1] == '.') {
				++curY;
				--curX;
			}
			else if (slice[curY+1][curX+1] == '.') {
				++curY;
				++curX;
			}
			else {
				slice[curY][curX] = 'O';
				++unitsOfSand;
				break;
			}
		}
		if (curX == 500 && curY == 0) break;
	}
	
	cout << "Part 1: " << unitsOfSandEndless << endl;
	cout << "Part 2: " << unitsOfSand << endl;

	return 0;
}