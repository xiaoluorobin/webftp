//============================================================================
// Name        : testinclude.cpp
// Author      : robinluo
// Version     :
// Copyright   : robin's study coding
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "socketclient.h"
using namespace std;

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	socketclient client;
	client.start();
	return 0;
}
