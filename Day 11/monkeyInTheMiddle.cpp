#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::queue;
using std::string;
using std::vector;

typedef struct Operation {
	int y;
	virtual void operator()(long long&) = 0;
	Operation(int y)
		: y(y) {}
} Operation;

typedef struct Addition : Operation {
	void operator()(long long& x) override { x += y; }
	Addition(int y)
		: Operation(y) {}
} Addition;

typedef struct Multiplication : Operation {
	void operator()(long long& x) override { x *= y; }
	Multiplication(int y)
		: Operation(y) {}
} Multiplication;

typedef struct Square : Operation {
	void operator()(long long& x) override { x *= x; }
	Square()
		: Operation(0) {}
} Square;

typedef struct Test {
	int y, t, f;
	int operator()(long long x) { return x % y == 0 ? t : f; }
	Test(int y, int trueVal, int falseVal)
		: y(y), t(trueVal), f(falseVal) {}
} Test;

typedef struct Monkey {
	queue<long long> items;
	Operation* operation;
	Test test;
	long long inspectCount = 0;
	Monkey(queue<long long> items, Operation* operation, Test test)
		: items(items), operation(operation), test(test) {}
} Monkey;

int main(int argc, char** argv) {
	string inputFile = "input.txt";
	if (argc > 1) inputFile = argv[1];
	ifstream file(inputFile);
	string line;
	vector<Monkey> monkeys;
	int modulo = 1;

	queue<long long> startingItems;
	Operation* op;
	int test, trueVal, falseVal;

	while (getline(file, line)) {
		istringstream is(line);
		string s;

		while (is >> s) {
			if (s == "Monkey") break;
			if (s == "Starting") {
				is >> s;
				while (is >> s) startingItems.push(stoi(s));
			}
			else if (s == "Operation:") {
				string x;
				is >> s >> s >> s >> s >> x;
				if (s == "*") {
					if (x == "old") op = new Square();
					else op = new Multiplication(stoi(x));
				}
				else if (s == "+") op = new Addition(stoi(x));
			}
			else if (s == "Test:") {
				is >> s >> s >> s;
				test = stoi(s);
				modulo *= stoi(s);
			}
			else if (s == "If") {
				is >> s;
				if (s == "true:") {
					is >> s >> s >> s >> s;
					trueVal = stoi(s);
				}
				else if (s == "false:") {
					is >> s >> s >> s >> s;
					falseVal = stoi(s);
					monkeys.push_back(Monkey(startingItems, op, Test(test, trueVal, falseVal)));
					while (!startingItems.empty()) startingItems.pop();
				}
			}
		}
	}
	cout << "here1" << endl;

	for (int i = 0; i < 10000; ++i) {
		cout << "round " << i << endl;
		for (int j = 0; j < monkeys.size(); ++j) {
			cout << "monkey " << j << endl;
			while (!monkeys[j].items.empty()) {
				Monkey& monkey = monkeys[j];
				++monkey.inspectCount;
				long long worryLevel = monkey.items.front();
				monkey.items.pop();
				(*(monkey.operation))(worryLevel);
				worryLevel %= modulo;
				// worryLevel /= 3;
				int monkeyToThrowTo = monkey.test(worryLevel);
				monkeys[monkeyToThrowTo].items.push(worryLevel);
			}
		}
	}

	long long max1 = monkeys[0].inspectCount, max2 = monkeys[1].inspectCount;
	for (int i = 2; i < monkeys.size(); ++i) {
		if (monkeys[i].inspectCount > max1 || monkeys[i].inspectCount > max2) {
			if (max1 < max2) max1 = monkeys[i].inspectCount;
			else max2 = monkeys[i].inspectCount;
		}
	}
	cout << max1 << " " << max2 << endl;

	//cout << "Part 1: " << (long long)max1 * max2 << endl;
	cout << "Part 2: " << (long long)max1 * max2 << endl;

	return 0;
}