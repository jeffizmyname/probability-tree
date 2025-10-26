#include "Node.h"

Node::Node() : nodes(nullptr) {}

Node::Node(Value val, int nodesCount)
{
	this->value = val;
	this->nodesCount = nodesCount;
	this->nodes = new Node[nodesCount];
}

Node::Node(Value val, int nodesCount, Node parent)
{
	this->value = val;
	this->nodesCount = nodesCount;
	this->nodes = new Node[nodesCount];
	parentNode = &parent;
}

void Node::print(int layer)
{
	if (parentNode)
		cout << "Layer: " << layer << " Node: " << value.name << " value:  " << value.val << " from " << parentNode->value.name << " has " << nodesCount << endl;
	else
		cout << "Layer: " << layer << " Node: " << value.name << " value:  " << value.val << " from root has " << nodesCount << endl;
	layer++;
	for (int i = 0; i < nodesCount; i++)
	{
		nodes[i].print(layer);
	}
}

rational<int> Node::calculateProbability(vector<string> flow, rational<int> prob) {
	rational<int> newProb = prob;
	for (int i = 0; i < flow.size(); i++) {
		for (int j = 0; j < nodesCount; j++) {
			if (nodes[j].value.name == flow[i]) {

				newProb *= nodes[j].value.val;

				flow.erase(flow.begin());
				if (nodes[j].nodesCount == 0) {
					return newProb;
				}
				else {
					return nodes[j].calculateProbability(flow, newProb);
				}
			}
		}
	}
	return newProb;
}

void Node::createBasicTree(vector<Value> values, int iterations)
{
	int valuesAmmount = values.size();

	if (iterations > 0) {
		for (int i = 0; i < valuesAmmount; i++) {

			Value childValue = values[i];
			int childNodes = (iterations == 1 ? 0 : valuesAmmount);

			Node childNode(childValue, childNodes);
			addChild(childNode, i);

			nodes[i].createBasicTree(values, iterations - 1);
		}
	}
}

void Node::addChild(Node child, int index) 
{
	child.parentNode = this;
	nodes[index] = child;
}
