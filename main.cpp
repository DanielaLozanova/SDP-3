#include <iostream>
#include <fstream>
#include <string>
#include "ExprTree.h"

using namespace std;

void readFromTextFile(const string& path)
{
	ifstream input(path);
	if (!input) {
		cerr << "Cannot load this file\n";
		return;
	}

	string expr;

	while (!input.eof()) 
	{
		getline(input, expr);
		Tree tree(expr);
		tree.create();
		tree.postOrd();
		tree.printInfix();
		cout << tree.evaluate() << endl;
	}

	input.clear();
	input.close();
}

int main() {

	string path = "file.txt";
	readFromTextFile(path);

	return 0;
}