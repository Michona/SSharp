#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "pch.h"
#include "Holder.h"


Holder::Holder()
{
	GlobalFunctions.push_back(Function("read", 0));
	GlobalFunctions.push_back(Function("write", 1));
}


Holder::~Holder()
{
}
