#include "Value.h"

Value::Value() {}
Value::Value(string name, rational<int> prob)
{
	this->name = name;
	this->val = prob;
}