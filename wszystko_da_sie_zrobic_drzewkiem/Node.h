#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <rational.hpp>
#include "Value.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

class Node
{
public:

	Value value;

	int nodesCount = 2;
	Node *nodes;
	Node *parentNode = nullptr;

	Node();
	Node(Value val, int nodesCount);
	Node(Value val, int nodesCount, Node parent);

	void print(int layer = 0);
	rational<int> calculateProbability(vector<string> flow, rational<int> prob = {1, 1});
	void createBasicTree(vector<Value> values, int iterations);
	void addChild(Node child, int index);
};

