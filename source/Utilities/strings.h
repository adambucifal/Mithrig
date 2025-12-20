#pragma once

#include <maya/MString.h>


namespace Mithrig::Strings 
{

	MString get(char c, int count);
	MString pad(int num, int padding);

	MString short_name(const MString& long_name);

	int sequential_count(const MString& str, char c);

}
