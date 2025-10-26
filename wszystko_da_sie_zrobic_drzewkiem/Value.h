#pragma once
#include <string>
#include <rational.hpp>

using std::string;
using boost::rational;

class Value
{
public:
	string name;
	
	rational<int> val;

	Value();
	Value(string name, rational<int> prob = {1, 1});

};

	