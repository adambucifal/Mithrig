#pragma once

#include <maya/MString.h>


namespace Mithrig::Utilities::Strings 
{
	MString get(char c, int count);
	MString pad(int num, int padding);
	int sequential_count(const MString& str, char c);
}
