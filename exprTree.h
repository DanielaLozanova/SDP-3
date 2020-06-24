#ifndef _HEADER_EXPRESSIONTREE_INCLUDED_
#define _HEADER_EXPRESSIONTREE_INCLUDED_

#include <string>
#include <vector>
#include <utility>

using namespace std;

struct Node {
	string data;
	Node *left, *right;

	Node(const string& data, Node *left = nullptr, Node *right = nullptr)
		: data(data), left(left), right(right) {}
};

class Tree {
private:
	Node *root;
	string expr;
	vector<pair<char, int>> variable;
private:
	bool isNum(char symbol)const;
	bool isOperation(const string& expr)const;
	bool isVariable(const string& expr)const;
	const string makeString(size_t pos)const;
	int charToInt(Node* root) const;
	void inOrder(Node *root) const;
private:
	void add(Node *&root, const string& value);
	bool isComplete(Node *root)const;
	void clear(Node *&root);
	int eval(Node * root);
	bool isVariableExist(Node * root) const;
	int findVariableNum(Node * root) const;
	void postOrder(Node * root) const;
public:
	Tree(const string& s) : root(nullptr), expr(s), variable() {}
	~Tree() { clear(root); }
	void create();
	void printInfix() const;
	int evaluate();
	void postOrd() const;

};

#endif