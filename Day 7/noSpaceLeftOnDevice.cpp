#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::map;
using std::queue;
using std::string;
using std::unordered_set;
using std::vector;

/* long long calcSize(dir* root, long long* sum) {
	cout << "calc" << endl;
	if (root->childDirs.size() != 0) {
		for (int i = 0; i < root->childDirs.size(); ++i) {
			root->size += calcSize(root->childDirs[i], sum);
		}
	}
	if (root->size <= 100000) *sum += root->size;
	return root->size;
} */

typedef struct dir{
	vector<dir*> childDirs;
	dir* parent;
	long long size = 0;
	string name = "";

	dir(string name, dir* parent)
		: name(name), parent(parent) { cout << "creating " << this << " with parent " << parent << endl; }
} dir;

int main(int argc, char** argv) {
	string inputFile = "input.txt";
	if (argc > 1) inputFile = argv[1];
	ifstream file(inputFile);
	string line;
	map<string, dir*> dirs;
	dir* curDir = nullptr;
	dir* needToPropagate = nullptr;
	unordered_set<string> calledLs;
	bool skippingLs = false;

	while (getline(file, line)) {
		istringstream is(line);
		string x;

		while (is >> x) {
			cout << x << endl;
			if (skippingLs && x != "$") continue;
			if (x == "$") {
				skippingLs = false;
				if (needToPropagate) {
					long long size = needToPropagate->size;
					while (needToPropagate->parent) {
						cout << "propagating " << size << " to " << needToPropagate->parent->name << endl;
						long long oldSize = needToPropagate->parent->size;
						needToPropagate->parent->size += size;
						if (oldSize > needToPropagate->parent->size) cout << "overflow detected!" << endl;
						needToPropagate = needToPropagate->parent;
					}
					needToPropagate = nullptr;
				}
				is >> x;
				cout << x << endl;
				if (x == "cd") {
					is >> x;
					cout << x << endl;
					if (x == "..") curDir = curDir->parent ? curDir->parent : curDir;
					else {
						string name = x;
						dir* curName = curDir;
						while (curName) {
							if (curName->name != "/") name = curName->name + "/" + name;
							else name = "/" + name;
							curName = curName->parent;
						}
						if (dirs.find(name) == dirs.end()) dirs[name] = new dir(name, curDir);
						curDir = dirs.find(name)->second;
					}
				}
				else if (x == "ls") {
					if (calledLs.find(curDir->name) != calledLs.end()) {
						cout << "calling ls twice" << endl;
						skippingLs = true;
					}
					calledLs.insert(curDir->name);
				}
			}
			else if (x == "dir") {
				is >> x;
				cout << x << endl;
				string name = x;
				dir* curName = curDir;
				while (curName) {
					if (curName->name != "/") name = curName->name + "/" + name;
					else name = "/" + name;
					curName = curName->parent;
				}
				if (dirs.find(name) == dirs.end()) dirs[name] = new dir(name, curDir);
				curDir->childDirs.push_back(dirs[name]);
			}
			else {
				long long oldSize = curDir->size;
				curDir->size += stoi(x);
				if (oldSize > curDir->size) cout << "overflow detected!" << endl;
				is >> x;
				cout << x << endl;
				needToPropagate = curDir;
			}
		}
	}
	if (needToPropagate) {
		long long size = needToPropagate->size;
		while (needToPropagate->parent) {
			cout << "propagating " << size << " to " << needToPropagate->parent->name << endl;
			long long oldSize = needToPropagate->parent->size;
			needToPropagate->parent->size += size;
			if (oldSize > needToPropagate->parent->size) cout << "overflow detected!" << endl;
			needToPropagate = needToPropagate->parent;
		}
		needToPropagate = nullptr;
	}

	cout << "here1" << endl;
	long long totalSize = 0;
	long long oldSize = 0;
	long long minToDelete = 30000000 - (70000000 - dirs["/"]->size);
	long long currentMin = dirs["/"]->size;
	for (auto it = dirs.begin(); it != dirs.end(); ++it) {
		cout << it->second->name << " " << it->second->size << endl;
		oldSize = totalSize;
		if (it->second->size <= 100000) totalSize += it->second->size;
		if (oldSize > totalSize) cout << "overflow detected!";
		if (it->second->size >= minToDelete && it->second->size < currentMin) currentMin = it->second->size;
	}
	// cout << calcSize(dirs["/"], &totalSize);
	cout << "here2" << endl;
	cout << "Part 1: " << totalSize << endl;
	cout << "Part 2: " << currentMin << endl;

	return 0;
}