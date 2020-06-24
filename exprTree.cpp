#include "ExprTree.h"
#include <iostream>

using namespace std;

void Tree::create()
{
	for (int i = 0; i < expr.size(); ++i)
	{
		if (expr[i] == ' ') continue;
		add(root, makeString(i));

		while (isNum(expr[i])) { ++i; }
	}
}

void Tree::printInfix() const
{
	inOrder(root);
	cout << endl;
}

bool Tree::isNum(char symbol) const
{
	return symbol - '0' >= 0 && symbol - '0' <= 9;
}

bool Tree::isOperation(const string& expr) const
{
	return expr == "*" || expr == "-" || expr == "+";
}

bool Tree::isVariable(const string& expr) const
{
	return expr >= "a" && expr <= "z";
}

const string Tree::makeString(size_t pos) const
{
	string res;

	res += expr[pos];
	if (isNum(expr[pos]))
	{
		++pos;
		while (isNum(expr[pos]))
		{
			res += expr[pos];
			++pos;
		}
	}

	return res;
}

int Tree::charToInt(Node* root) const
{
	int cToI, in = 0, i = 0;
	string s = root->data;
	while (s[i] >= '0' && s[i] <= '9')
	{
		cToI = s[i] - '0';
		in = 10 * in + cToI;
		++i;
	}
	return in;
}

void Tree::inOrder(Node *root) const
{
	if (!root) return;

	if (isOperation(root->data)) cout << "(";

	inOrder(root->left);
	cout << root->data;
	if (isComplete(root->right)) 
	{
		inOrder(root->right);
		cout << ")";
	}
	else inOrder(root->right);
}

void Tree::add(Node *&root, const string& value)
{
	if (!root)
	{
		root = new Node(value);
		return;
	}

	bool isCompleteTree = isComplete(root->left);
	if (root->left && isCompleteTree)
	{
		add(root->right, value);
	}
	else if (root->left && !isCompleteTree)
	{
		add(root->left, value);
	}
	else add(root->left, value);
}

bool Tree::isComplete(Node *root)const
{
	if (!root) return false;
	if (!isOperation(root->data)) return true;

	isComplete(root->left);
	isComplete(root->right);
}

void Tree::clear(Node *&root)
{
	if (!root) return;

	clear(root->left);
	clear(root->right);

	delete root;
}

int Tree::evaluate()
{
	return eval(root);
}

void Tree::postOrder(Node *root) const
{
	if (!root) return;
	postOrder(root->left);
	postOrder(root->right);
	cout << root->data << " ";
}

void Tree::postOrd() const
{
	postOrder(root);
	cout << endl;
}

int Tree::eval(Node *root) 
{
	if (!root)
		return 0;

	if (!root->left && !root->right) 
	{
		if (isVariable(root->data))
		{
			if (isVariableExist(root)) 
			{
				return findVariableNum(root);
			}
			else {

				int a;
				cin >> a;
				variable.push_back(make_pair(root->data[0], a));
				return a;
			}
		}
		else return charToInt(root);
	}


	int l_val = eval(root->left);
	int r_val = eval(root->right);

	if (root->data == "+")
		return l_val + r_val;

	if (root->data == "-")
		return l_val - r_val;

	if (root->data == "*")
		return l_val * r_val;
}

bool Tree::isVariableExist(Node *root) const 
{
	for (size_t i = 0; i < variable.size(); ++i) 
	{
		if (variable[i].first == root->data[0]) return true;
	}

	return false;
}

int Tree::findVariableNum(Node *root) const 
{
	for (size_t i = 0; i < variable.size(); ++i) 
	{
		if (variable[i].first == root->data[0])
			return variable[i].second;
	}
}