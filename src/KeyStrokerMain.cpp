/*
 * KeyStrockerMain.cpp
 *
 *  Created on: 18 déc. 2010
 *      Author: canard
 */
#include "KeyStroker.h"

#include <string>

int main(int argc, char * argv[])
{
	std::string message = "Ouai gros";
	KeyStroker::StrokeKey(message.c_str());
	return 0;
}
